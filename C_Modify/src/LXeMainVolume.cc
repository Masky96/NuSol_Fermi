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
#include "G4PhysicalConstants.hh"
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
                  "fakeVolume", pMotherLogical, pMany, pCopyNo)
  , fConstructor(c)
  
{
  CopyValues();

  //Default Cosntants

 

  G4double lcrystal_x = 2*2.54*cm;
  G4double lcrystal_y = 2*2.54*cm;
  G4double lcrystal_z = 2.54*cm;
  
  G4double pmt_squarex = 2.54*cm;
  G4double pmt_squarey = 2.54*cm;
  G4double pmt_squarez = 2.54*cm;

  G4double air_pocketx = lcrystal_x+2*mm;
  G4double air_pockety = lcrystal_y+2*mm;
  G4double air_pocketz = lcrystal_z + pmt_squarez+3*mm;

  G4double al_GAGGx = lcrystal_x+1*mm;
  G4double al_GAGGy = lcrystal_y+1*mm;
  G4double al_GAGGz = lcrystal_z+1.1*mm;
  
  G4double althinx = air_pocketx + 1*mm;
  G4double althiny = air_pockety + 1*mm;
  G4double althinz = air_pocketz + 1*mm;

  G4double fVeto_x = althinx + 2*cm;
  G4double fVeto_y = althiny + 2*cm;
  G4double fVeto_z = althinz + 2*cm;
  
/*
  G4double fVeto_x = air_pocketx + 2*cm;
  G4double fVeto_y = air_pockety + 2*cm;
  G4double fVeto_z = air_pocketz + 2*cm;
*/



/*
  G4double fScint_x = air_pocketx + 2*cm;
  G4double fScint_y = air_pockety + 2*cm;
  G4double fScint_z = air_pocketz + 2*cm;
*/  
  G4double housing_x = fVeto_x + 2. * fD_mtl;
  G4double housing_y = fVeto_y + 2. * fD_mtl;
  G4double housing_z = fVeto_z + 2. * fD_mtl;

  G4double iron_shieldx = housing_x + 2*mm+3*cm;
  G4double iron_shieldy = housing_y + 2*mm +3*cm;
  G4double iron_shieldz = housing_z + pmt_squarez + 3*cm +2*mm;

  //Iron Shield Outside
  
  fIronShield = new G4Box("iron_shield", iron_shieldx/2., iron_shieldy/2., iron_shieldz/2.);

  fIron_log = new G4LogicalVolume(fIronShield, G4Material::GetMaterial("Iron Shield"),"iron_log", 0,0,0);

  //new G4PVPlacement(0, G4ThreeVector(0.,0,(pmt_squarez)/2.),fIron_log, "ironshield",pMotherLogical,false,0);

  //AirGap between Shield and Detector

  fAirGap = new G4Box("air_gap", (housing_x+2*mm)/2.,(housing_y+2*mm)/2., (housing_z+ pmt_squarez + 2*mm)/2.);

  fAirGap_log = new G4LogicalVolume(fAirGap, G4Material::GetMaterial("Air"), "air_gap", 0,0,0);

  new G4PVPlacement(0, G4ThreeVector(), fAirGap_log, "air_gap_shield", fIron_log,false,0);
  
  
  

  //*************************** housing and scintillator

/*
  fScint_box =
    new G4Box("scint_box", fScint_x / 2., fScint_y / 2., fScint_z / 2.);
  fScint_log   = new G4LogicalVolume(fScint_box, G4Material::GetMaterial("LXe"),
                                   "scint_log", 0, 0, 0);
*/

//Changing Things Around


  fVeto = new G4Box("Veto", fVeto_x/2., fVeto_y/2., fVeto_z/2.);

  fVeto_Log = new G4LogicalVolume(fVeto, G4Material::GetMaterial("Eljin"),"veto_log",0,0,0);



  fHousing_box =
    new G4Box("housing_box", housing_x / 2., housing_y / 2., housing_z / 2.);

  fHousing_log = new G4LogicalVolume(
    fHousing_box, G4Material::GetMaterial("Al"), "housing_log", 0, 0, 0);
  
/*
  new G4PVPlacement(0, G4ThreeVector(), fScint_log, "scintillator",
                    fHousing_log, false, 0);
*/
  new G4PVPlacement(0,G4ThreeVector(0,0,0),fVeto_Log,"Veto_Scint",fHousing_log, false , 0); 

  new G4PVPlacement(0, G4ThreeVector(0,0,-pmt_squarez/2.), fHousing_log, "housing_al",fAirGap_log,false,0);


  //----------------------------------------------------------------------------

  falumthin = new G4Box("alumthin", althinx/2., althiny/2., althinz/2.);

  falumthin_log = new G4LogicalVolume(falumthin, G4Material::GetMaterial("Al"), "alumthin",0,0,0);
 
  new G4PVPlacement(0, G4ThreeVector(), falumthin_log, "alumthin", fVeto_Log, false, 0);


//------------------------------------------------------------------------------
  //Small Air Pocket for GAGG and PMT
  fairpocket = new G4Box("airpocket", air_pocketx/2., air_pockety/2., air_pocketz/2.);

  fair_log = new G4LogicalVolume(fairpocket, G4Material::GetMaterial("Air"),"air_log", 0, 0, 0);

  new G4PVPlacement(0,G4ThreeVector(),fair_log, "air_pocket", falumthin_log, false, 0);


  
  
  //Fixing Al outside.
  falumGAGG = new G4Box("alumGAGG", al_GAGGx/2., al_GAGGy/2.,al_GAGGz/2.);

  falumGAGG_log = new G4LogicalVolume(falumGAGG, G4Material::GetMaterial("Al"), "al_GAGG", 0,0,0);

  new G4PVPlacement(0, G4ThreeVector(0,0,-(al_GAGGz)/2.),falumGAGG_log, "alum_gagg", fair_log,false,0);



  //-----------------------------------------------------------------------------
  //GAGG Cystal Place Holder
  

  fScint_box =
    new G4Box("scint_box", lcrystal_x/ 2., lcrystal_y / 2., lcrystal_z / 2.);

  fScint_log   = new G4LogicalVolume(fScint_box, G4Material::GetMaterial("GAGG"),
                                   "scint_log", 0, 0, 0);

  new G4PVPlacement(0, G4ThreeVector(), fScint_log, "scintillator",
                    falumGAGG_log, false, 0);
  
  /*
  fVeto = new G4Box("GAGG", lcrystal_x/2., lcrystal_y/2., lcrystal_z/2.);

  fVeto_Log = new G4LogicalVolume(fVeto, G4Material::GetMaterial("LXe"),"crystal_log",0,0,0);

  new G4PVPlacement(0,G4ThreeVector(0,0,0),fVeto_Log,"Veto_Scint",falumGAGG_log, false , 0); 
  */



  //****************** Build PMTs
  G4double innerRadius_pmt   = 0.;
  G4double height_pmt        = fD_mtl / 2.;
  G4double startAngle_pmt    = 0.;
  G4double spanningAngle_pmt = 360. * deg;
  /*
  fPmt = new G4Tubs("pmt_tube", innerRadius_pmt, fOuterRadius_pmt, height_pmt,
                    startAngle_pmt, spanningAngle_pmt);
  */
  //fPmt = new G4Box("pmt_box", pmt_squarex/2., pmt_squarey/2.,0.5*mm/2.);


  fPmtV = new G4Box("pmt_veto", pmt_squarex/2., pmt_squarey/2.,0.5*mm/2.);
  fPmtG = new G4Box("pmt_gagg", pmt_squarex/2., pmt_squarey/2.,0.5*mm/2.);

  

  // the "photocathode" is a metal slab at the back of the glass that
  // is only a very rough approximation of the real thing since it only
  // absorbs or detects the photons based on the efficiency set below

  /*
  fPhotocath = new G4Tubs("photocath_tube", innerRadius_pmt, fOuterRadius_pmt,
                          height_pmt / 2., startAngle_pmt, spanningAngle_pmt);
  */
   
  //fPhotocath = new G4Box("photocath_box",pmt_squarex/2., pmt_squarey/2.,(pmt_squarez-0.5*mm)/2.);

  
  fPhotocathV = new G4Box("photocath_veto",pmt_squarex/2., pmt_squarey/2.,(pmt_squarez-0.5*mm)/2.);
  
  fPhotocathG = new G4Box("photocath_gagg",pmt_squarex/2., pmt_squarey/2.,(pmt_squarez-0.5*mm)/2.);

  
  
  /*
  fPmt_log =
    new G4LogicalVolume(fPmt, G4Material::GetMaterial("Glass"), "pmt_log");
  */
  
  //fPmt_log = new G4LogicalVolume(fPmt, G4Material::GetMaterial("Glass"), "pmt_log");


  fPmtV_log = new G4LogicalVolume(fPmtV, G4Material::GetMaterial("Glass"), "pmtV_log");
  fPmtG_log = new G4LogicalVolume(fPmtG, G4Material::GetMaterial("Glass"), "pmtG_log");

  
  /*
  fPhotocath_log = new G4LogicalVolume(
    fPhotocath, G4Material::GetMaterial("Al"), "photocath_log");
  */
  
  //fPhotocath_log = new G4LogicalVolume(fPhotocath, G4Material::GetMaterial("Al"), "photocath_log");


  fPhotocathV_log = new G4LogicalVolume(fPhotocathV, G4Material::GetMaterial("Al"), "photocathV_log");
  fPhotocathG_log = new G4LogicalVolume(fPhotocathG, G4Material::GetMaterial("Al"), "photocathG_log");
  

  
  /*
 new G4PVPlacement(0, G4ThreeVector(0., 0., -height_pmt / 2.), fPhotocath_log,
                    "photocath", fPmt_log, false, 0);
  */
  //new G4PVPlacement(0, G4ThreeVector(0.,0., -(pmt_squarez)/2.), fPhotocath_log, "photocath", fPmt_log,false,0);

   new G4PVPlacement(0, G4ThreeVector(0.,0., -(pmt_squarez)/2.), fPhotocathV_log, "photocathV", fPmtV_log,false,0);
   new G4PVPlacement(0, G4ThreeVector(0.,0., -(pmt_squarez)/2.), fPhotocathG_log, "photocathG", fPmtG_log,false,0);

  //***********Arrange pmts around the outside of housing**********

  G4double dx = fVeto_x / fNx;
  G4double dy = fVeto_y / fNy;
  G4double dz = fVeto_z / fNz;

  G4double x, y, z;
  G4double xmin = -fVeto_x / 2. - dx / 2.;
  G4double ymin = -fVeto_y / 2. - dy / 2.;
  G4double zmin = -fVeto_z / 2. - dz / 2.;
  G4int k       = 0;
  /*
  z = -fScint_z / 2. - height_pmt;  // front
  PlacePMTs(fPmt_log, nullptr, x, y, dx, dy, xmin, ymin, fNx, fNy, x, y, z, k);
  */
  G4RotationMatrix* rm_z = new G4RotationMatrix();
  rm_z->rotateY(180. * deg);
  z = fVeto_z / 2. + height_pmt;  // back
  PlacePMTs(fPmtV_log, rm_z, x, y, dx, dy, xmin, ymin, fNx, fNy, x, y, z, k);

  
  PlacePMTs(fPmtG_log, rm_z, x, y, dx, dy, xmin, ymin, fNx, fNy, x, y, z, k);
  


  
  VisAttributes();
  SurfaceProperties();

  SetLogicalVolume(fIron_log);

  
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LXeMainVolume::CopyValues()
{
  /*
  fScint_x         = fConstructor->GetScintX();
  fScint_y         = fConstructor->GetScintY();
  fScint_z         = fConstructor->GetScintZ();
  */
  fD_mtl           = fConstructor->GetHousingThickness();
  fNx              = fConstructor->GetNX();
  fNy              = fConstructor->GetNY();
  fNz              = fConstructor->GetNZ();
  fOuterRadius_pmt = fConstructor->GetPMTRadius();
  //fSphereOn        = fConstructor->GetSphereOn();
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

  /*
  a = amin;
  for(G4int j = 1; j <= na; ++j)
  {
    a += da;
    b = bmin;
    for(G4int i = 1; i <= nb; ++i)
    {
      b += db;
      new G4PVPlacement(rot, G4ThreeVector(x, y, z), pmt_log, "pmt",
                        fHousing_log, false, k);
      fPmtPositions.push_back(G4ThreeVector(x, y, z));
      ++k;
    }
    }
  */
  
  G4double lcrystal_x = 2*2.54*cm;
  G4double lcrystal_y = 2*2.54*cm;
  G4double lcrystal_z = 2.54*cm;

  G4double air_pocketx = lcrystal_x+1*mm;
  G4double air_pockety = lcrystal_y+1*mm;
  //G4double air_pocketz = lcrystal_z + pmt_squarez+1*mm;

  G4double althinx = air_pocketx + 1*mm;
  G4double althiny = air_pockety + 1*mm;
  //G4double althinz = air_pocketz + 1*mm;
  
  G4double fVeto_x = althinx + 2*cm;
  G4double fVeto_y = althiny + 2*cm;
  //G4double fScint_z = air_pocketz + 2*cm;
  

  
  G4double al_GAGGz = lcrystal_z+1*mm;

  /*
  new G4PVPlacement(rot, G4ThreeVector(-fVeto_x/4.,-fVeto_y/4.,z-0.25*mm), fPmt_log, "pmt",fHousing_log, false, k);
fPmtPositions.push_back(G4ThreeVector(-fVeto_x/4.,-fVeto_y/4.,z-0.25*mm));
 
new G4PVPlacement(rot, G4ThreeVector(fVeto_x/4.,fVeto_y/4.,z-0.25*mm), fPmt_log, "pmt",fHousing_log, false,1);
fPmtPositions.push_back(G4ThreeVector(fVeto_x/4.,fVeto_y/4.,z-0.25*mm));
  
  
  new G4PVPlacement(rot, G4ThreeVector(0,0,(al_GAGGz-.5*mm)/2.), fPmt_log, "pmt",falumGAGG_log,false,2);
fPmtPositions.push_back(G4ThreeVector(0,0,(al_GAGGz-.5*mm)/2.));
  */



  //new G4PVPlacement(rot, G4ThreeVector(-fVeto_x/4.,-fVeto_y/4.,z-0.25*mm), fPmtV_log, "pmt_veto",fHousing_log, false, 0);
  new G4PVPlacement(rot, G4ThreeVector(0,0,z-0.25*mm), fPmtV_log, "pmt_veto",fHousing_log, false, 0);
  
  new G4PVPlacement(rot, G4ThreeVector(0,0,(al_GAGGz-.5*mm)/2.), fPmtG_log, "pmt_gagg",falumGAGG_log,false, 0);

 
  				      
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LXeMainVolume::VisAttributes()
{
  G4VisAttributes* housing_va = new G4VisAttributes(G4Colour(0.8, 0.8, 0.8));
  fHousing_log->SetVisAttributes(housing_va);
  /*
  G4VisAttributes* sphere_va = new G4VisAttributes();
  sphere_va->SetForceSolid(true);
  fSphere_log->SetVisAttributes(sphere_va);
  */
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//Defining the surface properties to different materials.

void LXeMainVolume::SurfaceProperties()
{
  //Surface property to all aluminum portions. 
  std::vector<G4double> ephoton ={((c_light*h_Planck)/(350*nm))*eV, ((c_light*h_Planck)/(370*nm))*eV, ((c_light*h_Planck)/(380*nm))*eV, ((c_light*h_Planck)/(390*nm))*eV, ((c_light*h_Planck)/(400*nm))*eV, ((c_light*h_Planck)/(410*nm))*eV, ((c_light*h_Planck)/(420*nm))*eV,((c_light*h_Planck)/(425*nm))*eV, ((c_light*h_Planck)/(430*nm))*eV, ((c_light*h_Planck)/(440*nm))*eV,     ((c_light*h_Planck)/(450*nm))*eV, ((c_light*h_Planck)/(460*nm))*eV,((c_light*h_Planck)/(470*nm))*eV, ((c_light*h_Planck)/(480*nm))*eV, ((c_light*h_Planck)/(490*nm))*eV, ((c_light*h_Planck)/(500*nm))*eV, ((c_light*h_Planck)/(510*nm))*eV,((c_light*h_Planck)/(520*nm))*eV,((c_light*h_Planck)/(530*nm))*eV,((c_light*h_Planck)/(540*nm))*eV,((c_light*h_Planck)/(550*nm))*eV};
  //**Scintillator housing properties
  std::vector<G4double> reflectivity     = { fRefl, fRefl, fRefl, fRefl, fRefl, fRefl, fRefl, fRefl, fRefl, fRefl, fRefl, fRefl, fRefl, fRefl,fRefl, fRefl, fRefl, fRefl, fRefl, fRefl, fRefl};
  std::vector<G4double> efficiency       = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  G4MaterialPropertiesTable* scintHsngPT = new G4MaterialPropertiesTable();
  scintHsngPT->AddProperty("REFLECTIVITY", ephoton, reflectivity);
  scintHsngPT->AddProperty("EFFICIENCY", ephoton, efficiency);
  G4OpticalSurface* OpScintHousingSurface =
    new G4OpticalSurface("HousingSurface", unified, polished, dielectric_metal);
  OpScintHousingSurface->SetMaterialPropertiesTable(scintHsngPT);



  
 
  //**Photocathode surface properties
  std::vector<G4double> photocath_EFF     = { 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1.,1., 1., 1., 1., 1., 1., 1.};
  std::vector<G4double> photocath_ReR     = { 1.92, 1.92, 1.92, 1.92, 1.92, 1.92, 1.92, 1.92, 1.92, 1.92, 1.92, 1.92, 1.92, 1.92, 1.92, 1.92, 1.92, 1.92, 1.92, 1.92, 1.92};
  std::vector<G4double> photocath_ImR     = { 1.69, 1.69, 1.69, 1.69, 1.69, 1.69, 1.69, 1.69, 1.69, 1.69, 1.69, 1.69, 1.69, 1.69, 1.69, 1.69, 1.69, 1.69, 1.69, 1.69, 1.69};
  G4MaterialPropertiesTable* photocath_mt = new G4MaterialPropertiesTable();
  photocath_mt->AddProperty("EFFICIENCY", ephoton, photocath_EFF);
  photocath_mt->AddProperty("REALRINDEX", ephoton, photocath_ReR);
  photocath_mt->AddProperty("IMAGINARYRINDEX", ephoton, photocath_ImR);
  G4OpticalSurface* photocath_opsurf = new G4OpticalSurface(
    "photocath_opsurf", glisur, polished, dielectric_metal);
  photocath_opsurf->SetMaterialPropertiesTable(photocath_mt);

  //**Create logical skin surfaces
  new G4LogicalSkinSurface("photocath_surf", fHousing_log,
                           OpScintHousingSurface);


  
  //new G4LogicalSkinSurface("photocath_surf", fPhotocath_log, photocath_opsurf);
  //new G4LogicalSkinSurface("alum_surf", falum_log,OpScintHousingSurface);
  new G4LogicalSkinSurface("photocathV_surf", fPhotocathV_log, photocath_opsurf);
  new G4LogicalSkinSurface("photocathG_surf", fPhotocathG_log, photocath_opsurf);
  

  new G4LogicalSkinSurface("photocath_surf", falumGAGG_log,OpScintHousingSurface);
  new G4LogicalSkinSurface("alumthin_surf", falumthin_log, OpScintHousingSurface); 

  
  
}
