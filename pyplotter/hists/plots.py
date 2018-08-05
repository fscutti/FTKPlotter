# encoding: utf-8

'''
plot.py
description: plot class 
'''
#from numba import jit
import ROOT
import math

# - - - - - - - - - - - class defs  - - - - - - - - - - - - #
#------------------------------------------------------------
class Plot1D(object):
    '''
    class to hold 1D plot specs
    '''
    #________________________________________________________
    def __init__(self,
            pname            = None,
            xtitle           = None,
            ytitle           = None,
            hlist            = None,
            xmin             = None,
            xmax             = None,
            ymin             = 0.,
            ymax             = None,
            ratio_num        = None,
            ratio_den        = [],
            instance         = None,
            leg_head         = None,
            plot_stat        = False,
            draw_line        = False,
            compare_shapes   = False,
            outfile          = None,
            plot_ineff_ratio = False,
            **kw):

       self.pname            = pname
       self.xtitle           = xtitle
       self.ytitle           = ytitle
       self.hlist            = hlist
       self.xmin             = xmin
       self.xmax             = xmax
       self.ymin             = ymin
       self.ymax             = ymax
       self.ratio_num        = ratio_num
       self.ratio_den        = ratio_den
       self.instance         = instance
       self.leg_head         = leg_head
       self.plot_stat        = plot_stat
       self.draw_line        = draw_line
       self.compare_shapes   = compare_shapes
       self.outfile          = outfile
       self.plot_ineff_ratio = plot_ineff_ratio

       ## set additional key-word args
       # ----------------------------------------------------
       for k,w in kw.iteritems():
           setattr(self, k, w)
   
    #________________________________________________________
    def get_name(self):
       return self.__class__.__name__

    #________________________________________________________
    def set_den(self):
      
       self.ratio_den = []
       for h in self.hlist: 
         if h != self.ratio_num:
           self.ratio_den.append(h)
       return

    #________________________________________________________
    def get_hist(self,hname):
       """
       check that histograms on the store have been filled
       """
       assert hname in self.hstore.keys(), "ERROR: required hist %s not in store"%hname
       h = self.hstore[hname]
       if not h.instance: 
         h.create_hist(self.chain)
       return h

    #________________________________________________________
    def get_max(self,hname):
       """
       get maximum of histogram
       """
       maximum = 0.
       if hname in self.hlist:
         h = self.get_hist(hname)
         hmax = h.instance.Clone()
         if self.compare_shapes:
           hmax.Scale(1./hmax.Integral())
         maximum = max(maximum, hmax.GetMaximum())
       return maximum
    
    #________________________________________________________
    def get_plot(self):
      
      if self.ratio_num and not self.ratio_den: self.set_den()
      
      leg = ROOT.TLegend(0.5,0.9,0.9,1.0)
      leg.SetBorderSize(0)
      leg.SetFillColor(0)
      leg.SetFillStyle(0)
      leg.SetHeader(self.leg_head)

      if self.ratio_num: c = ROOT.TCanvas(self.pname,self.pname,750,800)
      else: c = ROOT.TCanvas(self.pname,self.pname,800,700)
      
      rsplit = 0.0
      if self.ratio_num: rsplit = 0.3
      
      pad1 = None
      pad2 = None 

      pad1 = ROOT.TPad("pad1","pad1",0.,rsplit,1.,1.)
      pad1.SetLeftMargin(0.15)
      pad1.SetTicky()
      pad1.SetTickx()
        
      if self.ratio_num: pad1.SetBottomMargin(0.04)
      else:              pad1.SetBottomMargin(0.15)

      pad1.Draw()
      
      if self.ratio_num:
        pad2 = ROOT.TPad("pad2","pad2",0,0,1,rsplit)
        pad2.SetTopMargin(0.04)
        pad2.SetBottomMargin(0.40)
        pad2.SetLeftMargin(0.15)
        pad2.SetTicky()
        pad2.SetTickx()
        pad2.SetGridy()
        pad2.Draw()
      
      pad1.cd()
      
      h_main_list = []      
      
      ymax = 0.0 
      
      for hname in self.hlist:
        hist = self.get_hist(hname)
        h_main_list.append(hist)
        
        ymax = max(ymax,self.get_max(hname)) 
      
      if not self.ymax:
        self.ymax = ymax * 1.2

      fr1 = pad1.DrawFrame(self.xmin,self.ymin,self.xmax,self.ymax,';%s;%s'%(self.xtitle,self.ytitle))
      if self.ratio_num:
        fr1.GetXaxis().SetTitleSize(0)
        fr1.GetXaxis().SetLabelSize(0)
       
      xaxis1 = fr1.GetXaxis()
      yaxis1 = fr1.GetYaxis()
      scale = (1.3+rsplit)
      
      if not self.ratio_num:
        xaxis1.SetTitleSize( xaxis1.GetTitleSize() * scale )
        xaxis1.SetLabelSize( 0.7 * xaxis1.GetLabelSize() * scale )
        xaxis1.SetTickLength( xaxis1.GetTickLength() * scale )
        xaxis1.SetTitleOffset( 1.3 * xaxis1.GetTitleOffset() / scale )
        xaxis1.SetLabelOffset( 1.0 * xaxis1.GetLabelOffset() / scale )
      
      yaxis1.SetTitleSize( yaxis1.GetTitleSize() * scale )
      yaxis1.SetTitleOffset( 2.1 * yaxis1.GetTitleOffset() / scale )
      yaxis1.SetLabelSize( 0.8 * yaxis1.GetLabelSize() * scale )
      yaxis1.SetLabelOffset( 1. * yaxis1.GetLabelOffset() / scale )
      xaxis1.SetNdivisions(510)
      yaxis1.SetNdivisions(510)
      
      
      for hist in h_main_list:
        opt = "E1"
        if self.draw_line: opt = "L"
        # this would be better cloned 
        # but it leads to plotting problems
        # only the last histogram is plotted
        h_plot = hist.instance
        if self.compare_shapes:
          h_plot.Scale(1./h_plot.Integral())
        h_plot.Draw("SAME,%s"%opt)
        
        stat_info = hist.leg_entry
        if self.plot_stat:
          mean = hist.instance.GetMean()
          sigma = hist.instance.GetStdDev()
          stat_info = ",".join([
            hist.leg_entry,
            "avg: %s"%float('%.2g' % mean),
            "RMS: %s"%float('%.2g' % sigma) 
            ])
        leg.AddEntry(hist.instance,stat_info, "PL")
       
      leg.Draw()
      
      pad1.RedrawAxis()

      if self.ratio_num:

        h_ratio_list = []
        
        ymax2 = 2.0

        for hr_name in self.ratio_den:
          h_ratio_num = self.get_hist(self.ratio_num).instance.Clone()
          h_ratio_den = self.get_hist(hr_name).instance.Clone()
          
          if self.compare_shapes:
            h_ratio_num.Scale(1./h_ratio_num.Integral())
            h_ratio_den.Scale(1./h_ratio_den.Integral())
         
          h_ratio = h_ratio_num
          h_ratio.Divide(h_ratio_den)


          if "line_style" in self.get_hist(hr_name).style_dict.keys():
            h_ratio.SetLineStyle(self.get_hist(hr_name).style_dict["line_style"])
          if "line_color" in self.get_hist(hr_name).style_dict.keys():
            h_ratio.SetLineColor(self.get_hist(hr_name).style_dict["line_color"])
          if "line_width" in self.get_hist(hr_name).style_dict.keys():
            h_ratio.SetLineWidth(self.get_hist(hr_name).style_dict["line_width"])
          
          if "marker_style" in self.get_hist(hr_name).style_dict.keys():
            h_ratio.SetMarkerStyle(self.get_hist(hr_name).style_dict["marker_style"])
          if "marker_color" in self.get_hist(hr_name).style_dict.keys():
            h_ratio.SetMarkerColor(self.get_hist(hr_name).style_dict["marker_color"])
          if "marker_size" in self.get_hist(hr_name).style_dict.keys():
            h_ratio.SetMarkerSize(self.get_hist(hr_name).style_dict["marker_size"])

          h_ratio.SetNameTitle('%s_div_%s'%(self.get_hist(self.ratio_num).hname,self.get_hist(hr_name).hname),'%s_div_%s'%(self.get_hist(self.ratio_num).hname,self.get_hist(hr_name).hname)) 
          
          ymax2 = min(max(ymax2,h_ratio.GetMaximum()),12.)

          h_ratio_list.append(h_ratio)

        pad2.cd()
        den_title = self.get_hist(self.ratio_den[0]).leg_entry
        
        framey_max = 1.6
        framey_min = 0.4
        if len(self.ratio_den)>1:den_title = "X"
        
        if self.plot_ineff_ratio:
          framey_max = framey_max / 12.
          framey_min = 0.0

        fr2 = pad2.DrawFrame(self.xmin,framey_min,self.xmax,framey_max,';%s;%s / %s'%(self.xtitle, self.get_hist(self.ratio_num).leg_entry, den_title ))
        xaxis2 = fr2.GetXaxis()
        yaxis2 = fr2.GetYaxis()
        scale = (1. / rsplit)
        yaxis2.SetTitleSize(0.7 * yaxis2.GetTitleSize() * scale )
        
        if self.plot_ineff_ratio:
          yaxis2.SetLabelSize( yaxis2.GetLabelSize() * scale * 0.5 )
        else:
          yaxis2.SetLabelSize( yaxis2.GetLabelSize() * scale  )
        yaxis2.SetTitleOffset( 2.2 * yaxis2.GetTitleOffset() / scale  )
        yaxis2.SetLabelOffset(0.4 * yaxis2.GetLabelOffset() * scale )
        xaxis2.SetTitleSize( xaxis2.GetTitleSize() * scale )
        xaxis2.SetLabelSize( 0.8 * xaxis2.GetLabelSize() * scale )
        xaxis2.SetTickLength( xaxis2.GetTickLength() * scale )
        xaxis2.SetTitleOffset( 3.2* xaxis2.GetTitleOffset() / scale  )
        xaxis2.SetLabelOffset( 2.5* xaxis2.GetLabelOffset() / scale )
        yaxis2.SetNdivisions(510)
        xaxis2.SetNdivisions(508)
        
        for hr in h_ratio_list: 
          if self.plot_ineff_ratio:
            for ib in xrange(hr.GetNbinsX()):
              hr.SetBinContent(ib, 1.-hr.GetBinContent(ib))
          hr.Draw("SAME,E1")
        
        pad2.RedrawAxis()
       
      c.SaveAs(c.GetName()+".eps")
      c.Close()

      for hist in h_main_list:
        if hist.slices:
          for ibin,bin_dict in hist.slices.iteritems():
            if len(bin_dict["entries"]):

               c_ibin = ROOT.TCanvas("c_"+bin_dict["h_slice"].GetName(),"c_"+bin_dict["h_slice"].GetName(),800,800)
               c_ibin.SetTickx()
               c_ibin.SetTicky()
               c_ibin.cd()
               bin_dict["h_slice"].Draw("HIST")
               bin_dict["slice_fit"].Draw("SAME")
               c_ibin.SaveAs("./slices/"+c_ibin.GetName()+".eps")
               c_ibin.Close()

      return 

