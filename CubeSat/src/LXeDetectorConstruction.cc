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
/// \file optical/LXe/src/LXeDetectorConstruction.cc
/// \brief Implementation of the LXeDetectorConstruction class
//
//
#include "LXeDetectorConstruction.hh"

#include "LXeDetectorMessenger.hh"
#include "LXeMainVolume.hh"
#include "LXePMTSD.hh"
#include "LXeScintSD.hh"
#include "LXeEljinSD.hh"
//#include "LXeWLSSlab.hh"

#include "globals.hh"
#include "G4Box.hh"
#include "G4GeometryManager.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4LogicalVolume.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4OpticalSurface.hh"
#include "G4PhysicalConstants.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4PVPlacement.hh"
#include "G4RunManager.hh"
#include "G4SDManager.hh"
#include "G4SolidStore.hh"
#include "G4Sphere.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "G4Tubs.hh"
#include "G4UImanager.hh"
#include "G4VisAttributes.hh"
#include "G4NistManager.hh"

//G4bool LXeDetectorConstruction::fSphereOn = true;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LXeDetectorConstruction::LXeDetectorConstruction()
  : fLXe_mt(nullptr)
  , fMPTPStyrene(nullptr)
{
  fExperimentalHall_box  = nullptr;
  fExperimentalHall_log  = nullptr;
  fExperimentalHall_phys = nullptr;

  fLXe = fAl = fAir = fVacuum = fGlass = fEpoxy = fFe = fEljin_200 = nullptr;
  fPstyrene = fPMMA = fPethylene1 = fPethylene2 = fIronShield = nullptr;

  fN = fO = fC = fH  = nullptr;

  fSaveThreshold = 0;
  SetDefaults();

  DefineMaterials();
  fDetectorMessenger = new LXeDetectorMessenger(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LXeDetectorConstruction::~LXeDetectorConstruction()
{
  if(fMainVolume)
  {
    delete fMainVolume;
  }
  delete fLXe_mt;
  delete feljin_mt;
  delete fDetectorMessenger;
  delete fMPTPStyrene;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LXeDetectorConstruction::DefineMaterials()
{
  G4NistManager* nist = G4NistManager::Instance();


  
  G4double a;  // atomic mass
  G4double z;  // atomic number
  G4int ncomponents;
  G4double density, densityCombined;

  G4int polyPMMA = 1;
  G4int nC_PMMA  = 3 + 2 * polyPMMA;
  G4int nH_PMMA  = 6 + 2 * polyPMMA;

  G4int polyeth = 1;
  G4int nC_eth  = 2 * polyeth;
  G4int nH_eth  = 4 * polyeth;

  //***Elements
  fH = new G4Element("H", "H", z = 1., a = 1.01 * g / mole);
  fC = new G4Element("C", "C", z = 6., a = 12.01 * g / mole);
  fN = new G4Element("N", "N", z = 7., a = 14.01 * g / mole);
  fO = new G4Element("O", "O", z = 8., a = 16.00 * g / mole);
 

  //***Materials
  // Liquid Xenon
  fLXe = new G4Material("LXe", z = 54., a = 131.29 * g / mole,
                        density = 3.020 * g / cm3);
  // Aluminum
  fAl = new G4Material("Al", z = 13., a = 26.98 * g / mole,
                       density = 2.7 * g / cm3);
  // Vacuum
  fVacuum = new G4Material("Vacuum", z = 1., a = 1.01 * g / mole,
                           density = universe_mean_density, kStateGas,
                           0.1 * kelvin, 1.e-19 * pascal);

  fFe = nist -> FindOrBuildMaterial("G4_Fe");
  fEpoxy = nist->FindOrBuildMaterial("G4_POLYSTYRENE");


  //Getting Fractional Masses of Iron and Epoxy
  densityCombined = 4*g/cm3;

  G4double mass_epoxy=1;
  
  G4double mass_iron = (densityCombined/(7.87*g/cm3)-1)/(1-densityCombined/(1.15*g/cm3))*mass_epoxy;
  G4double epoxy_frac = mass_epoxy/(mass_iron+mass_epoxy);
  G4double iron_frac = mass_iron/(mass_iron+mass_epoxy);

  fIronShield = new G4Material("Iron Shield", densityCombined, ncomponents = 2);
  fIronShield->AddMaterial(fFe, iron_frac);
  fIronShield->AddMaterial(fEpoxy, epoxy_frac);

  fEljin_200 = new G4Material("Eljin", density = 1.02*g/cm3, ncomponents = 2);
  fEljin_200->AddElement(fC, 91.55* perCent);
  fEljin_200->AddElement(fH, 8.45* perCent);
  

  
  // Air
  fAir = new G4Material("Air", density = 1.29 * mg / cm3, 2);
  fAir->AddElement(fN, 70 * perCent);
  fAir->AddElement(fO, 30 * perCent);
  // Glass
  fGlass = new G4Material("Glass", density = 1.032 * g / cm3, 2);
  fGlass->AddElement(fC, 91.533 * perCent);
  fGlass->AddElement(fH, 8.467 * perCent);


  //***Material properties tables

//This portion is acting as the GAGG crystal material properties
	    std::vector<G4double> lxe_Energy ={((c_light*h_Planck)/(400*nm))*eV, ((c_light*h_Planck)/(410*nm))*eV,((c_light*h_Planck)/(420*nm))*eV,((c_light*h_Planck)/(430*nm))*eV,((c_light*h_Planck)/(440*nm))*eV,((c_light*h_Planck)/(450*nm))*eV,
		                               ((c_light*h_Planck)/(460*nm))*eV,((c_light*h_Planck)/(470*nm))*eV,((c_light*h_Planck)/(480*nm))*eV,((c_light*h_Planck)/(490*nm))*eV,((c_light*h_Planck)/(500*nm))*eV, ((c_light*h_Planck)/(510*nm))*eV,
		                               ((c_light*h_Planck)/(520*nm))*eV,((c_light*h_Planck)/(530*nm))*eV,((c_light*h_Planck)/(540*nm))*eV,((c_light*h_Planck)/(550*nm))*eV,((c_light*h_Planck)/(560*nm))*eV,((c_light*h_Planck)/(570*nm))*eV,
					       ((c_light*h_Planck)/(580*nm))*eV,((c_light*h_Planck)/(590*nm))*eV,((c_light*h_Planck)/(600*nm))*eV,((c_light*h_Planck)/(610*nm))*eV, ((c_light*h_Planck)/(620*nm))*eV, ((c_light*h_Planck)/(630*nm))*eV,
		                               ((c_light*h_Planck)/(640*nm))*eV, ((c_light*h_Planck)/(650*nm))*eV};

  std::vector<G4double> lxe_SCINT = { 0., 0., 0., 0., 0., 0., 0., 0.02, 0.13, 0.385, 0.766, 0.95, 1.00, 0.96, 0.896, 0.814, 0.716, 0.62, 0.51, 0.42, 0.34, 0.288, 0.242, 0.211, 0.185, 0.162};
  std::vector<G4double> lxe_RIND  = { 1.9, 1.9, 1.9 , 1.9, 1.9, 1.9, 1.9 , 1.9, 1.9, 1.9, 1.9 , 1.9, 1.9, 1.9, 1.9 , 1.9, 1.9, 1.9, 1.9 , 1.9, 1.9, 1.9, 1.9 , 1.9, 1.9, 1.9};
  std::vector<G4double> lxe_ABSL  = { 380.* cm, 380.* cm, 380.* cm, 380.* cm, 380.* cm, 380.* cm, 380.* cm, 380.* cm,380.* cm, 380.* cm, 380.* cm, 380.* cm,380.* cm, 380.* cm, 380.* cm, 380.* cm,380.* cm, 380.* cm, 380.* cm, 380.* cm,380.* cm, 380.* cm, 380.* cm, 380.* cm, 380.* cm, 380.* cm};
  fLXe_mt = new G4MaterialPropertiesTable();
  fLXe_mt->AddProperty("SCINTILLATIONCOMPONENT1", lxe_Energy, lxe_SCINT);
  //fLXe_mt->AddProperty("SCINTILLATIONCOMPONENT2", lxe_Energy, lxe_SCINT);
  fLXe_mt->AddProperty("RINDEX", lxe_Energy, lxe_RIND);
  fLXe_mt->AddProperty("ABSLENGTH", lxe_Energy, lxe_ABSL);
  fLXe_mt->AddConstProperty("SCINTILLATIONYIELD", 42000. / MeV);
  fLXe_mt->AddConstProperty("RESOLUTIONSCALE", 1.0);
  fLXe_mt->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 20. * ns);
  //fLXe_mt->AddConstProperty("SCINTILLATIONTIMECONSTANT2", 45. * ns);
  fLXe_mt->AddConstProperty("SCINTILLATIONYIELD1", 1.0);
  //fLXe_mt->AddConstProperty("SCINTILLATIONYIELD2", 0.0);
  fLXe->SetMaterialPropertiesTable(fLXe_mt);

  // Set the Birks Constant for the LXe scintillator
  fLXe->GetIonisation()->SetBirksConstant(0.126 * mm / MeV);



  //Glass Material Properties for the PMT portion
  std::vector<G4double> glass_RIND      = { 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49};
  std::vector<G4double> glass_AbsLength = { 420. * cm, 420. * cm, 420. * cm, 420.*cm, 420. * cm, 420. * cm, 420. * cm, 420.*cm, 420. * cm, 420. * cm, 420. * cm, 420.*cm, 420. * cm, 420. * cm, 420. * cm, 420.*cm,420. * cm, 420. * cm, 420. * cm, 420.*cm, 420. * cm, 420. * cm, 420. * cm, 420.*cm, 420. * cm, 420.*cm};  

  G4MaterialPropertiesTable* glass_mt   = new G4MaterialPropertiesTable();
  glass_mt->AddProperty("ABSLENGTH", lxe_Energy, glass_AbsLength);
  glass_mt->AddProperty("RINDEX", lxe_Energy, glass_RIND);
  fGlass->SetMaterialPropertiesTable(glass_mt);


//Material needed for when the photons go to Vacuum.
  //std::vector<G4double> vacuum_Energy  = { 2.0 * eV, 7.0 * eV, 7.14 * eV };
   std::vector<G4double> vacuum_Energy = {((c_light*h_Planck)/(400*nm))*eV, ((c_light*h_Planck)/(410*nm))*eV,((c_light*h_Planck)/(420*nm))*eV,((c_light*h_Planck)/(430*nm))*eV,((c_light*h_Planck)/(440*nm))*eV,((c_light*h_Planck)/(450*nm))*eV,
		                          ((c_light*h_Planck)/(460*nm))*eV,((c_light*h_Planck)/(470*nm))*eV,((c_light*h_Planck)/(480*nm))*eV,((c_light*h_Planck)/(490*nm))*eV,((c_light*h_Planck)/(500*nm))*eV, ((c_light*h_Planck)/(510*nm))*eV,
		                          ((c_light*h_Planck)/(520*nm))*eV,((c_light*h_Planck)/(530*nm))*eV,((c_light*h_Planck)/(540*nm))*eV,((c_light*h_Planck)/(550*nm))*eV,((c_light*h_Planck)/(560*nm))*eV,((c_light*h_Planck)/(570*nm))*eV,
					  ((c_light*h_Planck)/(580*nm))*eV,((c_light*h_Planck)/(590*nm))*eV,((c_light*h_Planck)/(600*nm))*eV,((c_light*h_Planck)/(610*nm))*eV, ((c_light*h_Planck)/(620*nm))*eV, ((c_light*h_Planck)/(630*nm))*eV,
		                          ((c_light*h_Planck)/(640*nm))*eV, ((c_light*h_Planck)/(650*nm))*eV};

  std::vector<G4double> vacuum_RIND    = { 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1.,1.,1.,1.,1.};

  G4MaterialPropertiesTable* vacuum_mt = new G4MaterialPropertiesTable();
  vacuum_mt->AddProperty("RINDEX", vacuum_Energy, vacuum_RIND);
  fVacuum->SetMaterialPropertiesTable(vacuum_mt);
  fAir->SetMaterialPropertiesTable(vacuum_mt);  // Give air the same rindex



//Eljin Scintillator (Veto) Properties
   std::vector<G4double> Eljin_Energy ={((c_light*h_Planck)/(400*nm))*eV, ((c_light*h_Planck)/(410*nm))*eV,((c_light*h_Planck)/(420*nm))*eV,((c_light*h_Planck)/(430*nm))*eV,((c_light*h_Planck)/(440*nm))*eV,((c_light*h_Planck)/(450*nm))*eV,
		                        ((c_light*h_Planck)/(460*nm))*eV,((c_light*h_Planck)/(470*nm))*eV,((c_light*h_Planck)/(480*nm))*eV,((c_light*h_Planck)/(490*nm))*eV,((c_light*h_Planck)/(500*nm))*eV};


  std::vector<G4double> Eljin_SCINT = {0., 0.26, 0.914, 0.98, 0.78, 0.565, 0.445, 0.308, 0.177, 0.097, 0.05};
  std::vector<G4double> Eljin_RIND  = {1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58};
  std::vector<G4double> Eljin_ABSL  = {380.*cm, 380.*cm, 380.*cm, 380.*cm, 380.*cm, 380.*cm, 380.*cm, 380.*cm, 380.*cm, 380.*cm, 380.*cm};
  feljin_mt = new G4MaterialPropertiesTable();

  feljin_mt->AddProperty("SCINTILLATIONCOMPONENT1", Eljin_Energy, Eljin_SCINT);
  
  feljin_mt->AddProperty("RINDEX", Eljin_Energy, Eljin_RIND);
  feljin_mt->AddProperty("ABSLENGTH", Eljin_Energy, Eljin_ABSL);
  feljin_mt->AddConstProperty("SCINTILLATIONYIELD", 10000. / MeV);
  feljin_mt->AddConstProperty("RESOLUTIONSCALE", 1.0);
  feljin_mt->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 20. * ns);
  feljin_mt->AddConstProperty("SCINTILLATIONYIELD1", 1.0);
  //feljin_mt->AddConstProperty("SCINTILLATIONYIELD2", 0.0);
  fEljin_200->SetMaterialPropertiesTable(feljin_mt);


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* LXeDetectorConstruction::Construct()
{


  // The experimental hall walls are all 1m away from housing walls
  G4double expHall_x = fD_mtl + 2. * m;
  G4double expHall_y = fD_mtl + 2. * m;
  G4double expHall_z = fD_mtl + 2. * m;

  // Create experimental hall
  fExperimentalHall_box =
    new G4Box("expHall_box", expHall_x, expHall_y, expHall_z);
  fExperimentalHall_log =
    new G4LogicalVolume(fExperimentalHall_box, fVacuum, "expHall_log", 0, 0, 0);
  fExperimentalHall_phys = new G4PVPlacement(
    0, G4ThreeVector(), fExperimentalHall_log, "expHall", 0, false, 0);

  fExperimentalHall_log->SetVisAttributes(G4VisAttributes::GetInvisible());

  // Place the main volume
  if(fMainVolumeOn)
  {
    fMainVolume = new LXeMainVolume(0, G4ThreeVector(), fExperimentalHall_log,
                                    false, 0, this);
  }
  
  return fExperimentalHall_phys;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LXeDetectorConstruction::ConstructSDandField()
{
  if(!fMainVolume)
    return;

  // PMT SD

  LXePMTSD* pmt = fPmt_SD.Get();
  if(!pmt)
  {
    // Created here so it exists as pmts are being placed
    G4cout << "Construction /LXeDet/pmtSD" << G4endl;
    LXePMTSD* pmt_SD = new LXePMTSD("/LXeDet/pmtSD");
    fPmt_SD.Put(pmt_SD);

    pmt_SD->InitPMTs();
    pmt_SD->SetPmtPositions(fMainVolume->GetPmtPositions());
  }
  else
  {
    pmt->InitPMTs();
    pmt->SetPmtPositions(fMainVolume->GetPmtPositions());
  }
  G4SDManager::GetSDMpointer()->AddNewDetector(fPmt_SD.Get());
  // sensitive detector is not actually on the photocathode.
  // processHits gets done manually by the stepping action.
  // It is used to detect when photons hit and get absorbed & detected at the
  // boundary to the photocathode (which doesn't get done by attaching it to a
  // logical volume.
  // It does however need to be attached to something or else it doesn't get
  // reset at the begining of events

  SetSensitiveDetector(fMainVolume->GetLogPhotoCath(), fPmt_SD.Get());

//This is delacring the GAGG crystal as a sensitive detector
  if(!fScint_SD.Get())
  {
    G4cout << "Construction /LXeDet/scintSD" << G4endl;
    LXeScintSD* scint_SD = new LXeScintSD("/LXeDet/scintSD");
    fScint_SD.Put(scint_SD);
  }
  G4SDManager::GetSDMpointer()->AddNewDetector(fScint_SD.Get());
  SetSensitiveDetector(fMainVolume->GetLogScint(), fScint_SD.Get());

//Same usage but this will be for the Veto System.

if(!fEljin_SD.Get())
  {
    G4cout << "Construction /LXeDet/eljinSD" << G4endl;
    LXeEljinSD* eljin_SD = new LXeEljinSD("/LXeDet/eljinSD");
    fEljin_SD.Put(eljin_SD);
  }
  G4SDManager::GetSDMpointer()->AddNewDetector(fEljin_SD.Get());
  SetSensitiveDetector(fMainVolume->GetLogVeto(), fEljin_SD.Get());





}


//Don't have to worry too much about the section below, this was from the original example that I did not want to manipulate too much. 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
/*
void LXeDetectorConstruction::SetDimensions(G4ThreeVector dims)
{
  fScint_x = dims[0];
  fScint_y = dims[1];
  fScint_z = dims[2];
  G4RunManager::GetRunManager()->ReinitializeGeometry();
}
*/
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LXeDetectorConstruction::SetHousingThickness(G4double d_mtl)
{
  fD_mtl = d_mtl;
  G4RunManager::GetRunManager()->ReinitializeGeometry();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LXeDetectorConstruction::SetNX(G4int nx)
{
  fNx = nx;
  G4RunManager::GetRunManager()->ReinitializeGeometry();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LXeDetectorConstruction::SetNY(G4int ny)
{
  fNy = ny;
  G4RunManager::GetRunManager()->ReinitializeGeometry();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LXeDetectorConstruction::SetNZ(G4int nz)
{
  fNz = nz;
  G4RunManager::GetRunManager()->ReinitializeGeometry();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LXeDetectorConstruction::SetPMTRadius(G4double outerRadius_pmt)
{
  fOuterRadius_pmt = outerRadius_pmt;
  G4RunManager::GetRunManager()->ReinitializeGeometry();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LXeDetectorConstruction::SetDefaults()
{
  // Resets to default values
  fD_mtl = 1* mm;
  /*
  fScint_x = 17.8 * cm;
  fScint_y = 17.8 * cm;
  fScint_z = 22.6 * cm;
  */
  fNx = 2;
  fNy = 2;
  fNz = 0;

  fOuterRadius_pmt = 2.3 * mm;

  //fSphereOn = true;
  fRefl     = 1.0;

  fNfibers      = 15;
  //fWLSslab      = false;
  fMainVolumeOn = true;
  fMainVolume   = nullptr;
  //fSlab_z       = 2.5 * mm;

  G4UImanager::GetUIpointer()->ApplyCommand(
    "/LXe/detector/scintYieldFactor 1.");

  if(fLXe_mt)
    fLXe_mt->AddConstProperty("SCINTILLATIONYIELD", 12000. / MeV);
  if(fMPTPStyrene)
    fMPTPStyrene->AddConstProperty("SCINTILLATIONYIELD", 10. / keV);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
/*
void LXeDetectorConstruction::SetSphereOn(G4bool b)
{
  fSphereOn = b;
  G4RunManager::GetRunManager()->ReinitializeGeometry();
}
*/
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LXeDetectorConstruction::SetHousingReflectivity(G4double r)
{
  fRefl = r;
  G4RunManager::GetRunManager()->ReinitializeGeometry();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
/*
void LXeDetectorConstruction::SetWLSSlabOn(G4bool b)
{
  fWLSslab = b;
  G4RunManager::GetRunManager()->ReinitializeGeometry();
}
*/
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LXeDetectorConstruction::SetMainVolumeOn(G4bool b)
{
  fMainVolumeOn = b;
  G4RunManager::GetRunManager()->ReinitializeGeometry();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
/*
void LXeDetectorConstruction::SetNFibers(G4int n)
{
  fNfibers = n;
  G4RunManager::GetRunManager()->ReinitializeGeometry();
}
*/
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LXeDetectorConstruction::SetMainScintYield(G4double y)
{
  fLXe_mt->AddConstProperty("SCINTILLATIONYIELD", y / MeV);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LXeDetectorConstruction::SetWLSScintYield(G4double y)
{
  fMPTPStyrene->AddConstProperty("SCINTILLATIONYIELD", y / MeV);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LXeDetectorConstruction::SetSaveThreshold(G4int save)
{
  // Sets the save threshold for the random number seed. If the number of
  // photons generated in an event is lower than this, then save the seed for
  // this event in a file called run###evt###.rndm

  fSaveThreshold = save;
  G4RunManager::GetRunManager()->SetRandomNumberStore(true);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
