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
/// \file optical/CSat/src/CSatMainVolume.cc
/// \brief Implementation of the CSatMainVolume class
//
//
#include "CSatMainVolume.hh"

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


CSatMainVolume::CSatMainVolume(G4RotationMatrix* pRot, const G4ThreeVector& tlate,
                             G4LogicalVolume* pMotherLogical, G4bool pMany,
                             G4int pCopyNo, CSatDetectorConstruction* c)
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

 

  G4double lcrystal_x = 3*cm;
  G4double lcrystal_y = 3*cm;
  G4double lcrystal_z = 1.4*cm;
  
  G4double pmt_gaggx = 3.0*cm;
  G4double pmt_gaggy = 3.0*cm;
  G4double pmt_gaggz = 1*cm;
  
  G4double pmt_vetox = 5.2*cm;
  G4double pmt_vetoy = 5.2*cm;
  G4double pmt_vetoz = 3.9*cm;

  

  G4double air_pocketx = lcrystal_x+2*mm;
  G4double air_pockety = lcrystal_y+2*mm;
  G4double air_pocketz = lcrystal_z + pmt_gaggz+3*mm;

  G4double al_GAGGx = lcrystal_x+1*mm;
  G4double al_GAGGy = lcrystal_y+1*mm;
  G4double al_GAGGz = lcrystal_z+1*mm;
  
  G4double althinx = air_pocketx + 1*mm;
  G4double althiny = air_pockety + 1*mm;
  G4double althinz = air_pocketz + 1*mm;

  G4double fVeto_x = 5.15*cm;
  G4double fVeto_y = 5.15*cm;
  G4double fVeto_z = 4.5*cm;
  
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
  G4double housing_x = fVeto_x + 2. * 1*mm;
  G4double housing_y = fVeto_y + 2. * 1*mm;
  G4double housing_z = fVeto_z + 2. * 1*mm;

  G4double iron_shieldx = 8.3*cm;
  G4double iron_shieldy = 8.3*cm;
  G4double iron_shieldz = 11.5*cm;

  G4double Emptyx = 20*cm;
  G4double Emptyy = 20*cm;
  G4double Emptyz = 20*cm;


   //Creating empty space so we can rotate the Iron 

   G4Box* emptyspace = new G4Box("empty", Emptyx/2., Emptyy/2., Emptyz/2.);
   G4LogicalVolume* emptyspaceLog = new G4LogicalVolume(emptyspace, G4Material::GetMaterial("Vacuum"), "spaceLog", 0,0,0);
   

    
  //Iron Shield Outside
  
  fIronShield = new G4Box("iron_shield", iron_shieldx/2., iron_shieldy/2., iron_shieldz/2.);

  fIron_log = new G4LogicalVolume(fIronShield, G4Material::GetMaterial("Iron Shield"),"iron_log", 0,0,0);

  
  G4RotationMatrix* rot = new G4RotationMatrix();
  rot->rotateY(225/10*deg);
  new G4PVPlacement(rot,G4ThreeVector(), fIron_log, "Shielding", emptyspaceLog, false, 0);
  
  


  //AirGap between Shield and Detector

  fAirGap = new G4Box("air_gap", (housing_x+2*mm)/2.,(housing_y+2*mm)/2., (housing_z+ pmt_vetoz + 2*mm)/2.);

  fAirGap_log = new G4LogicalVolume(fAirGap, G4Material::GetMaterial("Air"), "air_gap", 0,0,0);

  new G4PVPlacement(0, G4ThreeVector(), fAirGap_log, "air_gap_shield", fIron_log,false,0);
  
  
  

  //*************************** housing and scintillator
