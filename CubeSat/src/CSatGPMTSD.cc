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

      G4cout << wlen << " " << queff << G4endl;

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

  G4AnalysisManager::Instance()->FillNtupleDColumn(1 , 0 , timeG);
  G4AnalysisManager::Instance()->FillNtupleDColumn(1 , 1 , wavelength);
  G4AnalysisManager::Instance()->AddNtupleRow(1);
  
  if (G4UniformRand() < quanEff->Value(wavelength))
    {
  G4AnalysisManager::Instance()->FillNtupleDColumn(2 , 0 , timeG);
  G4AnalysisManager::Instance()->FillNtupleDColumn(2 , 1 , wavelength);
  G4AnalysisManager::Instance()->AddNtupleRow(2);
  
    }
  
  if(evtID == 0)
    {
      if (parentID == 6 )
	{
	  G4AnalysisManager::Instance()->FillNtupleDColumn(4 , 0 , timeG);
	  G4AnalysisManager::Instance()->AddNtupleRow(4);
	  //G4AnalysisManager::Instance()->FillH1(1, timeG);
	  //G4AnalysisManager::Instance()->FillNtupleDColumn(3 , 0 , timeG);
	  //G4AnalysisManager::Instance()->AddNtupleRow(3);
	}
      else
	{
	  //G4AnalysisManager::Instance()->FillH1(2, timeG);
	  //G4AnalysisManager::Instance()->FillNtupleDColumn(4 , 0 , timeG);
	  //G4AnalysisManager::Instance()->AddNtupleRow(4);
	  G4AnalysisManager::Instance()->FillNtupleDColumn(3 , 0 , timeG);
	  G4AnalysisManager::Instance()->AddNtupleRow(3);
	  
	}
    }

  if(evtID == 1)
    {
      if (parentID == 6)
	{
	  //G4AnalysisManager::Instance()->FillH1(3, timeG);
	  // G4AnalysisManager::Instance()->FillNtupleDColumn(5 , 0 , timeG);
	  //G4AnalysisManager::Instance()->AddNtupleRow(5);
	  G4AnalysisManager::Instance()->FillNtupleDColumn(6 , 0 , timeG);
	  G4AnalysisManager::Instance()->AddNtupleRow(6);
	}
      else
	{
	  //G4AnalysisManager::Instance()->FillH1(4, timeG);
	  //G4AnalysisManager::Instance()->FillNtupleDColumn(6 , 0 , timeG);
	  //G4AnalysisManager::Instance()->AddNtupleRow(6);
	  G4AnalysisManager::Instance()->FillNtupleDColumn(5 , 0 , timeG);
	  G4AnalysisManager::Instance()->AddNtupleRow(5);
	}
    }

  if(evtID == 2)
    {
      if (parentID == 6)
	{
	  //G4AnalysisManager::Instance()->FillH1(5, timeG);
	  //G4AnalysisManager::Instance()->FillNtupleDColumn(7 , 0 , timeG);
	  //G4AnalysisManager::Instance()->AddNtupleRow(7);
	  G4AnalysisManager::Instance()->FillNtupleDColumn(8 , 0 , timeG);
	  G4AnalysisManager::Instance()->AddNtupleRow(8);
	}
      else
	{
	  //G4AnalysisManager::Instance()->FillH1(6, timeG);
	  //G4AnalysisManager::Instance()->FillNtupleDColumn(8 , 0 , timeG);
	  //G4AnalysisManager::Instance()->AddNtupleRow(8);
	  G4AnalysisManager::Instance()->FillNtupleDColumn(7 , 0 , timeG);
	  G4AnalysisManager::Instance()->AddNtupleRow(7);
	}
    }


  if(evtID == 3)
    {
      if (parentID == 6)
	{
	  //G4AnalysisManager::Instance()->FillH1(7, timeG);
	  //G4AnalysisManager::Instance()->FillNtupleDColumn(9 , 0 , timeG);
	  //G4AnalysisManager::Instance()->AddNtupleRow(9);
	  G4AnalysisManager::Instance()->FillNtupleDColumn(10 , 0 , timeG);
	  G4AnalysisManager::Instance()->AddNtupleRow(10);
	}
      else
	{
	  //G4AnalysisManager::Instance()->FillH1(8, timeG);
	  //G4AnalysisManager::Instance()->FillNtupleDColumn(10 , 0 , timeG);
	  //G4AnalysisManager::Instance()->AddNtupleRow(10);
	  G4AnalysisManager::Instance()->FillNtupleDColumn(9 , 0 , timeG);
	  G4AnalysisManager::Instance()->AddNtupleRow(9);
	}
    }

  if(evtID == 4)
    {
      if (parentID == 6)
	{
	  //G4AnalysisManager::Instance()->FillH1(9, timeG);
	  //G4AnalysisManager::Instance()->FillNtupleDColumn(11 , 0 , timeG);
	  //G4AnalysisManager::Instance()->AddNtupleRow(11);
	  G4AnalysisManager::Instance()->FillNtupleDColumn(12 , 0 , timeG);
	  G4AnalysisManager::Instance()->AddNtupleRow(12);
	}
      else
	{
	  //G4AnalysisManager::Instance()->FillH1(10, timeG);
	  //G4AnalysisManager::Instance()->FillNtupleDColumn(12 , 0 , timeG);
	  //G4AnalysisManager::Instance()->AddNtupleRow(12);
	  G4AnalysisManager::Instance()->FillNtupleDColumn(11 , 0 , timeG);
	  G4AnalysisManager::Instance()->AddNtupleRow(11);
	}
    }

  if(evtID == 5)
    {
      if (parentID == 6)
	{
	  //G4AnalysisManager::Instance()->FillH1(11, timeG);
	  //G4AnalysisManager::Instance()->FillNtupleDColumn(13 , 0 , timeG);
	  //G4AnalysisManager::Instance()->AddNtupleRow(13);
	  G4AnalysisManager::Instance()->FillNtupleDColumn(14 , 0 , timeG);
	  G4AnalysisManager::Instance()->AddNtupleRow(14);
	}
      else
	{
	  //G4AnalysisManager::Instance()->FillH1(12, timeG);
	  //G4AnalysisManager::Instance()->FillNtupleDColumn(14 , 0 , timeG);
	  //G4AnalysisManager::Instance()->AddNtupleRow(14);
	  G4AnalysisManager::Instance()->FillNtupleDColumn(13 , 0 , timeG);
	  G4AnalysisManager::Instance()->AddNtupleRow(13);
	}
    }

  if(evtID == 6)
    {
      if (parentID == 6)
	{
	  //G4AnalysisManager::Instance()->FillH1(13, timeG);
	  //G4AnalysisManager::Instance()->FillNtupleDColumn(15 , 0 , timeG);
	  //G4AnalysisManager::Instance()->AddNtupleRow(15);
	  G4AnalysisManager::Instance()->FillNtupleDColumn(16 , 0 , timeG);
	  G4AnalysisManager::Instance()->AddNtupleRow(16);
	}
      else
	{
	  //G4AnalysisManager::Instance()->FillH1(14, timeG);
	  //G4AnalysisManager::Instance()->FillNtupleDColumn(16 , 0 , timeG);
	  //G4AnalysisManager::Instance()->AddNtupleRow(16);
	  G4AnalysisManager::Instance()->FillNtupleDColumn(15 , 0 , timeG);
	  G4AnalysisManager::Instance()->AddNtupleRow(15);
	}
    }

  if(evtID == 7)
    {
      if (parentID == 6)
	{
	  //G4AnalysisManager::Instance()->FillH1(15, timeG);
	  //G4AnalysisManager::Instance()->FillNtupleDColumn(17 , 0 , timeG);
	  // G4AnalysisManager::Instance()->AddNtupleRow(17);
	  G4AnalysisManager::Instance()->FillNtupleDColumn(18 , 0 , timeG);
	  G4AnalysisManager::Instance()->AddNtupleRow(18);
	}
      else
	{
	  //G4AnalysisManager::Instance()->FillH1(16, timeG);
	  //G4AnalysisManager::Instance()->FillNtupleDColumn(18 , 0 , timeG);
	  //G4AnalysisManager::Instance()->AddNtupleRow(18);
	  G4AnalysisManager::Instance()->FillNtupleDColumn(17 , 0 , timeG);
	  G4AnalysisManager::Instance()->AddNtupleRow(17);
	}
    }


  if(evtID == 8)
    {
      if (parentID == 6)
	{
	  //G4AnalysisManager::Instance()->FillH1(17, timeG);
	  //G4AnalysisManager::Instance()->FillNtupleDColumn(19 , 0 , timeG);
	  //G4AnalysisManager::Instance()->AddNtupleRow(19);
	  G4AnalysisManager::Instance()->FillNtupleDColumn(20 , 0 , timeG);
	  G4AnalysisManager::Instance()->AddNtupleRow(20);
	}
      else
	{
	  //G4AnalysisManager::Instance()->FillH1(18, timeG);
	  //G4AnalysisManager::Instance()->FillNtupleDColumn(20 , 0 , timeG);
	  //G4AnalysisManager::Instance()->AddNtupleRow(20);
	  G4AnalysisManager::Instance()->FillNtupleDColumn(19 , 0 , timeG);
	  G4AnalysisManager::Instance()->AddNtupleRow(19);
	}
    }

  if(evtID == 9)
    {
      if (parentID == 6)
	{
	  //G4AnalysisManager::Instance()->FillH1(19, timeG);
	  //G4AnalysisManager::Instance()->FillNtupleDColumn(21 , 0 , timeG);
	  //G4AnalysisManager::Instance()->AddNtupleRow(21);
	  G4AnalysisManager::Instance()->FillNtupleDColumn(22 , 0 , timeG);
	  G4AnalysisManager::Instance()->AddNtupleRow(22);
	}
      else
	{
	  // G4AnalysisManager::Instance()->FillH1(20, timeG);
	  //G4AnalysisManager::Instance()->FillNtupleDColumn(22 , 0 , timeG);
	  //G4AnalysisManager::Instance()->AddNtupleRow(22);
	  G4AnalysisManager::Instance()->FillNtupleDColumn(21 , 0 , timeG);
	  G4AnalysisManager::Instance()->AddNtupleRow(21);
	}
    }

  if(evtID == 10)
    {
      if (parentID == 6)
	{
	  //G4AnalysisManager::Instance()->FillH1(21, timeG);
	  // G4AnalysisManager::Instance()->FillNtupleDColumn(23 , 0 , timeG);
	  //G4AnalysisManager::Instance()->AddNtupleRow(23);
	  G4AnalysisManager::Instance()->FillNtupleDColumn(24 , 0 , timeG);
	  G4AnalysisManager::Instance()->AddNtupleRow(24);
	}
      else
	{
	  //G4AnalysisManager::Instance()->FillH1(22, timeG);
	  //G4AnalysisManager::Instance()->FillNtupleDColumn(24 , 0 , timeG);
	  //G4AnalysisManager::Instance()->AddNtupleRow(24);
	  G4AnalysisManager::Instance()->FillNtupleDColumn(23 , 0 , timeG);
	  G4AnalysisManager::Instance()->AddNtupleRow(23);
	}
    }


  if(evtID == 11)
    {
      if (parentID == 6)
	{
	  //G4AnalysisManager::Instance()->FillH1(23, timeG);
	  //G4AnalysisManager::Instance()->FillNtupleDColumn(25 , 0 , timeG);
	  //G4AnalysisManager::Instance()->AddNtupleRow(25);
	  G4AnalysisManager::Instance()->FillNtupleDColumn(26 , 0 , timeG);
	  G4AnalysisManager::Instance()->AddNtupleRow(26);
	}
      else
	{
	  //G4AnalysisManager::Instance()->FillH1(24, timeG);
	  //G4AnalysisManager::Instance()->FillNtupleDColumn(26 , 0 , timeG);
	  //G4AnalysisManager::Instance()->AddNtupleRow(26);
	  G4AnalysisManager::Instance()->FillNtupleDColumn(25 , 0 , timeG);
	  G4AnalysisManager::Instance()->AddNtupleRow(25);
	}
    }

  if(evtID == 12)
    {
      if (parentID == 6)
	{
	  //G4AnalysisManager::Instance()->FillH1(25, timeG);
	  //G4AnalysisManager::Instance()->FillNtupleDColumn(27 , 0 , timeG);
	  //G4AnalysisManager::Instance()->AddNtupleRow(27);
	  G4AnalysisManager::Instance()->FillNtupleDColumn(28 , 0 , timeG);
	  G4AnalysisManager::Instance()->AddNtupleRow(28); 
	}
      else
	{
	  //G4AnalysisManager::Instance()->FillH1(26, timeG);
	  //G4AnalysisManager::Instance()->FillNtupleDColumn(28 , 0 , timeG);
	  //G4AnalysisManager::Instance()->AddNtupleRow(28);
	  G4AnalysisManager::Instance()->FillNtupleDColumn(27 , 0 , timeG);
	  G4AnalysisManager::Instance()->AddNtupleRow(27);
	  
	}
    }


  if(evtID == 13)
    {
      if (parentID == 6)
	{
	  //G4AnalysisManager::Instance()->FillH1(27, timeG);
	  //G4AnalysisManager::Instance()->FillNtupleDColumn(29 , 0 , timeG);
	  //G4AnalysisManager::Instance()->AddNtupleRow(29);
	  G4AnalysisManager::Instance()->FillNtupleDColumn(30 , 0 , timeG);
	  G4AnalysisManager::Instance()->AddNtupleRow(30);
	}
      else
	{
	  //G4AnalysisManager::Instance()->FillH1(28, timeG);
	  //G4AnalysisManager::Instance()->FillNtupleDColumn(30 , 0 , timeG);
	  //G4AnalysisManager::Instance()->AddNtupleRow(30);
	  G4AnalysisManager::Instance()->FillNtupleDColumn(29 , 0 , timeG);
	  G4AnalysisManager::Instance()->AddNtupleRow(29);
	}
    }


  if(evtID == 14)
    {
      if (parentID == 6)
	{
	  //G4AnalysisManager::Instance()->FillH1(29, timeG);
	  //G4AnalysisManager::Instance()->FillNtupleDColumn(31 , 0 , timeG);
	  //G4AnalysisManager::Instance()->AddNtupleRow(31);
	  G4AnalysisManager::Instance()->FillNtupleDColumn(32 , 0 , timeG);
	  G4AnalysisManager::Instance()->AddNtupleRow(32);
	}
      else
	{
	  //G4AnalysisManager::Instance()->FillH1(30, timeG);
	  //G4AnalysisManager::Instance()->FillNtupleDColumn(32 , 0 , timeG);
	  //G4AnalysisManager::Instance()->AddNtupleRow(32);
	  G4AnalysisManager::Instance()->FillNtupleDColumn(31 , 0 , timeG);
	  G4AnalysisManager::Instance()->AddNtupleRow(31);
	}
    }

  if(evtID == 15)
    {
      if (parentID == 6)
	{
	  //G4AnalysisManager::Instance()->FillH1(31, timeG);
	  //G4AnalysisManager::Instance()->FillNtupleDColumn(33 , 0 , timeG);
	  //G4AnalysisManager::Instance()->AddNtupleRow(33);
	  G4AnalysisManager::Instance()->FillNtupleDColumn(34 , 0 , timeG);
	  G4AnalysisManager::Instance()->AddNtupleRow(34);
	}
      else
	{
	  //G4AnalysisManager::Instance()->FillH1(32, timeG);
	  //G4AnalysisManager::Instance()->FillNtupleDColumn(34 , 0 , timeG);
	  //G4AnalysisManager::Instance()->AddNtupleRow(34);
	  G4AnalysisManager::Instance()->FillNtupleDColumn(33 , 0 , timeG);
	  G4AnalysisManager::Instance()->AddNtupleRow(33);
	}
    }
  if(evtID == 16)
    {
      if (parentID == 6)
	{
	  //G4AnalysisManager::Instance()->FillH1(33, timeG);
	  //G4AnalysisManager::Instance()->FillNtupleDColumn(35 , 0 , timeG);
	  //G4AnalysisManager::Instance()->AddNtupleRow(35);
	  G4AnalysisManager::Instance()->FillNtupleDColumn(36 , 0 , timeG);
	  G4AnalysisManager::Instance()->AddNtupleRow(36);
	}
      else
	{
	  //G4AnalysisManager::Instance()->FillH1(34, timeG);
	  //G4AnalysisManager::Instance()->FillNtupleDColumn(36 , 0 , timeG);
	  //G4AnalysisManager::Instance()->AddNtupleRow(36);
	  G4AnalysisManager::Instance()->FillNtupleDColumn(35 , 0 , timeG);
	  G4AnalysisManager::Instance()->AddNtupleRow(35);
	}
    }

  if(evtID == 17)
    {
      if (parentID == 6)
	{
	  //G4AnalysisManager::Instance()->FillH1(35, timeG);
	  //G4AnalysisManager::Instance()->FillNtupleDColumn(37 , 0 , timeG);
	  //G4AnalysisManager::Instance()->AddNtupleRow(37);
	  G4AnalysisManager::Instance()->FillNtupleDColumn(38 , 0 , timeG);
	  G4AnalysisManager::Instance()->AddNtupleRow(38);
	}
      else
	{
	  //G4AnalysisManager::Instance()->FillH1(36, timeG);
	  //G4AnalysisManager::Instance()->FillNtupleDColumn(38 , 0 , timeG);
	  //G4AnalysisManager::Instance()->AddNtupleRow(38);
	  G4AnalysisManager::Instance()->FillNtupleDColumn(37 , 0 , timeG);
	  G4AnalysisManager::Instance()->AddNtupleRow(37);
	}
    }

  if(evtID == 18)
    {
      if (parentID == 6)
	{
	  //G4AnalysisManager::Instance()->FillH1(37, timeG);
	  //G4AnalysisManager::Instance()->FillNtupleDColumn(39 , 0 , timeG);
	  //G4AnalysisManager::Instance()->AddNtupleRow(39);
	  G4AnalysisManager::Instance()->FillNtupleDColumn(40 , 0 , timeG);
	  G4AnalysisManager::Instance()->AddNtupleRow(40); 
	}
      else
	{
	  //G4AnalysisManager::Instance()->FillH1(38, timeG);
	  //G4AnalysisManager::Instance()->FillNtupleDColumn(40 , 0 , timeG);
	  //G4AnalysisManager::Instance()->AddNtupleRow(40);
	  G4AnalysisManager::Instance()->FillNtupleDColumn(39 , 0 , timeG);
	  G4AnalysisManager::Instance()->AddNtupleRow(39);
	}
    }

  if(evtID == 19)
    {
      if (parentID == 6)
	{
	  //G4AnalysisManager::Instance()->FillH1(39, timeG);
	  //G4AnalysisManager::Instance()->FillNtupleDColumn(41 , 0 , timeG);
	  //G4AnalysisManager::Instance()->AddNtupleRow(41);
	  G4AnalysisManager::Instance()->FillNtupleDColumn(42 , 0 , timeG);
	  G4AnalysisManager::Instance()->AddNtupleRow(42);
	}
      else
	{
	  //G4AnalysisManager::Instance()->FillH1(40, timeG);
	  //G4AnalysisManager::Instance()->FillNtupleDColumn(42 , 0 , timeG);
	  //G4AnalysisManager::Instance()->AddNtupleRow(42);
	  G4AnalysisManager::Instance()->FillNtupleDColumn(41 , 0 , timeG);
	  G4AnalysisManager::Instance()->AddNtupleRow(41);
	}
    }



  
  
 
  gpmtHit->SetTimeG(timeG);

  fGPMTCollection->insert(gpmtHit);

  
  return true;





}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
