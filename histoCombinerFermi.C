// This program takes the outfile from the flight path out toward the
// neutrino gravitational focus and creates a stacked histogram 



void histoCombinerFermi () {  // file for opening
  
  //First Hist to Open

  TFile* myFile = TFile::Open("nu_e+35+1.root");
  //TFile* myFile = new TFile("Tutorial.root", "READ");

 
  TH1D* electronevt0 = new TH1D("Parent Electron Hit EVT 0","", 100, 0, 1000);
  TH1D* gammaevt0   = new TH1D("Parent Gamma Hit EVT 0","", 3000, 0, 30000);
  TH1D* electron_evt1 = new TH1D("Parent Electron Hit EVT 1","", 100, 0, 1000);
  TH1D* gamma_evt1   = new TH1D("Parent Gamma Hit EVT 1","", 3000, 0, 30000);
  TH1D* electron_evt2 = new TH1D("Parent Electron Hit EVT 2","", 100, 0, 1000);
  TH1D* gamma_evt2   = new TH1D("Parent Gamma Hit EVT 2","", 3000, 0, 30000);
  TH1D* electron_evt3 = new TH1D("Parent Electron Hit EVT 3","", 100, 0, 1000);
  TH1D* gamma_evt3   = new TH1D("Parent Gamma Hit EVT 3","", 3000, 0, 30000);
  TH1D* electron_evt4 = new TH1D("Parent Electron Hit EVT 4","", 100, 0, 1000);
  TH1D* gamma_evt4   = new TH1D("Parent Gamma Hit EVT 4","", 3000, 0, 30000);
  TH1D* electron_evt5 = new TH1D("Parent Electron Hit EVT 5","", 100, 0, 1000);
  TH1D* gamma_evt5   = new TH1D("Parent Gamma Hit EVT 5","", 3000, 0, 30000);
  TH1D* electron_evt6 = new TH1D("Parent Electron Hit EVT 6","", 100, 0, 1000);
  TH1D* gamma_evt6   = new TH1D("Parent Gamma Hit EVT 6","", 3000, 0, 30000);
  TH1D* electron_evt7 = new TH1D("Parent Electron Hit EVT 7","", 100, 0, 1000);
  TH1D* gamma_evt7   = new TH1D("Parent Gamma Hit EVT 7","", 3000, 0, 30000);
  TH1D* electron_evt8 = new TH1D("Parent Electron Hit EVT 8","",100, 0, 1000);
  TH1D* gamma_evt8   = new TH1D("Parent Gamma Hit EVT 8","", 3000, 0, 30000);
  TH1D* electron_evt9 = new TH1D("Parent Electron Hit EVT 9","",100, 0, 1000);
  TH1D* gamma_evt9   = new TH1D("Parent Gamma Hit EVT 9","", 3000, 0, 30000);
  TH1D* electron_evt10 = new TH1D("Parent Electron Hit EVT 10","", 100, 0, 1000);
  TH1D* gamma_evt10   = new TH1D("Parent Gamma Hit EVT 10","", 3000, 0, 30000);
  TH1D* electron_evt11 = new TH1D("Parent Electron Hit EVT 11","", 100, 0, 1000);
  TH1D* gamma_evt11   = new TH1D("Parent Gamma Hit EVT 11","", 3000, 0, 30000);
  TH1D* electron_evt12 = new TH1D("Parent Electron Hit EVT 12","", 100, 0, 1000);
  TH1D* gamma_evt12   = new TH1D("Parent Gamma Hit EVT 12","", 3000, 0, 30000);
  TH1D* electron_evt13 = new TH1D("Parent Electron Hit EVT 13","", 100, 0, 1000);
  TH1D* gamma_evt13   = new TH1D("Parent Gamma Hit EVT 13","", 3000, 0, 30000);
  TH1D* electron_evt14 = new TH1D("Parent Electron Hit EVT 14","", 100, 0, 1000);
  TH1D* gamma_evt14   = new TH1D("Parent Gamma Hit EVT 14","", 3000, 0, 30000);
  TH1D* electron_evt15 = new TH1D("Parent Electron Hit EVT 15","", 100, 0, 1000);
  TH1D* gamma_evt15   = new TH1D("Parent Gamma Hit EVT 15","", 3000, 0, 30000);
  TH1D* electron_evt16 = new TH1D("Parent Electron Hit EVT 16","", 100, 0, 1000);
  TH1D* gamma_evt16   = new TH1D("Parent Gamma Hit EVT 16","", 3000, 0, 30000);
  TH1D* electron_evt17 = new TH1D("Parent Electron Hit EVT 17","", 100, 0, 1000);
  TH1D* gamma_evt17   = new TH1D("Parent Gamma Hit EVT 17","", 3000, 0, 30000);
  TH1D* electron_evt18 = new TH1D("Parent Electron Hit EVT 18","", 100, 0, 1000);
  TH1D* gamma_evt18   = new TH1D("Parent Gamma Hit EVT 18","", 3000, 0, 30000);
  TH1D* electron_evt19 = new TH1D("Parent Electron Hit EVT 19","", 100, 0, 1000);
  TH1D* gamma_evt19   = new TH1D("Parent Gamma Hit EVT 19","", 3000, 0, 30000);
 




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
    Double_t ElectronTime0;
    Double_t GammaTime0;
    Double_t ElectronTime1;
    Double_t GammaTime1;
    Double_t ElectronTime2;
    Double_t GammaTime2;
    Double_t ElectronTime3;
    Double_t GammaTime3;
    Double_t ElectronTime4;
    Double_t GammaTime4;
    Double_t ElectronTime5;
    Double_t GammaTime5;
    Double_t ElectronTime6;
    Double_t GammaTime6;
    Double_t ElectronTime7;
    Double_t GammaTime7;

    Double_t ElectronTime8;
    Double_t GammaTime8;
    Double_t ElectronTime9;
    Double_t GammaTime9;
    Double_t ElectronTime10;
    Double_t GammaTime10;
    Double_t ElectronTime11;
    Double_t GammaTime11;
    Double_t ElectronTime12;
    Double_t GammaTime12;
    Double_t ElectronTime13;
    Double_t GammaTime13;
    Double_t ElectronTime14;
    Double_t GammaTime14;
    Double_t ElectronTime15;
    Double_t GammaTime15;
    Double_t ElectronTime16;
    Double_t GammaTime16;
    Double_t ElectronTime17;
    Double_t GammaTime17;
    Double_t ElectronTime18;
    Double_t GammaTime18;
    Double_t ElectronTime19;
    Double_t GammaTime19;

    
  };
  eventStruct myEvent;

  
  TTree*myTreeE0;
  TTree*myTreeG0;
  TTree*myTreeE1;
  TTree*myTreeG1;
  TTree*myTreeE2;
  TTree*myTreeG2;
  TTree*myTreeE3;
  TTree*myTreeG3;
  TTree*myTreeE4;
  TTree*myTreeG4;
  TTree*myTreeE5;
  TTree*myTreeG5;
  TTree*myTreeE6;
  TTree*myTreeG6;
  TTree*myTreeE7;
  TTree*myTreeG7;
  TTree*myTreeE8;
  TTree*myTreeG8;
  TTree*myTreeE9;
  TTree*myTreeG9;
  TTree*myTreeE10;
  TTree*myTreeG10;
  TTree*myTreeE11;
  TTree*myTreeG11;
  TTree*myTreeE12;
  TTree*myTreeG12;
  TTree*myTreeE13;
  TTree*myTreeG13;
  TTree*myTreeE14;
  TTree*myTreeG14;
  TTree*myTreeE15;
  TTree*myTreeG15;
  TTree*myTreeE16;
  TTree*myTreeG16;
  TTree*myTreeE17;
  TTree*myTreeG17;
  TTree*myTreeE18;
  TTree*myTreeG18;
  TTree*myTreeE19;
  TTree*myTreeG19;


  
  myFile->GetObject("Time of Hit of ElectronEVT0",myTreeE0);
  myFile->GetObject("Time of Hit of GammaEVT0",myTreeG0);

  myFile->GetObject("Time of Hit of ElectronEVT1",myTreeE1);
  myFile->GetObject("Time of Hit of GammaEVT1",myTreeG1);

  myFile->GetObject("Time of Hit of ElectronEVT2",myTreeE2);
  myFile->GetObject("Time of Hit of GammaEVT2",myTreeG2);

  myFile->GetObject("Time of Hit of ElectronEVT3",myTreeE3);
  myFile->GetObject("Time of Hit of GammaEVT3",myTreeG3);

  myFile->GetObject("Time of Hit of ElectronEVT4",myTreeE4);
  myFile->GetObject("Time of Hit of GammaEVT4",myTreeG4);

  myFile->GetObject("Time of Hit of ElectronEVT5",myTreeE5);
  myFile->GetObject("Time of Hit of GammaEVT5",myTreeG5);

  myFile->GetObject("Time of Hit of ElectronEVT6",myTreeE6);
  myFile->GetObject("Time of Hit of GammaEVT6",myTreeG6);

  myFile->GetObject("Time of Hit of ElectronEVT7",myTreeE7);
  myFile->GetObject("Time of Hit of GammaEVT7",myTreeG7);
  
  myFile->GetObject("Time of Hit of ElectronEVT8",myTreeE8);
  myFile->GetObject("Time of Hit of GammaEVT8",myTreeG8);
  
  myFile->GetObject("Time of Hit of ElectronEVT9",myTreeE9);
  myFile->GetObject("Time of Hit of GammaEVT9",myTreeG9);

  myFile->GetObject("Time of Hit of ElectronEVT10",myTreeE10);
  myFile->GetObject("Time of Hit of GammaEVT10",myTreeG10);

  myFile->GetObject("Time of Hit of ElectronEVT11",myTreeE11);
  myFile->GetObject("Time of Hit of GammaEVT11",myTreeG11);

  myFile->GetObject("Time of Hit of ElectronEVT12",myTreeE12);
  myFile->GetObject("Time of Hit of GammaEVT12",myTreeG12);

  myFile->GetObject("Time of Hit of ElectronEVT13",myTreeE13);
  myFile->GetObject("Time of Hit of GammaEVT13",myTreeG13);

  myFile->GetObject("Time of Hit of ElectronEVT14",myTreeE14);
  myFile->GetObject("Time of Hit of GammaEVT14",myTreeG14);

  myFile->GetObject("Time of Hit of ElectronEVT15",myTreeE15);
  myFile->GetObject("Time of Hit of GammaEVT15",myTreeG15);

  myFile->GetObject("Time of Hit of ElectronEVT16",myTreeE16);
  myFile->GetObject("Time of Hit of GammaEVT16",myTreeG16);

  myFile->GetObject("Time of Hit of ElectronEVT17",myTreeE17);
  myFile->GetObject("Time of Hit of GammaEVT17",myTreeG17);

  myFile->GetObject("Time of Hit of ElectronEVT18",myTreeE18);
  myFile->GetObject("Time of Hit of GammaEVT18",myTreeG18);

  myFile->GetObject("Time of Hit of ElectronEVT19",myTreeE19);
  myFile->GetObject("Time of Hit of GammaEVT19",myTreeG19);

 



  
  
  myTreeE0->SetBranchAddress("ElectronTime", &(myEvent.ElectronTime0) );
  myTreeG0->SetBranchAddress("GammaTime", &(myEvent.GammaTime0) );

  myTreeE1->SetBranchAddress("ElectronTime", &(myEvent.ElectronTime1) );
  myTreeG1->SetBranchAddress("GammaTime", &(myEvent.GammaTime1) );

  myTreeE2->SetBranchAddress("ElectronTime", &(myEvent.ElectronTime2) );
  myTreeG2->SetBranchAddress("GammaTime", &(myEvent.GammaTime2) );

  myTreeE3->SetBranchAddress("ElectronTime", &(myEvent.ElectronTime3) );
  myTreeG3->SetBranchAddress("GammaTime", &(myEvent.GammaTime3) );

  myTreeE4->SetBranchAddress("ElectronTime", &(myEvent.ElectronTime4) );
  myTreeG4->SetBranchAddress("GammaTime", &(myEvent.GammaTime4) );

  myTreeE5->SetBranchAddress("ElectronTime", &(myEvent.ElectronTime5) );
  myTreeG5->SetBranchAddress("GammaTime", &(myEvent.GammaTime5) );

  myTreeE6->SetBranchAddress("ElectronTime", &(myEvent.ElectronTime6) );
  myTreeG6->SetBranchAddress("GammaTime", &(myEvent.GammaTime6) );

  myTreeE7->SetBranchAddress("ElectronTime", &(myEvent.ElectronTime7) );
  myTreeG7->SetBranchAddress("GammaTime", &(myEvent.GammaTime7) );

  myTreeE8->SetBranchAddress("ElectronTime", &(myEvent.ElectronTime8) );
  myTreeG8->SetBranchAddress("GammaTime", &(myEvent.GammaTime8) );

  myTreeE9->SetBranchAddress("ElectronTime", &(myEvent.ElectronTime9) );
  myTreeG9->SetBranchAddress("GammaTime", &(myEvent.GammaTime9) );

  myTreeE10->SetBranchAddress("ElectronTime", &(myEvent.ElectronTime10) );
  myTreeG10->SetBranchAddress("GammaTime", &(myEvent.GammaTime10) );

  myTreeE11->SetBranchAddress("ElectronTime", &(myEvent.ElectronTime11) );
  myTreeG11->SetBranchAddress("GammaTime", &(myEvent.GammaTime11) );

  myTreeE12->SetBranchAddress("ElectronTime", &(myEvent.ElectronTime12) );
  myTreeG12->SetBranchAddress("GammaTime", &(myEvent.GammaTime12) );

  myTreeE13->SetBranchAddress("ElectronTime", &(myEvent.ElectronTime13) );
  myTreeG13->SetBranchAddress("GammaTime", &(myEvent.GammaTime13) );

  myTreeE14->SetBranchAddress("ElectronTime", &(myEvent.ElectronTime14) );
  myTreeG14->SetBranchAddress("GammaTime", &(myEvent.GammaTime14) );

  myTreeE15->SetBranchAddress("ElectronTime", &(myEvent.ElectronTime15) );
  myTreeG15->SetBranchAddress("GammaTime", &(myEvent.GammaTime15) );

  myTreeE16->SetBranchAddress("ElectronTime", &(myEvent.ElectronTime16) );
  myTreeG16->SetBranchAddress("GammaTime", &(myEvent.GammaTime16) );

  myTreeE17->SetBranchAddress("ElectronTime", &(myEvent.ElectronTime17) );
  myTreeG17->SetBranchAddress("GammaTime", &(myEvent.GammaTime17) );

  myTreeE18->SetBranchAddress("ElectronTime", &(myEvent.ElectronTime18) );
  myTreeG18->SetBranchAddress("GammaTime", &(myEvent.GammaTime18) );
  
  myTreeE19->SetBranchAddress("ElectronTime", &(myEvent.ElectronTime19) );
  myTreeG19->SetBranchAddress("GammaTime", &(myEvent.GammaTime19) );


  
  gROOT->ForceStyle();
  
  
  
 

  
  unsigned int mysizeE0 = myTreeE0->GetEntries();

  for (unsigned int i = 0; i < mysizeE0; ++i) {
    myTreeE0->GetEntry(i);
    electronevt0->Fill(myEvent.ElectronTime0);
  }
  unsigned int mysizeG0 = myTreeG0->GetEntries();

  for (unsigned int i = 0; i < mysizeG0; ++i) {
    myTreeG0->GetEntry(i);
    gammaevt0->Fill(myEvent.GammaTime0);
  }
  //---------------------------------------------------------
  unsigned int mysizeE1 = myTreeE1->GetEntries();

  for (unsigned int i = 0; i < mysizeE1; ++i) {
    myTreeE1->GetEntry(i);
    electron_evt1->Fill(myEvent.ElectronTime1);
  }
  unsigned int mysizeG1 = myTreeG1->GetEntries();

  for (unsigned int i = 0; i < mysizeG1; ++i) {
    myTreeG1->GetEntry(i);
    gamma_evt1->Fill(myEvent.GammaTime1);
  }

  //---------------------------------------------------------
  unsigned int mysizeE2 = myTreeE2->GetEntries();

  for (unsigned int i = 0; i < mysizeE2; ++i) {
    myTreeE2->GetEntry(i);
    electron_evt2->Fill(myEvent.ElectronTime2);
  }
  unsigned int mysizeG2 = myTreeG2->GetEntries();

  for (unsigned int i = 0; i < mysizeG2; ++i) {
    myTreeG2->GetEntry(i);
    gamma_evt2->Fill(myEvent.GammaTime2);
  }

  //---------------------------------------------------------
  unsigned int mysizeE3 = myTreeE3->GetEntries();

  for (unsigned int i = 0; i < mysizeE3; ++i) {
    myTreeE3->GetEntry(i);
    electron_evt3->Fill(myEvent.ElectronTime3);
  }
  unsigned int mysizeG3 = myTreeG3->GetEntries();

  for (unsigned int i = 0; i < mysizeG3; ++i) {
    myTreeG3->GetEntry(i);
    gamma_evt3->Fill(myEvent.GammaTime3);
  }

  //---------------------------------------------------------
  unsigned int mysizeE4 = myTreeE4->GetEntries();

  for (unsigned int i = 0; i < mysizeE4; ++i) {
    myTreeE4->GetEntry(i);
    electron_evt4->Fill(myEvent.ElectronTime4);
  }
  unsigned int mysizeG4 = myTreeG4->GetEntries();

  for (unsigned int i = 0; i < mysizeG4; ++i) {
    myTreeG4->GetEntry(i);
    gamma_evt4->Fill(myEvent.GammaTime4);
  }

  //---------------------------------------------------------
  unsigned int mysizeE5 = myTreeE5->GetEntries();

  for (unsigned int i = 0; i < mysizeE5; ++i) {
    myTreeE5->GetEntry(i);
    electron_evt5->Fill(myEvent.ElectronTime5);
  }
  unsigned int mysizeG5 = myTreeG5->GetEntries();

  for (unsigned int i = 0; i < mysizeG5; ++i) {
    myTreeG5->GetEntry(i);
    gamma_evt5->Fill(myEvent.GammaTime5);
  }

  //---------------------------------------------------------
  unsigned int mysizeE6 = myTreeE6->GetEntries();

  for (unsigned int i = 0; i < mysizeE6; ++i) {
    myTreeE6->GetEntry(i);
    electron_evt6->Fill(myEvent.ElectronTime6);
  }
  unsigned int mysizeG6 = myTreeG6->GetEntries();

  for (unsigned int i = 0; i < mysizeG6; ++i) {
    myTreeG6->GetEntry(i);
    gamma_evt6->Fill(myEvent.GammaTime6);
  }

  //---------------------------------------------------------
  unsigned int mysizeE7 = myTreeE7->GetEntries();

  for (unsigned int i = 0; i < mysizeE7; ++i) {
    myTreeE7->GetEntry(i);
    electron_evt7->Fill(myEvent.ElectronTime7);
  }
  unsigned int mysizeG7 = myTreeG7->GetEntries();

  for (unsigned int i = 0; i < mysizeG7; ++i) {
    myTreeG7->GetEntry(i);
    gamma_evt7->Fill(myEvent.GammaTime7);
  }
  //---------------------------------------------------------

  unsigned int mysizeE8 = myTreeE8->GetEntries();

  for (unsigned int i = 0; i < mysizeE8; ++i) {
    myTreeE8->GetEntry(i);
    electron_evt8->Fill(myEvent.ElectronTime8);
  }
  unsigned int mysizeG8 = myTreeG8->GetEntries();

  for (unsigned int i = 0; i < mysizeG8; ++i) {
    myTreeG8->GetEntry(i);
    gamma_evt8->Fill(myEvent.GammaTime8);
  }
  //---------------------------------------------------------
 
  unsigned int mysizeE9 = myTreeE9->GetEntries();

  for (unsigned int i = 0; i < mysizeE9; ++i) {
    myTreeE9->GetEntry(i);
    electron_evt9->Fill(myEvent.ElectronTime9);
  }
  unsigned int mysizeG9 = myTreeG9->GetEntries();

  for (unsigned int i = 0; i < mysizeG9; ++i) {
    myTreeG9->GetEntry(i);
    gamma_evt9->Fill(myEvent.GammaTime9);
  }
  //---------------------------------------------------------

  unsigned int mysizeE10 = myTreeE10->GetEntries();

  for (unsigned int i = 0; i < mysizeE10; ++i) {
    myTreeE10->GetEntry(i);
    electron_evt10->Fill(myEvent.ElectronTime10);
  }
  unsigned int mysizeG10 = myTreeG10->GetEntries();

  for (unsigned int i = 0; i < mysizeG10; ++i) {
    myTreeG10->GetEntry(i);
    gamma_evt10->Fill(myEvent.GammaTime10);
  }
  //---------------------------------------------------------

  unsigned int mysizeE11 = myTreeE11->GetEntries();

  for (unsigned int i = 0; i < mysizeE11; ++i) {
    myTreeE11->GetEntry(i);
    electron_evt11->Fill(myEvent.ElectronTime11);
  }
  unsigned int mysizeG11 = myTreeG11->GetEntries();

  for (unsigned int i = 0; i < mysizeG11; ++i) {
    myTreeG11->GetEntry(i);
    gamma_evt11->Fill(myEvent.GammaTime11);
  }
  //---------------------------------------------------------

  unsigned int mysizeE12 = myTreeE12->GetEntries();

  for (unsigned int i = 0; i < mysizeE12; ++i) {
    myTreeE12->GetEntry(i);
    electron_evt12->Fill(myEvent.ElectronTime12);
  }
  unsigned int mysizeG12 = myTreeG12->GetEntries();

  for (unsigned int i = 0; i < mysizeG12; ++i) {
    myTreeG12->GetEntry(i);
    gamma_evt12->Fill(myEvent.GammaTime12);
  }
  //---------------------------------------------------------

  unsigned int mysizeE13 = myTreeE13->GetEntries();

  for (unsigned int i = 0; i < mysizeE13; ++i) {
    myTreeE13->GetEntry(i);
    electron_evt13->Fill(myEvent.ElectronTime13);
  }
  unsigned int mysizeG13 = myTreeG13->GetEntries();

  for (unsigned int i = 0; i < mysizeG13; ++i) {
    myTreeG13->GetEntry(i);
    gamma_evt13->Fill(myEvent.GammaTime13);
  }
  //---------------------------------------------------------

  unsigned int mysizeE14 = myTreeE14->GetEntries();

  for (unsigned int i = 0; i < mysizeE14; ++i) {
    myTreeE14->GetEntry(i);
    electron_evt14->Fill(myEvent.ElectronTime14);
  }
  unsigned int mysizeG14 = myTreeG14->GetEntries();

  for (unsigned int i = 0; i < mysizeG14; ++i) {
    myTreeG14->GetEntry(i);
    gamma_evt14->Fill(myEvent.GammaTime14);
  }
  //---------------------------------------------------------

  unsigned int mysizeE15 = myTreeE15->GetEntries();

  for (unsigned int i = 0; i < mysizeE15; ++i) {
    myTreeE15->GetEntry(i);
    electron_evt15->Fill(myEvent.ElectronTime15);
  }
  unsigned int mysizeG15 = myTreeG15->GetEntries();

  for (unsigned int i = 0; i < mysizeG15; ++i) {
    myTreeG15->GetEntry(i);
    gamma_evt15->Fill(myEvent.GammaTime15);
  }
  //---------------------------------------------------------

  unsigned int mysizeE16 = myTreeE16->GetEntries();

  for (unsigned int i = 0; i < mysizeE16; ++i) {
    myTreeE16->GetEntry(i);
    electron_evt16->Fill(myEvent.ElectronTime16);
  }
  unsigned int mysizeG16 = myTreeG16->GetEntries();

  for (unsigned int i = 0; i < mysizeG16; ++i) {
    myTreeG16->GetEntry(i);
    gamma_evt16->Fill(myEvent.GammaTime16);
  }
  //---------------------------------------------------------
 
  unsigned int mysizeE17 = myTreeE17->GetEntries();

  for (unsigned int i = 0; i < mysizeE17; ++i) {
    myTreeE17->GetEntry(i);
    electron_evt17->Fill(myEvent.ElectronTime17);
  }
  unsigned int mysizeG17 = myTreeG17->GetEntries();

  for (unsigned int i = 0; i < mysizeG17; ++i) {
    myTreeG17->GetEntry(i);
    gamma_evt17->Fill(myEvent.GammaTime17);
  }
  //---------------------------------------------------------
 
  unsigned int mysizeE18 = myTreeE18->GetEntries();

  for (unsigned int i = 0; i < mysizeE18; ++i) {
    myTreeE18->GetEntry(i);
    electron_evt18->Fill(myEvent.ElectronTime18);
  }
  unsigned int mysizeG18 = myTreeG18->GetEntries();

  for (unsigned int i = 0; i < mysizeG18; ++i) {
    myTreeG18->GetEntry(i);
    gamma_evt18->Fill(myEvent.GammaTime18);
  }
  //---------------------------------------------------------
 
  unsigned int mysizeE19 = myTreeE19->GetEntries();

  for (unsigned int i = 0; i < mysizeE19; ++i) {
    myTreeE19->GetEntry(i);
    electron_evt19->Fill(myEvent.ElectronTime19);
  }
  unsigned int mysizeG19 = myTreeG19->GetEntries();

  for (unsigned int i = 0; i < mysizeG19; ++i) {
    myTreeG19->GetEntry(i);
    gamma_evt19->Fill(myEvent.GammaTime19);
  }
  
  //---------------------------------------------------------

  /*
  auto canvas = new TCanvas("c","c");

  electron_evt1->Draw();
  gamma_evt1->Draw();
  canvas->Draw();
 
  */
  //---------------------------------------------------------------
 
 

  
  
  //Creating Canvas and Stack placeholders. 
  auto canvas_1 = new TCanvas("canvas1","canvas1");
  
  auto hs0 = new THStack("hs0", "Timing of Photons hitting PMT in Event 0;Time of Photon hits (ns);Photon Counts");
  gStyle->SetPalette(kRainBow);
  electronevt0->SetLineColor(kWhite);
  gammaevt0->SetLineColor(kWhite);
  
  hs0->Add(electronevt0);
  hs0->Add(gammaevt0);
  
    
  //hs0->Draw("HIST pfc nostack");

  
  
  
  auto hs1 = new THStack("hs1", "Timing of Photons hitting PMT in Event 1;Time of Photon hits (ns);Photon Counts");
  gStyle->SetPalette(kRainBow);
  electron_evt1->SetLineColor(kWhite);
  gamma_evt1->SetLineColor(kWhite);
  
  hs1->Add(electron_evt1);
  hs1->Add(gamma_evt1);
 
  //hs1->Draw("HIST pfc nostack");
  //canvas_new->Draw();
  
  
 auto hs2 = new THStack("hs2", "Timing of Photons hitting PMT in Event 2;Time of Photon hits (ns);Photon Counts");
  gStyle->SetPalette(kRainBow);
  electron_evt2->SetLineColor(kWhite);
  gamma_evt2->SetLineColor(kWhite);
  
  hs2->Add(electron_evt2);
  hs2->Add(gamma_evt2);
 
  //hs2->Draw("HIST pfc nostack");

  
 auto hs3 = new THStack("hs3", "Timing of Photons hitting PMT in Event 3;Time of Photon hits (ns);Photon Counts");
  gStyle->SetPalette(kRainBow);
  electron_evt3->SetLineColor(kWhite);
  gamma_evt3->SetLineColor(kWhite);
  
  hs3->Add(electron_evt3);
  hs3->Add(gamma_evt3);
 
  // hs3->Draw("HIST pfc nostack");
  
  canvas_1->Divide(2,2);
  
  canvas_1->cd(1);
  hs0->Draw("HIST pfc nostack");
  canvas_1->cd(2);
  hs1->Draw("HIST pfc nostack");
  canvas_1->cd(3);
  hs2->Draw("HIST pfc nostack");
  canvas_1->cd(4);
  hs3->Draw("HIST pfc nostack");


  canvas_1->SetCanvasSize(1600,1600);
  canvas_1->SetWindowSize(400,400);
  canvas_1->Draw();
  
  canvas_1->Print("Set0-3.png");
  //canvas_1->Close();
  
  //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
 auto canvas_2 = new TCanvas("canvas2","canvas2");
 
 auto hs4 = new THStack("hs4", "Timing of Photons hitting PMT in Event 4;Time of Photon hits (ns);Photon Counts");
  gStyle->SetPalette(kRainBow);
  electron_evt4->SetLineColor(kWhite);
  gamma_evt4->SetLineColor(kWhite);
  
  hs4->Add(electron_evt4);
  hs4->Add(gamma_evt4);
 
  //hs4->Draw("HIST pfc nostack");


 auto hs5 = new THStack("hs5", "Timing of Photons hitting PMT in Event 5;Time of Photon hits (ns);Photon Counts");
  gStyle->SetPalette(kRainBow);
  electron_evt5->SetLineColor(kWhite);
  gamma_evt5->SetLineColor(kWhite);
  
  hs5->Add(electron_evt5);
  hs5->Add(gamma_evt5);
 
  //hs5->Draw("HIST pfc nostack");


 auto hs6 = new THStack("hs6", "Timing of Photons hitting PMT in Event 6;Time of Photon hits (ns);Photon Counts");
  gStyle->SetPalette(kRainBow);
  electron_evt6->SetLineColor(kWhite);
  gamma_evt6->SetLineColor(kWhite);
  
  hs6->Add(electron_evt6);
  hs6->Add(gamma_evt6);
 
  //hs6->Draw("HIST pfc nostack");



 auto hs7 = new THStack("hs7", "Timing of Photons hitting PMT in Event 7;Time of Photon hits (ns);Photon Counts");
  gStyle->SetPalette(kRainBow);
  electron_evt7->SetLineColor(kWhite);
  gamma_evt7->SetLineColor(kWhite);
  
  hs7->Add(electron_evt7);
  hs7->Add(gamma_evt7);
 
  //hs7->Draw("HIST pfc nostack");
  canvas_2->SetCanvasSize(1600,1600);
  canvas_2->SetWindowSize(400,400);
  canvas_2->Draw();

  canvas_2->Divide(2,2);
  
  canvas_2->cd(1);
  hs4->Draw("HIST pfc nostack");
  canvas_2->cd(2);
  hs5->Draw("HIST pfc nostack");
  canvas_2->cd(3);
  hs6->Draw("HIST pfc nostack");
  canvas_2->cd(4);
  hs7->Draw("HIST pfc nostack");


  
  canvas_2->Print("Set4-7.png");
  //canvas_2->Close();
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
 auto canvas_3 = new TCanvas("canvas3","canvas3");
 auto hs8 = new THStack("hs8", "Timing of Photons hitting PMT in Event 8;Time of Photon hits (ns);Photon Counts");
  gStyle->SetPalette(kRainBow);
  electron_evt8->SetLineColor(kWhite);
  gamma_evt8->SetLineColor(kWhite);
  
  hs8->Add(electron_evt8);
  hs8->Add(gamma_evt8);
 
  //hs8->Draw("HIST pfc nostack");



 auto hs9 = new THStack("hs9", "Timing of Photons hitting PMT in Event 9;Time of Photon hits (ns);Photon Counts");
  gStyle->SetPalette(kRainBow);
  electron_evt9->SetLineColor(kWhite);
  gamma_evt9->SetLineColor(kWhite);
  
  hs9->Add(electron_evt9);
  hs9->Add(gamma_evt9);
 
  //hs9->Draw("HIST pfc nostack");

  
