#include <cmath>
#include <typeinfo>
#include <iostream>
#include <utility>

#include <AsgTools/MessageCheck.h>
#include <EventLoop/Job.h>
#include <EventLoop/StatusCode.h>
#include <EventLoop/Worker.h>
#include <FTKPlots/FTKReader.h>

#include "xAODEventInfo/EventInfo.h"

#include "xAODEventInfo/EventInfo.h"
//#include "xAODTruth/TruthParticleAuxContainer.h"
//#include "xAODTruth/TruthParticleContainer.h"
#include "xAODTruth/TruthVertex.h"
#include "xAODTracking/TrackParticleContainer.h"
#include "xAODTracking/TrackParticleAuxContainer.h"
#include "xAODTracking/TrackMeasurementValidationContainer.h"
#include "xAODTracking/TrackStateValidationContainer.h"
#include "xAODRootAccess/TStore.h"
#include "xAODCore/ShallowCopy.h"

#include "TTree.h"
#include "TMath.h"

#define GeV 1000.

// this is needed to distribute the algorithm to the workers
ClassImp(FTKReader)

inline bool contains(std::string s1, std::string s2)
{
  if (s1.find(s2) != std::string::npos) return true;
  else return false;
}

bool FTKReader::isAcceptedParticle(const xAOD::TrackParticle* p) {
 
  // check if particle passes basic kin cuts
  if(p->pt() < m_minPT || fabs(p->eta()) > m_maxEta || fabs(p->phi()) > m_maxPhi) return false;
  if(p->isAvailable<float>("d0") && fabs(p->auxdataConst<float>("d0")) > m_maxD0) return false;
  if(p->isAvailable<float>("z0") && fabs(p->auxdataConst<float>("z0")) > m_maxZ0) return false;
   
  return true;
}

bool FTKReader::isAcceptedParticle(const xAOD::TruthParticle* p)
{
  // check if is valid truth particle
  if (p->status() != 1)                           return false; // check if stable
  if (p->isNeutral())                             return false; // check if neutral
  if (p->barcode() == 0 or p->barcode() >= 200e3) return false; // check if truth is found for track
  //if (p->pt() < 1000 || fabs(p->eta()) > 2.4)     return false; // additiona truth acceptance
  //if (p->pt() < 1000 || fabs(p->eta()) > 2.4)     return false; // additiona truth acceptance


  // check if particle passes basic kin cuts
  if(p->pt() < m_minPT || fabs(p->eta()) > m_maxEta || fabs(p->phi()) > m_maxPhi) return false;
  if(p->isAvailable<float>("d0") && fabs(p->auxdataConst<float>("d0")) > m_maxD0) return false;
  if(p->isAvailable<float>("z0") && fabs(p->auxdataConst<float>("z0")) > m_maxZ0) return false;

  return true;
}

inline const xAOD::TruthParticle* getParticleLink(const xAOD::TrackParticle *track)
{
  typedef ElementLink< xAOD::TruthParticleContainer > Link_t;
  static const char* NAME = "truthParticleLink";
  if(!track->isAvailable< Link_t >(NAME)) {
    return nullptr;
  }
  const Link_t& link = track->auxdata< Link_t >(NAME);
  if(!link.isValid()) {
    Error("getParticleLink()", "xAOD::TrackParticle has an invalid truthParticleLink");
    return nullptr;
  }
  return *link;
}

/*
inline void fillBarcodeMap( std::unordered_map<signed long, bool>BarcodeMap,  const xAOD::TrackParticle *trkPart, std::string trkType) 
{
  const xAOD::TruthParticle* truth = getTruthParticle(trkPart);
  if (!truth) {
    std::string msg = "Truth particle not found for "; msg.append(trkType);
    //Warning("execute()", msg.c_str());
    return;
  }
  if (!isAcceptedParticle(truth)) return; 
  if (trkPart->auxdata< float >( "truthMatchProbability" ) < 0.7) return;
  if(!BarcodeMap[truth->barcode()]) BarcodeMap[truth->barcode()] = true;;
  
  return;
}
*/

inline float getDR(float eta1, float eta2, float phi1, float phi2)
{
 float deta = std::abs(eta1-eta2);
 float dphi = std::abs(phi1-phi2);
 dphi = ( dphi <= TMath::Pi() ) ? dphi : ( 2 * TMath::Pi() - dphi );
 return sqrt(deta*deta + dphi*dphi);
}

