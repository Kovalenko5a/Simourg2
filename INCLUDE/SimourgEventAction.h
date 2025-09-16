
#ifndef SimourgEventAction_h
#define SimourgEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class SimourgEventAction : public G4UserEventAction
{
  public:
    SimourgEventAction();
    virtual ~SimourgEventAction();

  public:
    virtual void   BeginOfEventAction(const G4Event*);
    virtual void   EndOfEventAction(const G4Event*);

  private:
    FILE *outputFile;
};
 
#endif


