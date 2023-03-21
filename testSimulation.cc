#include <iostream>

//add the necessary headers to perform the simulation
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "construction.hh"
#include "physics.hh"
#include "action.hh"

//main function
int main(int argc, char** argv)
{
    /*create a pointer called runManager using G4RunManager class
    which controls all of states changes */
    G4RunManager *runManager = new G4RunManager();

    /*Initialize our Detector Construction and our Physics list*/
    runManager->SetUserInitialization(new MyDetectorConstruction());
    runManager->SetUserInitialization(new MyPhysicsList());
    runManager->SetUserInitialization(new MyActionInitialization());


    /*This method invokes all the necessary initialization procedures for an
    event loop*/
    runManager->Initialize();
    
    /*create a pointer called ui using G4UIExecutive class
    which helps automatic instantiation of user session
    according to your environment variable*/
    G4UIExecutive *ui = new G4UIExecutive(argc, argv);

    /*create a pointer called visManager using G4VisManager class
    which creates and manages graphics systems, scenes, scenehandlers,
    viewers and some models and model makers*/
    G4VisManager *visManager = new G4VisExecutive();
    visManager->Initialize();

    /*create a pointer called UImanager using the GetUIpointer object 
    from G4UImanager class which controls the command manipulation and 
    the user interface(s)*/
    G4UImanager *UImanager = G4UImanager::GetUIpointer();

    /*Apply commands that allow us to visualize our simulation*/
    UImanager->ApplyCommand("/vis/open OGL");
    UImanager->ApplyCommand("/vis/viewer/set/viewpointVector 1 1 1");
    UImanager->ApplyCommand("/vis/drawVolume");
    UImanager->ApplyCommand("/vis/viewer/set/autoRefresh true");
    UImanager->ApplyCommand("/vis/scene/add/trajectories smooth");
    UImanager->ApplyCommand("/vis/scene/endOfEventAction accumulate");

    /*Start user session from G4UIExective class*/
    ui->SessionStart();

    return 0;
}