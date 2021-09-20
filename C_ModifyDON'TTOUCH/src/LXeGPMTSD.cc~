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
/// \file optical/LXe/src/LXeGPMTSD.cc
/// \brief Implementation of the LXeGPMTSD class
//
//
#include "LXeGPMTSD.hh"

#include "LXeGPMTHit.hh"

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

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LXeGPMTSD::LXeGPMTSD(G4String name)
  : G4VSensitiveDetector(name)
  , fHitsCID(-1)
{
  fGPMTCollection = nullptr;
  collectionName.insert("gpmtCollection");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LXeGPMTSD::~LXeGPMTSD() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LXeGPMTSD::Initialize(G4HCofThisEvent* hitsCE)
{
  fGPMTCollection =
    new LXeGPMTHitsCollection(SensitiveDetectorName, collectionName[0]);

  if(fHitsCID < 0)
  {
    fHitsCID = G4SDManager::GetSDMpointer()->GetCollectionID(fGPMTCollection);
  }
  hitsCE->AddHitsCollection(fHitsCID, fGPMTCollection);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool LXeGPMTSD::ProcessHits(G4Step* aStep, G4TouchableHistory*) {

// need to know if this is an optical photon
  if(aStep->GetTrack()->GetDefinition() !=
     G4OpticalPhoton::OpticalPhotonDefinition())
    return false;
  

  G4TouchableHistory* theTouchable =
    (G4TouchableHistory*) (aStep->GetPreStepPoint()->GetTouchable());
  
  G4VPhysicalVolume* thePrePV = theTouchable->GetVolume(0);

  LXeGPMTHit* gpmtHit = new LXeGPMTHit(thePrePV);
  
  G4double edep = aStep->GetTrack()->GetTotalEnergy();
  G4double timeG = aStep->GetTrack()->GetGlobalTime();

  gpmtHit->SetEdepG(edep);
  gpmtHit->SetTimeG(timeG);

  fGPMTCollection->insert(gpmtHit);

  // aStep->GetTrack()->SetTrackStatus(fStopAndKill);
  
  return true;





}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
