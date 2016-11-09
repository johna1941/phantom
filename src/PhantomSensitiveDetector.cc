#include "PhantomSensitiveDetector.hh"

#include "PhantomRunAction.hh"

#include "G4Step.hh"
#include "G4OpticalPhoton.hh"

PhantomSensitiveDetector::PhantomSensitiveDetector
(const G4String& name,
 PhantomRunAction* pRunAction)
: G4VSensitiveDetector(name)
, fpRunAction(pRunAction)
{}

G4bool PhantomSensitiveDetector::ProcessHits(G4Step* step,
                                             G4TouchableHistory*)
{

/*  G4cout << "PhantomSensitiveDetector::ProcessHits" << G4endl;
  G4Track* track = step->GetTrack();
  const G4ParticleDefinition* pPDef = track->GetParticleDefinition();
  if (pPDef != G4OpticalPhoton::Definition()) {return true;}
  
  G4ThreeVector direction = track->GetMomentumDirection();

  if (direction.z() > 0.92388) {
    fpRunAction->IncrementPhotonCount();
  }

  // Ask the tracking manager to kill it!!!
  track->SetTrackStatus(fStopAndKill);
*/
  return true;
}
