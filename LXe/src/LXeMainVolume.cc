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
/// \file optical/LXe/src/LXeMainVolume.cc
/// \brief Implementation of the LXeMainVolume class
//
//
#include "LXeMainVolume.hh"

#include "globals.hh"
#include "G4Box.hh"
#include "G4Colour.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "G4MaterialPropertiesTable.hh"
#include "G4OpticalSurface.hh"
#include "G4Sphere.hh"
#include "G4SystemOfUnits.hh"
#include "G4Tubs.hh"
#include "G4VisAttributes.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LXeMainVolume::LXeMainVolume(G4RotationMatrix* pRot, const G4ThreeVector& tlate,
                             G4LogicalVolume* pMotherLogical, G4bool pMany,
                             G4int pCopyNo, LXeDetectorConstruction* c)


  // Pass info to the G4PVPlacement constructor
  : G4PVPlacement(pRot, tlate,
                  // Temp logical volume must be created here
                  new G4LogicalVolume(new G4Box("temp", 1, 1, 1),
                                      G4Material::GetMaterial("Vacuum"), "temp",
                                      0, 0, 0),
                  "housing", pMotherLogical, pMany, pCopyNo)
  , fConstructor(c)
{
  CopyValues();

  G4double housing_x = fScint_x + 25. * km;
  G4double housing_y = fScint_y + 25. * km;
  G4double housing_z = fScint_z + 225. * km;



  //*************************** housing and scintillator
  
  fScint_box =
    new G4Box("scint_box", fScint_x / 2., fScint_y / 2., fScint_z / 2.);
  
  
  //Making chunks instead of one continuous atmosphere
  /*
  fScint_box1 =
    new G4Box("scint_box1", fScint_x / 2., fScint_y / 2., fScint_z / 20.);
  
  fScint_box2 =
    new G4Box("scint_box2", fScint_x / 2., fScint_y / 2., fScint_z / 20.);
  fScint_box3 =
    new G4Box("scint_box3", fScint_x / 2., fScint_y / 2., fScint_z / 20.);
  fScint_box4 =
    new G4Box("scint_box4", fScint_x / 2., fScint_y / 2., fScint_z / 20.);
  fScint_box5 =
    new G4Box("scint_box5", fScint_x / 2., fScint_y / 2., fScint_z / 20.);
  fScint_box6 =
    new G4Box("scint_box6", fScint_x / 2., fScint_y / 2., fScint_z / 20.);
  fScint_box7 =
    new G4Box("scint_box7", fScint_x / 2., fScint_y / 2., fScint_z / 20.);
  fScint_box8 =
    new G4Box("scint_box8", fScint_x / 2., fScint_y / 2., fScint_z / 20.);
  fScint_box9 =
    new G4Box("scint_box9", fScint_x / 2., fScint_y / 2., fScint_z / 20.);
  fScint_box10 =
    new G4Box("scint_box10", fScint_x / 2., fScint_y / 2., fScint_z / 20.);
  fScint_box11 =
    new G4Box("scint_box11", fScint_x / 2., fScint_y / 2., fScint_z / 20.);
  fScint_box12 =
    new G4Box("scint_box12", fScint_x / 2., fScint_y / 2., fScint_z / 20.);
  fScint_box13 =
    new G4Box("scint_box13", fScint_x / 2., fScint_y / 2., fScint_z / 20.);
  fScint_box14 =
    new G4Box("scint_box14", fScint_x / 2., fScint_y / 2., fScint_z / 20.);
  fScint_box15 =
    new G4Box("scint_box15", fScint_x / 2., fScint_y / 2., fScint_z / 20.);
  fScint_box16 =
    new G4Box("scint_box16", fScint_x / 2., fScint_y / 2., fScint_z / 20.);
  fScint_box17 =
    new G4Box("scint_box17", fScint_x / 2., fScint_y / 2., fScint_z / 20.);
  fScint_box18 =
    new G4Box("scint_box18", fScint_x / 2., fScint_y / 2., fScint_z / 20.);
  fScint_box19 =
    new G4Box("scint_box19", fScint_x / 2., fScint_y / 2., fScint_z / 20.);
  fScint_box20 =
    new G4Box("scint_box20", fScint_x / 2., fScint_y / 2., fScint_z / 20.);
  */





  
  fHousing_box =
    new G4Box("housing_box", housing_x / 2., housing_y / 2., housing_z / 2.);

  
  
  fScint_log   = new G4LogicalVolume(fScint_box, G4Material::GetMaterial("Neptune Atmosphere"),
                                   "scint_log", 0, 0, 0);
  /*
  
  fScint_log1   = new G4LogicalVolume(fScint_box1, G4Material::GetMaterial("Neptune Atmosphere"),
                                   "scint_log1", 0, 0, 0);
  
  fScint_log2   = new G4LogicalVolume(fScint_box2, G4Material::GetMaterial("Neptune Atmosphere"),
  				   "scint_log2", 0, 0, 0);
  
  fScint_log3   = new G4LogicalVolume(fScint_box3, G4Material::GetMaterial("Neptune Atmosphere"),
                                   "scint_log3", 0, 0, 0);

  fScint_log4   = new G4LogicalVolume(fScint_box4, G4Material::GetMaterial("Neptune Atmosphere"),
                                   "scint_log4", 0, 0, 0);
  
  fScint_log5   = new G4LogicalVolume(fScint_box5, G4Material::GetMaterial("Neptune Atmosphere"),
				   "scint_log5", 0, 0, 0);
  
  fScint_log6   = new G4LogicalVolume(fScint_box6, G4Material::GetMaterial("Neptune Atmosphere"),
                                   "scint_log6", 0, 0, 0);
  
  fScint_log7   = new G4LogicalVolume(fScint_box7, G4Material::GetMaterial("Neptune Atmosphere"),
				   "scint_log7", 0, 0, 0);
  
  fScint_log8   = new G4LogicalVolume(fScint_box8, G4Material::GetMaterial("Neptune Atmosphere"),
                                   "scint_log8", 0, 0, 0);
  
  fScint_log9   = new G4LogicalVolume(fScint_box9, G4Material::GetMaterial("Neptune Atmosphere"),
                                   "scint_log9", 0, 0, 0);
  
  fScint_log10   = new G4LogicalVolume(fScint_box10, G4Material::GetMaterial("Neptune Atmosphere"),
                                   "scint_log10", 0, 0, 0);
  
  fScint_log11   = new G4LogicalVolume(fScint_box10, G4Material::GetMaterial("Neptune Atmosphere"),
                                   "scint_log11", 0, 0, 0);
  
  fScint_log12   = new G4LogicalVolume(fScint_box10, G4Material::GetMaterial("Neptune Atmosphere"),
                                   "scint_log12", 0, 0, 0);
  
  fScint_log13   = new G4LogicalVolume(fScint_box10, G4Material::GetMaterial("Neptune Atmosphere"),
                                   "scint_log13", 0, 0, 0);
  
  fScint_log14   = new G4LogicalVolume(fScint_box10, G4Material::GetMaterial("Neptune Atmosphere"),
                                   "scint_log14", 0, 0, 0);
  
  fScint_log15   = new G4LogicalVolume(fScint_box10, G4Material::GetMaterial("Neptune Atmosphere"),
                                   "scint_log15", 0, 0, 0);
  
  fScint_log16   = new G4LogicalVolume(fScint_box10, G4Material::GetMaterial("Neptune Atmosphere"),
                                   "scint_log16", 0, 0, 0);
  
  fScint_log17   = new G4LogicalVolume(fScint_box10, G4Material::GetMaterial("Neptune Atmosphere"),
                                   "scint_log17", 0, 0, 0);
  
  fScint_log18   = new G4LogicalVolume(fScint_box10, G4Material::GetMaterial("Neptune Atmosphere"),
                                   "scint_log18", 0, 0, 0);
  
  fScint_log19   = new G4LogicalVolume(fScint_box10, G4Material::GetMaterial("Neptune Atmosphere"),
                                   "scint_log19", 0, 0, 0);
  
  fScint_log20   = new G4LogicalVolume(fScint_box10, G4Material::GetMaterial("Neptune Atmosphere"),
                                   "scint_log20", 0, 0, 0);
  
  */
 
 
  fHousing_log = new G4LogicalVolume(fHousing_box, G4Material::GetMaterial("Vacuum"), "housing_log", 0, 0, 0);



  
  new G4PVPlacement(0, G4ThreeVector(), fScint_log, "scintillator",fHousing_log , false, 0);
  
  /*
  new G4PVPlacement(0, G4ThreeVector(0 , 0 , fScint_z / 40.), fScint_log1, "scintillator1",fHousing_log , false, 0);
  
  new G4PVPlacement(0, G4ThreeVector(0 , 0 , 3*fScint_z / 40.), fScint_log2, "scintillator2",fHousing_log , false, 0);
  
  new G4PVPlacement(0, G4ThreeVector(0 , 0 , 5*fScint_z / 40.), fScint_log3, "scintillator3",fHousing_log , false, 0);
  
  new G4PVPlacement(0, G4ThreeVector(0 , 0 , 7*fScint_z / 40.), fScint_log4, "scintillator4",fHousing_log , false, 0);
  
  new G4PVPlacement(0, G4ThreeVector(0 , 0 , 9*fScint_z / 40.), fScint_log5, "scintillator5",fHousing_log , false, 0);
  
  new G4PVPlacement(0, G4ThreeVector(0 , 0 , 11*fScint_z / 40.), fScint_log6, "scintillator6",fHousing_log , false, 0);
  
  new G4PVPlacement(0, G4ThreeVector(0 , 0 , 13*fScint_z / 40.), fScint_log7, "scintillator7",fHousing_log , false, 0);
  
  new G4PVPlacement(0, G4ThreeVector(0 , 0 , 15*fScint_z / 40.), fScint_log8, "scintillator8",fHousing_log , false, 0);
  
  new G4PVPlacement(0, G4ThreeVector(0 , 0 , 17*fScint_z / 40.), fScint_log9, "scintillator9",fHousing_log , false, 0);
  
  new G4PVPlacement(0, G4ThreeVector(0 , 0 , 19*fScint_z / 40.), fScint_log10, "scintillator10",fHousing_log , false, 0);

  new G4PVPlacement(0, G4ThreeVector(0 , 0 , -1*fScint_z / 40.), fScint_log11, "scintillator11",fHousing_log , false, 0);
  
  new G4PVPlacement(0, G4ThreeVector(0 , 0 , -3*fScint_z / 40.), fScint_log12, "scintillator12",fHousing_log , false, 0);
  
  new G4PVPlacement(0, G4ThreeVector(0 , 0 , -5*fScint_z / 40.), fScint_log13, "scintillator13",fHousing_log , false, 0);
  
  new G4PVPlacement(0, G4ThreeVector(0 , 0 , -7*fScint_z / 40.), fScint_log14, "scintillator14",fHousing_log , false, 0);
  
  new G4PVPlacement(0, G4ThreeVector(0 , 0 , -9*fScint_z / 40.), fScint_log15, "scintillator15",fHousing_log , false, 0);
  
  new G4PVPlacement(0, G4ThreeVector(0 , 0 , -11*fScint_z / 40.), fScint_log16, "scintillator16",fHousing_log , false, 0);
  
  new G4PVPlacement(0, G4ThreeVector(0 , 0 , -13*fScint_z / 40.), fScint_log17, "scintillator17",fHousing_log , false, 0);
  
  new G4PVPlacement(0, G4ThreeVector(0 , 0 , -15*fScint_z / 40.), fScint_log18, "scintillator18",fHousing_log , false, 0);
  
  new G4PVPlacement(0, G4ThreeVector(0 , 0 , -17*fScint_z / 40.), fScint_log19, "scintillator19",fHousing_log , false, 0);
  
  new G4PVPlacement(0, G4ThreeVector(0 , 0 , -19*fScint_z / 40.), fScint_log20, "scintillator20",fHousing_log , false, 0);
  */



 
 
  //****************** Build PMTs
  G4double innerRadius_pmt   = 0.;
  G4double height_pmt        = fD_mtl / 2.;
  G4double startAngle_pmt    = 0.;
  G4double spanningAngle_pmt = 360. * deg;

  fPmt = new G4Tubs("pmt_tube", innerRadius_pmt, fOuterRadius_pmt, height_pmt,
                    startAngle_pmt, spanningAngle_pmt);

  // the "photocathode" is a metal slab at the back of the glass that
  // is only a very rough approximation of the real thing since it only
  // absorbs or detects the photons based on the efficiency set below
  fPhotocath = new G4Tubs("photocath_tube", innerRadius_pmt, fOuterRadius_pmt,
                          height_pmt / 2., startAngle_pmt, spanningAngle_pmt);

  fPmt_log =
    new G4LogicalVolume(fPmt, G4Material::GetMaterial("Vacuum"), "pmt_log");
  fPhotocath_log = new G4LogicalVolume(
    fPhotocath, G4Material::GetMaterial("Vacuum"), "photocath_log");

  new G4PVPlacement(0, G4ThreeVector(0., 0., -height_pmt/2 ), fPhotocath_log,
                    "photocath", fPmt_log, false, 0);

  //***********Arrange pmts around the outside of housing**********

  G4double dx = 0. ;
  G4double dy = 0. ; 
  G4double dz = 0. ; 

  G4double x, y, z;
  G4double xmin = 0.; 
  G4double ymin = 0.; 
  G4double zmin = 0.; 
  G4int k       = 0;

  //z = -(-fScint_z / 2. - height_pmt);  // front
  z = 100*km;
  
  
  /*
  G4RotationMatrix* rm_z = new G4RotationMatrix();
  rm_z->rotateY(180. * deg);
  */
  
  PlacePMTs(fPmt_log, nullptr, x, y, dx, dy, xmin, ymin, fNx, fNy, x, y, z, k); 
  VisAttributes();
  SurfaceProperties();
  
  SetLogicalVolume(fHousing_log);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LXeMainVolume::CopyValues()
{
  fScint_x         = fConstructor->GetScintX();
  fScint_y         = fConstructor->GetScintY();
  fScint_z         = fConstructor->GetScintZ();
  fD_mtl           = fConstructor->GetHousingThickness();
  fOuterRadius_pmt = fConstructor->GetPMTRadius();
  fRefl            = fConstructor->GetHousingReflectivity();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......




void LXeMainVolume::PlacePMTs(G4LogicalVolume* pmt_log, G4RotationMatrix* rot,
                              G4double& a, G4double& b, G4double da,
                              G4double db, G4double amin, G4double bmin,
                              G4int na, G4int nb, G4double& x, G4double& y,
                              G4double& z, G4int& k)

{
  /*  PlacePMTs : a different way to parameterize placement that does not depend
   * on calculating the position from the copy number
   *
   *  pmt_log = logical volume for pmts to be placed
   *  rot = rotation matrix to apply
   *  a,b = coordinates to vary(ie. if varying in the xy plane then pass x,y)
   *  da,db = value to increment a,b by
   *  amin,bmin = start values for a,b
   *  na,nb = number of repitions in a and b
   *  x,y,z = just pass x,y, and z by reference (the same ones passed for a,b)
   *  k = copy number to start with
   *  sd = sensitive detector for pmts
   */


  
a=x;
b=y;

k=0.;

new G4PVPlacement(rot, G4ThreeVector(x,y,z), pmt_log, "pmt",fHousing_log, false, k);
fPmtPositions.push_back(G4ThreeVector(x,y,z));

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LXeMainVolume::VisAttributes()
{

  //fHousing_log->SetVisAttributes(G4VisAttributes::GetInvisible());
  fPhotocath_log ->SetVisAttributes(G4Colour(0.5,0.5,0.5));

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LXeMainVolume::SurfaceProperties()
{
  std::vector<G4double> ephoton = { 1.588 * eV, 1.622 * eV, 1.657 * eV, 1.691 * eV, 1.725 * eV, 1.76 * eV, 1.794 * eV, 1.828 * eV,1.863 * eV, 1.897 * eV, 1.931 * eV,1.966 * eV, 2.00 * eV,2.034 * eV, 2.068 * eV, 2.103 * eV, 2.139 * eV, 2.177 * eV, 2.216 * eV,
    2.256 * eV, 2.298 * eV, 2.341 * eV, 2.386 * eV, 2.433 * eV, 2.481 * eV,
    2.532 * eV, 2.585 * eV, 2.640 * eV, 2.697 * eV, 2.757 * eV, 2.820 * eV,
    2.885 * eV, 2.954 * eV, 3.026 * eV, 3.102 * eV, 3.181 * eV, 3.265 * eV,
    3.353 * eV, 3.446 * eV, 3.545 * eV, 3.649 * eV, 3.760 * eV, 3.877 * eV,
    4.002 * eV, 4.136 * eV };



  //**Scintillator housing properties
  std::vector<G4double> reflectivity     = { fRefl, fRefl, fRefl, fRefl, fRefl, fRefl, fRefl, fRefl, fRefl, fRefl, fRefl, fRefl, fRefl, fRefl, fRefl, fRefl, fRefl, fRefl, fRefl, fRefl, fRefl, fRefl, fRefl, fRefl, fRefl, fRefl, fRefl, fRefl,fRefl, fRefl, fRefl, fRefl, fRefl, fRefl, fRefl, fRefl, fRefl, fRefl, fRefl, fRefl, fRefl, fRefl, fRefl, fRefl, fRefl};

  std::vector<G4double> efficiency = { 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1};
  G4MaterialPropertiesTable* scintHsngPT = new G4MaterialPropertiesTable();
  scintHsngPT->AddProperty("REFLECTIVITY", ephoton, reflectivity);
  scintHsngPT->AddProperty("EFFICIENCY", ephoton, efficiency);
  G4OpticalSurface* OpScintHousingSurface =
    new G4OpticalSurface("HousingSurface", unified, polished, dielectric_dielectric);
  OpScintHousingSurface->SetMaterialPropertiesTable(scintHsngPT);



  //**Photocathode surface properties
  std::vector<G4double> photocath_EFF = { 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1.,1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1.};

  std::vector<G4double> photocath_ReR = { 1.92, 1.92, 1.92, 1.92, 1.92, 1.92, 1.92, 1.92, 1.92, 1.92, 1.92, 1.92, 1.92, 1.92, 1.92, 1.92, 1.92, 1.92, 1.92, 1.92, 1.92, 1.92, 1.92, 1.92, 1.92, 1.92, 1.92, 1.92, 1.92, 1.92, 1.92, 1.92, 1.92, 1.92, 1.92, 1.92, 1.92, 1.92, 1.92, 1.92, 1.92, 1.92, 1.92, 1.92, 1.92};

  std::vector<G4double> photocath_ImR = { 1.69, 1.69, 1.69, 1.69, 1.69, 1.69, 1.69, 1.69, 1.69, 1.69, 1.69, 1.69, 1.69, 1.69, 1.69, 1.69, 1.69, 1.69, 1.69, 1.69, 1.69, 1.69, 1.69, 1.69, 1.69, 1.69, 1.69, 1.69, 1.69, 1.69, 1.69, 1.69, 1.69, 1.69, 1.69, 1.69, 1.69, 1.69, 1.69, 1.69, 1.69, 1.69, 1.69, 1.69, 1.69};

  G4MaterialPropertiesTable* photocath_mt = new G4MaterialPropertiesTable();
  photocath_mt->AddProperty("EFFICIENCY", ephoton, photocath_EFF);
  photocath_mt->AddProperty("REALRINDEX", ephoton, photocath_ReR);
  photocath_mt->AddProperty("IMAGINARYRINDEX", ephoton, photocath_ImR);
  G4OpticalSurface* photocath_opsurf = new G4OpticalSurface(
    "photocath_opsurf", glisur, polished, dielectric_metal);
  photocath_opsurf->SetMaterialPropertiesTable(photocath_mt);


  new G4LogicalSkinSurface("photocath_surf", fHousing_log, OpScintHousingSurface);
  new G4LogicalSkinSurface("photocath_surf", fPhotocath_log, photocath_opsurf);
  new G4LogicalSkinSurface("scin_surf", fScint_log, OpScintHousingSurface);
  /*
  new G4LogicalSkinSurface("scin_surf",fScint_log1, OpScintHousingSurface);
  new G4LogicalSkinSurface("scin_surf",fScint_log2, OpScintHousingSurface);
  new G4LogicalSkinSurface("scin_surf",fScint_log3, OpScintHousingSurface);
  new G4LogicalSkinSurface("scin_surf",fScint_log4, OpScintHousingSurface);
  new G4LogicalSkinSurface("scin_surf",fScint_log5, OpScintHousingSurface);
  new G4LogicalSkinSurface("scin_surf",fScint_log6, OpScintHousingSurface);
  new G4LogicalSkinSurface("scin_surf",fScint_log7, OpScintHousingSurface);
  new G4LogicalSkinSurface("scin_surf",fScint_log8, OpScintHousingSurface);
  new G4LogicalSkinSurface("scin_surf",fScint_log9, OpScintHousingSurface);
  new G4LogicalSkinSurface("scin_surf",fScint_log10, OpScintHousingSurface);
  new G4LogicalSkinSurface("scin_surf",fScint_log11, OpScintHousingSurface);
  new G4LogicalSkinSurface("scin_surf",fScint_log12, OpScintHousingSurface);
  new G4LogicalSkinSurface("scin_surf",fScint_log13, OpScintHousingSurface);
  new G4LogicalSkinSurface("scin_surf",fScint_log14, OpScintHousingSurface);
  new G4LogicalSkinSurface("scin_surf",fScint_log15, OpScintHousingSurface);
  new G4LogicalSkinSurface("scin_surf",fScint_log16, OpScintHousingSurface);
  new G4LogicalSkinSurface("scin_surf",fScint_log17, OpScintHousingSurface);
  new G4LogicalSkinSurface("scin_surf",fScint_log18, OpScintHousingSurface);
  new G4LogicalSkinSurface("scin_surf",fScint_log19, OpScintHousingSurface);
  new G4LogicalSkinSurface("scin_surf",fScint_log20, OpScintHousingSurface);
  */




    
}
