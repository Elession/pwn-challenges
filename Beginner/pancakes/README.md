# Challenge Name
pancakes

## Learning Objective
Understand stack concepts

## Description 
Basics of pwn 101 Part 1

## Difficulty:
Guided (intro)

## Guide
One of the important concepts when solving pwn challenges is the **stack memory**.

### What is the stack memory?
It actually resides in your RAM in your computer. There are also other things in the memory but we will focus on this for now.

You can imagine the stack as like the exercise name - a pancake stack.

How does it work then?

### Last-In First Out (LIFO)
The stack uses the **LIFO** method to process the memory. What this means it is newer values on the stack are always taken out first. (See next section)


### PUSH/POP
As you might have recalled from your data structure modules, you would have heard of **PUSH** or **POP**. This concept can be applied here.

Let's take the following as an example:

|C|
:-:
|B|
|A| 

`C` is at the top of the stack.

### POP
Let's say `C` needs to be used or needs to get off the stack. We will then **POP** it.

|B|
:-:
|A| 

### PUSH
We want to store another value, `D` for later use. Let's **PUSH** it onto the stack using the first example.

|D|
:-:
|C|
|B|
|A| 

### How to view the stack/common misconception
When everyone is learning about the stack, there is always this confusion:

- does the stack start from the bottom or the top?
- is it top to bottom/bottom to top??
etc etc.

In order to identify, we always talk about **higher** and **lower** addressing.

In stack, the bottom of the stack always has a **higher** address, and the top of the stack has a **lower** address.

For example:

Let's say each item on the stack is 8 bytes long and the start of the stack starts at `A` at `0x100`

This means `A` has a **higher** address.

|C|
:-:
|B|
|A| 

`B` would then be at a lower address of `0xF8` (`0x100` - `0x8` = `0x0F8`).

Similarly, `C` would a lower address of `0xF0` (`0x0F8` - `0x8` = `0x0F0`).


### Exercise
Go to your terminal and netcat into the service provided in the exercise description

## Solution


## Hints


## Attached Files


## Resources


## Flag