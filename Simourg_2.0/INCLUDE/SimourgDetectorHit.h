

//..../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......
//..../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......

#ifndef SimourgDetectorHit_h
#define SimourgDetectorHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"

//..../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......

class SimourgDetectorHit : public G4VHit
{
 public:

   SimourgDetectorHit();
  ~SimourgDetectorHit();
   SimourgDetectorHit(const SimourgDetectorHit&);
   const SimourgDetectorHit& operator=(const SimourgDetectorHit&);
   int operator==(const SimourgDetectorHit&) const;

   inline void* operator new(size_t);
   inline void  operator delete(void*);

   void Draw();
   void Print();
      
 public:
  
   void AddAbs(G4double de, G4double dl) {EdepAbs += de; TrackLengthAbs += dl;};
//   void AddGap(G4double de, G4double dl) {EdepGap += de; TrackLengthGap += dl;};
                 
   G4double GetEdepAbs()     { return EdepAbs; };
   G4double GetTrakAbs()     { return TrackLengthAbs; };
//   G4double GetEdepGap()     { return EdepGap; };
//   G4double GetTrakGap()     { return TrackLengthGap; };
    
 private:
  
   G4double EdepAbs, TrackLengthAbs;
//   G4double EdepGap, TrackLengthGap;     
};

//..../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......

typedef G4THitsCollection<SimourgDetectorHit> SimourgDetectorHitsCollection;

extern G4Allocator<SimourgDetectorHit> SimourgDetectorHitAllocator;

//..../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......

inline void* SimourgDetectorHit::operator new(size_t)
{
  void* aHit;
  aHit = (void*) SimourgDetectorHitAllocator.MallocSingle();
  return aHit;
}

//..../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......

inline void SimourgDetectorHit::operator delete(void* aHit)
{
  SimourgDetectorHitAllocator.FreeSingle((SimourgDetectorHit*) aHit);
}

//..../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......

#endif

