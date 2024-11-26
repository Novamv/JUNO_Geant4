#include "PrimaryGenerator.hh"

PrimaryGenerator::PrimaryGenerator()
{
    G4int n_particle = 1;
    fParticleGun = new G4ParticleGun(1); //Nb of particles per event
    
    //Default particle kinematics
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* particle = particleTable->FindParticle("e-");

    G4ThreeVector pos(0.,0.,0.);
    G4ThreeVector mom(1.,0.,0.);

    fParticleGun->SetParticleDefinition(particle);
    fParticleGun->SetParticlePosition(pos);
    fParticleGun->SetParticleMomentumDirection(mom);
    fParticleGun->SetParticleEnergy(1. * CLHEP::MeV);
}

PrimaryGenerator::~PrimaryGenerator()
{
    delete fParticleGun;
}

void PrimaryGenerator::GeneratePrimaries(G4Event* anEvent)
{
    fParticleGun->GeneratePrimaryVertex(anEvent);
}

