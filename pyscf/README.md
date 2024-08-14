
This file contains  sample code to test whether PySCF runs correctly on the Pi cluster

### Optimisation Calcualtion

#### Sample Code

```python
from pyscf import gto, dft
from pyscf import lib

# Specifying number of threads
lib.num_threads(8)

# Inputting water molecule
mol_hf = gto.M(atom = '''
        O    -2.504662267894     -0.023765873921     -3.911004734200
        H    -2.504662267901      0.735571126078     -3.314961734199
        H    -2.504662267901     -0.783102873922     -3.314961734201
               ''', basis = 'ccpvdz', symmetry = True)
mf_hf = dft.RKS(mol_hf)
mf_hf.xc = 'wb97x-v' # Functional
mf_hf = mf_hf.newton() # second-order algortihm
mf_hf.kernel()

# final_coords = mol_hf.atom_coords()
final_coords = mol_hf._atom
print("Final Converged Structure (in Ångstroms):")
print(final_coords)

```

### Expected output
```bash
converged SCF energy = -76.3917582916355
Final Converged Structure (in Ångstroms):
[('O', [-4.7331257208516675, -0.044910992821633196, -7.390727819515376]), ('H', [-4.733125720864896, 1.3900279734253376, -6.264369791049353]), ('H', [-4.733125720864896, -1.4798499590723833, -6.264369791053132])] 
```