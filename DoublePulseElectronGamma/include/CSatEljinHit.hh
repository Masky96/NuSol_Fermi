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
/// \file optical/CSat/include/CSatEljinHit.hh
/// \brief Definition of the CSatEljinHit class
//
//
#ifndef CSatEljinHit_h
#define CSatEljinHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4VPhysicalVolume.hh"

class CSatEljinHit : public G4VHit
{
 public:
  CSatEljinHit();
  CSatEljinHit(G4VPhysicalVolume* pVol);
  ~CSatEljinHit();

  CSatEljinHit(const CSatEljinHit& right);
  const CSatEljinHit& operator=(const CSatEljinHit& right);
  G4bool operator==(const CSatEljinHit& right) const;

  inline void* operator new(size_t);
  inline void operator delete(void* aHit);

  inline void SetEdep(G4double deE) { fEdepE = deE; }
  inline void AddEdep(G4double deE) { fEdepE += deE; }
  inline G4double GetEdepE() { return fEdepE; }

  // inline void SetPos(G4ThreeVector xyz) { fPos = xyz; }
  //inline G4ThreeVector GetPos() { return fPos; }

  inline const G4VPhysicalVolume* GetPhysVE() { return fPhysVolE; }

 private:
  G4double fEdepE;
  //G4ThreeVector fPos;
  const G4VPhysicalVolume* fPhysVolE;
};

typedef G4THitsCollection<CSatEljinHit> CSatEljinHitsCollection;

extern G4ThreadLocal G4Allocator<CSatEljinHit>* CSatEljinHitAllocator;

inline void* CSatEljinHit::operator new(size_t)
{
  if(!CSatEljinHitAllocator)
    CSatEljinHitAllocator = new G4Allocator<CSatEljinHit>;
  return (void*) CSatEljinHitAllocator->MallocSingle();
}

inline void CSatEljinHit::operator delete(void* aHit)
{
  CSatEljinHitAllocator->FreeSingle((CSatEljinHit*) aHit);
}

#endif
