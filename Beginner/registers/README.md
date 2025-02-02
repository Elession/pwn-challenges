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

Other registers not explained will be treated as general-purpose registers (used when needed).

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

### Assembly Language
For ASM basics, you can just use this [link](https://www.tutorialspoint.com/assembly_programming/assembly_basic_syntax.htm).

Once you start to ascend and learn new concepts, there will be newer types of intructions, but they realistically won't be that daunting to learn.

Always remember that Google is your friend :)

## Solution
0x1257_0x8

## Hints
none needed 

## Attached Files
- chall.c
- chall

## Resources
- https://www.tutorialspoint.com/assembly_programming/assembly_basic_syntax.htm

## Flag
TBD