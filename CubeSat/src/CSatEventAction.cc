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
/// \file optical/CSat/src/CSatEventAction.cc
/// \brief Implementation of the CSatEventAction class
//
//
#include "CSatEventAction.hh"

#include "CSatDetectorConstruction.hh"
//#include "CSatHistoManager.hh"
//#include "CSatPMTHit.hh"
#include "CSatRun.hh"
#include "CSatScintHit.hh"

//New 
#include "CSatEljinHit.hh"
#include "CSatVPMTHit.hh"
#include "CSatGPMTHit.hh"


#include "CSatTrajectory.hh"
#include "CSatAnalysis.hh"
#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4ios.hh"
#include "G4RunManager.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4Trajectory.hh"
#include "G4TrajectoryContainer.hh"
#include "G4UImanager.hh"
#include "G4VVisManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CSatEventAction::CSatEventAction(const CSatDetectorConstruction* det)
  : fDetector(det)
  , fScintCollID(-1)
    //, fPMTCollID(-1)
//Adding a new collection ID
  , fEljinCollID(-1)
  , fVerbose(0)
  , fPMTThreshold(1)
  , fForcedrawphotons(false)
  , fForcenophotons(false)
  , fVPMTCollID(-1)
  , fGPMTCollID(-1)
{
  //fEventMessenger = new CSatEventMessenger(this);
  /*
  fHitCount                = 0;
  
  fHitCount_1               =0;
  fHitCount_2               =0;
  fHitCount_3               =0;
  */
  
  fPhotonCount_Scint       = 0;
  fPhotonCount_Ceren       = 0;
  fAbsorptionCount         = 0;
  fBoundaryAbsorptionCount = 0;
  fTotE                    = 0.0;
  fTotEljin                = 0.0;
  
  //fTotEV                 = 0.0;
  //fTotEG                 = 0.0;
  

  fConvPosSet = false;
  fEdepMax    = 0.0;

  fPMTsAboveThreshold = 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CSatEventAction::~CSatEventAction() { }
  //delete fEventMessenger; }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CSatEventAction::BeginOfEventAction(const G4Event*)
{
  /*
  fHitCount                = 0;

  
  fHitCount_1               =0;
  fHitCount_2               =0;
  fHitCount_3               =0;
  */


  
  fPhotonCount_Scint       = 0;
  fPhotonCount_Ceren       = 0;
  fAbsorptionCount         = 0;
  fBoundaryAbsorptionCount = 0;
  fTotE                    = 0.0;
  fTotEljin                = 0.0;
  
  //fTotEV                 = 0.0;
  //fTotEG                 = 0.0;



  fConvPosSet = false;
  fEdepMax    = 0.0;

  fPMTsAboveThreshold = 0;

  G4SDManager* SDman = G4SDManager::GetSDMpointer();
  if(fScintCollID < 0)
    fScintCollID = SDman->GetCollectionID("scintCollection");
  //New 
  if(fEljinCollID < 0)
    fEljinCollID = SDman->GetCollectionID("eljinCollection");

  
  if(fVPMTCollID < 0)
    fVPMTCollID = SDman->GetCollectionID("vpmtCollection");
  
  if(fGPMTCollID < 0)
    fGPMTCollID = SDman->GetCollectionID("gpmtCollection");
  

  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CSatEventAction::EndOfEventAction(const G4Event* anEvent)
{
  G4TrajectoryContainer* trajectoryContainer =
    anEvent->GetTrajectoryContainer();

  G4int n_trajectories = 0;
  if(trajectoryContainer)
    n_trajectories = trajectoryContainer->entries();

  // extract the trajectories and draw them
  if(G4VVisManager::GetConcreteInstance())
  {
    for(G4int i = 0; i < n_trajectories; ++i)
    {
      CSatTrajectory* trj =
        (CSatTrajectory*) ((*(anEvent->GetTrajectoryContainer()))[i]);
      if(trj->GetParticleName() == "opticalphoton")
      {
        trj->SetForceDrawTrajectory(fForcedrawphotons);
        trj->SetForceNoDrawTrajectory(fForcenophotons);
      }
      trj->DrawTrajectory();
    }
  }

  CSatScintHitsCollection* scintHC = nullptr;
  //CSatPMTHitsCollection* pmtHC     = nullptr;
  //New
  CSatEljinHitsCollection* eljinHC = nullptr;

  CSatVPMTHitsCollection* vpmtHC = nullptr;
  CSatGPMTHitsCollection* gpmtHC = nullptr;
  G4HCofThisEvent* hitsCE         = anEvent->GetHCofThisEvent();

  // Get the hit collections
  if(hitsCE)
  {
    if(fScintCollID >= 0)
    {
      scintHC = (CSatScintHitsCollection*) (hitsCE->GetHC(fScintCollID));
    }
    if(fEljinCollID >=0)
    {
      eljinHC = (CSatEljinHitsCollection*) (hitsCE->GetHC(fEljinCollID));
    }
     
    //New
    if(fVPMTCollID >=0)
    {
      vpmtHC = (CSatVPMTHitsCollection*) (hitsCE->GetHC(fVPMTCollID));
    }
    if(fGPMTCollID >=0)
    {
      gpmtHC = (CSatGPMTHitsCollection*) (hitsCE->GetHC(fGPMTCollID));
    }
    
    
 
  }

  // Hits in scintillator
  if(scintHC)
  {
    size_t n_hit = scintHC->entries();
    G4ThreeVector eWeightPos(0.);
    G4double edep;
    G4double edepMax = 0;

    for(size_t i = 0; i < n_hit; ++i)
    {  // gather info on hits in scintillator
      edep = (*scintHC)[i]->GetEdep();

      //G4AnalysisManager::Instance()->FillNtupleDColumn( edep);
      
      fTotE += edep;
      eWeightPos +=
        (*scintHC)[i]->GetPos() * edep;  // calculate energy weighted pos
      if(edep > edepMax)
      {
        edepMax = edep;  // store max energy deposit
        G4ThreeVector posMax = (*scintHC)[i]->GetPos();
        fPosMax              = posMax;
        fEdepMax             = edep;
      }
    }
    //G4AnalysisManager::Instance()->FillNtupleDColumn(0, fTotE);

    if(fTotE == 0.)
    {
      if(fVerbose > 0)
        G4cout << "No hits in the scintillator this event." << G4endl;
    }
    else
    {
      // Finish calculation of energy weighted position
      eWeightPos /= fTotE;
      fEWeightPos = eWeightPos;
      if(fVerbose > 0)
      {
        G4cout << "\tEnergy weighted position of hits in CSat : "
               << eWeightPos / mm << G4endl;
      }
    }
    if(fVerbose > 0)
    {
      G4cout << "\tTotal energy deposition in scintillator : " << fTotE / keV
             << " (keV)" << G4endl;
    }
  }


  
 if(eljinHC)
  {
    size_t n_hit = eljinHC->entries();
    G4double edep;

    for(size_t i = 0; i < n_hit; ++i)
    {  // gather info on hits in scintillator
      edep = (*eljinHC)[i]->GetEdepE(); //Take individual edeps and make them into a graph later.
      fTotEljin += edep;
       
    }

    if(fVerbose > 0)
    {
      G4cout << "\tTotal energy deposition in scintillator : " << fTotE / keV
             << " (keV)" << G4endl;
    }
  }
 //G4AnalysisManager::Instance()->FillNtupleDColumn(1, fTotEljin);

    
if(vpmtHC)
  {
    size_t n_hits = vpmtHC->entries();
    //G4double edepV;
    G4double tfirstV;
    G4double timeV;
    G4double tdiffV;
    G4AnalysisManager::Instance()->FillNtupleFColumn(1, n_hits);
    for(size_t i = 0; i < n_hits; ++i)
    {  // gather info on hits in scintillator
     
      
      tfirstV = (*vpmtHC)[0]->GetTimeV();
      timeV = (*vpmtHC)[i]->GetTimeV();
      tdiffV = timeV -tfirstV;
      
      
    }

  }
  
 if(gpmtHC)
  {
    size_t n_hits = gpmtHC->entries();
    G4AnalysisManager::Instance()->FillNtupleFColumn(0, n_hits);

    //G4ThreeVector eWeightPos(0.);
    //G4double edepG;
    G4double tfirstG;
    G4double timeG;
    G4double tdiffG;
    
    for(size_t i = 0; i < n_hits; ++i)
    {  // gather info on hits in scintillator
      
      tfirstG = (*gpmtHC)[0]->GetTimeG();

      timeG = (*gpmtHC)[i]->GetTimeG();
      tdiffG = timeG - tfirstG;

    }
    

  }

 
 G4AnalysisManager::Instance()->AddNtupleRow(0);






  
    
  
  // update the run statistics
  CSatRun* run = static_cast<CSatRun*>(
    G4RunManager::GetRunManager()->GetNonConstCurrentRun());
  /*
  run->IncHitCount(fHitCount);
  
  run->IncHitCount1(fHitCount_1);
  run->IncHitCount2(fHitCount_2);
  run->IncHitCount3(fHitCount_3);
  */

  
  run->IncPhotonCount_Scint(fPhotonCount_Scint);
  run->IncPhotonCount_Ceren(fPhotonCount_Ceren);
  run->IncEDep(fTotE);
  run->IncEDepE(fTotEljin);


  //run->IncEDepG(fTotEG);
  //run->IncEDepV(fTotEV);
  
  run->IncAbsorption(fAbsorptionCount);
  run->IncBoundaryAbsorption(fBoundaryAbsorptionCount);
  run->IncHitsAboveThreshold(fPMTsAboveThreshold);

 }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
