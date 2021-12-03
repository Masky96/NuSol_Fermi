// This program will evaluate the data created by Neutrino Double Pulses
// It will fit both peaks using a Landau function and output the parameters to a CSV file
#include <math.h>
#include <fstream>
#include <algorithm>







void FitPulseElecGam() {  // file for opening
  
  //First Hist to Open

  string nameFileElectron = "nu_e+40+2+Electron";
  string nameFileGamma    = "nu_e+40+2+Gamma";
  string name             = "nu_e+40+2";

  
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
    //<< "Comparison Electron Peaks"                           << ','
    //<< "Comparison of Electron MPV"                          << ','
    // << "Comparison of Electron Sigma"                        << ','
    // << "Comparison Gamma Peaks"                              << ','
    // << "Comparison of Gamma MPV"                             << ','
    // << "Comparison of Gamma Sigma"                           << ','
       << "Interesting?"                                        << ','
       << "Binary Interesting"                                  << ','
       << "Gamma Check"                                         << ','
       << "Binary Gamma Check"                                  << ','
       << "Fake Gamma Check"                                    << ','
       << "Binary Fake Gam Check"                               << ','
       << "Did the Combined function fit?"                      << ','
       << "Binary Combined fit Check"                           << ','
       << "Total Number of Interesting Events"                  << ','
       << "Total Number of SS Events (True Singles)"            << ','
       << "Total Number of SD Events (False Doubles)"           << ','
       << "Total Number of DS Events (True Double, Measured Singles)" << ','
       << "Total Number including Corrections for Double Doubles"     << ','
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


  
  Int_t numInteresting = 0;
  Int_t numFakePulses = 0;
  Int_t numGamNoFit = 0;
  Int_t NogamNum = 0;
  Int_t numOfActualDoublePulses =0;
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
  Int_t nfound = s->Search(Combined,2,"",0.10);


  Double_t*xpos;
  
  xpos = s->GetPositionX();


  Double_t xposition = 0;
  Double_t fpeak = 0;
  
  //Making sure that we get the corresponding x value for our gamma peak which will occur after the electron peak always.

  //Good Criteria for the later decays, if it is the 79ns then set decay time limit to 50
  
  if(xpos[0] > 150)
    {
      xposition = xpos[0];
    }
  else
    {
      xposition = xpos[1];
      fpeak = xpos[0];
    }







  
  //Setting some upper limit to our fit based on the position of the peaks.
 unsigned int upperB =  std::max(xposition+300 , xposition * 1.25);
 //unsigned int upperBElectron =  std::max(fpeak+400 , fpeak * 1.25);

 
 //----------------------------------------------------------------------------------------------------------------------------
 //Creating a separate Fit that will be used for the Electron and Gamma pulse.
 TF1* PulseFits = new TF1("Pulse Fit", " (([0])*(TMath::Landau(x,[1],[2])))", -20, upperB);
 PulseFits->SetParNames("Peak Guess","Most Probable Location","Scale Factor");
 PulseFits->SetParameters(200, fpeak, 1);
 PulseFits->FixParameter(1,fpeak);
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
 PulseFitGam->SetParameters(200, xposition, 1);
 PulseFitGam->FixParameter(1,xposition);
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
  
  NeuFits->SetParameters(200, fpeak, 1 , 200, xposition,1);
  NeuFits->FixParameter(4,xposition);
  NeuFits->FixParameter(1,fpeak);
  NeuFits->SetLineColor(4);
  NeuFits->SetNpx(1000);
 
  
  Double_t par[6];
  



  /*
  Int_t eleId = 0;
  Int_t gammaId = 0;

  if(mysizeE0 >= 10)
  {
    eleId = 1;
  }
  if(mysizeG0 >= 10)
  {
    gammaId = 1;
  }


  if(eleId ==1)
    {
      cout << "We saw an electron pulse" << endl;
    }

  if(gammaId ==1)
    {
      cout << "We saw an gamma pulse" << endl;
    }
  */


  


  
  Combined->SetFillColor(kGreen);
  
  //Fitting our Histogram to the function that we defined.
  Combined->Fit(NeuFits,"Q","bar");
  
  //Grabbing the parameters of our fit functino and placing the values in par[]
  NeuFits->GetParameters(&par[0]);
  /*
  cout << par[0]     << ','
       << par[1]     << ','
       << par[2]     << ','
       << par[3]     << ','
       << par[4]     << ','
       << par[5]     << ','
       << endl;
  */
  
  
  const string pName = name + ".png";
  const char *printName = pName.c_str();

  
  //canvas->Draw();
  
  //canvas->Print(nameCombined);

  //Calculating the overall peak of the landau functions respectively because we already have the function defined here.
  
  //Double_t elecPeak = (par[0])*TMath::Landau(par[1], par[1], par[2]);
  //Double_t gamPeak = (par[3])*TMath::Landau(par[4],par[4],par[5]);




  
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
  


  //Finding the range of each of our parameters that we will use to do our checks below. 
  rangeEpar1 = Epar[0]*percent;
  rangeEpar2 = Epar[1]*percent;
  rangeEpar3 = Epar[2]*percent;

  rangeGpar1 = Gpar[0]*percent;
  rangeGpar2 = Gpar[1]*percent;
  rangeGpar3 = Gpar[2]*percent;


  
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






  
  //Using a comparison to find if any of the parameters did not match so we can classify them as interesting
  Int_t interesting = 0;
  Int_t GammaCheck = 0;
  Int_t FakePulse =0;
  Int_t GammaNoFit = 0;

  //Performing a logic check on each of the comparisons that were found above, and if Gpar[1] which is the most probable value for the gamma pulse was greater than 0 which means that there was a gamma pulse.

  
  if((compEpar1 == 0 || compEpar2 == 0 || compEpar3 == 0 || compGpar1 == 0 || compGpar2 == 0 || compGpar3 == 0) && (par[4]>0)) //par[3]>0 ||
    {
      interesting = 1;
    }
 

  //cout << interesting << endl; 


  //Making a string for our interesting case so I can easily find it in the spread sheet.
  string intCheck = "";
  
  string gamCheck = "";

  string fakegamCheck="";

  string noFitGamma = "";


  string CorrectDoublePulse = "";



  /*
    These are my Incremental variables
    Int_t numInteresting = 0;
    Int_t numFakePulses = 0;
    Int_t numGamNoFit = 0;
    Int_t NogamNum = 0;
  */

  /*
  //Initial check for if there was really no gamma pulse because it left the volume, so Gpar[1] = 0
  if(Gpar[1] ==0)
    {

      //This is the real amount of No Double Pulses Using Parameters
      if((par[3] < 0 || par[4] == 0 || par[5] < 0))
	{
      gamCheck = "There was no Gamma Pulse";
      NogamNum++;
      GammaCheck = 1;
	}
      
      if(par[3]>0 && par[5] > 0)
	{
	  fakegamCheck = "This was a fake Gamma Pulse";
	  numFakePulses++;
	  FakePulse =1;
	  
	}
      
      
    }
  */


  /*
  if(mysizeE0 > 15 && mysizeG0 > 15)
    {
      CorrectDoublePulse = "There was a confirmed Double Pulse";
      numOfActualDoublePulses++;
    }
  */
  if((Epar[0]>0 && Epar[2]>0) && (Gpar[0]>0 && Gpar[2]>0)
    {
      CorrectDoublePulse = "There was a confirmed Double Pulse";
      numOfActualDoublePulses++;
    }

















  
   if(mysizeG0 < 15)
    {

    
      gamCheck = "There was no Gamma Pulse";
      NogamNum++;
      GammaCheck = 1;

      
      if(par[3]>0 && par[5] > 0)
	{
	  fakegamCheck = "This was a fake Gamma Pulse";
	  numFakePulses++;
	  FakePulse =1;
	  
	}
      
      
    }
 
  //This one we can modify for what we consider is a fake pulse that is generated.

  //If we are not fixing the position of the first two fits then this is the boolean you want to use:
  /*
  if((par[3]<0 || par[5] < 0) && Gpar[1] != 0)
	{
	  noFitGamma = "The Combined Funciton could not fit the Gamma";
          numGamNoFit++;
	  GammaNoFit =1;
	}

  */

  
  //If you are fixing the position of each of the fits, then use this boolean. 
  
   if((par[3]<0 || par[5] < 0 || par[0]< 0|| par[2]<0) && (mysizeG0 >15))
	{
	  noFitGamma = "The Combined Funciton could not fit the Gamma";
          numGamNoFit++;
	  GammaNoFit =1;
	}
  
  //Now what we consider Interesting is that when we have one of our interesting cases from above, but also connected with there was a gamma pulse. This means that we need to check that file to make sure it fit correctly or if something was wrong. 
  if(interesting == 1 && gamCheck == "")
    {
      intCheck = "Check Here";
      numInteresting++;	
    }


  
  
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
       //<< compEpar1   << ','
       //<< compEpar2   << ','
       //<< compEpar3   << ','
       //<< compGpar1   << ','
       //<< compGpar2   << ','
       //<< compGpar3   << ','
       << intCheck    <<  ','
       << interesting <<  ','
       << gamCheck    <<  ','
       << GammaCheck  <<  ','
       << fakegamCheck << ','
       << FakePulse    << ','
       << noFitGamma   << ','
       << GammaNoFit   << ','
       << ""           << ','
       << ""           << ','
       << ""           << ','
       << ""           << ','
       << ""           << ','
       << ""           << ',' 
       
       << endl;
  
   }
   data << ""     << ','
       <<  ""     << ','
       <<  ""     << ','
	<< ""     << ','
       << ""      << ','
       << ""      << ','
       << ""      << ','
       << ""      << ','
       << ""      << ','
       << ""      << ','
       << ""      << ','
       << ""      << ','
       //<< compEpar1   << ','
       //<< compEpar2   << ','
       //<< compEpar3   << ','
       //<< compGpar1   << ','
       //<< compGpar2   << ','
       //<< compGpar3   << ','
       << ""      << ','
       << ""      << ','
       << ""      << ','
       << ""      << ','
       << ""      << ','
       << ""      << ','
       << ""      << ','
       << ""      << ','
       << numInteresting << ','
       << NogamNum     << ','
       << numFakePulses << ','
       << numGamNoFit   << ','
       << ""           << ',' 
       
       << endl;
  data.close();
  //cout << "This is the total number of Truely positive Double Pulses: " << numberOfEvents -(numFakePulses+ NogamNum + numGamNoFit)  << endl;
  //cout << "Check the each of the interesting results and add the ones that did truly fit to your result: " << numInteresting << endl;
  
}


  












