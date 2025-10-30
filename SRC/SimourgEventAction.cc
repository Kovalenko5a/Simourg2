
#include <time.h>

// #include <CLHEP/Random/Randomize.h>
#define minZ(a,b)  (((a) < (b)) ? (a) : (b))

#include "SimourgEventAction.h"
 
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4VHitsCollection.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4VVisManager.hh"
#include "G4SDManager.hh"
#include "G4UImanager.hh"
#include "G4ios.hh"
#include "G4UnitsTable.hh"

#include "SimourgSensDet.h"
#include "SimourgGlobal.h"

extern SimourgGlobal gl;

SimourgEventAction::SimourgEventAction()
{
  if (gl.is1stEvAct)
  {
    gl.TimeStampEvAct = "Executing " __FILE__ " (" __TIMESTAMP__ ") (compiled " __DATE__ " " __TIME__ ")";
    gl.is1stEvAct = false; // only first EventAction in the experiment
  }
}

SimourgEventAction::~SimourgEventAction()
{
//	fclose(outputFile);
}

void SimourgEventAction::BeginOfEventAction(const G4Event* evt)
{
  SimourgSensDet::numOfEvents = 0;
  gl.numHits = 0;
	gl.tMinHit = 1.e100;
	gl.tMaxHit = -1.e100;

//===========================
// uncomment if RandomSeed for particle transport should be random:
  //HepRandom::setTheSeed((unsigned)clock());
//===========================

}

void SimourgEventAction::EndOfEventAction(const G4Event* evt)
{
  // extract the trajectories and draw them
// #ifdef G4VIS_USE
  if(gl.DoPicture != 0)
  {
    if (G4VVisManager::GetConcreteInstance())
    {
      G4TrajectoryContainer *trajectoryContainer = evt->GetTrajectoryContainer();
      G4int n_trajectories = 0;
      if (trajectoryContainer) n_trajectories = trajectoryContainer->entries();

      for (G4int i=0; i < minZ(n_trajectories,100); i++)
      { 
        G4Trajectory* trj = (G4Trajectory*)((*(evt->GetTrajectoryContainer()))[i]);
        trj->DrawTrajectory();
      }
    }

  }
// #endif

//   ++SimourgSensDet::numOfHit;
	if (gl.VerboseAll > 0)
	{
		G4cout << "### Event is finished! The number of detector hits is " << gl.numHits << G4endl;
		if (gl.numHits > 0)
		{
			G4cout << "### The first detector hit is at " << (gl.tMinHit / s) << " s, the last hit at " << (gl.tMaxHit / s) << " s." << G4endl;
			G4cout << "### Energy distribution in time:" << G4endl;
			gl.E_ASCII_Distr();
		}
	}
}