#------------------------------------------------------------
class Plot2D(object):
    '''
    class to hold 2D plot specs
    '''
    #________________________________________________________
    def __init__(self,
            pname            = None,
            xtitle           = None,
            ytitle           = None,
            xmin             = None,
            xmax             = None,
            ymin             = None,
            ymax             = None,
            hist_num         = None,
            hist_den         = None,
            instance         = None,
            leg_head         = None,
            plot_stat        = False,
            draw_line        = False,
            outfile          = None,
            plot_ineff_ratio = False,
            **kw):

       self.pname            = pname
       self.xtitle           = xtitle
       self.ytitle           = ytitle
       self.xmin             = xmin
       self.xmax             = xmax
       self.ymin             = ymin
       self.ymax             = ymax
       self.hist_num         = hist_num
       self.hist_den         = hist_den
       self.instance         = instance
       self.leg_head         = leg_head
       self.plot_stat        = plot_stat
       self.draw_line        = draw_line
       self.outfile          = outfile
       self.plot_ineff_ratio = plot_ineff_ratio

       ## set additional key-word args
       # ----------------------------------------------------
       for k,w in kw.iteritems():
           setattr(self, k, w)
   
    #________________________________________________________
    def get_name(self):
       return self.__class__.__name__

    #________________________________________________________
    def get_hist(self,hname):
       """
       check that histograms on the store have been filled
       """
       assert hname in self.hstore.keys(), "ERROR: required hist %s not in store"%hname
       h = self.hstore[hname]
       if not h.instance: 
         h.create_hist(self.chain)
       return h
    
    #________________________________________________________
    def get_plot(self):
      
      leg = ROOT.TLegend(0.5,0.9,0.9,1.0)
      leg.SetBorderSize(0)
      leg.SetFillColor(0)
      leg.SetFillStyle(0)
      leg.SetHeader(self.leg_head)

      c = ROOT.TCanvas(self.pname,self.pname,800,700)
      
      pad = ROOT.TPad("pad","pad",0.,0.,1.,1.)
      pad.SetLeftMargin(0.15)
      pad.SetTicky()
      pad.SetTickx()
      pad.SetBottomMargin(0.15)
      
      pad.Draw()
      pad.cd()
      
      hist_num = self.get_hist(self.hist_num).instance.Clone()
      hist_den = None
      hist_ratio = None

      if self.hist_den:
        hist_den = self.get_hist(self.hist_den).instance.Clone()
        
        hist_ratio = hist_num.Clone()
        hist_ratio.SetNameTitle('%s_div_%s'%(hist_num.GetName(),hist_den.GetName()),'%s_div_%s'%(hist_num.GetName(),hist_den.GetName())) 
        hist_ratio.Divide(hist_den)
        
        if self.plot_ineff_ratio:
          for ibx in xrange(hist_num.GetNbinsX()):
            for iby in xrange(hist_den.GetNbinsY()):
              hist_ratio.SetBinContent(ibx,iby, 1.-hist_ratio.GetBinContent(ibx,iby))
        
        hist_ratio.SetStats(False)
        hist_ratio.Draw("SAME,colz")

      else:
        hist_num.SetStats(False)
        hist_num.Draw("SAME,colz")

      
      stat_info = self.get_hist(self.hist_num).leg_entry
      if self.plot_stat: 
        """
        mean = hist.instance.GetMean()
        sigma = hist.instance.GetStdDev()
        stat_info = ",".join([
          hist.leg_entry,
          "avg: %s"%float('%.2g' % mean),
          "RMS: %s"%float('%.2g' % sigma) 
          ])
        """
        pass
      
      #leg.AddEntry(hist.instance,stat_info, "PL")
      #leg.Draw()
      pad.RedrawAxis()

      c.SaveAs(c.GetName()+".root")
      c.Close()

      return 

## EOF

