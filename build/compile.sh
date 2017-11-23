#!bin/bash

PFPATH=/home/fscutti/FTKPlotter
##PFFILE=package_filters.txt

##cmake -DATLAS_PACKAGE_FILTER_FILE=${PFPATH}/${PFFILE} ${PFPATH}/athena/Projects/WorkDir
cmake ${PFPATH}/source
make 


