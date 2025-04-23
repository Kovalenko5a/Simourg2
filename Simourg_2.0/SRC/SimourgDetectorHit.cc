
// 

//..../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......
//..../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......

#include "SimourgDetectorHit.h"

G4Allocator<SimourgDetectorHit> SimourgDetectorHitAllocator;

//..../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......

SimourgDetectorHit::SimourgDetectorHit()
{
   EdepAbs = 0.; TrackLengthAbs = 0.;
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

