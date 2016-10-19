#include "PhantomRunAction.hh"

#include "G4Run.hh"
#include "G4AccumulableManager.hh"

PhantomRunAction::PhantomRunAction()
: fNPhotons(0)
{
  // Register accumulable to the accumulable manager
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->RegisterAccumulable(fNPhotons);
}

PhantomRunAction::~PhantomRunAction()
{}

void PhantomRunAction::BeginOfRunAction(const G4Run*)
{
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Reset();
}

void PhantomRunAction::EndOfRunAction(const G4Run* run)
{
  G4int nofEvents = run->GetNumberOfEvent();
  if (nofEvents == 0) return;

  // Merge accumulables
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Merge();

  G4String runType;
  if (IsMaster()) {
    runType = "Global Run";
  } else {
    runType = "Local Run-";
  }

  G4cout
  << "\n----------------------End of " << runType << "------------------------"
  << "\n The run consists of " << nofEvents << " events."
  << "\n Number of photons reaching the sensitive detector: "
  << fNPhotons.GetValue()
  << "\n------------------------------------------------------------"
  << G4endl;
}
