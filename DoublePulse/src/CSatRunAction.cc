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
#include "CSatRun.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"

using namespace std;

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
 
  analysisManager->CreateH1("0", "dummy", nbins, vmin, vmax);
  
  
  
 G4int ntupleID = analysisManager->CreateNtuple("Example", "Example Background");

 //analysisManager->CreateNtupleDColumn("Veto_Edep"); //ID 1
 //analysisManager->CreateNtupleDColumn("GAGG_Edep"); //ID 2


 
 analysisManager->CreateNtupleFColumn(ntupleID, "GAGG_hits"); //ID 0
 analysisManager->CreateNtupleFColumn(ntupleID, "Veto_hits"); //ID 1 
 //analysisManager->CreateNtupleDColumn(ntupleID, "Veto_Time"); //ID 2 
 //analysisManager->CreateNtupleDColumn(ntupleID, "GAGG_Time"); //ID 3 
 analysisManager->FinishNtuple(ntupleID);

 
 G4int ntupleID1 = analysisManager->CreateNtuple("Time of Hits Veto", "Time of Hits Veto");
 analysisManager->CreateNtupleFColumn(ntupleID1, "TimingofhitsAfterQEVeto"); //ID 0
 analysisManager->CreateNtupleFColumn(ntupleID1, "Wavelength");
 analysisManager->FinishNtuple(ntupleID1);

 G4int ntupleID2 = analysisManager->CreateNtuple("Time of Hits GAGG", "Time of Hits GAGG");
 analysisManager->CreateNtupleFColumn(ntupleID2, "TimingofhitsBeforeQEVeto"); //ID 0
 analysisManager->CreateNtupleFColumn(ntupleID2, "Wavelength");
 analysisManager->FinishNtuple(ntupleID2);

 /*
 int numEvents = 1000;
 
 for(int i = 0; i < numEvents; i++)
   {
     int index = 0;
     string indexstr = to_string(index);
     
     G4int ntupleIDtest  = analysisManager->CreateNtuple("Neutrino Double Pulses Event "+indexstr,"Neutrino Double Pulses Event"+indexstr); // Event ID 0
     analysisManager->CreateNtupleFColumn(ntupleIDtest, "DoublePulse"); //ID 0
     analysisManager->FinishNtuple(ntupleIDtest);
     index ++;
   }
 */


 
 int numEvents = 10;
 
 for(int i = 0; i < numEvents; i++)
   {
     
     string indexstr = to_string(i);
     string indexName = "Neutrino Double Pulses Event" +indexstr;
     const char *indexConst = indexName.c_str();
     analysisManager->CreateH1(indexConst,indexConst, 100, 0, 1000);
    
    
     
   }

 for(int i = 0; i < numEvents; i++)
   {
     
     string indexstr = to_string(i);
     string indexName =  "Veto Timing Event"+indexstr;
     const char *indexConst = indexName.c_str();
     analysisManager->CreateH1(indexConst,indexConst, 100, 0, 1000);
    
     
   }
 





 //G4RunManager::GetRunManager()->SetRandomNumberStore(true);




 
  
 
 
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
