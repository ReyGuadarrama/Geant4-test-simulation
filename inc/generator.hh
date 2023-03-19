#ifndef GENERATOR_HH
#define GENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"

/*G4VUserPrimaryGeneratorAction is an abstract base class for user's mandatory 
action class for primary vertex/particle generation. This class has only one pure 
virtual method GeneratePrimaries() which is invoked from G4RunManager during 
the event loop.
This class is NOT intended for generating primary vertex/particle
by itself. This class should:
- have one or more G4VPrimaryGenerator concrete classes such as G4ParticleGun
- set/change properties of generator(s)
- pass G4Event object so that the generator(s) can generate primaries.*/
class MyPrimaryGenerator : public G4VUserPrimaryGeneratorAction
{
public:
    MyPrimaryGenerator();
    ~MyPrimaryGenerator();

    /*GeneratePrimaries() is the only one method of the G4VUserPrimaryGeneratorAction 
    class, it recives a G4Event object so that the generator can generate primaries.
    G4Event is the class which represents an event. A G4Event is constructed and
    deleted by G4RunManager (or its derived class). When a G4Event object is
    passed to G4EventManager, G4Event must have one or more primary vertices
    and primary particle(s) associated to the vertices as an input of
    simulating an event.
    G4Event has trajectories, hits collections, and/or digi collections*/
    virtual void GeneratePrimaries(G4Event*);

private:

    /*G4ParticleGun is a concrete class of G4VPrimaryGenerator. It shoots a particle of
    given type into a given direction with either a given kinetic energy or
    momentum.
    G4VPrimaryGenerator is an abstract base class of all of primary generators.
    This class has only one pure virtual method GeneratePrimaryVertex()
    which takes a G4Event object and generates a primay vertex and
    primary particles associate to the vertex*/
    G4ParticleGun *fParticleGun;
    
};

#endif