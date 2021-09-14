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
/// \file optical/LXe/src/LXePrimaryGeneratorAction.cc
/// \brief Implementation of the LXePrimaryGeneratorAction class
//
//
#include "LXePrimaryGeneratorAction.hh"

#include "globals.hh"
#include "G4Event.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"

#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4LogicalVolumeStore.hh"
#include "Randomize.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LXePrimaryGeneratorAction::LXePrimaryGeneratorAction()
{
  G4int n_particle = 1;

  G4double x0 =  50.*(G4UniformRand() -0.5)*km;
  G4double y0 =  50.*(G4UniformRand() -0.5)*km;
  G4double z0 =  -5*km;
  //G4double z0 =  50.*(G4UniformRand() -0.5)*km;
  /*
  G4double x0 = 4.*G4UniformRand()*km;
  G4double y0 = sqrt(4*km - x0*x0);

  val = G4UniformRand()*100;
  if (val>0 && val <=25)
    {
      x0 =-1*x0;
      y0 = y0;
    }
  else if(val>25 && val <=50)
    {
      x0 = x0;
      y0 = -1*y0;
    }
  else if(val>50 && val <=75)
    {
      x0 = x0;
      y0 = y0;
    }
  else
    {
      x0 = -1*x0;
      y0 = -1*y0;
    }
  
      
  
  
  G4double z0 = -50.*km;
  G4double startPoint = -24572.*km
  G4double openAngle = 0.1;
  */


  
  fParticleGun     = new G4ParticleGun(n_particle);

  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();

  G4String particleName;
  fParticleGun->SetParticleDefinition(
    particleTable->FindParticle(particleName = "mu-"));
  // Default energy,position,momentum
  fParticleGun->SetParticleEnergy(100. * GeV);
  fParticleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0,0,1));
					     //fParticleGun->SetParticleMomentumDirection(G4ThreeVector(sin(openAngle*G4UniformRand()),sin(openAngle*G4UniformRand()),cos(openAngle*G4UniformRand())));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LXePrimaryGeneratorAction::~LXePrimaryGeneratorAction() { delete fParticleGun; }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LXePrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{


  fParticleGun->GeneratePrimaryVertex(anEvent);
}
