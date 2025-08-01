# cvms5

<a href="https://github.com/sceccode/cvms5.git"><img src="https://github.com/sceccode/cvms5/wiki/images/cvms5_logo.png"></a>


[![License](https://img.shields.io/badge/License-BSD_3--Clause-blue.svg)](https://opensource.org/licenses/BSD-3-Clause)
![GitHub repo size](https://img.shields.io/github/repo-size/sceccode/cvms5)
[![cvms5-ucvm-ci Actions Status](https://github.com/SCECcode/cvms5/workflows/cvms5-ucvm-ci/badge.svg)](https://github.com/SCECcode/cvms5/actions)

Tomography improved Southern California Velocity Model with 
optional geotechnical layer(Ely-Jordan GTL)

CVM-S4.26 is full-3-D tomography (F3DT) based on a combination of the scattering-integral method (SI-F3DT) and the adjoint-wavefield method (AW-F3DT) to iteratively improve a 3-D starting model, the Southern California Earthquake Center (SCEC) Community Velocity Model version 4.0 (CVM-S4). More than half-a-million misfit measurements made on about 38,000 earthquake seismograms and 12,000 ambient-noise correlagrams have been assimilated into our inversion. After 26 F3DT iterations, synthetic seismograms computed using CVM-S4.26, show substantially better fit to observed seismograms at frequencies below 0.2 Hz than those computed using our 3-D starting model. CVM-S4.26 reveals strong crustal heterogeneities throughout Southern California, some of which are completely missing in other existing southern California seismic models include CVM-S4 and CVM-H, but exist in models obtained from previous crustal-scale 2-D active-source refraction tomography models. At shallow depths, our model shows strong correlation with sedimentary basins and reveals velocity contrasts across major mapped strike-slip and dip-slip faults. At middle to lower crustal depths, structural features in this model provides new insights into regional tectonics.

Lee, E.-J., P. Chen, T. H. Jordan, P. J. Maechling, M. A. M. Denolle, and G. C.Beroza (2014), Full 3-D tomography for crustal structure in Southern California based on the scattering-integral and the adjoint-wavefield methods, J. Geophys. Res. Solid Earth, 119, doi:10.1002/2014JB011346. SCEC Contribution 6093

## Installation

This package is intended to be installed as part of the UCVM framework,
version 25.x or higher. 

## Library

The library ./lib/libcvms5.a may be statically linked into any
user application. Also, if your system supports dynamic linking,
you will also have a ./lib/libcvms5.so file that can be used
for dynamic linking. The header file defining the API is located
in ./include/cvms5.h.

## Contact the authors

If you would like to contact the authors regarding this software,
please e-mail software@scec.org. Note this e-mail address should
be used for questions regarding the software itself (e.g. how
do I link the library properly?). Questions regarding the model's
science (e.g. on what paper is the CVMS5 based?) should be directed
to the model's authors, located in the AUTHORS file.

