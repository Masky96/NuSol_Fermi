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
/// \file optical/CSat/include/CSatGPMTHit.hh
/// \brief Definition of the CSatGPMTHit class
//
//
#ifndef CSatGPMTHit_h
#define CSatGPMTHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4VPhysicalVolume.hh"

class CSatGPMTHit : public G4VHit
{
 public:
  CSatGPMTHit();
  CSatGPMTHit(G4VPhysicalVolume* pVolG);
  ~CSatGPMTHit();

  
  CSatGPMTHit(const CSatGPMTHit& right);
  const CSatGPMTHit& operator=(const CSatGPMTHit& right);
  G4bool operator==(const CSatGPMTHit& right) const;

  inline void* operator new(size_t);
  inline void operator delete(void* aHit);

  inline void SetEdepG(G4double de) { fEdepG = de; }
  inline void AddEdepG(G4double de) { fEdepG += de; }
  inline G4double GetEdepG() { return fEdepG; }

  //inline void SetPosG(G4ThreeVector xyz) { fPosG = xyz; }
  //inline G4ThreeVector GetPosG() { return fPosG; }

  inline void SetTimeG(G4double tG) {ftimeG = tG; }
  inline void AddTimeG(G4double tG) {ftimeG += tG;}
  inline G4double GetTimeG() {return ftimeG; } 

  
  inline const G4VPhysicalVolume* GetPhysG() { return fPhysVolG; }

 private:
  G4double fEdepG;
  G4double ftimeG;
  G4ThreeVector fPosG;
  const G4VPhysicalVolume* fPhysVolG;
};

typedef G4THitsCollection<CSatGPMTHit> CSatGPMTHitsCollection;

extern G4ThreadLocal G4Allocator<CSatGPMTHit>* CSatGPMTHitAllocator;

inline void* CSatGPMTHit::operator new(size_t)
{
  if(!CSatGPMTHitAllocator)
    CSatGPMTHitAllocator = new G4Allocator<CSatGPMTHit>;
  return (void*) CSatGPMTHitAllocator->MallocSingle();
}

inline void CSatGPMTHit::operator delete(void* aHit)
{
  CSatGPMTHitAllocator->FreeSingle((CSatGPMTHit*) aHit);
}

#endif
