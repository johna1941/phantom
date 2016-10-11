#include "G4RunManager.hh"
#include "B1DetectorConstruction.hh"
#include "QBBC.hh"
#include "B1ActionInitialization.hh"
#include "G4UImanager.hh"int main(int argc,char** argv)
{
  G4UIExecutive* ui = new G4UIExecutive(argc, argv);
  G4RunManager* runManager = new G4RunManager;
  runManager->SetUserInitialization(new B1DetectorConstruction);
  runManager->SetUserInitialization(new QBBC);
  runManager->SetUserInitialization(new B1ActionInitialization);
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();
  ui->SessionStart();
  delete ui;
  delete visManager;
  delete runManager;
}
