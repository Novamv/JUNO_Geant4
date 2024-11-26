#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4Sphere.hh"

class G4Box;
class G4Element;
class G4LogicalVolume;
class G4Material;
class G4MaterialPropertiesTable;
class G4Tubs;
class G4VPhysicalVolume;

class JUNODetectorConstruction : public G4VUserDetectorConstruction
{
public:
    JUNODetectorConstruction();
    ~JUNODetectorConstruction();

    virtual G4VPhysicalVolume* Construct();

private:

    G4Box* solidWorld;              //pointer to the solid World
    G4LogicalVolume* logicWorld;    //pointer to the logical World
    G4VPhysicalVolume* physWorld;   //pointer to the physical World

    G4Sphere* solidLSSphere;           //pointer to the Sphere
    G4LogicalVolume* logicLSSphere;
    G4VPhysicalVolume* physiLSSphere;

    G4Material *fVacuum;
    G4Material *fLAB;
};



#endif
