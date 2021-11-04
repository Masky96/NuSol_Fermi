// This program takes the outfile from the flight path out toward the
// neutrino gravitational focus and creates a stacked histogram 
#include <math.h>
#include <fstream>

/*
Double_t heaviexpofirst(Double_t *x, Double_t * par)
  {
    Float_t xx = x[0];
    Double_t theReturn =par[0]*exp(par[1]*xx);
   
    return theReturn;
  }
*/





void testFermi () {  // file for opening
  
  //First Hist to Open

  TFile* myFile = TFile::Open("Tutorial.root");
  


  ofstream data;
  data.open("Attempt1.csv");

  data << "Peak Max First"           << ','
       << "Decay Rate"               << ','
       << "Gamma Peak Parameter"     << ','
       << "Time of Gamma Peak ns"    << ','
       << "Scale Factor"             << ','
       << "Calculated Peak Height"   << ','
       << "Half max Height e-"       << ','
       << endl;
  struct eventStruct{
    Float_t DoubleTimes;
   

    
  };
  eventStruct myEvent;

  
  TTree*myTreeE0;
 
  int numberOfEvents = 10000;

  for(unsigned int i = 1; i <= 10; ++i)
    {
  
  string indexstr = std::to_string(i);
  //cout << indexstr << endl;
  const string name = "Neutrino Double Pulses Event 0;" + indexstr;

  const char *nameNew = name.c_str();
  
  myFile->GetObject(nameNew,myTreeE0);
  myTreeE0->SetBranchAddress("DoublePulse", &(myEvent.DoubleTimes) );
  gROOT->ForceStyle();
  
  
  
 

  
  
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


  
  for (unsigned int i = 0; i < mysizeE0; ++i) {
    myTreeE0->GetEntry(i);
   
    
    Neutrino->Fill(myEvent.DoubleTimes);
  }

  
  
  
  Int_t npeaks = 2;

  
  TSpectrum *s = new TSpectrum(npeaks);
  Int_t nfound = s->Search(Neutrino,2,"",0.10);

  //cout << nfound << endl;

  Double_t*xpos;
  
  xpos = s->GetPositionX();


  Double_t xposition = 0;
  

  if(xpos[0] > 100)
    {
      xposition = xpos[0];
    }
  else
    {
      xposition = xpos[1];
    }
  
  
  //cout << xposition << endl;
  //cout << xpos[0] << endl;
  





  
  
  /*
  TF1 *hifirst = new TF1("hifirst", "heaviexpofirst", 0, 800 ,2);
  hifirst->SetParNames("init peak", "rate of decay 1st");
  hifirst -> SetParameters(1000,-0.1);
  hifirst ->SetLineColor(1);
  

  std::max((xposition+200) , (xposition * 1.05));
  std::min((xposition-200) , (xposition * 0.95));
  
  unsigned int upperB =  ceil(std::max((xposition+200) , (xposition * 1.05)));
  cout << upperB << endl; 
  
  unsigned int lowerB = 0;
  if(xposition-200 > 0)
    {
    lowerB =  floor(std::min((xposition-200) , (xposition * 0.95)));
    }
  cout << lowerB << endl; 
  
  TF1 *hisecond = new TF1("hisecond", "([0])*(TMath::Landau(x,[1],[2]))", lowerB, upperB);
  hisecond->SetParNames("second peak","rate of decay 2nd","peak guess");
  hisecond->SetParameters(70,xposition,1);
  hisecond->SetLineColor(4);
  */
  
  unsigned int upperB =  std::max((xposition+200) , (xposition * 1.05));
  
  TF1* NeuFits = new TF1("NeuFit", "([0]*exp([1]*x)) + (([2])*(TMath::Landau(x,[3],[4])))", 0 ,upperB);
  NeuFits->SetParNames("peak first","Decay rate","height second", "mpv","scale");
  NeuFits->SetParameters(1000,-0.1, 70, xposition,1);
  NeuFits->FixParameter(3,xposition);
  NeuFits->SetLineColor(4);


  
     

  
  Double_t par[5];
  Neutrino->Fit(NeuFits, "R");
  NeuFits -> GetParameters(&par[0]);
  
  //cout << "Half max time: " << -0.693/(par[1]) << " Height at this time: "  << par[0]/2 << endl;
  
  
  
  //cout << (par[2])*TMath::Landau(par[3],par[3],par[4]) << endl;

  //cout << "Difference between the Half-max from first and main peak from second pulse: " << (par[3] - (-0.693/(par[1]))) << "ns. \n" << "Difference between half-max and main peak: " << (par[0]/2) - (par[2])*TMath::Landau(par[3],par[3],par[4]) << endl;



  Double_t gamPeak = (par[2])*TMath::Landau(par[3],par[3],par[4]);
  Double_t halfmaxH = (par[0])/2;
  data << par[0]   << ','
       << par[1]   << ','
       << par[2]   << ','
       << par[3]   << ','
       << par[4]   << ','
       << gamPeak  << ','
       << halfmaxH << ','
       << endl;

    }
  data.close();
}


  












