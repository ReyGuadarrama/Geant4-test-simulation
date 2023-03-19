#include "generator.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
    fParticleGun = new G4ParticleGun(1);
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
    delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
    /*G4ParticleTable is the table of pointers to G4ParticleDefinition.
    Each G4ParticleDefinition pointer is stored with its name as a key
    to itself. So, each G4ParticleDefinition object must have unique
    name. */
    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();

    /*G4String is a commong string type for Geant4, it can be passed to any function
    accepting `std::string` or `std::string_view` arguments*/
    G4String particleName = "proton";

    /*G4ParticleDefinition class contains all the static data of a particle.
    It uses the process manager in order to collect all the processes
    this kind of particle can undertake.
    The FindParticle method returns a pointer to the particle given in the argument*/
    G4ParticleDefinition *particle = particleTable->FindParticle("proton");

    /*Define the vectors for initial position an momentum of the generate particle
    these are just vectors which names where choosen to distinguish its porpuses*/
    G4ThreeVector pos(0., 0., 0.);
    G4ThreeVector mom(0., 0., 1.);

    /*Set all the particle's characteristics and initial values by using G4VPrimaryGenerator 
    and G4ParticleGun methods*/
    fParticleGun->SetParticlePosition(pos);
    fParticleGun->SetParticleMomentumDirection(mom);
    fParticleGun->SetParticleMomentum(100. *GeV);
    fParticleGun->SetParticleDefinition(particle);

    /*create a primary vertex at a given point and put primary particles to it*/
    fParticleGun->GeneratePrimaryVertex(anEvent);
}