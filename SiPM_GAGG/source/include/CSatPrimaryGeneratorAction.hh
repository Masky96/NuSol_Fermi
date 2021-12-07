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
/// \file optical/CSat/include/CSatPrimaryGeneratorAction.hh
/// \brief Definition of the CSatPrimaryGeneratorAction class
//
//
#ifndef CSatPrimaryGeneratorAction_h
#define CSatPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ThreeVector.hh"
#include "globals.hh"
#include "CSatDataStructures.hh"
#include "CSatShowerGenerator.hh"
#include "G4ParticleGun.hh"
#include "CSatRunAction.hh"
#include <vector>
#include <fstream>
#include <mutex>
#include "G4UserRunAction.hh"


class G4GeneralParticleSource;
class G4ParticleGun;
class G4Event;
class CSatShowerGenerator;

//class CSatPrimaryGeneratorMessenger;

  class CSatPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
  {
  public:
    CSatPrimaryGeneratorAction();
    ~CSatPrimaryGeneratorAction();

    void GeneratePrimaries(G4Event* anEvent) override;

    /**
     * @brief 
     *  generate primary particles for transport
     *
     * @param G4Event*
     */
    void SetOptPhotonPolar(G4double);

    /**
     * @brief 
     *  return primary particle kinetic energy (MeV)
     *
     * @return G4double
     */
    G4double GetEnergyPrimary()   {return energyPri;};

    /**
     * @brief 
     *  return primary particle position
     *
     * @param G4ThreeVector
     */
    G4ThreeVector GetPositionPrimary()   {return position;};

    /**
     * @brief 
     *  return primary particle direction
     *
     * @param G4ThreeVector
     */
    G4ThreeVector GetDirectionPrimary()   {return direction;};

    /**
     * @brief 
     *  return primary particle name
     *
     * @param G4String
     */
    G4String GetParticleName() { return particleName;};

    /**
     * @brief 
     *  return translation vector which hits or nearly hits the detector volume
     *  with given shower
     *
     * @param G4String
     */
    G4ThreeVector TranslationToHit(User::event);

    /* private:

       G4GeneralParticleSource* particleGun;*/
    
    /*
  long int FileLength(){
    long int len = 0;
    std::ifstream myfile("shower100K.out");
    std::string myline;
    while ( std::getline(myfile, myline) ) {
      len++;
      if(len % 5000 == 0){
	G4cout << "File length is " << len << '\n';
      }
    }
    myfile.close();
    return len;
  }

  // Vector to hold the showers we run
    std::vector< std::vector< User::event* >* > showers = CSatShowerGenerator::GenerateShower();
    */
  

  private:
    G4GeneralParticleSource* particleGun;
  
    G4ParticleGun* fparticleGun;
    // CSatPrimaryGeneratorMessenger* gunMessenger;
    G4double energyPri;
    G4ThreeVector position;
    G4ThreeVector direction;
    G4String particleName;
  
    // mutually exclusive to make showers share the total number
    static std::mutex showerShackle;
    // int to hold number of total showers
    static G4int nShowers;
  };


#endif
