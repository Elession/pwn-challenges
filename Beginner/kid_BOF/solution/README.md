# Challenge Name
baby_BOF

## Learning Objective
Understand simple buffer overflow and `gets` vulnerability.

## Description 
Order me more pizzas.

## Difficulty:
Guided (Easy)

## Guide
Source code looks fairly long but it is a simple code, let's try to highlight the main points:

1. When a segmentation fault is triggered while binary is running, it will run the `pizza` function , which will read the flag
2. `burger` function is called, which asks for a input of 200 bytes. It also has the vulnerable c function `gets`, which allows us to buffer overflow.

We can try to do this: 

#### To find the offset needed:
1. use `cyclic 300` in pwndbg (this generates the de bruijin sequence)
2. `break main` and run the program (C)
3. you should see that the `RSP` pointer contains `caaaaaab` and beyond. We just need the first 8 bytes because that is where the return address is.

```sh
pwndbg> cyclic -l caaaaaab
Finding cyclic pattern of 8 bytes: b'caaaaaab' (hex: 0x6361616161616162)
Found at offset 216
```

## Solution
Refer to solve.py.

## Hints
1.  Have you considered saved edp address?

## Attached Files
- kid_BOF.c
- kid_BOF_bin

## Resources
- http://ctf101.org

## Flag
TBD
