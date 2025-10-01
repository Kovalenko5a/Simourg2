
#ifndef SimourgGlobal_h
#define SimourgGlobal_h 1

#include <fstream>
#include "globals.hh"
#include "G4ios.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4UImanager.hh"
#include "G4ThreeVector.hh"

#define LENGTH_HIT_ARR 10000
#define LENGTH_HIT_ASCII_ARR 100
#define HEIGHT_HIT_ASCII_ARR 20

class SimourgMessenger;

class SimourgGlobal 
{
public:
// parameters from external file:

  G4double D_SHLD; // diameter of the shield, mm
  G4double ZL_SHLD; // length of the shield along z axis, mm
  G4double MaterialSHLDDensity; // Density of the shield material, g/cm^3
  G4String MaterialSHLDElementNames[20]; // Names of elements in chemical formula of MaterialSHLD
  G4String MaterialSHLDElementName; // Name of element in chemical formula of MaterialSHLD
  G4int MaterialSHLDFormulaN[20]; // Numbers of atoms (by element) in chemical formula of MaterialSHLD
  G4int MaterialSHLDFormulaNum; // Number of atoms of given element in chemical formula of MaterialSHLD
  G4int MaterialSHLDNComponents; // Number of components in chemical formula of MaterialSHLD
  std::map<G4String, G4double> SHLDElementSolution;


  G4int isCover2Box; // if 0, the Cover2 is cylindric (in this case, there should be XL_Cover2==YL_Cover2)
  G4double D_Cover2; // diameter of the Cover2, mm
  G4double XL_Cover2; // length of the Cover2 along x axis, mm
  G4double YL_Cover2; // length of the Cover2 along y axis, mm
  G4double ZL_Cover2; // length of the Cover2 along z axis, mm
  G4double Z_Cover2; // Z coordinate of the Cover2 center, mm
  G4double X_Cover2; // X coordinate of the Cover2 center, mm
  G4double Y_Cover2; // Y coordinate of the Cover2 center, mm
  G4ThreeVector Rot_Cover2; // Rotation vector (for rotation matrix) Cover2
  G4double MaterialCover2Density; // Density of the Cover2 material, g/cm^3
  G4String MaterialCover2ElementNames[20]; // Names of elements in chemical formula of MaterialCover2
  G4String MaterialCover2ElementName; // Name of element in chemical formula of MaterialCover2
  G4int MaterialCover2FormulaN[20]; // Numbers of atoms (by element) in chemical formula of MaterialCover2
  G4int MaterialCover2FormulaNum; // Number of atoms of given element in chemical formula of MaterialCover2
  G4int MaterialCover2NComponents; // Number of components in chemical formula of MaterialCover2
  std::map<G4String, G4double> Cover2ElementSolution;


  G4int isCover1Box; // if 0, the core is cylindric (in this case, there should be XL_Cover1==YL_Cover1)
  G4double D_Cover1; // diameter of the core, mm
  G4double XL_Cover1; // length of the core along x axis, mm
  G4double YL_Cover1; // length of the core along y axis, mm
  G4double ZL_Cover1; // length of the core along z axis, mm
  G4double Z_Cover1; // Z coordinate of the core center, mm
  G4double X_Cover1; // X coordinate of the core center, mm
  G4double Y_Cover1; // Y coordinate of the core center, mm
  G4ThreeVector Rot_Cover1; // Rotation vector (for rotation matrix) Cover1
  G4double MaterialCover1Density; // Density of the core material, g/cm^3
  G4String MaterialCover1ElementNames[20]; // Names of elements in chemical formula of MaterialCover1
  G4String MaterialCover1ElementName; // Name of element in chemical formula of MaterialCover1
  G4int MaterialCover1FormulaN[20]; // Numbers of atoms (by element) in chemical formula of MaterialCover1
  G4int MaterialCover1FormulaNum; // Number of atoms of given element in chemical formula of MaterialCover1
  G4int MaterialCover1NComponents; // Number of components in chemical formula of MaterialCover1
  std::map<G4String, G4double> Cover1ElementSolution;

