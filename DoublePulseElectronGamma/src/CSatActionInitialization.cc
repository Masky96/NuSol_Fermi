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
/// \file CSatActionInitialization.cc
/// \brief Implementation of the CSatActionInitialization class

#include "CSatActionInitialization.hh"

#include "CSatDetectorConstruction.hh"
#include "CSatEventAction.hh"
#include "CSatPrimaryGeneratorAction.hh"
#include "CSatRunAction.hh"
#include "CSatStackingAction.hh"
#include "CSatSteppingAction.hh"
#include "CSatTrackingAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CSatActionInitialization::CSatActionInitialization(
  const CSatDetectorConstruction* det)
  : G4VUserActionInitialization()
  , fDetector(det)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CSatActionInitialization::~CSatActionInitialization() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CSatActionInitialization::BuildForMaster() const
{
  SetUserAction(new CSatRunAction());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CSatActionInitialization::Build() const
{
  SetUserAction(new CSatPrimaryGeneratorAction());

  CSatEventAction* eventAction = new CSatEventAction(fDetector);
  SetUserAction(eventAction);
  SetUserAction(new CSatStackingAction(eventAction));

  SetUserAction(new CSatRunAction());
  SetUserAction(new CSatTrackingAction());
  SetUserAction(new CSatSteppingAction(eventAction));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
