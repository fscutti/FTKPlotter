import os 
import ROOT
from hists.histconfig import hlist
from hists.plotconfig import plist

inpath  = "/home/fscutti/FTKPlotter/run/testDir"
infile  = "hist-user.fscutti.26Nov11_EXT0.root"
outfile = "test.root"

chain = ROOT.TChain("tracks")
chain.Add(os.path.join(inpath,infile))

ROOT.gROOT.SetBatch(True)

hstore = {}

# declare a hstore container which keeps all histograms
for h in hlist:
  h.create_hist()
  hstore[h.hname] = h


nentries = chain.GetEntries()
for i in xrange(nentries):
  chain.GetEntry(i+1)
  
  for h in hlist:
    exec("passed = "+h.condition)                
    
    # fill flat variables
    # -------------------
    if passed and h.var_fill:                    
      exec("var = "+h.var_fill)                  
      h.instance.Fill(var)                       
    
    # fill vector variables
    # ---------------------
    elif passed and h.vec_fill:                       
      exec("size = "+h.vec_fill+".size()")       
      for i in xrange(size):                        
        exec("vec_i = "+h.vec_fill+".at(%d)"%i)  
        h.instance.Fill(vec_i)

#for h in hlist:
#  h.instance.Print("all")

outf =  ROOT.TFile.Open(outfile,"RECREATE")


for p in plist:
  p.hstore = hstore
  p.get_plot()




#for hname, hroot in hstore.iteritems():
#  hroot.Print("all")
#  hroot.Write(hname)

outf.Close()



