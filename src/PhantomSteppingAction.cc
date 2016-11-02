#include "PhantomSteppingAction.hh"

#include "globals.hh"

PhantomSteppingAction::PhantomSteppingAction()
{}

PhantomSteppingAction::~PhantomSteppingAction()
{}

void PhantomSteppingAction::UserSteppingAction(const G4Step* /*step*/)
{
  G4cout << "PhantomSteppingAction::UserSteppingAction" << G4endl;
}
