# Mini-Supercomputer

This document explains the process of setting up and running a mini-supercomputer using 8 Raspberry Pi cluster.
 
## Parts used to build the cluster
1. 8 x Raspberry Pi 4B
2. Cluster case (C4Labs 8 Slot Cluster Cloudlet)
3. Ethernet Switch
4. Ethernet Cables
5. 8 x PoE+ hat
6. SSD harddisk

## Configuring Raspberry Pi operating system
1. Install Raspberry Pi Imager on you laptop/PC
2. Connect microSD card to you PC and start the installation process
3. Click on the “CHOOSE OS” button and select ‘Raspberry Pi OS (other) “ and then “Raspberry Pi OS Lite (64-bit).
4. Click on the “Advanced” menu. Set the hostnames (for eg.pi1.local,...pi8.local). 
5. Enable SSH server and setup username and password
6. Save the settings and choose storage and then click on the “WRITE” button to write the operating system to the microSD card. Wait until it finishes and then eject the microSD and install it in Raspberry Pi.

## Set up the Raspberry pi

* To change password or timezone or make any other changes after installing OS
```bash
   sudo raspi-config
```

* Make sure the system time is right - The SLURM scheduler require accurate system time. Install the ntpdate package to sync the system time periodically in the background.
```bash
   sudo apt install ntpdate -y
```


## References 
https://glmdev.medium.com/building-a-raspberry-pi-cluster-784f0df9afbd