  G4int isDetBox; // if 0, the detector is cylindric (in this case, there should be XL_Det==YL_Det)
  G4double D_Det; // diameter of the detector, mm
  G4double XL_Det; // length of the detector along x axis, mm
  G4double YL_Det; // length of the detector along y axis, mm
  G4double ZL_Det; // length of the detector along z axis, mm
  G4double Z_Det; // Z coordinate of the detector center, mm
  G4double X_Det; // X coordinate of the detector center, mm
  G4double Y_Det; // Y coordinate of the detector center, mm
  G4ThreeVector Rot_Det; // Rotation vector (for rotation matrix) Detector
  G4double MaterialDetDensity; // Density of the detector material, g/cm^3
  G4String MaterialDetElementNames[20]; // Names of elements in chemical formula of MaterialDet
  G4String MaterialDetElementName; // Name of element in chemical formula of MaterialDet
  G4int MaterialDetFormulaN[20]; // Numbers of atoms (by element) in chemical formula of MaterialDet
  G4int MaterialDetFormulaNum; // Number of atoms of given element in chemical formula of MaterialDet
  G4int MaterialDetNComponents; // Number of components in chemical formula of MaterialDet
  std::map<G4String, G4double> DetElementSolution;

  G4int isCavityBox; // if 0, the detector is cylindric (in this case, there should be XL_Det==YL_Det)  
	G4double D_Cavity; // diameter of the cavity, mm
  G4double XL_Cavity; // length of the cavity along x axis, mm
  G4double YL_Cavity; // length of the cavity along y axis, mm
  G4double ZL_Cavity; // length of the cavity along z axis, mm
  G4double Z_Cavity; // Z coordinate of the cavity center, mm
  G4double X_Cavity; // X coordinate of the cavity center, mm
  G4double Y_Cavity; // Y coordinate of the cavity center, mm
  G4ThreeVector Rot_Cavity; // Rotation vector (for rotation matrix) Cavity
  G4double MaterialCavityDensity; // Density of the cavity material, g/cm^3
  G4String MaterialCavityElementNames[20]; // Names of elements in chemical formula of MaterialCavity
  G4String MaterialCavityElementName; // Name of element in chemical formula of MaterialCavity
  G4int MaterialCavityFormulaN[20]; // Numbers of atoms (by element) in chemical formula of MaterialCavity
  G4int MaterialCavityFormulaNum; // Number of atoms of given element in chemical formula of MaterialCavity
  G4int MaterialCavityNComponents; // Number of components in chemical formula of MaterialCavity
  std::map<G4String, G4double> CavityElementSolution;

  G4double D_Top1; // length of the Top1 volume along x axis, mm
  G4double d_Top1; // inner diameter of the Top1 volume, mm
  G4double ZL_Top1; // length of the Top1 volume along z axis, mm
  G4double Z_Top1; // Z coordinate of the Top1 volume center, mm
  G4double Y_Top1; // Y coordinate of the Top1 volume center, mm
  G4double X_Top1; // X coordinate of the Top1 volume center, mm
  G4ThreeVector Rot_Top1; // Rotation vector (for rotation matrix) Top1
  // G4int isTop1aDetector;
  std::vector<std::string> DetectorsList; //Detector list for sensative detector creation
  std::map<std::string, G4double> EdepDetect; // Map to store energy deposition per detector
  std::map<std::string, std::pair<long double, long double>> TimeDetect; // Map to store time of deposition per detector states

  G4double MaterialTop1Density; // Density of the Top1 volume material, g/cm^3
  G4String MaterialTop1ElementNames[20]; // Names of elements in chemical formula of MaterialTop1
  G4String MaterialTop1ElementName; // Name of element in chemical formula of MaterialTop1
  G4int MaterialTop1FormulaN[20]; // Numbers of atoms (by element) in chemical formula of MaterialTop1
  G4int MaterialTop1FormulaNum; // Number of atoms of given element in chemical formula of MaterialTop1
  G4int MaterialTop1NComponents; // Number of components in chemical formula of MaterialTop1
  std::map<G4String, G4double> Top1ElementSolution;

