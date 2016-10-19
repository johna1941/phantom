#ifndef PHANTOMSENSITIVEDETECTOR_HH
#define PHANTOMSENSITIVEDETECTOR_HH

#include "G4VSensitiveDetector.hh"

class PhantomRunAction;

class PhantomSensitiveDetector : public G4VSensitiveDetector
{
public:
  PhantomSensitiveDetector(const G4String& name,
                           PhantomRunAction*);
  G4bool ProcessHits(G4Step*, G4TouchableHistory*);
private:
  PhantomRunAction* fpRunAction;
};

#endif
