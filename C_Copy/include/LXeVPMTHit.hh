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
/// \file optical/LXe/include/LXeVPMTHit.hh
/// \brief Definition of the LXeVPMTHit class
//
//
#ifndef LXeVPMTHit_h
#define LXeVPMTHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4VPhysicalVolume.hh"

class LXeVPMTHit : public G4VHit
{
 public:
  LXeVPMTHit();
  LXeVPMTHit(G4VPhysicalVolume*pVolV);
  ~LXeVPMTHit();

  LXeVPMTHit(const LXeVPMTHit& right);
  const LXeVPMTHit& operator=(const LXeVPMTHit& right);
  G4bool operator==(const LXeVPMTHit& right) const;

  inline void* operator new(size_t);
  inline void operator delete(void* aHit);

  inline void SetEdepV(G4double de) { fEdepV = de; }
  inline void AddEdepV(G4double de) { fEdepV += de; }
  inline G4double GetEdepV() { return fEdepV; }

  inline void SetTimeV(G4double tV) {ftimeV = tV; }
  inline void AddTimeV(G4double tV) {ftimeV += tV;}
  inline G4double GetTimeV() {return ftimeV; } 


  
  inline const G4VPhysicalVolume* GetPhysV() { return fPhysVolV; }

 private:
  G4double fEdepV;
  G4double ftimeV;
  G4ThreeVector fPosV;
  const G4VPhysicalVolume* fPhysVolV;
};

typedef G4THitsCollection<LXeVPMTHit> LXeVPMTHitsCollection;

extern G4ThreadLocal G4Allocator<LXeVPMTHit>* LXeVPMTHitAllocator;

inline void* LXeVPMTHit::operator new(size_t)
{
  if(!LXeVPMTHitAllocator)
    LXeVPMTHitAllocator = new G4Allocator<LXeVPMTHit>;
  return (void*) LXeVPMTHitAllocator->MallocSingle();
}

inline void LXeVPMTHit::operator delete(void* aHit)
{
  LXeVPMTHitAllocator->FreeSingle((LXeVPMTHit*) aHit);
}

#endif
