from hists import *
import ROOT

"""
This contains the histogram configuration
"""

basic_style = {"marker_style" : 20, "marker_size":0,}

fastsim_style = {"line_color" : ROOT.kRed, "line_width" : 2, "marker_color" : ROOT.kRed}
fastsim_style.update(basic_style)
fullsim_style = {"line_color" : ROOT.kBlue, "line_width" : 2,"marker_color" : ROOT.kBlue}
fullsim_style.update(basic_style)
offline_style = {"line_color" : ROOT.kGreen, "line_width" : 2,"marker_color" : ROOT.kGreen}
offline_style.update(basic_style)

# ---------------
# fast simulation
# ---------------

h_fastsim_track_pt  = Hist1D( hname      = "h_fastsim_track_pt",
                              leg_entry  = "FastSim",
                              xtitle     = "p_{T}(#mu) [GeV]",
                              ytitle     = "Entries",
                              nbins      = 50,
                              xmin       = 0.,
                              xmax       = 100.,
                              vec_fill   = "chain.fastsim_track_pt",
                              condition  = "chain.fastsim_track_pt.size()>0",
                              style_dict = fastsim_style,
                             )

# ---------------
# full simulation
# ---------------

h_fullsim_track_pt  = Hist1D( hname      = "h_fullsim_track_pt",
                              leg_entry  = "FullSim",
                              xtitle     = "p_{T}(#mu) [GeV]",
                              ytitle     = "Entries",
                              nbins      = 50,
                              xmin       = 0.,
                              xmax       = 100.,
                              vec_fill   = "chain.fullsim_track_pt",
                              condition  = "chain.fullsim_track_pt.size()>0",
                              style_dict = fullsim_style,
                             )

# ------------------
# offline simulation
# ------------------

h_offline_track_pt  = Hist1D( hname      = "h_offline_track_pt",
                              leg_entry  = "Offline",
                              xtitle     = "p_{T}(#mu) [GeV]",
                              ytitle     = "Entries",
                              nbins      = 50,
                              xmin       = 0.,
                              xmax       = 100.,
                              vec_fill   = "chain.offline_track_pt",
                              condition  = "chain.offline_track_pt.size()>0",
                              style_dict = offline_style,
                             )

hlist = []
hlist.append(h_fastsim_track_pt)
hlist.append(h_fullsim_track_pt)
hlist.append(h_offline_track_pt)


## EOF


