from plots import *
import ROOT

"""
This contains the plot configuration
"""


p_track_pt  = Plot1D( pname      = "p_track_pt",
                      leg_head   = "p_{T}",
                      plot_stat  = True,
                      hlist      = ["h_truth_track_pt","h_fastsim_track_pt","h_fullsim_track_pt","h_offline_track_pt"],
                      ratio_num  = "h_truth_track_pt",
                      xtitle     = "p_{T}(#mu) [GeV]",
                      ytitle     = "Entries",
                      xmin       = 0.,
                      xmax       = 100.,
                     )

p_eff_pt  = Plot1D( pname               = "p_eff_pt",
                      leg_head          = "#varepsilon(p_{T})",
                      ratio_num         = "h_truth_fullsim_eff_track_pt", # give full eff for inefficiency ratio
                      hlist             = ["h_truth_fastsim_eff_track_pt","h_truth_fullsim_eff_track_pt",],
                      xtitle            = "p_{T}(#mu) [GeV]",
                      ytitle            = "Efficiency",
                      xmin              = 0.,
                      xmax              = 200.,
                      ymin              = 0.,
                      plot_ineff_ratio  = True,
                     )

p_eff_qinv2pt  = Plot1D( pname          = "p_eff_qinv2pt",
                      leg_head          = "#varepsilon(q/2p_{T})",
                      ratio_num         = "h_truth_fullsim_eff_track_qinv2pt", # give full eff for inefficiency ratio
                      hlist             = ["h_truth_fastsim_eff_track_qinv2pt","h_truth_fullsim_eff_track_qinv2pt",],
                      xtitle            = "q/2p_{T}(#mu) [GeV^{-1}]",
                      ytitle            = "Efficiency",
                      xmin              = -0.6,
                      xmax              = 0.6,
                      ymin              = 0.,
                      plot_ineff_ratio  = True,
                     )

p_eff_eta  = Plot1D( pname               = "p_eff_eta",
                      leg_head          = "#varepsilon(#eta)",
                      ratio_num         = "h_truth_fullsim_eff_track_eta", # give full eff for inefficiency ratio
                      hlist             = ["h_truth_fastsim_eff_track_eta","h_truth_fullsim_eff_track_eta",],
                      xtitle            = "#eta(#mu)",
                      ytitle            = "Efficiency",
                      xmin              = -2.5,
                      xmax              = 2.5,
                      ymin              = 0.,
                      plot_ineff_ratio  = True,
                     )

p_eff_phi  = Plot1D( pname               = "p_eff_phi",
                      leg_head          = "#varepsilon(#phi)",
                      ratio_num         = "h_truth_fullsim_eff_track_phi", # give full eff for inefficiency ratio
                      hlist             = ["h_truth_fastsim_eff_track_phi","h_truth_fullsim_eff_track_phi",],
                      xtitle            = "#phi(#mu)",
                      ytitle            = "Efficiency",
                      xmin              = -3.14,
                      xmax              = 3.14,
                      ymin              = 0.,
                      plot_ineff_ratio  = True,
                     )

p_eff_d0  = Plot1D( pname               = "p_eff_d0",
                      leg_head          = "#varepsilon(d_{0})",
                      ratio_num         = "h_truth_fullsim_eff_track_d0", # give full eff for inefficiency ratio
                      hlist             = ["h_truth_fastsim_eff_track_d0","h_truth_fullsim_eff_track_d0",],
                      xtitle            = "d_{0}(#mu) [mm]",
                      ytitle            = "Efficiency",
                      xmin              = -2.5,
                      xmax              = 2.5,
                      ymin              = 0.,
                      plot_ineff_ratio  = True,
                     )

p_eff_z0  = Plot1D( pname               = "p_eff_z0",
                      leg_head          = "#varepsilon(z_{0})",
                      ratio_num         = "h_truth_fullsim_eff_track_z0", # give full eff for inefficiency ratio
                      hlist             = ["h_truth_fastsim_eff_track_z0","h_truth_fullsim_eff_track_z0",],
                      xtitle            = "z_{0}(#mu) [mm]",
                      ytitle            = "Efficiency",
                      xmin              = -110.,
                      xmax              = 110.,
                      ymin              = 0.,
                      plot_ineff_ratio  = True,
                     )



