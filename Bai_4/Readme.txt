Set up wifi, ssh and uart

Quick start

B1, Enable Uart:

Sau khi flash image vao SD card, truy cap vao boot partion tren the nho, them dong sau vao cuoi file config.txt
enable_uart=1
Cam the nho vao board va cap nguon.

B2, Control PI qua cong serial
-Cam cab TTY-USB vao may tinh, su dung picocom de ket not vao terminal cua PI
sudo picocom /dev/ttyUSB0 -b 115200

Login: 
username: pi
pass: raspberry

B3, Config wifi
sudo raspi-config
SSID: Ten wifi
Passphrase: passworld

ping google.com

B4, Set static IP address
sudo apt-get update
sudo apt-get install vim
vim etc/dhcpcd.conf
interface wlan0
static ipaddress=192.168.10.97/24
B5, Enable ssh
sudo raspi-config
reboot va check lai dia chi ip

B6, Ket noi voi PI qua ssh

Mo terminal moi
ssh pi@192.168.10.97

