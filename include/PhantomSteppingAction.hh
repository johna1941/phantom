#ifndef PHANTOMSTEPPINACTION_HH
#define PHANTOMSTEPPINACTION_HH

#include "G4UserSteppingAction.hh"

class PhantomRunAction;

class PhantomSteppingAction : public G4UserSteppingAction
{
public:
  PhantomSteppingAction(PhantomRunAction*);
  virtual ~PhantomSteppingAction();
  virtual void UserSteppingAction(const G4Step*);
private:
  PhantomRunAction* fpRunAction;
};

#endif
