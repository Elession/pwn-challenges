1. babybof
2. babyr2w
3. babyrop
4. kidbof
5. kidr2w
6. kidrop
7. breakthebank
8. coffeebean
9. iridium
10. libraryc
11. piefect
12. rollthedice
13. babyshellcode



## Alternative Dockerfile
FROM ubuntu:24.04
RUN apt-get update
RUN apt-get install -y ucspi-tcp-ipv6 gcc

RUN useradd -u 8888 -m pwn
RUN mkdir -p /home/pwn
RUN chown -R pwn:pwn /home/pwn

ADD ./flag.txt /home/pwn/flag.txt
ADD ./chall.c /home/pwn/chall.c
RUN gcc -o /home/pwn/chall.c /home/pwn/chall
RUN chmod +r /home/pwn/flag.txt
RUN chmod +x /home/pwn/chall
WORKDIR /home/pwn

CMD ["tcpserver","-t","50","-u","8888","-g","8888","-RHl0","0.0.0.0","8881","/home/pwn/chall"]