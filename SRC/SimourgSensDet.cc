
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
  DetCollection = new SimourgDetectorHitsCollection(SensitiveDetectorName,collectionName[0]);
  G4cout <<  SensitiveDetectorName << " SensitiveDetectorName  " << G4endl;
  G4cout <<  fName << " fName  " << G4endl;
  HitID = -1;
  gl.EdepDetect[fName] =0;
  gl.TimeDetect[fName] ={0,0};
  
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
/////////HIT COLLECTION	start
G4double tHit = aStep->GetPostStepPoint()->GetGlobalTime();
// G4double tHit = aStep->GetPreStepPoint()->GetGlobalTime();
	if (tHit < gl.tMinHit) gl.tMinHit = tHit;
	if (gl.tMaxHit < tHit) gl.tMaxHit = tHit;
	gl.tHit[gl.numHits] = tHit;
	gl.eHit[gl.numHits] = (partCharge <= 1) ? edep : edep*gl.AlphaBeta;
	gl.numHits++;
	if (gl.numHits >= LENGTH_HIT_ARR) // to compress arrays if they are overfilled
	{
		for (G4int i = 0; i < (LENGTH_HIT_ARR/2); i++ ) 
		{
			G4int ii = i + i;
			G4int i1 = ii + 1;
			G4double e2 = gl.eHit[ii] + gl.eHit[i1];
			gl.tHit[i] = (gl.tHit[ii] * gl.eHit[ii] + gl.tHit[i1] * gl.eHit[i1]) / e2; // two hittimes are compressed to a single one with weighted (by energies) average time
			gl.eHit[i] = e2;
		}
		gl.numHits = LENGTH_HIT_ARR / 2;
		if (verboseLevel > 0 || gl.VerboseAll > 0)
		{
			G4cout << "### Array of hits for this event is compressed to " << gl.numHits << " points" << G4endl;
		}
	}
	if (HitID == -1) gl.tFirstHit = tHit; //0; 
	G4double globalTime = aStep->GetPostStepPoint()->GetGlobalTime();
	G4double globalTimeSince1stHit = globalTime - gl.tFirstHit; // in order to start time counting from the first hit
		
				G4cout << " IN " << fName << " At a time " << globalTime << " Edep " << edep << G4endl;
	if( 
		1
	// globalTimeSince1stHit >= gl.tMin && globalTimeSince1stHit <= gl.tMax
	)
	{
		G4cout << "### New Detector Hit! At t =" << (globalTime / s) << " s (" << (globalTimeSince1stHit / s) << " s after 1st hit), E = " << edep / MeV << " MeV";
		if (HitID==-1)
		{
			SimourgDetectorHit* DetectorHit = new SimourgDetectorHit();
			DetectorHit->AddAbs(edep,stepl);
			HitID = DetCollection->insert(DetectorHit) - 1;
			if (verboseLevel > 0 || gl.VerboseAll > 0)
			{
				G4cout << "### New Detector Hit! At t =" << (globalTime / s) << " s (" << (globalTimeSince1stHit / s) << " s after 1st hit), E = " << edep / MeV << " MeV";
				if (partCharge > 1) G4cout << ", Eobs = " << gl.AlphaBeta * edep / MeV << " MeV (alpha)";
				G4cout << G4endl;
			}
		} else 
		{ 
			(*DetCollection)[HitID]->AddAbs(edep,stepl);
			if (verboseLevel > 0 || gl.VerboseAll > 0)
			{
				G4cout << "### Energy released in Detector! At t =" << (globalTime / s) << " s (" << (globalTimeSince1stHit / s) << " s after 1st hit), E = " << edep / MeV << " MeV";
				if (partCharge > 1) G4cout << ", Eobs = " << gl.AlphaBeta * edep / MeV << " MeV (alpha)";
				G4cout << G4endl;
			}
		}

/////////HIT COLLECTION end


		

/////////Save energy deposition globaly
		G4double kinEnergy = aStep->GetTrack()->GetKineticEnergy();
		if(aStep->IsFirstStepInVolume()) gl.TimeDetect[fName].first = aStep->GetPreStepPoint()->GetGlobalTime();
		if(aStep->IsLastStepInVolume() || kinEnergy==0) gl.TimeDetect[fName].second = aStep->GetPostStepPoint()->GetGlobalTime();

		// G4cout << "### numOfEvent = " << numOfEvents << " Edep =" << edep  << " Volume name " << fName << G4endl;
		if(partCharge <1.5)
		{
			EOfHit += edep; // not alpha particle
			gl.EdepDetect[fName]+=edep;
			G4cout << " IN " << fName << " At a time " << globalTime << " Edep " << edep << G4endl;
		} else {
			EOfHit += edep * gl.AlphaBeta; // alpha particle
			gl.EdepDetect[fName] +=edep;
			G4cout << " IN " << fName << " At a time " << globalTime << " Edep " << edep << G4endl;
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

