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

   Mount the hard drive
   ```bash
   mount /dev/sda1 /clusterfs
   ```