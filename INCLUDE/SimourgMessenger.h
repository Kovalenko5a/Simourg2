
#ifndef SimourgMessenger_h
#define SimourgMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithABool.hh"


class SimourgGlobal;
class G4UIdirectory;
class G4UIcmdWithADouble;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithAnInteger;
class G4UIcmdWithAString;
class G4UIcmdWithoutParameter;




//..../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......

class SimourgMessenger: public G4UImessenger
{
  public:
    SimourgMessenger(SimourgGlobal* gl1);//
   ~SimourgMessenger();
    
    void SetNewValue(G4UIcommand*, G4String);

  
private:
    
  G4UIdirectory*             userDir; 
    
  G4UIcmdWithoutParameter*   showAllCmd;
  G4UIcmdWithoutParameter*   initCmd; // init and reset -- equivalent commands
  G4UIcmdWithoutParameter*   resetCmd;

  G4UIcmdWithADoubleAndUnit*  D_SHLDCmd;
  G4UIcmdWithADoubleAndUnit*  ZL_SHLDCmd;
  G4UIcmdWithADoubleAndUnit*  MaterialSHLDDensityCmd;
  
	G4UIcmdWithADoubleAndUnit*  D_Cover2Cmd;
  G4UIcmdWithADoubleAndUnit*  XL_Cover2Cmd;
  G4UIcmdWithADoubleAndUnit*  YL_Cover2Cmd;
  G4UIcmdWithADoubleAndUnit*  ZL_Cover2Cmd;
  G4UIcmdWithADoubleAndUnit*  Z_Cover2Cmd;
  G4UIcmdWithADoubleAndUnit*  X_Cover2Cmd;
  G4UIcmdWithADoubleAndUnit*  Y_Cover2Cmd;
  G4UIcmdWith3VectorAndUnit*  Rot_Cover2Cmd;
  G4UIcmdWithADoubleAndUnit*  MaterialCover2DensityCmd;
  
	G4UIcmdWithADoubleAndUnit*  D_Cover1Cmd;
  G4UIcmdWithADoubleAndUnit*  XL_Cover1Cmd;
  G4UIcmdWithADoubleAndUnit*  YL_Cover1Cmd;
  G4UIcmdWithADoubleAndUnit*  ZL_Cover1Cmd;
  G4UIcmdWithADoubleAndUnit*  Z_Cover1Cmd;
  G4UIcmdWithADoubleAndUnit*  X_Cover1Cmd;
  G4UIcmdWithADoubleAndUnit*  Y_Cover1Cmd;
  G4UIcmdWith3VectorAndUnit*  Rot_Cover1Cmd;
  G4UIcmdWithADoubleAndUnit*  MaterialCover1DensityCmd;
	
	G4UIcmdWithADoubleAndUnit*  D_MarinelliCmd;
  G4UIcmdWithADoubleAndUnit*  XL_MarinelliCmd;
  G4UIcmdWithADoubleAndUnit*  YL_MarinelliCmd;
  G4UIcmdWithADoubleAndUnit*  ZL_MarinelliCmd;
  G4UIcmdWithADoubleAndUnit*  Z_MarinelliCmd;
  G4UIcmdWithADoubleAndUnit*  Y_MarinelliCmd;
  G4UIcmdWithADoubleAndUnit*  X_MarinelliCmd;
  G4UIcmdWith3VectorAndUnit*  Rot_MarinelliCmd;
  G4UIcmdWithADoubleAndUnit*  MaterialMarinelliDensityCmd;
  
	G4UIcmdWithADoubleAndUnit*  D_CoreCmd;
  G4UIcmdWithADoubleAndUnit*  XL_CoreCmd;
  G4UIcmdWithADoubleAndUnit*  YL_CoreCmd;
  G4UIcmdWithADoubleAndUnit*  ZL_CoreCmd;
  G4UIcmdWithADoubleAndUnit*  Z_CoreCmd;
  G4UIcmdWithADoubleAndUnit*  X_CoreCmd;
  G4UIcmdWithADoubleAndUnit*  Y_CoreCmd;
  G4UIcmdWith3VectorAndUnit*  Rot_CoreCmd;
  G4UIcmdWithADoubleAndUnit*  MaterialCoreDensityCmd;

