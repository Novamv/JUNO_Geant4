#include "EventHandler.hh"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

EventHandler* EventHandler::me = 0;

EventHandler::EventHandler()
{
    ClearAll();
    treename = "Output.root";
}

EventHandler::~EventHandler()
{}

EventHandler* EventHandler::Get(){
    if(!me) me = new EventHandler();
    return me;
}

void EventHandler::CreateTree(){
    f = new TFile(treename, "RECREATE", "Output file");
    f->cd();
    t = new TTree("t", "Output tree");

    t->Branch("evid",&evid,"evid/I");
    t->Branch("NPrimary",&NPrimary,"NPrimary/I");
    t->Branch("vtxX",&vtxX,"vtxX[NPrimary]/D");
    t->Branch("vtxY",&vtxY,"vtxY[NPrimary]/D");
    t->Branch("vtxZ",&vtxZ,"vtxZ[NPrimary]/D");
    t->Branch("vtxE",&vtxE,"vtxE[NPrimary]/D");
    t->Branch("vtxT",&vtxT,"vtxT[NPrimary]/D");
    t->Branch("dirX",&dirX,"dirX[NPrimary]/D");
    t->Branch("dirY",&dirY,"dirY[NPrimary]/D");
    t->Branch("dirZ",&dirZ,"dirZ[NPrimary]/D");
    t->Branch("PDG",&PDG,"PDG/I");
    t->Branch("Etot",&Etot,"Etot/D");
    t->Branch("NDeposits",&NDeposits,"NDeposits/I");
    t->Branch("DepPDG",&DepPDG,"DepPDG[NDeposits]/I");
    t->Branch("DepEnergy",&DepEnergy,"DepEnergy[NDeposits]/D");
    t->Branch("Energy",&Energy,"Energy[NDeposits]/D");
    t->Branch("DepPTID",&DepPTID,"DepPTID[NDeposits]/I");
    t->Branch("DepTID",&DepTID,"DepTID[NDeposits]/I");
    t->Branch("DepProcess",&DepProcess);
    t->Branch("DepPosX",&DepPosX,"DepPosX[NDeposits]/D");
    t->Branch("DepPosY",&DepPosY,"DepPosY[NDeposits]/D");
    t->Branch("DepPosZ",&DepPosZ,"DepPosZ[NDeposits]/D");
    t->Branch("DepStepLength",&DepStepLength,"DepStepLength[NDeposits]/D");
    t->Branch("TrackLength",&TrackLength,"TrackLength[NDeposits]/D");
}

G4ThreeVector EventHandler::CopyArrayToVector( float *val) {
   G4ThreeVector vector;
   vector[0] = val[0] ;
   vector[1] = val[1] ;
   vector[2] = val[2] ;
  return vector;

}

void EventHandler::ClearAll(){
    evidtree=0;
    NPrimary=1;
    Etot=0;
    NDeposits=0;
    DepProcess.clear();
}
