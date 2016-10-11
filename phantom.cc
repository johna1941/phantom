#include "G4RunManager.hh"
#include "PhantomDetectorConstruction.hh"
#include "QBBC.hh"
#include "PhantomActionInitialization.hh"
#include "G4UIExecutive.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
int main(int argc,char** argv)
{
  G4UIExecutive* ui = new G4UIExecutive(argc, argv);
  G4RunManager* runManager = new G4RunManager;
  runManager->SetUserInitialization(new PhantomDetectorConstruction);
  runManager->SetUserInitialization(new QBBC);
  runManager->SetUserInitialization(new PhantomActionInitialization);
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();
  ui->SessionStart();
  delete ui;
  delete visManager;
  delete runManager;
}
