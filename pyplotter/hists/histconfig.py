from hists import *

"""
This contains the histogram configuration
"""


# ---------------
# fast simulation
# ---------------
h_fastsim_track_pt  = Hist1D( hname     = "h_fastsim_track_pt",
                              xtitle    = "p_{T}(#mu_{fast}) [GeV]",
                              ytitle    = "Entries",
                              nbins     = 500,
                              xmin      = 0.,
                              xmax      = 500.,
                              vec_fill  = "chain.fastsim_track_pt",
                              condition = "chain.fastsim_track_pt.size()>0",
                             )


hlist = []
hlist.append(h_fastsim_track_pt)


## EOF


