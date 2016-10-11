#ifndef PhantomDetectorConstruction_h
#define PhantomDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

class PhantomDetectorConstruction : public G4VUserDetectorConstruction
{
public:
  PhantomDetectorConstruction();
  virtual ~PhantomDetectorConstruction();

  virtual G4VPhysicalVolume* Construct();
};

#endif