auto hs10 = new THStack("hs10", "Timing of Photons hitting PMT in Event 10;Time of Photon hits (ns);Photon Counts");
  gStyle->SetPalette(kRainBow);
  electron_evt10->SetLineColor(kWhite);
  gamma_evt10->SetLineColor(kWhite);
  
  hs10->Add(electron_evt10);
  hs10->Add(gamma_evt10);
 
  //hs10->Draw("HIST pfc nostack");


auto hs11 = new THStack("hs11", "Timing of Photons hitting PMT in Event 11;Time of Photon hits (ns);Photon Counts");
  gStyle->SetPalette(kRainBow);
  electron_evt11->SetLineColor(kWhite);
  gamma_evt11->SetLineColor(kWhite);
  
  hs11->Add(electron_evt11);
  hs11->Add(gamma_evt11);
 
  // hs11->Draw("HIST pfc nostack");
  canvas_3->SetCanvasSize(1600,1600);
  canvas_3->SetWindowSize(400,400);
  canvas_3->Draw();

  canvas_3->Divide(2,2);
  
  canvas_3->cd(1);
  hs8->Draw("HIST pfc nostack");
  canvas_3->cd(2);
  hs9->Draw("HIST pfc nostack");
  canvas_3->cd(3);
  hs10->Draw("HIST pfc nostack");
  canvas_3->cd(4);
  hs11->Draw("HIST pfc nostack");



  
  canvas_3->Print("Set8-11.png");
  //canvas_3->Close();
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

