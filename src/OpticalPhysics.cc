#include "OpticalPhysics.hh"


OpticalPhysics::OpticalPhysics(G4bool do_cerenkov) : G4VPhysicsConstructor("Optical")
{
    fScintillationProcess = nullptr;
    fCerenkovProcess = nullptr;

    fCerenkovOn = do_cerenkov;

    fMaxBetaChange = 10.0;
}

OpticalPhysics::~OpticalPhysics(){ }


void OpticalPhysics::ConstructParticle()
{
    G4OpticalPhoton::OpticalPhotonDefinition();
}


void OpticalPhysics::ConstructProcess()
{
    G4cout << "OpticalPhysics : Add Optical Processes" << G4endl;

    auto params = G4OpticalParameters::Instance();

    // Add Optical Process


    G4ProcessManager* pManager = 
        G4OpticalPhoton::OpticalPhoton()->GetProcessManager();

    if(!pManager)
    {
        G4ExceptionDescription ed;
        ed << "Optical Photon without a Process Manager";
        G4Exception("G4OpticalPhysics::ConstructProcess()", "", FatalException, ed);
        return;
    }

    
    fAbsorptionProcess = new G4OpAbsorption();
    if(params->GetProcessActivation("OpAbsorption"))
        pManager->AddDiscreteProcess(fAbsorptionProcess);
        
    fRayleighScattering = new G4OpRayleigh();
    if(params->GetProcessActivation("OpRayleigh"))
        pManager->AddDiscreteProcess(fRayleighScattering);
    
    fMieHGScatteringProcess = new G4OpMieHG();
    if(params->GetProcessActivation("OpMieHG"))
        pManager->AddDiscreteProcess(fMieHGScatteringProcess);

    fBoundaryProcess = new G4OpBoundaryProcess();
    if(params->GetProcessActivation("OpBoundary"))
        pManager->AddDiscreteProcess(fBoundaryProcess);
   
    G4OpWLS* wls = new G4OpWLS();
    if(params->GetProcessActivation("OpWLS"))
        pManager->AddDiscreteProcess(wls);

    G4OpWLS2* wls2 = new G4OpWLS2();  // comment if using G4v10.4
    if(params->GetProcessActivation("OpWLS2"))
        pManager->AddDiscreteProcess(wls2);


    fScintillationProcess = new G4Scintillation();
    G4EmSaturation* emSaturation = G4LossTableManager::Instance()->EmSaturation();
    fScintillationProcess->AddSaturation(emSaturation);

    if (fCerenkovOn){

        fCerenkovProcess = new G4Cerenkov();
        fCerenkovProcess->SetMaxNumPhotonsPerStep(300);
        fCerenkovProcess->SetTrackSecondariesFirst(true);

        // fCerenkovProcess->SetMaxBetaChangePerStep(fMaxBetaChange);
        // G4double maxBetaChange = fCerenkovProcess->GetMaxBetaChangePerStep();
        // std::cout << "Max Beta Change is set to: " << maxBetaChange * 100 << "%" << std::endl;

    }



    auto particleIterator = GetParticleIterator();
    particleIterator->reset();
    while ( (*particleIterator)() )
    {
        G4ParticleDefinition* particle = particleIterator->value();
        G4String particleName = particle->GetParticleName();

        pManager = particle->GetProcessManager();
        if(!pManager)
        {
        G4ExceptionDescription ed;
        ed << "Particle " << particleName << "without a Process Manager";
        G4Exception("G4OpticalPhysics::ConstructProcess()", "", FatalException,
                    ed);
        return;  // else coverity complains for pManager use below
        }

        if(fCerenkovOn){
            if (fCerenkovProcess->IsApplicable(*particle) && params->GetProcessActivation("Cerenkov"))
            {
                pManager->AddProcess(fCerenkovProcess);
                pManager->SetProcessOrdering(fCerenkovProcess, idxPostStep);

            }
            
        }
        if (fScintillationProcess->IsApplicable(*particle) && params->GetProcessActivation("Scintillation"))
        {
            pManager->AddProcess(fScintillationProcess);
            pManager->SetProcessOrderingToLast(fScintillationProcess,idxAtRest);
            pManager->SetProcessOrderingToLast(fScintillationProcess,idxPostStep);
        }
        if(fBoundaryProcess->IsApplicable(*particle) && params->GetProcessActivation("OpBoundary"))
        {
            pManager->SetProcessOrderingToLast(fBoundaryProcess, idxPostStep);
        }
        
    }
    

}

void OpticalPhysics::SetMaxBetaChangePerStep(G4double value){
    fMaxBetaChange = value;
}
