#!/bin/bash

##folder=testDir
##packages="$ROOTCOREDIR/scripts/load_packages.C"
##steering="../source/ATestRun.cxx ("${folder}")"

##root -b -q ${packages} ${steering}

root -b -q '$ROOTCOREDIR/scripts/load_packages.C' '../source/ATestRun.cxx ("testDir")'

