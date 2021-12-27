// This program will evaluate the data created by Neutrino Double Pulses
// It will fit both peaks using a Landau function and output the parameters to a CSV file
#include <math.h>
#include <fstream>
#include <algorithm>







void FitPulseElecGamTEST() {  // file for opening
  
  //First Hist to Open

  string nameFileElectron = "nu_e+34+2+Electron";
  string nameFileGamma    = "nu_e+34+2+Gamma";
  string name             = "nu_e+34+2";

  
  string nameFRootElec  = nameFileElectron + ".root";
  string nameFRootGamma = nameFileGamma    + ".root";

  const char *nameFRoot2Elec = nameFRootElec.c_str();
  const char *nameFRoot2Gam = nameFRootGamma.c_str();

  
  
  string nameFCSV = name + ".csv";

  const char *nameFCSV2 = nameFCSV.c_str();
  
  
  //Opening the Neutrino Data from a root file
  TFile* myFileElec = TFile::Open(nameFRoot2Elec);
  TFile* myFileGamm = TFile::Open(nameFRoot2Gam);
  

  //Preparing paring the data and CSV file
  ofstream data;
  data.open(nameFCSV2);
  
  data << "Electron Pulse Single"                               << ','
       << "Most Probable Value Elec Single (ns)"                << ','
       << "Sigma Elec Single(Multiplier)"                       << ','
       << "Gamma Peak Const Single"                             << ','
       << "Most Probable Value Gammma Single (ns)"              << ','
       << "Sigma Gamma Single (Multiplier)"                     << ','
       << "Elec Peak Const Combined"                            << ','
       << "Most Probable Value Elec Combined (ns)"              << ','
       << "Sigma Elec Combined(Multiplier)"                     << ','
       << "Gamma Peak Const Combined"                           << ','
       << "Most Probable Value Gammma Combined (ns)"            << ','
       << "Sigma Gamma Combined(Multiplier)"                    << ','
       << "Interesting Check"                                   << ','
       << "Checking if there was a gamma"                       << ','
       << "Correctly Measured Double Pulses String"             <<  ','
       << "Double pulses that were measured as singles String " <<  ','
       << "Correctly measured single pulses String "            << ','
       << "Non-Characterized Pulse String"                      << ','
       << "Fake Double Pulses String"                           << ','
       << "Number of Interesting Events"                        << ','
       << "Known Double Pulses"                                 <<  ','
       << "Correctly Measured Double Pulses"                    <<  ','
       << "Double pulses that were measured as singles"         <<  ','
       << "Known Single Pulses"                                 <<  ','
       << "Correctly measured single pulses"                    << ','
       << "Fake Double Pulses OR Combined"                                  << ','
       << "Number of events that nothing happend"               << ','
       << "Pulses that weren't Characterized"                    << ','
       << endl;
  
      

  
  //Counstructing our event and TTree's to read in 
  struct eventStruct{
    Float_t ElectronTimes;
    Float_t GammaTimes;
   

    
  };
  eventStruct myEvent;
  
  

  
  TTree*myTreeE0;
  TTree*myTreeG0;

  //Initializing the number of events that it should be reading
  int numberOfEvents = 1000;

  Int_t knownDouble    = 0;
  Int_t DoubleDouble   = 0;
  Int_t DoubleSingle   = 0;
  Int_t knownSingle    = 0;
  Int_t SingleSingle   = 0;
  Int_t SingleDouble   = 0;
  Int_t numInteresting = 0;

  Int_t NoEvent = 0;
  Int_t gamFailCount =0;

  
  //Looping over all of the events Data.
  for(unsigned int i = 1; i <= numberOfEvents; ++i)
    {
  
  
      //Using a method to read in each of our NTuples given the same index number of our loop.
      string indexstr = std::to_string(i);
      const string nameElec = "Neutrino Double Pulses Event 0;" + indexstr;
      const string nameGam =  "Neutrino Double Pulses Event 0;" + indexstr;
      const string nameCom =  "Neutrino Double Pulses Event 0;" + indexstr;

      
      const char *nameNewElec      = nameElec.c_str();
      const char *nameNewGam   = nameGam.c_str();
      

      myFileElec->GetObject(nameNewElec,myTreeE0);
      myTreeE0->SetBranchAddress("SinglePulse", &(myEvent.ElectronTimes) );

      myFileGamm->GetObject(nameNewGam,myTreeG0);
      myTreeG0->SetBranchAddress("SinglePulse", &(myEvent.GammaTimes) );






      const string elecName = nameElec + "Electron";
      const char *elecNamechar = elecName.c_str();

      const string gammaName = nameGam + "Gamma";
      const char *gamNamechar = gammaName.c_str();

      
      const string combinedName = nameCom +" Combined";
      const char *nameCombined = combinedName.c_str();
      
      gROOT->ForceStyle();
  
  
  
      //First finding the total size of the data that was read in, and then finding the maximum time value so we can preset our Histograms.

      
      unsigned int mysizeE0 = myTreeE0->GetEntries();
      unsigned int mysizeG0 = myTreeG0->GetEntries();
  
  Float_t maximum = 0;

  for (unsigned int i = 0; i < mysizeG0; ++i) {
    myTreeG0->GetEntry(i);
   
    if(myEvent.GammaTimes>maximum)
      {
	maximum = myEvent.GammaTimes;
      }
  }

  
  Float_t maxNew = floor(maximum);

  Int_t extra = static_cast<int>(maximum)%10;

  maximum = maxNew - extra + 300;





  
  TH1D* Gamma    = new TH1D(elecNamechar,"Gamma", maximum/10+2, -20, maximum);
  TH1D* Electron = new TH1D(gamNamechar,"Electron", maximum/10+2, -20, maximum);
  
  TH1D* Combined  = new TH1D(nameCombined,"Combined Neutrino Events",maximum/10+2, -20, maximum);
  


  
  //Grabing data from NTupel and placing it within the histogram
  for (unsigned int i = 0; i < mysizeE0; ++i)
    {
      myTreeE0->GetEntry(i);
   
    
      Electron->Fill(myEvent.ElectronTimes);
      
    
    }


  for (unsigned int i = 0; i < mysizeG0; ++i)
    {
      myTreeG0->GetEntry(i);
   
    
      Gamma->Fill(myEvent.GammaTimes);
      
    }


  Combined-> Add(Electron,Gamma);

  


auto canvas = new TCanvas("canvas1","canvas1");

  

  //Defining the total number of peaks that it should be seeing
  Int_t npeaks = 2;

  //Using TSpectrum to search our data and find at least two peaks to estimate the position of our fits
  TSpectrum *s = new TSpectrum(npeaks);
  Int_t nfound = s->Search(Combined,2,"",0.1);


  Double_t*xpos;
  
  xpos = s->GetPositionX();


  Double_t xposition = 0;
  Double_t fpeak = 0;
  
  //Making sure that we get the corresponding x value for our gamma peak which will occur after the electron peak always.

  //Good Criteria for the later decays, if it is the 79ns then set decay time limit to 50



  //cout << xpos[0] << " and " << xpos[1] << endl;

  Double_t firstpeak = 0;
  Double_t secondpeak = 0;

  if(xpos[0] < xpos[1])
    {
      firstpeak = xpos[0];
      secondpeak = xpos[1];
    }
  else if(xpos[1] == 0 && xpos[0] == 25 )
    {
      firstpeak = xpos[0];
      secondpeak = 400;
    }
  else if(xpos[1] == 25 && xpos[0] == 0)
    {
      firstpeak = xpos[1];
      secondpeak = 400;
    }
  else
    {
      firstpeak = xpos[1];
      secondpeak = xpos[0];
    }
 
  /*
  if(xpos[1] > 50)
    {
      xposition = xpos[1];
      fpeak = xpos[0];
    }
  else
    {
      xposition = 600;
    }
  */



  
  //Setting some upper limit to our fit based on the position of the peaks.
 unsigned int upperB =  std::max(secondpeak+300 , secondpeak * 1.25);
 //unsigned int upperBElectron =  std::max(fpeak+400 , fpeak * 1.25);

 
 //----------------------------------------------------------------------------------------------------------------------------
 //Creating a separate Fit that will be used for the Electron and Gamma pulse.
 TF1* PulseFits = new TF1("Pulse Fit", " (([0])*(TMath::Landau(x,[1],[2])))", -20, upperB);
 PulseFits->SetParNames("Peak Guess","Most Probable Location","Scale Factor");
 PulseFits->SetParameters(200, firstpeak, 1);
 PulseFits->FixParameter(1,firstpeak);
 PulseFits->SetLineColor(4);
 PulseFits->SetNpx(1000);


 
 Double_t Epar[3];


 
 Electron->Fit(PulseFits,"Q","bar");
 //Grabbing the parameters of our fit function and placing the values in par[]
 PulseFits->GetParameters(&Epar[0]);
 /*
 cout << Epar[0]     << ','
      << Epar[1]     << ','
      << Epar[2]     << ','
      << endl;

 */
  
 //Creating a separate Fit that will be used for the Electron and Gamma pulse.
 TF1* PulseFitGam = new TF1("Pulse Fit Gam", " (([0])*(TMath::Landau(x,[1],[2])))", -20, upperB);
 PulseFitGam->SetParNames("Peak Guess","Most Probable Location","Scale Factor");
 PulseFitGam->SetParameters(200, secondpeak, 1);
 PulseFitGam->FixParameter(1,secondpeak);
 PulseFitGam->SetLineColor(4);
 PulseFitGam->SetNpx(1000);






  
 Double_t Gpar[3];
 
 
   
 Gamma->Fit(PulseFitGam,"Q","bar");
 

 
 //Grabbing the parameters of our fit function and placing the values in par[]
 PulseFitGam->GetParameters(&Gpar[0]);
 /*
 cout << Gpar[0]     << ','
      << Gpar[1]     << ','
      << Gpar[2]     << ','
      << endl;
 */

 //----------------------------------------------------------------------------------------------------------------------------
 


  
 
   //Creating a fit function using two Landau functions
  TF1* NeuFits = new TF1("NeuFit", " (([0])*(TMath::Landau(x,[1],[2])))+ (([3])*(TMath::Landau(x,[4],[5])))", -20 ,upperB);
  NeuFits->SetParNames("Electron Peak","mpv electron","scale electron", "Gamma Peak", "mpv","scale gamma");
  
  NeuFits->SetParameters(200, firstpeak, 1 , 200, secondpeak,1);
  NeuFits->FixParameter(1,firstpeak);
  NeuFits->FixParameter(4,secondpeak);
  NeuFits->SetLineColor(4);
  NeuFits->SetNpx(1000);
 
  
  Double_t par[6];
  
  


  
  Combined->SetFillColor(kGreen);
  
  //Fitting our Histogram to the function that we defined.
  Combined->Fit(NeuFits,"Q","bar");
  
  //Grabbing the parameters of our fit functino and placing the values in par[]
  NeuFits->GetParameters(&par[0]);

  
  
  const string pName = name + ".png";
  const char *printName = pName.c_str();

  
  //canvas->Draw();
  
  canvas->Print(nameCombined);

  //Calculating the overall peak of the landau functions respectively because we already have the function defined here.
  
 




  
  //---------------------------------------------------------------------------------------------------------------------------


  //Checking the parameters for failures and interesting events.
  //Here is our percent tolerance that we want to compare our parameters to. 
  Double_t percent = 0.5;


  //Creating intial variables for 0 being False and 1 being True
  Int_t  compEpar1 = 0;
  Int_t  compEpar2 = 0;
  Int_t  compEpar3 = 0;

  Int_t  compGpar1 = 0;
  Int_t  compGpar2 = 0;
  Int_t  compGpar3 = 0;


  Double_t rangeEpar1;
  Double_t rangeEpar2;
  Double_t rangeEpar3;

  Double_t rangeGpar1;
  Double_t rangeGpar2;
  Double_t rangeGpar3;



  Int_t compPeaks = 0;
  Double_t rangeLE;

  Double_t LandauPeakE1 = (Epar[0])*(TMath::Landau(firstpeak,Epar[1],Epar[2]));
  Double_t LandauPeakE2 = (par[0])*(TMath::Landau(firstpeak,par[1],par[2]));
  
  


  //Finding the range of each of our parameters that we will use to do our checks below. 
  rangeEpar1 = Epar[0]*percent;
  rangeEpar2 = Epar[1]*percent;
  rangeEpar3 = Epar[2]*percent;

  rangeGpar1 = Gpar[0]*percent;
  rangeGpar2 = Gpar[1]*percent;
  rangeGpar3 = Gpar[2]*percent;


  
  rangeLE = LandauPeakE1*percent;

  
  //Using statements to check if the parameters of the doublefit are within a tolerance range of the singular fits.
  if((par[0]-(Epar[0]-rangeEpar1))*(par[0]-(Epar[0]+rangeEpar1)) <= 0)
    {
      compEpar1 = 1;
      //cout << "We are within range" << endl;
    
    }

  if((par[1]-(Epar[1]-rangeEpar2))*(par[1]-(Epar[1]+rangeEpar2)) <= 0)
    {
      compEpar2 = 1;
      //cout << "We are within range" << endl;
    
    }
 
  if((par[2]-(Epar[2]-rangeEpar3))*(par[2]-(Epar[2]+rangeEpar3)) <= 0)
    {
      compEpar3 = 1;
      //cout << "We are within range" << endl;
    
    }

  if((par[3]-(Gpar[0]-rangeGpar1))*(par[3]-(Gpar[0]+rangeGpar1)) <= 0)
    {
      compGpar1 = 1;
      //cout << "We are within range" << endl;
    
    }
  if((par[4]-(Gpar[1]-rangeGpar2))*(par[4]-(Gpar[1]+rangeGpar2)) <= 0)
    {
      compGpar2 = 1;
      //cout << "We are within range" << endl;
    
    }

  if((par[5]-(Gpar[2]-rangeGpar3))*(par[5]-(Gpar[2]+rangeGpar3)) <= 0)
    {
      compGpar3 = 1;
      //cout << "We are within range" << endl;
    
    }

  if((LandauPeakE2-(LandauPeakE1-rangeLE))*(LandauPeakE2-(LandauPeakE1+rangeLE)) <= 0)
    {
      compPeaks = 1;
      //cout << "We are within range" << endl;
    
    }


  
  
  string DDFit = "";
  string DDNoFit = "";
  string SSFit = "";
  string SSNoFit = "";

  string gamCheck ="";
  string intCheck = "";

  string gamFailed = "";
  
  Int_t  interesting =0;
  
 
  /*
    if(((par[0]>0 && par[2] > 0) && (par[3] > 0 && par[5]>0)) && ((Epar[0] > 0 && Epar[2] >0) && (Gpar[0]>0 && Gpar[2]>0)))
    {
    DDFit = "Two Pulses were measured correctly";
    DoubleDouble++;
    }
  */

  //Gpar[0] > 0  && Gpar[2] > 0 &&





  /*
  if(((Epar[0] > 0 && Epar[2]>0) &&  Gpar[1] != 400) && ((compEpar1 == 1 && compEpar3 == 1) && (compGpar1 == 1 && compGpar3 == 1)) )
    {
      DDFit = "Two Pulses were measured correctly";
      DoubleDouble++;
    }
  */
 if(((Epar[0] > 0 && Epar[2]>0) &&  Gpar[1] != 400) && ((compPeaks == 1) && (compGpar1 == 1 && compGpar3 == 1)) )
    {
      DDFit = "Two Pulses were measured correctly";
      DoubleDouble++;
    }
  /*
  if(((Epar[0] > 0 && Epar[2]>0) && Gpar[1] != 400) && (compGpar1 == 0 || compGpar3 == 0 || compEpar1 == 0 || compEpar3 == 0) )
    {
      DDNoFit = "Two Pulses were not measured correctly";
      DoubleSingle++;
    }
  */
if(((Epar[0] > 0 && Epar[2]>0) && Gpar[1] != 400) && (compGpar1 == 0 || compGpar3 == 0) && compPeaks ==1 && mysizeG0 >20 )
    {
      DDNoFit = "Two Pulses were not measured correctly";
      DoubleSingle++;
 
    }
      /*
if(((Epar[0] > 0 && Epar[2]>0) && Gpar[1] == 400) && ((compEpar1 == 1 && compEpar3 == 1) && (compGpar1 == 0 && par[4] == 400 && (par[3] < 0 || par[5] < 0))) )
    {
      SSFit = "One pulse was measured correctly";
      SingleSingle++;
    }
 

  
  if(((Epar[0] > 0 && Epar[2] > 0) && Gpar[1] == 400) && ((compEpar1 == 1 && compEpar3 == 1) && (par[3] > 0 && par[5] >0 && par[4] != 400)) )
    {
      SSNoFit = "A Fake Double Pulse was measured"; 
      SingleDouble++;
    }
      */

 if(((Epar[0] > 0 && Epar[2]>0) && Gpar[1] == 400) && ((compPeaks == 1) && ((compGpar1 == 0 || compGpar3 == 0) && par[4] == 400 && (par[3] < 0 || par[5] < 0))) )
    {
      SSFit = "One pulse was measured correctly";
      SingleSingle++;
    }

 
 if(((Epar[0] > 0 && Epar[2] > 0) && mysizeG0 < 20) && ((compPeaks == 1) && (((par[3] > 0 || par[5] >0) &&  par[4] != 400) || ((par[3] > 0 && par[5] >0) && par[4] == 400 ))))
    {
      SSNoFit = "A Fake Double Pulse was measured"; 
      SingleDouble++;
    }



      
  if(mysizeE0 < 20 && mysizeG0 < 20)
    {
      NoEvent++;
    }

  if(mysizeG0 < 20)
    {
      gamCheck= "There was no gamma here";
    }

  cout << mysizeG0 << endl; 

  //Performing a logic check on each of the comparisons that were found above, and if Gpar[1] which is the most probable value for the gamma pulse was greater than 0 which means that there was a gamma pulse.

  
  if((compEpar1 == 0 || compEpar2 == 0 || compEpar3 == 0 || compGpar1 == 0 || compGpar2 == 0 || compGpar3 == 0) && (Gpar[1]>0 || (Gpar[1] == 0 && (Gpar[0] > 500 && Gpar[2] > 1))))
    {
      interesting = 1;
    }
 
  
  
  if(mysizeG0 >20 && DDFit == "" && DDNoFit == "" && SSFit == "" && SSNoFit == "")
    {
      gamFailed = "The program failed to detect or classify this gamma pulse";
      gamFailCount++;
    }
  
    //Now what we consider Interesting is that when we have one of our interesting cases from above, but also connected with there was a gamma pulse. This means that we need to check that file to make sure it fit correctly or if something was wrong. 
  if((interesting == 1 && gamCheck == "") && gamFailed == "")
    {
      intCheck = "Check Here";
      numInteresting++;	
    }
  



  cout << (Gpar[0])*(TMath::Landau(secondpeak,Gpar[1],Gpar[2])) << endl;
  cout << (par[3])*(TMath::Landau(secondpeak,par[4],par[5])) << endl;

  
  //Taking the parameters and placing them into our CSV file that we can later manipulate.
  data << Epar[0]     << ','
       << Epar[1]     << ','
       << Epar[2]     << ','
       << Gpar[0]     << ','
       << Gpar[1]     << ','
       << Gpar[2]     << ','
       << par[0]      << ','
       << par[1]      << ','
       << par[2]      << ','
       << par[3]      << ','
       << par[4]      << ','
       << par[5]      << ','
       << intCheck    << ','
       << gamCheck    << ',' 
       << DDFit       << ','
       << DDNoFit     << ','
       << SSFit       << ','
       << SSNoFit     << ','
       << gamFailed   << ','
       << ""          << ','
       << ""          <<  ','
       << ""          <<  ','
       << ""          <<  ','
       << ""          <<  ','
       << ""          << ','
       << ""          << ','
       << ""          << ','
       << ""          << ','
       
       << endl;
  
   }
  data << ""      << ','
       << ""      << ','
       << ""      << ','
       << ""      << ','
       << ""      << ','
       << ""      << ','
       << ""      << ','
       << ""      << ','
       << ""      << ','
       << ""      << ','
       << ""      << ','
       << ""      << ','
       << ""      << ','
       << ""      << ','
       << ""      << ','
       << ""      << ','
       << ""      << ','
       << ""      << ','
       << ""      << ','
       << numInteresting  << ','
       << knownDouble     <<  ','
       << DoubleDouble    <<  ','
       << DoubleSingle    <<  ','
       << knownSingle     <<  ','
       << SingleSingle    << ','
       << SingleDouble    << ','
       << NoEvent         << ','
       << gamFailCount    << ','
       << endl;
  data.close();
  //cout << "This is the total number of Truely positive Double Pulses: " << numberOfEvents -(numFakePulses+ NogamNum + numGamNoFit)  << endl;
  //cout << "Check the each of the interesting results and add the ones that did truly fit to your result: " << numInteresting << endl;
  
}


  












