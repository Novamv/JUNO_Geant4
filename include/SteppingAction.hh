#ifndef STEPPINGACTION_HH
#define STEPPINGACTION_HH

#include "G4UserSteppingAction.hh"

class DetectorConstruction;
class EventAction;

class SteppingAction : public G4UserSteppingAction
{
private:
    DetectorConstruction* detector;
    EventAction* eventaction;
public:
    SteppingAction();
    ~SteppingAction();

    void UserSteppingAction(const G4Step*);
};


#endif
