# Setting up Wireless Access Point

1. First update and upgrade raspberry pi software
```bash
sudo apt update
sudo apt upgrade
```

2.Install our two packages hostapd, dnsmasq and iptables.
```bash
sudo apt install hostapd dnsmasq iptables
```

3. Stop the packages from running as we haven't configured them yet.
```bash
sudo systemctl stop hostapd
sudo systemctl stop dnsmasq
```
