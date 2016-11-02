#include "PhantomDetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Orb.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4VisAttributes.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "PhantomSensitiveDetector.hh"
#include "PhantomRunAction.hh"
#include "G4SDManager.hh"

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

  // Materials
  G4NistManager* nist = G4NistManager::Instance();
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
  //  G4Material* env_mat = nist->FindOrBuildMaterial("G4_WATER");
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

  // Optical properties
  G4double photonEnergyRI[] =
  { 2.034*eV, 2.068*eV, 2.103*eV, 2.139*eV,
    2.177*eV, 2.216*eV, 2.256*eV, 2.298*eV,
    2.341*eV, 2.386*eV, 2.433*eV, 2.481*eV,
    2.532*eV, 2.585*eV, 2.640*eV, 2.697*eV,
    2.757*eV, 2.820*eV, 2.885*eV, 2.954*eV,
    3.026*eV, 3.102*eV, 3.181*eV, 3.265*eV,
    3.353*eV, 3.446*eV, 3.545*eV, 3.649*eV,
    3.760*eV, 3.877*eV, 4.002*eV, 4.136*eV }; //32
  G4double refractiveIndex[] =
  { 1.3435, 1.3440,  1.3445, 1.3450, 1.3455, //5
    1.3460, 1.3465,  1.3470, 1.3475, 1.3480, //10
    1.3485, 1.3492,  1.3500, 1.3505, 1.3510, //15
    1.3518, 1.3522,  1.3530, 1.3535, 1.3540, //20
    1.3545, 1.3550,  1.3555, 1.3560, 1.3568, //25
    1.3572, 1.3580,  1.3585, 1.3590, 1.3595, //30
    1.3600, 1.3608}; // 32
  // Values from EJ301-em.xls data table. To be incorporated...
  G4double photonEnergySF[] =
  { 3.108*eV, 3.089*eV, 3.069*eV, 3.051*eV,
    3.039*eV, 3.032*eV, 3.022*eV, 3.014*eV,
    2.995*eV, 2.988*eV, 2.981*eV, 2.974*eV,
    2.967*eV, 2.963*eV, 2.960*eV, 2.956*eV,
    2.952*eV, 2.946*eV, 2.939*eV, 2.935*eV,
    2.932*eV, 2.928*eV, 2.925*eV, 2.922*eV,
    2.918*eV, 2.908*eV, 2.891*eV, 2.882*eV,
    2.872*eV, 2.868*eV, 2.865*eV, 2.858*eV,
    2.841*eV, 2.825*eV, 2.820*eV, 2.814*eV,
    2.803*eV, 2.794*eV, 2.781*eV, 2.771*eV,
    2.763*eV, 2.747*eV, 2.732*eV, 2.717*eV,
    2.702*eV, 2.673*eV, 2.645*eV, 2.617*eV,
    2.590*eV, 2.563*eV, 2.537*eV, 2.511*eV,
    2.486*eV, 2.462*eV, 2.438*eV, 2.414*eV,
    2.391*eV }; //57
  G4double scintilFast[] =
  { 0.052, 0.078, 0.119, 0.168,
    0.210, 0.255, 0.353, 0.455,
    0.727, 0.797, 0.853, 0.892,
    0.925, 0.936, 0.948, 0.958,
    0.967, 0.981, 0.991, 0.996,
    1.000, 0.997, 0.993, 0.986,
    0.969, 0.895, 0.799, 0.762,
    0.729, 0.724, 0.721, 0.711,
    0.708, 0.704, 0.701, 0.697,
    0.680, 0.662, 0.632, 0.598,
    0.554, 0.490, 0.438, 0.401,
    0.364, 0.312, 0.273, 0.238,
    0.208, 0.183, 0.158, 0.136,
    0.119, 0.104, 0.092, 0.080,
    0.070 }; //57
  G4double absorption[] =  // Quoted to be 2.5-3m bulk absorption, we'll assume worst case.
  { 2.5*m, 2.5*m, 2.5*m, 2.5*m, 2.5*m, //5
    2.5*m, 2.5*m, 2.5*m, 2.5*m, 2.5*m, //10
    2.5*m, 2.5*m, 2.5*m, 2.5*m, 2.5*m, //15
    2.5*m, 2.5*m, 2.5*m, 2.5*m, 2.5*m, //20
    2.5*m, 2.5*m, 2.5*m, 2.5*m, 2.5*m, //25
    2.5*m, 2.5*m, 2.5*m, 2.5*m, 2.5*m, //30
    2.5*m, 2.5*m, 2.5*m, 2.5*m, 2.5*m, //35
    2.5*m, 2.5*m, 2.5*m, 2.5*m, 2.5*m, //40
    2.5*m, 2.5*m, 2.5*m, 2.5*m, 2.5*m, //45
    2.5*m, 2.5*m, 2.5*m, 2.5*m, 2.5*m, //50
    2.5*m, 2.5*m, 2.5*m, 2.5*m, 2.5*m, //55
    2.5*m, 2.5*m}; //57

  // Properties of liquid scintillator bulk medium
  const G4int nEntriesSF = sizeof(photonEnergySF)/sizeof(G4double);
  const G4int nEntriesRI = sizeof(photonEnergyRI)/sizeof(G4double);
  // Create material properties table and add properties
  G4MaterialPropertiesTable* scint_mpt = new G4MaterialPropertiesTable();
  // Add to material properties table
  scint_mpt->AddProperty("RINDEX",       photonEnergyRI, refractiveIndex, nEntriesRI)
  ->SetSpline(true);
  scint_mpt->AddProperty("ABSLENGTH",    photonEnergySF,   absorption,      nEntriesSF)
  ->SetSpline(true);
  scint_mpt->AddProperty("FASTCOMPONENT",photonEnergySF,   scintilFast,     nEntriesSF)
  ->SetSpline(true);
  scint_mpt->AddConstProperty("SCINTILLATIONYIELD",12000/MeV);
  scint_mpt->AddConstProperty("RESOLUTIONSCALE",1.0);
  scint_mpt->AddConstProperty("FASTTIMECONSTANT", 3.2*ns); // Given to be 3.2ns in EJ-301 PDF
  //scint_mpt->AddConstProperty("SLOWTIMECONSTANT",32.3*ns); // "First three components; 3.2, 32.3, 270...?"
  //scint_mpt->AddConstProperty("YIELDRATIO",0.8); // Relative strength of the fast vs. slow, i.e. 80% scintillations are fast.
  G4cout << "Scint G4MaterialPropertiesTable\n"; scint_mpt->DumpTable();
  // Associate material properties table with the liquid scintillator material
  LS->SetMaterialPropertiesTable(scint_mpt);

  // Optical properties of the surface of the scintillator
  G4double photonEnergyRe[] =
  { 3.315*eV, 3.261*eV, 3.208*eV, 3.157*eV,
    3.108*eV, 3.060*eV, 3.014*eV, 2.925*eV,
    2.841*eV, 2.763*eV, 2.688*eV, 2.617*eV,
    2.550*eV, 2.486*eV, 2.426*eV, 2.368*eV,
    2.313*eV, 2.260*eV, 2.210*eV, 2.162*eV,
    2.116*eV, 2.072*eV };

