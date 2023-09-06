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
