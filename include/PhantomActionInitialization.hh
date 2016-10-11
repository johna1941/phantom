#ifndef PhantomActionInitialization_h
#define PhantomActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

class PhantomActionInitialization : public G4VUserActionInitialization
{
  public:
    PhantomActionInitialization();
    virtual ~PhantomActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
};

#endif

    
