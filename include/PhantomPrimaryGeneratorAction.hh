#ifndef PhantomPrimaryGeneratorAction_h
#define PhantomPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"

class G4GeneralParticleSource;

class PhantomPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  PhantomPrimaryGeneratorAction();
  virtual ~PhantomPrimaryGeneratorAction();

  // method from the base class
  virtual void GeneratePrimaries(G4Event*);

private:
  G4GeneralParticleSource*  fParticleGun;
};

#endif
