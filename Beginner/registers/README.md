# Challenge Name
registers

## Learning Objective
Learn about the different registers and their usage

## Description 
Basics of pwn 101 part 2

## Difficulty:
guided (intro)

## Guide
What exactly are **registers**?

They are actually computer memories that resides in your CPU. This is to allows for the fastest access to memory.

Each register is able to contain data (values, addresses, etc.). But we will categorise and talk about the more important registers.

### `RBP` & `RSP`
`RBP` register stands for **Base Pointer**. This register points to the **higher address** of the **current stack frame** (covered in pancakes).

`RSP` register stands for **Stack Pointer**. This register points to the **lower address** of the **current stack frame**.

In actual practice, they always work together so that they can help us reference to any values/addresses.

Example:

|C|
:-:
|B|
|A|

Currently, the `RBP` register is pointing at `A`, and `RSP` register is pointing at `C`.

Let's say we need `A` in `RAX` register, it can do the following:

```
ADD RSP, 0x10
POP RAX
```

`ADD RSP, 0x10` moves the RSP up by 16 bytes.

This means the stack frame is now smaller and the `RSP` is now pointing at `A`. Based on where `RSP` ia poinr


### How do we know what is in the current stack frame/size of stack frame?

`RBP` - `RSP` = stack frame


### `RIP`
`RIP` is the **instruction pointer**. It points to the **next** intruction that needs to be excecuted.

Example:

```
# RAX: 0
# RIP: 0x40000


0x40000: ADD RAX, 3
0x40001: SUB RAX, 1
```

`RIP` is currently pointing to instruction at `0x40000`, but it is not executed yet. Let's run next intruction:

```
# RAX: 3
# RIP: 0x40001


0x40000: ADD RAX, 3
0x40001: SUB RAX, 1
```

3 is finally added to `RAX`, and now `RIP` is pointing to the `0x40001` intruction. 

### Other registers
You will encounter other types of registers. For example:

- `RAX`
- `RBX`
- `RSI`
- `RDI`
- `R9`
...and so on

We treat these as **general-purpose** registers, which means they can be used to just hold values or addresses as when the program requests for it.

### Assembly Language
From the example just now:

```shell
ADD RAX, 3
```

That is assembly language (or ASM). You can see these after you compile a program.

For ASM basics, you can just watch this [link](https://youtu.be/75gBFiFtAb8?si=dJH9dxozjtBGo6CP).

Once you start to ascend and learn new concepts, there will be different types of intructions you will encounter and need to understand what they do.

But not to worry, we are starting as beginners.

Also, always remember that Google is your friend :)

### Exercise
netcat into the service using your terminal (based on challenge description):

```shell
nc <IP> <port>
```

You would observe this:

```shell
WELCOME TO THE REGISTER EXERCISE

Here are the current contents of the registers:

----------------------------------
|   Register   |     Value       |
----------------------------------
|     RAX      |    0x0          |
|     RBX      |    0x1          |
|     RCX      |    0x10         |
|     RDX      |    0x0          |
|     RSI      |    0x0          |
|     RDI      |    0xC          |
----------------------------------

Here are some instructions: 
MOV RAX, 0x1234
MOV RBX, RAX
ADD RBX, 0x23
SUB RDI, 0x4
ADD RSI, RDI
What are the values in RBX and RSI after running the instructions above?

Put your answer in (ans1_ans2) format:
```

Let's slowly go through each instruction one by one:

```shell
MOV RAX, 0x1234 # This means `RAX` new value is `0x1234`.
```

```shell
MOV RBX, RAX # `RBX` value is replaced with `0x1234`.
```

```shell
ADD RBX, 0x23 # `RBX`: 0x1234 + 0x23 = 0x1257
```

Now we have `RBX` value.

```shell
SUB RDI, 0x4 # `RDI`: 0xC - 0x4 = 0x8
# remember, they are hexademicals
```

```shell
ADD RSI, RDI # `RSI`: 0x0 + 0x8 = 0x8
```

Your final answer:
0x1257_0x8

```shell
Put your answer in (ans1_ans2) format: 0x1257_0x8
Correct! Here's your flag:
CTF{PLACEHOLDER}
```

## Solution
0x1257_0x8

## Hints
none needed 

## Attached Files
none

## Resources
- https://youtu.be/75gBFiFtAb8?si=z0fzf-r0g9lfP8NH

## Flag
TBD