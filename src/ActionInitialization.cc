#include "ActionInitialization.hh"



ActionInitialization::ActionInitialization()
{
}

ActionInitialization::~ActionInitialization()
{
}

void ActionInitialization::Build() const
{
    SetUserAction(new PrimaryGenerator());

    SetUserAction(new RunAction());

    SetUserAction(new EventAction());
    
    SetUserAction(new SteppingAction());
    
}
