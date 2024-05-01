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

Note: In a cluster all raspberry Pis should have same version of operating system to work properly. 

## Set up the Raspberry pi

* To change password or timezone or make any other changes after installing OS
    ```bash
   sudo raspi-config
    ```

* Make sure the system time is right - The SLURM scheduler require accurate system time. Install the ntpdate package to sync the system time periodically in the background.
    ```bash
   sudo apt install ntpdate -y
    ```

* Configure static ip address for raspberry pi
    ```bash
    sudo nano /etc/dhcpcd.conf
    ```

    Now scroll down the bottom and add the following lines
    ```bash
    interface eth0
    metric 300
    static ip_address=192.168.0.40/24
    static routers=192.168.0.1
    static domain_name_servers=192.168.0.1

    interface wlan0
    metric 200
    ```
    Don't forgot to change the ip addresses

* Reboot the Raspberry Pi to apply the changes
    ```bash
    sudo reboot
    ```

* Power off the Raspberry Pi
    ```bash
    sudo poweroff
    ```
In a Raspberry Pi cluster the login node should know the ip addresses of the worker node and the worker node should know the ip address of login node. So, the next step is to configure static ip address for the Raspberry pis.

Then configure wireless access point

Next step is to configure the storage

Then configure the login node (same raspberry pi that is used as wireless access point)

Configure the worker nodes

## References 
1. Raspberry pi cluster configuration - https://glmdev.medium.com/building-a-raspberry-pi-cluster-784f0df9afbd
2. Setup wireless access point - https://pimylifeup.com/raspberry-pi-wireless-access-point/