  G4UIcmdWithADoubleAndUnit*  D_DetCmd;
  G4UIcmdWithADoubleAndUnit*  XL_DetCmd;
  G4UIcmdWithADoubleAndUnit*  YL_DetCmd;
  G4UIcmdWithADoubleAndUnit*  ZL_DetCmd;
  G4UIcmdWithADoubleAndUnit*  Z_DetCmd;
  G4UIcmdWithADoubleAndUnit*  X_DetCmd;
  G4UIcmdWithADoubleAndUnit*  Y_DetCmd;
  G4UIcmdWith3VectorAndUnit*  Rot_DetCmd;
  G4UIcmdWithADoubleAndUnit*  MaterialDetDensityCmd;

  G4UIcmdWithADoubleAndUnit*  D_CavityCmd;
  G4UIcmdWithADoubleAndUnit*  XL_CavityCmd;
  G4UIcmdWithADoubleAndUnit*  YL_CavityCmd;
  G4UIcmdWithADoubleAndUnit*  ZL_CavityCmd;
  G4UIcmdWithADoubleAndUnit*  Z_CavityCmd;
  G4UIcmdWithADoubleAndUnit*  X_CavityCmd;
  G4UIcmdWithADoubleAndUnit*  Y_CavityCmd;
  G4UIcmdWith3VectorAndUnit*  Rot_CavityCmd;
  G4UIcmdWithADoubleAndUnit*  MaterialCavityDensityCmd;

  G4UIcmdWithADoubleAndUnit*  D_Top1Cmd;
  G4UIcmdWithADoubleAndUnit*  d_Top1Cmd;
  G4UIcmdWithADoubleAndUnit*  ZL_Top1Cmd;
  G4UIcmdWithADoubleAndUnit*  Z_Top1Cmd;
  G4UIcmdWithADoubleAndUnit*  X_Top1Cmd;
  G4UIcmdWithADoubleAndUnit*  Y_Top1Cmd;
  G4UIcmdWith3VectorAndUnit*  Rot_Top1Cmd;
  G4UIcmdWithADoubleAndUnit*  MaterialTop1DensityCmd;

  G4UIcmdWithADoubleAndUnit*  D_Top2Cmd;
  G4UIcmdWithADoubleAndUnit*  d_Top2Cmd;
  G4UIcmdWithADoubleAndUnit*  ZL_Top2Cmd;
  G4UIcmdWithADoubleAndUnit*  Z_Top2Cmd;
  G4UIcmdWithADoubleAndUnit*  X_Top2Cmd;
  G4UIcmdWithADoubleAndUnit*  Y_Top2Cmd;
  G4UIcmdWith3VectorAndUnit*  Rot_Top2Cmd;
  G4UIcmdWithADoubleAndUnit*  MaterialTop2DensityCmd;

  G4UIcmdWithADoubleAndUnit*  D_Top3Cmd;
  G4UIcmdWithADoubleAndUnit*  d_Top3Cmd;
  G4UIcmdWithADoubleAndUnit*  ZL_Top3Cmd;
  G4UIcmdWithADoubleAndUnit*  Z_Top3Cmd;
  G4UIcmdWithADoubleAndUnit*  Y_Top3Cmd;
  G4UIcmdWithADoubleAndUnit*  X_Top3Cmd;
  G4UIcmdWith3VectorAndUnit*  Rot_Top3Cmd;
  G4UIcmdWithADoubleAndUnit*  MaterialTop3DensityCmd;

  G4UIcmdWithADoubleAndUnit*  D_Bot1Cmd;
  G4UIcmdWithADoubleAndUnit*  d_Bot1Cmd;
  G4UIcmdWithADoubleAndUnit*  ZL_Bot1Cmd;
  G4UIcmdWithADoubleAndUnit*  Z_Bot1Cmd;
  G4UIcmdWithADoubleAndUnit*  X_Bot1Cmd;
  G4UIcmdWithADoubleAndUnit*  Y_Bot1Cmd;
  G4UIcmdWith3VectorAndUnit*  Rot_Bot1Cmd;
  G4UIcmdWithADoubleAndUnit*  MaterialBot1DensityCmd;

