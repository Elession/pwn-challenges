from pwn import *

# remote
p = remote("SERVER", PORT)

# answer
payload = b'0x1257_0x8'

# send answer
p.sendline(payload)
p.interactive()