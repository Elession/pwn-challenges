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

What we need to do:
1. Find the exact offset before it overflows
2. Find return address of `win` address

To find the offset needed:
1. use `cyclic 100` in pwndb
2. `break main` and run the program (C)
3. you should see that the `RSP` pointer contains `faaaaaaa` and beyond. We just need the first 8 bytes because that is where the return address.

```shell
pwndbg> cyclic -l faaaaaaa
Finding cyclic pattern of 8 bytes: b'faaaaaaa' (hex: 0x6661616161616161)
Found at offset 40
```

To find the 

## Solution
Refer to solve.py

## Hints
1. 

## Attached Files
baby_R2W.c
baby_R2W_bin

## Flag