  G4double D_Top2; // length of the Top2 volume along x axis, mm
  G4double d_Top2; // inner diameter of the Top2 volume, mm
  G4double ZL_Top2; // length of the Top2 volume along z axis, mm
  G4double Z_Top2; // Z coordinate of the Top2 volume center, mm
  G4double Y_Top2; // Y coordinate of the Top2 volume center, mm
  G4double X_Top2; // X coordinate of the Top2 volume center, mm
  G4ThreeVector Rot_Top2; // Rotation vector (for rotation matrix) Top2
  G4double MaterialTop2Density; // Density of the Top2 volume material, g/cm^3
  G4String MaterialTop2ElementNames[20]; // Names of elements in chemical formula of MaterialTop2
  G4String MaterialTop2ElementName; // Name of element in chemical formula of MaterialTop2
  G4int MaterialTop2FormulaN[20]; // Numbers of atoms (by element) in chemical formula of MaterialTop2
  G4int MaterialTop2FormulaNum; // Number of atoms of given element in chemical formula of MaterialTop2
  G4int MaterialTop2NComponents; // Number of components in chemical formula of MaterialTop2
  std::map<G4String, G4double> Top2ElementSolution;
  // G4int isTop2aDetector;

  G4double D_Top3; // length of the Top3 volume along x axis, mm
  G4double d_Top3; // inner diameter of the Top3 volume, mm
  G4double ZL_Top3; // length of the Top3 volume along z axis, mm
  G4double Z_Top3; // Z coordinate of the Top3 volume center, mm
  G4double X_Top3; // X coordinate of the Top3 volume center, mm
  G4double Y_Top3; // Y coordinate of the Top3 volume center, mm
  G4ThreeVector Rot_Top3; // Rotation vector (for rotation matrix) Top3
  G4double MaterialTop3Density; // Density of the Top3 volume material, g/cm^3
  G4String MaterialTop3ElementNames[20]; // Names of elements in chemical formula of MaterialTop3
  G4String MaterialTop3ElementName; // Name of element in chemical formula of MaterialTop3
  G4int MaterialTop3FormulaN[20]; // Numbers of atoms (by element) in chemical formula of MaterialTop3
  G4int MaterialTop3FormulaNum; // Number of atoms of given element in chemical formula of MaterialTop3
  G4int MaterialTop3NComponents; // Number of components in chemical formula of MaterialTop3
  std::map<G4String, G4double> Top3ElementSolution;

  G4double D_Bot1; // length of the Bot1 volume along x axis, mm
  G4double d_Bot1; // inner diameter, mm
  G4double ZL_Bot1; // length of the Bot1 volume along z axis, mm
  G4double Z_Bot1; // Z coordinate of the Bot1 volume center, mm
  G4double Y_Bot1; // Y coordinate of the Bot1 volume center, mm
  G4double X_Bot1; // X coordinate of the Bot1 volume center, mm
  G4ThreeVector Rot_Bot1; // Rotation vector (for rotation matrix) Bot1
  G4double MaterialBot1Density; // Density of the Bot1 volume material, g/cm^3
  G4String MaterialBot1ElementNames[20]; // Names of elements in chemical formula of MaterialBot1
  G4String MaterialBot1ElementName; // Name of element in chemical formula of MaterialBot1
  G4int MaterialBot1FormulaN[20]; // Numbers of atoms (by element) in chemical formula of MaterialBot1
  G4int MaterialBot1FormulaNum; // Number of atoms of given element in chemical formula of MaterialBot1
  G4int MaterialBot1NComponents; // Number of components in chemical formula of MaterialBot1
  std::map<G4String, G4double> Bot1ElementSolution;

