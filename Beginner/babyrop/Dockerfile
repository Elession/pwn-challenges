FROM ubuntu:24.04
RUN apt-get update
RUN apt-get update && apt-get install -y \
    gcc \
    git \
    build-essential \
    ucspi-tcp \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

RUN useradd -u 8888 -m pwn
RUN mkdir -p /home/pwn
RUN chown -R pwn:pwn /home/pwn

RUN git clone https://github.com/Elession/pwn-challenges.git /home/pwn
RUN mv /home/pwn/Beginner/babyrop/challenge/chall /home/pwn
RUN mv /home/pwn/Beginner/babyrop/challenge/chall.c /home/pwn
RUN mv /home/pwn/Beginner/babyrop/challenge/flag.txt /home/pwn
RUN rm -r /home/pwn/Beginner
RUN rm -r /home/pwn/Challenges
RUN rm -r /home/pwn/docker
RUN rm /home/pwn/Template.md
RUN rm /home/pwn/README.md


RUN chmod +r /home/pwn/flag.txt
RUN chmod +x /home/pwn/chall
WORKDIR /home/pwn

CMD sh -c 'echo "${FLAG_VALUE}" > /home/pwn/flag.txt && tcpserver -t 50 -u 8888 -g 8888 -RHl0 0.0.0.0 10000 /home/pwn/chall'