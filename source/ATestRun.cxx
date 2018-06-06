#include <EventLoop/DirectDriver.h>
#include <EventLoop/Job.h>
#include <FTKPlots/FTKReader.h>
#include <TSystem.h>
#include <SampleHandler/ScanDir.h>

#include <xAODRootAccess/Init.h>
#include <AsgTools/MessageCheck.h>

void ATestRun (const std::string& submitDir)
{
  // Set up the job for xAOD access:
  xAOD::Init().ignore();

  // create a new sample handler to describe the data files we use
  SH::SampleHandler sh;

  // scan for datasets in the given directory
  // this works if you are on lxplus, otherwise you'd want to copy over files
  // to your local machine and use a local path.  if you do so, make sure
  // that you copy all subdirectories and point this to the directory
  // containing all the files, not the subdirectories.

  // use SampleHandler to scan all of the subdirectories of a directory for particular MC single file:
  //const char* inputFilePath = gSystem->ExpandPathName ("/data/fscutti/user.fscutti");
  //SH::ScanDir().filePattern("user.fscutti.12548767.EXT0._000001.InDetDxAOD.pool.root").scan(sh,inputFilePath);
  //SH::ScanDir().filePattern("InDetDxAOD.pool.root").scan(sh,inputFilePath);
  
  
  // old output used for reference 
  //const char* inputFilePath = gSystem->ExpandPathName ("/home/fscutti/FastSim/xAODAnalysis/OldInputDAOD");
  //SH::ScanDir().filePattern("InDetDxAOD.pool.root").scan(sh,inputFilePath);
 
  // output from the grid 
  //const char* inputFilePath = gSystem->ExpandPathName ("/data/fscutti/FTKSamples/output/user.fscutti.26Nov11_EXT0");
  //SH::ScanDir().filePattern("user.fscutti.12680603.EXT0._000001.InDetDxAOD.pool.root").scan(sh,inputFilePath);

  // complete output, but incorrect sectors (lots of events!!!)
  //const char* inputFilePath = gSystem->ExpandPathName ("/data/fscutti/FTKSamples/output");
  //SH::ScanDir().filePattern("merged.root").scan(sh,inputFilePath);
  
  // complete output with correct sectors (lots of events!!!)
  //const char* inputFilePath = gSystem->ExpandPathName ("/data/fscutti/FTKSamples/output_5Dec");
  //SH::ScanDir().filePattern("merged_5Dec.root").scan(sh,inputFilePath);
  
  // alternative smearing approach (lots of events!!!)
  //const char* inputFilePath = gSystem->ExpandPathName ("/data/fscutti/FTKSamples/output_11Dec");
  //SH::ScanDir().filePattern("merged_11Dec.root").scan(sh,inputFilePath);

  // bugged constants from Jason (lots of events!!!)
  //const char* inputFilePath = gSystem->ExpandPathName ("/data/fscutti/FTKSamples/output_8Feb");
  //SH::ScanDir().filePattern("merged_8Feb.root").scan(sh,inputFilePath);
  
  // debugged constants
  //const char* inputFilePath = gSystem->ExpandPathName ("/data/fscutti/FTKSamples/output_14Feb");
  //SH::ScanDir().filePattern("merged_14Feb.root").scan(sh,inputFilePath);
  
  // debugged constants eta propagation formula
  //const char* inputFilePath = gSystem->ExpandPathName ("/data/fscutti/FTKSamples/output_10Apr");
  //SH::ScanDir().filePattern("merged_10Apr.root").scan(sh,inputFilePath);
  
  // debugged flat eta trend
  const char* inputFilePath = gSystem->ExpandPathName ("/data/fscutti/FTKSamples/output_12Apr");
  SH::ScanDir().filePattern("merged_12Apr.root").scan(sh,inputFilePath);
  
  // set the name of the tree in our files
  // in the xAOD the TTree containing the EDM containers is "CollectionTree"
  sh.setMetaString ("nc_tree", "CollectionTree");

  // further sample handler configuration may go here

  // print out the samples we found
  sh.print ();

  // this is the basic description of our job
  EL::Job job;
  job.sampleHandler (sh); // use SampleHandler in this job
  job.options()->setDouble (EL::Job::optMaxEvents, 100000000); // for testing purposes, limit to run over the first 500 events only!
  
  // configuration file 
  //std::string configName = "./FTKReader/config/FTKReader.config";
  //TEnv* config = new TEnv(configName.c_str());
  
  //float minPT  = 1000; // MeV
  //float maxEta = 2.4;
  //float maxPhi = 3.14;
  //float maxD0  = 2.;
  //float maxZ0  = 100.;
 
  // tighter for full efficiency
  float minPT  = 5000; // MeV
  float maxEta = 1.;
  float maxPhi = 3.14;
  float maxD0  = 0.2;
  float maxZ0  = 100.;


  //float minPT  = 0.0; // MeV
  //float maxEta = 1000.;
  //float maxPhi = 1000.;
  //float maxD0  = 1000.;
  //float maxZ0  = 1000.;

  // add our algorithm to the job
  FTKReader *alg = new FTKReader;

  alg->m_minPT  = minPT;
  alg->m_maxEta = maxEta;
  alg->m_maxPhi = maxPhi;
  alg->m_maxD0  = maxD0;
  alg->m_maxZ0  = maxZ0;

  ///alg->m_FTKFastSimTrackParticlesContainerName = config->GetValue("FTKFastSimTrackParticlesContainerName",  "FTK_Converted_TrackParticles");

  // set the name of the algorithm (this is the name use with messages)
  alg->SetName ("AnalysisAlg");

  // later on we'll add some configuration options for our algorithm that go here
  job.algsAdd (alg);

  // make the driver we want to use:
  // this one works by running the algorithm directly:
  EL::DirectDriver driver;
  // we can use other drivers to run things on the Grid, with PROOF, etc.

  // process the job using the driver
  driver.submit (job, submitDir);
}

int main (int argc, char* argv[])
{
  // set the return type and reporting category for ANA_CHECK
  using namespace asg::msgUserCode;
  ANA_CHECK_SET_TYPE (int);

  // Take the submit directory from the input if provided:
  std::string submitDir = "submitDir";
  if( argc == 2 ) submitDir = argv[1];
  if (argc > 2)
  {
    ANA_MSG_ERROR ("don't know what to do with extra arguments, aborting");
    return -1;
  }

  // Set up the job for xAOD access:
  ANA_CHECK (xAOD::Init());

  // call our actual job-submission code
  ATestRun (submitDir);

  return 0;
}


