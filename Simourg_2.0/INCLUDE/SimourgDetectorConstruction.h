
#ifndef SimourgDetectorConstruction_H
#define SimourgDetectorConstruction_H 1

//#include "defs.h"

class G4VPhysicalVolume;

#include "G4VUserDetectorConstruction.hh"

class SimourgDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    SimourgDetectorConstruction();
    ~SimourgDetectorConstruction();

  public:
    G4VPhysicalVolume* Construct();
    std::map<G4String, G4LogicalVolume*> logicalVolumeMap;

};

#endif

