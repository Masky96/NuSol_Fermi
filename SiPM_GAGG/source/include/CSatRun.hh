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
// * for the full disclaimer and the limitation of liability.
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file optical/CSat/include/CSatRun.hh
/// \brief Definition of the CSatRun class
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef CSatRun_h
#define CSatRun_h 1

#include "globals.hh"
#include "G4Run.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class CSatRun : public G4Run
{
 public:
  CSatRun();
  ~CSatRun();


  void IncPhotonCount_Scint(G4int count)
  {
    fPhotonCount_Scint += count;
    fPhotonCount_Scint2 += count * count;
  }
  void IncPhotonCount_Ceren(G4int count)
  {
    fPhotonCount_Ceren += count;
    fPhotonCount_Ceren2 += count * count;
  }
  void IncEDep(G4double dep)
  {
    fTotE += dep;
    fTotE2 += dep * dep;
  }

  //New
  void IncEDepE(G4double depE)
  {
    fTotEljin += depE;
    fTotEljin2 += depE * depE;
  }
  
void IncEDepG(G4double depG)
  {
    fTotEG += depG;
    fTotEG2 += depG * depG;
  }

void IncEDepV(G4double depV)
  {
    fTotEV += depV;
    fTotEV2 += depV * depV;
  }


  
  void IncAbsorption(G4int count)
  {
    fAbsorptionCount += count;
    fAbsorptionCount2 += count * count;
  }
  void IncBoundaryAbsorption(G4int count)
  {
    fBoundaryAbsorptionCount += count;
    fBoundaryAbsorptionCount2 += count * count;
  }
  void IncHitCount(G4int count)
  {
    fHitCount += count;
    fHitCount2 += count * count;
  }

void IncHitCount1(G4int count)
  {
    fHitCount_1 += count;
    fHitCount_12 += count * count;
  }
  void IncHitCount2(G4int count)
  {
    fHitCount_2 += count;
    fHitCount_22 += count * count;
  }

void IncHitCount3(G4int count)
  {
    fHitCount_3 += count;
    fHitCount_32 += count * count;
  }









  
  void IncHitsAboveThreshold(G4int count)
  {
    fPMTsAboveThreshold += count;
    fPMTsAboveThreshold2 += count * count;
  }

  void Merge(const G4Run* run) override;

  void EndOfRun();
  
  

 private:
  G4int fHitCount;
  G4int fHitCount2;

  
  G4int fHitCount_1;
  G4int fHitCount_12;

  G4int fHitCount_2;
  G4int fHitCount_22;

  G4int fHitCount_3;
  G4int fHitCount_32;


  
  G4int fPhotonCount_Scint;
  G4int fPhotonCount_Scint2;
  G4int fPhotonCount_Ceren;
  G4int fPhotonCount_Ceren2;
  G4int fAbsorptionCount;
  G4int fAbsorptionCount2;
  G4int fBoundaryAbsorptionCount;
  G4int fBoundaryAbsorptionCount2;
  G4int fPMTsAboveThreshold;
  G4int fPMTsAboveThreshold2;

  G4double fTotE;
  G4double fTotE2;
  G4double fTotEljin;
  G4double fTotEljin2;

  G4double fTotEG;
  G4double fTotEG2;

  G4double fTotEV;
  G4double fTotEV2;


  
};

#endif  // CSatRun_h
