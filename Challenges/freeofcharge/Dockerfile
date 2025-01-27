FROM ubuntu:24.04
RUN apt-get update
RUN apt-get install -y ucspi-tcp-ipv6 gcc

RUN useradd -u 8888 -m pwn
RUN mkdir -p /home/pwn
RUN chown -R pwn:pwn /home/pwn

ADD ./flag.txt /home/pwn/flag.txt
ADD ./chall /home/pwn/chall
RUN chmod +x /home/pwn/chall
WORKDIR /home/pwn

CMD sh -c 'echo "${FLAG_VALUE}" > /home/pwn/flag.txt && tcpserver -t 50 -u 8888 -g 8888 -RHl0 0.0.0.0 10000 /home/pwn/chall'