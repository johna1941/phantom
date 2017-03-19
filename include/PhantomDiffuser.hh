#ifndef PHANTOMDIFFUSER_HH
#define PHANTOMDIFFUSER_HH

#include "G4VDiscreteProcess.hh"

class PhantomDiffuser : public G4VDiscreteProcess
{
public:
  PhantomDiffuser(const G4String&);
  ~PhantomDiffuser();
  virtual G4bool IsApplicable(const G4ParticleDefinition&);
  virtual G4double PostStepGetPhysicalInteractionLength
  (const G4Track&,G4double previousStepSize,G4ForceCondition* condition);
  virtual G4VParticleChange* PostStepDoIt(const G4Track&, const G4Step&);
  virtual G4double GetMeanFreePath(const G4Track&,G4double,G4ForceCondition*)
  {return 0.;};     // it is not needed here !
private:
  const G4VPhysicalVolume* fpScint_phys;
  const G4VPhysicalVolume* fpFibre_phys;
};

#endif
