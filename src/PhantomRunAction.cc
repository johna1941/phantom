#include "PhantomRunAction.hh"

#include "G4Run.hh"
#include "G4Threading.hh"
#include "G4AutoLock.hh"

#include <cassert>
#include <fstream>

PhantomRunAction* PhantomRunAction::fpMasterRunAction = 0;

PhantomRunAction::PhantomRunAction()
: fNPhotons(0)
{
  if (G4Threading::IsWorkerThread()) {
    // Worker thread.  fpMasterRunAction should have been initialised by now.
    assert(fpMasterRunAction);
  } else {
    fpMasterRunAction = this;
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
  G4Mutex runActionMutex = G4MUTEX_INITIALIZER;
}

void PhantomRunAction::EndOfRunAction(const G4Run* run)
{
  G4int nofEvents = run->GetNumberOfEvent();
  if (nofEvents == 0) return;

  G4String runType;
  if (G4Threading::IsWorkerThread()) {
    
    runType = "Local Run-";
    // Merge to master counter
    G4AutoLock lock(&runActionMutex);  // For duration of scope.
    fpMasterRunAction->fNPhotons += fNPhotons;

  } else {
    runType = "Global Run";

    //Print to file: "std::ios::app" adds data onto the end of file
    std::ofstream output("photon_sensitivity.txt", std::ios::app); 
    output << fNPhotons << std::endl;
    output.close();

  }

  G4cout
  << "\n----------------------End of " << runType << "------------------------"
  << "\n The run consists of " << nofEvents << " events."
  << "\n Number of photons reaching the sensitive detector: "
  << fNPhotons
  << "\n------------------------------------------------------------"
  << G4endl;
}
