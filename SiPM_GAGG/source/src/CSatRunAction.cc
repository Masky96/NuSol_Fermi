//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file optical/CSat/src/CSatRunAction.cc
/// \brief Implementation of the CSatRunAction class
//
//
#include "CSatRunAction.hh"
#include "CSatShowerGenerator.hh"
#include "CSatAnalysis.hh"
//#include "CSatHistoManager.hh"
#include "CSatRun.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CSatRunAction::CSatRunAction()
  : G4UserRunAction()
  , fRun(nullptr)
    //, fHistoManager(nullptr)
{
  // Book predefined histograms
  //fHistoManager = new CSatHistoManager();

  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  G4cout << "Using " << analysisManager->GetType() << G4endl;
 
  // Default settings
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetFileName("Tutorial");
  analysisManager->SetNtupleMerging(true);
  G4int nbins   = 1000;
  G4double vmin = 0.;
  G4double vmax = 1000.;
 

 
 G4int ntupleID = analysisManager->CreateNtuple("Example", "Example Background");

 //analysisManager->CreateNtupleDColumn("Veto_Edep"); //ID 1
 //analysisManager->CreateNtupleDColumn("GAGG_Edep"); //ID 2


 
 analysisManager->CreateNtupleFColumn(ntupleID, "GAGG_hits"); //ID 0
 analysisManager->CreateNtupleFColumn(ntupleID, "Veto_hits"); //ID 1 
 //analysisManager->CreateNtupleDColumn(ntupleID, "Veto_Time"); //ID 2 
 //analysisManager->CreateNtupleDColumn(ntupleID, "GAGG_Time"); //ID 3 
 analysisManager->FinishNtuple(ntupleID);

 /*
 G4int ntupleID1 = analysisManager->CreateNtuple("Time of Hits Veto", "Time of Hits Veto");
 analysisManager->CreateNtupleFColumn(ntupleID1, "TimingofhitsAfterQEVeto"); //ID 0
 analysisManager->CreateNtupleFColumn(ntupleID1, "Wavelength");
 analysisManager->FinishNtuple(ntupleID1);

 G4int ntupleID2 = analysisManager->CreateNtuple("Time of Hits GAGG", "Time of Hits GAGG");
 analysisManager->CreateNtupleFColumn(ntupleID2, "TimingofhitsBeforeQEVeto"); //ID 0
 analysisManager->CreateNtupleFColumn(ntupleID2, "Wavelength");
 analysisManager->FinishNtuple(ntupleID2);
 */
 if(showers -> empty()){
 CSatShowerGenerator::GenerateShower(showers);
 }
 G4cout << "showers size: " << CSatRunAction::showers->size();

 //std::vector< std::vector< User::event* >* > *CSatRunAction::showers = new std::vector< std::vector< User::event* >* >{CSatShowerGenerator::GenerateShower().begin(),CSatShowerGenerator::GenerateShower().end()};



 /*
 //Event Ntuples
 G4int ntupleID3 = analysisManager->CreateNtuple("Time of Hit of ElectronEVT0","Time of Hit of Electron"); // Event ID 0
 analysisManager->CreateNtupleDColumn(ntupleID3, "ElectronTime"); //ID 0
 analysisManager->FinishNtuple(ntupleID3);

 G4int ntupleID4 = analysisManager->CreateNtuple("Time of Hit of GammaEVT0","Time of Hit of Gamma");
 analysisManager->CreateNtupleDColumn(ntupleID4, "GammaTime"); //ID 0
 analysisManager->FinishNtuple(ntupleID4);

 G4int ntupleID5 = analysisManager->CreateNtuple("Time of Hit of ElectronEVT1","Time of Hit of Electron"); // Event ID 1
 analysisManager->CreateNtupleDColumn(ntupleID5, "ElectronTime"); //ID 0
 analysisManager->FinishNtuple(ntupleID5);

 G4int ntupleID6 = analysisManager->CreateNtuple("Time of Hit of GammaEVT1","Time of Hit of Gamma");
 analysisManager->CreateNtupleDColumn(ntupleID6, "GammaTime"); //ID 0
 analysisManager->FinishNtuple(ntupleID6);

 G4int ntupleID7 = analysisManager->CreateNtuple("Time of Hit of ElectronEVT2","Time of Hit of Electron"); // Event ID 2
 analysisManager->CreateNtupleDColumn(ntupleID7, "ElectronTime"); //ID 0
 analysisManager->FinishNtuple(ntupleID7);

 G4int ntupleID8 = analysisManager->CreateNtuple("Time of Hit of GammaEVT2","Time of Hit of Gamma");
 analysisManager->CreateNtupleDColumn(ntupleID8, "GammaTime"); //ID 0
 analysisManager->FinishNtuple(ntupleID8);

 G4int ntupleID9 = analysisManager->CreateNtuple("Time of Hit of ElectronEVT3","Time of Hit of Electron"); // Event ID 3
 analysisManager->CreateNtupleDColumn(ntupleID9, "ElectronTime"); //ID 0
 analysisManager->FinishNtuple(ntupleID9);

 G4int ntupleID10 = analysisManager->CreateNtuple("Time of Hit of GammaEVT3","Time of Hit of Gamma");
 analysisManager->CreateNtupleDColumn(ntupleID10, "GammaTime"); //ID 0
 analysisManager->FinishNtuple(ntupleID10);

 G4int ntupleID11 = analysisManager->CreateNtuple("Time of Hit of ElectronEVT4","Time of Hit of Electron"); // Event ID 4
 analysisManager->CreateNtupleDColumn(ntupleID11, "ElectronTime"); //ID 0
 analysisManager->FinishNtuple(ntupleID11);

 
 G4int ntupleID12 = analysisManager->CreateNtuple("Time of Hit of GammaEVT4","Time of Hit of Gamma");
 analysisManager->CreateNtupleDColumn(ntupleID12, "GammaTime"); //ID 0
 analysisManager->FinishNtuple(ntupleID12);

 
 G4int ntupleID13 = analysisManager->CreateNtuple("Time of Hit of ElectronEVT5","Time of Hit of Electron"); // Event ID 5
 analysisManager->CreateNtupleDColumn(ntupleID13, "ElectronTime"); //ID 0
 analysisManager->FinishNtuple(ntupleID13);

 
 G4int ntupleID14 = analysisManager->CreateNtuple("Time of Hit of GammaEVT5","Time of Hit of Gamma");
 analysisManager->CreateNtupleDColumn(ntupleID14, "GammaTime"); //ID 0
 analysisManager->FinishNtuple(ntupleID14);

 
 G4int ntupleID15 = analysisManager->CreateNtuple("Time of Hit of ElectronEVT6","Time of Hit of Electron"); // Event ID 6
 analysisManager->CreateNtupleDColumn(ntupleID15, "ElectronTime"); //ID 0
 analysisManager->FinishNtuple(ntupleID15);

 
 G4int ntupleID16 = analysisManager->CreateNtuple("Time of Hit of GammaEVT6","Time of Hit of Gamma");
 analysisManager->CreateNtupleDColumn(ntupleID16, "GammaTime"); //ID 0
 analysisManager->FinishNtuple(ntupleID16);

 
 G4int ntupleID17 = analysisManager->CreateNtuple("Time of Hit of ElectronEVT7","Time of Hit of Electron"); // Event ID 7
 analysisManager->CreateNtupleDColumn(ntupleID17, "ElectronTime"); //ID 0
 analysisManager->FinishNtuple(ntupleID17);

 
 G4int ntupleID18 = analysisManager->CreateNtuple("Time of Hit of GammaEVT7","Time of Hit of Gamma");
 analysisManager->CreateNtupleDColumn(ntupleID18, "GammaTime"); //ID 0
 analysisManager->FinishNtuple(ntupleID18);

 
 G4int ntupleID19 = analysisManager->CreateNtuple("Time of Hit of ElectronEVT8","Time of Hit of Electron"); // Event ID 8
 analysisManager->CreateNtupleDColumn(ntupleID19, "ElectronTime"); //ID 0
 analysisManager->FinishNtuple(ntupleID19);

 
 G4int ntupleID20 = analysisManager->CreateNtuple("Time of Hit of GammaEVT8","Time of Hit of Gamma");
 analysisManager->CreateNtupleDColumn(ntupleID20, "GammaTime"); //ID 0
 analysisManager->FinishNtuple(ntupleID20);

 
 G4int ntupleID21 = analysisManager->CreateNtuple("Time of Hit of ElectronEVT9","Time of Hit of Electron"); // Event ID 9
 analysisManager->CreateNtupleDColumn(ntupleID21, "ElectronTime"); //ID 0
 analysisManager->FinishNtuple(ntupleID21);

 G4int ntupleID22 = analysisManager->CreateNtuple("Time of Hit of GammaEVT9","Time of Hit of Gamma");
 analysisManager->CreateNtupleDColumn(ntupleID22, "GammaTime"); //ID 0
 analysisManager->FinishNtuple(ntupleID22);

 
 G4int ntupleID23 = analysisManager->CreateNtuple("Time of Hit of ElectronEVT10","Time of Hit of Electron"); // Event ID 10
 analysisManager->CreateNtupleDColumn(ntupleID23, "ElectronTime"); //ID 0
 analysisManager->FinishNtuple(ntupleID23);

 G4int ntupleID24 = analysisManager->CreateNtuple("Time of Hit of GammaEVT10","Time of Hit of Gamma");
 analysisManager->CreateNtupleDColumn(ntupleID24, "GammaTime"); //ID 0
 analysisManager->FinishNtuple(ntupleID24);

 G4int ntupleID25 = analysisManager->CreateNtuple("Time of Hit of ElectronEVT11","Time of Hit of Electron"); // Event ID 11
 analysisManager->CreateNtupleDColumn(ntupleID25, "ElectronTime"); //ID 0
 analysisManager->FinishNtuple(ntupleID25);

 G4int ntupleID26 = analysisManager->CreateNtuple("Time of Hit of GammaEVT11","Time of Hit of Gamma");
 analysisManager->CreateNtupleDColumn(ntupleID26, "GammaTime"); //ID 0
 analysisManager->FinishNtuple(ntupleID26);

 
 G4int ntupleID27 = analysisManager->CreateNtuple("Time of Hit of ElectronEVT12","Time of Hit of Electron"); // Event ID 12
 analysisManager->CreateNtupleDColumn(ntupleID27, "ElectronTime"); //ID 0
 analysisManager->FinishNtuple(ntupleID27);

 G4int ntupleID28 = analysisManager->CreateNtuple("Time of Hit of GammaEVT12","Time of Hit of Gamma");
 analysisManager->CreateNtupleDColumn(ntupleID28, "GammaTime"); //ID 0
 analysisManager->FinishNtuple(ntupleID28);

 G4int ntupleID29 = analysisManager->CreateNtuple("Time of Hit of ElectronEVT13","Time of Hit of Electron"); // Event ID 13
 analysisManager->CreateNtupleDColumn(ntupleID29, "ElectronTime"); //ID 0
 analysisManager->FinishNtuple(ntupleID29);

 G4int ntupleID30 = analysisManager->CreateNtuple("Time of Hit of GammaEVT13","Time of Hit of Gamma");
 analysisManager->CreateNtupleDColumn(ntupleID30, "GammaTime"); //ID 0
 analysisManager->FinishNtuple(ntupleID30);

 G4int ntupleID31 = analysisManager->CreateNtuple("Time of Hit of ElectronEVT14","Time of Hit of Electron"); // Event ID 14
 analysisManager->CreateNtupleDColumn(ntupleID31, "ElectronTime"); //ID 0
 analysisManager->FinishNtuple(ntupleID31);

 G4int ntupleID32 = analysisManager->CreateNtuple("Time of Hit of GammaEVT14","Time of Hit of Gamma");
 analysisManager->CreateNtupleDColumn(ntupleID32, "GammaTime"); //ID 0
 analysisManager->FinishNtuple(ntupleID32);

 
 G4int ntupleID33 = analysisManager->CreateNtuple("Time of Hit of ElectronEVT15","Time of Hit of Electron"); // Event ID 15
 analysisManager->CreateNtupleDColumn(ntupleID33, "ElectronTime"); //ID 0
 analysisManager->FinishNtuple(ntupleID33);

 G4int ntupleID34 = analysisManager->CreateNtuple("Time of Hit of GammaEVT15","Time of Hit of Gamma");
 analysisManager->CreateNtupleDColumn(ntupleID34, "GammaTime"); //ID 0
 analysisManager->FinishNtuple(ntupleID34);

 G4int ntupleID35 = analysisManager->CreateNtuple("Time of Hit of ElectronEVT16","Time of Hit of Electron"); // Event ID 16
 analysisManager->CreateNtupleDColumn(ntupleID35, "ElectronTime"); //ID 0
 analysisManager->FinishNtuple(ntupleID35);

 G4int ntupleID36 = analysisManager->CreateNtuple("Time of Hit of GammaEVT16","Time of Hit of Gamma");
 analysisManager->CreateNtupleDColumn(ntupleID36, "GammaTime"); //ID 0
 analysisManager->FinishNtuple(ntupleID36);

 G4int ntupleID37 = analysisManager->CreateNtuple("Time of Hit of ElectronEVT17","Time of Hit of Electron"); // Event ID 17
 analysisManager->CreateNtupleDColumn(ntupleID37, "ElectronTime"); //ID 0
 analysisManager->FinishNtuple(ntupleID37);

 
 G4int ntupleID38 = analysisManager->CreateNtuple("Time of Hit of GammaEVT17","Time of Hit of Gamma");
 analysisManager->CreateNtupleDColumn(ntupleID38, "GammaTime"); //ID 0
 analysisManager->FinishNtuple(ntupleID38);

 G4int ntupleID39 = analysisManager->CreateNtuple("Time of Hit of ElectronEVT18","Time of Hit of Electron"); // Event ID 18
 analysisManager->CreateNtupleDColumn(ntupleID39, "ElectronTime"); //ID 0
 analysisManager->FinishNtuple(ntupleID39);

 G4int ntupleID40 = analysisManager->CreateNtuple("Time of Hit of GammaEVT18","Time of Hit of Gamma");
 analysisManager->CreateNtupleDColumn(ntupleID40, "GammaTime"); //ID 0
 analysisManager->FinishNtuple(ntupleID40);

 G4int ntupleID41 = analysisManager->CreateNtuple("Time of Hit of ElectronEVT19","Time of Hit of Electron"); // Event ID 19
 analysisManager->CreateNtupleDColumn(ntupleID41, "ElectronTime"); //ID 0
 analysisManager->FinishNtuple(ntupleID41);

 G4int ntupleID42 = analysisManager->CreateNtuple("Time of Hit of GammaEVT19","Time of Hit of Gamma");
 analysisManager->CreateNtupleDColumn(ntupleID42, "GammaTime"); //ID 0
 analysisManager->FinishNtuple(ntupleID42);
 */

 // 0
 //analysisManager->CreateH1("0", "dummy", nbins, vmin, vmax);
 
 //1 New
 /*
 analysisManager->CreateH1("Time of hit from Initial particle evt 0","time of each hit GAGG", nbins, vmin, vmax);
 //2
 analysisManager->CreateH1("Time of hit from Secondary particle evt 0","time of each hit GAGG", nbins, vmin, vmax);
 //3
 analysisManager->CreateH1("Time of hit from Initial particle evt 1","time of each hit GAGG", nbins, vmin, vmax);
 //4
 analysisManager->CreateH1("Time of hit from Secondary particle evt 1","time of each hit GAGG", nbins, vmin, vmax);
 //5
 analysisManager->CreateH1("Time of hit from Initial particle evt 2","time of each hit GAGG", nbins, vmin, vmax);
 //6
 analysisManager->CreateH1("Time of hit from Secondary particle evt 2","time of each hit GAGG", nbins, vmin, vmax);
 //7  
 analysisManager->CreateH1("Time of hit from Initial particle evt 3","time of each hit GAGG", nbins, vmin, vmax);
 //8
 analysisManager->CreateH1("Time of hit from Secondary particle evt 3","time of each hit GAGG", nbins, vmin, vmax);
 //9
 analysisManager->CreateH1("Time of hit from Initial particle evt 4","time of each hit GAGG", nbins, vmin, vmax);
 //10
 analysisManager->CreateH1("Time of hit from Secondary particle evt 4","time of each hit GAGG", nbins, vmin, vmax); 
 //11 
 analysisManager->CreateH1("Time of hit from Initial particle evt 5","time of each hit GAGG", nbins, vmin, vmax);
 //12
 analysisManager->CreateH1("Time of hit from Secondary particle evt 5","time of each hit GAGG", nbins, vmin, vmax);
 //13
 analysisManager->CreateH1("Time of hit from Initial particle evt 6","time of each hit GAGG", nbins, vmin, vmax);
 //14
 analysisManager->CreateH1("Time of hit from Secondary particle evt 6","time of each hit GAGG", nbins, vmin, vmax);
 //15  
 analysisManager->CreateH1("Time of hit from Initial particle evt 7","time of each hit GAGG", nbins, vmin, vmax);
 //16
 analysisManager->CreateH1("Time of hit from Secondary particle evt 7","time of each hit GAGG", nbins, vmin, vmax);
 //17
 analysisManager->CreateH1("Time of hit from Initial particle evt 8","time of each hit GAGG", nbins, vmin, vmax);
 //18
 analysisManager->CreateH1("Time of hit from Secondary particle evt 8","time of each hit GAGG", nbins, vmin, vmax);
//19 
 analysisManager->CreateH1("Time of hit from Initial particle evt 9","time of each hit GAGG", nbins, vmin, vmax);
 //20
 analysisManager->CreateH1("Time of hit from Secondary particle evt 9","time of each hit GAGG", nbins, vmin, vmax);
 //21
 analysisManager->CreateH1("Time of hit from Initial particle evt 10","time of each hit GAGG", nbins, vmin, vmax);
 //22
 analysisManager->CreateH1("Time of hit from Secondary particle evt 10","time of each hit GAGG", nbins, vmin, vmax);
 //23 
 analysisManager->CreateH1("Time of hit from Initial particle evt 11","time of each hit GAGG", nbins, vmin, vmax);
 //24
 analysisManager->CreateH1("Time of hit from Secondary particle evt 11","time of each hit GAGG", nbins, vmin, vmax);
 //25
 analysisManager->CreateH1("Time of hit from Initial particle evt 12","time of each hit GAGG", nbins, vmin, vmax);
 //26
 analysisManager->CreateH1("Time of hit from Secondary particle evt 12","time of each hit GAGG", nbins, vmin, vmax); 
 //27
 analysisManager->CreateH1("Time of hit from Initial particle evt 13","time of each hit GAGG", nbins, vmin, vmax);
 //28
 analysisManager->CreateH1("Time of hit from Secondary particle evt 13","time of each hit GAGG", nbins, vmin, vmax);
 //29
 analysisManager->CreateH1("Time of hit from Initial particle evt 14","time of each hit GAGG", nbins, vmin, vmax);
 //30
 analysisManager->CreateH1("Time of hit from Secondary particle evt 14","time of each hit GAGG", nbins, vmin, vmax);
 //31  
 analysisManager->CreateH1("Time of hit from Initial particle evt 15","time of each hit GAGG", nbins, vmin, vmax);
 //32
 analysisManager->CreateH1("Time of hit from Secondary particle evt 15","time of each hit GAGG", nbins, vmin, vmax);
 //33
 analysisManager->CreateH1("Time of hit from Initial particle evt 16","time of each hit GAGG", nbins, vmin, vmax);
 //34
 analysisManager->CreateH1("Time of hit from Secondary particle evt 16","time of each hit GAGG", nbins, vmin, vmax);
 //35
 analysisManager->CreateH1("Time of hit from Initial particle evt 17","time of each hit GAGG", nbins, vmin, vmax);
 //36
 analysisManager->CreateH1("Time of hit from Secondary particle evt 17","time of each hit GAGG", nbins, vmin, vmax); 
 //37
 analysisManager->CreateH1("Time of hit from Initial particle evt 18","time of each hit GAGG", nbins, vmin, vmax);
 //38
 analysisManager->CreateH1("Time of hit from Secondary particle evt 18","time of each hit GAGG", nbins, vmin, vmax);
 //39
 analysisManager->CreateH1("Time of hit from Initial particle evt 19","time of each hit GAGG", nbins, vmin, vmax);
 //40
 analysisManager->CreateH1("Time of hit from Secondary particle evt 19","time of each hit GAGG", nbins, vmin, vmax);
 */











 
  
 /*
 
   for(G4int i = 0; i < analysisManager->GetNofH1s(); ++i)
  {
    analysisManager->SetH1Activation(i, false);
  }
 */
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CSatRunAction::~CSatRunAction() { }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4Run* CSatRunAction::GenerateRun()
{
  fRun = new CSatRun();
  return fRun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CSatRunAction::BeginOfRunAction(const G4Run*)
{
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  /*
   if(analysisManager->IsActive())
  {
    analysisManager->OpenFile();
  }
  */
  
  analysisManager->OpenFile();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CSatRunAction::EndOfRunAction(const G4Run*)
{
  if(isMaster)
    fRun->EndOfRun();

  
  // save histograms
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();
 
  
}


 //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//Initialize showers to null
std::vector< std::vector< User::event* >* > *CSatRunAction::showers = new std::vector< std::vector< User::event* >* >{};
//std::vector< std::vector< User::event* >* > *CSatRunAction::showers = new std::vector< std::vector< User::event* >* >{CSatShowerGenerator::GenerateShower().begin(),CSatShowerGenerator::GenerateShower().end()};