//  G4double scale = 0.01;
  G4double scale = 1.;
  G4double reflectivity[] =
   {scale*0.7000, scale*0.8000, scale*0.8700, scale*0.8990,
    scale*0.9200, scale*0.9340, scale*0.9450, scale*0.9550,
    scale*0.9575, scale*0.9600, scale*0.9620, scale*0.9625,
    scale*0.9640, scale*0.9640, scale*0.9640, scale*0.9650,
    scale*0.9650, scale*0.9650, scale*0.9650, scale*0.9645,
    scale*0.9630, scale*0.9620 };

  G4OpticalSurface* scint_surface = new G4OpticalSurface("scint-surface");
  scint_surface->SetType(dielectric_dielectric); // If both surfaces have refractive properties added, this will actually calculate reflection for us
  scint_surface->SetFinish(groundfrontpainted);
  scint_surface->SetModel(unified);
  const G4int nEntriesRe = sizeof(photonEnergyRe)/sizeof(G4double);
  assert(sizeof(reflectivity) == sizeof(photonEnergyRe));
  G4MaterialPropertiesTable* mptForSkin = new G4MaterialPropertiesTable();
  mptForSkin->AddProperty("REFLECTIVITY", photonEnergyRe, reflectivity, nEntriesRe) // Takes photonEnergy, nEntries from liquid scint above. Looks like this is instead of using rindex of a new surface
  ->SetSpline(true);
  G4cout << "Skin G4MaterialPropertiesTable\n"; mptForSkin->DumpTable();
  // Associates the material properties with the surface of the liquid scintillator.
  scint_surface->SetMaterialPropertiesTable(mptForSkin);

  name = "World";
  G4VSolid* world = new G4Box(name,12.*cm,12.*cm,18.*cm);
  G4LogicalVolume* world_log = new G4LogicalVolume(world,world_mat,name);
  world_log->SetVisAttributes(G4VisAttributes::GetInvisible());
  G4VPhysicalVolume* physWorld = new G4PVPlacement(G4Transform3D(),world_log,name,0,false,0);

  name = "Orb";
  G4VSolid* scint = new G4Orb(name, 10.*cm);
  G4LogicalVolume* scint_log = new G4LogicalVolume(scint,LS,name);
  new G4PVPlacement(G4Transform3D(),scint_log,name,world_log,false,0,checkOverlaps);
  new G4LogicalSkinSurface("scint_surface", scint_log, scint_surface);

  name = "Fibre";
  G4VSolid* fibre = new G4Tubs(name,0.,1.*cm,1.*mm,0.,twopi);
  fpFibre_log = new G4LogicalVolume(fibre,LS,name);
  new G4PVPlacement(G4Translate3D(0.,0.,9.5*cm),fpFibre_log,name,scint_log,false,0,checkOverlaps);

  return physWorld;
}

void PhantomDetectorConstruction::ConstructSDandField()
{
//  PhantomRunAction* pRunAction =
//  const_cast<PhantomRunAction*>
//  (static_cast<const PhantomRunAction*>
//   (G4RunManager::GetRunManager()->GetUserRunAction()));
//
//  G4VSensitiveDetector* fibreSD = new PhantomSensitiveDetector("Fibre",pRunAction);
//
//  G4SDManager* pSDman = G4SDManager::GetSDMpointer();
//  pSDman->AddNewDetector(fibreSD);
//  fpFibre_log->SetSensitiveDetector(fibreSD);
}