# ---------------------
# inclusive resolutions
# ---------------------

p_track_delta_pt  = Plot1D( pname     = "p_track_delta_pt",
                      leg_head        = "Reso",
                      plot_stat       = True,
                      hlist           = ["h_fastsim_track_delta_pt","h_fullsim_track_delta_pt",],
                      xtitle          = "p_{T}(true) - p_{T}(reco)[GeV]",
                      ytitle          = "Entries",
                      xmin            = -0.5,
                      xmax            = 0.5,
                      compare_shapes  = True,
                      ratio_num       = "h_fastsim_track_delta_pt",
                     )

p_track_delta_qinv2pt  = Plot1D( pname  = "p_track_delta_qinv2pt",
                      leg_head          = "Reso",
                      plot_stat         = True,
                      hlist             = ["h_fastsim_track_delta_qinv2pt","h_fullsim_track_delta_qinv2pt",],
                      xtitle            = "q/2p_{T}(true) - q/2p_{T}(reco)[GeV^{-1}]",
                      ytitle            = "Entries",
                      xmin              = -0.08,
                      xmax              = 0.08,
                      compare_shapes    = True,
                      ratio_num         = "h_fastsim_track_delta_qinv2pt",
                     )

p_track_delta_eta  = Plot1D( pname    = "p_track_delta_eta",
                      leg_head        = "Reso",
                      plot_stat       = True,
                      hlist           = ["h_fastsim_track_delta_eta","h_fullsim_track_delta_eta",],
                      xtitle          = "#eta(true) - #eta(reco)",
                      ytitle          = "Entries",
                      xmin            = -0.03,
                      xmax            = 0.03,
                      compare_shapes  = True,
                      ratio_num       = "h_fastsim_track_delta_eta",
                     )

p_track_delta_phi  = Plot1D( pname    = "p_track_delta_phi",
                      leg_head        = "Reso",
                      plot_stat       = True,
                      hlist           = ["h_fastsim_track_delta_phi","h_fullsim_track_delta_phi",],
                      xtitle          = "#phi(true) - #phi(reco)",
                      ytitle          = "Entries",
                      xmin            = -0.03,
                      xmax            = 0.03,
                      compare_shapes  = True,
                      ratio_num       = "h_fastsim_track_delta_phi",
                     )

p_track_delta_d0  = Plot1D( pname     = "p_track_delta_d0",
                      leg_head        = "Reso",
                      plot_stat       = True,
                      hlist           = ["h_fastsim_track_delta_d0","h_fullsim_track_delta_d0",],
                      xtitle          = "d_{0}(true) - d_{0}(reco)[mm]",
                      ytitle          = "Entries",
                      xmin            = -1.2,
                      xmax            = 1.2,
                      compare_shapes  = True,
                      ratio_num       = "h_fastsim_track_delta_d0",
                     )

p_track_delta_z0  = Plot1D( pname    = "p_track_delta_z0",
                      leg_head       = "Reso",
                      plot_stat      = True,
                      hlist          = ["h_fastsim_track_delta_z0","h_fullsim_track_delta_z0",],
                      xtitle         = "z_{0}(true) - z_{0}(reco)[mm]",
                      ytitle         = "Entries",
                      xmin           = -10.,
                      xmax           = 10.,
                      compare_shapes = True,
                      ratio_num      = "h_fastsim_track_delta_z0",
                     )

p_track_delta_theta  = Plot1D( pname = "p_track_delta_theta",
                      leg_head       = "Reso",
                      plot_stat      = True,
                      hlist          = ["h_fastsim_track_delta_theta","h_fullsim_track_delta_theta",],
                      xtitle         = "#theta(true) - #theta(reco)",
                      ytitle         = "Entries",
                      xmin           = -0.007,
                      xmax           = 0.007,
                      compare_shapes = True,
                      ratio_num      = "h_fastsim_track_delta_theta",
                     )

