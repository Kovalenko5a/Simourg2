
//..../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......
//..../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......

#include "SimourgSensDet.h"

#include "SimourgDetectorHit.h"
#include "SimourgDetectorConstruction.h"

#include "G4VPhysicalVolume.hh"
#include "G4Step.hh"
#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"
#include "G4SDManager.hh"

#include "G4ios.hh"

#include "SimourgGlobal.h"

extern SimourgGlobal gl;

//..../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......
G4int SimourgSensDet::numOfHit = 0;
G4int SimourgSensDet::numOfEvents = 0;
G4double SimourgSensDet::EOfHit = 0;



SimourgSensDet::SimourgSensDet(G4String name,
                                   SimourgDetectorConstruction* det)
:G4VSensitiveDetector(name),Detector(det)
{
  gl.TimeStampSensDet = "Executing " __FILE__ " (compiled " __DATE__ " " __TIME__ ")";

  collectionName.insert("DetCollection");
  G4int HitID;
  fName = name;
  
}

//..../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......

SimourgSensDet::~SimourgSensDet()
{
}

//..../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......

void SimourgSensDet::Initialize(G4HCofThisEvent* HCE)
{
  DetCollection = new SimourgDetectorHitsCollection
                      (SensitiveDetectorName,collectionName[0]); 
  HitID = -1;
  gl.EdepDetect[fName] =0;
  
}

//..../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......

G4bool SimourgSensDet::ProcessHits(G4Step* aStep,G4TouchableHistory* ROhist)
{
  G4double edep = aStep->GetTotalEnergyDeposit();
//   G4cout << " Volume name " << fName  << " Edep " << edep << G4endl;
  G4double stepl = 0.;
	G4double partCharge = aStep->GetTrack()->GetDefinition()->GetPDGCharge();
  if (partCharge != 0.)
      stepl = aStep->GetStepLength();
      
  if ((edep==0.)&&(stepl==0.)) return false;      

  G4TouchableHistory* theTouchable
    = (G4TouchableHistory*)(aStep->GetPreStepPoint()->GetTouchable());
    
  G4VPhysicalVolume* physVol = theTouchable->GetVolume(); 
/////////HIT COLLECTION	(not needed?)
	if (HitID == -1) gl.tFirstHit = 0;// aStep->GetPostStepPoint()->GetGlobalTime();
	G4double globalTimeSince1stHit = aStep->GetPostStepPoint()->GetGlobalTime() - gl.tFirstHit; // in order to start time counting from the first hit
	if( globalTimeSince1stHit >= gl.tMin && globalTimeSince1stHit <= gl.tMax)
	{

		if (HitID==-1)
		{
			SimourgDetectorHit* DetectorHit = new SimourgDetectorHit();
			DetectorHit->AddAbs(edep,stepl);
			HitID = DetCollection->insert(DetectorHit) - 1;
			if (verboseLevel > 0 || gl.VerboseAll > 0)
			{
				G4cout << "### New Detector Hit! At t =" << globalTimeSince1stHit / s << " s, E = " << edep / MeV << " MeV";
				if (partCharge > 1.5) G4cout << ", Eobs = " << gl.AlphaBeta * edep / MeV << " MeV (alpha)";
				G4cout << G4endl;
			}
		} else 
		{ 
			(*DetCollection)[HitID]->AddAbs(edep,stepl);
			if (verboseLevel > 0 || gl.VerboseAll > 0)
			{
				G4cout << "### Energy released in Detector! At t =" << globalTimeSince1stHit / s << " s, E = " << edep / MeV << " MeV";
				if (partCharge > 1.5) G4cout << ", Eobs = " << gl.AlphaBeta * edep / MeV << " MeV (alpha)";
				G4cout << G4endl;
			}
		}

		++numOfEvents;
		if( (numOfEvents % gl.Step == 0) && (gl.VerboseAll > 0) )
		{
			  G4cout << "### numOfEvents=" << numOfEvents << " E=" << edep  << " Volume name " << fName << G4endl;
		}
/////////////////////////////////


		

/////////Save energy deposition globaly
		// G4cout << "### numOfEvent = " << numOfEvents << " Edep =" << edep  << " Volume name " << fName << G4endl;
		if(partCharge <1.5)
		{
			EOfHit += edep; // not alpha particle
			gl.EdepDetect[fName]+=edep;
		} else {
			EOfHit += edep * gl.AlphaBeta; // alpha particle
			gl.EdepDetect[fName] +=edep;
		}
	} else 
	{
		if (verboseLevel > 0 || gl.VerboseAll > 0)
		{
			G4cout << "### Energy released in Detector is out of time! At t =" << globalTimeSince1stHit / s << " s, E = " << edep / MeV << " MeV";
			if (partCharge > 1.5) G4cout << ", Eobs = " << gl.AlphaBeta * edep / MeV << " MeV (alpha)";
			G4cout << G4endl;
		}
	}
  return true;
}

//..../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......

void SimourgSensDet::EndOfEvent(G4HCofThisEvent* HCE)
{
/////////HIT COLLECTION CONTINUE	(not needed?)
  static G4int HCID = -1;
  if(HCID<0)
  { HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]); }
  HCE->AddHitsCollection(HCID,DetCollection);
/////////////
	


}

//..../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......

void SimourgSensDet::clear()
{} 

//..../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......

void SimourgSensDet::DrawAll()
{} 

//..../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......

void SimourgSensDet::PrintAll()
{} 

//..../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......

