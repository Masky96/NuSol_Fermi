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
/// \file optical/LXe/include/LXeMainVolume.hh
/// \brief Definition of the LXeMainVolume class
//
#ifndef LXeMainVolume_h
#define LXeMainVolume_h 1

#include "LXeDetectorConstruction.hh"

#include "G4PVPlacement.hh"

class G4Box;
class G4LogicalVolume;
class G4Sphere;
class G4Tubs;

class LXeMainVolume : public G4PVPlacement
{
 public:
  LXeMainVolume(G4RotationMatrix* pRot, const G4ThreeVector& tlate,
                G4LogicalVolume* pMotherLogical, G4bool pMany, G4int pCopyNo,
                LXeDetectorConstruction* c);

  G4LogicalVolume* GetLogPhotoCath() { return fPhotocath_log; }
  G4LogicalVolume* GetLogScint() { return fScint_log; }

  std::vector<G4ThreeVector> GetPmtPositions() { return fPmtPositions; }

 private:
  void VisAttributes();
  void SurfaceProperties();


  void PlacePMTs(G4LogicalVolume* pmt_Log, G4RotationMatrix* rot, G4double& a,
                 G4double& b, G4double da, G4double db, G4double amin,
                 G4double bmin, G4int na, G4int nb, G4double& x, G4double& y,
                 G4double& z, G4int& k);

  void CopyValues();

  LXeDetectorConstruction* fConstructor;

  G4double fScint_x;
  G4double fScint_y;
  G4double fScint_z;
  G4double fD_mtl;
  G4int fNx;
  G4int fNy;
  G4int fNz;
  G4double fOuterRadius_pmt;
  //G4bool fSphereOn;
  G4double fRefl;

  // Basic Volumes
  //
  G4Box* fScint_box;
  G4Box* fHousing_box;
  //New things I am trying
  G4Box* fScint_box1;
  G4Box* fScint_box2;
  G4Box* fScint_box3;
  G4Box* fScint_box4;
  G4Box* fScint_box5;
  G4Box* fScint_box6;
  G4Box* fScint_box7;
  G4Box* fScint_box8;
  G4Box* fScint_box9;
  G4Box* fScint_box10;
  G4Box* fScint_box11;
  G4Box* fScint_box12;
  G4Box* fScint_box13;
  G4Box* fScint_box14;
  G4Box* fScint_box15;
  G4Box* fScint_box16;
  G4Box* fScint_box17;
  G4Box* fScint_box18;
  G4Box* fScint_box19;
  G4Box* fScint_box20;
  
  //---------------------
  G4Tubs* fPmt;
  G4Tubs* fPhotocath;
  //G4Sphere* fSphere;

  
  // Logical volumes
  //
  G4LogicalVolume* fScint_log;
  //New ones
  G4LogicalVolume* fScint_log1;
  G4LogicalVolume* fScint_log2;
  G4LogicalVolume* fScint_log3;
  G4LogicalVolume* fScint_log4;
  G4LogicalVolume* fScint_log5;
  G4LogicalVolume* fScint_log6;
  G4LogicalVolume* fScint_log7;
  G4LogicalVolume* fScint_log8;
  G4LogicalVolume* fScint_log9;
  G4LogicalVolume* fScint_log10;
  G4LogicalVolume* fScint_log11;
  G4LogicalVolume* fScint_log12;
  G4LogicalVolume* fScint_log13;
  G4LogicalVolume* fScint_log14;
  G4LogicalVolume* fScint_log15;
  G4LogicalVolume* fScint_log16;
  G4LogicalVolume* fScint_log17;
  G4LogicalVolume* fScint_log18;
  G4LogicalVolume* fScint_log19;
  G4LogicalVolume* fScint_log20;





  
  G4LogicalVolume* fHousing_log;
  G4LogicalVolume* fPmt_log;
  G4LogicalVolume* fPhotocath_log;
  //G4LogicalVolume* fSphere_log;

  // Sensitive Detectors positions
  std::vector<G4ThreeVector> fPmtPositions;
};

#endif
