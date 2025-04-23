
#ifndef SimourgPrimaryGeneratorAction_h
#define SimourgPrimaryGeneratorAction_h 1


#include <stdio.h>
#include <fstream>

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4NucleusLimits.hh"
#include "G4RadioactiveDecay.hh"

class G4ParticleGun;
class G4Event;

class SimourgPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    SimourgPrimaryGeneratorAction();
    ~SimourgPrimaryGeneratorAction();

  public:
    void GeneratePrimaries(G4Event* anEvent);

  private:
    G4ParticleGun* particleSource;
		G4int A, Z; // ion

};

#endif

