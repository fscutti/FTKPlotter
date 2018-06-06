from hists import *
from style import *
import ROOT

"""
This contains the histogram configuration
"""

use_roostat = False
use_fit = True

min = -0.5
max = 0.5


hlist = []

for typ in ["truth", "fastsim", "fullsim", "offline"]:
  
  # ----------
  # kinematics
  # ----------
   
  globals()["h_%s_track_pt"%typ] = Hist( hname      = "h_%s_track_pt"%typ,
                                           leg_entry  = typ,
                                           xtitle     = "p_{T}(#mu) [GeV]",
                                           ytitle     = "Entries",
                                           nbins      = 100,
                                           xmin       = 0.,
                                           xmax       = 1000.,
                                           var_fill   = "%s_track_pt"%typ,
                                           style_dict = globals()["%s_style"%typ],
                                           )
  hlist.append(globals()["h_%s_track_pt"%typ])




for typ in ["fastsim", "fullsim", "offline"]:
  
  # -------------
  # truth matched
  # -------------
   
  globals()["h_truth_%s_matched_track_pt"%typ] = Hist( hname      = "h_truth_%s_matched_track_pt"%typ,
                                                         leg_entry  = typ,
                                                         xtitle     = "p_{T}(#mu) [GeV]",
                                                         ytitle     = "Entries",
                                                         nbins      = 100,
                                                         xmin       = 0.,
                                                         xmax       = 1000.,
                                                         var_fill   = "truth_track_pt",
                                                         selection  = "truth_ismatched_%s==1"%(typ),
                                                         style_dict = globals()["%s_style"%typ],
                                                         )
  hlist.append(globals()["h_truth_%s_matched_track_pt"%typ])


  # ------------
  # efficiencies
  # ------------

  globals()["h_truth_%s_eff_track_pt"%typ] = Hist( hname              = "h_truth_%s_eff_track_pt"%typ,
                                                         leg_entry      = typ,
                                                         xtitle         = "p_{T}(#mu) [GeV]",
                                                         ytitle         = "Entries",
                                                         nbins          = 200,
                                                         xmin           = 0.,
                                                         xmax           = 1000.,
                                                         var_fill       = "truth_track_pt",
                                                         num_selection  = "truth_ismatched_%s==1"%(typ),
                                                         style_dict = globals()["%s_style"%typ],
                                                         )
  hlist.append(globals()["h_truth_%s_eff_track_pt"%typ])
 

  # ---------------------
  # inclusive resolutions
  # ---------------------

  globals()["h_%s_track_delta_pt"%typ] = Hist( hname      = "h_%s_track_delta_pt"%typ,
                                                         leg_entry  = typ,
                                                         xtitle     = "p_{T}(true) - p_{T}(reco)[GeV]",
                                                         ytitle     = "Entries",
                                                         nbins      = 100000,
                                                         xmin       = -1000,
                                                         xmax       = 1000,
                                                         var_fill   = "%s_track_delta_pt"%typ,
                                                         style_dict = globals()["%s_style"%typ],
                                                         )
  hlist.append(globals()["h_%s_track_delta_pt"%typ])
 
  
  globals()["h_%s_track_delta_qinv2pt"%typ] = Hist( hname      = "h_%s_track_delta_qinv2pt"%typ,
                                                         leg_entry  = typ,
                                                         xtitle     = "q/2p_{T}(true) - q/2p_{T}(reco) [GeV^{-1}]",
                                                         ytitle     = "Entries",
                                                         nbins      = 400000,
                                                         xmin       = -1000,
                                                         xmax       = 1000,
                                                         var_fill   = "%s_track_delta_qinv2pt"%typ,
                                                         style_dict = globals()["%s_style"%typ],
                                                         )
  hlist.append(globals()["h_%s_track_delta_qinv2pt"%typ])

  
  globals()["h_%s_track_delta_eta"%typ] = Hist( hname      = "h_%s_track_delta_eta"%typ,
                                                         leg_entry  = typ,
                                                         xtitle     = "#eta(true) - #eta(reco)",
                                                         ytitle     = "Entries",
                                                         nbins      = 50,
                                                         xmin       = -0.05,
                                                         xmax       = 0.05,
                                                         var_fill   = "%s_track_delta_eta"%typ,
                                                         style_dict = globals()["%s_style"%typ],
                                                         )
  hlist.append(globals()["h_%s_track_delta_eta"%typ])


  globals()["h_%s_track_delta_phi"%typ] = Hist( hname      = "h_%s_track_delta_phi"%typ,
                                                         leg_entry  = typ,
                                                         xtitle     = "#phi(true) - #phi(reco)",
                                                         ytitle     = "Entries",
                                                         nbins      = 50,
                                                         xmin       = -0.03,
                                                         xmax       = 0.03,
                                                         var_fill   = "%s_track_delta_phi"%typ,
                                                         style_dict = globals()["%s_style"%typ],
                                                         )
  hlist.append(globals()["h_%s_track_delta_phi"%typ])


  globals()["h_%s_track_delta_d0"%typ] = Hist( hname      = "h_%s_track_delta_d0"%typ,
                                                         leg_entry  = typ,
                                                         xtitle     = "d_{0}(true) - d_{0}(reco)[mm]",
                                                         ytitle     = "Entries",
                                                         nbins      = 50,
                                                         xmin       = -2.,
                                                         xmax       = 2.,
                                                         var_fill   = "%s_track_delta_d0"%typ,
                                                         style_dict = globals()["%s_style"%typ],
                                                         )
  hlist.append(globals()["h_%s_track_delta_d0"%typ])

  
  globals()["h_%s_track_delta_z0"%typ] = Hist( hname      = "h_%s_track_delta_z0"%typ,
                                                         leg_entry  = typ,
                                                         xtitle     = "z_{0}(true) - z_{0}(reco)[mm]",
                                                         ytitle     = "Entries",
                                                         nbins      = 50,
                                                         xmin       = -10.,
                                                         xmax       = 10.,
                                                         var_fill   = "%s_track_delta_z0"%typ,
                                                         style_dict = globals()["%s_style"%typ],
                                                         )
  hlist.append(globals()["h_%s_track_delta_z0"%typ])


  globals()["h_%s_track_delta_theta"%typ] = Hist( hname      = "h_%s_track_delta_theta"%typ,
                                                         leg_entry  = typ,
                                                         xtitle     = "#theta(true) - #theta(reco)",
                                                         ytitle     = "Entries",
                                                         nbins      = 50,
                                                         xmin       = -0.007,
                                                         xmax       = 0.007,
                                                         var_fill   = "%s_track_delta_theta"%typ,
                                                         style_dict = globals()["%s_style"%typ],
                                                         )
  hlist.append(globals()["h_%s_track_delta_theta"%typ])


  globals()["h_%s_track_delta_qop"%typ] = Hist( hname      = "h_%s_track_delta_qop"%typ,
                                                         leg_entry  = typ,
                                                         xtitle     = "q/p(true) - q/p(reco)[GeV^{-1}]",
                                                         ytitle     = "Entries",
                                                         nbins      = 50,
                                                         xmin       = -0.08,
                                                         xmax       = 0.08,
                                                         var_fill   = "%s_track_delta_qop"%typ,
                                                         style_dict = globals()["%s_style"%typ],
                                                         )
  hlist.append(globals()["h_%s_track_delta_qop"%typ])


  # -------------------
  # profile resolutions
  # -------------------
  
  globals()["h_%s_track_reso_qinv2pt_vs_truth_track_qinv2pt"%typ] = Hist( hname        = "h_%s_track_reso_qinv2pt_vs_truth_track_qinv2pt"%typ,
                                                                 is_profile   = True,
                                                                 use_roostat = use_roostat,
                                                                 use_fit      = use_fit,
                                                                 get_slices   = True,
                                                                 leg_entry    = typ,
                                                                 ytitle       = "q/2p_{T}(true) - q/2p_{T}(reco) [GeV^{-1}]",
                                                                 xtitle       = "q/2p_{T}(true) [GeV^{-1}]",
                                                                 nbins        = 22,
                                                                 xmin         = min,
                                                                 xmax         = max,
                                                                 ymin         = -0.08,
                                                                 ymax         = 0.08,
                                                                 fitmin       = -0.04,
                                                                 fitmax       = 0.04,
                                                                 var_fill_x   = "%s_track_true_qinv2pt"%typ,
                                                                 var_fill_y   = "%s_track_delta_qinv2pt"%typ,
                                                                 style_dict   = globals()["%s_style"%typ],
                                                                 )
  hlist.append(globals()["h_%s_track_reso_qinv2pt_vs_truth_track_qinv2pt"%typ])
  
  
  globals()["h_%s_track_reso_eta_vs_truth_track_qinv2pt"%typ] = Hist( hname        = "h_%s_track_reso_eta_vs_truth_track_qinv2pt"%typ,
                                                                 is_profile   = True,
                                                                 use_roostat = use_roostat,
                                                                 use_fit      = use_fit,
                                                                 get_slices   = True,
                                                                 leg_entry    = typ,
                                                                 ytitle       = "#eta(true) - #eta(reco)",
                                                                 xtitle       = "q/2p_{T}(true) [GeV^{-1}]",
                                                                 nbins        = 22,
                                                                 xmin         = min,
                                                                 xmax         = max,
                                                                 ymin         = -0.02,
                                                                 ymax         = 0.02,
                                                                 fitmin       = -0.014,
                                                                 fitmax       = 0.014,
                                                                 var_fill_x   = "%s_track_true_qinv2pt"%typ,
                                                                 var_fill_y   = "%s_track_delta_eta"%typ,
                                                                 style_dict   = globals()["%s_style"%typ],
                                                                 )
  hlist.append(globals()["h_%s_track_reso_eta_vs_truth_track_qinv2pt"%typ])


  globals()["h_%s_track_reso_phi_vs_truth_track_qinv2pt"%typ] = Hist( hname        = "h_%s_track_reso_phi_vs_truth_track_qinv2pt"%typ,
                                                                 is_profile   = True,
                                                                 use_roostat = use_roostat,
                                                                 use_fit      = use_fit,
                                                                 get_slices   = True,
                                                                 leg_entry    = typ,
                                                                 ytitle       = "#phi(true) - #phi(reco)",
                                                                 xtitle       = "q/2p_{T}(true) [GeV^{-1}]",
                                                                 nbins        = 22,
                                                                 xmin         = min,
                                                                 xmax         = max,
                                                                 ymin         = -0.02,
                                                                 ymax         = 0.02,
                                                                 fitmin       = -0.014,
                                                                 fitmax       = 0.014,
                                                                 var_fill_x   = "%s_track_true_qinv2pt"%typ,
                                                                 var_fill_y   = "%s_track_delta_phi"%typ,
                                                                 style_dict   = globals()["%s_style"%typ],
                                                                 )
  hlist.append(globals()["h_%s_track_reso_phi_vs_truth_track_qinv2pt"%typ])

  
  globals()["h_%s_track_reso_d0_vs_truth_track_qinv2pt"%typ] = Hist( hname        = "h_%s_track_reso_d0_vs_truth_track_qinv2pt"%typ,
                                                                 is_profile   = True,
                                                                 use_roostat = use_roostat,
                                                                 use_fit      = use_fit,
                                                                 get_slices   = True,
                                                                 leg_entry    = typ,
                                                                 ytitle       = "d_{0}(true) - d_{0}(reco)",
                                                                 xtitle       = "q/2p_{T}(true) [GeV^{-1}]",
                                                                 nbins        = 22,
                                                                 xmin         = min,
                                                                 xmax         = max,
                                                                 ymin         = -0.9,
                                                                 ymax         = 0.9,
                                                                 fitmin       = -0.35,
                                                                 fitmax       = 0.35,
                                                                 var_fill_x   = "%s_track_true_qinv2pt"%typ,
                                                                 var_fill_y   = "%s_track_delta_d0"%typ,
                                                                 #var_fill_y2  = "%s_track_true_d0"%typ,
                                                                 style_dict   = globals()["%s_style"%typ],
                                                                 )
  hlist.append(globals()["h_%s_track_reso_d0_vs_truth_track_qinv2pt"%typ])
 

  globals()["h_%s_track_reso_z0_vs_truth_track_qinv2pt"%typ] = Hist( hname    = "h_%s_track_reso_z0_vs_truth_track_qinv2pt"%typ,
                                                                 is_profile   = True,
                                                                 use_roostat = use_roostat,
                                                                 use_fit      = use_fit,
                                                                 get_slices   = True,
                                                                 leg_entry    = typ,
                                                                 ytitle       = "z_{0}(true) - z_{0}(reco) [mm]",
                                                                 xtitle       = "q/2p_{T}(true) [GeV^{-1}]",
                                                                 nbins        = 22,
                                                                 xmin         = min,
                                                                 xmax         = max,
                                                                 ymin         = -4.5,
                                                                 ymax         = 4.5,
                                                                 fitmin       = -2.0,
                                                                 fitmax       = 2.0,
                                                                 var_fill_x   = "%s_track_true_qinv2pt"%typ,
                                                                 var_fill_y   = "%s_track_delta_z0"%typ,
                                                                 style_dict   = globals()["%s_style"%typ],
                                                                 )
  hlist.append(globals()["h_%s_track_reso_z0_vs_truth_track_qinv2pt"%typ])





  globals()["h_%s_track_reso_qinv2pt_vs_truth_track_eta"%typ] = Hist( hname        = "h_%s_track_reso_qinv2pt_vs_truth_track_eta"%typ,
                                                                 is_profile   = True,
                                                                 use_roostat = use_roostat,
                                                                 use_fit      = use_fit,
                                                                 get_slices   = True,
                                                                 leg_entry    = typ,
                                                                 ytitle       = "q/2p_{T}(true) - q/2p_{T}(reco) [GeV^{-1}]",
                                                                 xtitle       = "#eta",
                                                                 nbins        = 10,
                                                                 xmin         = -2.5,
                                                                 xmax         = 2.5,
                                                                 ymin         = -0.06,
                                                                 ymax         = 0.06,
                                                                 fitmin       = -0.02,
                                                                 fitmax       = 0.02,
                                                                 var_fill_x   = "%s_track_true_eta"%typ,
                                                                 var_fill_y   = "%s_track_delta_qinv2pt"%typ,
                                                                 style_dict   = globals()["%s_style"%typ],
                                                                 )
  hlist.append(globals()["h_%s_track_reso_qinv2pt_vs_truth_track_eta"%typ])
  
  
  globals()["h_%s_track_reso_eta_vs_truth_track_eta"%typ] = Hist( hname        = "h_%s_track_reso_eta_vs_truth_track_eta"%typ,
                                                                 is_profile   = True,
                                                                 use_roostat = use_roostat,
                                                                 use_fit      = use_fit,
                                                                 get_slices   = True,
                                                                 leg_entry    = typ,
                                                                 ytitle       = "#eta(true) - #eta(reco)",
                                                                 xtitle       = "#eta",
                                                                 nbins        = 10,
                                                                 xmin         = -2.5,
                                                                 xmax         = 2.5,
                                                                 ymin         = -0.02,
                                                                 ymax         = 0.02,
                                                                 fitmin       = -0.003,
                                                                 fitmax       = 0.003,
                                                                 var_fill_x   = "%s_track_true_eta"%typ,
                                                                 var_fill_y   = "%s_track_delta_eta"%typ,
                                                                 style_dict   = globals()["%s_style"%typ],
                                                                 )
  hlist.append(globals()["h_%s_track_reso_eta_vs_truth_track_eta"%typ])


  globals()["h_%s_track_reso_phi_vs_truth_track_eta"%typ] = Hist( hname        = "h_%s_track_reso_phi_vs_truth_track_eta"%typ,
                                                                 is_profile   = True,
                                                                 use_roostat = use_roostat,
                                                                 use_fit      = use_fit,
                                                                 get_slices   = True,
                                                                 leg_entry    = typ,
                                                                 ytitle       = "#phi(true) - #phi(reco)",
                                                                 xtitle       = "#eta",
                                                                 nbins        = 10,
                                                                 xmin         = -2.5,
                                                                 xmax         = 2.5,
                                                                 ymin         = -0.02,
                                                                 ymax         = 0.02,
                                                                 fitmin       = -0.005,
                                                                 fitmax       = 0.005,
                                                                 var_fill_x   = "%s_track_true_eta"%typ,
                                                                 var_fill_y   = "%s_track_delta_phi"%typ,
                                                                 style_dict   = globals()["%s_style"%typ],
                                                                 )
  hlist.append(globals()["h_%s_track_reso_phi_vs_truth_track_eta"%typ])

  
  globals()["h_%s_track_reso_d0_vs_truth_track_eta"%typ] = Hist( hname        = "h_%s_track_reso_d0_vs_truth_track_eta"%typ,
                                                                 is_profile   = True,
                                                                 use_roostat = use_roostat,
                                                                 use_fit      = use_fit,
                                                                 get_slices   = True,
                                                                 leg_entry    = typ,
                                                                 ytitle       = "d_{0}(true) - d_{0}(reco)",
                                                                 xtitle       = "#eta",
                                                                 nbins        = 10,
                                                                 xmin         = -2.5,
                                                                 xmax         = 2.5,
                                                                 ymin         = -0.9,
                                                                 ymax         = 0.9,
                                                                 fitmin       = -0.2,
                                                                 fitmax       = 0.2,
                                                                 var_fill_x   = "%s_track_true_eta"%typ,
                                                                 var_fill_y   = "%s_track_delta_d0"%typ,
                                                                 style_dict   = globals()["%s_style"%typ],
                                                                 )
  hlist.append(globals()["h_%s_track_reso_d0_vs_truth_track_eta"%typ])
 

  globals()["h_%s_track_reso_z0_vs_truth_track_eta"%typ] = Hist( hname    = "h_%s_track_reso_z0_vs_truth_track_eta"%typ,
                                                                 is_profile   = True,
                                                                 use_roostat = use_roostat,
                                                                 use_fit      = use_fit,
                                                                 get_slices   = True,
                                                                 leg_entry    = typ,
                                                                 ytitle       = "z_{0}(true) - z_{0}(reco) [mm]",
                                                                 xtitle       = "#eta",
                                                                 nbins        = 10,
                                                                 xmin         = -2.5,
                                                                 xmax         = 2.5,
                                                                 ymin         = -4.0,
                                                                 ymax         = 4.0,
                                                                 fitmin       = -1.5,
                                                                 fitmax       = 1.5,
                                                                 var_fill_x   = "%s_track_true_eta"%typ,
                                                                 var_fill_y   = "%s_track_delta_z0"%typ,
                                                                 style_dict   = globals()["%s_style"%typ],
                                                                 )
  hlist.append(globals()["h_%s_track_reso_z0_vs_truth_track_eta"%typ])




## EOF


