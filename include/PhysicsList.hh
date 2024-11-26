#ifndef PHYSICSLIST_HH
#define PHYSICSLIST_HH

#include "G4VModularPhysicsList.hh"
#include "G4EmStandardPhysics.hh"
#include "G4EmLivermorePhysics.hh"

#include "G4OpticalPhysics.hh"
#include "G4Cerenkov.hh"
#include "G4Scintillation.hh"

class PhysicsList : public G4VModularPhysicsList
{
private:
    
public:
    PhysicsList();
    ~PhysicsList();
};


#endif