  G4UIcmdWithADoubleAndUnit*  D_Bot2Cmd;
  G4UIcmdWithADoubleAndUnit*  d_Bot2Cmd;
  G4UIcmdWithADoubleAndUnit*  ZL_Bot2Cmd;
  G4UIcmdWithADoubleAndUnit*  Z_Bot2Cmd;
  G4UIcmdWithADoubleAndUnit*  X_Bot2Cmd;
  G4UIcmdWithADoubleAndUnit*  Y_Bot2Cmd;
  G4UIcmdWith3VectorAndUnit*  Rot_Bot2Cmd;
  G4UIcmdWithADoubleAndUnit*  MaterialBot2DensityCmd;

  G4UIcmdWithADoubleAndUnit*  D_Bot3Cmd;
  G4UIcmdWithADoubleAndUnit*  d_Bot3Cmd;
  G4UIcmdWithADoubleAndUnit*  ZL_Bot3Cmd;
  G4UIcmdWithADoubleAndUnit*  Z_Bot3Cmd;
  G4UIcmdWithADoubleAndUnit*  X_Bot3Cmd;
  G4UIcmdWithADoubleAndUnit*  Y_Bot3Cmd;
  G4UIcmdWith3VectorAndUnit*  Rot_Bot3Cmd;
  G4UIcmdWithADoubleAndUnit*  MaterialBot3DensityCmd;

  G4UIcmdWithADoubleAndUnit*  D_SrcCmd;
  G4UIcmdWithADoubleAndUnit*  XL_SrcCmd;
  G4UIcmdWithADoubleAndUnit*  YL_SrcCmd;
  G4UIcmdWithADoubleAndUnit*  ZL_SrcCmd;
  G4UIcmdWithADoubleAndUnit*  X_SrcCmd;
  G4UIcmdWithADoubleAndUnit*  Y_SrcCmd;
  G4UIcmdWithADoubleAndUnit*  Z_SrcCmd;
  G4UIcmdWith3VectorAndUnit*  Rot_SrcCmd;

  G4UIcmdWithADoubleAndUnit*  D_UnSrcCmd;
  G4UIcmdWithADoubleAndUnit*  XL_UnSrcCmd;
  G4UIcmdWithADoubleAndUnit*  YL_UnSrcCmd;
  G4UIcmdWithADoubleAndUnit*  ZL_UnSrcCmd;
  G4UIcmdWithADoubleAndUnit*  X_UnSrcCmd;
  G4UIcmdWithADoubleAndUnit*  Y_UnSrcCmd;
  G4UIcmdWithADoubleAndUnit*  Z_UnSrcCmd;
  G4UIcmdWith3VectorAndUnit*  Rot_UnSrcCmd;
  
  G4UIcmdWithADoubleAndUnit*  EGammaCmd;
  G4UIcmdWithADoubleAndUnit*  ThresholdCmd;
  G4UIcmdWithADoubleAndUnit*  tMinCmd;
  G4UIcmdWithADoubleAndUnit*  tMaxCmd;
  G4UIcmdWithADoubleAndUnit*  ELowLimitCmd;
  G4UIcmdWithADoubleAndUnit*  DELowLimitCmd;
  G4UIcmdWithADoubleAndUnit*  DGLowLimitCmd;
  G4UIcmdWithADoubleAndUnit*  ChannelWidthCmd;

  G4UIcmdWithADouble* FWHM1Cmd;
  G4UIcmdWithADouble* FWHM2Cmd;
  G4UIcmdWithADouble* AlphaBetaCmd;

