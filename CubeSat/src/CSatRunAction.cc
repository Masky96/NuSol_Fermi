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
  analysisManager->SetActivation(true);
  G4int nbins   = 100;
  G4double vmin = 0.;
  G4double vmax = 100.;
 

 
 G4int ntupleID = analysisManager->CreateNtuple("Example", "Example Background");

 //analysisManager->CreateNtupleDColumn("Veto_Edep"); //ID 1
 //analysisManager->CreateNtupleDColumn("GAGG_Edep"); //ID 2


 
 analysisManager->CreateNtupleDColumn(ntupleID, "GAGG_hits"); //ID 0
 analysisManager->CreateNtupleDColumn(ntupleID, "Veto_hits"); //ID 1 
 //analysisManager->CreateNtupleDColumn(ntupleID, "Veto_Time"); //ID 2 
 //analysisManager->CreateNtupleDColumn(ntupleID, "GAGG_Time"); //ID 3 
 analysisManager->FinishNtuple(ntupleID);

 
 G4int ntupleID1 = analysisManager->CreateNtuple("Time of Hits Veto", "Time of Hits Veto");
 analysisManager->CreateNtupleDColumn(ntupleID1, "Veto_Time"); //ID 0
 analysisManager->CreateNtupleDColumn(ntupleID1, "Wavelength");
 analysisManager->FinishNtuple(ntupleID1);

 G4int ntupleID2 = analysisManager->CreateNtuple("Time of Hits GAGG", "Time of Hits GAGG");
 analysisManager->CreateNtupleDColumn(ntupleID2, "GAGG_Time"); //ID 0
 analysisManager->CreateNtupleDColumn(ntupleID2, "Wavelength");
 analysisManager->FinishNtuple(ntupleID2);

 

 // 0
 analysisManager->CreateH1("0", "dummy", nbins, vmin, vmax);
 
 //1 New
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
  











 
  


   for(G4int i = 0; i < analysisManager->GetNofH1s(); ++i)
  {
    analysisManager->SetH1Activation(i, false);
  }
  
  
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
