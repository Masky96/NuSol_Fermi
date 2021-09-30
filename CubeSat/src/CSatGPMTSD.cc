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
/// \file optical/CSat/src/CSatGPMTSD.cc
/// \brief Implementation of the CSatGPMTSD class
//
//
#include "CSatGPMTSD.hh"

#include "CSatGPMTHit.hh"
#include "CSatAnalysis.hh"

#include "G4ios.hh"
#include "G4LogicalVolume.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"
#include "G4TouchableHistory.hh"
#include "G4Track.hh"
#include "G4VPhysicalVolume.hh"
#include "G4VProcess.hh"
#include "G4VTouchable.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh" 
#include "G4RunManager.hh"
#include "G4Gamma.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CSatGPMTSD::CSatGPMTSD(G4String name)
  : G4VSensitiveDetector(name)
  , fHitsCID(-1)
{
  fGPMTCollection = nullptr;
  collectionName.insert("gpmtCollection");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CSatGPMTSD::~CSatGPMTSD() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CSatGPMTSD::Initialize(G4HCofThisEvent* hitsCE)
{
  fGPMTCollection =
    new CSatGPMTHitsCollection(SensitiveDetectorName, collectionName[0]);

  if(fHitsCID < 0)
  {
    fHitsCID = G4SDManager::GetSDMpointer()->GetCollectionID(fGPMTCollection);
  }
  hitsCE->AddHitsCollection(fHitsCID, fGPMTCollection);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool CSatGPMTSD::ProcessHits(G4Step* aStep, G4TouchableHistory*) {
 

  if(aStep->GetTrack()->GetDefinition() != G4OpticalPhoton::OpticalPhotonDefinition()) //&&  aStep->GetTrack()->GetDefinition() != G4Gamma::GammaDefinition())
    {
      return false;
    }
  /*
    else if(aStep->GetTrack()->GetDefinition() != G4Gamma::GammaDefinition())
    {
      return false;
    }
  */


  G4int evtID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
  //G4cout << "The Event ID is: " << evtID << G4endl;
  
  G4int parentID = aStep->GetTrack()->GetParentID();

  //G4cout << "The Parent ID is: " << parentID << G4endl;
  aStep->GetTrack()->SetTrackStatus(fStopAndKill);

  G4TouchableHistory* theTouchable =
    (G4TouchableHistory*) (aStep->GetPreStepPoint()->GetTouchable());
  
  G4VPhysicalVolume* thePrePV = theTouchable->GetVolume(0);

  G4StepPoint* thePrePoint = aStep->GetPreStepPoint();
  

  CSatGPMTHit* gpmtHit = new CSatGPMTHit(thePrePV);
  
  G4double mom = thePrePoint->GetMomentum().mag();
  G4double wavelength = (1.239841939*eV/mom)*1E+03*nm; 
  
  G4double timeG = aStep->GetTrack()->GetGlobalTime();

  /*
  if (timeG > 50*ns)
    {
      G4AnalysisManager::Instance()->FillNtupleDColumn(2 , 0 , timeG*ns);
      G4AnalysisManager::Instance()->FillNtupleDColumn(2 , 1 , wavelength);
      G4AnalysisManager::Instance()->AddNtupleRow(2);
    }
  */
 
  G4AnalysisManager::Instance()->FillNtupleDColumn(2 , 0 , timeG);
  G4AnalysisManager::Instance()->FillNtupleDColumn(2 , 1 , wavelength);
  G4AnalysisManager::Instance()->AddNtupleRow(2);
  if(evtID == 0)
    {
      if (parentID == 2)
	{
	  G4AnalysisManager::Instance()->FillH1(1, timeG);
	}
      else
	{
	  G4AnalysisManager::Instance()->FillH1(2, timeG);
	}
    }

if(evtID == 1)
    {
      if (parentID == 2)
	{
	  G4AnalysisManager::Instance()->FillH1(3, timeG);
	}
      else
	{
	  G4AnalysisManager::Instance()->FillH1(4, timeG);
	}
    }

if(evtID == 2)
    {
      if (parentID == 2)
	{
	  G4AnalysisManager::Instance()->FillH1(5, timeG);
	}
      else
	{
	  G4AnalysisManager::Instance()->FillH1(6, timeG);
	}
    }


if(evtID == 3)
    {
      if (parentID == 2)
	{
	  G4AnalysisManager::Instance()->FillH1(7, timeG);
	}
      else
	{
	  G4AnalysisManager::Instance()->FillH1(8, timeG);
	}
    }

if(evtID == 4)
    {
      if (parentID == 2)
	{
	  G4AnalysisManager::Instance()->FillH1(9, timeG);
	}
      else
	{
	  G4AnalysisManager::Instance()->FillH1(10, timeG);
	}
    }

if(evtID == 5)
    {
      if (parentID == 2)
	{
	  G4AnalysisManager::Instance()->FillH1(11, timeG);
	}
      else
	{
	  G4AnalysisManager::Instance()->FillH1(12, timeG);
	}
    }

if(evtID == 6)
    {
      if (parentID == 2)
	{
	  G4AnalysisManager::Instance()->FillH1(13, timeG);
	}
      else
	{
	  G4AnalysisManager::Instance()->FillH1(14, timeG);
	}
    }

if(evtID == 7)
    {
      if (parentID == 2)
	{
	  G4AnalysisManager::Instance()->FillH1(15, timeG);
	}
      else
	{
	  G4AnalysisManager::Instance()->FillH1(16, timeG);
	}
    }


if(evtID == 8)
    {
      if (parentID == 2)
	{
	  G4AnalysisManager::Instance()->FillH1(17, timeG);
	}
      else
	{
	  G4AnalysisManager::Instance()->FillH1(18, timeG);
	}
    }

if(evtID == 9)
    {
      if (parentID == 2)
	{
	  G4AnalysisManager::Instance()->FillH1(19, timeG);
	}
      else
	{
	  G4AnalysisManager::Instance()->FillH1(20, timeG);
	}
    }

if(evtID == 10)
    {
      if (parentID == 2)
	{
	  G4AnalysisManager::Instance()->FillH1(21, timeG);
	}
      else
	{
	  G4AnalysisManager::Instance()->FillH1(22, timeG);
	}
    }


if(evtID == 11)
    {
      if (parentID == 2)
	{
	  G4AnalysisManager::Instance()->FillH1(23, timeG);
	}
      else
	{
	  G4AnalysisManager::Instance()->FillH1(24, timeG);
	}
    }

if(evtID == 12)
    {
      if (parentID == 2)
	{
	  G4AnalysisManager::Instance()->FillH1(25, timeG);
	}
      else
	{
	  G4AnalysisManager::Instance()->FillH1(26, timeG);
	}
    }


if(evtID == 13)
    {
      if (parentID == 2)
	{
	  G4AnalysisManager::Instance()->FillH1(27, timeG);
	}
      else
	{
	  G4AnalysisManager::Instance()->FillH1(28, timeG);
	}
    }


if(evtID == 14)
    {
      if (parentID == 2)
	{
	  G4AnalysisManager::Instance()->FillH1(29, timeG);
	}
      else
	{
	  G4AnalysisManager::Instance()->FillH1(30, timeG);
	}
    }

if(evtID == 15)
    {
      if (parentID == 2)
	{
	  G4AnalysisManager::Instance()->FillH1(31, timeG);
	}
      else
	{
	  G4AnalysisManager::Instance()->FillH1(32, timeG);
	}
    }
if(evtID == 16)
    {
      if (parentID == 2)
	{
	  G4AnalysisManager::Instance()->FillH1(33, timeG);
	}
      else
	{
	  G4AnalysisManager::Instance()->FillH1(34, timeG);
	}
    }

if(evtID == 17)
    {
      if (parentID == 2)
	{
	  G4AnalysisManager::Instance()->FillH1(35, timeG);
	}
      else
	{
	  G4AnalysisManager::Instance()->FillH1(36, timeG);
	}
    }

if(evtID == 18)
    {
      if (parentID == 2)
	{
	  G4AnalysisManager::Instance()->FillH1(37, timeG);
	}
      else
	{
	  G4AnalysisManager::Instance()->FillH1(38, timeG);
	}
    }

if(evtID == 19)
    {
      if (parentID == 2)
	{
	  G4AnalysisManager::Instance()->FillH1(39, timeG);
	}
      else
	{
	  G4AnalysisManager::Instance()->FillH1(40, timeG);
	}
    }





























  
  
 
  gpmtHit->SetTimeG(timeG);

  fGPMTCollection->insert(gpmtHit);

  
  return true;





}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
