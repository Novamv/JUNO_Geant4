#ifndef EVENTACTION_HH
#define EVENTACTION_HH

#include "G4UserEventAction.hh"
#include "globals.hh"


class RunAction;


class EventAction : public G4UserEventAction
{
private:
    RunAction* runAct;
    G4int printModulo;
public:
    EventAction();
    ~EventAction();

    void BeginOfEventAction(const G4Event*);
    void EndOfEventAction(const G4Event*);

    void SetPrintModulo(G4int val){printModulo=val;};
};



#endif

