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
#ifndef CSatShowerGenerator_h
#define CSatShowerGenerator_h 1

#include "G4UserRunAction.hh"
#include "G4ThreeVector.hh"
#include "globals.hh"
#include "G4ParticleGun.hh"
//#include "CSatRunAction.hh"
#include <vector>
#include <fstream>
#include "CSatDataStructures.hh"
#include "CSatShowerGenerator.hh"
#include "CSatRunAction.hh"


class G4GeneralParticleSource;
class G4ParticleGun;
class G4Event;

//class CSatPrimaryGeneratorMessenger;

class CSatShowerGenerator : public G4UserRunAction
{
public:
  CSatShowerGenerator();
  ~CSatShowerGenerator();

  //static std::vector< std::vector< User::event* >* > GenerateShower();
  static void GenerateShower(std::vector< std::vector< User::event* >* > *showers);

  static const long int FileLength(){
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

};


#endif
