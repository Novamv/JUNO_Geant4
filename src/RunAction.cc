#include "RunAction.hh"
#include "EventHandler.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "TFile.h"
#include "TTree.h"

RunAction::RunAction()
{
    OutName="Output.root";

}

RunAction::~RunAction()
{
}

void RunAction::BeginOfRunAction(const G4Run* aRun)
{
  G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;

  //inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);

  //initialize cumulative quantities
  //
  EventHandler::Get()->SetTreeName(OutName);
  EventHandler::Get()->CreateTree();

}


void RunAction::EndOfRunAction(const G4Run* aRun)
{
  G4int NbOfEvents = aRun->GetNumberOfEvent();
  if (NbOfEvents == 0) return;

  //
  G4cout
     << "\n--------------------End of Run------------------------------\n"
     << G4endl;



  EventHandler::Get()->GetFile()->cd();
  EventHandler::Get()->GetTree()->Write();
  EventHandler::Get()->GetFile()->Close();

}
