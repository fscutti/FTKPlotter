#ifndef FTKPlots_FTKReader_H
#define FTKPlots_FTKReader_H

#include <EventLoop/Algorithm.h>

#include "xAODRootAccess/Init.h"
#include "xAODRootAccess/TEvent.h"

#ifndef __MAKECINT__
#include "xAODTracking/TrackParticle.h"
#include "xAODTracking/Vertex.h"
#include "xAODTruth/TruthParticle.h"
#include "xAODTruth/TruthParticleAuxContainer.h"
#include "xAODTruth/TruthParticleContainer.h"
#endif

class FTKReader : public EL::Algorithm
{
  // put your configuration variables here as public variables.
  // that way they can be set directly from CINT and python.
public:
  // float cutValue;

private:
  bool m_exist_fastsim_tracks; //!
  bool m_exist_fullsim_tracks; //!
  bool m_exist_offline_tracks; //!


  // variables that don't get filled at submission time should be
  // protected from being send from the submission node to the worker
  // node (done by the //!)

public:
  // Tree *myTree; //!
  // TH1 *myHist; //!

  // this is a standard constructor
  FTKReader (bool truth=true,
             bool fastsim_tracks=true,
             bool fullsim_tracks=true,
             bool offline_tracks=true
             );

  float m_minPT, m_maxEta, m_maxPhi, m_maxD0, m_maxZ0;

  // these are the functions inherited from Algorithm
  virtual EL::StatusCode setupJob (EL::Job& job);
  virtual EL::StatusCode fileExecute ();
  virtual EL::StatusCode histInitialize ();
  virtual EL::StatusCode changeInput (bool firstFile);
  virtual EL::StatusCode initialize ();
  virtual EL::StatusCode execute ();
  virtual EL::StatusCode postExecute ();
  virtual EL::StatusCode finalize ();
  virtual EL::StatusCode histFinalize ();

  // Everything in the header file  that refers to the xAOD edm needs
#ifndef __MAKECINT__
  
  bool isAcceptedParticle(const xAOD::TrackParticle* p);
  bool isAcceptedParticle(const xAOD::TruthParticle* p);
  //std::pair<const xAOD::TrackParticle*, int> findBestMatchDR(const xAOD::TruthParticle* truth, const xAOD::TrackParticleContainer* trkPartCont, float best_DR);
  //std::pair<const xAOD::TrackParticle*, int> findBestMatch(const xAOD::TruthParticle* truth, const xAOD::TrackParticleContainer* trkPartCont, float best_truth_prob);

  std::unordered_map<int, std::pair<const xAOD::TrackParticle*, const xAOD::TruthParticle* > > findBestMatchDR(const xAOD::TruthParticleContainer* truthPartCont,
                                                                                                               const xAOD::TrackParticleContainer* trkPartCont,
                                                                                                               float best_DR);

  void AddBranches(TTree* tree);
  void ResetBranches();
#endif
  
  
  bool m_truth;                //!
  bool m_simulation;           //!
  //bool m_tsos_offline;       //!
  //bool m_tsos_ftk;           //!
  xAOD::TEvent *m_event;       //!
  unsigned int m_eventCounter; //!
  TTree *tree;                 //!

  int event_number, truth_track_n, fastsim_track_n, fullsim_track_n, offline_track_n;
  
  // --------------- 
  // truth
  // --------------- 
  std::vector<float> truth_track_pt,
                     truth_track_qinv2pt,
                     truth_track_eta,
                     truth_track_phi,
                     truth_track_d0,
                     truth_track_z0,
                     truth_track_qop,
                     truth_track_theta;

  std::vector<int>   truth_track_charge,
                     truth_track_pdgid,
                     truth_track_status,
                     truth_track_barcode;

  std::vector<int>   truth_ismatched_fastsim,
                     truth_ismatched_fullsim,
                     truth_ismatched_offline;

  // --------------- 
  // fast simulation 
  // --------------- 
  std::vector<float> fastsim_track_pt,
                     fastsim_track_qinv2pt,
                     fastsim_track_eta,
                     fastsim_track_phi,
                     fastsim_track_d0,
                     fastsim_track_z0,
                     fastsim_track_qop,
                     fastsim_track_theta;
  
  std::vector<float> fastsim_track_true_qinv2pt,
                     fastsim_track_true_pt,
                     fastsim_track_true_eta,
                     fastsim_track_true_phi,
                     fastsim_track_true_d0,
                     fastsim_track_true_z0,
                     fastsim_track_true_qop,
                     fastsim_track_true_theta;
  
  std::vector<float> fastsim_track_delta_pt,
                     fastsim_track_delta_qinv2pt,
                     fastsim_track_delta_eta,
                     fastsim_track_delta_phi,
                     fastsim_track_delta_d0,
                     fastsim_track_delta_z0,
                     fastsim_track_delta_qop,
                     fastsim_track_delta_theta;
  
  
  std::vector<int>   fastsim_track_charge;
                     //fastsim_track_ismatched;


  // --------------- 
  // full simulation 
  // --------------- 
  std::vector<float> fullsim_track_pt,
                     fullsim_track_qinv2pt,
                     fullsim_track_eta,
                     fullsim_track_phi,
                     fullsim_track_d0,
                     fullsim_track_z0,
                     fullsim_track_qop,
                     fullsim_track_theta;
  
  std::vector<float> fullsim_track_true_qinv2pt,
                     fullsim_track_true_pt,
                     fullsim_track_true_eta,
                     fullsim_track_true_phi,
                     fullsim_track_true_d0,
                     fullsim_track_true_z0,
                     fullsim_track_true_qop,
                     fullsim_track_true_theta;
  
  std::vector<float> fullsim_track_delta_pt,
                     fullsim_track_delta_qinv2pt,
                     fullsim_track_delta_eta,
                     fullsim_track_delta_phi,
                     fullsim_track_delta_d0,
                     fullsim_track_delta_z0,
                     fullsim_track_delta_qop,
                     fullsim_track_delta_theta;
  
  std::vector<int>   fullsim_track_charge;
                     //fullsim_track_ismatched;


  // --------------- 
  // offline
  // --------------- 
  std::vector<float> offline_track_pt,
                     offline_track_qinv2pt,
                     offline_track_eta,
                     offline_track_phi,
                     offline_track_d0,
                     offline_track_z0,
                     offline_track_qop,
                     offline_track_theta;
  
  std::vector<float> offline_track_true_qinv2pt,
                     offline_track_true_pt,
                     offline_track_true_eta,
                     offline_track_true_phi,
                     offline_track_true_d0,
                     offline_track_true_z0,
                     offline_track_true_qop,
                     offline_track_true_theta;
  
  std::vector<float> offline_track_delta_pt,
                     offline_track_delta_qinv2pt,
                     offline_track_delta_eta,
                     offline_track_delta_phi,
                     offline_track_delta_d0,
                     offline_track_delta_z0,
                     offline_track_delta_qop,
                     offline_track_delta_theta;
  
  std::vector<int>   offline_track_charge;
                     //offline_track_ismatched;

  //std::string m_FTKFastSimTrackParticlesContainerName;

  // this is needed to distribute the algorithm to the workers
  ClassDef(FTKReader, 1);
};

#endif
