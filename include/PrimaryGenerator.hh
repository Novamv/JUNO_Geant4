#ifndef GENERATOR_HH
#define GENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "globals.hh"

class PrimaryGenerator : public G4VUserPrimaryGeneratorAction
{
private:
    G4ParticleGun *fParticleGun;
public:
    PrimaryGenerator(/* args */);
    ~PrimaryGenerator();

    virtual void GeneratePrimaries(G4Event*);
};

#endif
