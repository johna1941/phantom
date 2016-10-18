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
#include "G4OpticalSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4LogicalBorderSurface.hh"

PhantomDetectorConstruction::PhantomDetectorConstruction()
{ }

PhantomDetectorConstruction::~PhantomDetectorConstruction()
{ }

G4VPhysicalVolume* PhantomDetectorConstruction::Construct()
{  
  // Useful names
  G4String name, symbol;
  G4double density;
  G4int ncomponents, natoms;
  G4double fractionmass;
  //  G4UnitDefinition::BuildUnitsTable();  ??
  G4bool checkOverlaps = true;

  G4NistManager* nist = G4NistManager::Instance();
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
  G4Material* env_mat = nist->FindOrBuildMaterial("G4_WATER");
  G4Element* C = nist->FindOrBuildElement("C");
  G4Element* H = nist->FindOrBuildElement("H");
  G4Element* N = nist->FindOrBuildElement("N");
  //Styrene
  G4Material* styrene = new G4Material(name = "Styrene", density=0.909*g/cm3, ncomponents=2);
  styrene->AddElement(C, natoms=8);
  styrene->AddElement(H, natoms=8);
  //1,3-Butadiene
  density = 0.6149*g/cm3; // At 25\degree (solid)
  G4Material* buta = new G4Material(name = "1,3-Butadiene", density, ncomponents=2);
  buta->AddElement(C, natoms=4);
  buta->AddElement(H, natoms=6);
  //Acrylonitrile
  G4Material* acryl = new G4Material(name = "Acrylonitrile", density=0.81*g/cm3, ncomponents=3);
  acryl->AddElement(C, natoms=3);
  acryl->AddElement(H, natoms=3);
  acryl->AddElement(N, natoms=1);
  // ABS
  density = 1.08*g/cm3; //1.06-1.08, according to wikipedia
  G4Material* ABS = new G4Material(name = "ABS", density, ncomponents=3);
  ABS->AddMaterial(styrene, fractionmass=55*perCent); // 40-60%
  ABS->AddMaterial(buta, fractionmass=20*perCent); // 5-30%
  ABS->AddMaterial(acryl, fractionmass=25*perCent); //15-35%
  ////////// Construct LiqScint //////////
  // The atomic composition of our liquid scintillator is simply given as a
  // ratio of H:C (1.33), since there are no other molecules and its simply a
  // percentage mixture of two hydrocarbons
  density = 1.136*g/cm3;
  G4Material* LS = new G4Material(name = "LS", density, ncomponents=2);
  LS->AddElement(C, natoms=3);
  LS->AddElement(H, natoms=4);

  name = "World";
  G4VSolid* world = new G4Box(name,12.*cm,12.*cm,18.*cm);
  G4LogicalVolume* world_log = new G4LogicalVolume(world,world_mat,name);
  world_log->SetVisAttributes(G4VisAttributes::GetInvisible());
  G4VPhysicalVolume* physWorld = new G4PVPlacement(G4Transform3D(),world_log,name,0,false,0);

  name = "Orb";
  G4VSolid* env = new G4Orb(name, 10.*cm);
  G4LogicalVolume* env_log = new G4LogicalVolume(env,LS,name);
  new G4PVPlacement(G4Transform3D(),env_log,name,world_log,false,0,checkOverlaps);

  return physWorld;
}
