#!/bin/bash
# First tests of a shell script to do a bunch of runs at once

#Energy Variable
#EnergyValue=1


#Setting the number of threads for the experiment.
#NThreads=14

#Number of particles to Run
#NParticles = 1;



##declare meanRange
#Loop over the different particles
for particleName in  "nu_e"  
do
    #For Particle energies in E-1 MeV (Format Issues)
    for EnergyValue in 30 35 40 45 50 55 60
    do
        #Selecting which modes we want in our Neutrino Decay
	for mode in 1 2
	do
	    
	    
	    #Define the Directory for the doings
	    directory=''$EnergyValue' E-1 MeV '$particleName'Root Data'
	    #Make the Directory for the files to go into
	    mkdir "$directory"
	    
	    
	    #Fix up phys.mac for use with proper energy for particle
	    ##meanLower = $meanRange - $meanRange/2
	    echo "# Macro file for the initialization of physics items
# This file follows ans.mac in the ~geant4/ansmt/source directory
# It provides information to the PhysicsListMessenger



#  MY STUDIES
#Point Source of electrons for Scintillation


/run/initialize

/gps/particle "$particleName"
/gps/energy "$EnergyValue"E-1 MeV
/gps/pos/type Volume
/gps/pos/shape Sphere
/gps/pos/centre 0 0 -2.95 cm
/gps/pos/radius 0.3 cm

/gps/direction 0 0 1




	       #Creating Histograms
/analysis/setFileName "$particleName+$EnergyValue+$mode"








/tracking/verbose 0 
/tracking/storeTrajectory 0


/control/verbose 0
/control/saveHistory
/run/verbose 0




/run/beamOn 10000" > photon.mac

	    echo '/// \file optical/CSat/src/CSatPrimaryGeneratorAction.cc
/// \brief Implementation of the CSatPrimaryGeneratorAction class
//
//
#include "CSatPrimaryGeneratorAction.hh"

#include "globals.hh"
#include "G4Event.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4GeneralParticleSource.hh"
#include "Randomize.hh"
#include "G4ParticleGun.hh"
#include "G4IonTable.hh"
#include "G4ParticlePropertyData.hh"
#include "G4Electron.hh"
#include "G4Step.hh"
#include "G4Track.hh"







