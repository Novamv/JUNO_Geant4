#include "DetectorConstruction.hh"

#include "G4Box.hh"
#include "G4Element.hh"
// #include "G4GDMLParser.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "G4OpticalSurface.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

JUNODetectorConstruction::JUNODetectorConstruction(){


}

JUNODetectorConstruction::~JUNODetectorConstruction(){


}

G4VPhysicalVolume* JUNODetectorConstruction::Construct()
{
  // Clean old geometry, if any

    G4GeometryManager::GetInstance()->OpenGeometry();
    G4PhysicalVolumeStore::GetInstance()->Clean();
    G4LogicalVolumeStore::GetInstance()->Clean();
    G4SolidStore::GetInstance()->Clean();

    G4double z, a, density;
    G4int nelements;
  // ------------- Materials -------------

    //Vaccum

    auto N = new G4Element("Nitrogen", "N", z = 7, a = 14.01 * g / mole);
    auto O = new G4Element("Oxygen", "O", z = 8, a = 16.00 * g / mole);
    fVacuum = new G4Material("Vacuum", density = 1.29e-20 * g/cm3, nelements = 2);
    fVacuum->AddElement(N, 70. * perCent);
    fVacuum->AddElement(O, 30. * perCent);

    //LAB
    auto H = new G4Element("Hydrogen", "H", z = 1, a = 1.01 * g / mole);
    auto C = new G4Element("Carbon", "C", z = 6, a = a = 12.01 * g / mole);
    fLAB = new G4Material("LAB", density = 0.86 * g/cm3, nelements = 2);
    fLAB->AddElement(C, 18);        
    fLAB->AddElement(H, 30); 

  // ------------ Generate & Add Material Properties Table ------------
  //

    G4double LAB_ENERGY[2] = {2.034 * eV, 4.136 * eV};
    G4double LAB_SCINT[2] = {1.0, 1.0};
    G4double RINDEX[2] = {1.58, 1.58};
    G4double ABSLENGTH[2] = {1.58, 1.58};

    G4MaterialPropertiesTable* mptLAB = new G4MaterialPropertiesTable();

    mptLAB->AddProperty("RINDEX", LAB_ENERGY, RINDEX, 2);
    mptLAB->AddProperty("ABSLENGTH", LAB_ENERGY, ABSLENGTH, 2);
    mptLAB->AddProperty("SCINTILLATIONCOMPONENT1", LAB_ENERGY, LAB_SCINT, 2);

    mptLAB->AddConstProperty("SCINTILLATIONYIELD", 14000. / MeV);
    mptLAB->AddConstProperty("RESOLUTIONSCALE", 1.0);
    mptLAB->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 1. * ns);

    fLAB->SetMaterialPropertiesTable(mptLAB);

  // ------------- Volumes --------------

    //World
    G4double WorldSizeX = 25 * m;
    G4double WorldSizeYZ = 25 * m;

    solidWorld = new G4Box("World", WorldSizeX/2, WorldSizeYZ/2, WorldSizeYZ/2);

    logicWorld = new G4LogicalVolume(solidWorld, fVacuum, "World");

    physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "World", 0, false, 0, true);

    //Sphere

    solidLSSphere = new G4Sphere("LSSphere",  0, 10 * m, 0, 360 * deg, 0, 180 *deg );

    logicLSSphere = new G4LogicalVolume(solidLSSphere, fLAB, "LSSphere");

    physiLSSphere = new G4PVPlacement( 0,G4ThreeVector(0,0,0),
				       logicLSSphere,    // its logical volume
				       "LSSphere",       // its name
				       logicWorld,  // its mother  volume
				       false,           // no boolean operations
				       0,              // no particular field
				       true);

    return physWorld;

}
