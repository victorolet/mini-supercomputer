
Configure static ip address for raspberry pi

Method 1 - 
1. open network configuration
   ```bash
   sudo nmtui
   ```
2. Click on Edit a connection
3. click on wired connection and click Edit
4. IPV4 configuration (manual)
5. change the static ip address, gateway and DNS server

Method 2 - using dhcpcd.conf (This will work only if the version of Raspberry pi OS you are using contain a file called dhcpcd.conf)
    
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