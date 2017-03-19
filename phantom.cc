#include "G4MTRunManager.hh"
#include "PhantomDetectorConstruction.hh"
#include "OpNovicePhysicsList.hh"
#include "PhantomActionInitialization.hh"
#include "G4UIExecutive.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"

int main(int argc,char** argv)
{
  // Do this first to capture all output
  G4UIExecutive* ui = new G4UIExecutive(argc, argv);

  G4RunManager* runManager = new G4MTRunManager;

  runManager->SetUserInitialization(new PhantomDetectorConstruction);

  runManager->SetUserInitialization(new OpNovicePhysicsList);

  runManager->SetUserInitialization(new PhantomActionInitialization);

  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();

  G4UImanager* UImanager = G4UImanager::GetUIpointer();
  UImanager->ApplyCommand("/control/execute vis.mac");

  ui->SessionStart();

  delete ui;
  delete visManager;
  delete runManager;
}
