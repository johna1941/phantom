#ifndef PhantomRunAction_h
#define PhantomRunAction_h

#include "G4UserRunAction.hh"

#include "G4Accumulable.hh"

class G4Run;

class PhantomRunAction : public G4UserRunAction
{
public:
  PhantomRunAction();
  virtual ~PhantomRunAction();

  virtual void BeginOfRunAction(const G4Run*);
  virtual void   EndOfRunAction(const G4Run*);
  
  void IncrementPhotonCount() {fNPhotons += 1;}

private:
  G4Accumulable<G4int> fNPhotons;
};

#endif

