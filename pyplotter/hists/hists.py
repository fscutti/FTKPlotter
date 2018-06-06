# encoding: utf-8

'''
hist.py
description: histogram class 
'''
"""
from numba import jit, jitclass, njit      # import the decorators
from numba import int32, float32    # import the types

spec = [
    ('value', int32),               # a simple scalar field
    ('array', float32[:]),          # an array field
]
"""
import ROOT
from math import sqrt
from numba import jit

#________________________________________________________
@jit
def _get_moments(data,moment):

    N = len(data)
    if N == 0: 
      #print "No events"
      return 0

    mean = sigma = rms = sigsigma = 0

    for i in data: 
      mean += i
    mean /= N

    if moment=="mean": return mean
    
    for i in data: 
      sigma += pow(i-mean,2)
      rms += pow(i,2)
    
    sigma = sqrt( sigma / (N-1) )
    rms = sqrt(rms/N) # this is the default error in a Projection
    sig_rms = rms / sqrt(N)
   
    if moment=="rms": return rms
    if moment=="sig_rms": return sig_rms
    if moment=="sigma": return sigma
    
    if moment=="sigsigma":
      sigsigma = 2 * pow(sigma,4) / (N-1)
      return sqrt(sigsigma)


# - - - - - - - - - - - class defs  - - - - - - - - - - - - #
#------------------------------------------------------------
class Hist(object):
    '''
    class to hold histogram info for plotting
    one-dimensional histograms
    '''
    #________________________________________________________
    def __init__(self,
            hname          = None,
            leg_entry      = None,
            xtitle         = None,
            ytitle         = None,
            nbins          = None,
            xmin           = None,
            xmax           = None,
            ymin           = None,
            ymax           = None,
            fitmin         = None,
            fitmax         = None,
            var_fill       = None,
            vec_fill       = None,
            instance       = None,
            selection      = "",
            num_selection  = "",
            style_dict     = None,
            chain          = None,
            is_profile     = False,
            use_roostat    = False,
            use_fit        = True,
            get_slices     = False,
            slices         = None,
            **kw):

       self.hname          = hname
       self.leg_entry      = leg_entry
       self.xtitle         = xtitle
       self.ytitle         = ytitle
       self.nbins          = nbins
       self.xmin           = xmin
       self.xmax           = xmax
       self.ymin           = ymin
       self.ymax           = ymax
       self.fitmin         = fitmin
       self.fitmax         = fitmax
       self.var_fill       = var_fill
       self.vec_fill       = vec_fill
       self.instance       = instance
       self.selection      = selection
       self.num_selection  = num_selection
       self.style_dict     = style_dict
       self.chain          = chain
       self.is_profile     = is_profile
       self.use_roostat    = use_roostat
       self.use_fit        = use_fit
       self.get_slices     = get_slices
       self.slices         = slices

       ## set additional key-word args
       # ----------------------------------------------------
       for k,w in kw.iteritems():
           setattr(self, k, w)

    #________________________________________________________
    def get_name(self,chain=None):
       return self.__class__.__name__

    #________________________________________________________
    def set_style(self,h=None):
       """
       set style of histogram
       """

       h.GetXaxis().SetTitle(self.xtitle)
       h.GetYaxis().SetTitle(self.ytitle)

       if self.style_dict:
         for k,v in self.style_dict.iteritems():
           if k=="line_style": h.SetLineStyle(self.style_dict[k])
           if k=="line_color": h.SetLineColor(self.style_dict[k])
           if k=="line_width": h.SetLineWidth(self.style_dict[k])

           if k=="marker_style": h.SetMarkerStyle(self.style_dict[k])
           if k=="marker_color": h.SetMarkerColor(self.style_dict[k])
           if k=="marker_size": h.SetMarkerSize(self.style_dict[k])

       return h


    #________________________________________________________
    def build_data_dict(self,h=None):
       bin_dict = {}
       for ibin in xrange(1,h.GetNbinsX()+1):
         bin_dict[ibin] = {"lowedge":0., "hiedge":0., "entries":[], "content":0., "error":0., "mean":0., "RMS":0., "RMSError":0.}         
         bin_dict[ibin]["lowedge"]  = h.GetBinLowEdge(ibin)
         bin_dict[ibin]["hiedge"]   = h.GetBinLowEdge(ibin) + h.GetBinWidth(ibin)
         bin_dict[ibin]["content"]  = h.GetBinContent(ibin)
         bin_dict[ibin]["error"]    = h.GetBinError(ibin)
         h_name = h.GetName()+"_slice_%s_%s"%(bin_dict[ibin]["lowedge"],bin_dict[ibin]["hiedge"])
         # just a dummy hist
         bin_dict[ibin]["h_slice"]  = ROOT.TH1D(h_name,h_name, 4, -1.,1. )
         bin_dict[ibin]["h_slice"].GetXaxis().SetTitle(self.ytitle)
         bin_dict[ibin]["h_slice"].GetYaxis().SetTitle("Entries")
         bin_dict[ibin]["h_slice"].GetYaxis().SetTitleOffset(1.3)
         bin_dict[ibin]["h_slice"].Sumw2()

       return bin_dict


    #________________________________________________________
    def get_moments(self,data,moment):
        return _get_moments(data,moment)

    #________________________________________________________
    def create_hist(self,chain=None):
       if chain: self.chain=chain
       assert self.chain,    "ERROR: chain not initialised for %s"%self.hname

       if self.is_profile:
          #h_prof = ROOT.TProfile(self.hname,self.hname, self.nbins, self.xmin, self.xmax, self.ymin, self.ymax)
          h_prof = ROOT.TProfile(self.hname,self.hname, self.nbins, self.xmin, self.xmax)
          if self.use_roostat:
            self.chain.Draw(self.var_fill_y+":"+self.var_fill_x+">>"+self.hname,self.selection,"prof")
           
          h = h_prof.ProjectionX()
          
          if self.use_roostat:          
               """
               Use ROOT facilities to compute moments
               """
               for ibin in xrange(1,h.GetNbinsX()+1):
                 h.SetBinContent(ibin,h.GetBinError(ibin)) 
                 h.SetBinError(ibin,10e-10) 
          
          if not self.use_roostat: 
               """
               Compute moments by hand
               """
               ddict =  self.build_data_dict(h)
               
               nentries = self.chain.GetEntries() 
               for i in xrange(nentries):
                 self.chain.GetEntry(i+1)
                 for s in xrange(getattr(self.chain,self.var_fill_x).size()):
                   ibin = h.FindBin(getattr(self.chain,self.var_fill_x).at(s))   
                   ddict[ibin]["entries"].append(getattr(self.chain,self.var_fill_y).at(s))
                   #ddict[ibin]["h_slice"].Fill(getattr(self.chain,self.var_fill_y).at(s))

               outfile = None
               #if self.get_slices:
               #  outfile = ROOT.TFile.Open("fits_"+self.hname+".root","RECREATE")
               
               for ibin in xrange(1,h.GetNbinsX()+1):
                 if len(ddict[ibin]["entries"]):

                   fit_range = []
                   hist_range = []

                   if not self.ymin or not self.ymax:
                     pass
                     
                     #fit_range = [-0.15*ibin_sigma,0.15*ibin_sigma]
                     #hist_range = [-1.5*ibin_sigma,1.5*ibin_sigma]
                     
                     #fit_range = [-3.*ibin_mean,3.*ibin_mean]
                     #hist_range = [-6.*ibin_mean,6.*ibin_mean]
                   else:
                     hist_range = [self.ymin, self.ymax]
                   
                   # fill the slices
                   ddict[ibin]["h_slice"].SetBins(70,min(hist_range),max(hist_range))
                   for i in ddict[ibin]["entries"]: ddict[ibin]["h_slice"].Fill(i)
                   
                   if self.use_fit:

                       """
                       Perform a gaussian fit to get the resolution
                       """

                       if not self.fitmin or not self.fitmax:
                         fit_range = [0.1*self.ymin, 0.1*self.ymax]
                       else:
                         fit_range = [self.fitmin, self.fitmax]
                       
                       f_ibin = ROOT.TF1("f_ibin_%s"%ibin,"gaus", min(fit_range), max(fit_range));
                       ddict[ibin]["h_slice"].Fit(f_ibin,"R")
                       
                       if self.get_slices:
                         ddict[ibin]["slice_fit"] = f_ibin
                         self.slices = ddict
                       
                       h.SetBinContent(ibin,f_ibin.GetParameter(2))
                       h.SetBinError(ibin,f_ibin.GetParError(2)) 
                   
                   else:
                        
                       """
                       Compute the moments by hand for each slice
                       """
                       # use user defined moments        
                       # ------------------------
                       #ibin_mean = self.get_moments(ddict[ibin]["entries"],"mean")
                       #ibin_rms = self.get_moments(ddict[ibin]["entries"],"rms")
                       #ibin_sigrms = self.get_moments(ddict[ibin]["entries"],"sig_rms")
                       ibin_sigma = self.get_moments(ddict[ibin]["entries"],"sigma")
                       ibin_sigsigma = self.get_moments(ddict[ibin]["entries"],"sigsigma")
                       
                       # use root moments
                       # ------------------------
                       #ibin_sigma = ddict[ibin]["h_slice"].GetStdDev()
                       #ibin_sigsigma = ddict[ibin]["h_slice"].GetStdDevError()


                       h.SetBinContent(ibin,ibin_sigma)
                       h.SetBinError(ibin,ibin_sigsigma) 
          
          self.instance = self.set_style(h)
       
       else:
          h = ROOT.TH1D(self.hname,self.hname, self.nbins, self.xmin, self.xmax)
          h.Sumw2()
          assert h, "ERROR: histogram % not initialised!!!" % self.hname
          
          if self.num_selection:
           
           if self.selection: 
             self.num_selection = " && ".join([self.num_selection,self.selection])
           
           h_num = ROOT.TH1D(self.hname+"_num",self.hname+"_num", self.nbins, self.xmin, self.xmax)
           h_num.Sumw2()
           self.chain.Draw(self.var_fill+">>"+self.hname+"_num",self.num_selection)
           
           h_den = ROOT.TH1D(self.hname+"_den",self.hname+"_den", self.nbins, self.xmin, self.xmax)
           h_den.Sumw2()
           self.chain.Draw(self.var_fill+">>"+self.hname+"_den",self.selection)
          
           h.Divide(h_num,h_den,1.,1.,"b")
         
          else: 
            
            """ 
            mean = 0.
            n = 1.
            
            nentries = self.chain.GetEntries() 
            for i in xrange(nentries):
              self.chain.GetEntry(i+1)
              for s in xrange(getattr(self.chain,self.var_fill).size()):
                h.Fill(getattr(self.chain,self.var_fill).at(s))
                mean += getattr(self.chain,self.var_fill).at(s)
                n += 1
            print "hist: ", self.hname, " mean: ", mean/n
            """ 
             
            self.chain.Draw(self.var_fill+">>"+self.hname,self.selection)
          
          self.instance = self.set_style(h)
          #self.instance.Print("all")
       return self.instance


## EOF





