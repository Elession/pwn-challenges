# Challenge Name
baby_BOF

## Learning Objective
Understand simple buffer overflow and `gets` vulnerability.

## Description 
We have a buffer overflow exercise here. Identify the exact offset that the binary overflows. Put the offset in `MACCTF{answer}` format

## Difficulty:
Guided (Easy)

## Guide
Let's look at the source code:

In `main`:

```c
    // runs sigsegv_trigger() when a segmentation fault occurs
    signal(SIGSEGV, sigsegv_trigger);
```

From the code comment, we need to trigger a **segmentation fault** to run `sigsegv_trigger` function.


In `sigsegv_trigger`:

```c
    printf("Here is your flag: \n");
    FILE *file = fopen("flag.txt", "r");
    char flag[256];
    fgets(flag, 256, file);
    printf("%s", flag);
    fclose(file);
```

This will give us our flag. This begs the question...

### What is Segmentation Fault?

This is an error that occurs when a program attempts to access memory that is not permitted to the user. 

For example: reading/writing outside given boundaries (aka Buffer overflow)





### To find the offset needed:
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
TBD
