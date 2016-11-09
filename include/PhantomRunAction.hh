#ifndef PhantomRunAction_h
#define PhantomRunAction_h

#include "G4UserRunAction.hh"

class G4Run;

class PhantomRunAction : public G4UserRunAction
{
public:
  PhantomRunAction();
  virtual ~PhantomRunAction();

  virtual void BeginOfRunAction(const G4Run*);
  virtual void   EndOfRunAction(const G4Run*);
  
  void IncrementPhotonCount() {++fNPhotons;}
  void SetOutside() {foutside = 1;}
  G4int GetOutside() {return foutside;}

private:
  static PhantomRunAction* fpMasterRunAction;
  G4int fNPhotons;
  G4int foutside;
};

#endif

