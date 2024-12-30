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

What to consider:
1. buffer (20 bytes)
2. saved edp address (4 bytes) 

To overflow, we thus need to send at least 25 bytes of input.


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
