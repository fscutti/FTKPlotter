import os 
import ROOT

import time
start_time = time.time()

from hists.histconfig import hlist
from hists.plotconfig import plist

# full stat correct smearing, debugged sigma inv pt
inpath  = "/home/fscutti/FTKPlotter/run/testDir12Apr"
infile  = "hist-output_12Apr.root"

# full stat
#inpath  = "/home/fscutti/FTKPlotter/run/testDir5Dec"
#infile  = "hist-output_5Dec.root"

# full stat alt smearing
#inpath  = "/home/fscutti/FTKPlotter/run/testDir11Dec"
#infile  = "hist-output_11Dec.root"

# old original run
#inpath  = "/home/fscutti/FTKPlotter/run/testOld"
#infile  = "hist-OldInputDAOD.root"

# subsample
#inpath  = "/home/fscutti/FTKPlotter/run/testDir29Nov"
#infile  = "hist-user.fscutti.26Nov11_EXT0.root"

#outfile = "test.root"

chain = ROOT.TChain("tracks")
chain.Add(os.path.join(inpath,infile))

ROOT.gROOT.SetBatch(True)
ROOT.gStyle.SetOptStat(1111)
ROOT.gStyle.SetOptFit(1111)

hstore = {}

# declare a hstore container which keeps all histograms
for h in hlist: hstore[h.hname] = h


#outplots =  ROOT.TFile.Open(outfile,"RECREATE")
for p in plist:
  p.hstore = hstore
  p.chain  = chain
  p.get_plot()
  #plot.Write(plot.GetName())
  #plot.SaveAs(plot.GetName()+".eps")
#outplots.Close()

print "Finished running in ", time.time() - start_time

