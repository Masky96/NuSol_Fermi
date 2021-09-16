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
/// \file optical/LXe/src/LXeGPMTHit.cc
/// \brief Implementation of the LXeGPMTHit class
//
//
#include "LXeGPMTHit.hh"

#include "G4ios.hh"
#include "G4Colour.hh"
#include "G4LogicalVolume.hh"
#include "G4VisAttributes.hh"
#include "G4VPhysicalVolume.hh"
#include "G4VVisManager.hh"

G4ThreadLocal G4Allocator<LXeGPMTHit>* LXeGPMTHitAllocator = nullptr;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LXeGPMTHit::LXeGPMTHit()
  : fEdepG(0.)
    //, fPosG(0.)
  , fPhysVolG(nullptr)
  , ftimeG(0.)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
LXeGPMTHit::LXeGPMTHit(G4VPhysicalVolume* pVolG)
  : fPhysVolG(pVolG)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LXeGPMTHit::~LXeGPMTHit() {}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LXeGPMTHit::LXeGPMTHit(const LXeGPMTHit& right)
  : G4VHit()
{
  fEdepG    = right.fEdepG;
  //fPosG     = right.fPosG;
  fPhysVolG = right.fPhysVolG;
  ftimeG    = right.ftimeG;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const LXeGPMTHit& LXeGPMTHit::operator=(const LXeGPMTHit& right)
{
  fEdepG    = right.fEdepG;
  //fPosG     = right.fPosG;
  fPhysVolG = right.fPhysVolG;
  ftimeG    = right.ftimeG;
  return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4bool LXeGPMTHit::operator==(const LXeGPMTHit&) const
{
  return false;
  // returns false because there currently isn't need to check for equality
}
