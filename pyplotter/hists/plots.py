# encoding: utf-8

'''
plot.py
description: plot class 
'''

import ROOT

# - - - - - - - - - - - class defs  - - - - - - - - - - - - #
#------------------------------------------------------------
class Plot1D(object):
    '''
    class to hold plot specs
    '''
    #________________________________________________________
    def __init__(self,
            pname      = None,
            xtitle     = None,
            ytitle     = None,
            hlist      = None,
            xmin       = None,
            xmax       = None,
            ymin       = None,
            ymax       = None,
            ratio_num  = None,
            ratio_den  = None,
            instance   = None,
            leg_head   = None,
            plot_stat  = None,
            **kw):

       self.pname      = pname
       self.xtitle     = xtitle
       self.ytitle     = ytitle
       self.hlist      = hlist
       self.xmin       = xmin
       self.xmax       = xmax
       self.ymin       = ymin
       self.ymax       = ymax
       self.ratio_num  = ratio_num
       self.ratio_den  = ratio_den
       self.instance   = instance
       self.leg_head   = leg_head
       self.plot_stat  = plot_stat

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
    def get_plot(self):
      
      if self.ratio_num and not self.ratio_den: self.set_den()

      nLegend = len([self.ratio_num]+self.ratio_den) + 1
      x_legend    = 0.5
      x_leg_shift = -0.055
      y_leg_shift = 0.0
      legYCompr   = 8.0
      legYMax     = 0.85
      legYMin     = legYMax - (legYMax - (0.55 + y_leg_shift)) / legYCompr * nLegend
      legXMin     = x_legend + x_leg_shift
      legXMax     = legXMin + 0.4
      
      ## create legend (could use metaroot functionality?)
      if not self.ratio_num:
        legXMin -= 0.005
        legXMax -= 0.058
      leg = ROOT.TLegend(legXMin,legYMin,legXMax,legYMax)
      leg.SetBorderSize(0)
      leg.SetFillColor(0)
      leg.SetFillStyle(0)
      leg.SetHeader(self.leg_head)

      cname = "c_%s"%self.pname
      if self.ratio_num: c = ROOT.TCanvas(cname,cname,750,800)
      else: c = ROOT.TCanvas(cname,cname,800,700)
      
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

      fr1 = pad1.DrawFrame(self.xmin,self.ymin,self.xmax,self.ymax,';%s;%s'%(self.xtitle,self.ytitle))
      if self.ratio_num:
        fr1.GetXaxis().SetTitleSize(0)
        fr1.GetXaxis().SetLabelSize(0)
       
      xaxis1 = fr1.GetXaxis()
      yaxis1 = fr1.GetYaxis()
      scale = (1.3+rsplit)
      
      if not self.ratio_num:
        xaxis1.SetTitleSize( xaxis1.GetTitleSize() * scale )
        xaxis1.SetLabelSize( 0.9 * xaxis1.GetLabelSize() * scale )
        xaxis1.SetTickLength( xaxis1.GetTickLength() * scale )
        xaxis1.SetTitleOffset( 1.3 * xaxis1.GetTitleOffset() / scale )
        xaxis1.SetLabelOffset( 1.0 * xaxis1.GetLabelOffset() / scale )
      
      yaxis1.SetTitleSize( yaxis1.GetTitleSize() * scale )
      yaxis1.SetTitleOffset( 2.1 * yaxis1.GetTitleOffset() / scale )
      yaxis1.SetLabelSize( 0.8 * yaxis1.GetLabelSize() * scale )
      yaxis1.SetLabelOffset( 1. * yaxis1.GetLabelOffset() / scale )
      xaxis1.SetNdivisions(510)
      yaxis1.SetNdivisions(510)
      
      pad1.cd()
      
      for hname,hist in self.hstore.iteritems():
        hist.instance.Draw("SAME,E1")
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
        pad2.cd()
        den_title = self.hstore[self.ratio_den[0]].leg_entry
        if len(self.ratio_den)>1:den_title = "X"
        fr2 = pad2.DrawFrame(self.xmin,0.49,self.xmax,1.51,';%s;%s / %s'%(self.xtitle, self.hstore[self.ratio_num].leg_entry, den_title ))
        xaxis2 = fr2.GetXaxis()
        yaxis2 = fr2.GetYaxis()
        scale = (1. / rsplit)
        yaxis2.SetTitleSize(0.7 * yaxis2.GetTitleSize() * scale )
        
        yaxis2.SetLabelSize( yaxis2.GetLabelSize() * scale )
        yaxis2.SetTitleOffset( 0.7 * yaxis2.GetTitleOffset() / scale  )
        yaxis2.SetLabelOffset(0.4 * yaxis2.GetLabelOffset() * scale )
        xaxis2.SetTitleSize( xaxis2.GetTitleSize() * scale )
        xaxis2.SetLabelSize( 0.8 * xaxis2.GetLabelSize() * scale )
        xaxis2.SetTickLength( xaxis2.GetTickLength() * scale )
        xaxis2.SetTitleOffset( 3.2* xaxis2.GetTitleOffset() / scale  )
        xaxis2.SetLabelOffset( 2.5* xaxis2.GetLabelOffset() / scale )
        yaxis2.SetNdivisions(510)
        xaxis2.SetNdivisions(510)
        
        h_ratio_list = []
        
        for hr_name in self.ratio_den:
          h_ratio = self.hstore[self.ratio_num].instance.Clone()
          h_ratio.Divide(self.hstore[hr_name].instance)
          
          if "line_style" in self.hstore[hr_name].style_dict.keys():
            h_ratio.SetLineStyle(self.hstore[hr_name].style_dict["line_style"])
          if "line_color" in self.hstore[hr_name].style_dict.keys():
            h_ratio.SetLineColor(self.hstore[hr_name].style_dict["line_color"])
          if "line_width" in self.hstore[hr_name].style_dict.keys():
            h_ratio.SetLineWidth(self.hstore[hr_name].style_dict["line_width"])
          
          if "marker_style" in self.hstore[hr_name].style_dict.keys():
            h_ratio.SetMarkerStyle(self.hstore[hr_name].style_dict["marker_style"])
          if "marker_color" in self.hstore[hr_name].style_dict.keys():
            h_ratio.SetMarkerColor(self.hstore[hr_name].style_dict["marker_color"])
          if "marker_size" in self.hstore[hr_name].style_dict.keys():
            h_ratio.SetMarkerSize(self.hstore[hr_name].style_dict["marker_size"]+1)

          h_ratio.SetNameTitle('%s_div_%s'%(self.hstore[self.ratio_num].hname,self.hstore[hr_name].hname),'%s_div_%s'%(self.hstore[self.ratio_num].hname,self.hstore[hr_name].hname)) 
          h_ratio_list.append(h_ratio)
        
        for hr in h_ratio_list: 
          hr.Draw("SAME,E1")
        
        pad2.RedrawAxis()
       
      c.SaveAs(cname+".eps")


## EOF








