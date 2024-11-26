#ifndef ACTIONINIT_HH
#define ACTIONINIT_HH

#include "G4VUserActionInitialization.hh"
#include "PrimaryGenerator.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"
#include "DetectorConstruction.hh"

class ActionInitialization : public G4VUserActionInitialization
{
private:
    
public:
    ActionInitialization();
    ~ActionInitialization();

    virtual void Build() const;
};




#endif
