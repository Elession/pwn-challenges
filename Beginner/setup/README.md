# Name
setup

## Learning Objective
Help users install needed tools for binary exploitation/pwn.

Expain the use of each tool

## Description 
The start of your pwn journey.

## Difficulty:
easy

## Guide
From the challenge/exercise description, download `setup.sh` script. We will be using this in your Kali virtual machine (VM).

### Virtual Machine (VM)
Virtual machines allows you to run different operating systems in an virtualised environment. To run virtual machines, we need a virtualisation software.

### Oracle VirtualBox
One of the more popular platforms to run VMs. You can also run VMWare Workstation but we will be using Vbox for the setup.

### Linux 
Linux is an open source operating system with its own set of functionalities. Compared to Windows, Linux is highly customisable, which is why different communities have introduced their own version of Linux with their own set of packages, tools, etc. Hence the term - distributions/distros.

Examples of distributions include:
- Ubuntu
- Linux Mint
- Arch Linux
- Fedora 

and etc...

### Kali Linux
Kali distro is tailored towards penetration testing. Kali is the distro we will be using for the exercises/challenges. 

Install Kali from this [site](https://www.kali.org/get-kali/#kali-platforms). (Install the ISO image)

Tutorial to setup the VM: [here](https://phoenixnap.com/kb/how-to-install-kali-linux-on-virtualbox).

Once you have done the installation process for your VM, Do the following:

1. On your VM, you should see a line of configuration options (File, Machine, View etc), click on `Devices`.
2. Hover to `Shared clipboard`, change option to `Host to Guest` (or `bidrectional` if you want to copy paste back and forth from your host and VM)
3. Do the same for `Drag & Drop`

After you have done so, you can drag and drop `setup.sh` from your host into the Kali Desktop.

1. Open the terminal (or `Ctrl + Alt + T`)
2. `cd Desktop`
3. `chmod +x setup.sh`
4. `./setup.sh`

If the system prompts for service restart, just press `enter` to accept.

### Brief explaination on tools you will be using
Visual studio code - same code editor but on Linux, enter `code-oss` in your terminal to access it

pwntools - python library for exploit development/CTF

Pwndbg - additional features & QoL changes for debugging programs

ROPgadgets - find gadgets in your programs (for later exercises)

pwninit - automates finding linker for relevant libc version (for later exercises)

### Once done
Go to your terminal and enter the following:
1. `nc SERVICE PORT`
2. when prompted, read the introduction and enter accordingly

## Solution
1. netcat service and type `READY` 

## Hints
NIL

## Attached Files
- setup.sh

## Resources
- https://phoenixnap.com/kb/how-to-install-kali-linux-on-virtualbox
- https://www.kali.org/get-kali/#kali-platforms
- https://www.geeksforgeeks.org/linux-history/
- https://github.com/pwndbg/pwndbg
- https://github.com/io12/pwninit

## Flag
TBD