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
/// \file optical/LXe/src/LXeRun.cc
/// \brief Implementation of the LXeRun class
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "LXeRun.hh"

#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LXeRun::LXeRun()
  : G4Run()
{
  fHitCount = fHitCount2 = 0;
  //fPhotonCount_Scint = fPhotonCount_Scint2 = 0;
  //fPhotonCount_Ceren = fPhotonCount_Ceren2 = 0;
  //fAbsorptionCount = fAbsorptionCount2 = 0;
  //fBoundaryAbsorptionCount = fBoundaryAbsorptionCount2 = 0;
  fPMTsAboveThreshold = fPMTsAboveThreshold2 = 0;

  //fTotE = fTotE2 = 0.0;

  //New 
  fHitC1   =   fHitC1_2      = 0;
  fHitC2   =   fHitC2_2      = 0;
  fHitC3   =   fHitC3_2      = 0;
  fHitC4   =   fHitC4_2      = 0;
  fHitC5   =   fHitC5_2      = 0;
  fHitC6   =   fHitC6_2      = 0;
  fHitC7   =   fHitC7_2      = 0;
  fHitC8   =   fHitC8_2      = 0;
  /*
  fHitC9   =   fHitC9_2      = 0;
  fHitC10  =   fHitC10_2     = 0;
  fHitC11  =   fHitC11_2     = 0;
  fHitC12  =   fHitC12_2     = 0;
  fHitC13  =   fHitC13_2     = 0;
  fHitC14  =   fHitC14_2     = 0;
  fHitC15  =   fHitC15_2     = 0;
  fHitC16  =   fHitC16_2     = 0;
  */
  fTotEP_tot = fTotEP2_tot = 0.0;
  
  fTotEP1  =  fTotEP1_2  = 0.0;
  fTotEP2  =  fTotEP2_2  = 0.0;
  fTotEP3  =  fTotEP3_2  = 0.0;
  fTotEP4  =  fTotEP4_2  = 0.0;
  fTotEP5  =  fTotEP5_2  = 0.0;
  fTotEP6  =  fTotEP6_2  = 0.0;
  fTotEP7  =  fTotEP7_2  = 0.0;
  fTotEP8  =  fTotEP8_2  = 0.0;
  /*
  fTotEP9  =  fTotEP9_2  = 0.0;
  fTotEP10  =  fTotEP10_2  = 0.0;
  fTotEP11  =  fTotEP11_2  = 0.0;
  fTotEP12  =  fTotEP12_2  = 0.0;
  fTotEP13  =  fTotEP13_2  = 0.0;
  fTotEP14  =  fTotEP14_2  = 0.0;
  fTotEP15  =  fTotEP15_2  = 0.0;
  fTotEP16  =  fTotEP16_2  = 0.0;
  */
 

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LXeRun::~LXeRun() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LXeRun::Merge(const G4Run* run)
{
  const LXeRun* localRun = static_cast<const LXeRun*>(run);

  fHitCount += localRun->fHitCount;
  fHitCount2 += localRun->fHitCount2;
  fPMTsAboveThreshold += localRun->fPMTsAboveThreshold;
  fPMTsAboveThreshold2 += localRun->fPMTsAboveThreshold2;

  



  
/*
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
*/  

  //New
  fTotEP_tot += localRun->fTotEP_tot;
  fTotEP2_tot += localRun->fTotEP2_tot;

  
  fTotEP1 += localRun->fTotEP1;
  fTotEP1_2 += localRun->fTotEP1_2;
  
  fTotEP2 += localRun->fTotEP2;
  fTotEP2_2 += localRun->fTotEP2_2;
  
  fTotEP3 += localRun->fTotEP3;
  fTotEP3_2 += localRun->fTotEP3_2;
  
  fTotEP4 += localRun->fTotEP4;
  fTotEP4_2 += localRun->fTotEP4_2;
  
  fTotEP5 += localRun->fTotEP5;
  fTotEP5_2 += localRun->fTotEP5_2;
  
  fTotEP6 += localRun->fTotEP6;
  fTotEP6_2 += localRun->fTotEP6_2;
  
  fTotEP7 += localRun->fTotEP7;
  fTotEP7_2 += localRun->fTotEP7_2;
  
  fTotEP8 += localRun->fTotEP8;
  fTotEP8_2 += localRun->fTotEP8_2;
  /*
  fTotEP9 += localRun->fTotEP9;
  fTotEP9_2 += localRun->fTotEP9_2;
  
  fTotEP10 += localRun->fTotEP10;
  fTotEP10_2 += localRun->fTotEP10_2;
  
  fTotEP11 += localRun->fTotEP11;
  fTotEP11_2 += localRun->fTotEP11_2;
  
  fTotEP12 += localRun->fTotEP12;
  fTotEP12_2 += localRun->fTotEP12_2;
  
  fTotEP13 += localRun->fTotEP13;
  fTotEP13_2 += localRun->fTotEP13_2;
  
  fTotEP14 += localRun->fTotEP14;
  fTotEP14_2 += localRun->fTotEP14_2;
  
  fTotEP15 += localRun->fTotEP15;
  fTotEP15_2 += localRun->fTotEP15_2;

  fTotEP16 += localRun->fTotEP16;
  fTotEP16_2 += localRun->fTotEP16_2;
  */

  fHitC1 += localRun ->fHitC1;
  fHitC1_2 += localRun -> fHitC1_2;
  
  fHitC2 += localRun ->fHitC2;
  fHitC2_2 += localRun -> fHitC2_2;

  fHitC3 += localRun ->fHitC3;
  fHitC3_2 += localRun -> fHitC3_2;

  fHitC4 += localRun ->fHitC4;
  fHitC4_2 += localRun -> fHitC4_2;

  fHitC5 += localRun ->fHitC5;
  fHitC5_2 += localRun -> fHitC5_2;

  fHitC6 += localRun ->fHitC6;
  fHitC6_2 += localRun -> fHitC6_2;

  fHitC7 += localRun ->fHitC7;
  fHitC7_2 += localRun -> fHitC7_2;

  fHitC8 += localRun ->fHitC8;
  fHitC8_2 += localRun -> fHitC8_2;

  /*
  fHitC9 += localRun ->fHitC9;
  fHitC9_2 += localRun -> fHitC9_2;
  
  fHitC10 += localRun ->fHitC10;
  fHitC10_2 += localRun -> fHitC10_2;
  
  fHitC11 += localRun ->fHitC11;
  fHitC11_2 += localRun -> fHitC11_2;
  
  fHitC12 += localRun ->fHitC12;
  fHitC12_2 += localRun -> fHitC12_2;

  fHitC13 += localRun ->fHitC13;
  fHitC13_2 += localRun -> fHitC13_2;

  fHitC14 += localRun ->fHitC14;
  fHitC14_2 += localRun -> fHitC14_2;

  fHitC15 += localRun ->fHitC15;
  fHitC15_2 += localRun -> fHitC15_2;

  fHitC16 += localRun ->fHitC16;
  fHitC16_2 += localRun -> fHitC16_2;
  */


  

  

  
  //-----------------------------------------------

  G4Run::Merge(run);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LXeRun::EndOfRun()
{
  G4cout << "\n ======================== run summary ======================\n";

  G4int prec = G4cout.precision();

  G4double n_evt = (G4double) numberOfEvent;
  G4cout << "The run was " << numberOfEvent << " events." << G4endl;

  G4cout.precision(6);

  G4double hits     = G4double(fHitCount) / n_evt;
  G4double hits2    = G4double(fHitCount2) / n_evt;
  G4double rms_hits = hits2 - hits * hits;
  if(rms_hits > 0.)
    rms_hits = std::sqrt(rms_hits / n_evt);
  else
    rms_hits = 0.;
  G4cout << "Number of hits per event:\t " << hits << " +- " << rms_hits
         << G4endl;
  
  G4double hitsAbove     = G4double(fPMTsAboveThreshold) / n_evt;
  G4double hitsAbove2    = G4double(fPMTsAboveThreshold2) / n_evt;
  G4double rms_hitsAbove = hitsAbove2 - hitsAbove * hitsAbove;
  if(rms_hitsAbove > 0.)
    rms_hitsAbove = std::sqrt(rms_hitsAbove / n_evt);
  else
    rms_hitsAbove = 0.;

  G4cout << "Number of hits per event above threshold:\t " << hitsAbove
         << " +- " << rms_hitsAbove << G4endl;

//New--------------------------------------------------------------------
 G4double pmtEn         =G4double(fTotEP_tot)/n_evt;
 G4double pmtEn2        =G4double(fTotEP2_tot)/n_evt;
 G4double rms_pmtEn     = pmtEn2 - pmtEn * pmtEn;
  if(rms_pmtEn > 0.)
    rms_pmtEn = std::sqrt(rms_pmtEn/n_evt);
  else 
    rms_pmtEn = 0.;  


  G4cout << "Energy Deposition in PMT per event:\t " << pmtEn/ eV << " +- "
	 << rms_pmtEn/ eV << " eV" << G4endl;





 G4double avgEnph	= pmtEn/hits;

 G4cout << "Average Energy per Photon in PMT:\t " << avgEnph/eV << " eV" <<G4endl;


 G4cout << G4endl;
 //Specific Hits and Energies-------------------------------------------------------------------------

  G4double Hits1     = G4double(fHitC1) / n_evt;
  G4double Hits1_2    = G4double(fHitC1_2) / n_evt;
  G4double rms_Hits1 = Hits1_2 - Hits1 * Hits1;
  if(rms_Hits1 > 0.)
    rms_Hits1 = std::sqrt(rms_Hits1 / n_evt);
  else
    rms_Hits1 = 0.;
  G4cout << "Number of hits per event with a wavelength in the range of 625 nm to 780 nm:\t " << Hits1 << " +- " << rms_Hits1
         << G4endl;


  G4double ranEn1      =G4double(fTotEP1)/n_evt;
  G4double ranEn1_2    =G4double(fTotEP1_2)/n_evt;

  G4double rms_ranEn1  =ranEn1_2 - ranEn1 * ranEn1;
  if(rms_ranEn1 >0.)
    rms_ranEn1 = std::sqrt(rms_ranEn1/n_evt);
  else
    rms_ranEn1 = 0.;
  G4cout << "Energy Deposition in PMT with a wavelength in the range of 625 nm to 780 nm per event:\t " << ranEn1/eV  << " eV "<<  " +- " << rms_ranEn1/eV
         << " eV " << G4endl;

  

  G4double  avgranEn1;

  if(Hits1 >0)
      avgranEn1 = ranEn1/Hits1;
  else
      avgranEn1 = 0.;

  G4cout << "Average Energy per Photon in the range 625 nm to 780 nm:\t" << avgranEn1/eV << " eV" << G4endl;
  //------------------------------------------------------------------------------------------------------------------
  G4cout << G4endl;

  G4double Hits2     = G4double(fHitC2) / n_evt;
  G4double Hits2_2    = G4double(fHitC2_2) / n_evt;
  G4double rms_Hits2 = Hits2_2 - Hits2 * Hits2;
  if(rms_Hits2 > 0.)
    rms_Hits2 = std::sqrt(rms_Hits2 / n_evt);
  else
    rms_Hits2 = 0.;
  G4cout << "Number of hits per event with a wavelength in the range of 590 nm to 625 nm:\t " << Hits2 << " +- " << rms_Hits2
         << G4endl;


  G4double ranEn2      =G4double(fTotEP2)/n_evt;
  G4double ranEn2_2    =G4double(fTotEP2_2)/n_evt;

  G4double rms_ranEn2  =ranEn2_2 - ranEn2 * ranEn2;
  if(rms_ranEn2 >0.)
    rms_ranEn2 = std::sqrt(rms_ranEn2/n_evt);
  else
    rms_ranEn2 = 0.;
  G4cout << "Energy Deposition in PMT with a wavelength in the range of 590 nm to 625 nm per event:\t " << ranEn2/eV  << " eV "<<  " +- " << rms_ranEn2/eV
         << " eV " << G4endl;

  

  G4double  avgranEn2;

  if(Hits2 >0)
      avgranEn2 = ranEn2/Hits2;
  else
      avgranEn2 = 0.;

  G4cout << "Average Energy per Photon in range 590 nm to 625 nm:\t" << avgranEn2/eV << " eV" << G4endl;

  //-----------------------------------------------------------------------------------------------------------------
 G4cout << G4endl;
  
  G4double Hits3     = G4double(fHitC3) / n_evt;
  G4double Hits3_2    = G4double(fHitC3_2) / n_evt;
  G4double rms_Hits3 = Hits3_2 - Hits3 * Hits3;
  if(rms_Hits3 > 0.)
    rms_Hits3 = std::sqrt(rms_Hits3 / n_evt);
  else
    rms_Hits3 = 0.;
  G4cout << "Number of hits per event with a wavelength in the range of 565 nm to 590 nm:\t " << Hits3 << " +- " << rms_Hits3
         << G4endl;


  G4double ranEn3      =G4double(fTotEP3)/n_evt;
  G4double ranEn3_2    =G4double(fTotEP3_2)/n_evt;

  G4double rms_ranEn3  =ranEn3_2 - ranEn3 * ranEn3;
  if(rms_ranEn3 >0.)
    rms_ranEn3 = std::sqrt(rms_ranEn3/n_evt);
  else
    rms_ranEn3 = 0.;
  G4cout << "Energy Deposition in PMT with a wavelength in the range of 565 nm to 590 nm per event:\t " << ranEn3/eV  << " eV "<<  " +- " << rms_ranEn3/eV
         << " eV " << G4endl;

  

  G4double  avgranEn3;

  if(Hits3 >0)
      avgranEn3 = ranEn3/Hits3;
  else
      avgranEn3 = 0.;

  G4cout << "Average Energy per Photon in range 565 nm to 590 nm:\t" << avgranEn3/eV << " eV" << G4endl;

  //-----------------------------------------------------------------------------------------------------------------
 G4cout << G4endl;
  
  G4double Hits4     = G4double(fHitC4) / n_evt;
  G4double Hits4_2   = G4double(fHitC4_2) / n_evt;
  G4double rms_Hits4 = Hits4_2 - Hits4 * Hits4;
  if(rms_Hits4 > 0.)
    rms_Hits4 = std::sqrt(rms_Hits4 / n_evt);
  else
    rms_Hits4 = 0.;
  G4cout << "Number of hits per event with a wavelength in the range of 520 nm to 565 nm:\t " << Hits4 << " +- " << rms_Hits4
         << G4endl;


  G4double ranEn4      =G4double(fTotEP4)/n_evt;
  G4double ranEn4_2    =G4double(fTotEP4_2)/n_evt;

  G4double rms_ranEn4  =ranEn4_2 - ranEn4 * ranEn4;
  if(rms_ranEn4 >0.)
    rms_ranEn4 = std::sqrt(rms_ranEn4/n_evt);
  else
    rms_ranEn4 = 0.;
  G4cout << "Energy Deposition in PMT with a wavelength in the range of 520 nm to 565 nm per event:\t " << ranEn4/eV  << " eV "<<  " +- " << rms_ranEn4/eV
         << " eV " << G4endl;

  

  G4double  avgranEn4;

  if(Hits4 >0)
      avgranEn4 = ranEn4/Hits4;
  else
      avgranEn4 = 0.;

  G4cout << "Average Energy per Photon in range 520 nm to 565 nm:\t" << avgranEn4/eV << " eV" << G4endl;

  //-------------------------------------------------------------------------------------------------------------------
  G4cout << G4endl; 
  
  
  G4double Hits5     = G4double(fHitC5) / n_evt;
  G4double Hits5_2    = G4double(fHitC5_2) / n_evt;
  G4double rms_Hits5 = Hits5_2 - Hits5 * Hits5;
  if(rms_Hits5 > 0.)
    rms_Hits5 = std::sqrt(rms_Hits5 / n_evt);
  else
    rms_Hits5 = 0.;
  G4cout << "Number of hits per event with a wavelength in the range of 500 nm to 520 nm:\t " << Hits5 << " +- " << rms_Hits5
         << G4endl;


  G4double ranEn5      =G4double(fTotEP5)/n_evt;
  G4double ranEn5_2    =G4double(fTotEP5_2)/n_evt;

  G4double rms_ranEn5  =ranEn5_2 - ranEn5 * ranEn5;
  if(rms_ranEn5 >0.)
    rms_ranEn5 = std::sqrt(rms_ranEn5/n_evt);
  else
    rms_ranEn5 = 0.;
  G4cout << "Energy Deposition in PMT with a wavelength in the range of 500 nm to 520 nm per event:\t " << ranEn5/eV  << " eV "<<  " +- " << rms_ranEn5/eV
         << " eV " << G4endl;

  

  G4double  avgranEn5;

  if(Hits5 >0)
      avgranEn5 = ranEn5/Hits5;
  else
      avgranEn5 = 0.;

  G4cout << "Average Energy per Photon in range 500 nm to 520 nm:\t" << avgranEn5/eV << " eV" << G4endl;

  //--------------------------------------------------------------------------------------------------------------------
  G4cout << G4endl; 
  
  G4double Hits6     = G4double(fHitC6) / n_evt;
  G4double Hits6_2    = G4double(fHitC6_2) / n_evt;
  G4double rms_Hits6 = Hits6_2 - Hits6 * Hits6;
  if(rms_Hits6 > 0.)
    rms_Hits6 = std::sqrt(rms_Hits6 / n_evt);
  else
    rms_Hits6 = 0.;
  G4cout << "Number of hits per event with a wavelength in the range of 435 nm to 500 nm:\t " << Hits6 << " +- " << rms_Hits6
         << G4endl;


  G4double ranEn6      =G4double(fTotEP6)/n_evt;
  G4double ranEn6_2    =G4double(fTotEP6_2)/n_evt;

  G4double rms_ranEn6  =ranEn6_2 - ranEn6 * ranEn6;
  if(rms_ranEn6 >0.)
    rms_ranEn6 = std::sqrt(rms_ranEn6/n_evt);
  else
    rms_ranEn6 = 0.;
  G4cout << "Energy Deposition in PMT with a wavelength in the range of 435 nm to 500 nm per event:\t " << ranEn6/eV  << " eV "<<  " +- " << rms_ranEn6/eV
         << " eV " << G4endl;

  

  G4double  avgranEn6;

  if(Hits6 >0)
      avgranEn6 = ranEn6/Hits6;
  else
      avgranEn6 = 0.;

  G4cout << "Average Energy per Photon in range 435 nm to 500 nm:\t" << avgranEn6/eV << " eV" << G4endl;

  //---------------------------------------------------------------------------------------------------------------
  G4cout << G4endl; 
  

  G4double Hits7     = G4double(fHitC7)/ n_evt;
  G4double Hits7_2    = G4double(fHitC7_2) / n_evt;
  G4double rms_Hits7 = Hits7_2 - Hits7 * Hits7;
  if(rms_Hits7 > 0.)
    rms_Hits7 = std::sqrt(rms_Hits7 / n_evt);
  else
    rms_Hits7 = 0.;
  G4cout << "Number of hits per event with a wavelength in the range of 380 nm to 435 nm:\t " << Hits7 << " +- " << rms_Hits7
         << G4endl;


  G4double ranEn7      =G4double(fTotEP7)/n_evt;
  G4double ranEn7_2    =G4double(fTotEP7_2)/n_evt;

  G4double rms_ranEn7  =ranEn7_2 - ranEn7 * ranEn7;
  if(rms_ranEn7 >0.)
    rms_ranEn7 = std::sqrt(rms_ranEn7/n_evt);
  else
    rms_ranEn7 = 0.;
  G4cout << "Energy Deposition in PMT with a wavelength in the range of 380 nm to 435 nm per event:\t " << ranEn7/eV  << " eV "<<  " +- " << rms_ranEn7/eV
         << " eV " << G4endl;

  

  G4double  avgranEn7;

  if(Hits7 >0)
      avgranEn7 = ranEn7/Hits7;
  else
      avgranEn7 = 0.;

  G4cout << "Average Energy per Photon in range of 380 nm to 435 nm:\t" << avgranEn7/eV << " eV" << G4endl;

  //----------------------------------------------------------------------------------------------------------------
  G4cout << G4endl; 
  

  G4double Hits8     = G4double(fHitC8)/ n_evt;
  G4double Hits8_2    = G4double(fHitC8_2) / n_evt;
  G4double rms_Hits8 = Hits8_2 - Hits8 * Hits8;
  if(rms_Hits8 > 0.)
    rms_Hits8 = std::sqrt(rms_Hits8 / n_evt);
  else
    rms_Hits8 = 0.;
  G4cout << "Number of hits per event with a wavelength less than 380 nm:\t " << Hits8 << " +- " << rms_Hits8
         << G4endl;


  G4double ranEn8      =G4double(fTotEP8)/n_evt;
  G4double ranEn8_2    =G4double(fTotEP8_2)/n_evt;

  G4double rms_ranEn8  =ranEn8_2 - ranEn8 * ranEn8;
  if(rms_ranEn8 >0.)
    rms_ranEn8 = std::sqrt(rms_ranEn8/n_evt);
  else
    rms_ranEn8 = 0.;
  G4cout << "Energy Deposition in PMT with a wavelength less than 380 nm per event:\t " << ranEn8/eV  << " eV "<<  " +- " << rms_ranEn8/eV
         << " eV " << G4endl;

  

  G4double  avgranEn8;

  if(Hits8 >0)
      avgranEn8 = ranEn8/Hits8;
  else
      avgranEn8 = 0.;

  G4cout << "Average Energy per Photon with a wavelength less than 380 nm:\t" << avgranEn8/eV << " eV" << G4endl;

  //----------------------------------------------------------------------------------------------------------------------
  G4cout << G4endl; 
  /*

  G4double Hits9     = G4double(fHitC9)/ n_evt;
  G4double Hits9_2    = G4double(fHitC9_2) / n_evt;
  G4double rms_Hits9 = Hits9_2 - Hits9* Hits9;
  if(rms_Hits9 > 0.)
    rms_Hits9 = std::sqrt(rms_Hits9 / n_evt);
  else
    rms_Hits9 = 0.;
  G4cout << "Number of hits per event in the range of 430 nm to 449 nm:\t " << Hits9 << " +- " << rms_Hits9
         << G4endl;


  G4double ranEn9      =G4double(fTotEP9)/n_evt;
  G4double ranEn9_2    =G4double(fTotEP9_2)/n_evt;

  G4double rms_ranEn9  =ranEn9_2 - ranEn9 * ranEn9;
  if(rms_ranEn9 >0.)
    rms_ranEn9 = std::sqrt(rms_ranEn9/n_evt);
  else
    rms_ranEn9 = 0.;
  G4cout << "Energy Deposition in PMT in range 430 nm to 449 nm per event:\t " << ranEn9/eV  << " eV "<<  " +- " << rms_ranEn9/eV
         << " eV " << G4endl;

  

  G4double  avgranEn9;

  if(Hits9 >0)
      avgranEn9 = ranEn9/Hits9;
  else
      avgranEn9 = 0.;

  G4cout << "Average Energy per Photon in range 430 nm to 449 nm:\t" << avgranEn9/eV << " eV" << G4endl;

  //----------------------------------------------------------------------------------------------------------------------
  G4cout << G4endl; 

  
  G4double Hits10    = G4double(fHitC10)/ n_evt;
  G4double Hits10_2    = G4double(fHitC10_2) / n_evt;
  G4double rms_Hits10 = Hits10_2 - Hits10* Hits10;
  if(rms_Hits10 > 0.)
    rms_Hits10 = std::sqrt(rms_Hits10 / n_evt);
  else
    rms_Hits10 = 0.;
  G4cout << "Number of hits per event in the range of 410 nm to 429 nm:\t " << Hits10 << " +- " << rms_Hits10
         << G4endl;


  G4double ranEn10      =G4double(fTotEP10)/n_evt;
  G4double ranEn10_2    =G4double(fTotEP10_2)/n_evt;

  G4double rms_ranEn10  =ranEn10_2 - ranEn10 * ranEn10;
  if(rms_ranEn10 >0.)
    rms_ranEn10 = std::sqrt(rms_ranEn10/n_evt);
  else
    rms_ranEn10 = 0.;
  G4cout << "Energy Deposition in PMT in range 410 nm to 429 nm per event:\t " << ranEn10/eV  << " eV "<<  " +- " << rms_ranEn10/eV
         << " eV " << G4endl;

  

  G4double  avgranEn10;

  if(Hits10 >0)
      avgranEn10 = ranEn10/Hits10;
  else
      avgranEn10 = 0.;

  G4cout << "Average Energy per Photon in range 410 nm to 429 nm:\t" << avgranEn10/eV << " eV" << G4endl;

  //----------------------------------------------------------------------------------------------------------------------
  G4cout << G4endl; 


  G4double Hits11    = G4double(fHitC11)/ n_evt;
  G4double Hits11_2    = G4double(fHitC11_2) / n_evt;
  G4double rms_Hits11 = Hits11_2 - Hits11* Hits11;
  if(rms_Hits11 > 0.)
    rms_Hits11 = std::sqrt(rms_Hits11 / n_evt);
  else
    rms_Hits11 = 0.;
  G4cout << "Number of hits per event in the range of 390 nm to 409 nm:\t " << Hits11 << " +- " << rms_Hits11
         << G4endl;


  G4double ranEn11      =G4double(fTotEP11)/n_evt;
  G4double ranEn11_2    =G4double(fTotEP11_2)/n_evt;

  G4double rms_ranEn11  =ranEn11_2 - ranEn11 * ranEn11;
  if(rms_ranEn11 >0.)
    rms_ranEn11 = std::sqrt(rms_ranEn11/n_evt);
  else
    rms_ranEn11 = 0.;
  G4cout << "Energy Deposition in PMT in range 390 nm to 409 nm per event:\t " << ranEn11/eV  << " eV "<<  " +- " << rms_ranEn11/eV
         << " eV " << G4endl;

  

  G4double  avgranEn11;

  if(Hits11 >0)
      avgranEn11 = ranEn11/Hits11;
  else
      avgranEn11 = 0.;

  G4cout << "Average Energy per Photon in range 390 nm to 409 nm:\t" << avgranEn11/eV << " eV" << G4endl;

  //----------------------------------------------------------------------------------------------------------------------
  G4cout << G4endl; 
  

  G4double Hits12    = G4double(fHitC12)/ n_evt;
  G4double Hits12_2    = G4double(fHitC12_2) / n_evt;
  G4double rms_Hits12 = Hits12_2 - Hits12* Hits12;
  if(rms_Hits12 > 0.)
    rms_Hits12 = std::sqrt(rms_Hits12 / n_evt);
  else
    rms_Hits12 = 0.;
  G4cout << "Number of hits per event in the range of 370 nm to 389 nm:\t " << Hits12 << " +- " << rms_Hits12
         << G4endl;


  G4double ranEn12      =G4double(fTotEP12)/n_evt;
  G4double ranEn12_2    =G4double(fTotEP12_2)/n_evt;

  G4double rms_ranEn12  =ranEn12_2 - ranEn12 * ranEn12;
  if(rms_ranEn12 >0.)
    rms_ranEn12 = std::sqrt(rms_ranEn12/n_evt);
  else
    rms_ranEn12 = 0.;
  G4cout << "Energy Deposition in PMT in range 370 nm to 389 nm per event:\t " << ranEn12/eV  << " eV "<<  " +- " << rms_ranEn12/eV
         << " eV " << G4endl;

  

  G4double  avgranEn12;

  if(Hits12 >0)
      avgranEn12 = ranEn12/Hits12;
  else
      avgranEn12 = 0.;

  G4cout << "Average Energy per Photon in range 370 nm to 389 nm:\t" << avgranEn12/eV << " eV" << G4endl;

  //----------------------------------------------------------------------------------------------------------------------
  G4cout << G4endl; 
  

  G4double Hits13    = G4double(fHitC13)/ n_evt;
  G4double Hits13_2    = G4double(fHitC13_2) / n_evt;
  G4double rms_Hits13 = Hits13_2 - Hits13* Hits13;
  if(rms_Hits13 > 0.)
    rms_Hits13 = std::sqrt(rms_Hits13 / n_evt);
  else
    rms_Hits13 = 0.;
  G4cout << "Number of hits per event in the range of 350 nm to 369 nm:\t " << Hits13 << " +- " << rms_Hits13
         << G4endl;


  G4double ranEn13      =G4double(fTotEP13)/n_evt;
  G4double ranEn13_2    =G4double(fTotEP13_2)/n_evt;

  G4double rms_ranEn13  =ranEn13_2 - ranEn13 * ranEn13;
  if(rms_ranEn13 >0.)
    rms_ranEn13 = std::sqrt(rms_ranEn13/n_evt);
  else
    rms_ranEn13 = 0.;
  G4cout << "Energy Deposition in PMT in range 350 nm to 369 nm per event:\t " << ranEn13/eV  << " eV "<<  " +- " << rms_ranEn13/eV
         << " eV " << G4endl;

  

  G4double  avgranEn13;

  if(Hits13 >0)
      avgranEn13 = ranEn13/Hits13;
  else
      avgranEn13 = 0.;

  G4cout << "Average Energy per Photon in range 350 nm to 369 nm:\t" << avgranEn13/eV << " eV" << G4endl;

  //----------------------------------------------------------------------------------------------------------------------
  G4cout << G4endl; 


  G4double Hits14    = G4double(fHitC14)/ n_evt;
  G4double Hits14_2    = G4double(fHitC14_2) / n_evt;
  G4double rms_Hits14 = Hits14_2 - Hits14* Hits14;
  if(rms_Hits14 > 0.)
    rms_Hits14 = std::sqrt(rms_Hits14 / n_evt);
  else
    rms_Hits14 = 0.;
  G4cout << "Number of hits per event in the range of 330 nm to 349 nm:\t " << Hits14 << " +- " << rms_Hits14
         << G4endl;


  G4double ranEn14      =G4double(fTotEP14)/n_evt;
  G4double ranEn14_2    =G4double(fTotEP14_2)/n_evt;

  G4double rms_ranEn14  =ranEn14_2 - ranEn14 * ranEn14;
  if(rms_ranEn14 >0.)
    rms_ranEn14 = std::sqrt(rms_ranEn14/n_evt);
  else
    rms_ranEn14 = 0.;
  G4cout << "Energy Deposition in PMT in range 330 nm to 349 nm per event:\t " << ranEn14/eV  << " eV "<<  " +- " << rms_ranEn14/eV
         << " eV " << G4endl;

  

  G4double  avgranEn14;

  if(Hits14 >0)
      avgranEn14 = ranEn14/Hits14;
  else
      avgranEn14 = 0.;

  G4cout << "Average Energy per Photon in range 330 nm to 349 nm:\t" << avgranEn14/eV << " eV" << G4endl;

  //----------------------------------------------------------------------------------------------------------------------
  G4cout << G4endl; 
  

  G4double Hits15    = G4double(fHitC15)/ n_evt;
  G4double Hits15_2    = G4double(fHitC15_2) / n_evt;
  G4double rms_Hits15 = Hits15_2 - Hits15* Hits15;
  if(rms_Hits15 > 0.)
    rms_Hits15 = std::sqrt(rms_Hits15 / n_evt);
  else
    rms_Hits15 = 0.;
  G4cout << "Number of hits per event in the range of 310 nm to 329 nm:\t " << Hits15 << " +- " << rms_Hits15
         << G4endl;


  G4double ranEn15      =G4double(fTotEP15)/n_evt;
  G4double ranEn15_2    =G4double(fTotEP15_2)/n_evt;

  G4double rms_ranEn15  =ranEn15_2 - ranEn15 * ranEn15;
  if(rms_ranEn15 >0.)
    rms_ranEn15 = std::sqrt(rms_ranEn15/n_evt);
  else
    rms_ranEn15 = 0.;
  G4cout << "Energy Deposition in PMT in range 310 nm to 329 nm per event:\t " << ranEn15/eV  << " eV "<<  " +- " << rms_ranEn15/eV
         << " eV " << G4endl;

  

  G4double  avgranEn15;

  if(Hits15 >0)
      avgranEn15 = ranEn15/Hits15;
  else
      avgranEn15 = 0.;

  G4cout << "Average Energy per Photon in range 310 nm to 329 nm:\t" << avgranEn15/eV << " eV" << G4endl;

  //----------------------------------------------------------------------------------------------------------------------
  G4cout << G4endl; 
  

  G4double Hits16    = G4double(fHitC16/ n_evt);
  G4double Hits16_2    = G4double(fHitC16_2) / n_evt;
  G4double rms_Hits16 = Hits16_2 - Hits16* Hits16;
  if(rms_Hits16 > 0.)
    rms_Hits16 = std::sqrt(rms_Hits16 / n_evt);
  else
    rms_Hits16 = 0.;
  G4cout << "Number of hits per event in the range of less than 309 nm:\t " << Hits16 << " +- " << rms_Hits16
         << G4endl;


  G4double ranEn16      =G4double(fTotEP16)/n_evt;
  G4double ranEn16_2    =G4double(fTotEP16_2)/n_evt;

  G4double rms_ranEn16  =ranEn16_2 - ranEn16 * ranEn16;
  if(rms_ranEn16 >0.)
    rms_ranEn16 = std::sqrt(rms_ranEn16/n_evt);
  else
    rms_ranEn16 = 0.;
  G4cout << "Energy Deposition in PMT in range less than 309 nm per event:\t " << ranEn16/eV  << " eV "<<  " +- " << rms_ranEn16/eV
         << " eV " << G4endl;

  

  G4double  avgranEn16;

  if(Hits16 >0)
      avgranEn16 = ranEn16/Hits16;
  else
      avgranEn16 = 0.;

  G4cout << "Average Energy per Photon in range less than 309 nm:\t" << avgranEn16/eV << " eV" << G4endl;

  //----------------------------------------------------------------------------------------------------------------------
  */

















  
  
    







  

 



  G4cout << G4endl;

  G4cout.precision(prec);
}
