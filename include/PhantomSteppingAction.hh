#ifndef PHANTOMSTEPPINACTION_HH
#define PHANTOMSTEPPINACTION_HH

#include "G4UserSteppingAction.hh"

class PhantomSteppingAction : public G4UserSteppingAction
{
public:
  PhantomSteppingAction();
  virtual ~PhantomSteppingAction();
  virtual void UserSteppingAction(const G4Step*);
};

#endif
