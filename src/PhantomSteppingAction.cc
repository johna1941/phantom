#include "PhantomSteppingAction.hh"

#include "PhantomRunAction.hh"
#include "PhantomDetectorConstruction.hh"
#include "G4Track.hh"
#include "G4OpticalPhoton.hh"
#include "G4RunManager.hh"

namespace {
  G4VPhysicalVolume* pFibre_phys = 0;
  G4VPhysicalVolume* scint_phys = 0;
}

PhantomSteppingAction::PhantomSteppingAction(PhantomRunAction* runAction)
: fpRunAction(runAction)
{
  pFibre_phys =
  static_cast<const PhantomDetectorConstruction*>
  (G4RunManager::GetRunManager()->GetUserDetectorConstruction())->
  GetFibrePhys();

  scint_phys =
  static_cast<const PhantomDetectorConstruction*>
  (G4RunManager::GetRunManager()->GetUserDetectorConstruction())->
  GetScintPhys();
}

PhantomSteppingAction::~PhantomSteppingAction()
{}

void PhantomSteppingAction::UserSteppingAction(const G4Step* step)
{
  // If we are ever outside, we don't care about this node at all
  if (fpRunAction->GetOutside() == 0){
    
    // Is the photon in a place it shouldn't be (outside phantom/in ABS)?
    G4StepPoint* postStepPoint = step->GetPostStepPoint();
    //Must be in neither detector nor scintillator
    if (postStepPoint->GetPhysicalVolume() != pFibre_phys && postStepPoint->GetPhysicalVolume() != scint_phys) {
      //This being 1 will print -1 for the total photon count
      fpRunAction->SetOutside();
      return;
    }

    // Is the photon inside the fibre?
    if (postStepPoint->GetPhysicalVolume() != pFibre_phys) return;

    // Is it an optical photon?
    G4Track* track = step->GetTrack();
    const G4ParticleDefinition* pPDef = track->GetParticleDefinition();
    if (pPDef != G4OpticalPhoton::Definition()) return;

    // It's an optical photon entering the fibre
    G4StepPoint* preStepPoint = step->GetPreStepPoint();
    const G4ThreeVector& incomingDirection = preStepPoint->GetMomentumDirection();
    G4ThreeVector z_axis (0., 0., 1.);

    if (incomingDirection * z_axis > 0.92388) {
      fpRunAction->IncrementPhotonCount();
      // Ask the tracking manager to kill it!!!
      track->SetTrackStatus(fStopAndKill);
    } else {
      // What happens to photons not in acceptance cone?  Do they reflect off?
      // Or should we kill these too?  Yes...kill for now
      track->SetTrackStatus(fStopAndKill);
    }

  } else {
    //Kill all tracks from bad nodes
    G4Track* track = step->GetTrack();
    track->SetTrackStatus(fStopAndKill);
  }

  return;
}
