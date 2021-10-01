// This program takes the outfile from the flight path out toward the
// neutrino gravitational focus and creates a stacked histogram 



void histoCombinerFermi () {  // file for opening
  
  //First Hist to Open

  TFile* myFile = TFile::Open("nu_e+35+2.root");
  //TFile* myFile = new TFile("Tutorial.root", "READ");

 
  TH1D* electronevt0 = new TH1D("Parent Electron Hit EVT 0","", 300, 0, 300);
  TH1D* gammaevt0   = new TH1D("Parent Gamma Hit EVT 0","", 30000, 0,30000);
  TH1D* electron_evt1 = new TH1D("Parent Electron Hit EVT 1","", 300, 0, 300);
  TH1D* gamma_evt1   = new TH1D("Parent Gamma Hit EVT 1","", 30000, 0,30000);
  TH1D* electron_evt2 = new TH1D("Parent Electron Hit EVT 2","", 300, 0, 300);
  TH1D* gamma_evt2   = new TH1D("Parent Gamma Hit EVT 2","", 30000, 0,30000);
  TH1D* electron_evt3 = new TH1D("Parent Electron Hit EVT 3","", 300, 0, 300);
  TH1D* gamma_evt3   = new TH1D("Parent Gamma Hit EVT 3","", 30000, 0,30000);
  TH1D* electron_evt4 = new TH1D("Parent Electron Hit EVT 4","", 300, 0, 300);
  TH1D* gamma_evt4   = new TH1D("Parent Gamma Hit EVT 4","", 30000, 0,30000);
  TH1D* electron_evt5 = new TH1D("Parent Electron Hit EVT 5","", 300, 0, 300);
  TH1D* gamma_evt5   = new TH1D("Parent Gamma Hit EVT 5","", 30000, 0,30000);
  TH1D* electron_evt6 = new TH1D("Parent Electron Hit EVT 6","", 300, 0, 300);
  TH1D* gamma_evt6   = new TH1D("Parent Gamma Hit EVT 6","", 30000, 0,30000);
  TH1D* electron_evt7 = new TH1D("Parent Electron Hit EVT 7","", 300, 0, 300);
  TH1D* gamma_evt7   = new TH1D("Parent Gamma Hit EVT 7","", 30000, 0,30000);
  TH1D* electron_evt8 = new TH1D("Parent Electron Hit EVT 8","", 300, 0, 300);
  TH1D* gamma_evt8   = new TH1D("Parent Gamma Hit EVT 8","", 30000, 0,30000);
  TH1D* electron_evt9 = new TH1D("Parent Electron Hit EVT 9","", 300, 0, 300);
  TH1D* gamma_evt9   = new TH1D("Parent Gamma Hit EVT 9","", 30000, 0,30000);
  TH1D* electron_evt10 = new TH1D("Parent Electron Hit EVT 10","", 300, 0, 300);
  TH1D* gamma_evt10   = new TH1D("Parent Gamma Hit EVT 10","", 30000, 0,30000);
  TH1D* electron_evt11 = new TH1D("Parent Electron Hit EVT 11","", 300, 0, 300);
  TH1D* gamma_evt11   = new TH1D("Parent Gamma Hit EVT 11","", 30000, 0,30000);
  TH1D* electron_evt12 = new TH1D("Parent Electron Hit EVT 12","", 300, 0, 300);
  TH1D* gamma_evt12   = new TH1D("Parent Gamma Hit EVT 12","", 30000, 0,30000);
  TH1D* electron_evt13 = new TH1D("Parent Electron Hit EVT 13","", 300, 0, 300);
  TH1D* gamma_evt13   = new TH1D("Parent Gamma Hit EVT 13","", 30000, 0,30000);
  TH1D* electron_evt14 = new TH1D("Parent Electron Hit EVT 14","", 300, 0, 300);
  TH1D* gamma_evt14   = new TH1D("Parent Gamma Hit EVT 14","", 30000, 0,30000);
  TH1D* electron_evt15 = new TH1D("Parent Electron Hit EVT 15","", 300, 0, 300);
  TH1D* gamma_evt15   = new TH1D("Parent Gamma Hit EVT 15","", 30000, 0,30000);
  TH1D* electron_evt16 = new TH1D("Parent Electron Hit EVT 16","", 300, 0, 300);
  TH1D* gamma_evt16   = new TH1D("Parent Gamma Hit EVT 16","", 30000, 0,30000);
  TH1D* electron_evt17 = new TH1D("Parent Electron Hit EVT 17","", 300, 0, 300);
  TH1D* gamma_evt17   = new TH1D("Parent Gamma Hit EVT 17","", 30000, 0,30000);
  TH1D* electron_evt18 = new TH1D("Parent Electron Hit EVT 18","", 300, 0, 300);
  TH1D* gamma_evt18   = new TH1D("Parent Gamma Hit EVT 18","", 30000, 0,30000);
  TH1D* electron_evt19 = new TH1D("Parent Electron Hit EVT 19","", 300, 0, 300);
  TH1D* gamma_evt19   = new TH1D("Parent Gamma Hit EVT 19","", 30000, 0,30000);
 
  //auto canvas = new TCanvas("c","c");
  

  /*
  myFile->GetObject("Time of hit from Initial particle evt 0", electronevt0);
  myFile->GetObject("Time of hit from Secondary particle evt 0", gammaevt0);
  
  
  myFile->GetObject("Time of hit from Initial particle evt 1;1", electron_evt1);
  myFile->GetObject("Time of hit from Secondary particle evt 1;1", gamma_evt1);
  
  myFile->GetObject("Time of hit from Initial particle evt 2;1", electron_evt2);
  myFile->GetObject("Time of hit from Secondary particle evt 2;1", gamma_evt2);
  
  myFile->GetObject("Time of hit from Initial particle evt 3;1", electron_evt3);
  myFile->GetObject("Time of hit from Secondary particle evt 3;1", gamma_evt3);
  
  myFile->GetObject("Time of hit from Initial particle evt 4;1", electron_evt4);
  myFile->GetObject("Time of hit from Secondary particle evt 4;1", gamma_evt4);
  
  myFile->GetObject("Time of hit from Initial particle evt 5;1", electron_evt5);
  myFile->GetObject("Time of hit from Secondary particle evt 5;1", gamma_evt5);
  
  myFile->GetObject("Time of hit from Initial particle evt 6;1", electron_evt6);
  myFile->GetObject("Time of hit from Secondary particle evt 6;1", gamma_evt6);
  
  myFile->GetObject("Time of hit from Initial particle evt 7;1", electron_evt7);
  myFile->GetObject("Time of hit from Secondary particle evt 7;1", gamma_evt7);
  
  myFile->GetObject("Time of hit from Initial particle evt 8;1", electron_evt8);
  myFile->GetObject("Time of hit from Secondary particle evt 8;1", gamma_evt8);
  
  myFile->GetObject("Time of hit from Initial particle evt 9;1", electron_evt9);
  myFile->GetObject("Time of hit from Secondary particle evt 9;1", gamma_evt9);
  
  myFile->GetObject("Time of hit from Initial particle evt 10;1", electron_evt10);
  myFile->GetObject("Time of hit from Secondary particle evt 10;1", gamma_evt10);
  
  myFile->GetObject("Time of hit from Initial particle evt 11;1", electron_evt11);
  myFile->GetObject("Time of hit from Secondary particle evt 11;1", gamma_evt11);
  
  myFile->GetObject("Time of hit from Initial particle evt 12;1", electron_evt12);
  myFile->GetObject("Time of hit from Secondary particle evt 12;1", gamma_evt12);
  
  myFile->GetObject("Time of hit from Initial particle evt 13;1", electron_evt13);
  myFile->GetObject("Time of hit from Secondary particle evt 13;1", gamma_evt13);
  
  myFile->GetObject("Time of hit from Initial particle evt 14;1", electron_evt14);
  myFile->GetObject("Time of hit from Secondary particle evt 14;1", gamma_evt14);
  
  myFile->GetObject("Time of hit from Initial particle evt 15;1", electron_evt15);
  myFile->GetObject("Time of hit from Secondary particle evt 15;1", gamma_evt15);
  
  myFile->GetObject("Time of hit from Initial particle evt 16;1", electron_evt16);
  myFile->GetObject("Time of hit from Secondary particle evt 16;1", gamma_evt16);
  
  myFile->GetObject("Time of hit from Initial particle evt 17;1", electron_evt17);
  myFile->GetObject("Time of hit from Secondary particle evt 17;1", gamma_evt17);
  
  myFile->GetObject("Time of hit from Initial particle evt 18;1", electron_evt18);
  myFile->GetObject("Time of hit from Secondary particle evt 18;1", gamma_evt18);
  
  myFile->GetObject("Time of hit from Initial particle evt 19;1", electron_evt19);
  myFile->GetObject("Time of hit from Secondary particle evt 19;1", gamma_evt19);
  */

  struct eventStruct{
    Double_t ElectronTime;
  };
  eventStruct myEvent;

  
  TTree*myTree;

  myFile->GetObject("Time of Hit of ElectronEVT0",myTree);
  
  myTree->SetBranchAddress("ElectronTime", &(myEvent.ElectronTime) );
  
unsigned int mysize = myTree->GetEntries();

 for (unsigned int i = 0; i < mysize; ++i) {
   myTree->GetEntry(i);
   electronevt0->Fill(myEvent.ElectronTime);
 }

 auto canvas = new TCanvas("c","c");
 electronevt0->Draw();
 canvas->Draw();
 
  
 
  
  
  gROOT->ForceStyle();
  
  
  
 

  /*
  TH1D* ran = new TH1D("ran", "", 100, 0, 100);
  ran->FillRandom("gaus", 1E2);
  auto canvas = new TCanvas("c","c");
  
  ran->Draw();  
  canvas->Draw();
  */
  //---------------------------------------------------------------
 
 

  
  /*
  //Creating Canvas and Stack placeholders. 
  auto canvas_new = new TCanvas("canvas","canvas");
  
  auto hs0 = new THStack("hs0", "Timing of Photons hitting PMT in evt 0;Time of Photon hits (ns);Photon Counts");
  gStyle->SetPalette(kRainBow);
  //electron_evt0->SetLineColor(kWhite);
  //gamma_evt0->SetLineColor(kWhite);
  
  hs0->Add(electronevt0);
  hs0->Add(gammaevt0);
  
    
  hs0->Draw("HIST pfc nostack");
  hs0->GetHistogram()->GetXaxis()->SetRange(0,10000);
  hs0->Draw("HIST pfc nostack");
  canvas_new->Draw();
  */
  
  /*
 auto hs1 = new THStack("hs1", "Timing of Photons hitting PMT in evt 1;Time of Photon hits (ns);Photon Counts");
  gStyle->SetPalette(kRainBow);
  electron_evt1->SetLineColor(kWhite);
  gamma_evt1->SetLineColor(kWhite);
  
  hs1->Add(electron_evt1);
  hs1->Add(gamma_evt1);
 
  //hs1->Draw("HIST pfc nostack");

 auto hs2 = new THStack("hs2", "Timing of Photons hitting PMT in evt 2;Time of Photon hits (ns);Photon Counts");
  gStyle->SetPalette(kRainBow);
  electron_evt2->SetLineColor(kWhite);
  gamma_evt2->SetLineColor(kWhite);
  
  hs2->Add(electron_evt2);
  hs2->Add(gamma_evt2);
 
  //hs2->Draw("HIST pfc nostack");

  
 auto hs3 = new THStack("hs3", "Timing of Photons hitting PMT in evt 3;Time of Photon hits (ns);Photon Counts");
  gStyle->SetPalette(kRainBow);
  electron_evt3->SetLineColor(kWhite);
  gamma_evt3->SetLineColor(kWhite);
  
  hs3->Add(electron_evt3);
  hs3->Add(gamma_evt3);
 
  // hs3->Draw("HIST pfc nostack");
  
 auto hs4 = new THStack("hs4", "Timing of Photons hitting PMT in evt 4;Time of Photon hits (ns);Photon Counts");
  gStyle->SetPalette(kRainBow);
  electron_evt4->SetLineColor(kWhite);
  gamma_evt4->SetLineColor(kWhite);
  
  hs4->Add(electron_evt4);
  hs4->Add(gamma_evt4);
 
  //hs4->Draw("HIST pfc nostack");


 auto hs5 = new THStack("hs5", "Timing of Photons hitting PMT in evt 5;Time of Photon hits (ns);Photon Counts");
  gStyle->SetPalette(kRainBow);
  electron_evt5->SetLineColor(kWhite);
  gamma_evt5->SetLineColor(kWhite);
  
  hs5->Add(electron_evt5);
  hs5->Add(gamma_evt5);
 
  //hs5->Draw("HIST pfc nostack");


 auto hs6 = new THStack("hs6", "Timing of Photons hitting PMT in evt 6;Time of Photon hits (ns);Photon Counts");
  gStyle->SetPalette(kRainBow);
  electron_evt6->SetLineColor(kWhite);
  gamma_evt6->SetLineColor(kWhite);
  
  hs6->Add(electron_evt6);
  hs6->Add(gamma_evt6);
 
  //hs6->Draw("HIST pfc nostack");



 auto hs7 = new THStack("hs7", "Timing of Photons hitting PMT in evt 7;Time of Photon hits (ns);Photon Counts");
  gStyle->SetPalette(kRainBow);
  electron_evt7->SetLineColor(kWhite);
  gamma_evt7->SetLineColor(kWhite);
  
  hs7->Add(electron_evt7);
  hs7->Add(gamma_evt7);
 
  //hs7->Draw("HIST pfc nostack");



 auto hs8 = new THStack("hs8", "Timing of Photons hitting PMT in evt 8;Time of Photon hits (ns);Photon Counts");
  gStyle->SetPalette(kRainBow);
  electron_evt8->SetLineColor(kWhite);
  gamma_evt8->SetLineColor(kWhite);
  
  hs8->Add(electron_evt8);
  hs8->Add(gamma_evt8);
 
  //hs8->Draw("HIST pfc nostack");



 auto hs9 = new THStack("hs9", "Timing of Photons hitting PMT in evt 9;Time of Photon hits (ns);Photon Counts");
  gStyle->SetPalette(kRainBow);
  electron_evt9->SetLineColor(kWhite);
  gamma_evt9->SetLineColor(kWhite);
  
  hs9->Add(electron_evt9);
  hs9->Add(gamma_evt9);
 
  //hs9->Draw("HIST pfc nostack");

  
auto hs10 = new THStack("hs10", "Timing of Photons hitting PMT in evt 10;Time of Photon hits (ns);Photon Counts");
  gStyle->SetPalette(kRainBow);
  electron_evt10->SetLineColor(kWhite);
  gamma_evt10->SetLineColor(kWhite);
  
  hs10->Add(electron_evt10);
  hs10->Add(gamma_evt10);
 
  //hs10->Draw("HIST pfc nostack");


auto hs11 = new THStack("hs11", "Timing of Photons hitting PMT in evt 11;Time of Photon hits (ns);Photon Counts");
  gStyle->SetPalette(kRainBow);
  electron_evt11->SetLineColor(kWhite);
  gamma_evt11->SetLineColor(kWhite);
  
  hs11->Add(electron_evt11);
  hs11->Add(gamma_evt11);
 
  // hs11->Draw("HIST pfc nostack");

auto hs12 = new THStack("hs12", "Timing of Photons hitting PMT in evt 12;Time of Photon hits (ns);Photon Counts");
  gStyle->SetPalette(kRainBow);
  electron_evt12->SetLineColor(kWhite);
  gamma_evt12->SetLineColor(kWhite);
  
  hs12->Add(electron_evt12);
  hs12->Add(gamma_evt12);
 
  //hs12->Draw("HIST pfc nostack");


  
auto hs13 = new THStack("hs13", "Timing of Photons hitting PMT in evt 13;Time of Photon hits (ns);Photon Counts");
  gStyle->SetPalette(kRainBow);
  electron_evt13->SetLineColor(kWhite);
  gamma_evt13->SetLineColor(kWhite);
  
  hs13->Add(electron_evt13);
  hs13->Add(gamma_evt13);
 
  //hs13->Draw("HIST pfc nostack");

  
auto hs14 = new THStack("hs14", "Timing of Photons hitting PMT in evt 14;Time of Photon hits (ns);Photon Counts");
  gStyle->SetPalette(kRainBow);
  electron_evt14->SetLineColor(kWhite);
  gamma_evt14->SetLineColor(kWhite);
  
  hs14->Add(electron_evt14);
  hs14->Add(gamma_evt14);
 
  //hs14->Draw("HIST pfc nostack");


auto hs15 = new THStack("hs15", "Timing of Photons hitting PMT in evt 15;Time of Photon hits (ns);Photon Counts");
  gStyle->SetPalette(kRainBow);
  electron_evt15->SetLineColor(kWhite);
  gamma_evt15->SetLineColor(kWhite);
  
  hs15->Add(electron_evt15);
  hs15->Add(gamma_evt15);
 
  //hs15->Draw("HIST pfc nostack");

  
auto hs16 = new THStack("hs16", "Timing of Photons hitting PMT in evt 16;Time of Photon hits (ns);Photon Counts");
  gStyle->SetPalette(kRainBow);
  electron_evt16->SetLineColor(kWhite);
  gamma_evt16->SetLineColor(kWhite);
  
  hs16->Add(electron_evt16);
  hs16->Add(gamma_evt16);
 
  //hs16->Draw("HIST pfc nostack");


auto hs17 = new THStack("hs17", "Timing of Photons hitting PMT in evt 17;Time of Photon hits (ns);Photon Counts");
  gStyle->SetPalette(kRainBow);
  electron_evt17->SetLineColor(kWhite);
  gamma_evt17->SetLineColor(kWhite);
  
  hs17->Add(electron_evt17);
  hs17->Add(gamma_evt17);
 
  //hs17->Draw("HIST pfc nostack");



auto hs18 = new THStack("hs18", "Timing of Photons hitting PMT in evt 18;Time of Photon hits (ns);Photon Counts");
  gStyle->SetPalette(kRainBow);
  electron_evt18->SetLineColor(kWhite);
  gamma_evt18->SetLineColor(kWhite);
  
  hs18->Add(electron_evt18);
  hs18->Add(gamma_evt18);
 
  //hs18->Draw("HIST pfc nostack");

  
auto hs19 = new THStack("hs19", "Timing of Photons hitting PMT in evt 19;Time of Photon hits (ns);Photon Counts");
  gStyle->SetPalette(kRainBow);
  electron_evt19->SetLineColor(kWhite);
  gamma_evt19->SetLineColor(kWhite);
  
  hs19->Add(electron_evt19);
  hs19->Add(gamma_evt19);
 
  // hs19->Draw("HIST pfc nostack");
  */

  /*
  canvas_new->Divide(4,5);
  canvas_new->cd(1); hs0->Draw("HIST pfc nostack");
  canvas_new->cd(2); hs1->Draw("HIST pfc nostack");
  canvas_new->cd(3); hs2->Draw("HIST pfc nostack");
  canvas_new->cd(4); hs3->Draw("HIST pfc nostack");
  canvas_new->cd(5); hs4->Draw("HIST pfc nostack");
  canvas_new->cd(6); hs5->Draw("HIST pfc nostack");
  canvas_new->cd(7); hs6->Draw("HIST pfc nostack");
  canvas_new->cd(8); hs7->Draw("HIST pfc nostack");
  canvas_new->cd(9); hs8->Draw("HIST pfc nostack");
  canvas_new->cd(10); hs9->Draw("HIST pfc nostack");
  canvas_new->cd(11); hs10->Draw("HIST pfc nostack");
  canvas_new->cd(12); hs11->Draw("HIST pfc nostack");
  canvas_new->cd(13); hs12->Draw("HIST pfc nostack");
  canvas_new->cd(14); hs13->Draw("HIST pfc nostack");
  canvas_new->cd(15); hs14->Draw("HIST pfc nostack");
  canvas_new->cd(16); hs15->Draw("HIST pfc nostack");
  canvas_new->cd(17); hs16->Draw("HIST pfc nostack");
  canvas_new->cd(18); hs17->Draw("HIST pfc nostack");
  canvas_new->cd(19); hs18->Draw("HIST pfc nostack");
  canvas_new->cd(20); hs19->Draw("HIST pfc nostack");
  */



  
  //canvas_new->Draw();
  

  
  


  
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











