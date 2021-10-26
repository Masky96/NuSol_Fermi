/*
Dr. Robert McTaggart
South Dakota State University
Fall 2018

This is the routine that fires the initial particles ,
or uses information from particles fired by /gps in a macro
and performs kinematics (if necessary)

 */

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4Event.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleGun.hh"
#include "Randomize.hh"

#include "G4DecayPhysics.hh"
#include "G4IonTable.hh"
#include "G4ParticlePropertyData.hh"
#include "G4NuclearDecay.hh"

#include "NuSolarPrimaryGeneratorAction.hh"
#include "PrimaryGeneratorMessenger.hh"
#include "globals.hh"

#include "G4RunManager.hh"

namespace User{

  NuSolarPrimaryGeneratorAction::NuSolarPrimaryGeneratorAction()
  {
    particleGun = new G4GeneralParticleSource();

    //create a messenger for this class
    gunMessenger = new PrimaryGeneratorMessenger(this);
    

    //default kinematic
   
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* particle = particleTable->FindParticle("mu-");

    particleGun->SetParticleDefinition(particle);
    particleGun->SetParticleTime(0.0*ns);

    //create a new Particle Gun that will steal the randomized location of the
    //first particle gun, and use its energy from said gps for the decay products

    G4int n_particle=1;
    fparticleGun = new G4ParticleGun(n_particle);

    energyPri=0;


  }

  NuSolarPrimaryGeneratorAction::~NuSolarPrimaryGeneratorAction()
  {
    delete particleGun;
    delete gunMessenger;
    delete fparticleGun;
  }

  std::vector< std::vector< event* >* >* NuSolarPrimaryGeneratorAction::GenerateShower(){
    //read in shower data

    long int FileLength = 0;
    
      std::ifstream myfile("shower100K.out");
      std::string myline;
      
      
      while ( std::getline(myfile, myline) ) {
	FileLength++;
	if(FileLength % 1900 == 0){
	  //G4cout << "File length is " << FileLength << '\n';
	}
      }
      
      //G4cout << "closing file\n";
      myfile.close();
    
    


    
    G4double ShowerArray[FileLength][10];
    //G4double ShowerArray[10000][10];
    //std::ifstream file("/home/bdoty/Desktop/VetoTestStand-Custom-GPS/build/shower10000.out");// Very explicit
    std::ifstream file("shower100K.out");// not explicit; checks where the executable is
    // G4cout << "mark 1\n";
    for(int row = 0; row < FileLength + 1; ++row)
      //for(int row = 0; row < 9999; ++row)


{
        std::string line;
        std::getline(file, line);
        if ( !file.good() )
            break;
	line.append(",");
        std::stringstream iss(line);

        for (int col = 0; col <= 10; ++col)
        {
            std::string val;
            std::getline(iss, val, ',');
            if ( !iss.good() )
                break;

            std::stringstream convertor(val);
            convertor >> ShowerArray[row][col];
        }
    }
    //G4cout << "mark 2\n";



    // make an array of stuff to shoot
    // something in her e breaks stuff
    //G4cout << "I get here.\n";
    std::vector< std::vector<event*>* > theseShowers;

    G4int nEventID = 0;
    G4int ShowerNumber = 0;
    G4int line = 0;
   

    std::vector< event* > *thisShower = new std::vector< event* >; // used in both loops
    //G4cout << "Help me please "  << '\n';
    
    //G4cout << "File length is " << FileLength << '\n';

      for(int k = 1 ; k < FileLength; ++k){
	//G4cout << "for loop is on element " << k << '\n';
      //for(int k = 1 ; k < 9999; ++k){
	//This part decides whether or not to add this particle to the same shower
	if(ShowerNumber != ShowerArray[k][0]){
	  ShowerNumber = ShowerArray[k][0];   //update shower number
	  theseShowers.vector::push_back(thisShower);  //push shower to showers array
	  thisShower =  new std::vector< event* >; //reinitialize shower
	}

	event *a = new event;
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
	
	G4ThreeVector *thisPos = new G4ThreeVector(ShowerArray[k][4]*m,ShowerArray[k][5]*m,0.90*m);
	a->position = thisPos;
	G4ThreeVector *thisMom = new G4ThreeVector(ShowerArray[k][7],ShowerArray[k][8],ShowerArray[k][9]);
	a->momentum = thisMom;
	//G4double *thisEner = new G4double(ShowerArray[k][3]*keV);
	//G4double *thisEner = new G4double(42069);
	G4double *thisEner = new G4double(ShowerArray[k][3]*keV);
	a->energy = thisEner;
	//G4cout << "energy = " << (a->energy) << ".\n";
	


	 
	thisShower->vector::push_back(a);
	//G4cout << "thisShower is empty: " << (thisShower -> empty() ) << ".\n";
	//delete a;
	//delete placeholder;
	//showers[i][j] = 1;
	//showers[i][j] = a;
      }
      theseShowers.vector::push_back(thisShower);// put last shower in
      //showers -> vector::pop_back();
      //showers -> vector::push_back(thisShower);
   
    
    
    
    //G4cout << showers;

    // Clean up and return
    std::vector< std::vector< event* >* >* theReturn = new std::vector< std::vector< event* >* >(theseShowers.begin(), theseShowers.end() );
    G4cout << "The Number of showers is " << theReturn -> size() << "\n";
    // Return the Return
    //G4cout << "theReturn[0] is empty: " << ( (*theReturn)[0] -> empty() ) << ".\n";
    //G4cout << "theseShowers[0] is empty: " << (theseShowers[0] -> empty() ) << ".\n";
    //G4cout << "thisShower is empty: " << (thisShower -> empty() ) << ".\n";
    return theReturn;

  }


