#ifndef EVENTHANDLER_HH
#define EVENTHANDLER_HH

#include "G4ThreeVector.hh"
#include "G4String.hh"
#include <iostream>
#include <fstream>
#include "TTree.h"
#include "TFile.h"
#include "TH2F.h"
#include "TH1F.h"
#include "TRandom3.h"
#include <vector>

using namespace std;

class EventHandler
{
private:
    EventHandler();
    static EventHandler* me;

    int evidtree; 
    
    G4String treename;
    TFile* f;
    TTree *t;
    Int_t evid;
    G4double vtxT;
    G4double vtxX[5],vtxY[5],vtxZ[5],vtxE[5],dirX[5],dirY[5],dirZ[5];
    G4int PDG[5];
    G4int NDeposits;
    G4int NPrimary;
    G4double Etot;
    int    DepPDG[10000];
    double DepEnergy[10000];
    double Energy[10000];
    int    DepPTID[10000];
    int    DepTID[10000];
    vector<string> DepProcess;
    double DepPosX[10000];
    double DepPosY[10000];
    double DepPosZ[10000];
    double DepStepLength[10000];
    double TrackLength[10000];
    
public:
    virtual ~EventHandler();
    
    static EventHandler* Get();
    
    TTree * GetTree() {return t;};
    TFile * GetFile() {return f;};

    void CreateTree();
    void ClearAll();
    void SetNPrimary(G4int val){NPrimary=val;};
    void SetVertexX (G4double val, G4int idx=0) {vtxX[idx] = val;};
    void SetVertexY (G4double val, G4int idx=0) {vtxY[idx] = val;};
    void SetVertexZ (G4double val, G4int idx=0) {vtxZ[idx] = val;};
    void SetEnergy (G4double val, G4int idx=0) {vtxE[idx] = val;};
    void SetvtxT (G4double val) {vtxT = val;};
    G4double GetEnergy( G4int idx=0){return vtxE[idx];};
    void SetDirectionX (G4double val, G4int idx=0) {dirX[idx] = val;};
    void SetDirectionY (G4double val, G4int idx=0) {dirY[idx] = val;};
    void SetDirectionZ (G4double val, G4int idx=0) {dirZ[idx] = val;};
    void SetPDG (G4int val, G4int idx=0) {PDG[idx] = val;};
    G4int GetPDG ( G4int idx=0) {return PDG[idx];};

    void SetEvID(G4int val){evid=val;};
    int GetEvID(void){return evid;};

    void SetTreeName(G4String name){treename=name;};
    void SetDepPDG (G4int val){DepPDG[NDeposits]=val;};
    void SetDepEnergy (G4double val){DepEnergy[NDeposits]=val;};
    void SetRemainingEnergy (G4double val){Energy[NDeposits]=val;};
    void SetDepPTID (G4int val){DepPTID[NDeposits]=val;};
    void SetDepTID (G4int val){DepTID[NDeposits]=val;};
    void SetDepProcess (string val){DepProcess.push_back(val);};
    void SetDepPosX (G4double val){DepPosX[NDeposits]=val;};
    void SetDepPosY (G4double val){DepPosY[NDeposits]=val;};
    void SetDepPosZ (G4double val){DepPosZ[NDeposits]=val;};
    void SetDepStepLength (G4double val){DepStepLength[NDeposits]=val;};
    void SetTrackLength (G4double val){TrackLength[NDeposits]=val;};
    void FillDeposits(void){NDeposits++;};
    string GetDepProcess (void){return DepProcess[NDeposits];};

    void SetEvIDtree(G4int val){evidtree=val;};
    int GetEvIDtree(void){return evidtree;};

    G4ThreeVector CopyArrayToVector(G4float*);
};






#endif
