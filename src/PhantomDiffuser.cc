#include "PhantomDiffuser.hh"

#include "PhantomDetectorConstruction.hh"
#include "G4RunManager.hh"
#include "G4OpticalPhoton.hh"
#include "G4RandomDirection.hh"

PhantomDiffuser::PhantomDiffuser(const G4String& processName)
: G4VDiscreteProcess(processName)
{
  const PhantomDetectorConstruction* phantomDetectorConstruction =
  static_cast<const PhantomDetectorConstruction*>
  (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
  fpScint_phys = phantomDetectorConstruction->GetScintPhys();
  assert(fpScint_phys);
  fpFibre_phys = phantomDetectorConstruction->GetFibrePhys();
  assert(fpFibre_phys);
}

PhantomDiffuser::~PhantomDiffuser() {}

G4bool PhantomDiffuser::IsApplicable(const G4ParticleDefinition& particle)
{
  return (&particle == G4OpticalPhoton::OpticalPhoton());
}

G4double PhantomDiffuser::PostStepGetPhysicalInteractionLength
(const G4Track&,G4double,G4ForceCondition* condition )
{
  // Force tracking to invoke PostStepDoIt at every step
  *condition = Forced;
  return DBL_MAX;
}

G4VParticleChange* PhantomDiffuser::PostStepDoIt(const G4Track& track, const G4Step&)
{
  aParticleChange.Initialize(track);

  // If entering the fibre from the scintialltor or v.v., represent a ground
  // surface by proposing a random direction
  if ((track.GetVolume()==fpScint_phys && track.GetNextVolume()==fpFibre_phys) ||
      (track.GetVolume()==fpFibre_phys && track.GetNextVolume()==fpScint_phys)) {
    aParticleChange.ProposeMomentumDirection(G4RandomDirection());
  }
  
  return &aParticleChange;
}


