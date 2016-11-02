#include "PhantomActionInitialization.hh"

#include "PhantomPrimaryGeneratorAction.hh"
#include "PhantomRunAction.hh"
#include "PhantomSteppingAction.hh"

PhantomActionInitialization::PhantomActionInitialization()
{}

PhantomActionInitialization::~PhantomActionInitialization()
{}

void PhantomActionInitialization::BuildForMaster() const
{
  SetUserAction(new PhantomRunAction);
}

void PhantomActionInitialization::Build() const
{
  SetUserAction(new PhantomPrimaryGeneratorAction);
  SetUserAction(new PhantomRunAction);
  SetUserAction(new PhantomSteppingAction);
}