p_track_delta_qop  = Plot1D( pname   = "p_track_delta_qop",
                      leg_head       = "Reso",
                      plot_stat      = True,
                      hlist          = ["h_fastsim_track_delta_qop","h_fullsim_track_delta_qop",],
                      xtitle         = "q/p(true) - q/p(reco)[GeV^{-1}]",
                      ytitle         = "Entries",
                      xmin           = -0.06,
                      xmax           = 0.06,
                      compare_shapes = True,
                      ratio_num      = "h_fastsim_track_delta_qop",
                     )



# -------------------
# profile resolutions
# -------------------

p_track_reso_qinv2pt_vs_truth_track_qinv2pt  = Plot1D( pname      = "p_track_reso_qinv2pt_vs_truth_track_qinv2pt",
                                              leg_head   = "Reso",
                                              #hlist      = ["h_fullsim_track_reso_qinv2pt_vs_truth_track_qinv2pt","h_fastsim_track_reso_qinv2pt_vs_truth_track_qinv2pt","h_offline_track_reso_qinv2pt_vs_truth_track_qinv2pt"],
                                              hlist      = ["h_fullsim_track_reso_qinv2pt_vs_truth_track_qinv2pt","h_fastsim_track_reso_qinv2pt_vs_truth_track_qinv2pt",],
                                              ratio_num  = "h_fastsim_track_reso_qinv2pt_vs_truth_track_qinv2pt",
                                              xtitle     = "q/2p_{T}(true) [GeV^{-1}]",
                                              ytitle     = "#sigma(q/2p_{T}(true) - q/2p_{T}(reco)) [GeV^{-1}]",
                                              xmin       = -0.7,
                                              xmax       = 0.7,
                                              ymin       = 0.,
                                              #ymax       = 0.3,
                                             )
p_track_reso_eta_vs_truth_track_qinv2pt  = Plot1D( pname = "p_track_reso_eta_vs_truth_track_qinv2pt",
                                              leg_head   = "Reso",
                                              #hlist      = ["h_fullsim_track_reso_eta_vs_truth_track_qinv2pt","h_fastsim_track_reso_eta_vs_truth_track_qinv2pt","h_offline_track_reso_eta_vs_truth_track_qinv2pt"],
                                              hlist      = ["h_fullsim_track_reso_eta_vs_truth_track_qinv2pt","h_fastsim_track_reso_eta_vs_truth_track_qinv2pt",],
                                              ratio_num  = "h_fastsim_track_reso_eta_vs_truth_track_qinv2pt",
                                              xtitle     = "q/2p_{T}(true) [GeV^{-1}]",
                                              ytitle     = "#sigma(#eta(true) - #eta(reco))",
                                              xmin       = -0.7,
                                              xmax       = 0.7,
                                              ymin       = 0.,
                                              #ymax       = 0.01,
                                             )
p_track_reso_phi_vs_truth_track_qinv2pt  = Plot1D( pname = "p_track_reso_phi_vs_truth_track_qinv2pt",
                                              leg_head   = "Reso",
                                              #hlist      = ["h_fullsim_track_reso_phi_vs_truth_track_qinv2pt","h_fastsim_track_reso_phi_vs_truth_track_qinv2pt","h_offline_track_reso_phi_vs_truth_track_qinv2pt"],
                                              hlist      = ["h_fullsim_track_reso_phi_vs_truth_track_qinv2pt","h_fastsim_track_reso_phi_vs_truth_track_qinv2pt",],
                                              ratio_num  = "h_fastsim_track_reso_phi_vs_truth_track_qinv2pt",
                                              xtitle     = "q/2p_{T}(true) [GeV^{-1}]",
                                              ytitle     = "#sigma(#phi(true) - #phi(reco))",
                                              xmin       = -0.7,
                                              xmax       = 0.7,
                                              ymin       = 0.,
                                              #ymax       = 0.008,
                                             )
