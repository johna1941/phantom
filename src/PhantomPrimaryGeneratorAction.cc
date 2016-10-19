#include "PhantomPrimaryGeneratorAction.hh"

#include "G4GeneralParticleSource.hh"

PhantomPrimaryGeneratorAction::PhantomPrimaryGeneratorAction()
{
  fParticleGun  = new G4GeneralParticleSource;
}

PhantomPrimaryGeneratorAction::~PhantomPrimaryGeneratorAction()
{
  delete fParticleGun;
}

void PhantomPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  fParticleGun->GeneratePrimaryVertex(anEvent);
}
