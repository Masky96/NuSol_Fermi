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
/// \file optical/LXe/include/LXeRun.hh
/// \brief Definition of the LXeRun class
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef LXeRun_h
#define LXeRun_h 1

#include "globals.hh"
#include "G4Run.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class LXeRun : public G4Run
{
 public:
  LXeRun();
  ~LXeRun();
  //New

  void IncEDepP(G4double depP)
  {
	fTotEP_tot += depP;
	fTotEP2_tot += depP * depP;
  }
void IncEDepP1(G4double depP1)
  {
	fTotEP1 += depP1;
	fTotEP1_2 += depP1 * depP1;
  }
void IncEDepP2(G4double depP2)
  {
	fTotEP2 += depP2;
	fTotEP2_2 += depP2 * depP2;
  }
void IncEDepP3(G4double depP3)
  {
	fTotEP3 += depP3;
	fTotEP3_2 += depP3 * depP3;
  }
void IncEDepP4(G4double depP4)
  {
	fTotEP4 += depP4;
	fTotEP4_2 += depP4 * depP4;
  }
void IncEDepP5(G4double depP5)
  {
	fTotEP5 += depP5;
	fTotEP5_2 += depP5 * depP5;
  }
void IncEDepP6(G4double depP6)
  {
	fTotEP6 += depP6;
	fTotEP6_2 += depP6 * depP6;
  }
void IncEDepP7(G4double depP7)
  {
	fTotEP7 += depP7;
	fTotEP7_2 += depP7 * depP7;
  }
void IncEDepP8(G4double depP8)
  {
	fTotEP8 += depP8;
	fTotEP8_2 += depP8 * depP8;
  }
  /*
void IncEDepP9(G4double depP9)
  {
    fTotEP9 += depP9;
	fTotEP9_2 += depP9 * depP9;
  }
void IncEDepP10(G4double depP10)
  {
	fTotEP10 += depP10;
	fTotEP10_2 += depP10 * depP10;
  }
void IncEDepP11(G4double depP11)
  {
	fTotEP11 += depP11;
	fTotEP11_2 += depP11 * depP11;
  }
void IncEDepP12(G4double depP12)
  {
	fTotEP12 += depP12;
	fTotEP12_2 += depP12 * depP12;
  }
void IncEDepP13(G4double depP13)
  {
	fTotEP13 += depP13;
	fTotEP13_2 += depP13 * depP13;
  }
void IncEDepP14(G4double depP14)
  {
	fTotEP14 += depP14;
	fTotEP14_2 += depP14 * depP14;
  }
void IncEDepP15(G4double depP15)
  {
	fTotEP15 += depP15;
	fTotEP15_2 += depP15 * depP15;
  }
void IncEDepP16(G4double depP16)
  {
	fTotEP16 += depP16;
	fTotEP16_2 += depP16 * depP16;
  }
  */
  //------------------------ 

  void IncHitCount(G4int count)
  {
    fHitCount += count;
    fHitCount2 += count * count;
  }
  void IncHitC1(G4int count1)
  {
    fHitC1 += count1;
    fHitC1_2 += count1 * count1;
  }
  void IncHitC2(G4int count2)
  {
    fHitC2 += count2;
    fHitC2_2 += count2 * count2;
  }
 void IncHitC3(G4int count3)
  {
    fHitC3 += count3;
    fHitC3_2 += count3 * count3;
  }
 void IncHitC4(G4int count4)
  {
    fHitC4 += count4;
    fHitC4_2 += count4 * count4;
  }
 void IncHitC5(G4int count5)
  {
    fHitC5 += count5;
    fHitC5_2 += count5 * count5;
  }
 void IncHitC6(G4int count6)
  {
    fHitC6 += count6;
    fHitC6_2 += count6 * count6;
  }
 void IncHitC7(G4int count7)
  {
    fHitC7 += count7;
    fHitC7_2 += count7 * count7;
  }
 void IncHitC8(G4int count8)
  {
    fHitC8 += count8;
    fHitC8_2 += count8 * count8;
  }
  /*
 void IncHitC9(G4int count9)
  {
    fHitC9 += count9;
    fHitC9_2 += count9 * count9;
  }
 void IncHitC10(G4int count10)
  {
    fHitC10 += count10;
    fHitC10_2 += count10 * count10;
  }
 void IncHitC11(G4int count11)
  {
    fHitC11 += count11;
    fHitC11_2 += count11 * count11;
  }
 void IncHitC12(G4int count12)
  {
    fHitC12 += count12;
    fHitC12_2 += count12 * count12;
  }
 void IncHitC13(G4int count13)
  {
    fHitC13 += count13;
    fHitC13_2 += count13 * count13;
  }
 void IncHitC14(G4int count14)
  {
    fHitC14 += count14;
    fHitC14_2 += count14 * count14;
  }
 void IncHitC15(G4int count15)
  {
    fHitC15 += count15;
    fHitC15_2 += count15 * count15;
  }
  void IncHitC16(G4int count16)
  {
    fHitC16 += count16;
    fHitC16_2 += count16 * count16;
  }
  */

  
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

  G4int fHitC1;
  G4int fHitC1_2;
  
  G4int fHitC2;
  G4int fHitC2_2;

  G4int fHitC3;
  G4int fHitC3_2;
  
  G4int fHitC4;
  G4int fHitC4_2;

  G4int fHitC5;
  G4int fHitC5_2;

  G4int fHitC6;
  G4int fHitC6_2;

  G4int fHitC7;
  G4int fHitC7_2;

  G4int fHitC8;
  G4int fHitC8_2;
  /*
  G4int fHitC9;
  G4int fHitC9_2;

  G4int fHitC10;
  G4int fHitC10_2;

  G4int fHitC11;
  G4int fHitC11_2;

  G4int fHitC12;
  G4int fHitC12_2;

  G4int fHitC13;
  G4int fHitC13_2;

  G4int fHitC14;
  G4int fHitC14_2;

  G4int fHitC15;
  G4int fHitC15_2;
  
  G4int fHitC16;
  G4int fHitC16_2;
  */



  G4int fPMTsAboveThreshold;
  G4int fPMTsAboveThreshold2;

  G4double fTotEP_tot;
  G4double fTotEP2_tot;
  G4double fTotEP1;
  G4double fTotEP1_2;
  G4double fTotEP2;
  G4double fTotEP2_2;
  G4double fTotEP3;
  G4double fTotEP3_2;
  G4double fTotEP4;
  G4double fTotEP4_2;
  G4double fTotEP5;
  G4double fTotEP5_2;
  G4double fTotEP6;
  G4double fTotEP6_2;
  G4double fTotEP7;
  G4double fTotEP7_2;
  G4double fTotEP8;
  G4double fTotEP8_2;
  /*
  G4double fTotEP9;
  G4double fTotEP9_2;
  G4double fTotEP10;
  G4double fTotEP10_2;
  G4double fTotEP11;
  G4double fTotEP11_2;
  G4double fTotEP12;
  G4double fTotEP12_2;
  G4double fTotEP13;
  G4double fTotEP13_2;
  G4double fTotEP14;
  G4double fTotEP14_2;
  G4double fTotEP15;
  G4double fTotEP15_2;
  G4double fTotEP16;
  G4double fTotEP16_2;
  */
  

};

#endif  // LXeRun_h
