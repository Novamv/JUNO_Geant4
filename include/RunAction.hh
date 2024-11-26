#ifndef RUNACTION_HH
#define RUNACTION_HH

#include "G4UserRunAction.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"
#include "TFile.h"
#include "TTree.h"

class G4Run;
class RunAction : public G4UserRunAction
{
private:
    G4String OutName;
public:
    RunAction();
    ~RunAction();

    void BeginOfRunAction(const G4Run*);
    void EndOfRunAction(const G4Run*);

    void SetOutName(G4String val) { OutName = val;};
};



#endif
