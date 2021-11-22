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
  quanEff = new G4PhysicsOrderedFreeVector();
  
  std::ifstream datafile;
  datafile.open("quantumeff.dat");

  while(1)
    {
      G4double wlen, queff;

      datafile >> wlen >> queff;

      if(datafile.eof())
	break;

      //G4cout << wlen << " " << queff << G4endl;

      quanEff->InsertValues(wlen, queff/100);
    }
  datafile.close();

  //quanEff->SetSpline(true);
  
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
 

  if(aStep->GetTrack()->GetDefinition() != G4OpticalPhoton::OpticalPhotonDefinition()) 
    {
      return false;
    }

  
    
  aStep->GetTrack()->SetTrackStatus(fStopAndKill);
  G4int evtID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
  G4TouchableHistory* theTouchable =
    (G4TouchableHistory*) (aStep->GetPreStepPoint()->GetTouchable());
  
  G4VPhysicalVolume* thePrePV = theTouchable->GetVolume(0);

  G4StepPoint* thePrePoint = aStep->GetPreStepPoint();
  

  CSatGPMTHit* gpmtHit = new CSatGPMTHit(thePrePV);
  
  G4float mom = thePrePoint->GetMomentum().mag();
  G4float wavelength = (1.239841939/mom)*1E+03*nm; 
  
  G4float timeG = aStep->GetTrack()->GetGlobalTime();


  
  if (G4UniformRand() < quanEff->Value(wavelength))
    {
      
	G4AnalysisManager::Instance()->FillNtupleFColumn(evtID+1 , 0 , timeG);
	G4AnalysisManager::Instance()->AddNtupleRow(evtID+1);
      
	//G4AnalysisManager::Instance()->FillH1(evtID+1,timeG);
      
    }

 
  
    
 
  gpmtHit->SetTimeG(timeG);

  fGPMTCollection->insert(gpmtHit);

  
  return true;





}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
