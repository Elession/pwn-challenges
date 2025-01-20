# Challenge Name
baby_BOF

## Learning Objective
Understand simple buffer overflow and `gets` vulnerability.

## Description 
We have a buffer overflow exercise here. Identify the exact offset that the binary overflows. Put the offset in `MACCTF{answer}` format

## Difficulty:
Guided (Easy)

## Guide
Source code looks fairly long but it is a simple code, let's try to highlight the main points:

1. When a segmentation fault is triggered while binary is running, it will run the sigsegv_trigger function , which contains the flag.
2. `vuln` function is called, which asks for a input of 20 bytes. It also has the vulnerable c function `gets`, which allows us to buffer overflow.

In other programs, there will be other items on the stack as well. 

Which is why we will learn to find the number of bytes to overflow ourselves


#### To find the offset needed:
1. use `cyclic 100` in pwndbg (this generates the de bruijin sequence)
2. `break main` to set a breakpoint at main
3. `c` or `continue` to continue running program after breakpoint.
4. you should see that the `RSP` pointer contains `faaaaaaa` and beyond. We just need the first 8 bytes because that is where the return address is.

```shell
pwndbg> cyclic -l faaaaaaa
Finding cyclic pattern of 8 bytes: b'faaaaaaa' (hex: 0x6661616161616161)
Found at offset 40
```

## Solution
Refer to solve.py.

## Hints
1.  Have you considered saved edp address?

## Attached Files
- chall.c
- chall

## Resources
- http://ctf101.org

## Flag
`MACCTF{25}`
