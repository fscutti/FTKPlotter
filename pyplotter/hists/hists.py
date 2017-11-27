# encoding: utf-8

'''
hist.py
description: histogram class 
'''

import ROOT

# - - - - - - - - - - - class defs  - - - - - - - - - - - - #
#------------------------------------------------------------
class Hist1D(object):
    '''
    class to hold histogram info for plotting
    one-dimensional histograms
    '''
    #________________________________________________________
    def __init__(self,
            hname     = None,
            xtitle    = None,
            ytitle    = None,
            nbins     = None,
            xmin      = None,
            xmax      = None,
            var_fill  = None,
            vec_fill  = None,
            instance  = None,
            condition = "True",
            **kw):

       self.hname     = hname
       self.xtitle    = xtitle
       self.ytitle    = ytitle
       self.nbins     = nbins
       self.xmin      = xmin
       self.xmax      = xmax
       self.var_fill  = var_fill
       self.vec_fill  = vec_fill
       self.instance  = instance
       self.condition = condition

       ## set additional key-word args
       # ----------------------------------------------------
       for k,w in kw.iteritems():
           setattr(self, k, w)

    #________________________________________________________
    def get_name(self):
       return self.__class__.__name__

    #________________________________________________________
    def create_hist(self):
       self.instance = ROOT.TH1F(self.hname,self.hname, self.nbins, self.xmin, self.xmax)
       assert self.instance, "ERROR: histogram % not initialised!!!" % self.hname
       self.instance.GetXaxis().SetTitle(self.xtitle)
       self.instance.GetYaxis().SetTitle(self.ytitle)
       return self.instance




#------------------------------------------------------------
class Hist2D(object):
    '''
    class to hold histogram info for plotting
    two-dimensional histograms
    '''
    #________________________________________________________
    def __init__(self,
            hname    = None,
            xtitle   = None,
            ytitle   = None,
            nbinsx   = None,
            nbinsy   = None,
            xmin     = None,
            xmax     = None,
            ymin     = None,
            ymax     = None,
            vexpr    = None,
            **kw):

       self.hname    = hname
       self.xtitle   = xtitle
       self.ytitle   = ytitle
       self.nbinsx   = nbinsx
       self.nbinsy   = nbinsy
       self.xmin     = xmin
       self.xmax     = xmax
       self.ymin     = ymin
       self.ymax     = ymax
       self.vexpr    = vexpr

       ## set additional key-word args
       # -------------------------------------------------------
       for k,w in kw.iteritems():
           setattr(self, k, w)

    #________________________________________________________
    def get_name(self):
      return self.__class__.__name__



## EOF





