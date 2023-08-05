# Shared Storage

In a mini-supercomputer all the nodes should be able to access the same files, in order to work efficienly. For this, we need a storage drive connected to the login node and exporting that drive as a network file system (NFS). NFS share should be then mounted to all the nodes to give them access to it.