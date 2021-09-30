// This program takes the outfile from the flight path out toward the
// neutrino gravitational focus and creates a stacked histogram 



void histoCombinerFermi () {  // file for opening
  
  //First Hist to Open

  TFile* myFile = TFile::Open("testFile.root");
  //TFile* myFile = new TFile("Tutorial.root", "READ");

  //TH1D* electron = new TH1D("Parent Electron Hit","", 10, 100, 150);
  TH1D* electron = new TH1D("Parent Electron Hit","", 100, 0, 150);
  
  //TH1D* gamma    = new TH1D("Parent Gamma Hit","", 100, 1500, 3000);
  
  TH1D* gamma    = new TH1D("Parent Gamma Hit","", 1000, 1500,3000);
  myFile->GetObject("Time of hit from Initial particle;1", electron);
  myFile->GetObject("Time of hit from Secondary particle;1", gamma);

 
  
  gROOT->ForceStyle();
  
  
  electron->SetBinsLength(100);
  gamma->SetBinsLength(100);
 


  

  
  //---------------------------------------------------------------
 
 

  
  
  //Creating Canvas and Stack placeholders. 
  auto canvas_new = new TCanvas("canvas","canvas");
  
  auto hs = new THStack("hs", "Timing of Photons hitting PMT;Time of Photon hits (ns);Photon Counts");
  gStyle->SetPalette(kRainBow);
  electron->SetLineColor(kWhite);
  gamma->SetLineColor(kWhite);
  
  hs ->Add(electron);
  hs->Add(gamma);
 
  hs->Draw("HIST pfc nostack");

  canvas_new->Draw();
  

  
  





  /*
  THStack* myStack = new THStack("myStack","Events;Radius(Solar Radii);Events/Bin");

  TLegend *EnerLegend = new TLegend(0.15,0.65,0.55,0.85);
  EnerLegend -> SetHeader("Legend");
  
  cosmicRadHist->SetFillColor(kRed);
  cosmicRadHist->Rebin(2);
  myStack->Add(cosmicRadHist);
  
  solarRadHist ->SetFillColor(kYellow);
  solarRadHist->Rebin(2);
  myStack->Add(solarRadHist);
  
  nRadHist->SetFillColor(kBlue);
  nRadHist->Rebin(2);
  myStack -> Add( nRadHist );


  TCanvas *c1 = new TCanvas("c1","Stacked",700,900);
  myStack->Draw("");

  EnerLegend -> AddEntry(nRadHist,"Neutrino Signal");
  EnerLegend -> AddEntry(solarRadHist,"Solar Background");
  EnerLegend -> AddEntry(cosmicRadHist,"Cosmic Background");
  EnerLegend -> Draw();





  THStack* myStack1 = new THStack("myStack1","Events;Radius(Solar Radii);Events/Bin");

  TLegend *EnerLegend1 = new TLegend(0.45,0.65,0.85,0.85);
  EnerLegend1 -> SetHeader("Legend");
  
  cosmic35RadHist->SetFillColor(kRed);
  //cosmicRadHist->Rebin(2);
  myStack1->Add(cosmic35RadHist);
  
  solar35RadHist ->SetFillColor(kYellow);
  //solarRadHist->Rebin(2);
  myStack1->Add(solar35RadHist);
  
  n35RadHist->SetFillColor(kBlue);
  //n35RadHist->Rebin(2);
  myStack1-> Add( n35RadHist );




  TCanvas *c2 = new TCanvas("c2","Stacked",700,900);
  myStack1->Draw("");

  EnerLegend1 -> AddEntry(n35RadHist,"Neutrino Signal");
  EnerLegend1 -> AddEntry(solar35RadHist,"Solar Background");
  EnerLegend1 -> AddEntry(cosmic35RadHist,"Cosmic Background");
  EnerLegend1 -> Draw();
  */



 





}











