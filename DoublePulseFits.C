// This program will evaluate the data created by Neutrino Double Pulses
// It will fit both peaks using a Landau function and output the parameters to a CSV file
#include <math.h>
#include <fstream>



void DoublePulseFit() {  // file for opening
  
  //First Hist to Open

  string nameFile = "NeutrinoPulse";
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
  struct eventStruct{
    Float_t DoubleTimes;
   

    
  };
  eventStruct myEvent;

  
  TTree*myTreeE0;

  //Initializing the number of events that it should be reading
  int numberOfEvents = 10;


  //Looping over all of the events Data.
  for(unsigned int i = 1; i <= 10; ++i)
    {
  
  
      //Using a method to read in each of our NTuples given the same index number of our loop.
      string indexstr = std::to_string(i);
      const string name = "Neutrino Double Pulses Event 0;" + indexstr;

      const char *nameNew = name.c_str();

      myFile->GetObject(nameNew,myTreeE0);
      myTreeE0->SetBranchAddress("DoublePulse", &(myEvent.DoubleTimes) );
      gROOT->ForceStyle();
  
  
  
 

  
      //First finding the total size of the data that was read in, and then finding the maximum time value so we can preset our Histograms.
  unsigned int mysizeE0 = myTreeE0->GetEntries();
 
  
  Float_t max = 0;

  for (unsigned int i = 0; i < mysizeE0; ++i) {
    myTreeE0->GetEntry(i);
   
    if(myEvent.DoubleTimes>max)
      {
	max = myEvent.DoubleTimes;
      }
  }

  TH1D* Neutrino = new TH1D(nameNew,"", floor((max+301)/5), 0, max+300);



  //Grabing data from NTupel and placing it within the histogram
  for (unsigned int i = 0; i < mysizeE0; ++i) {
    myTreeE0->GetEntry(i);
   
    
    Neutrino->Fill(myEvent.DoubleTimes);
  }

  
  
  //Defining the total number of peaks that it should be seeing
  Int_t npeaks = 2;

  //Using TSpectrum to search our data and find at least two peaks to estimate the position of our fits
  TSpectrum *s = new TSpectrum(npeaks);
  Int_t nfound = s->Search(Neutrino,2,"",0.10);

  //cout << nfound << endl;

  Double_t*xpos;
  
  xpos = s->GetPositionX();


  Double_t xposition = 0;
  
  //Making sure that we get the corresponding x value for our gamma peak which will occur after the electron peak always. 
  if(xpos[0] > 100)
    {
      xposition = xpos[0];
    }
  else
    {
      xposition = xpos[1];
    }
  
  

  
  //Setting some upper limit to our fit based on the position of the peaks.
  unsigned int upperB =  std::max((xposition+400) , (xposition * 1.25));

  
  //Creating a fit function using two Landau functions
  TF1* NeuFits = new TF1("NeuFit", " (([0])*(TMath::Landau(x,[1],[2])))+ (([3])*(TMath::Landau(x,[4],[5])))", 0 ,upperB);
  NeuFits->SetParNames("Electron Peak","mpv electron","scale electron", "Gamma Peak", "mpv","scale gamma");
  NeuFits->SetParameters(100,0, 1 , 500, xposition,1);
  //Fixing our mpv gamma value to be the xpositon of the corresponding peak. We don't want it moving too much and it is a good guess for our data.
  NeuFits->FixParameter(4,xposition);
  NeuFits->SetLineColor(4);


  
     

  
  Double_t par[6];
  
  //auto canvas = new TCanvas("c","c");

  //Fitting our Histogram to the function that we defined.
  Neutrino->Fit(NeuFits, "R");
  //Grabbing the parameters of our fit functino and placing the values in par[]
  NeuFits ->GetParameters(&par[0]);

  //canvas->Draw();
  

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


  