std::unordered_map<int, std::pair<const xAOD::TrackParticle*, const xAOD::TruthParticle* > > FTKReader::findBestMatchDR(const xAOD::TruthParticleContainer* truthPartCont, 
                                                                                                                        const xAOD::TrackParticleContainer* trkPartCont, 
                                                                                                                        float best_DR=10)
{
  // Find track that best matches a truth particle using DR
  // If matching is successfull returns a map where the key 
  // is the  container index of the matched track and the value
  // is the pair of the matched track and the true one
  
  float default_best_DR = best_DR; 
  int itruth = -1;
  int best_itruth = -1;
  const xAOD::TruthParticle* best_truth = nullptr;
  
  std::unordered_map<int, std::pair<const xAOD::TrackParticle*, const xAOD::TruthParticle*>> match_map;

  for (const auto truth : *truthPartCont) {
      ++itruth;
      if (!isAcceptedParticle(truth)) continue;

      int itrack = -1;
      int best_itrack = -1;
      const xAOD::TrackParticle* best_track = nullptr;
      float DR = 0;
      

      for (const auto track : *trkPartCont) {
        ++itrack;
        if (!isAcceptedParticle(track)) continue;
        
        DR = getDR(track->eta(),truth->eta(),track->phi(),truth->phi()); 
        
        if (DR < best_DR) {
          best_DR = DR;
          best_track = track;
          best_truth = truth;
          best_itrack = itrack;
          best_itruth = itruth;
        }
      }
      
      std::unordered_map<int, std::pair<const xAOD::TrackParticle*, const xAOD::TruthParticle* > >::const_iterator got = match_map.find (best_itruth); 
      
      // if a new match is found for a previous 
      // track keep the new match if it is better 
      
      if (got == match_map.end() and best_itrack != -1 and best_itruth != -1) {
        match_map[best_itruth] = std::pair<const xAOD::TrackParticle*, const xAOD::TruthParticle*>(best_track, best_truth);
      }
      else if (got != match_map.end() and best_itrack != -1 and best_itruth != -1) {
        float old_DR = getDR(match_map[best_itruth].first->eta(), match_map[best_itruth].second->eta(),match_map[best_itruth].first->phi(), match_map[best_itruth].second->phi());
        if (old_DR > best_DR) {
          match_map[best_itruth] = std::pair<const xAOD::TrackParticle*, const xAOD::TruthParticle*>(best_track, best_truth);
        }
      }
      // reset the best_DR to the default value
      best_DR = default_best_DR;
  } 
  return match_map;
}


/*
std::pair<const xAOD::TrackParticle*, int> FTKReader::findBestMatchDR(const xAOD::TruthParticle* truth, const xAOD::TrackParticleContainer* trkPartCont, float best_DR=10)
{
  // Find track that best matches a truth particle using DR
  // Return the best matching track (if any) and index 
  // of this track in the container
  
  int itrack = -1, best_itrack = -1;
  const xAOD::TrackParticle* best_track = nullptr;
  float DR = 0;
  
  for (const auto track : *trkPartCont) {
    if (!isAcceptedParticle(track)) continue;
    ++itrack;
    
    DR = getDR(track->eta(),truth->eta(),track->phi(),truth->phi()); 
    
    if (DR < best_DR) {
      best_DR = DR;
      best_track = track;
      best_itrack = itrack;
    }
  }
  
  return std::pair<const xAOD::TrackParticle*, int>(best_track, best_itrack);
}
*/
/*
std::pair<const xAOD::TrackParticle*, int> FTKReader::findBestMatch(const xAOD::TruthParticle* truth, const xAOD::TrackParticleContainer* trkPartCont, float best_truth_prob=0)
{
  // Find track that best matches a truth particle
  // Return the best matching track (if any) and index 
  // of this track in the container
  
  int itrack = -1, best_itrack = -1;
  float truth_prob;
  const xAOD::TrackParticle* best_track = nullptr;
  const xAOD::TruthParticle* matched_truth;
  bool at_least_one_tplink = false;
  
  for (const auto track : *trkPartCont) {
    ++itrack;
    
    if (!isAcceptedParticle(track)) continue; // WARNING: selection after incrementing the index
    
    matched_truth = getParticleLink(track);
    if (!matched_truth) continue;
    at_least_one_tplink = true;
    if (matched_truth->barcode() != truth->barcode()) continue;
    truth_prob = track->auxdata<float>("truthMatchProbability");
    if (truth_prob > best_truth_prob) {
      best_truth_prob = truth_prob;
      best_track = track;
      best_itrack = itrack;
    }
  }
  
  if (!at_least_one_tplink) {
    Warning("findBestMatch()", "No xAOD::TrackParticles had a truthParticleLink");
  }
  
  return std::pair<const xAOD::TrackParticle*, int>(best_track, best_itrack);
}
*/


FTKReader :: FTKReader (bool truth, bool fastsim_tracks, bool fullsim_tracks, bool offline_tracks)
{
  // Here you put any code for the base initialization of variables,
  // e.g. initialize all pointers to 0.  Note that you should only put
  // the most basic initialization here, since this method will be
  // called on both the submission and the worker node.  Most of your
  // initialization code will go into histInitialize() and
  // initialize().
  m_truth        = truth;
  m_simulation   = false;
  m_eventCounter = 0;
  m_exist_fastsim_tracks = fastsim_tracks;
  m_exist_fullsim_tracks = fullsim_tracks;
  m_exist_offline_tracks = offline_tracks;
}



