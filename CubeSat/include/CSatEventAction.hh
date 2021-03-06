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
/// \file optical/CSat/include/CSatEventAction.hh
/// \brief Definition of the CSatEventAction class
//

#ifndef CSatEventAction_h
#define CSatEventAction_h 1

//#include "CSatEventMessenger.hh"

#include "globals.hh"
#include "G4ThreeVector.hh"
#include "G4UserEventAction.hh"

class G4Event;
class CSatDetectorConstruction;

class CSatEventAction : public G4UserEventAction
{
 public:
  CSatEventAction(const CSatDetectorConstruction*);
  ~CSatEventAction();

 public:
  void BeginOfEventAction(const G4Event*) override;
  void EndOfEventAction(const G4Event*) override;

  void SetEventVerbose(G4int v) { fVerbose = v; }

  void SetPMTThreshold(G4int t) { fPMTThreshold = t; }

  void SetForceDrawPhotons(G4bool b) { fForcedrawphotons = b; }
  void SetForceDrawNoPhotons(G4bool b) { fForcenophotons = b; }

  void IncPhotonCount_Scint() { ++fPhotonCount_Scint; }
  void IncPhotonCount_Ceren() { ++fPhotonCount_Ceren; }
  void IncEDep(G4double dep) { fTotE += dep; }

  //New Additions
  void IncEDepE(G4double depE) {fTotEljin += depE; }

  void IncEDepG(G4double depG) {fTotEG += depG; }
  void IncEDepV(G4double depV) {fTotEV += depV; }
  

  
  void IncAbsorption() { ++fAbsorptionCount; }
  void IncBoundaryAbsorption() { ++fBoundaryAbsorptionCount; }
  void IncHitCount(G4int i = 1) { fHitCount += i; }
  
  void IncHitCount1(G4int i = 1) { fHitCount_1 += i; }
  void IncHitCount2(G4int i = 1) { fHitCount_2 += i; }
  void IncHitCount3(G4int i = 1) { fHitCount_3 += i; }


  //void TimeAdd(G4double time) {ftime += time; }
  
  
  void SetEWeightPos(const G4ThreeVector& p) { fEWeightPos = p; }
  void SetReconPos(const G4ThreeVector& p) { fReconPos = p; }
  void SetConvPos(const G4ThreeVector& p)
  {
    fConvPos    = p;
    fConvPosSet = true;
  }
  void SetPosMax(const G4ThreeVector& p, G4double edep)
  {
    fPosMax  = p;
    fEdepMax = edep;
  }

  G4int GetPhotonCount_Scint() const { return fPhotonCount_Scint; }
  G4int GetPhotonCount_Ceren() const { return fPhotonCount_Ceren; }
  G4int GetHitCount() const { return fHitCount; }
  G4double GetEDep() const { return fTotE; }
  //New---------------------------------------
  //G4double Getedep() const { return fedep; }
  G4double GetEDepE() const { return fTotEljin; }

  //Uncomment when I get things added. 
  G4double GetEdepV() const {return fTotEV; }
  G4double GetEdepG() const {return fTotEG; }


  
  //G4double GetTime() const { return ftime; } 
 
  G4int GetAbsorptionCount() const { return fAbsorptionCount; }
  G4int GetBoundaryAbsorptionCount() const { return fBoundaryAbsorptionCount; }

  G4ThreeVector GetEWeightPos() { return fEWeightPos; }
  G4ThreeVector GetReconPos() { return fReconPos; }
  G4ThreeVector GetConvPos() { return fConvPos; }
  G4ThreeVector GetPosMax() { return fPosMax; }
  G4double GetEDepMax() { return fEdepMax; }
  G4double IsConvPosSet() { return fConvPosSet; }

  // Gets the total photon count produced
  G4int GetPhotonCount() { return fPhotonCount_Scint + fPhotonCount_Ceren; }

  void IncPMTSAboveThreshold() { ++fPMTsAboveThreshold; }
  G4int GetPMTSAboveThreshold() { return fPMTsAboveThreshold; }

 private:
  //CSatEventMessenger* fEventMessenger;
  const CSatDetectorConstruction* fDetector;

  G4int fScintCollID;
  //G4int fPMTCollID;
  G4int fEljinCollID;
  G4int fVPMTCollID;
  G4int fGPMTCollID;
  

  G4int fVerbose;

  G4int fPMTThreshold;

  G4bool fForcedrawphotons;
  G4bool fForcenophotons;

  G4int fHitCount;
  
  G4int fHitCount_1;
  G4int fHitCount_2;
  G4int fHitCount_3;
  
  G4int fPhotonCount_Scint;
  G4int fPhotonCount_Ceren;
  G4int fAbsorptionCount;
  G4int fBoundaryAbsorptionCount;

  G4double fTotE;
  G4double fTotEljin;

  G4double fTotEV;
  G4double fTotEG;
  

  G4double fedep;
  G4double ftime;

  // These only have meaning if totE > 0
  // If totE = 0 then these won't be set by EndOfEventAction
  G4ThreeVector fEWeightPos;
  G4ThreeVector fReconPos;  // Also relies on hitCount>0
  G4ThreeVector fConvPos;   // true (initial) converstion position
  G4bool fConvPosSet;
  G4ThreeVector fPosMax;
  G4double fEdepMax;

  G4int fPMTsAboveThreshold;
};

#endif
