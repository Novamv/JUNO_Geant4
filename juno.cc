#include <iostream>

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "ActionInitialization.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"


int main(int argc, char** argv)
{
    G4RunManager* runManager = new G4RunManager();

    // Register detector geometry and meterials 
    JUNODetectorConstruction* theDetector = new JUNODetectorConstruction();
    runManager->SetUserInitialization(theDetector);

    // Register PhysicsList
    runManager->SetUserInitialization(new PhysicsList());

    //Register Action Initialization
    runManager->SetUserInitialization(new ActionInitialization());

    runManager->Initialize();


    G4VisManager* visManager = new G4VisExecutive();
    visManager->Initialize();

    G4UImanager* UImanager = G4UImanager::GetUIpointer();

    if (argc!=1)    
    {
        G4String command = "/control/execute ";
        G4String filename = argv[1];
        UImanager->ApplyCommand(command+filename);

    }
    else
    {
        G4UIExecutive* ui = new G4UIExecutive(argc, argv);

        UImanager->ApplyCommand("/vis/open OGL");
        UImanager->ApplyCommand("/vis/viewer/set/viewpointVector 1 1.5 1");
        UImanager->ApplyCommand("/vis/drawVolume");
    //     UImanager->ApplyCommand("/vis/viewer/set/autoRefresh true");
    //     UImanager->ApplyCommand("vis/scene/add/trajectories smooth");
    //     UImanager->ApplyCommand("/control/execute run.mac");

        ui->SessionStart();
        delete ui;
    }
    
    return 0;
}
