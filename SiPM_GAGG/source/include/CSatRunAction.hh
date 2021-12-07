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
/// \file optical/CSat/include/CSatRunAction.hh
/// \brief Definition of the CSatRunAction class
//
//
#include "G4UserRunAction.hh"
#include "G4ThreeVector.hh"
#include "G4Types.hh"
#include <vector>
#include <fstream>
#include <mutex>
#include "CSatDataStructures.hh"
#include "CSatShowerGenerator.hh"

#ifndef CSatRunAction_h
#  define CSatRunAction_h 1

class CSatRun;
class CSatHistoManager;
class CSatShowerGenerator;

class G4Run;

class CSatRunAction : public G4UserRunAction
{
 public:
  CSatRunAction();
  ~CSatRunAction();

  G4Run* GenerateRun() override;
  void BeginOfRunAction(const G4Run*) override;
  void EndOfRunAction(const G4Run*) override;

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
  static std::vector< std::vector< User::event* >* > *showers;
  /*
    void somefunction(){
    G4cout << "I here\n";
    User::event* dummyEvent = new User::event;
    std::vector< User::event* > *dummyShower = new std::vector< User::event* >{dummyEvent};
    std::vector< std::vector< User::event* >* > dummyShowers = {dummyShower};
    //CSatShowerGenerator::GenerateShower();
    //{dummyShower};
    *showers = {};
    }
  */

  //= new std::vector< std::vector< User::event* >* >{CSatShowerGenerator::GenerateShower().begin(),CSatShowerGenerator::GenerateShower().end()};
  
  
 private:
  CSatRun* fRun;
  CSatHistoManager* fHistoManager;
};

#endif
