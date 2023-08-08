# Shared Storage

In a mini-supercomputer all the nodes should be able to access the same files, in order to work efficienly. For this, we need a storage drive connected to the login node and exporting that drive as a network file system (NFS). NFS share should be then mounted to all the nodes to give them access to it.

## Connect and mount storage drive

1. Login to the master node
   ```bash
   ssh pi@<ip address of login node>
   ```

2. Find the drive identifier
   Plug the harddisk into one of the USB ports on the login node and find its dev location from the output of 
   ```bash
   lsblk
   ```
   
3. Format the hard disk - In our case the main partition of the flash drive is at /dev/sda1
   ```bash
   sudo mkfs /dev/sda1
   ```

4. Create the mount directory
   The mount directory should be same accross all the nodes.
   In our cluster it is /clusterfs

   ```bash
   sudo mkdir /clusterfs
   ```
   Change the folder permission and make the directory accessible by all the users in the system. They can read, write and execute.

   ```bash
   sudo chown nobody.nogroup -R /clusterfs
   ```

   ```bash
   sudo chmod 777 -R /clusterfs
   ```

5. Setup automatic mounting
   To mount the hard drive while booting, we need to find the unique ID (UUID) of the hard drive. To find that, run blkid and note down the UUID of /dev/sda1 (Not the UUID of raspberry pi memory card)

   Now edit fstab to mount the drive on boot.
   ```bash
   sudo nano /etc/fstab
   ```
   add the following line
   ```bash
   UUID=<UUID of hard drive> /clusterfs ext2 defaults,nofail 0 0
   ```
   Exit the file.

   Mount the hard drive
   ```bash
   mount /dev/sda1 /clusterfs
   ```
   set loose permisson - owner has read, write and execute permissions. The group and other users have read and write permissions.
   ```bash
   sudo chown nobody.nogroup -R /clusterfs
   sudo chmod -R 766 /clusterfs
   ```

   ## Export the NFS share
   Now, we need to export the mounted drive as a network file system share so the other nodes can access it.

   1. Install the NFS server
   ```bash
   sudo apt install nfs-kernel-server -y
   ```

  2. Export the NFS share 
     Edit /etc/exports
     ```bash
     nano /etc/exports
     ```
     Add the following line to the file
     ```bash
     /clusterfs    <ip addr schema>(rw,sync,no_root_squash,no_subtree_check)
     ```
     (Eg_ If your LAN addresses were 192.168.1.x you would have 
     /clusterfs 192.168.1.0/24(rw,sync,no_root_squash,no_subtree_check) )

    Run the following command to update the NFS kernel server
    ```bash
    sudo exportfs -a
    ```

    ## Mount NFS Share on other nodes
    Mount NFS share on the other nodes so that they can access it. Do this process for all the worker nodes.

    1. Install the NFS client
       ```bash
       sudo apt install nfs-common -y
       ```

    2. 