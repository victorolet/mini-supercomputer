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