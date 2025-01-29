FROM ubuntu:24.04
RUN apt-get update
RUN apt-get update && apt-get install -y \
    gcc \
    git \
    ucspi-tcp \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

RUN useradd -u 8888 -m pwn
RUN mkdir -p /home/pwn
RUN chown -R pwn:pwn /home/pwn

RUN git clone https://github.com/Elession/pwn-challenges.git /tmp
RUN mv /tmp/Beginner/kidrop/challenge/chall /home/pwn
RUN mv /tmp/Beginner/kidrop/challenge/chall.c /home/pwn
RUN mv /tmp/Beginner/kidrop/challenge/flag.txt /home/pwn
RUN rm -rf /tmp/*
RUN rm -r /tmp/.git
RUN chmod +r /home/pwn/flag.txt
RUN chmod +x /home/pwn/chall
WORKDIR /home/pwn

CMD sh -c 'echo "${FLAG_VALUE}" > /home/pwn/flag.txt && tcpserver -t 50 -u 8888 -g 8888 -RHl0 0.0.0.0 80 /home/pwn/chall'