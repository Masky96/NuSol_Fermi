#ifndef CSatDataStructures_h
#define CSatDataStructures_h 1

namespace User{
  
    struct event{
      G4String *particleType = new G4String[7];// no strink will be more than 7 long
      G4ThreeVector *position = new G4ThreeVector;
      G4ThreeVector *momentum = new G4ThreeVector;
      G4double *energy = new G4double(-1);
    };
}




#endif /*CSatDataStructures_h*/
