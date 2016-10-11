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
  G4Material* shape1_mat = nist->FindOrBuildMaterial("G4_A-150_TISSUE");
  G4Material* shape2_mat = nist->FindOrBuildMaterial("G4_BONE_COMPACT_ICRU");

  G4VSolid* world = new G4Box("World",12.*cm,12.*cm,18.*cm);
  G4LogicalVolume* world_log = new G4LogicalVolume(world,world_mat,"World");
  world_log->SetVisAttributes(G4VisAttributes::GetInvisible());
  G4VPhysicalVolume* physWorld = new G4PVPlacement(G4Transform3D(),world_log,"World",0,false,0);

  G4VSolid* env = new G4Box("Envelope", 10.*cm, 10.*cm, 15.*cm);
  G4LogicalVolume* env_log = new G4LogicalVolume(env,env_mat,"Envelope");
  new G4PVPlacement(G4Transform3D(),env_log,"Envelope",world_log,false,0);

  G4VSolid* shape1 = new G4Cons("Shape1",0.,2.*cm,0.,4.*cm,3.*cm,0.,twopi);
  G4LogicalVolume* shape1_log = new G4LogicalVolume(shape1,shape1_mat,"Shape1");
  new G4PVPlacement(G4Translate3D(0,2*cm,-7*cm),shape1_log,"Shape1",env_log,false,0);

  G4VSolid* shape2 = new G4Trd("Shape2",6.*cm,6.*cm,5.*cm,8.*cm,3.*cm);
  G4LogicalVolume* shape2_log = new G4LogicalVolume(shape2,shape2_mat,"Shape2");
  new G4PVPlacement(G4Translate3D(0,-1.*cm,7.*cm),shape2_log,"Shape2",env_log,false,0);
                
  return physWorld;
}
