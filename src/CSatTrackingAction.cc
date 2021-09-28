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
/// \file optical/CSat/src/CSatTrackingAction.cc
/// \brief Implementation of the CSatTrackingAction class
//
//
#include "CSatTrackingAction.hh"

#include "CSatDetectorConstruction.hh"
#include "CSatTrajectory.hh"
#include "CSatUserTrackInformation.hh"

#include "G4OpticalPhoton.hh"
#include "G4Track.hh"
#include "G4TrackingManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CSatTrackingAction::CSatTrackingAction() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CSatTrackingAction::PreUserTrackingAction(const G4Track* aTrack)
{
  // Let this be up to the user via vis.mac
  //  fpTrackingManager->SetStoreTrajectory(true);

  // Use custom trajectory class
  fpTrackingManager->SetTrajectory(new CSatTrajectory(aTrack));

  // This user track information is only relevant to the photons
  fpTrackingManager->SetUserTrackInformation(new CSatUserTrackInformation);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CSatTrackingAction::PostUserTrackingAction(const G4Track* aTrack)
{
  CSatTrajectory* trajectory =
    (CSatTrajectory*) fpTrackingManager->GimmeTrajectory();
  CSatUserTrackInformation* trackInformation =
    (CSatUserTrackInformation*) aTrack->GetUserInformation();

  trajectory->SetDrawTrajectory(true);

  // Let's choose to draw only the photons that hit the sphere and a pmt
  if(aTrack->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition())
  {
    /*
    const G4VProcess* creator = aTrack->GetCreatorProcess();
    if(creator && creator->GetProcessName() == "OpWLS")
    {
      trajectory->WLS();
      trajectory->SetDrawTrajectory(true);
    }
    
    if(CSatDetectorConstruction::GetSphereOn())
    {
      if((trackInformation->GetTrackStatus() & hitPMT) &&
         (trackInformation->GetTrackStatus() & hitSphere))
      {
        trajectory->SetDrawTrajectory(true);
      }
    }
    else
    {
      if(trackInformation->GetTrackStatus() & hitPMT)
        trajectory->SetDrawTrajectory(true);
    }
    */
      if(trackInformation->GetTrackStatus() & hitPMT)
        trajectory->SetDrawTrajectory(true);
    
    
  }
  // draw all other (not optical photon) trajectories
  
  
  else
    trajectory->SetDrawTrajectory(true);

  if(trackInformation->GetForceDrawTrajectory())
    trajectory->SetDrawTrajectory(true);
}
