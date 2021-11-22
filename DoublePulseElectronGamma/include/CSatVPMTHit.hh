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
/// \file optical/CSat/include/CSatVPMTHit.hh
/// \brief Definition of the CSatVPMTHit class
//
//
#ifndef CSatVPMTHit_h
#define CSatVPMTHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4VPhysicalVolume.hh"

class CSatVPMTHit : public G4VHit
{
 public:
  CSatVPMTHit();
  CSatVPMTHit(G4VPhysicalVolume*pVolV);
  ~CSatVPMTHit();

  CSatVPMTHit(const CSatVPMTHit& right);
  const CSatVPMTHit& operator=(const CSatVPMTHit& right);
  G4bool operator==(const CSatVPMTHit& right) const;

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

typedef G4THitsCollection<CSatVPMTHit> CSatVPMTHitsCollection;

extern G4ThreadLocal G4Allocator<CSatVPMTHit>* CSatVPMTHitAllocator;

inline void* CSatVPMTHit::operator new(size_t)
{
  if(!CSatVPMTHitAllocator)
    CSatVPMTHitAllocator = new G4Allocator<CSatVPMTHit>;
  return (void*) CSatVPMTHitAllocator->MallocSingle();
}

inline void CSatVPMTHit::operator delete(void* aHit)
{
  CSatVPMTHitAllocator->FreeSingle((CSatVPMTHit*) aHit);
}

#endif
