
#include "Randomize.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4UImanager.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"


#include "CLHEP/Random/RandGeneral.h"

#include "SimourgPrimaryGeneratorAction.h"
#include "SimourgSensDet.h"

#include <fstream>
#include <string>

#include "SimourgGlobal.h"

extern SimourgGlobal gl;
//static std::ifstream in( gl.InFileName );

const G4double tan60 = sqrt(3.);
const G4double tan30 = 1./tan60;
const G4double pi3 = pi/3.;

SimourgPrimaryGeneratorAction::SimourgPrimaryGeneratorAction()
{
  gl.TimeStampPriGenAct = "Executing " __FILE__ " (compiled " __DATE__ " " __TIME__ ")";

  if(!gl.isEGamma)
  {
    const G4int sz = 128;
    char buf[sz];
  
    if(!gl.in)
    {
      G4cout << "### " << gl.Decay0FileName << " IS NOT OPEN" << G4endl;
      G4cerr << "### " << gl.Decay0FileName << " IS NOT OPEN" << G4endl;
      exit(1);
    }

    G4cout << "### " << gl.Decay0FileName << "  OPEN" << G4endl;
    G4bool isLLNotFound = true;
    for(G4int iLine=0; iLine<50; iLine++) //scroll the header of the input data file
    {
      gl.in.getline(buf, sz);
      G4String line(buf);
      G4cout << "### " << buf << G4endl;
      if( line.find("First") != G4String::npos ) // the line with "First" is found
      {
        G4cout << "### end of header: line " << iLine << G4endl;
        gl.ScrollLines = iLine+2;    
        gl.in.getline(buf, sz);
        G4cout << "### " << buf << G4endl;
        gl.in.getline(buf, sz);
        G4cout << "### " << buf << G4endl;
        isLLNotFound = false;
        break;
      }
    }
    if(isLLNotFound) G4Exception ("CMOPrimaryGeneratorAction::CMOPrimaryGeneratorAction()",
                            "IOProblem", FatalException,      
                            "### The end of header is not found in the input data file.");
  }
  particleSource = new G4ParticleGun(1);
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
}


SimourgPrimaryGeneratorAction::~SimourgPrimaryGeneratorAction()
{
  delete particleSource;
  //in.close();
}

void SimourgPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  //static std::ifstream SimourgPrimaryGeneratorAction::in( InFileName );

  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();


  G4RotationMatrix rotRand;

  G4double partPos_x,partPos_y,partPos_z; // vertex coordinates
  G4ThreeVector partPos = G4ThreeVector(0,0,0);
  G4double R2xy; // distance^2 from the central axis
  // generate vertex coords:
	int EmergencyCounter = 0;
	bool isXYZUnSrc;
	do
	{ 
		isXYZUnSrc = gl.isUnSrc;
		if(gl.isSrcBox >= 1)
		{  // box source
			partPos_x =  (gl.XL_Src>0) ? (gl.XL_Src*(G4UniformRand()-0.5)) : 0;
	    partPos_y =  (gl.YL_Src>0) ? (gl.YL_Src*(G4UniformRand()-0.5)) : 0;
		}else
		{  // cylindric source

			do // set uniform 2D distribution in the XY plane and select only vertices inside the circle
			{
				partPos_x =  G4UniformRand()-0.5;
	      partPos_y =  G4UniformRand()-0.5;
		    R2xy =  partPos_x*partPos_x + partPos_y*partPos_y;

			} while( R2xy > 0.25 );
			partPos_x *= gl.D_Src;
			partPos_y *= gl.D_Src;
		}
		partPos_x += gl.X_Src;
		partPos_y += gl.Y_Src;

		partPos_z =  (gl.ZL_Src>0) ? (gl.ZL_Src*(G4UniformRand()-0.5)) : 0;
		partPos_z += gl.Z_Src;
		// now, check if (XYZ) is in UnSource
		if(gl.isUnSrc && (gl.isUnSrcBox >= 1) )
		{	// box UnSource
			isXYZUnSrc =		isXYZUnSrc &&
									(partPos_x <= gl.X_UnSrc + gl.XL_UnSrc/2) &&
									(partPos_x >= gl.X_UnSrc - gl.XL_UnSrc/2) &&
									(partPos_y <= gl.Y_UnSrc + gl.YL_UnSrc/2) &&
									(partPos_y >= gl.Y_UnSrc - gl.YL_UnSrc/2) &&
									(partPos_z <= gl.Z_UnSrc + gl.ZL_UnSrc/2) &&
									(partPos_z >= gl.Z_UnSrc - gl.ZL_UnSrc/2);
		} else if (gl.isUnSrc && (gl.isUnSrcBox < 1) )
		{	// cylindric UnSource
			double dx = partPos_x - gl.X_UnSrc;
			double dy = partPos_y - gl.Y_UnSrc;
			isXYZUnSrc  =	isXYZUnSrc &&
									(partPos_z <= gl.Z_UnSrc + gl.ZL_UnSrc/2) &&
									(partPos_z >= gl.Z_UnSrc - gl.ZL_UnSrc/2) &&
									(dx*dx+dy*dy <= gl.UnSrc_Radius2);
		}

		if (++EmergencyCounter >= 1000000)
		{
			G4cout << "### Infinity loop, possibly UnSource contains Source. EmergencyCounter: " << EmergencyCounter << G4endl; 
			exit(1);
		}
	} while (isXYZUnSrc);
  partPos.setX(partPos_x);
  partPos.setY(partPos_y);
  partPos.setZ(partPos_z);

	if(gl.VerboseAll > 2) G4cout << "### partPosition: " << partPos << G4endl 
			<< "### (rho, phi): " << ( partPos.getRho() ) << ", " << ( partPos.getPhi() / deg )  << G4endl;

  G4ThreeVector Polarization, Momentum;
  G4String ParticleName;
  const int sz = 128;
  char buf[sz];

  int iEvt = 0; // number of the event
  double tEvt = 0.; // time of the event
  int nOfPParticles; // number of primary particles generated
  G4int iPartType = 1;
  G4double dPartType, MomX, MomY, MomZ, tPart;
  if(gl.isEGamma)
  {
    do// set uniform 3D distribution in a cube and select only vertices inside a sphere
    {
      MomX = G4UniformRand()-0.5;
      MomY = G4UniformRand()-0.5;
      MomZ = G4UniformRand()-0.5;
    } while (MomX*MomX+MomY*MomY+MomZ*MomZ > 0.25);
    Momentum = ( G4ThreeVector(MomX, MomY, MomZ) ).unit() * gl.EGamma * MeV;
    MomX = Momentum.x();
    MomY = Momentum.y();
    MomZ = Momentum.z();

    dPartType = 1.0; // particle type = 1 (gamma quantum)
    tPart = 0.0; // time of emission is 0
    nOfPParticles = 1;
    iEvt++;
  } else // read from Decay0 file
  {

    gl.in >> iEvt >> tEvt >> nOfPParticles;
    if(gl.in.eof())
    {
      gl.in.clear();
      gl.in.seekg(0); //if EOF, come back to the beginning of the input data file
      for(int iLine=0; iLine<gl.ScrollLines; iLine++) //scrolling the header
      {
        gl.in.getline(buf, sz);
      }
      if(gl.VerboseAll>0) G4cout << "### Input data file finished, starting it again." << G4endl;
      gl.in >> iEvt >> tEvt >> nOfPParticles;

    }
    if(gl.VerboseAll > 0)
    {
      G4cout << "### " << iEvt << " " << tEvt << " " << nOfPParticles << G4endl;
    }
    if(gl.AllowIsotropicRotation!=0)
    {
      G4double randPhi  = twopi*G4UniformRand()*rad; // Phi, Theta -- direction of random axis
      G4double randTheta= (std::acos(2.*G4UniformRand()-1.));
      G4double randPsi  = twopi*G4UniformRand()*rad; // Psi -- random angle of rotation around the axis
      rotRand.set(randPhi,randTheta,randPsi); // random matrix to rotate the event around its vertex
    }
  }
	G4double tCurr=0.;
  for(G4int i=0; i < nOfPParticles; i++) // cycle over the particles in the event
  {
    if (gl.isDecay0) 
    {
      gl.in >> dPartType >> MomX >> MomY >> MomZ >> tPart;
    }
    iPartType = int(dPartType+0.0);
    G4double eLvl = (dPartType - iPartType) * 1000*MeV; 
    // eLvl (energy of a level) is a fractional part of dPartType -- one thousandth is 1 MeV.
    // For example, dPartType 110047.00011759 is for metastable Ag110[117.59 keV] (Z=47, A=110).
		tCurr += tPart*s;
    if(gl.VerboseAll > 0)
    {
      G4cout << "### " << iPartType << "; level " << eLvl << " MeV; " 
        << MomX << " " << MomY << " " << MomZ << " " << tPart;
			/*if(tCurr < gl.tMin || tCurr > gl.tMax) 
			{
				G4cout << " (out of time range! " << gl.tMin/s << " " << tCurr/s << " " << gl.tMax/s << " s)";
			}*/
			G4cout << G4endl;
    }
		//if(tCurr < gl.tMin || tCurr > gl.tMax) continue;
    if (gl.isDecay0) 
    {
      Momentum = G4ThreeVector(MomX, MomY, MomZ) * MeV;
      if(gl.AllowIsotropicRotation!=0)
      {
        Momentum *= rotRand; // rotate the event in random angle around random axis
      }
    }

    if(iPartType == 1)
    {
      ParticleName = "gamma";
      // generate a random orthogonal polarization vector
      G4ThreeVector uP,vP; // orths in a plane orthogonal to Momentum
      uP=( Momentum.orthogonal() ).unit();
      vP=( uP.cross(Momentum)    ).unit();

      G4double phiRnd = twopi*G4UniformRand();
      G4double yRnd = sin(phiRnd);
      G4double xRnd = cos(phiRnd);
      Polarization = uP*xRnd + vP*yRnd;

    } else if(iPartType == 2)
    {
      ParticleName = "e+";
      Polarization = -Momentum.unit(); // For beta-electrons -- 
                                            // polarisation is  RIGHT (positrons -- LEFT)
    } else if(iPartType == 3)
    {
      ParticleName = "e-";
      Polarization = Momentum.unit(); // For beta-electrons -- 
                                            // polarisation is  RIGHT (positrons -- LEFT)
    } else if(iPartType == 5)
    {
      ParticleName = "mu+";
      Polarization = ((G4UniformRand()>0.5) ? 1 : -1) * Momentum.unit(); // For muons -- 
                                            // polarisation is random 
    } else if(iPartType == 6)
    {
      ParticleName = "mu-";
      Polarization = ((G4UniformRand()>0.5) ? 1 : -1) * Momentum.unit(); // For muons -- 
                                            // polarisation is random 
    } else if(iPartType == 13)
    {
      ParticleName = "neutron";
      Polarization = ((G4UniformRand()>0.5) ? 1 : -1) * Momentum.unit(); // For neutrons -- 
                                            // polarisation is random 
    } else if(iPartType == 47)
    {
      
      ParticleName = "alpha";
      Polarization = G4ThreeVector(0,0,0); // For alphas -- 
//                                            // polarisation is ZERO

		} else if(iPartType >= 1000) // nuclide atom, iPartType = A*1000 + Z
		{
			Z = iPartType % 1000;
			A = (iPartType - Z) / 1000;
		} else
    {
      G4cerr << "### Unknown particle type " << iPartType << G4endl;
      G4cerr << "### Bad data in the input data file?" << G4endl;
      exit(1);
    }
    G4ParticleDefinition* particle = (iPartType<1000)	?
																												particleTable->FindParticle(ParticleName)
																											:
                                                        G4IonTable::GetIonTable()->GetIon(Z,A,eLvl);//nucl.excitation energy eLvl
																												//particleTable->GetIonTable()->FindIon(Z,A,eLvl);//nucl.excitation energy eLvl
		if(iPartType >=1000)
		{
			char cCommand[40];
			//G4UImanager* UI = G4UImanager::GetUIpointer();
      //sprintf(cCommand, "/grdm/nucleusLimits %i %i %i %i", A, A, Z, Z);//aMin, aMax, zMin, and zMax (deprecated command)
      sprintf(cCommand, "/process/had/rdm/nucleusLimits %i %i %i %i", A, A, Z, Z);//aMin, aMax, zMin, and zMax 
      gl.UI->ApplyCommand(cCommand); // to allow only alpha and beta decay
		}

    G4double Mom2 = Momentum.mag2(); // momentum squared
    G4double Mass = particle->GetPDGMass(); // mass of the particle
    G4double KEnrg = sqrt(Mom2 + Mass*Mass) - Mass; // Kinetic energy

    particleSource->SetParticleDefinition(particle);
    particleSource->SetParticleEnergy( KEnrg );
//    particleSource->SetParticleMomentum( sqrt(Mom2) );
    particleSource->SetParticleMomentumDirection( Momentum.unit() ); // direction of the particle (unity vector)
    particleSource->SetParticlePolarization( Polarization ); 
    particleSource->SetParticlePosition(partPos);

    particleSource->GeneratePrimaryVertex(anEvent);
  } // end of cycle over the particles in the event

/*
  G4ParticleDefinition* particle = particleTable->FindParticle(ParticleName);
//  G4double Mom2 = Momentum.mag2(); // momentum squared
//  G4double Mass = particle->GetPDGMass(); // mass of the particle
//  G4double KEnrg = sqrt(Mom2 + Mass*Mass) - Mass; // Kinetic energy
  particleSource->SetParticleDefinition(particle);
//  particleSource->SetParticleEnergy( KEnrg );
//  particleSource->SetParticleMomentum( sqrt(Mom2) );
  particleSource->SetParticleMomentum( Momentum );
//  particleSource->SetParticleMomentumDirection( Momentum.unit() ); // direction (unit vector)
  particleSource->SetParticlePolarization( Polarization ); 
  particleSource->SetParticlePosition(G4ThreeVector(partPos_x, partPos_y, partPos_z));

  particleSource->GeneratePrimaryVertex(anEvent);
*/
}
