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

    //Find the material in the table provided by G4Material
    G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");

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

    return physWorld;
}