#ifndef PHYSICS_HH
#define PHYSICS_HH

#include "G4VModularPhysicsList.hh"
#include "G4EmStandardPhysics.hh"
#include "G4OpticalPhysics.hh"


/*G4VUserPhysicsList is class is an abstract class for constructing particles and processes.
User must implement the following two pure virtual methods in the concrete
class derived from this class:
- G4VUserPhysicsList::ConstructParticle()
    Construct particles
- G4VUserPhysicsList::ConstructProcess()
    Construct procesess and register them to particles.
G4ModulaPhysicsList is a sub class of G4VUserPhysicsList in which insted of construct the process
or the partcile from scratch we can register an existing one located in G4PhysicsList*/
class MyPhysicsList : public G4VModularPhysicsList
{
public:
    MyPhysicsList();
    ~MyPhysicsList();
};

#endif