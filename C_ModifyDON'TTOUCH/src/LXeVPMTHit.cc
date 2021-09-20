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
/// \file optical/LXe/src/LXeVPMTHit.cc
/// \brief Implementation of the LXeVPMTHit class
//
//
#include "LXeVPMTHit.hh"

#include "G4ios.hh"
#include "G4Colour.hh"
#include "G4LogicalVolume.hh"
#include "G4VisAttributes.hh"
#include "G4VPhysicalVolume.hh"
#include "G4VVisManager.hh"

G4ThreadLocal G4Allocator<LXeVPMTHit>* LXeVPMTHitAllocator = nullptr;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LXeVPMTHit::LXeVPMTHit()
  : fEdepV(0.)
    //, fPosV(0.)
  , fPhysVolV(nullptr)
  , ftimeV(0.)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LXeVPMTHit::LXeVPMTHit(G4VPhysicalVolume* pVol)
  : fPhysVolV(pVol)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LXeVPMTHit::~LXeVPMTHit() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LXeVPMTHit::LXeVPMTHit(const LXeVPMTHit& right)
  : G4VHit()
{
  fEdepV    = right.fEdepV;
  //fPosV     = right.fPosV;
  fPhysVolV = right.fPhysVolV;
  ftimeV    = right.ftimeV;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const LXeVPMTHit& LXeVPMTHit::operator=(const LXeVPMTHit& right)
{
  fEdepV    = right.fEdepV;
  //fPosV     = right.fPosV;
  fPhysVolV = right.fPhysVolV;
  ftimeV    = right.ftimeV;
  return *this;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool LXeVPMTHit::operator==(const LXeVPMTHit&) const
{
  return false;
  // returns false because there currently isn't need to check for equality
}
