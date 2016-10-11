#include "PhantomActionInitialization.hh"
#include "PhantomPrimaryGeneratorAction.hh"
//#include "PhantomRunAction.hh"
//#include "PhantomEventAction.hh"
//#include "PhantomSteppingAction.hh"

PhantomActionInitialization::PhantomActionInitialization()
{}

PhantomActionInitialization::~PhantomActionInitialization()
{}

void PhantomActionInitialization::BuildForMaster() const
{
//  PhantomRunAction* runAction = new PhantomRunAction;
//  SetUserAction(runAction);
}

void PhantomActionInitialization::Build() const
{
  SetUserAction(new PhantomPrimaryGeneratorAction);

//  PhantomRunAction* runAction = new PhantomRunAction;
//  SetUserAction(runAction);

//  PhantomEventAction* eventAction = new PhantomEventAction(runAction);
//  SetUserAction(eventAction);

//  SetUserAction(new PhantomSteppingAction(eventAction));
}
