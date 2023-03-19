#include "physics.hh"


MyPhysicsList::MyPhysicsList()
{
    //Register the physics processes needed for our simulation
    RegisterPhysics (new G4EmStandardPhysics());
    RegisterPhysics (new G4OpticalPhysics());
}

MyPhysicsList::~MyPhysicsList()
{}