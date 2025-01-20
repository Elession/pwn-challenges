FROM ubuntu:18.04
RUN apt-get update
RUN apt-get install -y ucspi-tcp-ipv6 gcc

RUN useradd -u 8888 -m pwn
RUN mkdir -p /home/pwn
RUN chown -R pwn:pwn /home/pwn

ADD ./challenge/flag.txt /home/pwn/flag.txt
ADD ./challenge/chall.c /home/pwn/chall.c
RUN gcc -fno-stack-protector -no-pie -o /home/pwn/chall /home/pwn/chall.c
RUN chmod +r /home/pwn/flag.txt
RUN chmod +x /home/pwn/chall
WORKDIR /home/pwn

CMD ["tcpserver","-t","50","-u","8888","-g","8888","-RHl0","0.0.0.0","8881","/home/pwn/chall"]
