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

16. 