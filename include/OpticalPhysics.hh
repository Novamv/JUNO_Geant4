#ifndef OPTICALPHYSICS_HH
#define OPTICALPHYSICS_HH 


#include "G4OpWLS.hh"
#include "G4OpWLS2.hh"
#include "G4Cerenkov.hh"
#include "G4Scintillation.hh"
#include "G4EmSaturation.hh"

#include "G4OpRayleigh.hh"
#include "G4OpAbsorption.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4OpMieHG.hh"
#include "G4OpticalParameters.hh"


#include "G4OpticalPhoton.hh"
#include "G4ProcessManager.hh"
#include "G4ParticleDefinition.hh"
#include "G4LossTableManager.hh"

#include "G4VPhysicsConstructor.hh"

class OpticalPhysics : public G4VPhysicsConstructor 
{
private:

    G4Cerenkov*             fCerenkovProcess;
    G4Scintillation*        fScintillationProcess;
    G4OpAbsorption*         fAbsorptionProcess;
    G4OpRayleigh*           fRayleighScattering;
    G4OpMieHG*              fMieHGScatteringProcess;
    G4OpBoundaryProcess*    fBoundaryProcess;

    G4bool fCerenkovOn;

    G4double fMaxBetaChange;

public:

    OpticalPhysics(G4bool do_cerenkov = true);
    virtual ~OpticalPhysics();

    virtual void ConstructParticle();
    virtual void ConstructProcess();

    void SetMaxBetaChangePerStep(G4double value);

    G4Cerenkov* GetCerenkovProcess() {return fCerenkovProcess;}


};




#endif
