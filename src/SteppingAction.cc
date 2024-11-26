#include "SteppingAction.hh"
#include "DetectorConstruction.hh"
#include "EventAction.hh"
#include "EventHandler.hh"
#include "G4Step.hh"
#include "G4RunManager.hh"

#include "G4VPhysicalVolume.hh"
#include "G4ThreeVector.hh"
#include <G4UnitsTable.hh>
#include "G4SystemOfUnits.hh"


SteppingAction::SteppingAction()
{
    detector = (DetectorConstruction*)G4RunManager::GetRunManager()->GetUserDetectorConstruction();
    eventaction = (EventAction*)G4RunManager::GetRunManager()->GetUserEventAction();
}

SteppingAction::~SteppingAction()
{}

void SteppingAction::UserSteppingAction(const G4Step* aStep)
{
    //Get Volume of the current Step
    G4VPhysicalVolume* volume = aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume();

    //Collect energy and track length step by step
    G4double edep = aStep->GetTotalEnergyDeposit();
    G4double energy = aStep->GetTrack()->GetKineticEnergy();

    G4double trackL = aStep->GetTrack()->GetTrackLength();

    G4double stepl = 0;
    if(aStep->GetTrack()->GetDefinition()->GetPDGCharge() != 0.){
        stepl = aStep->GetStepLength();
    }

    G4ThreeVector pos=aStep->GetPreStepPoint()->GetPosition();
    G4ThreeVector posProc=aStep->GetTrack()->GetPosition();
    G4ThreeVector mom=aStep->GetTrack()->GetMomentumDirection();
    string vol =  aStep->GetTrack()->GetVolume()->GetName();

    //save deposit
    if (aStep->GetTrack()->GetDefinition()->GetPDGCharge() != 0.)
    {
        EventHandler::Get()->SetDepEnergy(edep/keV);
        EventHandler::Get()->SetRemainingEnergy(energy/keV);
        EventHandler::Get()->SetDepPDG( aStep->GetTrack()->GetDefinition()->GetPDGEncoding());
        EventHandler::Get()->SetDepPTID(aStep->GetTrack()->GetParentID());
        EventHandler::Get()->SetDepTID(aStep->GetTrack()->GetTrackID());
        EventHandler::Get()->SetDepPosX(pos.x()/cm);
        EventHandler::Get()->SetDepPosY(pos.y()/cm);
        EventHandler::Get()->SetDepPosZ(pos.z()/cm);
        EventHandler::Get()->SetDepStepLength(stepl/cm);
        EventHandler::Get()->SetTrackLength(trackL/cm);
        std::string sname( aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName ());
        EventHandler::Get()->SetDepProcess(sname);
        EventHandler::Get()->FillDeposits();
    }
    

}
