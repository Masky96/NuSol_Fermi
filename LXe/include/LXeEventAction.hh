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
/// \file optical/LXe/include/LXeEventAction.hh
/// \brief Definition of the LXeEventAction class
//

#ifndef LXeEventAction_h
#define LXeEventAction_h 1

#include "LXeEventMessenger.hh"

#include "globals.hh"
#include "G4ThreeVector.hh"
#include "G4UserEventAction.hh"

class G4Event;
class LXeDetectorConstruction;

class LXeEventAction : public G4UserEventAction
{
 public:
  LXeEventAction(const LXeDetectorConstruction*);
  ~LXeEventAction();

 public:
  void BeginOfEventAction(const G4Event*) override;
  void EndOfEventAction(const G4Event*) override;

  void SetEventVerbose(G4int v) { fVerbose = v; }

  void SetPMTThreshold(G4int t) { fPMTThreshold = t; }

  void SetForceDrawPhotons(G4bool b) { fForcedrawphotons = b; }
  void SetForceDrawNoPhotons(G4bool b) { fForcenophotons = b; }

//New---------------------------------------------
  void IncEDepP(G4double depP)     {fTotEP += depP; }
  void IncEDepP1(G4double depP1)   {fTotEP1 += depP1; }
  void IncEDepP2(G4double depP2)   {fTotEP2 += depP2; }
  void IncEDepP3(G4double depP3)   {fTotEP3 += depP3; }
  void IncEDepP4(G4double depP4)   {fTotEP4 += depP4; }
  void IncEDepP5(G4double depP5)   {fTotEP5 += depP5; }
  void IncEDepP6(G4double depP6)   {fTotEP6 += depP6; }
  void IncEDepP7(G4double depP7)   {fTotEP7 += depP7; }
  void IncEDepP8(G4double depP8)   {fTotEP8 += depP8; }
  /*
  void IncEDepP9(G4double depP9)   {fTotEP9 += depP9; }
  void IncEDepP10(G4double depP10) {fTotEP10 += depP10; }
  void IncEDepP11(G4double depP11) {fTotEP11 += depP11; }
  void IncEDepP12(G4double depP12) {fTotEP12 += depP12; }
  void IncEDepP13(G4double depP13) {fTotEP13 += depP13; }
  void IncEDepP14(G4double depP14) {fTotEP14 += depP14; }
  void IncEDepP15(G4double depP15) {fTotEP15 += depP15; }
  void IncEDepP16(G4double depP16) {fTotEP16 += depP16; }
  */
  
//------------------------------------------------

  void IncHitCount(G4int i = 1) { fHitCount += i; }

  void IncHitC1(G4int i = 1) { fHitC1 += i; }
  void IncHitC2(G4int i = 1) { fHitC2 += i; }
  void IncHitC3(G4int i = 1) { fHitC3 += i; }
  void IncHitC4(G4int i = 1) { fHitC4 += i; }
  void IncHitC5(G4int i = 1) { fHitC5 += i; }
  void IncHitC6(G4int i = 1) { fHitC6 += i; }
  void IncHitC7(G4int i = 1) { fHitC7 += i; }
  void IncHitC8(G4int i = 1) { fHitC8 += i; }
  /*
  void IncHitC9(G4int i = 1) { fHitC9 += i; }
  void IncHitC10(G4int i = 1) { fHitC10 += i; }
  void IncHitC11(G4int i = 1) { fHitC11 += i; }
  void IncHitC12(G4int i = 1) { fHitC12 += i; }
  void IncHitC13(G4int i = 1) { fHitC13 += i; }
  void IncHitC14(G4int i = 1) { fHitC14 += i; }
  void IncHitC15(G4int i = 1) { fHitC15 += i; }
  void IncHitC16(G4int i = 1) { fHitC16 += i; }
  */

  
  

  G4int GetHitCount() const { return fHitCount; }
  
  //New-------------------------------------
  G4double GetEdepP() const {return fEdepP; }
  //----------------------------------------

  void IncPMTSAboveThreshold() { ++fPMTsAboveThreshold; }
  G4int GetPMTSAboveThreshold() { return fPMTsAboveThreshold; }

 private:
  LXeEventMessenger* fEventMessenger;
  const LXeDetectorConstruction* fDetector;

  G4int fScintCollID;
  G4int fPMTCollID;

  G4int fVerbose;

  G4int fPMTThreshold;

  G4bool fForcedrawphotons;
  G4bool fForcenophotons;

  G4int fHitCount;
  
  G4int fHitC1;
  G4int fHitC2;
  G4int fHitC3;
  G4int fHitC4;
  G4int fHitC5;
  G4int fHitC6;
  G4int fHitC7;
  G4int fHitC8;
  /*
  G4int fHitC9;
  G4int fHitC10;
  G4int fHitC11;
  G4int fHitC12;
  G4int fHitC13;
  G4int fHitC14;
  G4int fHitC15;
  G4int fHitC16;
  */





  
/*
  G4int fPhotonCount_Scint;
  G4int fPhotonCount_Ceren;
  G4int fAbsorptionCount;
  G4int fBoundaryAbsorptionCount;
*/
  //G4double fTotE;
  G4double fTotEP;
  G4double fEdepP;

  //For my individual Energy ranges
  G4double fTotEP1;
  G4double fTotEP2;
  G4double fTotEP3;
  G4double fTotEP4;
  G4double fTotEP5;
  G4double fTotEP6;
  G4double fTotEP7;
  G4double fTotEP8;
  G4double fTotEP9;
  G4double fTotEP10;
  G4double fTotEP11;
  G4double fTotEP12;
  G4double fTotEP13;
  G4double fTotEP14;
  G4double fTotEP15;
  G4double fTotEP16;



  
  // These only have meaning if totE > 0
  // If totE = 0 then these won't be set by EndOfEventAction
  //G4ThreeVector fEWeightPos;
  //G4ThreeVector fReconPos;  // Also relies on hitCount>0
  //G4ThreeVector fConvPos;   // true (initial) converstion position
 // G4bool fConvPosSet;
  //G4ThreeVector fPosMax;
  //G4double fEdepMax;

  G4int fPMTsAboveThreshold;
};

#endif
