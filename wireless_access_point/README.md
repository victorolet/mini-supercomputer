# Setting up Wireless Access Point

1. First update and upgrade raspberry pi software
```bash
sudo apt update
sudo apt upgrade
```

2. Install our two packages hostapd, dnsmasq and iptables.
```bash
sudo apt install hostapd dnsmasq iptables
```

3. Stop the packages from running as we haven't configured them yet.
```bash
sudo systemctl stop hostapd
sudo systemctl stop dnsmasq
```
4. Modify the dhcpd configuration
```bash
sudo nano /etc/dhcpcd.conf
```
5. Add the following code to the bottom of the file. then save it and quit.
```bash
interface wlan0
  static ip_address=192.168.0.1/24
  nohook wpa_supplicant
```
6. Reload the dhcpd service
```bash
sudo systemctl restart dhcpcd
```

7. Edit hostapd configuration
```bash
sudo nano /etc/hostapd/hostapd.conf
```

8. Add the following lines to the file. Do NOT forget to change the ssid and wpa_passphrase to your own password. Make sure it is secure enough.
```bash
interface=wlan0
driver=nl80211

hw_mode=g
channel=6
ieee80211n=1
wmm_enabled=0
macaddr_acl=0
ignore_broadcast_ssid=0

auth_algs=1
wpa=2
wpa_key_mgmt=WPA-PSK
wpa_pairwise=TKIP
rsn_pairwise=CCMP

# This is the name of the network
ssid=Pi_cluster
# The network passphrase
wpa_passphrase=minisupercomputer
```

9. Run the following command to edit hostapd
```bash
sudo nano /etc/default/hostapd
```
Find the line 
#DAEMON_CONF=""
and Replace it with the following code
```bash
DAEMON_CONF="/etc/hostapd/hostapd.conf"
```
Now save and Quit

10. Run the following command to edit the second configuration file which is located within init.d folder
```bash
sudo nano /etc/init.d/hostapd
```
Find the line 
#DAEMON_CONF=""
and Replace it with the following code
```bash
DAEMON_CONF="/etc/hostapd/hostapd.conf"
```
Now save and Quit. hostapd is now setup

13. Next step is to setting up dnsmasq.
First, rename the current dnsmasq file as we dont need it for our configuration.
```bash
sudo mv /etc/dnsmasq.conf /etc/dnsmasq.conf.orig
```
14. Now create a new file using nano comand
```bash
sudo nano /etc/dnsmasq.conf
```
15. Add the following commands to the file to tell dnsmasq how to handle all the incoming connections.
```bash
interface=wlan0       # Use interface wlan0  
server=1.1.1.1       # Use Cloudflare DNS  
dhcp-range=192.168.0.50,192.168.0.150,12h # IP range and lease time  
```
Now save and quit the file

16. Now we need to configure Raspberry Pi to forward all traffic from wlan0 connection to ethernet connection. We must do this by editing sysctl.conf file.
```bash
sudo nano /etc/sysctl.conf
```

17. Find
```bash
#net.ipv4.ip_forward=1
```
Replace it with
```bash
net.ipv4.ip_forward=1
```

18. Run the following command to activate it immediately 
```bash
sudo sh -c "echo 1 > /proc/sys/net/ipv4/ip_forward"
```

19. Configure a NAT between our wlan0 interface and our eth0 interface. 
```bash
sudo iptables -t nat -A POSTROUTING -o eth0 -j MASQUERADE
```

20. Save the new rules somewhere so they are loaded back in on every boot.
```bash
sudo sh -c "iptables-save > /etc/iptables.ipv4.nat"
```

21. To make this file loaded back in on every reboot, modify the rc.local file.
```bash
sudo nano /etc/rc.local
```

22. 