//Changing Things Around


  fVeto = new G4Box("Veto", fVeto_x/2., fVeto_y/2., fVeto_z/2.);


  fVeto_Log = new G4LogicalVolume(fVeto, G4Material::GetMaterial("Eljin"),"veto_log",0,0,0);



  fHousing_box =
    new G4Box("housing_box", housing_x / 2., housing_y / 2., housing_z / 2.);

  fHousing_log = new G4LogicalVolume(
    fHousing_box, G4Material::GetMaterial("Al"), "housing_log", 0, 0, 0);
  

  new G4PVPlacement(0,G4ThreeVector(0,0,0),fVeto_Log,"Veto_Scint",fHousing_log, false , 0); 

  new G4PVPlacement(0, G4ThreeVector(0,0,-pmt_vetoz/2.), fHousing_log, "housing_al",fAirGap_log,false,0);


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

  new G4PVPlacement(0, G4ThreeVector(0,0,(al_GAGGz-air_pocketz+1.5*mm)/2.),falumGAGG_log, "alum_gagg", fair_log,false,0);



  //-----------------------------------------------------------------------------
  //GAGG Cystal Place Holder
  

  fScint_box =
    new G4Box("scint_box", lcrystal_x/ 2., lcrystal_y / 2., lcrystal_z / 2.);

  fScint_log   = new G4LogicalVolume(fScint_box, G4Material::GetMaterial("GAGG"),
                                   "scint_log", 0, 0, 0);

  new G4PVPlacement(0, G4ThreeVector(), fScint_log, "scintillator",
                    falumGAGG_log, false, 0);
  




  
  fPhotocathV = new G4Box("photocath_veto",pmt_vetox/2., pmt_vetoy/2.,(pmt_vetoz)/2.);
  
  fPhotocathG = new G4Box("photocath_gagg",pmt_gaggx/2., pmt_gaggy/2.,(pmt_gaggz)/2.);

  
  
  fPhotocathV_log = new G4LogicalVolume(fPhotocathV, G4Material::GetMaterial("Al"), "photocathV_log");
  fPhotocathG_log = new G4LogicalVolume(fPhotocathG, G4Material::GetMaterial("Al"), "photocathG_log");
  

  

  G4RotationMatrix* rm_z = new G4RotationMatrix();
   rm_z->rotateY(180. * deg);
   G4double z = fVeto_z / 2.;  // back

  
  new G4PVPlacement(rm_z, G4ThreeVector(0,0,(z+(pmt_vetoz/2.))), fPhotocathV_log, "pmt_veto",fHousing_log, false, 0);
  
  new G4PVPlacement(rm_z, G4ThreeVector(0,0,(lcrystal_z+pmt_gaggz)/2.), fPhotocathG_log, "pmt_gagg",falumGAGG_log,false, 0);




 
  

  


  
  
  VisAttributes();
  SurfaceProperties();

  SetLogicalVolume(emptyspaceLog);
  
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CSatMainVolume::CopyValues()
{
 
  fNx              = fConstructor->GetNX();
  fNy              = fConstructor->GetNY();
  fNz              = fConstructor->GetNZ();
  fOuterRadius_pmt = fConstructor->GetPMTRadius();
  fRefl            = fConstructor->GetHousingReflectivity();
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CSatMainVolume::VisAttributes()
{
 

  G4VisAttributes* gagg_VA = new G4VisAttributes(G4Colour(1.,1.,0.,0.5));
  gagg_VA->SetForceSolid(true);
  fScint_log->SetVisAttributes(gagg_VA);

  G4VisAttributes* Veto_VA = new G4VisAttributes(G4Colour(0, 0, 0.5, 0.3));
  Veto_VA->SetForceSolid(true);
  fVeto_Log->SetVisAttributes(Veto_VA);

  G4VisAttributes* VetoPMT_VA = new G4VisAttributes(G4Colour(1, 0, 0, 1));
  VetoPMT_VA->SetForceSolid(true);
  fPhotocathV_log->SetVisAttributes(VetoPMT_VA);

  G4VisAttributes* gaggPMT_VA = new G4VisAttributes(G4Colour(1, 0, 0, 0.7));
  gaggPMT_VA->SetForceSolid(true);
  fPhotocathG_log->SetVisAttributes(gaggPMT_VA);
  
 

  G4VisAttributes* Iron_VA = new G4VisAttributes(G4Colour(0.5, 0.5, 0.5, 0.3));
  Iron_VA->SetForceSolid(true);
  fIron_log->SetVisAttributes(Iron_VA);

   
 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//Defining the surface properties to different materials.

void CSatMainVolume::SurfaceProperties()
{
  //Surface property to all aluminum portions.

  
  std::vector<G4double> ephoton = { 1.2398/.400 , 1.2398/.410 , 1.2398/.420 , 1.2398/.430 , 1.2398/.440 , 1.2398/.450 ,
				    1.2398/.460 , 1.2398/.470 , 1.2398/.480 , 1.2398/.490 , 1.2398/.500 , 1.2398/.510 ,
				    1.2398/.520 , 1.2398/.530 , 1.2398/.540 , 1.2398/.550 , 1.2398/.560 , 1.2398/.570 ,
				    1.2398/.580 , 1.2398/.590 , 1.2398/.600 , 1.2398/.610 , 1.2398/.620 , 1.2398/.630 ,
				    1.2398/.640 , 1.2398/.650 };
  
  //**Scintillator housing properties
  std::vector<G4double> reflectivity     = { fRefl, fRefl, fRefl, fRefl, fRefl, fRefl,
					     fRefl, fRefl, fRefl, fRefl, fRefl, fRefl,
					     fRefl, fRefl, fRefl, fRefl, fRefl, fRefl,
					     fRefl, fRefl, fRefl, fRefl, fRefl, fRefl,
					     fRefl, fRefl};
  
  std::vector<G4double> efficiency       = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
					     0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
					     0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
					     0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
					     0.0, 0.0};
  
  G4MaterialPropertiesTable* scintHsngPT = new G4MaterialPropertiesTable();
  scintHsngPT->AddProperty("REFLECTIVITY", ephoton, reflectivity);
  scintHsngPT->AddProperty("EFFICIENCY", ephoton, efficiency);
  G4OpticalSurface* OpScintHousingSurface =
    new G4OpticalSurface("HousingSurface", unified, polished, dielectric_metal);
  OpScintHousingSurface->SetMaterialPropertiesTable(scintHsngPT);



  
  
  //**Photocathode surface properties
  std::vector<G4double> photocath_EFF     = { 1., 1., 1., 1., 1., 1.,
					      1., 1., 1., 1., 1., 1.,
					      1., 1., 1., 1., 1., 1.,
					      1., 1., 1., 1., 1., 1.,
					      1.,1.};
  
  std::vector<G4double> photocath_ReR     = { 1.92, 1.92, 1.92, 1.92, 1.92, 1.92,
					      1.92, 1.92, 1.92, 1.92, 1.92, 1.92,
					      1.92, 1.92, 1.92, 1.92, 1.92, 1.92,
					      1.92, 1.92, 1.92, 1.92, 1.92, 1.92,
					      1.92, 1.92};
  
  std::vector<G4double> photocath_ImR     = { 1.69, 1.69, 1.69, 1.69, 1.69, 1.69,
					      1.69, 1.69, 1.69, 1.69, 1.69, 1.69,
					      1.69, 1.69, 1.69, 1.69, 1.69, 1.69,
					      1.69, 1.69, 1.69, 1.69, 1.69, 1.69,
					      1.69, 1.69};
  
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

  new G4LogicalSkinSurface("photocathV_surf", fPhotocathV_log, photocath_opsurf);
  new G4LogicalSkinSurface("photocathG_surf", fPhotocathG_log, photocath_opsurf);

  

  

  new G4LogicalSkinSurface("alumGAGG_surf", falumGAGG_log, OpScintHousingSurface);
  new G4LogicalSkinSurface("alumthin_surf", falumthin_log, OpScintHousingSurface); 

  
  
}



