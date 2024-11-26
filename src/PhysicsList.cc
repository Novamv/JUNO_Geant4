#include "PhysicsList.hh"
#include "OpticalPhysics.hh"
#include "G4EmParameters.hh"

PhysicsList::PhysicsList(){

    //EM physics
    // RegisterPhysics( new G4EmStandardPhysics() );
    RegisterPhysics( new G4EmLivermorePhysics() );

    G4EmParameters* param = G4EmParameters::Instance();
    param -> SetIntegral(1);
    //Optical Physics
    G4bool do_cerenkov = true; // set to false to remove Cerenkov

    G4double fBetaChange = 10.0;

    // G4OpticalPhysics* opticalPhysics = new G4OpticalPhysics();
    // RegisterPhysics(opticalPhysics);

    OpticalPhysics* fOpticalPhysics = new OpticalPhysics(do_cerenkov); 
    fOpticalPhysics->SetMaxBetaChangePerStep(fBetaChange);
    // RegisterPhysics(fOpticalPhysics);
}

PhysicsList::~PhysicsList(){

}
