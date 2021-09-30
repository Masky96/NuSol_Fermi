#!/bin/bash
# First tests of a shell script to do a bunch of runs at once

#Energy Variable
#EnergyValue=1


#Setting the number of threads for the experiment.
#NThreads=14

#Number of particles to Run
NParticles=1


#For Particle energies in GeV
for EnergyValue in  100000 1000000 10000000 100000000 1000000000 
do
    #Loop over the different particles
    for particleName in  "mu-" "tau-" "e-" 
    do

	#Loop over attenuation lengths
	for AttenLcm in  5e3 #1e-1 1e0 1e1 1e2 1e3 1e4 1e5 1e6
	do

	    #Define the Directory for the doings
	    directory='Histogram for Particles'
            #Make the Directory for the files to go into
            mkdir "$directory"
	    
	    
	    #Fix up phys.mac for use with proper energy for particle
	    echo "# Macro file for the initialization of physics items
# This file follows ans.mac in the ~geant4/ansmt/source directory
# It provides information to the PhysicsListMessenger


#BACKGROUND STUDIES (neutrino studies found below)

#/gps/particle proton
#/gps/particle neutron
#/gps/particle gamma
#/gps/particle e+
#/gps/particle e-
#/gps/particle anti_proton
#/gps/particle anti_neutron
#/gps/particle alpha
#/gps/particle ion
#/gps/ion 26 56 26 0

#  MY STUDIES
#Point Source of electrons for Scintillation


/run/initialize
#/run/numberOfThreads '"$NThreads"'

/gun/particle $particleName
/gun/energy $EnergyValue GeV

#Creating Histograms
/analysis/setFileName "$particleName+$EnergyValue+$AttenLcm"
/analysis/h1/set 3 40 380 790 nm

/tracking/verbose 0 
/tracking/storeTrajectory 0


/control/verbose 0
/control/saveHistory
/run/verbose 0

/run/initialize
/run/printProgress 1


/run/beamOn "$NParticles"" > photon.mac