//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CSatPrimaryGeneratorAction::CSatPrimaryGeneratorAction()
{
  
  particleGun = new G4GeneralParticleSource();
  /*
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* particle = particleTable->FindParticle("geantino");

    particleGun->SetParticleDefinition(particle);
    particleGun->SetParticleEnergy(0.*GeV);
    particleGun->SetParticlePosition(G4ThreeVector(0,0,-20*cm));
    particleGun->SetParticleTime(0.0*ns);

    //create a new Particle Gun that will steal the randomized location of the
    //first particle gun, and use its energy from said gps for the decay products

    G4int n_particle=1;
    fparticleGun = new G4ParticleGun(n_particle);

    energyPri=0.;
  */

  
  G4int n_particle = 1;
  fparticleGun     = new G4ParticleGun(n_particle);

  //G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
   //G4String particleName;
  //fparticleGun->SetParticleDefinition(particleTable->FindParticle(particleName = "geantino"));
  // Default energy,position,momentum
  //fparticleGun->SetParticleEnergy(0*MeV);
  //fparticleGun->SetParticleTime(0.0*ns);
  //fparticleGun->SetParticlePosition(G4ThreeVector(0, 0., -2.95 * cm));
  //fparticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CSatPrimaryGeneratorAction::~CSatPrimaryGeneratorAction()
{
  delete fparticleGun;
  delete particleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CSatPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  /*
  //G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4IonTable* ionTable = G4IonTable::GetIonTable();
  //G4ParticleDefinition* germaniumtest = ionTable->GetIon(32,69, 397*keV);
   
  G4int Z = 32;
  G4int A = 69;

  G4double charge = 0* eplus;
  G4double energy = 397*keV;
  G4ParticleDefinition* germaniumtest = ionTable->GetIon(Z,A, energy);
  germaniumtest -> SetPDGStable(false);
  fparticleGun->SetParticleDefinition(germaniumtest);
  fparticleGun->SetParticleCharge(charge);
  fparticleGun->SetParticlePosition(G4ThreeVector(0,0,-2.95*cm));
  fparticleGun->SetParticleEnergy(0*MeV);
  
       
  

  
  fparticleGun->GeneratePrimaryVertex(anEvent);
  */











  
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

    energyPri = 0.;
    particleGun->GeneratePrimaryVertex(anEvent);

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
   
    G4int neutrinoprocess = 1;  //0 for cosmic rays, 1 for neutrino events
    G4int galliumprocess = 0;  // 0 for Gallium-69, 1 for Gallium-71
    G4int gammaprocess = '$mode';  // 69Ge:  0 for ground state, 1 for 87 keV gamma, 2 for 397 keV gamma
                             // 71Ge:  0 for ground state, 1 for 198 keV excited state
                             // 71Ge:  2 is for firing the 174 keV state

    //G4int fireparticle = 2; 
   

    G4double atomicmassunit = 931.4940954*MeV;
   
    if (neutrinoprocess > 0) {

      // G4cout << "Neutrino Event begins." << G4endl;

      G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
      G4IonTable* ionTable = G4IonTable::GetIonTable();
      G4double excitEnergy= 0. * MeV; //the gamma ray energy
      G4double delay;            //the half-life of the excited germanium state
      G4double ionCharge = 1.*eplus;  //We go from a neutral gallium to a charged germanium

   
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

      germanium -> SetPDGStable(true);
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
      G4double pccm, energy;
     
      //neutrino + 69Ga --> m_69Ge + e-, m_69Ge --> 69Ge + gamma
      //neutrino + 71Ga --> m_71Ge + e-, m_71Ge --> 71Ge + gamma

      //mass = mass of electron
      mass1 = massge;  //excited state
      mass2 = massge0; //ground state
      mass3 = 0.;      //photon
      particle2 = germanium0;
      particle3 = photon;
     
      //mass1 is the  mass of the m1_69Ge (case 2)
      
      // PCCM IS THE BACK-TO-BACK MOMENTUM FOR MASS AND MASS1 IN THEIR CENTER OF MASS FRAME

      pccm = (invariantmass*invariantmass - (mass1 + mass)*(mass1 + mass));
      pccm = pccm*(invariantmass*invariantmass - (mass1 - mass)*(mass1 - mass));
      pccm = sqrt(pccm) / (2.*invariantmass);

      //Given the magnitude pccm, we randomize components and normalize.
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

      G4double px = pccm*ux;
      G4double py = pccm*uy;
      G4double pz = pccm*uz;
    
      //Boost mass (electron) into the lab frame
      energy = pccm * pccm + mass * mass;
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

      
     
      ux=-ux;
      uy=-uy;
      uz=-uz;
      energy = sqrt ( pccm*pccm + mass1*mass1 );
      
      //momentum for mass1
      //px=pccm*ux;
      //py=pccm*uy;
      //pz=pccm*uz;

      //boost mass1 into the lab frame  (energy0 and pz are now lab frame variables)
      //energy0 = gamma*energy + gamma*beta*pz;
      //pz = gamma*beta*energy + gamma*pz;  

      
      //Comment this out if only the ground state should be fired
      
      norm = px*px + py*py + pz*pz;
      norm = sqrt(norm);
      px = px/norm;
      py = py/norm;
      pz = pz/norm;
      
      //G4double kineticenergyGe = energy0 - mass1;

      G4double pxGer = 0;
      G4double pyGer = 0;
      G4double pzGer = 0;
      G4double kineticenergyGer = 0;
      
      fparticleGun->SetParticleDefinition(particle);
      fparticleGun->SetParticleMomentumDirection(G4ThreeVector(px,py,pz));
      fparticleGun->SetParticleEnergy(kineticenergy);
      fparticleGun->SetParticlePosition(GunPosition);
      fparticleGun->SetParticleTime(0.0*ns);
      fparticleGun->GeneratePrimaryVertex(anEvent);
      
      

      //G4cout << "Delay of the Germanium Atom is: " << lifetime << G4endl;
      
      fparticleGun->SetParticleDefinition(germanium);
      fparticleGun->SetParticleMomentumDirection(G4ThreeVector(pxGer,pyGer,pzGer));
      fparticleGun->SetParticleEnergy(kineticenergyGer);
      fparticleGun->SetParticlePosition(GunPosition);
      //fparticleGun->SetParticleTime(delay);
      
      fparticleGun->GeneratePrimaryVertex(anEvent);

      //G4ParticleDefinition* germaniumtest = ionTable->GetIon(31,69,0*keV);
      //germaniumtest->SetPDGStable(true);
      //G4double lifetime = germaniumtest ->GetPDGLifeTime();
      //G4cout << "Delay of the Germanium Atom is: " << lifetime/s << G4endl;

      
    }
    //G4IonTable* ionTable = G4IonTable::GetIonTable();
    //G4ParticleDefinition* germaniumtest = ionTable->GetIon(31,69,0*keV);
    //germaniumtest->SetPDGStable(true);
    //G4double lifetime = germaniumtest ->GetPDGLifeTime();
    //G4cout << "Delay of the Germanium Atom is: " << lifetime/s << G4endl;

    
}
  
  

void CSatPrimaryGeneratorAction::SetOptPhotonPolar(G4double angle)
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


' > CSatPrimaryGeneratorAction.cc


	    mv CSatPrimaryGeneratorAction.cc ~/Desktop/CubeSat/src
	    make
	    
	    ./CSat photon.mac
	    #Extra spaces added because the files want to move too soon otherwise.
	    #Don't know exactly why
	    
	    
	    
	    
	    

	    
	    mv $particleName+$EnergyValue+$mode.root "$directory"
	    
		      done 
		      done
		      done