p_track_reso_d0_vs_truth_track_qinv2pt  = Plot1D( pname  = "p_track_reso_d0_vs_truth_track_qinv2pt",
                                              leg_head   = "Reso",
                                              #hlist      = ["h_fullsim_track_reso_d0_vs_truth_track_qinv2pt","h_fastsim_track_reso_d0_vs_truth_track_qinv2pt","h_offline_track_reso_d0_vs_truth_track_qinv2pt"],
                                              hlist      = ["h_fullsim_track_reso_d0_vs_truth_track_qinv2pt","h_fastsim_track_reso_d0_vs_truth_track_qinv2pt",],
                                              ratio_num  = "h_fastsim_track_reso_d0_vs_truth_track_qinv2pt",
                                              xtitle     = "q/2p_{T}(true) [GeV^{-1}]",
                                              ytitle     = "#sigma(d_{0}(true) - d_{0}(reco)) [mm]",
                                              xmin       = -0.7,
                                              xmax       = 0.7,
                                              ymin       = 0.,
                                              #ymax       = 0.4,
                                             )
p_track_reso_z0_vs_truth_track_qinv2pt  = Plot1D( pname  = "p_track_reso_z0_vs_truth_track_qinv2pt",
                                              leg_head   = "Reso",
                                              #hlist      = ["h_fullsim_track_reso_z0_vs_truth_track_qinv2pt","h_fastsim_track_reso_z0_vs_truth_track_qinv2pt","h_offline_track_reso_z0_vs_truth_track_qinv2pt"],
                                              hlist      = ["h_fullsim_track_reso_z0_vs_truth_track_qinv2pt","h_fastsim_track_reso_z0_vs_truth_track_qinv2pt",],
                                              ratio_num  = "h_fastsim_track_reso_z0_vs_truth_track_qinv2pt",
                                              xtitle     = "q/2p_{T}(true) [GeV^{-1}]",
                                              ytitle     = "#sigma(z_{0}(true) - z_{0}(reco)) [mm]",
                                              xmin       = -0.7,
                                              xmax       = 0.7,
                                              ymin       = 0.0,
                                              #ymax       = 3.,
                                             )







p_track_reso_qinv2pt_vs_truth_track_eta  = Plot1D( pname      = "p_track_reso_qinv2pt_vs_truth_track_eta",
                                              leg_head   = "Reso",
                                              #hlist      = ["h_fullsim_track_reso_qinv2pt_vs_truth_track_eta","h_fastsim_track_reso_qinv2pt_vs_truth_track_eta","h_offline_track_reso_qinv2pt_vs_truth_track_eta"],
                                              hlist      = ["h_fullsim_track_reso_qinv2pt_vs_truth_track_eta","h_fastsim_track_reso_qinv2pt_vs_truth_track_eta",],
                                              ratio_num  = "h_fastsim_track_reso_qinv2pt_vs_truth_track_eta",
                                              xtitle     = "#eta(true)",
                                              ytitle     = "#sigma(q/2p_{T}(true) - q/2p_{T}(reco)) [GeV^{-1}]",
                                              xmin       = -3.,
                                              xmax       = 3.,
                                              ymin       = 0.,
                                              #ymax       = 0.3,
                                             )
p_track_reso_eta_vs_truth_track_eta  = Plot1D( pname = "p_track_reso_eta_vs_truth_track_eta",
                                              leg_head   = "Reso",
                                              #hlist      = ["h_fullsim_track_reso_eta_vs_truth_track_eta","h_fastsim_track_reso_eta_vs_truth_track_eta","h_offline_track_reso_eta_vs_truth_track_eta"],
                                              hlist      = ["h_fullsim_track_reso_eta_vs_truth_track_eta","h_fastsim_track_reso_eta_vs_truth_track_eta",],
                                              ratio_num  = "h_fastsim_track_reso_eta_vs_truth_track_eta",
                                              xtitle     = "#eta(true)",
                                              ytitle     = "#sigma(#eta(true) - #eta(reco))",
                                              xmin       = -3.,
                                              xmax       = 3.,
                                              ymin       = 0.,
                                              #ymax       = 0.01,
                                             )
