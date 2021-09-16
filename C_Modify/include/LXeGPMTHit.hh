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
/// \file optical/LXe/include/LXeGPMTHit.hh
/// \brief Definition of the LXeGPMTHit class
//
//
#ifndef LXeGPMTHit_h
#define LXeGPMTHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4VPhysicalVolume.hh"

class LXeGPMTHit : public G4VHit
{
 public:
  LXeGPMTHit();
  LXeGPMTHit(G4VPhysicalVolume* pVolG);
  ~LXeGPMTHit();

  
  LXeGPMTHit(const LXeGPMTHit& right);
  const LXeGPMTHit& operator=(const LXeGPMTHit& right);
  G4bool operator==(const LXeGPMTHit& right) const;

  inline void* operator new(size_t);
  inline void operator delete(void* aHit);

  inline void SetEdepG(G4double de) { fEdepG = de; }
  inline void AddEdepG(G4double de) { fEdepG += de; }
  inline G4double GetEdepG() { return fEdepG; }

  //inline void SetPosG(G4ThreeVector xyz) { fPosG = xyz; }
  //inline G4ThreeVector GetPosG() { return fPosG; }

  
  inline const G4VPhysicalVolume* GetPhysG() { return fPhysVolG; }

 private:
  G4double fEdepG;
  G4ThreeVector fPosG;
  const G4VPhysicalVolume* fPhysVolG;
};

typedef G4THitsCollection<LXeGPMTHit> LXeGPMTHitsCollection;

extern G4ThreadLocal G4Allocator<LXeGPMTHit>* LXeGPMTHitAllocator;

inline void* LXeGPMTHit::operator new(size_t)
{
  if(!LXeGPMTHitAllocator)
    LXeGPMTHitAllocator = new G4Allocator<LXeGPMTHit>;
  return (void*) LXeGPMTHitAllocator->MallocSingle();
}

inline void LXeGPMTHit::operator delete(void* aHit)
{
  LXeGPMTHitAllocator->FreeSingle((LXeGPMTHit*) aHit);
}

#endif