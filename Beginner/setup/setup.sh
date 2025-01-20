#!/bin/bash

echo "[*] Updating & upgrading"
sudo apt update && sudo apt upgrade -y

echo "[*] Installing Vim edtior"
sudo apt install -y vim

echo "[*] Installing python3, pwntools, ROPgadget, wget"
sudo apt install -y python3 python3-pip python3-dev git libssl-dev libffi-dev build-essential python3.13 python3.13-venv wget
sudo pip install pwntools --break-system-packages

echo "[*] Installing Visual Studio Code"
sudo apt install -y code-oss

echo "[*] Installing gdb"
sudo apt install -y gdb

echo "[*] Installing pwninit"
wget https://github.com/io12/pwninit/releases/download/3.3.1/pwninit .
chmod 755 pwninit

echo "[*] Installing pwndbg"
git clone https://github.com/pwndbg/pwndbg
cd pwndbg
./setup.sh

