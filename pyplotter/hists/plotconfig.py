from plots import *
import ROOT

"""
This contains the plot configuration
"""


p_track_pt  = Plot1D( pname      = "p_track_pt",
                      leg_head   = "p_{T}",
                      plot_stat  = True,
                      hlist      = ["h_fastsim_track_pt","h_fullsim_track_pt","h_offline_track_pt"],
                      ratio_num  = "h_fastsim_track_pt",
                      xtitle     = "p_{T}(#mu) [GeV]",
                      ytitle     = "Entries",
                      xmin       = 0.,
                      xmax       = 50.,
                      ymin       = 0.,
                      ymax       = 3000.,
                     )


plist = []
plist.append(p_track_pt)


## EOF