  G4double D_Bot2; // length of the Bot2 volume along x axis, mm
  G4double d_Bot2; // inner diameter, mm
  G4double ZL_Bot2; // length of the Bot2 volume along z axis, mm
  G4double Z_Bot2; // Z coordinate of the Bot2 volume center, mm
  G4double X_Bot2; // X coordinate of the Bot2 volume center, mm
  G4double Y_Bot2; // Y coordinate of the Bot2 volume center, mm
  G4ThreeVector Rot_Bot2; // Rotation vector (for rotation matrix) Bot2
  G4double MaterialBot2Density; // Density of the Bot2 volume material, g/cm^3
  G4String MaterialBot2ElementNames[20]; // Names of elements in chemical formula of MaterialBot2
  G4String MaterialBot2ElementName; // Name of element in chemical formula of MaterialBot2
  G4int MaterialBot2FormulaN[20]; // Numbers of atoms (by element) in chemical formula of MaterialBot2
  G4int MaterialBot2FormulaNum; // Number of atoms of given element in chemical formula of MaterialBot2
  G4int MaterialBot2NComponents; // Number of components in chemical formula of MaterialBot2
  std::map<G4String, G4double> Bot2ElementSolution;

  G4double D_Bot3; // length of the Bot3 volume along x axis, mm
  G4double d_Bot3; // inner diameter, mm
  G4double ZL_Bot3; // length of the Bot3 volume along z axis, mm
  G4double Z_Bot3; // Z coordinate of the Bot3 volume center, mm
  G4double X_Bot3; // X coordinate of the Bot3 volume center, mm
  G4double Y_Bot3; // Y coordinate of the Bot3 volume center, mm
  G4ThreeVector Rot_Bot3; // Rotation vector (for rotation matrix) Bot3
  G4double MaterialBot3Density; // Density of the Bot3 volume material, g/cm^3
  G4String MaterialBot3ElementNames[20]; // Names of elements in chemical formula of MaterialBot3
  G4String MaterialBot3ElementName; // Name of element in chemical formula of MaterialBot3
  G4int MaterialBot3FormulaN[20]; // Numbers of atoms (by element) in chemical formula of MaterialBot3
  G4int MaterialBot3FormulaNum; // Number of atoms of given element in chemical formula of MaterialBot3
  G4int MaterialBot3NComponents; // Number of components in chemical formula of MaterialBot3
  std::map<G4String, G4double> Bot3ElementSolution;


  G4int isSrcBox; // if 0, the source is cylindric (in this case, XL_Src==YL_Src)
  G4double D_Src; // diameter of the source, mm
  G4double XL_Src; // length of the source along x axis, mm
  G4double YL_Src; // length of the source along y axis, mm
  G4double ZL_Src; // length of the source along z axis, mm
  G4double X_Src; // X coordinate of the source center, mm
  G4double Y_Src; // Y coordinate of the source center, mm
  G4double Z_Src; // Z coordinate of the source center, mm
  G4ThreeVector Rot_Src; // Rotation vector (for rotation matrix) Source
	G4String SrcVolume;


  G4int isUnSrcBox; // if 0, the UnSource is cylindric (in this case, XL_UnSrc==YL_UnSrc)
  G4double D_UnSrc; // diameter of the UnSource, mm
  G4double XL_UnSrc; // length of the UnSource along x axis, mm
  G4double YL_UnSrc; // length of the UnSource along y axis, mm
  G4double ZL_UnSrc; // length of the UnSource along z axis, mm
  G4double X_UnSrc; // X coordinate of the UnSource center, mm
  G4double Y_UnSrc; // Y coordinate of the UnSource center, mm
  G4double Z_UnSrc; // Z coordinate of the UnSource center, mm
  G4ThreeVector Rot_UnSrc; // Rotation vector (for rotation matrix) UnSrc
	G4String UnSrcVolume;