EL::StatusCode FTKReader :: setupJob (EL::Job& job)
{
  // Here you put code that sets up the job on the submission object
  // so that it is ready to work with your algorithm, e.g. you can
  // request the D3PDReader service or add output files.  Any code you
  // put here could instead also go into the submission script.  The
  // sole advantage of putting it here is that it gets automatically
  // activated/deactivated when you add/remove the algorithm from your
  // job, which may or may not be of value to you.
  job.useXAOD();
  // let's initialize the algorithm to use the xAODRootAccess package
  xAOD::Init("FTKReader").ignore(); // call before opening first file
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode FTKReader :: histInitialize ()
{
  // Here you do everything that needs to be done at the very
  // beginning on each worker node, e.g. create histograms and output
  // trees.  This method gets called before any input files are
  // connected.
  
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode FTKReader :: fileExecute ()
{
  // Here you do everything that needs to be done exactly once for every
  // single file, e.g. collect a list of all lumi-blocks processed
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode FTKReader :: changeInput (bool /*firstFile*/)
{
  // Here you do everything you need to do when we change input files,
  // e.g. resetting branch addresses on trees.  If you are using
  // D3PDReader or a similar service this method is not needed.
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode FTKReader :: initialize ()
{
  // Here you do everything that you need to do after the first input
  // file has been connected and before the first event is processed,
  // e.g. create additional histograms based on which variables are
  // available in the input files.  You can also create all of your
  // histograms and trees in here, but be aware that this method
  // doesn't get called if no events are processed.  So any objects
  // you create here won't be available in the output if you have no
  // input events.
  m_event = wk()->xaodEvent();
  
  const xAOD::EventInfo* eventInfo = nullptr;
  if (!m_event->retrieve( eventInfo, "EventInfo").isSuccess()) {
    Error("execute()", "Failed to retrieve event info collection. Exiting.");
    return EL::StatusCode::FAILURE;
  }
  
  // check if the event is data or simulation
  m_simulation = eventInfo->eventType(xAOD::EventInfo::IS_SIMULATION);
  
  tree = new TTree("tracks", "tree with track variables per event");
  
  AddBranches(tree);
  wk()->addOutput(tree);
  
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode FTKReader :: execute ()
{
  // Here you do everything that needs to be done on every single
  // events, e.g. read input variables, apply cuts, and fill
  // histograms and trees.  This is where most of your actual analysis
  // code will go.
  
  
  // print every 100 events, so we know where we are:
  if((m_eventCounter % 100) == 0) {
    Info("execute()", "Event number = %i", m_eventCounter);
  }
  ++m_eventCounter;
  
  //---------------------------
  // Event information
  //---------------------------
  const xAOD::EventInfo* eventInfo = nullptr;
  if (!m_event->retrieve( eventInfo, "EventInfo").isSuccess()) {
    Error("execute()", "Failed to retrieve event info collection. Exiting.");
    return EL::StatusCode::FAILURE;
  }

  event_number = eventInfo->eventNumber();

  //---------------------------
  // Retrieve tracks
  //---------------------------
  
  // Reconstructed FTK Fast Sim Tracks
  const xAOD::TrackParticleContainer* FTKFastSimTracks = nullptr;
  if ( m_exist_fastsim_tracks && !m_event->retrieve( FTKFastSimTracks, "FTK_Converted_TrackParticles" ).isSuccess() ){
    Warning("execute()", "Failed to retrieve Reconstructed FTK Fast Sim Track container." );
    m_exist_fastsim_tracks = false;
  }
  
  // Reconstructed FTK Full Sim Tracks
  const xAOD::TrackParticleContainer* FTKFullSimTracks = nullptr;
  if ( m_exist_fullsim_tracks && !m_event->retrieve( FTKFullSimTracks, "Converted_FTK_TrackParticles" ).isSuccess() ){
    Warning("execute()", "Failed to retrieve Reconstructed FTK Full Sim Track container." );
    m_exist_fullsim_tracks = false;
  }

  // Reconstructed Offline tracks
  const xAOD::TrackParticleContainer* OfflineTracks = nullptr;
  if ( !m_event->retrieve( OfflineTracks, "InDetTrackParticles" ).isSuccess() ){
    Warning("execute()", "Failed to retrieve Offline track container. Exiting." );
    m_exist_offline_tracks = false;
  }

  // Reset branches
  ResetBranches();

  //---------------------------
  // Object loops
  //---------------------------
  
  // these are indexes in the 
  // original particle container
  int itruth = -1;
  int iftk_fastsim = -1;
  int iftk_fullsim = -1;
  int ioffline = -1;
  
  // truth matching maps
  std::unordered_map<int, std::pair<const xAOD::TrackParticle*, const xAOD::TruthParticle* > > truthMap_FTKFastSimTracks;
  std::unordered_map<int, std::pair<const xAOD::TrackParticle*, const xAOD::TruthParticle* > > truthMap_FTKFullSimTracks;
  std::unordered_map<int, std::pair<const xAOD::TrackParticle*, const xAOD::TruthParticle* > > truthMap_OfflineTracks;

  if (m_truth && m_simulation) {
  
    const xAOD::TruthParticleContainer* truthParticles = nullptr;
    if (!m_event->retrieve(truthParticles, "TruthParticles").isSuccess()) {
      Error("execute()", "Failed to retrieve TruthParticles. Exiting.");
      return EL::StatusCode::FAILURE;
    }


    //---------------------------
    // Fill truth matching maps
    //---------------------------
    
    // fastsim 
    truthMap_FTKFastSimTracks = findBestMatchDR(truthParticles,FTKFastSimTracks,false);
    
    // fullsim
    truthMap_FTKFullSimTracks = findBestMatchDR(truthParticles,FTKFullSimTracks,false);

    // offline
    truthMap_OfflineTracks = findBestMatchDR(truthParticles,OfflineTracks,false);
    
    //std::unordered_map<signed long, bool>hasBarcode_truthParticle; 
    for (auto truthPart: *truthParticles) {
      ++itruth;
      if (!isAcceptedParticle(truthPart)) continue;
      //if(!hasBarcode_truthParticle[truthPart->barcode()]) hasBarcode_truthParticle[truthPart->barcode()] = true;
      
      std::cout << "Truth pt " << truthPart->pt() << std::endl;
      truth_track_pt.push_back(     truthPart->pt() / GeV );
      truth_track_eta.push_back(         truthPart->eta() );
      truth_track_charge.push_back(   truthPart->charge() );
      
      truth_track_pdgid.push_back(     truthPart->pdgId() );
      truth_track_status.push_back(   truthPart->status() );
      truth_track_barcode.push_back( truthPart->barcode() );

      // Tracking decorations
      truth_track_theta.push_back( truthPart->auxdata<float>("theta"));
      truth_track_phi.push_back( truthPart->auxdata<float>("phi"));
      truth_track_d0.push_back( truthPart->auxdata<float>("d0"));
      truth_track_z0.push_back( truthPart->auxdata<float>("z0"));
      truth_track_qop.push_back( truthPart->auxdata<float>("qOverP"));

      
      // ---------------------------  
      // fastsim truth matching info
      // ---------------------------  
      
      std::unordered_map<int, std::pair<const xAOD::TrackParticle*, const xAOD::TruthParticle* > >::const_iterator it_fastsim = truthMap_FTKFastSimTracks.find (itruth); 
      
      if (it_fastsim != truthMap_FTKFastSimTracks.end()) {
        
        truth_ismatched_fastsim.push_back( 1 );
        
        //std::cout << " Matched pt " << truthMap_FTKFastSimTracks[itruth].second->pt() << " Part pt " << truthPart->pt() << std::endl;
       
        float dpt     = truthMap_FTKFastSimTracks[itruth].first->pt()                      - truthMap_FTKFastSimTracks[itruth].second->pt();
        float deta    = truthMap_FTKFastSimTracks[itruth].first->eta()                     - truthMap_FTKFastSimTracks[itruth].second->eta();
        float dtheta  = truthMap_FTKFastSimTracks[itruth].first->auxdata<float>("theta")   - truthMap_FTKFastSimTracks[itruth].second->auxdata<float>("theta");
        float dphi    = truthMap_FTKFastSimTracks[itruth].first->auxdata<float>("phi")     - truthMap_FTKFastSimTracks[itruth].second->auxdata<float>("phi");
        float dd0     = truthMap_FTKFastSimTracks[itruth].first->auxdata<float>("d0")      - truthMap_FTKFastSimTracks[itruth].second->auxdata<float>("d0");
        float dz0     = truthMap_FTKFastSimTracks[itruth].first->auxdata<float>("z0")      - truthMap_FTKFastSimTracks[itruth].second->auxdata<float>("z0");
        float dqop    = truthMap_FTKFastSimTracks[itruth].first->auxdata<float>("qOverP")  - truthMap_FTKFastSimTracks[itruth].second->auxdata<float>("qOverP");
        //dphi = ( dphi <= TMath::Pi() ) ? dphi : ( 2 * TMath::Pi() - dphi );
        
        fastsim_track_delta_pt.push_back( dpt );
        fastsim_track_delta_eta.push_back( deta );
        fastsim_track_delta_theta.push_back( dtheta );
        fastsim_track_delta_phi.push_back( dphi );
        fastsim_track_delta_d0.push_back( dd0 );
        fastsim_track_delta_z0.push_back( dz0 );
        fastsim_track_delta_qop.push_back( dqop );
      
        fastsim_track_true_pt.push_back(      truthMap_FTKFastSimTracks[itruth].second->pt()                      );
        fastsim_track_true_eta.push_back(     truthMap_FTKFastSimTracks[itruth].second->eta()                     );
        fastsim_track_true_theta.push_back(   truthMap_FTKFastSimTracks[itruth].second->auxdata<float>("theta")   );
        fastsim_track_true_phi.push_back(     truthMap_FTKFastSimTracks[itruth].second->auxdata<float>("phi")     );
        fastsim_track_true_d0.push_back(      truthMap_FTKFastSimTracks[itruth].second->auxdata<float>("d0")      );
        fastsim_track_true_z0.push_back(      truthMap_FTKFastSimTracks[itruth].second->auxdata<float>("z0")      );
        fastsim_track_true_qop.push_back(     truthMap_FTKFastSimTracks[itruth].second->auxdata<float>("qOverP")  );
      
      }
      else truth_ismatched_fastsim.push_back( 0 );


      // ---------------------------  
      // fullsim truth matching info
      // ---------------------------  

      std::unordered_map<int, std::pair<const xAOD::TrackParticle*, const xAOD::TruthParticle* > >::const_iterator it_fullsim = truthMap_FTKFullSimTracks.find (itruth); 
      
      if (it_fullsim != truthMap_FTKFullSimTracks.end()) {
        
        truth_ismatched_fullsim.push_back( 1 );
        
        //std::cout << " Matched pt " << truthMap_FTKFullSimTracks[itruth].second->pt() << " Part pt " << truthPart->pt() << std::endl;
       
        float dpt     = truthMap_FTKFullSimTracks[itruth].first->pt()                        - truthMap_FTKFullSimTracks[itruth].second->pt();
        float deta    = truthMap_FTKFullSimTracks[itruth].first->eta()                       - truthMap_FTKFullSimTracks[itruth].second->eta();
        float dtheta  = truthMap_FTKFullSimTracks[itruth].first->auxdata<float>("theta")     - truthMap_FTKFullSimTracks[itruth].second->auxdata<float>("theta");
        float dphi    = truthMap_FTKFullSimTracks[itruth].first->auxdata<float>("phi")       - truthMap_FTKFullSimTracks[itruth].second->auxdata<float>("phi");
        float dd0     = truthMap_FTKFullSimTracks[itruth].first->auxdata<float>("d0")        - truthMap_FTKFullSimTracks[itruth].second->auxdata<float>("d0");
        float dz0     = truthMap_FTKFullSimTracks[itruth].first->auxdata<float>("z0")        - truthMap_FTKFullSimTracks[itruth].second->auxdata<float>("z0");
        float dqop    = truthMap_FTKFullSimTracks[itruth].first->auxdata<float>("qOverP")    - truthMap_FTKFullSimTracks[itruth].second->auxdata<float>("qOverP");
        //dphi = ( dphi <= TMath::Pi() ) ? dphi : ( 2 * TMath::Pi() - dphi );
        
        fullsim_track_delta_pt.push_back( dpt );
        fullsim_track_delta_eta.push_back( deta );
        fullsim_track_delta_theta.push_back( dtheta );
        fullsim_track_delta_phi.push_back( dphi );
        fullsim_track_delta_d0.push_back( dd0 );
        fullsim_track_delta_z0.push_back( dz0 );
        fullsim_track_delta_qop.push_back( dqop );
      
        fullsim_track_true_pt.push_back(      truthMap_FTKFullSimTracks[itruth].second->pt() / GeV                );
        fullsim_track_true_eta.push_back(     truthMap_FTKFullSimTracks[itruth].second->eta()                     );
        fullsim_track_true_theta.push_back(   truthMap_FTKFullSimTracks[itruth].second->auxdata<float>("theta")   );
        fullsim_track_true_phi.push_back(     truthMap_FTKFullSimTracks[itruth].second->auxdata<float>("phi")     );
        fullsim_track_true_d0.push_back(      truthMap_FTKFullSimTracks[itruth].second->auxdata<float>("d0")      );
        fullsim_track_true_z0.push_back(      truthMap_FTKFullSimTracks[itruth].second->auxdata<float>("z0")      );
        fullsim_track_true_qop.push_back(     truthMap_FTKFullSimTracks[itruth].second->auxdata<float>("qOverP")  );
      
      }
      else truth_ismatched_fullsim.push_back( 0 );


      // ---------------------------  
      // offline truth matching info
      // ---------------------------  

      std::unordered_map<int, std::pair<const xAOD::TrackParticle*, const xAOD::TruthParticle* > >::const_iterator it_offline = truthMap_OfflineTracks.find (itruth); 
      
      if (it_offline != truthMap_OfflineTracks.end()) {
        
        truth_ismatched_offline.push_back( 1 );
        
        //std::cout << " Matched pt " << truthMap_OfflineTracks[itruth].second->pt() << " Part pt " << truthPart->pt() << std::endl;
       
        float dpt     = truthMap_OfflineTracks[itruth].first->pt()                        - truthMap_OfflineTracks[itruth].second->pt();
        float deta    = truthMap_OfflineTracks[itruth].first->eta()                       - truthMap_OfflineTracks[itruth].second->eta();
        float dtheta  = truthMap_OfflineTracks[itruth].first->auxdata<float>("theta")     - truthMap_OfflineTracks[itruth].second->auxdata<float>("theta");
        float dphi    = truthMap_OfflineTracks[itruth].first->auxdata<float>("phi")       - truthMap_OfflineTracks[itruth].second->auxdata<float>("phi");
        float dd0     = truthMap_OfflineTracks[itruth].first->auxdata<float>("d0")        - truthMap_OfflineTracks[itruth].second->auxdata<float>("d0");
        float dz0     = truthMap_OfflineTracks[itruth].first->auxdata<float>("z0")        - truthMap_OfflineTracks[itruth].second->auxdata<float>("z0");
        float dqop    = truthMap_OfflineTracks[itruth].first->auxdata<float>("qOverP")    - truthMap_OfflineTracks[itruth].second->auxdata<float>("qOverP");
        //dphi = ( dphi <= TMath::Pi() ) ? dphi : ( 2 * TMath::Pi() - dphi );
        
        offline_track_delta_pt.push_back( dpt );
        offline_track_delta_eta.push_back( deta );
        offline_track_delta_theta.push_back( dtheta );
        offline_track_delta_phi.push_back( dphi );
        offline_track_delta_d0.push_back( dd0 );
        offline_track_delta_z0.push_back( dz0 );
        offline_track_delta_qop.push_back( dqop );
      
        offline_track_true_pt.push_back(      truthMap_OfflineTracks[itruth].second->pt()                      );
        offline_track_true_eta.push_back(     truthMap_OfflineTracks[itruth].second->eta()                     );
        offline_track_true_theta.push_back(   truthMap_OfflineTracks[itruth].second->auxdata<float>("theta")   );
        offline_track_true_phi.push_back(     truthMap_OfflineTracks[itruth].second->auxdata<float>("phi")     );
        offline_track_true_d0.push_back(      truthMap_OfflineTracks[itruth].second->auxdata<float>("d0")      );
        offline_track_true_z0.push_back(      truthMap_OfflineTracks[itruth].second->auxdata<float>("z0")      );
        offline_track_true_qop.push_back(     truthMap_OfflineTracks[itruth].second->auxdata<float>("qOverP")  );
      
      }
      else truth_ismatched_offline.push_back( 0 );

    }
    truth_track_n = itruth + 1;
  } 


  //std::unordered_map<signed long, bool>hasBarcode_fastTrack; 
  for (auto fastTrack: *FTKFastSimTracks) {
    ++iftk_fastsim;
    if (!isAcceptedParticle(fastTrack)) continue;
    
    std::cout << "FTKFast pt " << fastTrack->pt() << std::endl;
    fastsim_track_pt.push_back( fastTrack->pt() / GeV );
    fastsim_track_eta.push_back( fastTrack->eta() );
    fastsim_track_charge.push_back( fastTrack->charge() );
    
    // Tracking decorations
    fastsim_track_theta.push_back( fastTrack->auxdata<float>("theta"));
    fastsim_track_phi.push_back( fastTrack->auxdata<float>("phi"));
    fastsim_track_d0.push_back( fastTrack->auxdata<float>("d0"));
    fastsim_track_z0.push_back( fastTrack->auxdata<float>("z0"));
    fastsim_track_qop.push_back( fastTrack->auxdata<float>("qOverP"));
    
    //fillBarcodeMap(hasBarcode_fastTrack,fastTrack,"fastTrack"); 

  }
  fastsim_track_n = iftk_fastsim + 1;



  //std::unordered_map<signed long, bool>hasBarcode_fullTrack; 
  for (auto fullTrack: *FTKFullSimTracks) {
    ++iftk_fullsim; 
    if (!isAcceptedParticle(fullTrack)) continue;
    
    std::cout << "FTKFull pt " << fullTrack->pt() << std::endl;
    fullsim_track_pt.push_back( fullTrack->pt() / GeV );
    fullsim_track_eta.push_back( fullTrack->eta() );
    fullsim_track_charge.push_back( fullTrack->charge() );
    
    // Tracking decorations
    fullsim_track_theta.push_back( fullTrack->auxdata<float>("theta"));
    fullsim_track_phi.push_back( fullTrack->auxdata<float>("phi"));
    fullsim_track_d0.push_back( fullTrack->auxdata<float>("d0"));
    fullsim_track_z0.push_back( fullTrack->auxdata<float>("z0"));
    fullsim_track_qop.push_back( fullTrack->auxdata<float>("qOverP"));

    //fillBarcodeMap(hasBarcode_fullTrack,fullTrack,"fullTrack"); 
  
  }
  fullsim_track_n = iftk_fullsim + 1;




  //std::unordered_map<signed long, bool>hasBarcode_offlineTrack; 
  for (auto offlineTrack: *OfflineTracks) {
    ++ioffline; 
    if (!isAcceptedParticle(offlineTrack)) continue;
    
    offline_track_pt.push_back( offlineTrack->pt() / GeV);
    offline_track_eta.push_back( offlineTrack->eta() );
    offline_track_charge.push_back( offlineTrack->charge() );
    
    // Tracking decorations
    offline_track_theta.push_back( offlineTrack->auxdata<float>("theta"));
    offline_track_phi.push_back( offlineTrack->auxdata<float>("phi"));
    offline_track_d0.push_back( offlineTrack->auxdata<float>("d0"));
    offline_track_z0.push_back( offlineTrack->auxdata<float>("z0"));
    offline_track_qop.push_back( offlineTrack->auxdata<float>("qOverP"));
    
    //fillBarcodeMap(hasBarcode_offlineTrack,offlineTrack,"offlineTrack"); 
  
  }
  offline_track_n = ioffline + 1;



  // fill the tree
  tree->Fill();
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode FTKReader :: postExecute ()
{
  // Here you do everything that needs to be done after the main event
  // processing.  This is typically very rare, particularly in user
  // code.  It is mainly used in implementing the NTupleSvc.
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode FTKReader :: finalize ()
{
  // This method is the mirror image of initialize(), meaning it gets
  // called after the last event has been processed on the worker node
  // and allows you to finish up any objects you created in
  // initialize() before they are written to disk.  This is actually
  // fairly rare, since this happens separately for each worker node.
  // Most of the time you want to do your post-processing on the
  // submission node after all your histogram outputs have been
  // merged.  This is different from histFinalize() in that it only
  // gets called on worker nodes that processed input events.
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode FTKReader :: histFinalize ()
{
  // This method is the mirror image of histInitialize(), meaning it
  // gets called after the last event has been processed on the worker
  // node and allows you to finish up any objects you created in
  // histInitialize() before they are written to disk.  This is
  // actually fairly rare, since this happens separately for each
  // worker node.  Most of the time you want to do your
  // post-processing on the submission node after all your histogram
  // outputs have been merged.  This is different from finalize() in
  // that it gets called on all worker nodes regardless of whether
  // they processed input events.
  return EL::StatusCode::SUCCESS;
}

void FTKReader::AddBranches(TTree* tree) {
  
  tree->Branch("event_number",         &event_number,       "event_number/I");
  tree->Branch("fastsim_track_n",      &fastsim_track_n, "fastsim_track_n/I");
  tree->Branch("fullsim_track_n",      &fullsim_track_n, "fullsim_track_n/I");
  tree->Branch("offline_track_n",      &offline_track_n, "offline_track_n/I");
  
  if (m_truth && m_simulation) {
    tree->Branch("truth_track_n",       &truth_track_n,       "truth_track_n/I");
    
    tree->Branch("truth_track_pt",      &truth_track_pt      );
    tree->Branch("truth_track_eta",     &truth_track_eta     );
    tree->Branch("truth_track_phi",     &truth_track_phi     );
    tree->Branch("truth_track_d0",      &truth_track_d0      );
    tree->Branch("truth_track_z0",      &truth_track_z0      );
    tree->Branch("truth_track_qop",     &truth_track_qop     );
    tree->Branch("truth_track_charge",  &truth_track_charge  );
    tree->Branch("truth_track_theta",   &truth_track_theta   );
    
    tree->Branch("truth_track_pdgid",   &truth_track_pdgid   );
    tree->Branch("truth_track_barcode", &truth_track_barcode );
    tree->Branch("truth_track_status",  &truth_track_status  );

    tree->Branch("truth_ismatched_fastsim", &truth_ismatched_fastsim );
    tree->Branch("truth_ismatched_fullsim", &truth_ismatched_fullsim );
    tree->Branch("truth_ismatched_offline", &truth_ismatched_offline );
    
  }



  tree->Branch("fastsim_track_pt",       &fastsim_track_pt        );
  tree->Branch("fastsim_track_eta",      &fastsim_track_eta       );
  tree->Branch("fastsim_track_phi",      &fastsim_track_phi       );
  tree->Branch("fastsim_track_d0",       &fastsim_track_d0        );
  tree->Branch("fastsim_track_z0",       &fastsim_track_z0        );
  tree->Branch("fastsim_track_qop",      &fastsim_track_qop       );
  tree->Branch("fastsim_track_theta",    &fastsim_track_theta     );
  
  tree->Branch("fastsim_track_true_pt",       &fastsim_track_true_pt        );
  tree->Branch("fastsim_track_true_eta",      &fastsim_track_true_eta       );
  tree->Branch("fastsim_track_true_phi",      &fastsim_track_true_phi       );
  tree->Branch("fastsim_track_true_d0",       &fastsim_track_true_d0        );
  tree->Branch("fastsim_track_true_z0",       &fastsim_track_true_z0        );
  tree->Branch("fastsim_track_true_qop",      &fastsim_track_true_qop       );
  tree->Branch("fastsim_track_true_theta",    &fastsim_track_true_theta     );
  
  tree->Branch("fastsim_track_delta_pt",       &fastsim_track_delta_pt        );
  tree->Branch("fastsim_track_delta_eta",      &fastsim_track_delta_eta       );
  tree->Branch("fastsim_track_delta_phi",      &fastsim_track_delta_phi       );
  tree->Branch("fastsim_track_delta_d0",       &fastsim_track_delta_d0        );
  tree->Branch("fastsim_track_delta_z0",       &fastsim_track_delta_z0        );
  tree->Branch("fastsim_track_delta_qop",      &fastsim_track_delta_qop       );
  tree->Branch("fastsim_track_delta_theta",    &fastsim_track_delta_theta     );
  
  tree->Branch("fastsim_track_charge",   &fastsim_track_charge    );
  //tree->Branch("fastsim_track_ismatched",&fastsim_track_ismatched );
 


  tree->Branch("fullsim_track_pt",       &fullsim_track_pt        );
  tree->Branch("fullsim_track_eta",      &fullsim_track_eta       );
  tree->Branch("fullsim_track_phi",      &fullsim_track_phi       );
  tree->Branch("fullsim_track_d0",       &fullsim_track_d0        );
  tree->Branch("fullsim_track_z0",       &fullsim_track_z0        );
  tree->Branch("fullsim_track_qop",      &fullsim_track_qop       );
  tree->Branch("fullsim_track_theta",    &fullsim_track_theta     );
  
  tree->Branch("fullsim_track_true_pt",       &fullsim_track_true_pt        );
  tree->Branch("fullsim_track_true_eta",      &fullsim_track_true_eta       );
  tree->Branch("fullsim_track_true_phi",      &fullsim_track_true_phi       );
  tree->Branch("fullsim_track_true_d0",       &fullsim_track_true_d0        );
  tree->Branch("fullsim_track_true_z0",       &fullsim_track_true_z0        );
  tree->Branch("fullsim_track_true_qop",      &fullsim_track_true_qop       );
  tree->Branch("fullsim_track_true_theta",    &fullsim_track_true_theta     );
  
  tree->Branch("fullsim_track_delta_pt",       &fullsim_track_delta_pt        );
  tree->Branch("fullsim_track_delta_eta",      &fullsim_track_delta_eta       );
  tree->Branch("fullsim_track_delta_phi",      &fullsim_track_delta_phi       );
  tree->Branch("fullsim_track_delta_d0",       &fullsim_track_delta_d0        );
  tree->Branch("fullsim_track_delta_z0",       &fullsim_track_delta_z0        );
  tree->Branch("fullsim_track_delta_qop",      &fullsim_track_delta_qop       );
  tree->Branch("fullsim_track_delta_theta",    &fullsim_track_delta_theta     );
  
  tree->Branch("fullsim_track_charge",   &fullsim_track_charge    );
  //tree->Branch("fullsim_track_ismatched",&fullsim_track_ismatched );
 


  tree->Branch("offline_track_pt",       &offline_track_pt        );
  tree->Branch("offline_track_eta",      &offline_track_eta       );
  tree->Branch("offline_track_phi",      &offline_track_phi       );
  tree->Branch("offline_track_d0",       &offline_track_d0        );
  tree->Branch("offline_track_z0",       &offline_track_z0        );
  tree->Branch("offline_track_qop",      &offline_track_qop       );
  tree->Branch("offline_track_theta",    &offline_track_theta     );
  
  tree->Branch("offline_track_true_pt",       &offline_track_true_pt        );
  tree->Branch("offline_track_true_eta",      &offline_track_true_eta       );
  tree->Branch("offline_track_true_phi",      &offline_track_true_phi       );
  tree->Branch("offline_track_true_d0",       &offline_track_true_d0        );
  tree->Branch("offline_track_true_z0",       &offline_track_true_z0        );
  tree->Branch("offline_track_true_qop",      &offline_track_true_qop       );
  tree->Branch("offline_track_true_theta",    &offline_track_true_theta     );
  
  tree->Branch("offline_track_delta_pt",       &offline_track_delta_pt        );
  tree->Branch("offline_track_delta_eta",      &offline_track_delta_eta       );
  tree->Branch("offline_track_delta_phi",      &offline_track_delta_phi       );
  tree->Branch("offline_track_delta_d0",       &offline_track_delta_d0        );
  tree->Branch("offline_track_delta_z0",       &offline_track_delta_z0        );
  tree->Branch("offline_track_delta_qop",      &offline_track_delta_qop       );
  tree->Branch("offline_track_delta_theta",    &offline_track_delta_theta     );
  
  tree->Branch("offline_track_charge",   &offline_track_charge    );
  //tree->Branch("offline_track_ismatched",&offline_track_ismatched );

}

void FTKReader::ResetBranches() {

 truth_track_pt.clear();   
 truth_track_eta.clear();   
 truth_track_phi.clear();   
 truth_track_d0.clear();   
 truth_track_z0.clear();    
 truth_track_qop.clear();  
 truth_track_charge.clear();
 truth_track_theta.clear(); 
 
 truth_track_pdgid.clear();  
 truth_track_barcode.clear();
 truth_track_status.clear(); 

 truth_ismatched_fastsim.clear();
 truth_ismatched_fullsim.clear();
 truth_ismatched_offline.clear();


 fastsim_track_pt.clear();   
 fastsim_track_eta.clear();   
 fastsim_track_phi.clear();   
 fastsim_track_d0.clear();   
 fastsim_track_z0.clear();    
 fastsim_track_qop.clear();  
 fastsim_track_theta.clear(); 
 
 fastsim_track_true_pt.clear();   
 fastsim_track_true_eta.clear();   
 fastsim_track_true_phi.clear();   
 fastsim_track_true_d0.clear();   
 fastsim_track_true_z0.clear();    
 fastsim_track_true_qop.clear();  
 fastsim_track_true_theta.clear(); 
 
 fastsim_track_delta_pt.clear();   
 fastsim_track_delta_eta.clear();   
 fastsim_track_delta_phi.clear();   
 fastsim_track_delta_d0.clear();   
 fastsim_track_delta_z0.clear();    
 fastsim_track_delta_qop.clear();  
 fastsim_track_delta_theta.clear(); 
 
 fastsim_track_charge.clear();
 //fastsim_track_ismatched.clear();
 
 fullsim_track_pt.clear();   
 fullsim_track_eta.clear();   
 fullsim_track_phi.clear();   
 fullsim_track_d0.clear();   
 fullsim_track_z0.clear();    
 fullsim_track_qop.clear();  
 fullsim_track_theta.clear(); 
 
 fullsim_track_true_pt.clear();   
 fullsim_track_true_eta.clear();   
 fullsim_track_true_phi.clear();   
 fullsim_track_true_d0.clear();   
 fullsim_track_true_z0.clear();    
 fullsim_track_true_qop.clear();  
 fullsim_track_true_theta.clear(); 
 
 fullsim_track_delta_pt.clear();   
 fullsim_track_delta_eta.clear();   
 fullsim_track_delta_phi.clear();   
 fullsim_track_delta_d0.clear();   
 fullsim_track_delta_z0.clear();    
 fullsim_track_delta_qop.clear();  
 fullsim_track_delta_theta.clear(); 
 
 fullsim_track_charge.clear();
 //fullsim_track_ismatched.clear();
 
 offline_track_pt.clear();   
 offline_track_eta.clear();   
 offline_track_phi.clear();   
 offline_track_d0.clear();   
 offline_track_z0.clear();    
 offline_track_qop.clear();  
 offline_track_theta.clear(); 
 
 offline_track_true_pt.clear();   
 offline_track_true_eta.clear();   
 offline_track_true_phi.clear();   
 offline_track_true_d0.clear();   
 offline_track_true_z0.clear();    
 offline_track_true_qop.clear();  
 offline_track_true_theta.clear(); 
 
 offline_track_delta_pt.clear();   
 offline_track_delta_eta.clear();   
 offline_track_delta_phi.clear();   
 offline_track_delta_d0.clear();   
 offline_track_delta_z0.clear();    
 offline_track_delta_qop.clear();  
 offline_track_delta_theta.clear(); 
 
 offline_track_charge.clear();
 //offline_track_ismatched.clear();

}

