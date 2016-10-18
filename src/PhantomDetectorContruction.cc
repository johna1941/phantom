#include "PhantomDetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4VisAttributes.hh"

PhantomDetectorConstruction::PhantomDetectorConstruction()
{ }

PhantomDetectorConstruction::~PhantomDetectorConstruction()
{ }

G4VPhysicalVolume* PhantomDetectorConstruction::Construct()
{  
  G4NistManager* nist = G4NistManager::Instance();
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
  G4Material* env_mat = nist->FindOrBuildMaterial("G4_WATER");

  G4String name;

  name = "World";
  G4VSolid* world = new G4Box(name,12.*cm,12.*cm,18.*cm);
  G4LogicalVolume* world_log = new G4LogicalVolume(world,world_mat,name);
  world_log->SetVisAttributes(G4VisAttributes::GetInvisible());
  G4VPhysicalVolume* physWorld = new G4PVPlacement(G4Transform3D(),world_log,name,0,false,0);

  name = "Orb";
  G4VSolid* env = new G4Orb(name, 10.*cm);
  G4LogicalVolume* env_log = new G4LogicalVolume(env,env_mat,name);
  new G4PVPlacement(G4Transform3D(),env_log,name,world_log,false,0);

  return physWorld;
}
