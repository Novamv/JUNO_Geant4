#include "EventAction.hh"
#include "RunAction.hh"
#include "EventHandler.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4UnitsTable.hh"

#include "Randomize.hh"
#include <iomanip>
#include "TMath.h"

EventAction::EventAction()
{
    runAct = (RunAction*)G4RunManager::GetRunManager()->GetUserRunAction();
    printModulo=10000;
}

EventAction::~EventAction()
{
}

void EventAction::BeginOfEventAction(const G4Event* evt)
{
  G4int evtNb = evt->GetEventID();
  if (evtNb%printModulo == 0) {
   G4cout << "\n---> Begin of event: " << evtNb << G4endl;
    // CLHEP::HepRandom::showEngineStatus();
    }

  EventHandler::Get()->ClearAll();
  // initialisation per event
  EventHandler::Get()->SetEvID(evtNb);


}


void EventAction::EndOfEventAction(const G4Event* evt)
{

  G4int evtNb = evt->GetEventID();
  G4cout << "---> End of event: " << evtNb << G4endl;


    EventHandler::Get()->GetTree()->Fill();

}
