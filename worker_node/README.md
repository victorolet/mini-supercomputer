# Worker nodes

## Worker nodes configuration

1. Install the SLURM Client

   ```bash
   sudo apt install slurmd slurm-client -y
   ```

2. Edit /etc/hosts
   Update /etc/hosts by adding all of the nodes and their ip adresses except that node.
   For example for pi2

   Add the following lines
   <ip addr>    pi1
   <ip addr>    pi3
   <ip addr>    pi4

3. Copy the configuration files from shared storage
   Configuration on the worker nodes should matches the configuration on the login node. So, copy it from shared storage:

   ```bash
   sudo cp /clusterfs/munge.key /etc/munge/munge.key
   sudo cp /clusterfs/slurm.conf /etc/slurm/slurm.conf
   sudo cp /clusterfs/cgroup* /etc/slurm
   ```

4. Enable and start munge
   ```bash
   sudo systemctl enable munge
   sudo systemctl start munge
   ```

5. Test Munge (Run this on a worker node)
   ```bash
   ssh pi@pi1 munge -n
   ```

6. Start the SLURM Daemon
   ```bash
   sudo systemctl enable slurmd
   sudo systemctl start slurmd
   ```
