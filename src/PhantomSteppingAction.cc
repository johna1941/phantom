#include "PhantomSteppingAction.hh"

#include "PhantomRunAction.hh"
#include "G4Track.hh"
#include "G4OpticalPhoton.hh"
#include "G4RunManager.hh"

PhantomSteppingAction::PhantomSteppingAction()
{}

PhantomSteppingAction::~PhantomSteppingAction()
{}

void PhantomSteppingAction::UserSteppingAction(const G4Step* step)
{
//  G4cout << "PhantomSteppingAction::UserSteppingAction" << G4endl;

  // Does it enter the fibre?
  G4StepPoint* postStepPoint = step->GetPostStepPoint();
  if (postStepPoint->GetPhysicalVolume()->GetName() != "Fibre") return;
  // Change the above to be a test on a pointer!!!

  // Is it an optical photon?
  G4Track* track = step->GetTrack();
  const G4ParticleDefinition* pPDef = track->GetParticleDefinition();
  if (pPDef != G4OpticalPhoton::Definition()) return;

  // It's an optical photon entering the fibre
  G4StepPoint* preStepPoint = step->GetPreStepPoint();
  const G4ThreeVector& incomingDirection = preStepPoint->GetMomentumDirection();
  G4ThreeVector z_axis (0, 0, 1);
  if (incomingDirection * z_axis > 0.92388) {
    PhantomRunAction* pRunAction =
    const_cast<PhantomRunAction*>
    (static_cast<const PhantomRunAction*>
     (G4RunManager::GetRunManager()->GetUserRunAction()));
    pRunAction->IncrementPhotonCount();
    // Ask the tracking manager to kill it!!!
    track->SetTrackStatus(fStopAndKill);
  } else {
    // What happens to photons not in acceptance cone?  Do they reflect off?
    // Or should we kill these too?  Yes...for now
    track->SetTrackStatus(fStopAndKill);
  }

  return;
}
