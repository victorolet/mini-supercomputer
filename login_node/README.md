

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
    ```bash
    cd /etc/slurm
    sudo -s
    cp /usr/share/doc/slurm-client/examples/slurm.conf.simple.gz .
    gzip -d slurm.conf.simple.gz
    mv slurm.conf.simple slurm.conf
    ```

4. Edit the configuration
   ```bash
   nano slurm.conf
   ```
   Then edit the configuration
   ```bash
   SlurmctldHost=pi1(<ip addr of pi1>)
   ```
   Set the cluster name
   ClusterName=mycluster

5. Near the end of the file, there should be an example entry for the compute node. Delete it, and add the following configurations for the cluster nodes:

    ```bash
    NodeName=pi1 NodeAddr=<ip addr of pi1> CPUs=4 State=UNKNOWN
    NodeName=pi2 NodeAddr=<ip addr of pi2> CPUs=4 State=UNKNOWN
    NodeName=pi3 NodeAddr=<ip addr of pi3> CPUs=4 State=UNKNOWN
    ```

6. Be sure to delete the example partition in the file, then add the following on one line

   ```bash
   PartitionName=mycluster Nodes=pi[2-8] Default=YES MaxTime=INFINITE State=UP
   ```


## Configure cgroups Support

1. Create a file called cgroup.conf
   ```bash
   nano cgroup.conf
   ```
   This will open a new file. copy and paste the following code and save it.
   ```bash
   CgroupMountpoint="/sys/fs/cgroup"
   CgroupAutomount=yes
   CgroupReleaseAgentDir="/etc/slurm/cgroup"
   AllowedDevicesFile="/etc/slurm/cgroup_allowed_devices_file.conf"
   ConstrainCores=no
   TaskAffinity=no
   ConstrainRAMSpace=yes
   ConstrainSwapSpace=no
   ConstrainDevices=no
   AllowedRamSpace=100
   AllowedSwapSpace=0
   MaxRAMPercent=100
   MaxSwapPercent=100
   MinRAMSpace=30
   ```

2. Now, whitelist system devices by creating the file cgroup_allowed_devices_file.conf
   ```bash
   nano cgroup_allowed_devices_file.conf
   ```
   add the following lines

   ```bash
   /dev/null
   /dev/urandom
   /dev/zero
   /dev/sda*
   /dev/cpu/*/*
   /dev/pts/*
   /clusterfs*
   ```

## Copy the configuration files to shared storage
Copy the configuration files and munge key in to shared storage so that the other nodes can have the same configuration files.

```bash
sudo cp slurm.conf cgroup.conf cgroup_allowed_devices_file.conf /clusterfs
sudo cp /etc/munge/munge.key /clusterfs
```

## Enable and Start SLURM Control Services

1. Munge
   ```bash
   sudo systemctl enable munge
   sudo systemctl start munge
   ```

2. The SLURM daemon
   ```bash
   sudo systemctl enable slurmd
   sudo systemctl start slurmd
   ```

3. And the control daemon
   ```bash
   sudo systemctl enable slurmctld
   sudo systemctl start slurmctld
   ```

4. Reboot