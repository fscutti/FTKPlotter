#!bin/bash

## ---------------------------------------------------------------
## tutorial:
## https://atlassoftwaredocs.web.cern.ch/ABtutorial/release_setup/
## ---------------------------------------------------------------

#export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase
#alias setupATLAS='source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh'
#setupATLAS

release=21.2.16
project="AnalysisBase"

echo ""
echo "++++++++++++++++++++++++++++++++++++++++++++++++++"
echo "setup runtime env "
echo "version: ${release}"
echo "project: ${project}"
echo "++++++++++++++++++++++++++++++++++++++++++++++++++"
echo ""

echo "asetup ${release}, ${project}"
asetup ${release}, ${project}




















