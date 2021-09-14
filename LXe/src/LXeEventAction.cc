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
/// \file optical/LXe/src/LXeEventAction.cc
/// \brief Implementation of the LXeEventAction class
//
//
#include "LXeEventAction.hh"

#include "LXeDetectorConstruction.hh"
#include "LXeHistoManager.hh"
#include "LXePMTHit.hh"
#include "LXeRun.hh"
#include "LXeScintHit.hh"
#include "LXeTrajectory.hh"

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

LXeEventAction::LXeEventAction(const LXeDetectorConstruction* det)
  : fDetector(det)
  , fScintCollID(-1)
  , fPMTCollID(-1)
  , fVerbose(0)
  , fPMTThreshold(1)
  //, fForcedrawphotons(false)
  //, fForcenophotons(false)
{
  fEventMessenger = new LXeEventMessenger(this);

  fHitCount                = 0;
  fHitC1                   = 0;
  fHitC2                   = 0;
  fHitC3                   = 0;
  fHitC4                   = 0;
  fHitC5                   = 0;
  fHitC6                   = 0;
  fHitC7                   = 0;
  fHitC8                   = 0;
  /*
  fHitC9                   = 0;
  fHitC10                   = 0;
  fHitC11                   = 0;
  fHitC12                   = 0;
  fHitC13                   = 0;
  fHitC14                   = 0;
  fHitC15                   = 0;
  fHitC16                   = 0;
  */
//New 
  fTotEP                   =0.0;
  fTotEP1                  = 0.0;
  fTotEP2                  = 0.0;
  fTotEP3                  = 0.0; 
  fTotEP4                  = 0.0;
  fTotEP5                  = 0.0;
  fTotEP6                  = 0.0;
  fTotEP7                  = 0.0;
  fTotEP8                  = 0.0;
  /*
  fTotEP9                  = 0.0;
  fTotEP10                  = 0.0;
  fTotEP11                  = 0.0;
  fTotEP12                  = 0.0;
  fTotEP13                  = 0.0;
  fTotEP14                  = 0.0;
  fTotEP15                  = 0.0;
  fTotEP16                  = 0.0;
  */
  
  fPMTsAboveThreshold = 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LXeEventAction::~LXeEventAction() { delete fEventMessenger; }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LXeEventAction::BeginOfEventAction(const G4Event*)
{
  fHitCount                = 0;
  fHitC1                   = 0;
  fHitC2                   = 0;
  fHitC3                   = 0;
  fHitC4                   = 0;
  fHitC5                   = 0;
  fHitC6                   = 0;
  fHitC7                   = 0;
  fHitC8                   = 0;
  /*
  fHitC9                   = 0;
  fHitC10                   = 0;
  fHitC11                   = 0;
  fHitC12                   = 0;
  fHitC13                   = 0;
  fHitC14                   = 0;
  fHitC15                   = 0;
  fHitC16                   = 0;
  */
  
//New 
  fTotEP                  = 0.0;
//
  fTotEP1                  = 0.0;
  fTotEP2                  = 0.0;
  fTotEP3                  = 0.0; 
  fTotEP4                  = 0.0;
  fTotEP5                  = 0.0;
  fTotEP6                  = 0.0;
  fTotEP7                  = 0.0;
  fTotEP8                  = 0.0;
  /*
  fTotEP9                  = 0.0;
  fTotEP10                  = 0.0;
  fTotEP11                  = 0.0;
  fTotEP12                  = 0.0;
  fTotEP13                  = 0.0;
  fTotEP14                  = 0.0;
  fTotEP15                  = 0.0;
  fTotEP16                  = 0.0;
  */
 
  //fConvPosSet = false;

  fPMTsAboveThreshold = 0;

  

  G4SDManager* SDman = G4SDManager::GetSDMpointer();
  if(fScintCollID < 0)
    fScintCollID = SDman->GetCollectionID("scintCollection");
  if(fPMTCollID < 0)
    fPMTCollID = SDman->GetCollectionID("pmtHitCollection");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LXeEventAction::EndOfEventAction(const G4Event* anEvent)
{

 //Constants

  G4double hP =6.626e-34*joule*s;
  G4double cofL = 3.0e8*(m/s);

  
  LXePMTHitsCollection* pmtHC     = nullptr;
  G4HCofThisEvent* hitsCE         = anEvent->GetHCofThisEvent();

  // Get the hit collections
  if(hitsCE)
  {
    if(fPMTCollID >= 0)
    {
      pmtHC = (LXePMTHitsCollection*) (hitsCE->GetHC(fPMTCollID));
    }
  }

  if(pmtHC)
  {
    G4ThreeVector reconPos(0., 0., 0.);
    size_t pmts = pmtHC->entries();

    // Gather info from all PMTs

    for(size_t i = 0; i < pmts; ++i)
    {

      G4double edepP;
      
      edepP = (*pmtHC)[i]->GetEdepP();
      
      fTotEP += edepP;
      // G4AnalysisManager::Instance()->FillH1(3, edepP/eV);

      /*
      if (edepP/eV >= 2.00 && edepP/eV < 2.103)
	{
	fTotEP1 += edepP;
      ++fHitC1;
        
	}

      */

      //Red-----------------------------------
      if ( edepP/eV >= 1.55 && edepP/eV < 1.98)
	{
	fTotEP1 += edepP;
      ++fHitC1;
	}
      
      //Orange-------------------------------
      if (edepP/eV >= 1.98 && edepP/eV < 2.10)
	{
	fTotEP2 += edepP;
      ++fHitC2;
	}
      
      //Yellow-------------------------------
      if (edepP/eV >= 2.10 && edepP/eV < 2.19)
	{
	fTotEP3 += edepP;
      ++fHitC3;
	}
      
      //Green--------------------------------
      if (edepP/eV >= 2.19 && edepP/eV < 2.38)
	{
	fTotEP4 += edepP;
      ++fHitC4;
	}
      //Cyan---------------------------------
      if (edepP/eV >= 2.38 && edepP/eV <= 2.48)
	{
	fTotEP5 += edepP;
      ++fHitC5;
	}

      //Blue----------------------------------
      if (edepP/eV >= 2.48 && edepP/eV < 2.85)
	{
	fTotEP6 += edepP;
      ++fHitC6;
	}
      //Violet---------------------------------
      if (edepP/eV >= 2.85 && edepP/eV < 3.26)
	{
	fTotEP7 += edepP;
      ++fHitC7;
	}
      //UV
      if (edepP/eV >= 3.26)
	{
	fTotEP8 += edepP;
      ++fHitC8;
	}
      /*
      if (edepP/eV >= 2.757 && edepP/eV < 2.885)
	{
	fTotEP9 += edepP;
      ++fHitC9;
	}
      if (edepP/eV >= 2.885 && edepP/eV < 3.026)
	{
	fTotEP10 += edepP;
      ++fHitC10;
	}
      if (edepP/eV >= 3.026 && edepP/eV < 3.181)
	{
	fTotEP11 += edepP;
      ++fHitC11;
	}
      if (edepP/eV >= 3.181 && edepP/eV < 3.353)
	{
	fTotEP12 += edepP;
      ++fHitC12;
	}
      if (edepP/eV >= 3.353 && edepP/eV < 3.545)
	{
	fTotEP13 += edepP;
      ++fHitC13;
	}
      if (edepP/eV >= 3.545 && edepP/eV < 3.760)
	{
	fTotEP14 += edepP;
      ++fHitC14;
	}
      if (edepP/eV >= 3.760 && edepP/eV < 4.002)
	{
	fTotEP15 += edepP;
      ++fHitC15;
	}
      if (edepP/eV >= 4.002)
	{
	fTotEP16 += edepP;
      ++fHitC16;
	}
      */
	
      fHitCount += (*pmtHC)[i]->GetPhotonCount();
      reconPos += (*pmtHC)[i]->GetPMTPos() * (*pmtHC)[i]->GetPhotonCount();      if((*pmtHC)[i]->GetPhotonCount() >= fPMTThreshold)
      {
        ++fPMTsAboveThreshold;
      }
      else
      {  // wasn't above the threshold, turn it back off
        (*pmtHC)[i]->SetDrawit(false);
      }
      /*
    G4AnalysisManager::Instance()->FillNtupleDColumn(0,fHitC1);
    G4AnalysisManager::Instance()->FillNtupleDColumn(1,fTotEP1);
    G4AnalysisManager::Instance()->AddNtupleRow();
      */
      //G4AnalysisManager::Instance()->FillH1(3, edepP);

            
      G4AnalysisManager::Instance()->FillH1(3, (hP*cofL)/(edepP));
    }
    
  }  
    G4AnalysisManager::Instance()->FillH1(1, fHitCount);
    G4AnalysisManager::Instance()->FillH1(2, fPMTsAboveThreshold);
    //G4AnalysisManager::Instance()->FillH1(3, fEdepP);

    /*
    G4AnalysisManager::Instance()->FillNtupleDColumn(0,fHitC1);
    G4AnalysisManager::Instance()->FillNtupleDColumn(1,fTotEP1);
    G4AnalysisManager::Instance()->AddNtupleRow();
    */


  LXeRun* run = static_cast<LXeRun*>(
    G4RunManager::GetRunManager()->GetNonConstCurrentRun());

  run->IncHitCount(fHitCount);
  
  run->IncHitC1(fHitC1);
  run->IncHitC2(fHitC2);
  run->IncHitC3(fHitC3);
  run->IncHitC4(fHitC4);
  run->IncHitC5(fHitC5);
  run->IncHitC6(fHitC6);
  run->IncHitC7(fHitC7);
  run->IncHitC8(fHitC8);
  /*
  run->IncHitC9(fHitC9);
  run->IncHitC10(fHitC10);
  run->IncHitC11(fHitC11);
  run->IncHitC12(fHitC12);
  run->IncHitC13(fHitC13);
  run->IncHitC14(fHitC14);
  run->IncHitC15(fHitC15);
  run->IncHitC16(fHitC16);
  */
 
  run->IncEDepP(fTotEP);
  
  run->IncEDepP1(fTotEP1);
  run->IncEDepP2(fTotEP2);
  run->IncEDepP3(fTotEP3);
  run->IncEDepP4(fTotEP4);
  run->IncEDepP5(fTotEP5);
  run->IncEDepP6(fTotEP6);
  run->IncEDepP7(fTotEP7);
  run->IncEDepP8(fTotEP8);
  /*
  run->IncEDepP9(fTotEP9);
  run->IncEDepP10(fTotEP10);
  run->IncEDepP11(fTotEP11);
  run->IncEDepP12(fTotEP12);
  run->IncEDepP13(fTotEP13);
  run->IncEDepP14(fTotEP14);
  run->IncEDepP15(fTotEP15);
  run->IncEDepP16(fTotEP16);
  */
  
  run->IncHitsAboveThreshold(fPMTsAboveThreshold);

 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
