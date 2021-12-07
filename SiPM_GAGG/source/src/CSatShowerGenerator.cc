//  File for generating a series of cosmic ray showers.
//  Opens a file containing the showers and then outputs
//  a vector containing the 
//
/// \file optical/CSat/src/CSatShowerGeneratorn.cc
/// \brief Implementation of the CSatRunAction class
//
//

#include "CSatShowerGenerator.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


void CSatShowerGenerator::GenerateShower(std::vector< std::vector< User::event* >* > *showers){
  // Start of shower generation
  
  G4cout << "File length is " << CSatShowerGenerator::FileLength() << '\n';
  const long int arrayLen = CSatShowerGenerator::FileLength();
  auto ShowerArray = new G4double [arrayLen][10];
 
  //std::ifstream file("/home/bdoty/Desktop/VetoTestStand-Custom-GPS/build/shower10000.out");// Very explicit
  std::ifstream file("10MShower_1258-76sec_5mx5m.out");// not explicit; checks where the executable is
  //G4cout << "mark 1\n";
  std::string thisLine;
  std::getline(file, thisLine);// skip first line of shower which has nonsense
  for(int row = 0; row < arrayLen; ++row)
    {
      std::getline(file, thisLine);
      if ( !file.good() )
	break;
      thisLine.append(",");
      std::stringstream iss(thisLine);
      
      for (int col = 0; col < 10; ++col)
        {
	  
	  std::string val;
	  std::getline(iss, val, ',');
	  
	  if ( !iss.good() )
	    break;
	  
	  //std::stringstream convertor(val);
	  double toConvert = stod(val);
	  G4double converted = toConvert;
	  //if( (row % 1000 == 0) && (col % 10 == 0))
	    //G4cout << "the value is: " << val <<'\n';
	  ShowerArray[row][col] = converted;
	  
        } // end for
    }// end for
  //G4cout << "mark 2\n";

  
  // make an array of stuff to shoot
  // something in her e breaks stuff
  //G4cout << "I get here.\n";
  //std::vector< std::vector<User::event*>* > theseShowers;

  G4int nEventID = 0;
  G4int ShowerNumber = 0;
  G4int line = 0;
   

  std::vector< User::event* > *thisShower = new std::vector< User::event* >; // used in both loops
  //G4cout << "Help me please "  << '\n';
    
  //G4cout << "File length is " << FileLength << '\n';

  for(int k = 1 ; k < arrayLen; ++k){
    //G4cout << "for loop is on element " << k << '\n';
    //for(int k = 1 ; k < 9999; ++k){
    //This part decides whether or not to add this particle to the same shower
    if(ShowerNumber != ShowerArray[k][0]){
      ShowerNumber = ShowerArray[k][0];   //update shower number
      showers->vector::push_back(thisShower);  //push shower to showers array
      thisShower =  new std::vector< User::event* >; //reinitialize shower
    }

    User::event *a = new User::event;
    G4String *placeholder = new G4String;
    if(ShowerArray[k][2] == 0){placeholder -> append("neutron");}
    if(ShowerArray[k][2] == 1){placeholder -> append("proton");}
    if(ShowerArray[k][2] == 2){placeholder -> append("pi-");}
    if(ShowerArray[k][2] == 3){placeholder -> append("kaon0");}
    if(ShowerArray[k][2] == 4){placeholder -> append("mu-");}
    if(ShowerArray[k][2] == 5){placeholder -> append("e-");}
    if(ShowerArray[k][2] == 6){placeholder -> append("gamma");}
    a->particleType = placeholder;
    //	G4cout << a->particleType;
	
    G4ThreeVector *thisPos = new G4ThreeVector(ShowerArray[k][4]*CLHEP::m,ShowerArray[k][5]*CLHEP::m,0.90*CLHEP::m);
    a->position = thisPos;
    G4ThreeVector *thisMom = new G4ThreeVector(ShowerArray[k][7],ShowerArray[k][8],ShowerArray[k][9]);
    a->momentum = thisMom;
    //G4double *thisEner = new G4double(ShowerArray[k][3]*CLHEP::keV);
    //G4double *thisEner = new G4double(42069);
    G4double *thisEner = new G4double(ShowerArray[k][3]*CLHEP::keV);
    a->energy = thisEner;
    //G4cout << "energy = " << (a->energy) << ".\n";
	


	 
    thisShower->vector::push_back(a);
    //G4cout << "thisShower is empty: " << (thisShower -> empty() ) << ".\n";
    //delete a;
    //delete placeholder;
    //showers[i][j] = 1;
    //showers[i][j] = a;
  }
  showers->vector::push_back(thisShower);// put last shower in
  //showers -> vector::pop_back();
  //showers -> vector::push_back(thisShower);
   
    
    
    
  //G4cout << showers;

  // Clean up and return
  //std::vector< std::vector< User::event* >* > theReturn (theseShowers.begin(), theseShowers.end() );
  G4cout << "The Number of showers is " << showers->size() << "\n";
  // Return the Return
  //G4cout << "theReturn[0] is empty: " << ( (*theReturn)[0] -> empty() ) << ".\n";
  //G4cout << "theseShowers[0] is empty: " << (theseShowers[0] -> empty() ) << ".\n";
  //G4cout << "thisShower is empty: " << (thisShower -> empty() ) << ".\n";
  //return theReturn;
  


  /*
  // working electron test
  // make an array of stuff to shoot
  G4cout << "I get here.\n"; // it's printing random hex codes somewhere below
  //std::vector< std::vector<User::event*>* > theseShowers;

  for(G4int i = 1; i<11; i++){
  std::vector< User::event* > *thisShower = new std::vector< User::event* >(1); // used in both loops
  thisShower -> pop_back();
  for(G4int j = 0; j < i; j++){
  User::event *a = new User::event;
  G4String *placeholder = new G4String;
  placeholder -> append("e-");
  a->particleType = placeholder;
  //G4cout << *(a->particleType);
	
  G4ThreeVector *thisPos = new G4ThreeVector(0,0,1*CLHEP::m);
  a->position = thisPos;
  G4ThreeVector *thisMom = new G4ThreeVector(0,0,-1);
  a->momentum = thisMom;
  G4double *thisEner = new G4double(10*CLHEP::MeV);
  a->energy = thisEner;
  thisShower->vector::push_back(a);
  //showers[i][j] = 1;
  //showers[i][j] = a;
  }
  std::vector< User::event* > *pushShower = new std::vector< User::event* >(thisShower->begin(),thisShower->end());
  //G4cout << "Hexbreaker\n";
  showers->vector::push_back(pushShower);
  //showers -> vector::pop_back();
  //showers -> vector::push_back(thisShower);
  }
    
    
    
  //G4cout << showers;

  // Clean up and return
  //std::vector< std::vector< User::event* >* >* theReturn = new std::vector< std::vector< User::event* >* >(theseShowers.begin(), theseShowers.end() );
  // Return the Return
  G4cout << "And then I get here \n.";
  //return theseShowers;//theReturn;
  */
}
