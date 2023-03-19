#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

//add the necessary headers to create our detector construction
#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"

/*Create our own Detector Construction class from G4VUserDetectorConstruction
class. This is the abstract base class for the user's mandatory initialization
of the detector setup. It has only one pure virtual method Construct()
which is invoked by G4RunManager when its Initialize() method is invoked.
The Construct() method must return the G4VPhysicalVolume pointer which
represents the world volume.*/
class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
    MyDetectorConstruction();
    ~MyDetectorConstruction();

    /*G4VPhysicalVolume is an Abstract Base class for the representation of positioned volume.  
    The volume is placed within a mother volume,  relative to its coordinate 
    system.  Either a single positioned volume or many positioned volume can 
    be represented by a particular G4VPhysicalVolume.*/
    virtual G4VPhysicalVolume *Construct();
};

#endif
