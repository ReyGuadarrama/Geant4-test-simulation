#ifndef ACTION_HH
#define ACTION_HH

#include "G4VUserActionInitialization.hh"

#include "generator.hh"

/*G4VUserActionInitialization is the abstract base class for instantiating 
all user action classes. It has a pure virtual method Build() which is invoked 
by G4RunManager for sequential execution,*/
class MyActionInitialization : public G4VUserActionInitialization
{
public:
    MyActionInitialization();
    ~MyActionInitialization();

    virtual void Build() const;
};

#endif