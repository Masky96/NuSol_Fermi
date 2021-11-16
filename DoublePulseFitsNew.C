// This program will evaluate the data created by Neutrino Double Pulses
// It will fit both peaks using a Landau function and output the parameters to a CSV file
#include <math.h>
#include <fstream>
#include <algorithm>



void DoublePulseFitNew() {  // file for opening
  
  //First Hist to Open

  string nameFile = "Tutorial";
  string nameFRoot = nameFile + ".root";

  const char *nameFRoot2 = nameFRoot.c_str();
  
  string nameFCSV = nameFile + ".csv";

  const char *nameFCSV2 = nameFCSV.c_str();
  
  
  //Opening the Neutrino Data from a root file
  TFile* myFile = TFile::Open(nameFRoot2);
  

  //Preparing paring the data and CSV file
  
  ofstream data;
  data.open(nameFCSV2);

  data << "Elec Peak Const"                             << ','
       << "Most Probable Value Elec (ns)"               << ','
       << "Sigma Elec (Multiplier)"                     << ','
       << "Gamma Peak Const"                            << ','
       << "Most Probable Value Gamm (ns)"               << ','
       << "Sigma Gamma (Multiplier)"                    << ','
       << "Corrected Height Electron"                   << ','
       << "Corrected Height Gamma"                      << ','
       << endl;
  
  //Counstructing our event and TTree's to read in
  


  
  //Initializing the number of events that it should be reading
  int numberOfEvents = 10;


  //Looping over all of the events Data.
  for(unsigned int i = 0; i < numberOfEvents; ++i)
    {
  
  
      //Using a method to read in each of our NTuples given the same index number of our loop.
      string indexstr = std::to_string(i);
      const string name = "Neutrino Double Pulses Event" + indexstr + ";1";

      const char *nameNew = name.c_str();
  
    TH1D* Neutrino = new TH1D(nameNew,"", 101, -10, 1000);
    Neutrino = (TH1D*)myFile->Get(nameNew);

    


 
    
  //Defining the total number of peaks that it should be seeing
  Int_t npeaks = 2;

  //Using TSpectrum to search our data and find at least two peaks to estimate the position of our fits
  TSpectrum *s = new TSpectrum(npeaks);
  Int_t nfound = s->Search(Neutrino,2,"",0.10);

  //cout << nfound << endl;

  Double_t*xpos;
  
  xpos = s->GetPositionX();


  Double_t xposition = 0;
  
  
  //Use this for shorter decay time.
if(xpos[0] > 50)
    {
      xposition = xpos[0];
    }
  else
    {
      xposition = xpos[1];
    }

  
  

  
  //Setting some upper limit to our fit based on the position of the peaks.
 unsigned int upperB =  std::max(xposition+400 , xposition * 1.25);

  
  //Creating a fit function using two Landau functions
  TF1* NeuFits = new TF1("NeuFit", " (([0])*(TMath::Landau(x,[1],[2])))+ (([3])*(TMath::Landau(x,[4],[5])))", -10 ,upperB);
  NeuFits->SetParNames("Electron Peak","mpv electron","scale electron", "Gamma Peak", "mpv","scale gamma");
  
  NeuFits->SetParameters(100,0 , 1 , 200, xposition,1);
  //Fixing our mpv gamma value to be the xpositon of the corresponding peak. We don't want it moving too much and it is a good guess for our data.
  NeuFits->FixParameter(1, 0);
  NeuFits->FixParameter(4,xposition);
  NeuFits->SetLineColor(4);
  NeuFits->SetNpx(1000);
    
  
     

  
  Double_t par[6];
  
  auto canvas = new TCanvas("Canvas","Canvas");

    gROOT->ForceStyle();
    
    Neutrino->SetFillColor(kGreen);
    
  
    //Fitting our Histogram to the function that we defined.
    Neutrino->Fit(NeuFits,"Q","bar1");
    
    //Grabbing the parameters of our fit functino and placing the values in par[]
    NeuFits ->GetParameters(&par[0]);

  

  const string pName = name + ".png";
  const char *printName = pName.c_str();


  //canvas->Draw("bar1");
  canvas->Print(printName);

  //Calculating the overall peak of the landau functions respectively because we already have the function defined here.
  Double_t elecPeak = (par[0])*TMath::Landau(par[1], par[1], par[2]);
  Double_t gamPeak = (par[3])*TMath::Landau(par[4],par[4],par[5]);
  
  //Taking the parameters and placing them into our CSV file that we can later manipulate.
  data << par[0]     << ','
       << par[1]     << ','
       << par[2]     << ','
       << par[3]     << ','
       << par[4]     << ','
       << par[5]     << ','
       << elecPeak   << ','
       << gamPeak    << ','
       << endl;
    
   }
  data.close();
}


  