  void NuSolarPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
  {

    //The variable neutrinoprocess controls whether we are studying the background (neutrinoprocess=0)
    //    or
    // neutrino + 69Ga --> m69Ge + e- ; 
    //                     m69Ge --> 69Ge + gamma

    //   or
    // neutrino + 71Ga --> m71Ge + e- ;
    //                     m71Ge --> 71Ge + gamma

    //Note that the germanium state CAN be the ground state (no gamma)

    //For neutrino studies we select the detector as a volume source and choose the neutrino
    //energy in phys.mac.  That will randomize the location of the neutrino event.
    //The initial neutrino momentum will be in the +z direction from the sun.

    //Neutrino runs steal this energy and the location generated by general particle source, 
    //and then fire the particle gun for the by-products of the neutrino event. 
      
    //For pure background analyses, we use the general particle source governed by the macros batch.mac and phys.mac.  
    
    
    G4cout.precision(16);
    
    // particle and ion tables for use
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4IonTable* ionTable = G4IonTable::GetIonTable();
    
    energyPri = 0.;
    //particleGun->GeneratePrimaryVertex(anEvent);
    
    
    //G4cout << "showers[0] is empty: " << ( (*showers)[0] -> empty() ) << ".\n";
    
    // find the number of events so we can loop around if beamOn is too big
    G4int modulus = NuSolarPrimaryGeneratorAction::showers -> size();
    
    

    std::vector<event*> *theShowerCopy = (*NuSolarPrimaryGeneratorAction::showers)[nShowers % modulus];// make a copy of the relevant shower
    nShowers++;// ready for next iteration
    //G4cout << "theShowerCopy is empty: " << ( theShowerCopy -> empty() ) << ".\n";

    event *thisParticle = new event;

    
    // for some reason this 
    //G4cout << "before while loop\n";
    while( !(theShowerCopy -> empty()) ){
      
      thisParticle = theShowerCopy -> back();
      
      //G4cout << "The momentum I'm puttting in is " << *(thisParticle -> momentum) << "\n";
      fparticleGun->SetParticleMomentumDirection( *(thisParticle -> momentum) );
      //G4cout << "The energy I'm puttting in is " << *(thisParticle -> energy) << "\n";
      fparticleGun->SetParticleEnergy( *(thisParticle -> energy) );
      //G4cout << "The position I'm puttting in is " << *(thisParticle -> position) << "\n";
      fparticleGun->SetParticlePosition( *(thisParticle -> position) );
      fparticleGun->SetParticleTime(0.0*ns);
      G4String partName = *(thisParticle -> particleType);
      //G4cout << "The particle I'm running is " << partName << '\n';
      G4ParticleDefinition* theParticle = particleTable -> FindParticle(partName);
      fparticleGun->SetParticleDefinition(theParticle);
      //G4cout << "marker 1 \n";
      
      
      fparticleGun->GeneratePrimaryVertex(anEvent); 
      //G4cout << "marker 2 \n";




      
      theShowerCopy -> pop_back();
      //G4cout << "marker 3 \n";
    }
    //G4cout << "after while loop\n";
    
    


    delete thisParticle;
    
    

    /*



    // get the energy from the first particle gun
    energyPri = particleGun->GetParticleEnergy();
    position=particleGun->GetParticlePosition();
    direction=particleGun->GetParticleMomentumDirection(); 

    G4ThreeVector GunPosition = particleGun->GetParticlePosition();
    // G4int eID;
    // eID = anEvent->GetEventID();
  
    // G4cout << "Event ID is " << eID << G4endl;
    // G4cout << "The Direction is " << direction << G4endl;
    //G4cout << "The Position is " << position << G4endl;


    //Program control
   
    G4int neutrinoprocess = 0;  //0 for cosmic rays, 1 for neutrino events
    G4int galliumprocess = 1;  // 0 for Gallium-69, 1 for Gallium-71
    G4int gammaprocess = 1;  // 69Ge:  0 for ground state, 1 for 87 keV gamma, 2 for 397 keV gamma
                             // 71Ge:  0 for ground state, 1 for 198 keV excited state
                             // 71Ge:  2 is for firing the 174 keV state

    G4int fireparticle = 0; 
    // Normally both are fired (fireparticle = 0)
    // if fireparticle is 0, then fire both particles
    // if fireparticle is 1, then fire the electron only
    // if fireparticle is 2, then fire the excited germanium state only
    //Note that if gammaprocess is 0, we will fire the ground state


    //For background studies, set neutrinoprocess equal to 0 to skip the following
    //but edit phys.mac accordingly

    //    G4double energy1, energy2;
    //    G4double p1x, p1y, p1z, p2x, p2y, p2z;
 

    G4double atomicmassunit = 931.4940954*MeV;
   
    if (neutrinoprocess > 0) {

      // G4cout << "Neutrino Event begins." << G4endl;

      G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
      G4IonTable* ionTable = G4IonTable::GetIonTable();
      G4double excitEnergy= 0. * MeV; //the gamma ray energy
      G4double delay = 0.;            //the half-life of the excited germanium state
      G4double ionCharge = 1.*eplus;  //We go from a neutral gallium to a charged germanium

      //G4double pc1;
      //G4double wx, wy, wz, norm1;
      G4int Z, A;

      //particle and mass refer to either the electron or positron in each of the decays.  
      //The electron is the default.

      //All masses are in MeV

      G4ParticleDefinition* particle = particleTable->FindParticle("e-");
      G4double mass = particle->GetPDGMass();  //the mass of an electron

      // G4cout << "Electron mass is " << mass << G4endl;

      G4ParticleDefinition* photon = particleTable->FindParticle("gamma");

      G4ParticleDefinition* particle0;
      G4ParticleDefinition* particle2;
      G4ParticleDefinition* particle3; 
    
      G4double mass0, massge, massge0;

      // For QA/QC, we sometimes fire only the electron or 
      // the excited germanium state (which will fire a gamma ray)
      // This is easier than trying to track the optical photons from each 
      // particle when the times are very close

      //particle0 and mass0 refer to what the neutrino hits in the lab frame (i.e. the neutrino target)

      Z=31;  

      if (galliumprocess == 0) {
	A = 69;
	mass0 = 68.9255735*atomicmassunit;
      }

      if (galliumprocess == 1) {
	A = 71;
	mass0 = 70.92470258*atomicmassunit;
      }
      
      particle0 = ionTable->GetIon(Z,A,excitEnergy);  //Gallium ground state to be studied

      //mass0 = particle0->GetPDGMass();                //mass of the Gallium target
                                                      //being hit by a neutrino.

      //mass1 is the excited germanium isotope with the same atomic number as the gallium
      Z=32;

      //the defaults for excitEnergy and delay are zero
      //if gammaprocess == 0, then we will fire a ground state germanium isotope

      
      if (galliumprocess == 0) {

	massge0 = 68.9280953 * atomicmassunit;

	//m1 decay for m69Ge
	if (gammaprocess == 1) {
	  
	  excitEnergy = 86.76 * keV;
	  delay = 5100. * ns;
	}

	//m2 decay for m69Ge
	if (gammaprocess == 2) {
	  excitEnergy = 397.94 * keV;
	  delay = 2810. * ns;
	}      

	massge = massge0 + excitEnergy;

      }

      if (galliumprocess == 1) {

	massge0 = 70.92495233 * atomicmassunit;

	//Generate the highest energy m71Ge state
	if (gammaprocess == 1) {
	  excitEnergy = 198.354 * keV;
	  delay = 20.40 * ms;
	 
	}

	//Generate the intermediary 174 keV state
	if (gammaprocess == 2) {
	  excitEnergy = 174.943 * keV;
	  delay = 79 * ns;
	}

	massge = massge0 + excitEnergy;

      }


      G4ParticleDefinition* germanium = ionTable->GetIon(Z,A,excitEnergy); 
      //If this is a Ge-69, it is in excited m1 or m2 state
      //If this is a Ge-71, it is in the m1 excited state

      //Below we deliver a radioactive decay.

      germanium -> SetPDGStable(false);
      germanium -> SetPDGLifeTime(delay);
      
      // G4cout << "Delay for Ge(198 keV) state is " << delay << G4endl;
 
      // G4double massge = germanium->GetPDGMass();
      //G4cout << "particlename is " << germanium->GetParticleName() <<" and  mass is " << massge << G4endl;

     
      //find information for Ge-69 after decay of m69Ge
      //or for Ge-71 after the decay of m71Ge

      excitEnergy = 0.; // ground state of germanium....no excitation energy

      G4ParticleDefinition* germanium0 = ionTable ->GetIon(Z,A,excitEnergy);
      // G4double massge0 = germanium0->GetPDGMass();  
      
      
      if (gammaprocess == 0) {  //we generate the ground state only...no double pulse
	germanium = germanium0;
	massge = massge0;
      }

     
      //neutrino + particle0 (gallium) --> germanium + e- ; 
      //Geant will facilitate germanium --> germanium0 + photon

      //*********************************************

      //Calculate boost quantities to get to the lab frame (common to all cases)

      //Note that the target Gallium is at rest in the lab frame, but the center of mass is not.
      //Decays below will be processed in the center of mass frame, boosted back into the lab frame
      //and then fired in the lab frame

      G4double geta = energyPri + mass0;  //energyPri is the incoming neutrino energy.  mass0 is the target.
      G4double beta = energyPri/geta;  //velocity/c of the center of mass in the lab frame
      G4double gamma = 1. / sqrt(1. - beta*beta);

      //invariant mass of incoming neutrino hitting stationary 69Ga
      G4double invariantmass = sqrt(2.*energyPri*mass0 + mass0*mass0);

      //minimum energy for producing electron and m69Ge
      G4double thresholdenergy = mass + massge; 

      //  G4cout << "Invariantmass is " << invariantmass << " and threshold energy is " << thresholdenergy << G4endl;

      if (thresholdenergy > invariantmass) {
	G4cout << "Energy is below threshold" << G4endl;
	G4cout << "thresholdenergy is " << thresholdenergy << " and invariantmass is " << invariantmass << G4endl;
	G4cout << "required neutrino energy is > " << (thresholdenergy*thresholdenergy - mass0*mass0)/(2.*mass0) << G4endl;
	return;
      }
      
      G4double mass1, mass3;
      G4double mass2;
      G4double mass4;
      G4double mass5;
      G4double pc, energy;
     
      //neutrino + 69Ga --> m_69Ge + e-, m_69Ge --> 69Ge + gamma
      //neutrino + 71Ga --> m_71Ge + e-, m_71Ge --> 71Ge + gamma

      //mass = mass of electron
      mass1 = massge;  //excited state
      mass2 = massge0; //ground state
      mass3 = 0.;      //photon
      particle2 = germanium0;
      particle3 = photon;
     
      //mass1 is the  mass of the m1_69Ge (case 2)
      
      // PC IS THE BACK-TO-BACK MOMENTUM FOR MASS AND MASS1 IN THEIR CENTER OF MASS FRAME

      // G4cout << "RobTest4:  invmass^2 is " << invariantmass*invariantmass << " and massinv is " << (mass + mass1)*(mass + mass1) << G4endl;

      pc = (invariantmass*invariantmass - (mass1 + mass)*(mass1 + mass));
      // if (pc < 0 ) {
      //	G4cout << "RobAlert1: Negative momentum!!!" << " Energy is " << energyPri << G4endl;
      //}
      pc = pc*(invariantmass*invariantmass - (mass1 - mass)*(mass1 - mass));
      pc = sqrt(pc) / (2.*invariantmass);

      //Given the magnitude pc, we randomize components and normalize.
      //for neutrinoprocess = 2, mass is the electron, and mass1 is m1_69Ge or m2_69Ge.
      //These are in the TOTAL center of mass frame of reference

      G4double ux, uy, uz, norm;
      ux = 2.*(G4UniformRand()-0.5);
      uy = 2.*(G4UniformRand()-0.5);
      uz = 2.*(G4UniformRand()-0.5);
      norm = ux*ux + uy*uy + uz*uz;
      norm = sqrt(norm);
      ux = ux/norm;
      uy = uy/norm;
      uz = uz/norm;

      G4double px = pc*ux;
      G4double py = pc*uy;
      G4double pz = pc*uz;
    
      //Boost mass (electron) into the lab frame
      energy = pc * pc + mass * mass;
      energy = sqrt (energy);

      G4double kineticenergy = energy - mass;
     
      // if (kineticenergy < 0 ) { 
      //	G4cout << "RobAlert2: kinetic energy of mass is negative " << kineticenergy << " mass is " << mass << G4endl;
      //}

      //boost the single electron forward to the lab frame.
      G4double energy0 = gamma*energy + gamma*beta*pz;
      pz = gamma*beta*energy + gamma*pz;
    
      mass5 = energy0*energy0 - px*px - py*py - pz*pz;
      mass5 = sqrt(mass5);
      //  Check if mass5 is equal to mass
      //G4cout << "Invariant mass of electron is " << mass5 << G4endl;

      norm = px*px + py*py + pz*pz;
      norm = sqrt(norm);
      px=px/norm;
      py=py/norm;
      pz=pz/norm;

      kineticenergy = energy0 - mass;
      //if (kineticenergy < 0) {
      //	G4cout << "RobAlert3: KE of mass < 0 in the lab frame " << kineticenergy << "Particle is " << particle->GetParticleName()<< G4endl;
      //}

      //SetParticleEnergy sets the kinetic energy
      //SetParticleMomentum requires that the G4ThreeVector is a unit vector
      //Note:  We now are using a second particle gun, fparticleGun, for the neutrino by-products
     
      //Set the characteristics of the electron

      //Fire an ELECTRON with the particle gun if fireparticle is 0 or 1
     
      if (fireparticle != 2) {
	fparticleGun->SetParticleDefinition(particle);
	fparticleGun->SetParticleMomentumDirection(G4ThreeVector(px,py,pz));
	fparticleGun->SetParticleEnergy(kineticenergy);
	fparticleGun->SetParticlePosition(GunPosition);
	fparticleGun->SetParticleTime(0.0*ns);
	fparticleGun->GeneratePrimaryVertex(anEvent); 
      }

      //      G4cout << "energy of the electron is " << kineticenergy << G4endl;

      //In all cases, mass1 is the invariant mass of everything besides the electron.
     
      ux=-ux;
      uy=-uy;
      uz=-uz;
      energy = sqrt ( pc*pc + mass1*mass1 );
      
      //momentum for mass1
      px=pc*ux;
      py=pc*uy;
      pz=pc*uz;

      //boost mass1 into the lab frame  (energy0 and pz are now lab frame variables)
      energy0 = gamma*energy + gamma*beta*pz;
      pz = gamma*beta*energy + gamma*pz;  

      
      //Comment this out if only the ground state should be fired
      norm = px*px + py*py + pz*pz;
      norm = sqrt(norm);
      px = px/norm;
      py = py/norm;
      pz = pz/norm;

      kineticenergy = energy0 - mass1;

      //The germanium will be stopped prior to its decay
      //we try and fire it with zero kinetic energy
      //to see if this impacts the double pulse event topology
      
      //kineticenergy = 0.;

      //Fire the excited germanium state if fireparticle is 0 or 2

      if (fireparticle != 1) {

	if (fireparticle==2 && galliumprocess == 1 && gammaprocess == 2) {
	  px = 0;
	  py = 0;
	  pz = 0;
	  kineticenergy = 0;
	}

	fparticleGun->SetParticleDefinition(germanium);
	fparticleGun->SetParticleMomentumDirection(G4ThreeVector(px,py,pz));
	fparticleGun->SetParticleEnergy(kineticenergy);
	fparticleGun->SetParticlePosition(GunPosition);
	fparticleGun->SetParticleTime(0.0*ns);
	//	fparticleGun->SetParticleCharge(ionCharge);
	fparticleGun->GeneratePrimaryVertex(anEvent); 
      }

    }
    */
  }
  
  void NuSolarPrimaryGeneratorAction::SetOptPhotonPolar(G4double angle)
  {
    if (particleGun->GetParticleDefinition()->GetParticleName() != "opticalphoton")
      {
	G4cout << "--> warning from NuSolarPrimaryGeneratorAction::SetOptPhotonPolar() :"
	  "the particleGun is not an opticalphoton" << G4endl;
	return;
      }
           
    G4ThreeVector normal (1., 0., 0.);
    G4ThreeVector kphoton = particleGun->GetParticleMomentumDirection();
    G4ThreeVector product = normal.cross(kphoton); 
    G4double modul2       = product*product;
 
    G4ThreeVector e_perpend (0., 0., 1.);
    if (modul2 > 0.) {
      e_perpend = (1./sqrt(modul2))*product;
    } 
    G4ThreeVector e_paralle    = e_perpend.cross(kphoton);
    
    G4ThreeVector polar = cos(angle)*e_paralle + sin(angle)*e_perpend;
    particleGun->SetParticlePolarization(polar);
  }
 

  } //end User namespace
