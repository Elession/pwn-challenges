# Challenge Name
overflowme

## Learning Objective
understand simple buffer overflow. Experiment with the stack memory. 

## Description 
We have a buffer overflow exercise here. Identify the offset needed before it overflows. Put the offset in `MACCTF{answer}` format

## Guide
1. read the main code, identify the number of bytes the buffer can hold
2. don't forget about the 


## Attached Files
overflowme.c

## Detailed Solution
1. payload: buffer (32 bytes) + saved edp (4 bytes) + any added input

## Flag
`MACCTF{104}`