  G4double EGamma; // [keV] Energy of generated gamma quanta
//  G4double AlphaBeta0; // Alpha-Beta ratio of the Detector:
//  G4double AlphaBeta1; //  ab = AlphaBeta0 + AlphaBeta1*Ealpha[MeV]
  G4double FWHM1; // [keV^2]  
  G4double FWHM2; // [keV] FWHM coefficients of the Detector: FWHM=sqrt(FWHM1+FWHM2*Egamma)
  G4double AlphaBeta; // [] AlphaBeta coefficient of the Detector (typically < 1): Eobserved = Ereleased * AlphaBeta
  G4double Threshold; // [keV] Energy threshold of the Detector
	G4double tMin; // [s] minimal time of particle emission to generate
	G4double tMax; // [s] maximal time of particle emission to generate 
  G4double ELowLimit;// [keV] Lower cut for particle energy;  
  G4double DELowLimit;// [nm] Lower cut for e+/e- distance step;
  G4double DGLowLimit;// [nm] Lower cut for gamma distance step;
  G4double ChannelWidth;// [keV] Width of one channel in the spectrum;

  G4int    numberOfRuns;
  G4int    Step;
  G4long   RandomSeed;
  //char     InFileName[128];
  G4int    WaitCommand;
  G4int    VerboseVis;
  G4int    VerboseAll;
  G4int    DoPicture;
  G4int    AllowIsotropicRotation;
  G4int    saveTo; // 0 - root; 1 - csv
  G4int    wrlFilesQuantity; // 0-N events
  G4String PhysicsList; // Options: hadr:  CHIPS, FTFP_BERT, FTFP_BERT_TRV, FTFP_BERT_HP, FTF_BIC, LBE, LHEP, 
                    // QBBC, QGSC_BERT, QGSP_BERT, QGSP_BERT_CHIPS, QGSP_BERT_HP, QGSP_BIC, QGSP_BIC_HP,
                    // QGSP_FTFP_BERT, QGS_BIC, QGSP_INCLXX, Shielding, ShieldingLEND with add  
                    // em: {"","_EMV","_EMX","_EMY","_EMZ","_LIV","_PEN"}, for example FTFP_BERT_LIV

  G4String Decay0FileName;

public:
// aux variables
  std::ifstream in;
  G4double Src_Radius2, UnSrc_Radius2; // External radius^2 of the source and UnSource
	G4double tFirstHit; // global time of the first hit in the event
  G4int iFlag;
  G4int ScrollLines;
	// Do the mandatory volumes exist?
  G4bool isSHLD;
  G4bool isDet;
  G4bool isSrc;
	// Do the optional volumes exist?
  G4bool isUnSrc;
	G4bool isCover2;
	G4bool isCover2X;
  G4bool isCover1;
  G4bool isCover1X;
  G4bool isCavity;//
  G4bool isTop1;// 
  G4bool isTop2;//
  G4bool isTop3;//
  G4bool isBot1;//
  G4bool isBot2;//
  G4bool isBot3;//
  G4bool isEGamma;// is EGamma defined? 
  G4bool isDecay0;// is Decay0 file defined?
	G4bool isBlur; // should Simourg make the blurred spectrum file?
  G4bool is1stEvAct;
  G4bool is1stDetHit;


  char* TimeStampMain;
  char* TimeStampDetConstr;
  char* TimeStampEvAct;
  char* TimeStampGlob;
  char* TimeStampPhyLis;
  char* TimeStampPhyLisEmS;
  char* TimeStampPriGenAct;
  char* TimeStampSensDet;
  char* TimeStampVisMan;
  char* TimeStampMess;

  G4int iRun;
	G4int numHits;
	G4double tMinHit;
	G4double tMaxHit;
	G4double tHit[LENGTH_HIT_ARR];
	G4double eHit[LENGTH_HIT_ARR];

  char* TimeStampDetHit;

	G4UImanager* UI;

  SimourgGlobal();
  ~SimourgGlobal();
  void Dump(void);
  void Dump1(int);
  void FineTuning(void);
  void Exception(const char*);
  void E_ASCII_Distr(void);
private:
	SimourgMessenger* SimMess;
  char ASCII_Distr[LENGTH_HIT_ASCII_ARR][HEIGHT_HIT_ASCII_ARR];
	G4double HitEDistr[LENGTH_HIT_ASCII_ARR];
};

#endif
