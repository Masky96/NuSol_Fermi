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
/// \file optical/CSat/src/CSatVPMTSD.cc
/// \brief Implementation of the CSatVPMTSD class
//
//
#include "CSatVPMTSD.hh"

#include "CSatVPMTHit.hh"
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
#include "G4Gamma.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CSatVPMTSD::CSatVPMTSD(G4String name)
  : G4VSensitiveDetector(name)
  , fHitsCID(-1)
{
  fVPMTCollection = nullptr;
  collectionName.insert("vpmtCollection");
  quanEff = new G4PhysicsOrderedFreeVector();

  
  std::ifstream datafileVeto;
  datafileVeto.open("quantumeffEljin.dat");

  while(1)
    {
      G4double wlen, queff;

      datafileVeto >> wlen >> queff;

      if(datafileVeto.eof())
	break;

      //G4cout << wlen << " " << queff << G4endl;

      quanEff->InsertValues(wlen, queff/100);
    }
  
  datafileVeto.close();


  
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CSatVPMTSD::~CSatVPMTSD() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CSatVPMTSD::Initialize(G4HCofThisEvent* hitsCE)
{
  fVPMTCollection =
    new CSatVPMTHitsCollection(SensitiveDetectorName, collectionName[0]);

  if(fHitsCID < 0)
  {
    fHitsCID = G4SDManager::GetSDMpointer()->GetCollectionID(fVPMTCollection);
  }
  hitsCE->AddHitsCollection(fHitsCID, fVPMTCollection);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool CSatVPMTSD::ProcessHits(G4Step* aStep, G4TouchableHistory*) {

// need to know if this is an optical photon
  
  if(aStep->GetTrack()->GetDefinition() != G4OpticalPhoton::OpticalPhotonDefinition())
    {
      return false;
    }


  aStep->GetTrack()->SetTrackStatus(fStopAndKill);
  
   G4TouchableHistory* theTouchable =
    (G4TouchableHistory*) (aStep->GetPreStepPoint()->GetTouchable());
   
  G4VPhysicalVolume* thePrePV = theTouchable->GetVolume(0);


  G4StepPoint* thePrePoint = aStep->GetPreStepPoint();
  
  CSatVPMTHit* vpmtHit = new CSatVPMTHit(thePrePV);
  
  G4double mom = thePrePoint->GetMomentum().mag();
  G4double wavelength = (1.239841939*eV/mom)*1E+03*nm; 

  G4double timeV = aStep->GetTrack()->GetGlobalTime();

  
  if (G4UniformRand() < quanEff->Value(wavelength))
    {
      G4AnalysisManager::Instance()->FillNtupleDColumn(1 , 0 , timeV);
      G4AnalysisManager::Instance()->FillNtupleDColumn(1 , 1 , wavelength);
      G4AnalysisManager::Instance()->AddNtupleRow(1);
    }
 
  vpmtHit->SetTimeV(timeV);
  

  fVPMTCollection->insert(vpmtHit);

    
  return true;
    



}


