# Shared Storage

In a mini-supercomputer all the nodes should be able to access the same files, in order to work efficienly. For this, we need a storage drive connected to the login node and exporting that drive as a network file system (NFS). NFS share should be then mounted to all the nodes to give them access to it.

## Connect and mount storage drive

1. Login to the master node
   ```bash
   ssh pi@<ip address of login node>
   ```

2. Find the drive identifier
   Plug the harddisk into one of the USB ports on the login node.
   
   ```bash
   UUID=64a0421a-ad9d-4e9d-bb82-d7db8fc45af2 /clusterfs ext2 defaults,nofail 0 0
   ```

3. Mount the harddrive
   ```bash
   mount /dev/sda1 /clusterfs
   ```