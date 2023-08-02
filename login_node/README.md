

# Login Node

## Configuring the login node
Login node is the Raspberry pi that you ssh into to use the cluster

Login to the login node
```bash
ssh pi@<ip_address>
```
1. Add hostnames of the other nodes and their IP addresses to the /etc/hosts file. 

   - open the file
   ```bash
    sudo nano /etc/hosts
    ```
   - Add the hostnames into the file
    ```bash
    <ip addr of pi2>      pi2
    <ip addr of pi3>      pi3
    <ip addr of pi4>      pi4

    ```

2. Install the SLURM Controller Packages
   ```bash
   sudo apt install slurm-wlm -y
   ``` 

3. SLURM Configuration

## Configure cgroups Support