auto canvas_4 = new TCanvas("canvas4","canvas4");
auto hs12 = new THStack("hs12", "Timing of Photons hitting PMT in Event 12;Time of Photon hits (ns);Photon Counts");
  gStyle->SetPalette(kRainBow);
  electron_evt12->SetLineColor(kWhite);
  gamma_evt12->SetLineColor(kWhite);
  
  hs12->Add(electron_evt12);
  hs12->Add(gamma_evt12);
 
  //hs12->Draw("HIST pfc nostack");


  
auto hs13 = new THStack("hs13", "Timing of Photons hitting PMT in Event 13;Time of Photon hits (ns);Photon Counts");
  gStyle->SetPalette(kRainBow);
  electron_evt13->SetLineColor(kWhite);
  gamma_evt13->SetLineColor(kWhite);
  
  hs13->Add(electron_evt13);
  hs13->Add(gamma_evt13);
 
  //hs13->Draw("HIST pfc nostack");

  
auto hs14 = new THStack("hs14", "Timing of Photons hitting PMT in Event 14;Time of Photon hits (ns);Photon Counts");
  gStyle->SetPalette(kRainBow);
  electron_evt14->SetLineColor(kWhite);
  gamma_evt14->SetLineColor(kWhite);
  
  hs14->Add(electron_evt14);
  hs14->Add(gamma_evt14);
 
  //hs14->Draw("HIST pfc nostack");