p_track_reso_phi_vs_truth_track_eta  = Plot1D( pname = "p_track_reso_phi_vs_truth_track_eta",
                                              leg_head   = "Reso",
                                              #hlist      = ["h_fullsim_track_reso_phi_vs_truth_track_eta","h_fastsim_track_reso_phi_vs_truth_track_eta","h_offline_track_reso_phi_vs_truth_track_eta"],
                                              hlist      = ["h_fullsim_track_reso_phi_vs_truth_track_eta","h_fastsim_track_reso_phi_vs_truth_track_eta",],
                                              ratio_num  = "h_fastsim_track_reso_phi_vs_truth_track_eta",
                                              xtitle     = "#eta(true)",
                                              ytitle     = "#sigma(#phi(true) - #phi(reco))",
                                              xmin       = -3.,
                                              xmax       = 3.,
                                              ymin       = 0.,
                                              #ymax       = 0.008,
                                             )
p_track_reso_d0_vs_truth_track_eta  = Plot1D( pname  = "p_track_reso_d0_vs_truth_track_eta",
                                              leg_head   = "Reso",
                                              #hlist      = ["h_fullsim_track_reso_d0_vs_truth_track_eta","h_fastsim_track_reso_d0_vs_truth_track_eta","h_offline_track_reso_d0_vs_truth_track_eta"],
                                              hlist      = ["h_fullsim_track_reso_d0_vs_truth_track_eta","h_fastsim_track_reso_d0_vs_truth_track_eta"],
                                              ratio_num  = "h_fastsim_track_reso_d0_vs_truth_track_eta",
                                              xtitle     = "#eta(true)",
                                              ytitle     = "#sigma(d_{0}(true) - d_{0}(reco)) [mm]",
                                              xmin       = -3.,
                                              xmax       = 3.,
                                              ymin       = 0.,
                                              #ymax       = 0.4,
                                             )
p_track_reso_z0_vs_truth_track_eta  = Plot1D( pname  = "p_track_reso_z0_vs_truth_track_eta",
                                              leg_head   = "Reso",
                                              #hlist      = ["h_fullsim_track_reso_z0_vs_truth_track_eta","h_fastsim_track_reso_z0_vs_truth_track_eta","h_offline_track_reso_z0_vs_truth_track_eta"],
                                              hlist      = ["h_fullsim_track_reso_z0_vs_truth_track_eta","h_fastsim_track_reso_z0_vs_truth_track_eta",],
                                              ratio_num  = "h_fastsim_track_reso_z0_vs_truth_track_eta",
                                              xtitle     = "#eta(true)",
                                              ytitle     = "#sigma(z_{0}(true) - z_{0}(reco)) [mm]",
                                              xmin       = -3.,
                                              xmax       = 3.,
                                              ymin       = 0.0,
                                              #ymax       = 3.,
                                             )


plist = []
#plist.append(p_track_pt)
plist.append(p_eff_pt)
plist.append(p_eff_qinv2pt)
plist.append(p_eff_eta)
plist.append(p_eff_phi)
plist.append(p_eff_d0)
plist.append(p_eff_z0)

"""
# inclusive distributions
# -----------------------
#plist.append(p_track_delta_pt)
plist.append(p_track_delta_qinv2pt)
plist.append(p_track_delta_eta)
plist.append(p_track_delta_phi)
plist.append(p_track_delta_d0)
plist.append(p_track_delta_z0)
#plist.append(p_track_delta_theta)
#plist.append(p_track_delta_qop)

#plist.append(p_track_reso_pt_vs_truth_track_eta)
#plist.append(p_track_reso_pt_vs_truth_track_phi)

# profile resolutions
# -------------------
plist.append(p_track_reso_qinv2pt_vs_truth_track_qinv2pt)  
plist.append(p_track_reso_phi_vs_truth_track_qinv2pt)      
plist.append(p_track_reso_eta_vs_truth_track_qinv2pt)      
plist.append(p_track_reso_d0_vs_truth_track_qinv2pt)       
plist.append(p_track_reso_z0_vs_truth_track_qinv2pt)

plist.append(p_track_reso_qinv2pt_vs_truth_track_eta)      
plist.append(p_track_reso_phi_vs_truth_track_eta)          
plist.append(p_track_reso_eta_vs_truth_track_eta)          
plist.append(p_track_reso_d0_vs_truth_track_eta)           
plist.append(p_track_reso_z0_vs_truth_track_eta)           
"""
## EOF


