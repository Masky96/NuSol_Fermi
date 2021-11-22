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
/// \file optical/CSat/src/CSatRun.cc
/// \brief Implementation of the CSatRun class
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "CSatRun.hh"

#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CSatRun::CSatRun()
  : G4Run()
{
  fHitCount = fHitCount2 = 0;
  fHitCount_1 = fHitCount_12 = 0;
  fHitCount_2 = fHitCount_22 = 0;
  fHitCount_3 = fHitCount_32 = 0; 

  
  fPhotonCount_Scint = fPhotonCount_Scint2 = 0;
  fPhotonCount_Ceren = fPhotonCount_Ceren2 = 0;
  fAbsorptionCount = fAbsorptionCount2 = 0;
  fBoundaryAbsorptionCount = fBoundaryAbsorptionCount2 = 0;
  fPMTsAboveThreshold = fPMTsAboveThreshold2 = 0;

  fTotE = fTotE2 = 0.0;
  fTotEljin = fTotEljin2 = 0.0;

  fTotEG = fTotEG2 = 0.0;
  fTotEV = fTotEV2 = 0.0;

  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CSatRun::~CSatRun() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CSatRun::Merge(const G4Run* run)
{
  const CSatRun* localRun = static_cast<const CSatRun*>(run);

  fHitCount += localRun->fHitCount;
  fHitCount2 += localRun->fHitCount2;

  fHitCount_1 += localRun->fHitCount_1;
  fHitCount_12 += localRun->fHitCount_12;
   
  fHitCount_2 += localRun->fHitCount_2;
  fHitCount_22 += localRun->fHitCount_22;

  fHitCount_3 += localRun->fHitCount_3;
  fHitCount_32 += localRun->fHitCount_32;


  
  fPMTsAboveThreshold += localRun->fPMTsAboveThreshold;
  fPMTsAboveThreshold2 += localRun->fPMTsAboveThreshold2;
  fPhotonCount_Scint += localRun->fPhotonCount_Scint;
  fPhotonCount_Scint2 += localRun->fPhotonCount_Scint2;
  fPhotonCount_Ceren += localRun->fPhotonCount_Ceren;
  fPhotonCount_Ceren2 += localRun->fPhotonCount_Ceren2;
  fAbsorptionCount += localRun->fAbsorptionCount;
  fAbsorptionCount2 += localRun->fAbsorptionCount2;
  fBoundaryAbsorptionCount += localRun->fBoundaryAbsorptionCount;
  fBoundaryAbsorptionCount2 += localRun->fBoundaryAbsorptionCount2;
  fTotE += localRun->fTotE;
  fTotE2 += localRun->fTotE2;

  //New
  fTotEljin  += localRun ->fTotEljin;
  fTotEljin2 += localRun ->fTotEljin2;

  fTotEG += localRun->fTotEG;
  fTotEG2 += localRun->fTotEG2;

  
  fTotEV += localRun->fTotEV;
  fTotEV2 += localRun->fTotEV2;

  

  G4Run::Merge(run);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CSatRun::EndOfRun()
{
  G4cout << "\n ======================== run summary ======================\n";

  G4int prec = G4cout.precision();

  G4double n_evt = (G4double) numberOfEvent;
  G4cout << "The run was " << numberOfEvent << " events." << G4endl;

  G4cout.precision(4);
  G4double hits     = G4double(fHitCount) / n_evt;
  G4double hits2    = G4double(fHitCount2) / n_evt;
  G4double rms_hits = hits2 - hits * hits;
  if(rms_hits > 0.)
    rms_hits = std::sqrt(rms_hits / n_evt);
  else
    rms_hits = 0.;
  G4cout << "Number of hits per event:\t " << hits << " +- " << rms_hits
         << G4endl;

  //------------------------------------------------------------------
/*
  G4cout << "Number of hits in PMT 0:\t " << fHitCount_1 << G4endl;
  G4cout << "Number of hits in PMT 1:\t " << fHitCount_2 << G4endl;
  G4cout << "Number of hits in PMT 2:\t " << fHitCount_3 << G4endl;
*/
  //Information about PMT_Veto_1
  /*
  G4double Veto_1_hits  = G4double(fHitCount_1)/n_evt;
  G4double Veto_1_hits2 = G4double(fHitCount_12)/n_evt;

  G4double rms_Veto1 = Veto_1_hits2 - Veto_1_hits*Veto_1_hits;

  if(rms_Veto1 >0.)
     rms_Veto1 = std::sqrt(rms_Veto1/n_evt);
  else
    rms_Veto1 = 0.;
  G4cout << "Number of hits in Veto 1 per event:\t " << Veto_1_hits << " +- " << rms_Veto1
	 << G4endl;

  //Information about PMT_Veto_2 

  G4double Veto_2_hits  = G4double(fHitCount_2)/n_evt;
  G4double Veto_2_hits2 = G4double(fHitCount_22)/n_evt;

  G4double rms_Veto2 = Veto_2_hits2 - Veto_2_hits*Veto_2_hits;

  if(rms_Veto2 >0.)
     rms_Veto2 = std::sqrt(rms_Veto2/n_evt);
  else
    rms_Veto2 = 0.;
  G4cout << "Number of hits in Veto 2 per event:\t " << Veto_2_hits << " +- " << rms_Veto2
         << G4endl;

  //Information about GAGG PMT
  G4double GAGG_hits  = G4double(fHitCount_3)/n_evt;
  G4double GAGG_hits2 = G4double(fHitCount_32)/n_evt;

  G4double rms_GAGG = GAGG_hits2 - GAGG_hits *GAGG_hits;

  if(rms_GAGG >0.)
     rms_GAGG = std::sqrt(rms_GAGG/n_evt);
  else
    rms_GAGG = 0.;
  G4cout << "Number of hits in the GAGG PMT :\t " << GAGG_hits << " +- " << rms_GAGG
         << G4endl;
  //------------------------------------------------------------------

  G4double hitsAbove     = G4double(fPMTsAboveThreshold) / n_evt;
  G4double hitsAbove2    = G4double(fPMTsAboveThreshold2) / n_evt;
  G4double rms_hitsAbove = hitsAbove2 - hitsAbove * hitsAbove;
  if(rms_hitsAbove > 0.)
    rms_hitsAbove = std::sqrt(rms_hitsAbove / n_evt);
  else
    rms_hitsAbove = 0.;

  G4cout << "Number of hits per event above threshold:\t " << hitsAbove
         << " +- " << rms_hitsAbove << G4endl;

  */
  G4double scint     = G4double(fPhotonCount_Scint) / n_evt;
  G4double scint2    = G4double(fPhotonCount_Scint2) / n_evt;
  G4double rms_scint = scint2 - scint * scint;
  if(rms_scint > 0.)
    rms_scint = std::sqrt(rms_scint / n_evt);
  else
    rms_scint = 0.;

  G4cout << "Number of scintillation photons per event :\t " << scint << " +- "
         << rms_scint << G4endl;

  G4double ceren     = G4double(fPhotonCount_Ceren) / n_evt;
  G4double ceren2    = G4double(fPhotonCount_Ceren2) / n_evt;
  G4double rms_ceren = ceren2 - ceren * ceren;
  if(rms_ceren > 0.)
    rms_ceren = std::sqrt(rms_ceren / n_evt);
  else
    rms_ceren = 0.;

  G4cout << "Number of Cerenkov photons per event:\t " << ceren << " +- "
         << rms_ceren << G4endl;

  G4double absorb     = G4double(fAbsorptionCount) / n_evt;
  G4double absorb2    = G4double(fAbsorptionCount2) / n_evt;
  G4double rms_absorb = absorb2 - absorb * absorb;
  if(rms_absorb > 0.)
    rms_absorb = std::sqrt(rms_absorb / n_evt);
  else
    rms_absorb = 0.;

  G4cout << "Number of absorbed photons per event :\t " << absorb << " +- "
         << rms_absorb << G4endl;

  G4double bdry     = G4double(fBoundaryAbsorptionCount) / n_evt;
  G4double bdry2    = G4double(fBoundaryAbsorptionCount2) / n_evt;
  G4double rms_bdry = bdry2 - bdry * bdry;
  if(rms_bdry > 0.)
    rms_bdry = std::sqrt(rms_bdry / n_evt);
  else
    rms_bdry = 0.;

  G4cout << "Number of photons absorbed at boundary per event:\t " << bdry
         << " +- " << rms_bdry << G4endl;

  G4double en     = fTotE / n_evt;
  G4double en2    = fTotE2 / n_evt;
  G4double rms_en = en2 - en * en;
  if(rms_en > 0.)
    rms_en = std::sqrt(rms_en / n_evt);
  else
    rms_en = 0.;

  G4cout << "Total energy deposition in scintillator per event:\t " << en / MeV
         << " +- " << rms_en / MeV << " MeV." << G4endl;

  //New --------------------------------------------------------------

  G4double enVeto  = fTotEljin/ n_evt;
  G4double enVeto2 = fTotEljin2 / n_evt;

  G4double rms_enVeto = enVeto2 - enVeto * enVeto;

  if( rms_enVeto > 0)
    rms_enVeto = std::sqrt(rms_enVeto/n_evt);
  else
    rms_enVeto = 0.;

  G4cout << "Total energy deposition in the Veto per event:\t" << enVeto /MeV
         << " +- " << rms_enVeto/MeV << " MeV. " << G4endl;




  //------------------------------------------------------

  
  G4double enG     = fTotEG / n_evt;
  G4double enG2    = fTotEG2 / n_evt;
  G4double rms_enG = enG2 - enG * enG;
  if(rms_enG > 0.)
    rms_enG = std::sqrt(rms_enG / n_evt);
  else
    rms_enG = 0.;

  G4cout << "Total energy deposition in scintillator PMT  per event:\t " << enG / eV
         << " +- " << rms_enG / eV << " eV." << G4endl;
  //-------------------------------------------------------------------
  G4double enV     = fTotEV / n_evt;
  G4double enV2    = fTotEV2 / n_evt;
  G4double rms_enV = enV2 - enV * enV;
  if(rms_enV > 0.)
    rms_enV = std::sqrt(rms_enV / n_evt);
  else
    rms_enV = 0.;

  G4cout << "Total energy deposition in VETO PMT  per event:\t " << enV / eV 
         << " +- " << rms_enV / eV  << " eV." << G4endl;





  
  G4cout << G4endl;
  G4cout.precision(prec);
}
