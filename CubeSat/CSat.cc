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
/// \file optical/CSat/CSat.cc
/// \brief Main program of the optical/CSat example
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "CSatActionInitialization.hh"
#include "CSatDetectorConstruction.hh"

#include "FTFP_BERT.hh"
//#include "G4EmStandardPhysics_option4.hh"
#include "G4OpticalParameters.hh"
#include "G4OpticalPhysics.hh"
#include "G4RunManagerFactory.hh"
#include "G4String.hh"
#include "G4Types.hh"
#include "G4UIExecutive.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"

#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4EmLivermorePhysics.hh"
#include "G4TrajectoryDrawByParticleID.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc, char** argv)
{
  // detect interactive mode (if no arguments) and define UI session
  G4UIExecutive* ui = nullptr;
  if(argc == 1)
  {
    ui = new G4UIExecutive(argc, argv);
  }

  auto runManager = G4RunManagerFactory::CreateRunManager();
  runManager-> SetNumberOfThreads(2);

  CSatDetectorConstruction* det = new CSatDetectorConstruction();
  runManager->SetUserInitialization(det);

  G4VModularPhysicsList* physicsList = new FTFP_BERT();
  physicsList->ReplacePhysics(new G4EmLivermorePhysics());
  

  //Declaring our Decay and RadioActive Decay's.
  
  G4DecayPhysics* fDecayPhys = new G4DecayPhysics();
  physicsList->RegisterPhysics(fDecayPhys);

  G4RadioactiveDecayPhysics* fRadDecayPhy = new G4RadioactiveDecayPhysics();
  physicsList->RegisterPhysics(fRadDecayPhy);






  

  G4OpticalPhysics* opticalPhysics = new G4OpticalPhysics();
  auto opticalParams               = G4OpticalParameters::Instance();

  opticalParams->SetWLSTimeProfile("delta");

  opticalParams->SetScintYieldFactor(1.0);
  //opticalParams->SetScintExcitationRatio(0.0);
  opticalParams->SetScintTrackSecondariesFirst(true);
  opticalParams->SetScintEnhancedTimeConstants(true);

  opticalParams->SetCerenkovMaxPhotonsPerStep(100);
  opticalParams->SetCerenkovMaxBetaChange(10.0);
  opticalParams->SetCerenkovTrackSecondariesFirst(true);

  physicsList->RegisterPhysics(opticalPhysics);
  runManager->SetUserInitialization(physicsList);

  runManager->SetUserInitialization(new CSatActionInitialization(det));



  
  // initialize visualization
  G4VisManager* visManager = new G4VisExecutive;


  
  visManager->Initialize();
  
  





  

  // get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  if(ui)
  {
    // interactive mode
    UImanager->ApplyCommand("/process/em/auger true");
    UImanager->ApplyCommand("/process/em/augerCascade true");
    UImanager->ApplyCommand("/process/em/pixe true");
    UImanager->ApplyCommand("/process/em/deexcitationIgnoreCut true");
    UImanager->ApplyCommand("/control/execute vis.mac");
    UImanager->ApplyCommand("/vis/ogl/set/displayListLimit 100000000");
    UImanager->ApplyCommand("/vis/multithreading/actionOnEventQueueFull wait");
    UImanager->ApplyCommand("/vis/multithreading/maxEventQueueSize 0");
    /*
    if(ui->IsGUI())
    {
      UImanager->ApplyCommand("/control/execute gui.mac");
    }
    */
    ui->SessionStart();
    delete ui;
  }
  else
  {
    // batch mode
    G4String command  = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command + fileName);
  }

  // job termination
  delete visManager;
  delete runManager;
  return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