echo '//
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
  //, fMPTPStyrene(nullptr)
{
  fExperimentalHall_box  = nullptr;
  fExperimentalHall_log  = nullptr;
  fExperimentalHall_phys = nullptr;

  fLXe = fAl = fAir = fVacuum = fGlass = fmolecH =  nullptr;
  fPstyrene = fPMMA = fPethylene1 = fPethylene2 = nullptr;

  fN = fO = fC = fH = nullptr;

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
  delete fDetectorMessenger;
  //delete fMPTPStyrene;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LXeDetectorConstruction::DefineMaterials()
{

  G4NistManager* nist = G4NistManager::Instance();
  G4double a;  // atomic mass
  G4double z;  // atomic number
  G4int nelements, ncomponents;
  G4double density;

  //***Elements
  fH = new G4Element("H", "H", z = 1., a = 1.01 * g / mole);
  //fC = new G4Element("C", "C", z = 6., a = 12.01 * g / mole);
  //fN = new G4Element("N", "N", z = 7., a = 14.01 * g / mole);
  //fO = new G4Element("O", "O", z = 8., a = 16.00 * g / mole);
  


  //***Materials

  //Methane Gas
  fMethane = nist->FindOrBuildMaterial("G4_METHANE");
  
  //Helium Gas	
  fHe = nist -> FindOrBuildMaterial("G4_He");


  //Neptunes Atmosphere
  fmolecH = new G4Material("Molecular Hydrogen", 0.0899* g/ cm3, nelements = 1);
  fmolecH ->AddElement(fH,2);

  fnepAt = new G4Material("Neptune Atmosphere", density = 0.00045 * g / cm3, ncomponents = 3, kStateGas, 55*kelvin, 10000*pascal);
  fnepAt -> AddMaterial(fmolecH, 80*perCent);
  fnepAt -> AddMaterial(fHe, 19*perCent);
  fnepAt -> AddMaterial(fMethane, 1*perCent);

  /*
  // Liquid Xenon
  fLXe = new G4Material("LXe", z = 54., a = 131.29 * g / mole,
                        density = 3.020 * g / cm3);

  
  // Aluminum
  fAl = new G4Material("Al", z = 13., a = 26.98 * g / mole,
                       density = 2.7 * g / cm3);
  */
  // Vacuum
  fVacuum = new G4Material("Vacuum", z = 1., a = 1.01 * g / mole,
                           density = universe_mean_density, kStateGas,
                           0.1 * kelvin, 1.e-19 * pascal);
 
  /*
  // Glass
  fGlass = new G4Material("Glass", density = 1.032 * g / cm3, 2);
  fGlass->AddElement(fC, 91.533 * perCent);
  fGlass->AddElement(fH, 8.467 * perCent);
  
  */



  //***Material properties tables
  std::vector<G4double> lxe_Energy = {1.588 * eV, 1.622 * eV, 1.657 * eV, 1.691 * eV, 1.725 * eV, 1.76 * eV, 1.794 * eV, 1.828 * eV,1.863 * eV, 1.897 * eV, 1.931 * eV,1.966 * eV, 2.00 * eV,
				      2.034 * eV, 2.068 * eV, 2.103 * eV, 2.139 * eV, 2.177 * eV, 2.216 * eV,
				      2.256 * eV, 2.298 * eV, 2.341 * eV, 2.386 * eV, 2.433 * eV, 2.481 * eV,
				      2.532 * eV, 2.585 * eV, 2.640 * eV, 2.697 * eV, 2.757 * eV, 2.820 * eV,
				      2.885 * eV, 2.954 * eV, 3.026 * eV, 3.102 * eV, 3.181 * eV, 3.265 * eV,
				      3.353 * eV, 3.446 * eV, 3.545 * eV, 3.649 * eV, 3.760 * eV, 3.877 * eV,
				      4.002 * eV, 4.136 * eV
  };
  
  std::vector<G4double> lxe_SCINT = {1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
    1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
				     1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00
  }; 

  std::vector<G4double> lxe_RIND  = {1.00013746013, 1.000137532569, 1.00013761206, 1.000137691217, 1.000137772048, 1.000137857102, 1.000137942084, 1.000138029198, 1.000138121605, 1.000138207496, 1.000138298874, 1.000138394758, 1.000138489695,
				     1.000138588, 1.000138687, 1.00013879, 1.000138898, 1.000139015, 1.000139136, 1.000139264, 1.000139401, 1.000139543, 1.000139696, 1.00013986, 1.000140029, 1.000140214, 1.000140411, 1.00014062, 1.000140842,
				     1.000141082, 1.000141341, 1.000141615, 1.000141913, 1.000142236, 1.000142585, 1.00014296, 1.000143371, 1.000143816, 1.000144303, 1.00014484,1.000145426, 1.000146076, 1.000146791, 1.000147586, 1.00014848 };

  std::vector<G4double> lxe_ABSL  = { 
'"$AttenLcm"' * cm, '"$AttenLcm"' * cm, '"$AttenLcm"' * cm, '"$AttenLcm"' * cm, '"$AttenLcm"' * cm, '"$AttenLcm"' * cm, '"$AttenLcm"' * cm, '"$AttenLcm"' * cm, '"$AttenLcm"' * cm, '"$AttenLcm"' * cm, '"$AttenLcm"' * cm, '"$AttenLcm"' * cm, '"$AttenLcm"' * cm,
'"$AttenLcm"' * cm, '"$AttenLcm"' * cm, '"$AttenLcm"' * cm, '"$AttenLcm"' * cm, '"$AttenLcm"' * cm, '"$AttenLcm"' * cm, '"$AttenLcm"' * cm, '"$AttenLcm"' * cm, '"$AttenLcm"' * cm, '"$AttenLcm"' * cm, '"$AttenLcm"' * cm, '"$AttenLcm"' * cm, '"$AttenLcm"' * cm,
'"$AttenLcm"' * cm, '"$AttenLcm"' * cm, '"$AttenLcm"' * cm, '"$AttenLcm"' * cm, '"$AttenLcm"' * cm, '"$AttenLcm"' * cm, '"$AttenLcm"' * cm, '"$AttenLcm"' * cm, '"$AttenLcm"' * cm, '"$AttenLcm"' * cm, '"$AttenLcm"' * cm, '"$AttenLcm"' * cm, '"$AttenLcm"' * cm,
'"$AttenLcm"' * cm, '"$AttenLcm"' * cm, '"$AttenLcm"' * cm, '"$AttenLcm"' * cm, '"$AttenLcm"' * cm, '"$AttenLcm"' *cm};



  fLXe_mt = new G4MaterialPropertiesTable();
  fLXe_mt->AddProperty("SCINTILLATIONCOMPONENT1", lxe_Energy, lxe_SCINT);
  fLXe_mt->AddProperty("SCINTILLATIONCOMPONENT2", lxe_Energy, lxe_SCINT);
  fLXe_mt->AddProperty("RINDEX", lxe_Energy, lxe_RIND);
  fLXe_mt->AddProperty("ABSLENGTH", lxe_Energy, lxe_ABSL);
  fLXe_mt->AddConstProperty("SCINTILLATIONYIELD", 1000. / MeV);
  fLXe_mt->AddConstProperty("RESOLUTIONSCALE", 1.0);
  fLXe_mt->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 20. * ns);
  fLXe_mt->AddConstProperty("SCINTILLATIONTIMECONSTANT2", 45. * ns);
  fLXe_mt->AddConstProperty("SCINTILLATIONYIELD1", 1.0);
  fLXe_mt->AddConstProperty("SCINTILLATIONYIELD2", 0.0);
  fnepAt->SetMaterialPropertiesTable(fLXe_mt);


  
  // Set the Birks Constant for the LXe scintillator
  fnepAt->GetIonisation()->SetBirksConstant(0.126 *mm /MeV);
  /*
  std::vector<G4double> glass_RIND = { 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49, 1.49 };

  std::vector<G4double> glass_AbsLength = { 420. * cm, 420. * cm, 420. * cm, 420. * cm, 420. * cm, 420. * cm, 420. * cm, 420. * cm, 420. * cm, 420. * cm, 420. * cm, 420. * cm, 420. * cm, 420. * cm, 420. * cm, 420. * cm, 420. * cm, 420. * cm, 420. * cm, 420. * cm, 420. * cm, 420. * cm, 420. * cm, 420. * cm, 420. * cm, 420. * cm, 420. * cm, 420. * cm, 420. * cm, 420. * cm, 420. * cm, 420. * cm };

  G4MaterialPropertiesTable* glass_mt   = new G4MaterialPropertiesTable();
  glass_mt->AddProperty("ABSLENGTH", lxe_Energy, glass_AbsLength);
  glass_mt->AddProperty("RINDEX", lxe_Energy, glass_RIND);
  fGlass->SetMaterialPropertiesTable(glass_mt);
  */
  

  std::vector<G4double> vacuum_Energy  = {1.588 * eV, 1.622 * eV, 1.657 * eV, 1.691 * eV, 1.725 * eV, 1.760 * eV, 1.794 * eV, 1.828 * eV, 1.863 * eV, 1.897 * eV, 1.931 * eV,1.966 * eV, 2.00* eV,
					  2.034 * eV, 2.068 * eV, 2.103 * eV, 2.139 * eV, 2.177 * eV, 2.216 * eV, 2.256 * eV, 2.298 * eV, 2.341 * eV, 2.386 * eV, 2.433 * eV, 2.481 * eV,
					  2.532 * eV, 2.585 * eV, 2.640 * eV, 2.697 * eV, 2.757 * eV, 2.820 * eV, 2.885 * eV, 2.954 * eV, 3.026 * eV, 3.102 * eV, 3.181 * eV, 3.265 * eV,
					  3.353 * eV, 3.446 * eV, 3.545 * eV, 3.649 * eV, 3.760 * eV, 3.877 * eV, 4.002 * eV, 4.136 * eV };

  std::vector<G4double> vacuum_RIND = { 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1.};


  G4MaterialPropertiesTable* vacuum_mt = new G4MaterialPropertiesTable();
  vacuum_mt->AddProperty("RINDEX", vacuum_Energy, vacuum_RIND);
  fVacuum->SetMaterialPropertiesTable(vacuum_mt);
 // Give air the same rindex

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* LXeDetectorConstruction::Construct()
{
  // The experimental hall walls are all 1m away from housing walls
  G4double expHall_x = fScint_x + 25. * km; 
  G4double expHall_y = fScint_y + 25. * km; 
  G4double expHall_z = fScint_z + 225. * km; 

  // Create experimental hall
  fExperimentalHall_box =
    new G4Box("expHall_box", expHall_x/2, expHall_y/2, expHall_z/2);
  fExperimentalHall_log =
    new G4LogicalVolume(fExperimentalHall_box, fVacuum, "expHall_log", 0, 0, 0);
  fExperimentalHall_phys = new G4PVPlacement(
    0, G4ThreeVector(), fExperimentalHall_log, "expHall", 0, false, 0);

  fExperimentalHall_log ->SetVisAttributes(G4VisAttributes::GetInvisible());

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
  // boundary to the photocathode (which does not get done by attaching it to a
  // logical volume.
  // It does however need to be attached to something or else it does not get
  // reset at the begining of events

  SetSensitiveDetector(fMainVolume->GetLogPhotoCath(), fPmt_SD.Get());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LXeDetectorConstruction::SetDimensions(G4ThreeVector dims)
{
  fScint_x = dims[0];
  fScint_y = dims[1];
  fScint_z = dims[2];
  G4RunManager::GetRunManager()->ReinitializeGeometry();
}

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
  fD_mtl = 1.0* m;

  fScint_x = 100. * km;
  fScint_y = 100. * km;
  fScint_z = 10. * km;



  fOuterRadius_pmt = 0.5*m;

  
  fRefl     = 0.41;

  fMainVolumeOn = true;
  fMainVolume   = nullptr;
  

  G4UImanager::GetUIpointer()->ApplyCommand(
    "/LXe/detector/scintYieldFactor 1.");

  if(fLXe_mt)
   // fLXe_mt->AddConstProperty("SCINTILLATIONYIELD", 120. / MeV);
    fLXe_mt->AddConstProperty("SCINTILLATIONYIELD", 1000. / MeV);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


void LXeDetectorConstruction::SetHousingReflectivity(G4double r)
{
  fRefl = r;
  G4RunManager::GetRunManager()->ReinitializeGeometry();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LXeDetectorConstruction::SetMainVolumeOn(G4bool b)
{
  fMainVolumeOn = b;
  G4RunManager::GetRunManager()->ReinitializeGeometry();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LXeDetectorConstruction::SetMainScintYield(G4double y)
{
  fLXe_mt->AddConstProperty("SCINTILLATIONYIELD", y / MeV);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

' > LXeDetectorConstruction.cc


            mv LXeDetectorConstruction.cc ~/Desktop/LXe/src
	    make
	    ./LXe photon.mac
	    #Extra spaces added because the files want to move too soon otherwise.
	    #Don't know exactly why
	    
	    
	    
	    
	    

	    
	    mv $particleName+$EnergyValue+$AttenLcm.root "$directory"
	   
	done
    done
done