auto hs15 = new THStack("hs15", "Timing of Photons hitting PMT in Event 15;Time of Photon hits (ns);Photon Counts");
  gStyle->SetPalette(kRainBow);
  electron_evt15->SetLineColor(kWhite);
  gamma_evt15->SetLineColor(kWhite);
  
  hs15->Add(electron_evt15);
  hs15->Add(gamma_evt15);
 
  //hs15->Draw("HIST pfc nostack");
  canvas_4->SetCanvasSize(1600,1600);
  canvas_4->SetWindowSize(400,400);
  canvas_4->Draw();
  
  canvas_4->Divide(2,2);
  
  canvas_4->cd(1);
  hs12->Draw("HIST pfc nostack");
  canvas_4->cd(2);
  hs13->Draw("HIST pfc nostack");
  canvas_4->cd(3);
  hs14->Draw("HIST pfc nostack");
  canvas_4->cd(4);
  hs15->Draw("HIST pfc nostack");



  
  canvas_4->Print("Set12-15.png");
  //canvas_4->Close();

  //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
  auto canvas_5 = new TCanvas("canvas5","canvas5");
  auto hs16 = new THStack("hs16", "Timing of Photons hitting PMT in Event 16;Time of Photon hits (ns);Photon Counts");
  gStyle->SetPalette(kRainBow);
  electron_evt16->SetLineColor(kWhite);
  gamma_evt16->SetLineColor(kWhite);
  
  hs16->Add(electron_evt16);
  hs16->Add(gamma_evt16);
 
  //hs16->Draw("HIST pfc nostack");


  auto hs17 = new THStack("hs17", "Timing of Photons hitting PMT in Event 17;Time of Photon hits (ns);Photon Counts");
  gStyle->SetPalette(kRainBow);
  electron_evt17->SetLineColor(kWhite);
  gamma_evt17->SetLineColor(kWhite);
  
  hs17->Add(electron_evt17);
  hs17->Add(gamma_evt17);
 
  //hs17->Draw("HIST pfc nostack");



  auto hs18 = new THStack("hs18", "Timing of Photons hitting PMT in Event 18;Time of Photon hits (ns);Photon Counts");
  gStyle->SetPalette(kRainBow);
  electron_evt18->SetLineColor(kWhite);
  gamma_evt18->SetLineColor(kWhite);
  
  hs18->Add(electron_evt18);
  hs18->Add(gamma_evt18);
 
  //hs18->Draw("HIST pfc nostack");

  
  auto hs19 = new THStack("hs19", "Timing of Photons hitting PMT in Event 19;Time of Photon hits (ns);Photon Counts");
  gStyle->SetPalette(kRainBow);
  electron_evt19->SetLineColor(kWhite);
  gamma_evt19->SetLineColor(kWhite);
  
  hs19->Add(electron_evt19);
  hs19->Add(gamma_evt19);
 
  // hs19->Draw("HIST pfc nostack");
  canvas_5->SetCanvasSize(1600,1600);
  canvas_5->SetWindowSize(400,400);
  canvas_5->Draw();

  canvas_5->Divide(2,2);
  
  canvas_5->cd(1);
  hs16->Draw("HIST pfc nostack");
  canvas_5->cd(2);
  hs17->Draw("HIST pfc nostack");
  canvas_5->cd(3);
  hs18->Draw("HIST pfc nostack");
  canvas_5->cd(4);
  hs19->Draw("HIST pfc nostack");
  
  canvas_5->Print("Set16-19.png");
  //canvas_5->Close();
  //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------   

  
  //canvas_new->Divide(2,2);
  /*
    canvas_new->cd(1);
    hs0->Draw("HIST pfc nostack");
    canvas_new->cd(2);
    hs1->Draw("HIST pfc nostack");
    canvas_new->cd(3);
    hs2->Draw("HIST pfc nostack");
    canvas_new->cd(4);
    hs3->Draw("HIST pfc nostack");
    canvas_new->cd(5);
    hs4->Draw("HIST pfc nostack");
    canvas_new->cd(6);
    hs5->Draw("HIST pfc nostack");
    canvas_new->cd(7);
    hs6->Draw("HIST pfc nostack");
    canvas_new->cd(8);
    hs7->Draw("HIST pfc nostack");
    canvas_new->cd(9);
    hs8->Draw("HIST pfc nostack");
    canvas_new->cd(10);
    hs9->Draw("HIST pfc nostack");
    canvas_new->cd(11);
    hs10->Draw("HIST pfc nostack");
    canvas_new->cd(12);
    hs11->Draw("HIST pfc nostack");
    canvas_new->cd(13);
    hs12->Draw("HIST pfc nostack");
    canvas_new->cd(14);
    hs13->Draw("HIST pfc nostack");
    canvas_new->cd(15);
    hs14->Draw("HIST pfc nostack");
    canvas_new->cd(16);
    hs15->Draw("HIST pfc nostack");
    canvas_new->cd(17);
    hs16->Draw("HIST pfc nostack");
    canvas_new->cd(18);
    hs17->Draw("HIST pfc nostack");
    canvas_new->cd(19);
    hs18->Draw("HIST pfc nostack");
    canvas_new->cd(20);
    hs19->Draw("HIST pfc nostack");
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











