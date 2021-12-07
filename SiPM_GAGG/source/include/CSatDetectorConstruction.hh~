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
/// \file optical/CSat/include/CSatDetectorConstruction.hh
/// \brief Definition of the CSatDetectorConstruction class
//
//
#ifndef CSatDetectorConstruction_h
#define CSatDetectorConstruction_h 1



#include "G4Cache.hh"
#include "G4VUserDetectorConstruction.hh"

class CSatMainVolume;
//class CSatPMTSD;
class CSatScintSD;
//New
class CSatEljinSD;

class CSatVPMTSD;
class CSatGPMTSD;

class G4Box;
class G4Element;
class G4LogicalVolume;
class G4Material;
class G4MaterialPropertiesTable;
//class G4Sphere;
class G4Tubs;
class G4VPhysicalVolume;

class CSatDetectorConstruction : public G4VUserDetectorConstruction
{
 public:
  CSatDetectorConstruction();
  ~CSatDetectorConstruction();

  G4VPhysicalVolume* Construct() override;
  void ConstructSDandField() override;

  // Functions to modify the geometry
  // void SetDimensions(G4ThreeVector);
  void SetHousingThickness(G4double);
  void SetNX(G4int);
  void SetNY(G4int);
  void SetNZ(G4int);
  void SetPMTRadius(G4double);
  void SetDefaults();
  void SetSaveThreshold(G4int);

  // Get values
  G4int GetNX() const { return fNx; };
  G4int GetNY() const { return fNy; };
  G4int GetNZ() const { return fNz; };
  //G4double GetScintX() const { return fScint_x; }
  // G4double GetScintY() const { return fScint_y; }
  // G4double GetScintZ() const { return fScint_z; }
  G4double GetHousingThickness() const { return fD_mtl; }
  G4double GetPMTRadius() const { return fOuterRadius_pmt; }
   /*
  void SetSphereOn(G4bool);
  static G4bool GetSphereOn() { return fSphereOn; }
  */
  void SetHousingReflectivity(G4double);
  G4double GetHousingReflectivity() const { return fRefl; }

  

  void SetMainVolumeOn(G4bool b);
  G4bool GetMainVolumeOn() const { return fMainVolumeOn; }


 private:
  void DefineMaterials();


  G4Box* fExperimentalHall_box;
  G4LogicalVolume* fExperimentalHall_log;
  G4VPhysicalVolume* fExperimentalHall_phys;

  // Materials & Elements
  G4Material* fCSat;
  G4Material* fAl;
  G4Material* fN;
  G4Material* fO;
  G4Material* fAir;
  G4Material* fVacuum;
  G4Material* fC;
  G4Material* fH;
  G4Material* fGlass;


  //--New-----------------
  G4Material* fEpoxy;
  G4Material* fIronShield;
  G4Material* fFe;
  G4Material* fEljin_200;
  G4Material* fGd;
  G4Material* fGa;
  G4Material* fCe;
  G4Material* fGAGG;
  

  

  // Geometry
  G4double fScint_x;
  G4double fScint_y;
  G4double fScint_z;
  G4double fD_mtl;
  G4int fNx;
  G4int fNy;
  G4int fNz;
  G4double fOuterRadius_pmt;
  G4int fNfibers;
  G4double fRefl;
  G4bool fMainVolumeOn;
  CSatMainVolume* fMainVolume;

  G4MaterialPropertiesTable* fCSat_mt;
  G4MaterialPropertiesTable* feljin_mt;

  // Sensitive Detectors
  G4Cache<CSatScintSD*> fScint_SD;
  //G4Cache<CSatPMTSD*> fPmt_SD;

  //New 
  G4Cache<CSatEljinSD*> fEljin_SD;

  G4Cache<CSatVPMTSD*> fVPMT_SD;
  G4Cache<CSatGPMTSD*> fGPMT_SD;
};

#endif
