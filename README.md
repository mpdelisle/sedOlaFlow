# sedOlaFlow
sedOlaFlow solver for OpenFOAM

### What is this repository for? ###
* OpenFOAM
* Supported OpenFOAM versions: v1712

### Installation ###

* Install OpenFOAM
* Install waves2Foam
* Install olaFlow
* git clone https://github.com/mpdelisle/sedOlaFlow sedOlaFlow
* cd sedOlaFlow
* Delete all dep files using (find . -name *.dep -type f -delete)
* source bashrc of OpenFOAM and waves2Foam
* ./Allwclean
* ./Allwmake

### Case setup ###
Gravel, permeable beach: https://github.com/mpdelisle/Kikkert-Pokrajac-ODonoghue-Steenhauer-2013  
*For details of the physical experiment refer to Kikkert et al., 2013, Coastal Engineering, https://doi.org/10.1016/j.coastaleng.2013.04.008*


### Contacts ###
* Marie-Pierre Delisle: mpdelisle@ucla.edu
* Yeulwoo Kim: yarkim@pknu.ac.kr
