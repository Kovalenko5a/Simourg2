
// 

//..../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......
//..../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......

#include "SimourgDetectorHit.h"
#include "SimourgGlobal.h"

extern SimourgGlobal gl;
G4Allocator<SimourgDetectorHit> SimourgDetectorHitAllocator;

//..../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......

SimourgDetectorHit::SimourgDetectorHit()
{
   EdepAbs = 0.; TrackLengthAbs = 0.;
   if (gl.is1stDetHit)
   {
     gl.TimeStampDetHit = "Executing " __FILE__ " (" __TIMESTAMP__ ") (compiled " __DATE__ " " __TIME__ ")";
     gl.is1stDetHit = false; // only first DetectorHit in the experiment
   }
}

//..../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\.....

SimourgDetectorHit::~SimourgDetectorHit()
{}

//..../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......

SimourgDetectorHit::SimourgDetectorHit(const SimourgDetectorHit& right)
{
  EdepAbs = right.EdepAbs; TrackLengthAbs = right.TrackLengthAbs;
}

//..../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......

const SimourgDetectorHit& SimourgDetectorHit::operator=(const SimourgDetectorHit& right)
{
  EdepAbs = right.EdepAbs; TrackLengthAbs = right.TrackLengthAbs;
  return *this;
}

//..../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......

int SimourgDetectorHit::operator==(const SimourgDetectorHit& right) const
{
  return 0;
}

//..../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......

void SimourgDetectorHit::Draw()
{}

//..../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......

void SimourgDetectorHit::Print()
{}

//..../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......

