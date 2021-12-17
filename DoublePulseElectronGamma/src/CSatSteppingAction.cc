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
/// \file optical/CSat/src/CSatSteppingAction.cc
/// \brief Implementation of the CSatSteppingAction class
//
//
#include "CSatSteppingAction.hh"

#include "CSatEventAction.hh"
//#include "CSatPMTSD.hh"
//#include "CSatSteppingMessenger.hh"
#include "CSatTrajectory.hh"
#include "CSatUserTrackInformation.hh"

//---------New----------------
#include "CSatVPMTSD.hh"
#include "CSatGPMTSD.hh"

#include "G4OpticalPhoton.hh"
#include "G4ProcessManager.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"
#include "G4SteppingManager.hh"
#include "G4StepPoint.hh"
#include "G4Track.hh"
#include "G4TrackStatus.hh"
#include "G4VPhysicalVolume.hh"



#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

#include "G4ParticleTypes.hh"
#include "G4ParticleDefinition.hh"
#include "G4IonTable.hh"
#include "G4VProcess.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CSatSteppingAction::CSatSteppingAction(CSatEventAction* ea)
  : fOneStepPrimaries(false)
  , fEventAction(ea)
{
  //fSteppingMessenger = new CSatSteppingMessenger(this);

  fExpectedNextStatus = Undefined;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CSatSteppingAction::~CSatSteppingAction() {}
  //delete fSteppingMessenger; }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CSatSteppingAction::UserSteppingAction(const G4Step* theStep)
{


  G4double time = theStep->GetPreStepPoint()->GetGlobalTime();
  G4LogicalVolume* volume = theStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
  G4String name = volume->GetName();

  G4String particlename = theStep->GetTrack()->GetDefinition()->GetParticleName();
  
  G4int trackID = theStep->GetTrack()->GetTrackID();
  G4double energy = theStep->GetPreStepPoint()->GetTotalEnergy();


  const G4VProcess* creatorProcess = theStep->GetTrack()->GetCreatorProcess();
  G4String processName = "hello";
  
  //G4cout << particlename << G4endl;


  G4IonTable* ionTable = G4IonTable::GetIonTable();
  G4ParticleDefinition* germaniumground = ionTable->GetIon(32,69, 0*keV);
 
  //kill any tracks associated with the decay of the Germanium-69 ground state (64 hours)

  
  if(theStep->GetTrack()->GetDefinition() == germaniumground)
    {
      // G4cout << "Hello World" << G4endl;
      theStep->GetTrack()->SetTrackStatus(fStopAndKill);
    }
  /*
  if (time > 1*s) {
    
    theStep->GetTrack()->SetTrackStatus(fStopAndKill); 
    
  }
  */
























  
  G4Track* theTrack = theStep->GetTrack();

  if(theTrack->GetCurrentStepNumber() == 1)
    fExpectedNextStatus = Undefined;

  CSatUserTrackInformation* trackInformation =
    (CSatUserTrackInformation*) theTrack->GetUserInformation();

  G4StepPoint* thePrePoint    = theStep->GetPreStepPoint();
  G4VPhysicalVolume* thePrePV = thePrePoint->GetPhysicalVolume();

  G4StepPoint* thePostPoint    = theStep->GetPostStepPoint();
  G4VPhysicalVolume* thePostPV = thePostPoint->GetPhysicalVolume();

  G4OpBoundaryProcessStatus boundaryStatus           = Undefined;
  static G4ThreadLocal G4OpBoundaryProcess* boundary = nullptr;

  // find the boundary process only once
  if(!boundary)
    {
      G4ProcessManager* pm =
	theStep->GetTrack()->GetDefinition()->GetProcessManager();
      G4int nprocesses    = pm->GetProcessListLength();
      G4ProcessVector* pv = pm->GetProcessList();
      for(G4int i = 0; i < nprocesses; ++i)
	{
	  if((*pv)[i]->GetProcessName() == "OpBoundary")
	    {
	      boundary = (G4OpBoundaryProcess*) (*pv)[i];
	      break;
	    }
	}
    }

  if(theTrack->GetParentID() == 0)
    {
      // This is a primary track

      G4TrackVector* fSecondary = fpSteppingManager->GetfSecondary();
      G4int tN2ndariesTot       = fpSteppingManager->GetfN2ndariesAtRestDoIt() +
	fpSteppingManager->GetfN2ndariesAlongStepDoIt() +
	fpSteppingManager->GetfN2ndariesPostStepDoIt();

      // If we haven't already found the conversion position and there were
      // secondaries generated, then search for it
      if(!fEventAction->IsConvPosSet() && tN2ndariesTot > 0)
	{
	  for(size_t lp1 = (*fSecondary).size() - tN2ndariesTot;
	      lp1 < (*fSecondary).size(); ++lp1)
	    {
	      const G4VProcess* creator = (*fSecondary)[lp1]->GetCreatorProcess();
	      if(creator)
		{
		  G4String creatorName = creator->GetProcessName();
		  if(creatorName == "phot" || creatorName == "compt" ||
		     creatorName == "conv")
		    {
		      // since this is happening before the secondary is being tracked,
            // the vertex position has not been set yet (set in initial step)
            fEventAction->SetConvPos((*fSecondary)[lp1]->GetPosition());
          }
        }
      }
    }
      /*
    if(fOneStepPrimaries && thePrePV->GetName() == "scintillator")
      theTrack->SetTrackStatus(fStopAndKill);
      */
  }

  if(!thePostPV)
  {  // out of world
    fExpectedNextStatus = Undefined;
    return;
  }

  if(theTrack->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition())
  {
    // Optical photon only

    // Was the photon absorbed by the absorption process
    if(thePostPoint->GetProcessDefinedStep()->GetProcessName() ==
       "OpAbsorption")
    {
      fEventAction->IncAbsorption();
      trackInformation->AddTrackStatusFlag(absorbed);
    }

    boundaryStatus = boundary->GetStatus();

    if(thePostPoint->GetStepStatus() == fGeomBoundary)
    {
      // Check to see if the particle was actually at a boundary
      // Otherwise the boundary status may not be valid
      if(fExpectedNextStatus == StepTooSmall)
      {
        if(boundaryStatus != StepTooSmall)
        {
          G4ExceptionDescription ed;
          ed << "CSatSteppingAction::UserSteppingAction(): "
             << "No reallocation step after reflection!" << G4endl;
          G4Exception("CSatSteppingAction::UserSteppingAction()", "CSatExpl01",
                      FatalException, ed,
                      "Something is wrong with the surface normal or geometry");
        }
      }
      fExpectedNextStatus = Undefined;
      switch(boundaryStatus)
      {
        case Absorption:
          trackInformation->AddTrackStatusFlag(boundaryAbsorbed);
          fEventAction->IncBoundaryAbsorption();
          break;

        case FresnelReflection:
        case TotalInternalReflection:
        case LambertianReflection:
        case LobeReflection:
        case SpikeReflection:
	  //case BackScattering:
          //trackInformation->IncReflections();
          //fExpectedNextStatus = StepTooSmall;
          break;
        default:
          break;
      }
       }
  }
}
