#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{}

MyDetectorConstruction::~MyDetectorConstruction()
{}

/*Define the Construct method from the Detector Construction class*/
G4VPhysicalVolume *MyDetectorConstruction::Construct()
{   
    /*Get G4Element by index, such class contains the table of characteristics of elements.
    Elements can be assembled singly or in mixtures into materials used in volume definitions 
    via the G4Material class.*/
    G4NistManager *nist = G4NistManager::Instance();

    /*G4Material is used to define the material composition of Geant4 volumes.
    A G4Material is always made of G4Elements. It should has the name, 
    the list of G4Elements, material density, material state, temperature, 
    pressure. The class also contains the Table of defined materials with its 
    characteristics.*/

    //Create SiO2 as a G4Material, the args are the name, the density and number of components
    G4Material *SiO2 = new G4Material("SiO2", 2.201*g/cm3, 2);
    //Add the Silicon and the Oxigen to our new material
    SiO2->AddElement(nist->FindOrBuildElement("Si"), 1);
    SiO2->AddElement(nist->FindOrBuildElement("O"), 2);

    //Create SiO2 as a G4Material, the args are the name, the density and number of components
    G4Material *H2O = new G4Material("H2O", 1.000*g/cm3, 2);
    //Add the Hidrogen and Oxigen to our new material
    H2O->AddElement(nist->FindOrBuildElement("H"), 2);
    H2O->AddElement(nist->FindOrBuildElement("O"), 1);

    //Create a pointer to the Carbon in G4Material index
    G4Element *C = nist->FindOrBuildElement("C");

    //Create Aerogel from the materials created previously
    G4Material *Aerogel = new G4Material("Aerogel", 0.200*g/cm3, 3);
    Aerogel->AddMaterial(SiO2, 62.5*perCent);
    Aerogel->AddMaterial(H2O, 37.4*perCent);
    Aerogel->AddElement(C, 0.1*perCent);

    G4double energy[2] = {1.239841939*eV/0.9,1.239841939*eV/0.2};
    G4double rindexAerogel[2] = {1.1, 1.1};
    G4double rindexWorld[2] = {1.0, 1.0};

    G4MaterialPropertiesTable *mptAerogel = new G4MaterialPropertiesTable();
    mptAerogel->AddProperty("RINDEX", energy, rindexAerogel, 2);

    Aerogel->SetMaterialPropertiesTable(mptAerogel);

    //Find the material in the table provided by G4Material
    G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");

    G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();
    mptWorld->AddProperty("RINDEX", energy, rindexWorld, 2);

    worldMat->SetMaterialPropertiesTable(mptWorld);

    /*A G4Box is a cuboid of given half lengths dx,dy,dz. The Box is
    centred on the origin with sides parallel to the x/y/z axes.
    We call World Volume is the volume which bound the space where all 
    of our physics processes and interactions happen. The main objetive of this 
    method is to create such Volume.
    Every volume created in Geant4 has to contain three parts:
    1. Solid Volume: Defines the shaspe and size of the volume
    2. Logical Volumen: includes the material of the volume
    3. Physical Volume: Places the volume in our Geant4 application*/
    G4Box *solidWorld = new G4Box("solidWorld", 0.5*m, 0.5*m, 0.5*m);

    /*G4LogicalVolume represents a leaf node or unpositioned subtree in the geometry hierarchy.
    Logical volumes are named, and may have daughters ascribed to them.
    They are responsible for retrieval of the physical and tracking attributes
    of the physical volume that it represents: solid, material, magnetic field,
    and optionally, user limits, sensitive detectors, regions, biasing weights.*/
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, 
    worldMat, "logicWorld");

    /*G4VPhysicalVolume is an Abstract Base class for the representation of positioned volume.  
    The volume is placed within a mother volume, relative to its coordinate 
    system.  Either a single positioned volume or many positioned volume can 
    be represented by a particular G4VPhysicalVolume.
    G4PVPlacemet is a class representing a single volume positioned within and relative
    to a mother volume.*/
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0.,
     0., 0.), logicWorld, "physWorld", 0, false, 0, true);

    //Create the solid volume of the cherenkov radiator
    G4Box *solidRadiator = new G4Box("solidRadiator", 0.4*m, 0.4*m, 0.01*m);

    //Create the logical volume of the cherenkov radiator
    G4LogicalVolume *logicRadiator = new G4LogicalVolume(solidRadiator, 
    Aerogel, "logicRadiator");

    //Create the physical volume of the cherenkov radiator
    G4VPhysicalVolume *physRadiator = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.25*m),
    logicRadiator, "physRadiator", logicWorld, false, 0, true);

    G4Box *solidDetector = new G4Box("solidDetector", 0.005*m, 0.005*m, 0.01*m);

    logicDetector = new G4LogicalVolume(solidDetector, worldMat, "logicalDetector");

    for(G4int i = 0; i < 100; i++)
    {
        for(G4int j = 0; j < 100; j++)
        {
            G4VPhysicalVolume *physDetector = new G4PVPlacement(0, G4ThreeVector(
                -0.5*m + (i + 0.5)*m/100, -0.5*m + (j + 0.5)*m/100, 0.49*m), logicDetector,
                "physDetector", logicWorld, false, j + i*100, true);
        }
    }

    return physWorld;
}