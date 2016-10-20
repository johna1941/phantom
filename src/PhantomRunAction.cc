#include "PhantomRunAction.hh"

#include "G4Run.hh"
#include "G4Threading.hh"
#include "G4AutoLock.hh"

namespace {
  PhantomRunAction* pMasterRunAction = 0;
}

PhantomRunAction::PhantomRunAction()
: fpMasterRunAction(0)
, fNPhotons(0)
{
  if (G4Threading::IsMasterThread()) {
    pMasterRunAction = this;
  }
  fpMasterRunAction = pMasterRunAction;
}

PhantomRunAction::~PhantomRunAction()
{}

void PhantomRunAction::BeginOfRunAction(const G4Run*)
{
  fNPhotons = 0;
}

namespace {
  //Mutex to lock master when merging accumulables
  G4Mutex mergeMutex = G4MUTEX_INITIALIZER;
}

void PhantomRunAction::IncrementPhotonCount()
{
  ++fNPhotons;
  // Increment master counter too
  G4AutoLock lock(&mergeMutex);
  ++(fpMasterRunAction->fNPhotons);
  lock.unlock();
}

void PhantomRunAction::EndOfRunAction(const G4Run* run)
{
  G4int nofEvents = run->GetNumberOfEvent();
  if (nofEvents == 0) return;

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
  << fNPhotons
  << "\n------------------------------------------------------------"
  << G4endl;
}