  G4UIcmdWithAnInteger* MaterialSHLDFormulaNumCmd;
  G4UIcmdWithAString*   MaterialSHLDWeightCmd;
  G4UIcmdWithAnInteger* MaterialCover2FormulaNumCmd;
  G4UIcmdWithAString*   MaterialCover2WeightCmd;
  G4UIcmdWithAnInteger* MaterialCover1FormulaNumCmd;
  G4UIcmdWithAString*   MaterialCover1WeightCmd;
  G4UIcmdWithAnInteger* MaterialMarinelliFormulaNumCmd;
  G4UIcmdWithAString*   MaterialMarinelliWeightCmd;
  G4UIcmdWithAnInteger* MaterialCoreFormulaNumCmd;
  G4UIcmdWithAString*   MaterialCoreWeightCmd;
  G4UIcmdWithAnInteger* MaterialDetFormulaNumCmd;
  G4UIcmdWithAString*   MaterialDetWeightCmd;
  G4UIcmdWithAnInteger* MaterialCavityFormulaNumCmd;
  G4UIcmdWithAString*   MaterialCavityWeightCmd;
  G4UIcmdWithAnInteger* MaterialTop1FormulaNumCmd;
  G4UIcmdWithAString*   MaterialTop1WeightCmd;
  G4UIcmdWithAnInteger* MaterialTop2FormulaNumCmd;
  G4UIcmdWithAString*   MaterialTop2WeightCmd;
  G4UIcmdWithAnInteger* MaterialTop3FormulaNumCmd;
  G4UIcmdWithAString*   MaterialTop3WeightCmd;
  G4UIcmdWithAnInteger* MaterialBot1FormulaNumCmd;
  G4UIcmdWithAString*   MaterialBot1WeightCmd;
  G4UIcmdWithAnInteger* MaterialBot2FormulaNumCmd;
  G4UIcmdWithAString*   MaterialBot2WeightCmd;
  G4UIcmdWithAnInteger* MaterialBot3FormulaNumCmd;
  G4UIcmdWithAString*   MaterialBot3WeightCmd;


  G4UIcmdWithAnInteger* isSrcBoxCmd;
  G4UIcmdWithAnInteger* numberOfRunsCmd;
  G4UIcmdWithAnInteger* StepCmd;
  G4UIcmdWithAnInteger* RandomSeedCmd;
  G4UIcmdWithAnInteger* WaitCommandCmd;
  G4UIcmdWithAnInteger* VerboseVisCmd;
  G4UIcmdWithAnInteger* VerboseAllCmd;
  G4UIcmdWithAnInteger* DoPictureCmd;
  G4UIcmdWithAnInteger* AllowIsotropicRotationCmd;
  G4UIcmdWithAnInteger*  Detector_Top1Cmd;
  G4UIcmdWithAnInteger*  Detector_Top2Cmd;
  G4UIcmdWithAnInteger*  Detector_Top3Cmd;
  G4UIcmdWithAnInteger*  Detector_Bot1Cmd;
  G4UIcmdWithAnInteger*  Detector_Bot2Cmd;
  G4UIcmdWithAnInteger*  Detector_Bot3Cmd;
  G4UIcmdWithAnInteger*  Detector_Cover1Cmd;
  G4UIcmdWithAnInteger*  Detector_Cover2Cmd;
  G4UIcmdWithAnInteger*  Detector_CavityCmd;
  G4UIcmdWithAnInteger*  Detector_UnSrcCmd;
  G4UIcmdWithAnInteger*  Detector_SrcCmd;
  G4UIcmdWithAnInteger*  Detector_SHLDCmd;
  G4UIcmdWithAnInteger* SaveToCmd;
  G4UIcmdWithAnInteger* wrlFilesQuantityCmd;


  G4UIcmdWithAString* MaterialSHLDElementNameCmd;
  G4UIcmdWithAString* MaterialCover2ElementNameCmd;
  G4UIcmdWithAString* MaterialCover1ElementNameCmd;
  G4UIcmdWithAString* MaterialMarinelliElementNameCmd;
  G4UIcmdWithAString* MaterialCoreElementNameCmd;
  G4UIcmdWithAString* MaterialDetElementNameCmd;
  G4UIcmdWithAString* MaterialCavityElementNameCmd;
  G4UIcmdWithAString* MaterialTop1ElementNameCmd;
  G4UIcmdWithAString* MaterialTop2ElementNameCmd;
  G4UIcmdWithAString* MaterialTop3ElementNameCmd;
  G4UIcmdWithAString* MaterialBot1ElementNameCmd;
  G4UIcmdWithAString* MaterialBot2ElementNameCmd;
  G4UIcmdWithAString* MaterialBot3ElementNameCmd;
  G4UIcmdWithAString* VolumeSrcCmd;
  G4UIcmdWithAString* VolumeUnSrcCmd;
  G4UIcmdWithAString* PhysicsListCmd; 
  G4UIcmdWithAString* Decay0FileCmd;
};

//..../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......

#endif

