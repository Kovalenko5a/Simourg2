
// 

//..../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\....
//..../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\....

#ifndef SimourgSensDet_h
#define SimourgSensDet_h 1

#include "G4VSensitiveDetector.hh"
#include "globals.hh"

class SimourgDetectorConstruction;
class G4HCofThisEvent;
class G4Step;
#include "SimourgDetectorHit.h"

//..../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\....

class SimourgSensDet : public G4VSensitiveDetector
{
  public:

      SimourgSensDet(G4String, SimourgDetectorConstruction* );
     ~SimourgSensDet();

      void Initialize(G4HCofThisEvent*);
      G4bool ProcessHits(G4Step*,G4TouchableHistory*);
      void EndOfEvent(G4HCofThisEvent*);
      void clear();
      void DrawAll();
      void PrintAll();

      static G4int numOfHit;
	    static G4int numOfEvents;
	    static G4double EOfHit;
      
  private:
      
      SimourgDetectorHitsCollection*  DetCollection;      
      SimourgDetectorConstruction* Detector;
      G4int HitID;
      G4String fName;
};
 
#endif

