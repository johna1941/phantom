#include "PhantomRunAction.hh"

#include "G4Run.hh"
#include "G4Threading.hh"
#include "G4AutoLock.hh"
#include <cassert>

namespace {
  PhantomRunAction* pMasterRunAction = 0;
}

PhantomRunAction::PhantomRunAction()
: fNPhotons(0)
{
  if (G4Threading::IsMasterThread()) {
    pMasterRunAction = this;
  } else {
    // Worker thread.  pMasterRunAction should have been initialised by now.
    assert(pMasterRunAction);
  }
}

PhantomRunAction::~PhantomRunAction()
{}

void PhantomRunAction::BeginOfRunAction(const G4Run*)
{
  fNPhotons = 0;
}

void PhantomRunAction::IncrementPhotonCount()
{
  ++fNPhotons;
}

namespace {
  //Mutex to lock master when merging accumulables
  G4Mutex runActionMutex = G4MUTEX_INITIALIZER;
}

void PhantomRunAction::EndOfRunAction(const G4Run* run)
{
  G4int nofEvents = run->GetNumberOfEvent();
  if (nofEvents == 0) return;

  G4String runType;
  if (G4Threading::IsMasterThread()) {
    runType = "Global Run";
  } else {
    runType = "Local Run-";
    // Merge to master counter
    G4AutoLock lock(&runActionMutex);
    pMasterRunAction->fNPhotons += fNPhotons;
    lock.unlock();
  }

  G4cout
  << "\n----------------------End of " << runType << "------------------------"
  << "\n The run consists of " << nofEvents << " events."
  << "\n Number of photons reaching the sensitive detector: "
  << fNPhotons
  << "\n------------------------------------------------------------"
  << G4endl;
}
