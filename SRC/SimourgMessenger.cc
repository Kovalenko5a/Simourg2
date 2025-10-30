//..../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......

#include "G4SystemOfUnits.hh"

#include "SimourgMessenger.h"
#include "Randomize.hh"

#include "SimourgGlobal.h"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithoutParameter.hh"

#include "globals.hh"

extern SimourgGlobal gl;

//..../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......

SimourgMessenger::SimourgMessenger(SimourgGlobal* gl1)
{ 
  
  G4bool omittable;
  userDir = new G4UIdirectory("/user/");
  userDir->SetGuidance("Simourg detector control.");  
  userDir->SetGuidance("  Available for user.");

  // gl.DetectorsList.push_back("Det/DetSD");

//=======Shield:============
  Detector_SHLDCmd = new G4UIcmdWithAnInteger("/user/isSHLDaDetector",this);  
  Detector_SHLDCmd->SetGuidance("\tIs SHLD a detector?");
  Detector_SHLDCmd->SetDefaultValue (0);
  // Detector_SHLDCmd->SetUnitCategory("Boolean");
  Detector_SHLDCmd->SetParameterName("isSHLDaDetector",omittable=false);
  Detector_SHLDCmd->SetRange("isSHLDaDetector==0 || isSHLDaDetector==1"); 
  Detector_SHLDCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  D_SHLDCmd = new G4UIcmdWithADoubleAndUnit("/user/D_SHLD",this);  
  D_SHLDCmd->SetGuidance("Diameter of shield.");
  D_SHLDCmd->SetDefaultValue (500);
  D_SHLDCmd->SetDefaultUnit("mm");
  D_SHLDCmd->SetUnitCategory("Length");
  D_SHLDCmd->SetParameterName("D_SHLD",omittable=false);
  D_SHLDCmd->SetRange("D_SHLD>=0."); 
  D_SHLDCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  ZL_SHLDCmd = new G4UIcmdWithADoubleAndUnit("/user/ZL_SHLD",this);  
  ZL_SHLDCmd->SetGuidance("\tLength of shield.");
  ZL_SHLDCmd->SetDefaultValue (500);
  ZL_SHLDCmd->SetDefaultUnit("mm");
  ZL_SHLDCmd->SetUnitCategory("Length");
  ZL_SHLDCmd->SetParameterName("ZL_SHLD",omittable=false);
  ZL_SHLDCmd->SetRange("ZL_SHLD>=0."); 
  ZL_SHLDCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  MaterialSHLDDensityCmd = new G4UIcmdWithADoubleAndUnit("/user/MaterialSHLDDensity",this);  
  MaterialSHLDDensityCmd->SetGuidance("\tDensity of shield material.");
  MaterialSHLDDensityCmd->SetDefaultValue (10);
  MaterialSHLDDensityCmd->SetDefaultUnit("g/cm3");
  MaterialSHLDDensityCmd->SetUnitCategory("Volumic Mass");
  MaterialSHLDDensityCmd->SetParameterName("MaterialSHLDDensity",omittable=false);
  MaterialSHLDDensityCmd->SetRange("MaterialSHLDDensity>0."); 
  MaterialSHLDDensityCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  MaterialSHLDElementNameCmd = new G4UIcmdWithAString("/user/MaterialSHLDElementName",this);  
  MaterialSHLDElementNameCmd->SetGuidance("\tName of chemical element.");
  MaterialSHLDElementNameCmd->SetDefaultValue ("Cu");
  MaterialSHLDElementNameCmd->SetCandidates("H He Li Be B C N O F Ne Na Mg Al Si P S Cl Ar K Ca Sc Ti V Cr Mn Fe Co Ni Cu Zn Ga Ge As Se Br Kr Rb Sr Y Zr Nb Mo Tc Ru Rh Pd Ag Cd In Sn Sb Te I Xe Cs Ba La Ce Pr Nd Pm Sm Eu Gd Tb Dy Ho Er Tm Yb Lu Hf Ta W Re Os Ir Pt Au Hg Tl Pb Bi Po At Rn Fr Ra Ac Th Pa U Np Pu Am Cm Bk Cf Es Fm");
  MaterialSHLDElementNameCmd->SetParameterName("MaterialSHLDElementName",omittable=false);
  MaterialSHLDElementNameCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  MaterialSHLDWeightCmd = new G4UIcmdWithAString("/user/MaterialSHLDWeight", this);
  MaterialSHLDWeightCmd->SetGuidance("\tProvide element-weight pairs. Example: Cd 1000 W 100 O 10");
  MaterialSHLDWeightCmd->SetParameterName("MaterialSHLDWeight", false);
  MaterialSHLDWeightCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  MaterialSHLDFormulaNumCmd = new G4UIcmdWithAnInteger("/user/MaterialSHLDFormulaNum",this);  
  MaterialSHLDFormulaNumCmd->SetGuidance("\tNumber of atoms of chemical element in the formula.");
  MaterialSHLDFormulaNumCmd->SetDefaultValue (1);
  MaterialSHLDFormulaNumCmd->SetParameterName("MaterialSHLDFormulaNum",omittable=false);
  MaterialSHLDFormulaNumCmd->SetRange("MaterialSHLDFormulaNum>=0"); 
  MaterialSHLDFormulaNumCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

//=======Cover2 (alias:Marinelli):================
  Detector_Cover2Cmd = new G4UIcmdWithAnInteger("/user/isCover2aDetector",this);  
  Detector_Cover2Cmd->SetGuidance("\tIs Cover2 a detector?");
  Detector_Cover2Cmd->SetDefaultValue (0);
  // Detector_Cover2Cmd->SetUnitCategory("Boolean");
  Detector_Cover2Cmd->SetParameterName("isCover2aDetector",omittable=false);
  Detector_Cover2Cmd->SetRange("isCover2aDetector==0 || isCover2aDetector==1"); 
  Detector_Cover2Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  D_Cover2Cmd = new G4UIcmdWithADoubleAndUnit("/user/D_Cover2",this);  
  D_Cover2Cmd->SetGuidance("\tDiameter of the Cover2 volume (if it is a cylinder).");
  D_Cover2Cmd->SetDefaultValue (60);
  D_Cover2Cmd->SetDefaultUnit("mm");
  D_Cover2Cmd->SetUnitCategory("Length");
  D_Cover2Cmd->SetParameterName("D_Cover2",omittable=false);
  D_Cover2Cmd->SetRange("D_Cover2>=0."); 
  D_Cover2Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  XL_Cover2Cmd = new G4UIcmdWithADoubleAndUnit("/user/XL_Cover2",this);  
  XL_Cover2Cmd->SetGuidance("\tX size of the Cover2 volume (if it is a prism).");
  XL_Cover2Cmd->SetDefaultValue (60);
  XL_Cover2Cmd->SetDefaultUnit("mm");
  XL_Cover2Cmd->SetUnitCategory("Length");
  XL_Cover2Cmd->SetParameterName("XL_Cover2",omittable=false);
  XL_Cover2Cmd->SetRange("XL_Cover2>=0."); 
  XL_Cover2Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  YL_Cover2Cmd = new G4UIcmdWithADoubleAndUnit("/user/YL_Cover2",this);  
  YL_Cover2Cmd->SetGuidance("\tY size of the Cover2 volume (if it is a prism).");
  YL_Cover2Cmd->SetDefaultValue (60);
  YL_Cover2Cmd->SetDefaultUnit("mm");
  YL_Cover2Cmd->SetUnitCategory("Length");
  YL_Cover2Cmd->SetParameterName("YL_Cover2",omittable=false);
  YL_Cover2Cmd->SetRange("YL_Cover2>=0."); 
  YL_Cover2Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  ZL_Cover2Cmd = new G4UIcmdWithADoubleAndUnit("/user/ZL_Cover2",this);  
  ZL_Cover2Cmd->SetGuidance("\tZ size (height) of the Cover2 volume.");
  ZL_Cover2Cmd->SetDefaultValue (60);
  ZL_Cover2Cmd->SetDefaultUnit("mm");
  ZL_Cover2Cmd->SetUnitCategory("Length");
  ZL_Cover2Cmd->SetParameterName("ZL_Cover2",omittable=false);
  ZL_Cover2Cmd->SetRange("ZL_Cover2>=0."); 
  ZL_Cover2Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  Z_Cover2Cmd = new G4UIcmdWithADoubleAndUnit("/user/Z_Cover2",this);  
  Z_Cover2Cmd->SetGuidance("\tZ coordinate of the Cover2 volume center.");
  Z_Cover2Cmd->SetDefaultValue (0);
  Z_Cover2Cmd->SetDefaultUnit("mm");
  Z_Cover2Cmd->SetUnitCategory("Length");
  Z_Cover2Cmd->SetParameterName("Z_Cover2",omittable=false);
  Z_Cover2Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  X_Cover2Cmd = new G4UIcmdWithADoubleAndUnit("/user/X_Cover2",this);  
  X_Cover2Cmd->SetGuidance("\tX coordinate of the Cover2 volume center.");
  X_Cover2Cmd->SetDefaultValue (0);
  X_Cover2Cmd->SetDefaultUnit("mm");
  X_Cover2Cmd->SetUnitCategory("Length");
  X_Cover2Cmd->SetParameterName("X_Cover2",omittable=false);
  X_Cover2Cmd->AvailableForStates(G4State_PreInit,G4State_Idle); 

  Y_Cover2Cmd = new G4UIcmdWithADoubleAndUnit("/user/Y_Cover2",this);  
  Y_Cover2Cmd->SetGuidance("\tY coordinate of the Cover2 volume center.");
  Y_Cover2Cmd->SetDefaultValue (0);
  Y_Cover2Cmd->SetDefaultUnit("mm");
  Y_Cover2Cmd->SetUnitCategory("Length");
  Y_Cover2Cmd->SetParameterName("Y_Cover2",omittable=false);
  Y_Cover2Cmd->AvailableForStates(G4State_PreInit,G4State_Idle); 

  Rot_Cover2Cmd = new G4UIcmdWith3VectorAndUnit("/user/Rot_Cover2", this);
  Rot_Cover2Cmd->SetGuidance("\tSet rotation angles for the volume Cover2 (X Y Z).");
  Rot_Cover2Cmd->SetUnitCategory("Angle");
  Rot_Cover2Cmd->SetDefaultUnit("deg");
  Rot_Cover2Cmd->SetParameterName("RotX", "RotY", "RotZ", false);
  Rot_Cover2Cmd->AvailableForStates(G4State_PreInit, G4State_Idle);


  MaterialCover2DensityCmd = new G4UIcmdWithADoubleAndUnit("/user/MaterialCover2Density",this);  
  MaterialCover2DensityCmd->SetGuidance("\tDensity of Cover2 (Marinelli) material.");
  MaterialCover2DensityCmd->SetDefaultValue (10);
  MaterialCover2DensityCmd->SetDefaultUnit("g/cm3");
  MaterialCover2DensityCmd->SetUnitCategory("Volumic Mass");
  MaterialCover2DensityCmd->SetParameterName("MaterialCover2Density",omittable=false);
  MaterialCover2DensityCmd->SetRange("MaterialCover2Density>0."); 
  MaterialCover2DensityCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  MaterialCover2ElementNameCmd = new G4UIcmdWithAString("/user/MaterialCover2ElementName",this);  
  MaterialCover2ElementNameCmd->SetGuidance("\tName of chemical element.");
  MaterialCover2ElementNameCmd->SetDefaultValue ("Cu");
  MaterialCover2ElementNameCmd->SetCandidates("H He Li Be B C N O F Ne Na Mg Al Si P S Cl Ar K Ca Sc Ti V Cr Mn Fe Co Ni Cu Zn Ga Ge As Se Br Kr Rb Sr Y Zr Nb Mo Tc Ru Rh Pd Ag Cd In Sn Sb Te I Xe Cs Ba La Ce Pr Nd Pm Sm Eu Gd Tb Dy Ho Er Tm Yb Lu Hf Ta W Re Os Ir Pt Au Hg Tl Pb Bi Po At Rn Fr Ra Ac Th Pa U Np Pu Am Cm Bk Cf Es Fm");
  MaterialCover2ElementNameCmd->SetParameterName("MaterialCover2ElementName",omittable=false);
  MaterialCover2ElementNameCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  MaterialCover2WeightCmd = new G4UIcmdWithAString("/user/MaterialCover2Weight", this);
  MaterialCover2WeightCmd->SetGuidance("\tProvide element-weight pairs. Example: Cd 1000 W 100 O 10");
  MaterialCover2WeightCmd->SetParameterName("MaterialCover2Weight", false);
  MaterialCover2WeightCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  MaterialCover2FormulaNumCmd = new G4UIcmdWithAnInteger("/user/MaterialCover2FormulaNum",this);  
  MaterialCover2FormulaNumCmd->SetGuidance("\tNumber of atoms of chemical element in the formula.");
  MaterialCover2FormulaNumCmd->SetDefaultValue (1);
  MaterialCover2FormulaNumCmd->SetParameterName("MaterialCover2FormulaNum",omittable=false);
  MaterialCover2FormulaNumCmd->SetRange("MaterialCover2FormulaNum>=0"); 
  MaterialCover2FormulaNumCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  


  D_MarinelliCmd = new G4UIcmdWithADoubleAndUnit("/user/D_Marinelli",this);  
  D_MarinelliCmd->SetGuidance("\tDiameter of the Marinelli volume (if it is a cylinder).");
  D_MarinelliCmd->SetDefaultValue (60);
  D_MarinelliCmd->SetDefaultUnit("mm");
  D_MarinelliCmd->SetUnitCategory("Length");
  D_MarinelliCmd->SetParameterName("D_Marinelli",omittable=false);
  D_MarinelliCmd->SetRange("D_Marinelli>=0."); 
  D_MarinelliCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  XL_MarinelliCmd = new G4UIcmdWithADoubleAndUnit("/user/XL_Marinelli",this);  
  XL_MarinelliCmd->SetGuidance("\tX size of the Marinelli volume (if it is a prism).");
  XL_MarinelliCmd->SetDefaultValue (60);
  XL_MarinelliCmd->SetDefaultUnit("mm");
  XL_MarinelliCmd->SetUnitCategory("Length");
  XL_MarinelliCmd->SetParameterName("XL_Marinelli",omittable=false);
  XL_MarinelliCmd->SetRange("XL_Marinelli>=0."); 
  XL_MarinelliCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  YL_MarinelliCmd = new G4UIcmdWithADoubleAndUnit("/user/YL_Marinelli",this);  
  YL_MarinelliCmd->SetGuidance("\tY size of the Marinelli volume (if it is a prism).");
  YL_MarinelliCmd->SetDefaultValue (60);
  YL_MarinelliCmd->SetDefaultUnit("mm");
  YL_MarinelliCmd->SetUnitCategory("Length");
  YL_MarinelliCmd->SetParameterName("YL_Marinelli",omittable=false);
  YL_MarinelliCmd->SetRange("YL_Marinelli>=0."); 
  YL_MarinelliCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  ZL_MarinelliCmd = new G4UIcmdWithADoubleAndUnit("/user/ZL_Marinelli",this);  
  ZL_MarinelliCmd->SetGuidance("\tZ size (height) of the Marinelli volume.");
  ZL_MarinelliCmd->SetDefaultValue (60);
  ZL_MarinelliCmd->SetDefaultUnit("mm");
  ZL_MarinelliCmd->SetUnitCategory("Length");
  ZL_MarinelliCmd->SetParameterName("ZL_Marinelli",omittable=false);
  ZL_MarinelliCmd->SetRange("ZL_Marinelli>=0."); 
  ZL_MarinelliCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  Z_MarinelliCmd = new G4UIcmdWithADoubleAndUnit("/user/Z_Marinelli",this);  
  Z_MarinelliCmd->SetGuidance("\tZ coordinate of the Marinelli volume center.");
  Z_MarinelliCmd->SetDefaultValue (0);
  Z_MarinelliCmd->SetDefaultUnit("mm");
  Z_MarinelliCmd->SetUnitCategory("Length");
  Z_MarinelliCmd->SetParameterName("Z_Marinelli",omittable=false);
  Z_MarinelliCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  X_MarinelliCmd = new G4UIcmdWithADoubleAndUnit("/user/X_Marinelli",this);  
  X_MarinelliCmd->SetGuidance("\tX coordinate of the Marinelli volume center.");
  X_MarinelliCmd->SetDefaultValue (0);
  X_MarinelliCmd->SetDefaultUnit("mm");
  X_MarinelliCmd->SetUnitCategory("Length");
  X_MarinelliCmd->SetParameterName("X_Marinelli",omittable=false);
  X_MarinelliCmd->AvailableForStates(G4State_PreInit,G4State_Idle); 

  Y_MarinelliCmd = new G4UIcmdWithADoubleAndUnit("/user/Y_Marinelli",this);  
  Y_MarinelliCmd->SetGuidance("\tY coordinate of the Marinelli volume center.");
  Y_MarinelliCmd->SetDefaultValue (0);
  Y_MarinelliCmd->SetDefaultUnit("mm");
  Y_MarinelliCmd->SetUnitCategory("Length");
  Y_MarinelliCmd->SetParameterName("Y_Marinelli",omittable=false);
  Y_MarinelliCmd->AvailableForStates(G4State_PreInit,G4State_Idle); 

  Rot_MarinelliCmd = new G4UIcmdWith3VectorAndUnit("/user/Rot_Marinelli", this);
  Rot_MarinelliCmd->SetGuidance("\tSet rotation angles for the volume Marinelli (X Y Z).");
  Rot_MarinelliCmd->SetUnitCategory("Angle");
  Rot_MarinelliCmd->SetDefaultUnit("deg");
  Rot_MarinelliCmd->SetParameterName("RotX", "RotY", "RotZ", false);
  Rot_MarinelliCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  MaterialMarinelliDensityCmd = new G4UIcmdWithADoubleAndUnit("/user/MaterialMarinelliDensity",this);  
  MaterialMarinelliDensityCmd->SetGuidance("\tDensity of Cover2 (Marinelli) material.");
  MaterialMarinelliDensityCmd->SetDefaultValue (10);
  MaterialMarinelliDensityCmd->SetDefaultUnit("g/cm3");
  MaterialMarinelliDensityCmd->SetUnitCategory("Volumic Mass");
  MaterialMarinelliDensityCmd->SetParameterName("MaterialMarinelliDensity",omittable=false);
  MaterialMarinelliDensityCmd->SetRange("MaterialMarinelliDensity>0."); 
  MaterialMarinelliDensityCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  MaterialMarinelliElementNameCmd = new G4UIcmdWithAString("/user/MaterialMarinelliElementName",this);  
  MaterialMarinelliElementNameCmd->SetGuidance("\tName of chemical element.");
  MaterialMarinelliElementNameCmd->SetDefaultValue ("Cu");
  MaterialMarinelliElementNameCmd->SetCandidates("H He Li Be B C N O F Ne Na Mg Al Si P S Cl Ar K Ca Sc Ti V Cr Mn Fe Co Ni Cu Zn Ga Ge As Se Br Kr Rb Sr Y Zr Nb Mo Tc Ru Rh Pd Ag Cd In Sn Sb Te I Xe Cs Ba La Ce Pr Nd Pm Sm Eu Gd Tb Dy Ho Er Tm Yb Lu Hf Ta W Re Os Ir Pt Au Hg Tl Pb Bi Po At Rn Fr Ra Ac Th Pa U Np Pu Am Cm Bk Cf Es Fm");
  MaterialMarinelliElementNameCmd->SetParameterName("MaterialMarinelliElementName",omittable=false);
  MaterialMarinelliElementNameCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  MaterialMarinelliWeightCmd = new G4UIcmdWithAString("/user/MaterialMarinelliWeight", this);
  MaterialMarinelliWeightCmd->SetGuidance("\tProvide element-weight pairs. Example: Cd 1000 W 100 O 10");
  MaterialMarinelliWeightCmd->SetParameterName("MaterialMarinelliWeight", false);
  MaterialMarinelliWeightCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  MaterialMarinelliFormulaNumCmd = new G4UIcmdWithAnInteger("/user/MaterialMarinelliFormulaNum",this);  
  MaterialMarinelliFormulaNumCmd->SetGuidance("\tNumber of atoms of chemical element in the formula.");
  MaterialMarinelliFormulaNumCmd->SetDefaultValue (1);
  MaterialMarinelliFormulaNumCmd->SetParameterName("MaterialMarinelliFormulaNum",omittable=false);
  MaterialMarinelliFormulaNumCmd->SetRange("MaterialMarinelliFormulaNum>=0"); 
  MaterialMarinelliFormulaNumCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  
 	
//=======Cover1 (alias:Core):================
  Detector_Cover1Cmd = new G4UIcmdWithAnInteger("/user/isCover1aDetector",this);  
  Detector_Cover1Cmd->SetGuidance("\tIs Cover1 a detector?");
  Detector_Cover1Cmd->SetDefaultValue (0);
  // Detector_Cover1Cmd->SetUnitCategory("Boolean");
  Detector_Cover1Cmd->SetParameterName("isCover1aDetector",omittable=false);
  Detector_Cover1Cmd->SetRange("isCover1aDetector==0 || isCover1aDetector==1"); 
  Detector_Cover1Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  D_Cover1Cmd = new G4UIcmdWithADoubleAndUnit("/user/D_Cover1",this);  
  D_Cover1Cmd->SetGuidance("\tDiameter of the Cover1 volume (if it is a cylinder).");
  D_Cover1Cmd->SetDefaultValue (60);
  D_Cover1Cmd->SetDefaultUnit("mm");
  D_Cover1Cmd->SetUnitCategory("Length");
  D_Cover1Cmd->SetParameterName("D_Cover1",omittable=false);
  D_Cover1Cmd->SetRange("D_Cover1>=0."); 
  D_Cover1Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  XL_Cover1Cmd = new G4UIcmdWithADoubleAndUnit("/user/XL_Cover1",this);  
  XL_Cover1Cmd->SetGuidance("\tX size of the Cover1 volume (if it is a prism).");
  XL_Cover1Cmd->SetDefaultValue (60);
  XL_Cover1Cmd->SetDefaultUnit("mm");
  XL_Cover1Cmd->SetUnitCategory("Length");
  XL_Cover1Cmd->SetParameterName("XL_Cover1",omittable=false);
  XL_Cover1Cmd->SetRange("XL_Cover1>=0."); 
  XL_Cover1Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  YL_Cover1Cmd = new G4UIcmdWithADoubleAndUnit("/user/YL_Cover1",this);  
  YL_Cover1Cmd->SetGuidance("\tY size of the Cover1 volume (if it is a prism).");
  YL_Cover1Cmd->SetDefaultValue (60);
  YL_Cover1Cmd->SetDefaultUnit("mm");
  YL_Cover1Cmd->SetUnitCategory("Length");
  YL_Cover1Cmd->SetParameterName("YL_Cover1",omittable=false);
  YL_Cover1Cmd->SetRange("YL_Cover1>=0."); 
  YL_Cover1Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  ZL_Cover1Cmd = new G4UIcmdWithADoubleAndUnit("/user/ZL_Cover1",this);  
  ZL_Cover1Cmd->SetGuidance("\tZ size (height) of the Cover1 volume.");
  ZL_Cover1Cmd->SetDefaultValue (60);
  ZL_Cover1Cmd->SetDefaultUnit("mm");
  ZL_Cover1Cmd->SetUnitCategory("Length");
  ZL_Cover1Cmd->SetParameterName("ZL_Cover1",omittable=false);
  ZL_Cover1Cmd->SetRange("ZL_Cover1>=0."); 
  ZL_Cover1Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  Z_Cover1Cmd = new G4UIcmdWithADoubleAndUnit("/user/Z_Cover1",this);  
  Z_Cover1Cmd->SetGuidance("\tZ coordinate of the Cover1 volume center.");
  Z_Cover1Cmd->SetDefaultValue (0);
  Z_Cover1Cmd->SetDefaultUnit("mm");
  Z_Cover1Cmd->SetUnitCategory("Length");
  Z_Cover1Cmd->SetParameterName("Z_Cover1",omittable=false);
  Z_Cover1Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  X_Cover1Cmd = new G4UIcmdWithADoubleAndUnit("/user/X_Cover1",this);  
  X_Cover1Cmd->SetGuidance("\tX coordinate of the Cover1 volume center.");
  X_Cover1Cmd->SetDefaultValue (0);
  X_Cover1Cmd->SetDefaultUnit("mm");
  X_Cover1Cmd->SetUnitCategory("Length");
  X_Cover1Cmd->SetParameterName("X_Cover1",omittable=false);
  X_Cover1Cmd->AvailableForStates(G4State_PreInit,G4State_Idle); 

  Y_Cover1Cmd = new G4UIcmdWithADoubleAndUnit("/user/Y_Cover1",this);  
  Y_Cover1Cmd->SetGuidance("\tY coordinate of the Cover1 volume center.");
  Y_Cover1Cmd->SetDefaultValue (0);
  Y_Cover1Cmd->SetDefaultUnit("mm");
  Y_Cover1Cmd->SetUnitCategory("Length");
  Y_Cover1Cmd->SetParameterName("Y_Cover1",omittable=false);
  Y_Cover1Cmd->AvailableForStates(G4State_PreInit,G4State_Idle); 

  Rot_Cover1Cmd = new G4UIcmdWith3VectorAndUnit("/user/Rot_Cover1", this);
  Rot_Cover1Cmd->SetGuidance("\tSet rotation angles for the volume Cover1 (X Y Z).");
  Rot_Cover1Cmd->SetUnitCategory("Angle");
  Rot_Cover1Cmd->SetDefaultUnit("deg");
  Rot_Cover1Cmd->SetParameterName("RotX", "RotY", "RotZ", false);
  Rot_Cover1Cmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  MaterialCover1DensityCmd = new G4UIcmdWithADoubleAndUnit("/user/MaterialCover1Density",this);  
  MaterialCover1DensityCmd->SetGuidance("\tDensity of Cover1 (Core) material.");
  MaterialCover1DensityCmd->SetDefaultValue (10);
  MaterialCover1DensityCmd->SetDefaultUnit("g/cm3");
  MaterialCover1DensityCmd->SetUnitCategory("Volumic Mass");
  MaterialCover1DensityCmd->SetParameterName("MaterialCover1Density",omittable=false);
  MaterialCover1DensityCmd->SetRange("MaterialCover1Density>0."); 
  MaterialCover1DensityCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  MaterialCover1ElementNameCmd = new G4UIcmdWithAString("/user/MaterialCover1ElementName",this);  
  MaterialCover1ElementNameCmd->SetGuidance("\tName of chemical element.");
  MaterialCover1ElementNameCmd->SetDefaultValue ("Cu");
  MaterialCover1ElementNameCmd->SetCandidates("H He Li Be B C N O F Ne Na Mg Al Si P S Cl Ar K Ca Sc Ti V Cr Mn Fe Co Ni Cu Zn Ga Ge As Se Br Kr Rb Sr Y Zr Nb Mo Tc Ru Rh Pd Ag Cd In Sn Sb Te I Xe Cs Ba La Ce Pr Nd Pm Sm Eu Gd Tb Dy Ho Er Tm Yb Lu Hf Ta W Re Os Ir Pt Au Hg Tl Pb Bi Po At Rn Fr Ra Ac Th Pa U Np Pu Am Cm Bk Cf Es Fm");
  MaterialCover1ElementNameCmd->SetParameterName("MaterialCover1ElementName",omittable=false);
  MaterialCover1ElementNameCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  MaterialCover1WeightCmd = new G4UIcmdWithAString("/user/MaterialCover1Weight", this);
  MaterialCover1WeightCmd->SetGuidance("\tProvide element-weight pairs. Example: Cd 1000 W 100 O 10");
  MaterialCover1WeightCmd->SetParameterName("MaterialCover1Weight", false);
  MaterialCover1WeightCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  MaterialCover1FormulaNumCmd = new G4UIcmdWithAnInteger("/user/MaterialCover1FormulaNum",this);  
  MaterialCover1FormulaNumCmd->SetGuidance("\tNumber of atoms of chemical element in the formula.");
  MaterialCover1FormulaNumCmd->SetDefaultValue (1);
  MaterialCover1FormulaNumCmd->SetParameterName("MaterialCover1FormulaNum",omittable=false);
  MaterialCover1FormulaNumCmd->SetRange("MaterialCover1FormulaNum>=0"); 
  MaterialCover1FormulaNumCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  


  D_CoreCmd = new G4UIcmdWithADoubleAndUnit("/user/D_Core",this);  
  D_CoreCmd->SetGuidance("\tDiameter of the Core volume (if it is a cylinder).");
  D_CoreCmd->SetDefaultValue (60);
  D_CoreCmd->SetDefaultUnit("mm");
  D_CoreCmd->SetUnitCategory("Length");
  D_CoreCmd->SetParameterName("D_Core",omittable=false);
  D_CoreCmd->SetRange("D_Core>=0."); 
  D_CoreCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  XL_CoreCmd = new G4UIcmdWithADoubleAndUnit("/user/XL_Core",this);  
  XL_CoreCmd->SetGuidance("\tX size of the Core volume (if it is a prism).");
  XL_CoreCmd->SetDefaultValue (60);
  XL_CoreCmd->SetDefaultUnit("mm");
  XL_CoreCmd->SetUnitCategory("Length");
  XL_CoreCmd->SetParameterName("XL_Core",omittable=false);
  XL_CoreCmd->SetRange("XL_Core>=0."); 
  XL_CoreCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  YL_CoreCmd = new G4UIcmdWithADoubleAndUnit("/user/YL_Core",this);  
  YL_CoreCmd->SetGuidance("\tY size of the Core volume (if it is a prism).");
  YL_CoreCmd->SetDefaultValue (60);
  YL_CoreCmd->SetDefaultUnit("mm");
  YL_CoreCmd->SetUnitCategory("Length");
  YL_CoreCmd->SetParameterName("YL_Core",omittable=false);
  YL_CoreCmd->SetRange("YL_Core>=0."); 
  YL_CoreCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  ZL_CoreCmd = new G4UIcmdWithADoubleAndUnit("/user/ZL_Core",this);  
  ZL_CoreCmd->SetGuidance("\tZ size (height) of the Core volume.");
  ZL_CoreCmd->SetDefaultValue (60);
  ZL_CoreCmd->SetDefaultUnit("mm");
  ZL_CoreCmd->SetUnitCategory("Length");
  ZL_CoreCmd->SetParameterName("ZL_Core",omittable=false);
  ZL_CoreCmd->SetRange("ZL_Core>=0."); 
  ZL_CoreCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  Z_CoreCmd = new G4UIcmdWithADoubleAndUnit("/user/Z_Core",this);  
  Z_CoreCmd->SetGuidance("\tZ coordinate of the Core volume center.");
  Z_CoreCmd->SetDefaultValue (0);
  Z_CoreCmd->SetDefaultUnit("mm");
  Z_CoreCmd->SetUnitCategory("Length");
  Z_CoreCmd->SetParameterName("Z_Core",omittable=false);
  Z_CoreCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  X_CoreCmd = new G4UIcmdWithADoubleAndUnit("/user/X_Core",this);  
  X_CoreCmd->SetGuidance("\tX coordinate of the Core volume center.");
  X_CoreCmd->SetDefaultValue (0);
  X_CoreCmd->SetDefaultUnit("mm");
  X_CoreCmd->SetUnitCategory("Length");
  X_CoreCmd->SetParameterName("X_Core",omittable=false);
  X_CoreCmd->AvailableForStates(G4State_PreInit,G4State_Idle); 

  Y_CoreCmd = new G4UIcmdWithADoubleAndUnit("/user/Y_Core",this);  
  Y_CoreCmd->SetGuidance("\tY coordinate of the Core volume center.");
  Y_CoreCmd->SetDefaultValue (0);
  Y_CoreCmd->SetDefaultUnit("mm");
  Y_CoreCmd->SetUnitCategory("Length");
  Y_CoreCmd->SetParameterName("Y_Core",omittable=false);
  Y_CoreCmd->AvailableForStates(G4State_PreInit,G4State_Idle); 

  Rot_CoreCmd = new G4UIcmdWith3VectorAndUnit("/user/Rot_Core", this);
  Rot_CoreCmd->SetGuidance("\tSet rotation angles for the volume Core (X Y Z).");
  Rot_CoreCmd->SetUnitCategory("Angle");
  Rot_CoreCmd->SetDefaultUnit("deg");
  Rot_CoreCmd->SetParameterName("RotX", "RotY", "RotZ", false);
  Rot_CoreCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  MaterialCoreDensityCmd = new G4UIcmdWithADoubleAndUnit("/user/MaterialCoreDensity",this);  
  MaterialCoreDensityCmd->SetGuidance("\tDensity of Cover1 (Core) material.");
  MaterialCoreDensityCmd->SetDefaultValue (10);
  MaterialCoreDensityCmd->SetDefaultUnit("g/cm3");
  MaterialCoreDensityCmd->SetUnitCategory("Volumic Mass");
  MaterialCoreDensityCmd->SetParameterName("MaterialCoreDensity",omittable=false);
  MaterialCoreDensityCmd->SetRange("MaterialCoreDensity>0."); 
  MaterialCoreDensityCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  MaterialCoreElementNameCmd = new G4UIcmdWithAString("/user/MaterialCoreElementName",this);  
  MaterialCoreElementNameCmd->SetGuidance("\tName of chemical element.");
  MaterialCoreElementNameCmd->SetDefaultValue ("Cu");
  MaterialCoreElementNameCmd->SetCandidates("H He Li Be B C N O F Ne Na Mg Al Si P S Cl Ar K Ca Sc Ti V Cr Mn Fe Co Ni Cu Zn Ga Ge As Se Br Kr Rb Sr Y Zr Nb Mo Tc Ru Rh Pd Ag Cd In Sn Sb Te I Xe Cs Ba La Ce Pr Nd Pm Sm Eu Gd Tb Dy Ho Er Tm Yb Lu Hf Ta W Re Os Ir Pt Au Hg Tl Pb Bi Po At Rn Fr Ra Ac Th Pa U Np Pu Am Cm Bk Cf Es Fm");
  MaterialCoreElementNameCmd->SetParameterName("MaterialCoreElementName",omittable=false);
  MaterialCoreElementNameCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  MaterialCoreWeightCmd = new G4UIcmdWithAString("/user/MaterialCoreWeight", this);
  MaterialCoreWeightCmd->SetGuidance("\tProvide element-weight pairs. Example: Cd 1000 W 100 O 10");
  MaterialCoreWeightCmd->SetParameterName("MaterialCoreWeight", false);
  MaterialCoreWeightCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  MaterialCoreFormulaNumCmd = new G4UIcmdWithAnInteger("/user/MaterialCoreFormulaNum",this);  
  MaterialCoreFormulaNumCmd->SetGuidance("\tNumber of atoms of chemical element in the formula.");
  MaterialCoreFormulaNumCmd->SetDefaultValue (1);
  MaterialCoreFormulaNumCmd->SetParameterName("MaterialCoreFormulaNum",omittable=false);
  MaterialCoreFormulaNumCmd->SetRange("MaterialCoreFormulaNum>=0"); 
  MaterialCoreFormulaNumCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

//=======Detector:================

  D_DetCmd = new G4UIcmdWithADoubleAndUnit("/user/D_Det",this);  
  D_DetCmd->SetGuidance("\tDiameter of the Det volume (if it is a cylinder).");
  D_DetCmd->SetDefaultValue (0);
  D_DetCmd->SetDefaultUnit("mm");
  D_DetCmd->SetUnitCategory("Length");
  D_DetCmd->SetParameterName("D_Det",omittable=false);
  D_DetCmd->SetRange("D_Det>=0.");
  D_DetCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  XL_DetCmd = new G4UIcmdWithADoubleAndUnit("/user/XL_Det",this);  
  XL_DetCmd->SetGuidance("\tX size of the Det volume (if it is a prism).");
  XL_DetCmd->SetDefaultValue (0);
  XL_DetCmd->SetDefaultUnit("mm");
  XL_DetCmd->SetUnitCategory("Length");
  XL_DetCmd->SetParameterName("XL_Det",omittable=false);
  XL_DetCmd->SetRange("XL_Det>=0.");
  XL_DetCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  YL_DetCmd = new G4UIcmdWithADoubleAndUnit("/user/YL_Det",this);  
  YL_DetCmd->SetGuidance("\tY size of the Det volume (if it is a prism).");
  YL_DetCmd->SetDefaultValue (0);
  YL_DetCmd->SetDefaultUnit("mm");
  YL_DetCmd->SetUnitCategory("Length");
  YL_DetCmd->SetParameterName("YL_Det",omittable=false);
  YL_DetCmd->SetRange("YL_Det>=0."); 
  YL_DetCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  ZL_DetCmd = new G4UIcmdWithADoubleAndUnit("/user/ZL_Det",this);  
  ZL_DetCmd->SetGuidance("\tZ size (height) of the Det volume.");
  ZL_DetCmd->SetDefaultValue (0);
  ZL_DetCmd->SetDefaultUnit("mm");
  ZL_DetCmd->SetUnitCategory("Length");
  ZL_DetCmd->SetParameterName("ZL_Det",omittable=false);
  ZL_DetCmd->SetRange("ZL_Det>=0."); 
  ZL_DetCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  Z_DetCmd = new G4UIcmdWithADoubleAndUnit("/user/Z_Det",this);  
  Z_DetCmd->SetGuidance("\tZ coordinate of the Det volume center.");
  Z_DetCmd->SetDefaultValue (0);
  Z_DetCmd->SetDefaultUnit("mm");
  Z_DetCmd->SetUnitCategory("Length");
  Z_DetCmd->SetParameterName("Z_Det",omittable=false);
  Z_DetCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  X_DetCmd = new G4UIcmdWithADoubleAndUnit("/user/X_Det",this);  
  X_DetCmd->SetGuidance("\tX coordinate of the Det volume center.");
  X_DetCmd->SetDefaultValue (0);
  X_DetCmd->SetDefaultUnit("mm");
  X_DetCmd->SetUnitCategory("Length");
  X_DetCmd->SetParameterName("X_Det",omittable=false);
  X_DetCmd->AvailableForStates(G4State_PreInit,G4State_Idle); 

  Y_DetCmd = new G4UIcmdWithADoubleAndUnit("/user/Y_Det",this);  
  Y_DetCmd->SetGuidance("\tY coordinate of the Det volume center.");
  Y_DetCmd->SetDefaultValue (0);
  Y_DetCmd->SetDefaultUnit("mm");
  Y_DetCmd->SetUnitCategory("Length");
  Y_DetCmd->SetParameterName("Y_Det",omittable=false);
  Y_DetCmd->AvailableForStates(G4State_PreInit,G4State_Idle); 

  Rot_DetCmd = new G4UIcmdWith3VectorAndUnit("/user/Rot_Det", this);
  Rot_DetCmd->SetGuidance("\tSet rotation angles for the volume Det (X Y Z).");
  Rot_DetCmd->SetUnitCategory("Angle");
  Rot_DetCmd->SetDefaultUnit("deg");
  Rot_DetCmd->SetParameterName("RotX", "RotY", "RotZ", false);
  Rot_DetCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  MaterialDetDensityCmd = new G4UIcmdWithADoubleAndUnit("/user/MaterialDetDensity",this);  
  MaterialDetDensityCmd->SetGuidance("\tDensity of detector material.");
  MaterialDetDensityCmd->SetDefaultValue (1.0e-20);
  MaterialDetDensityCmd->SetDefaultUnit("g/cm3");
  MaterialDetDensityCmd->SetUnitCategory("Volumic Mass");
  MaterialDetDensityCmd->SetParameterName("MaterialDetDensity",omittable=false);
  MaterialDetDensityCmd->SetRange("MaterialDetDensity>0."); 
  MaterialDetDensityCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  MaterialDetElementNameCmd = new G4UIcmdWithAString("/user/MaterialDetElementName",this);  
  MaterialDetElementNameCmd->SetGuidance("\tName of chemical element.");
  MaterialDetElementNameCmd->SetDefaultValue ("N");
  MaterialDetElementNameCmd->SetCandidates("H He Li Be B C N O F Ne Na Mg Al Si P S Cl Ar K Ca Sc Ti V Cr Mn Fe Co Ni Cu Zn Ga Ge As Se Br Kr Rb Sr Y Zr Nb Mo Tc Ru Rh Pd Ag Cd In Sn Sb Te I Xe Cs Ba La Ce Pr Nd Pm Sm Eu Gd Tb Dy Ho Er Tm Yb Lu Hf Ta W Re Os Ir Pt Au Hg Tl Pb Bi Po At Rn Fr Ra Ac Th Pa U Np Pu Am Cm Bk Cf Es Fm");
  MaterialDetElementNameCmd->SetParameterName("MaterialDetElementName",omittable=false);
  MaterialDetElementNameCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  MaterialDetWeightCmd = new G4UIcmdWithAString("/user/MaterialDetWeight", this);
  MaterialDetWeightCmd->SetGuidance("\tProvide element-weight pairs. Example: Cd 1000 W 100 O 10");
  MaterialDetWeightCmd->SetParameterName("MaterialDetWeight", false);
  MaterialDetWeightCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  MaterialDetFormulaNumCmd = new G4UIcmdWithAnInteger("/user/MaterialDetFormulaNum",this);  
  MaterialDetFormulaNumCmd->SetGuidance("\tNumber of atoms of chemical element in the formula.");
  MaterialDetFormulaNumCmd->SetDefaultValue (1);
  MaterialDetFormulaNumCmd->SetParameterName("MaterialDetFormulaNum",omittable=false);
  MaterialDetFormulaNumCmd->SetRange("MaterialDetFormulaNum>=0"); 
  MaterialDetFormulaNumCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

//=======Cavity:================
  Detector_CavityCmd = new G4UIcmdWithAnInteger("/user/isCavityaDetector",this);  
  Detector_CavityCmd->SetGuidance("\tIs Cavity a detector?");
  Detector_CavityCmd->SetDefaultValue (0);
  // Detector_CavityCmd->SetUnitCategory("Boolean");
  Detector_CavityCmd->SetParameterName("isCavityaDetector",omittable=false);
  Detector_CavityCmd->SetRange("isCavityaDetector==0 || isCavityaDetector==1"); 
  Detector_CavityCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  D_CavityCmd = new G4UIcmdWithADoubleAndUnit("/user/D_Cavity",this);  
  D_CavityCmd->SetGuidance("\tDiameter of the Cavity volume.");
  D_CavityCmd->SetDefaultValue (0.001);
  D_CavityCmd->SetDefaultUnit("mm");
  D_CavityCmd->SetUnitCategory("Length");
  D_CavityCmd->SetParameterName("D_Cavity",omittable=false);
  D_CavityCmd->SetRange("D_Cavity>=0."); 
  D_CavityCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  ZL_CavityCmd = new G4UIcmdWithADoubleAndUnit("/user/ZL_Cavity",this);  
  ZL_CavityCmd->SetGuidance("\tZ size (height) of the Cavity volume.");
  ZL_CavityCmd->SetDefaultValue (0.001);
  ZL_CavityCmd->SetDefaultUnit("mm");
  ZL_CavityCmd->SetUnitCategory("Length");
  ZL_CavityCmd->SetParameterName("ZL_Cavity",omittable=false);
  ZL_CavityCmd->SetRange("ZL_Cavity>=0."); 
  ZL_CavityCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  Z_CavityCmd = new G4UIcmdWithADoubleAndUnit("/user/Z_Cavity",this);  
  Z_CavityCmd->SetGuidance("\tZ coordinate of the Cavity volume center.");
  Z_CavityCmd->SetDefaultValue (0);
  Z_CavityCmd->SetDefaultUnit("mm");
  Z_CavityCmd->SetUnitCategory("Length");
  Z_CavityCmd->SetParameterName("Z_Cavity",omittable=false);
  Z_CavityCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  X_CavityCmd = new G4UIcmdWithADoubleAndUnit("/user/X_Cavity",this);  
  X_CavityCmd->SetGuidance("\tX coordinate of the Cavity volume center.");
  X_CavityCmd->SetDefaultValue (0);
  X_CavityCmd->SetDefaultUnit("mm");
  X_CavityCmd->SetUnitCategory("Length");
  X_CavityCmd->SetParameterName("X_Cavity",omittable=false);
  X_CavityCmd->AvailableForStates(G4State_PreInit,G4State_Idle); 

  Y_CavityCmd = new G4UIcmdWithADoubleAndUnit("/user/Y_Cavity",this);  
  Y_CavityCmd->SetGuidance("\tY coordinate of the Cavity volume center.");
  Y_CavityCmd->SetDefaultValue (0);
  Y_CavityCmd->SetDefaultUnit("mm");
  Y_CavityCmd->SetUnitCategory("Length");
  Y_CavityCmd->SetParameterName("Y_Cavity",omittable=false);
  Y_CavityCmd->AvailableForStates(G4State_PreInit,G4State_Idle); 

  Rot_CavityCmd = new G4UIcmdWith3VectorAndUnit("/user/Rot_Cavity", this);
  Rot_CavityCmd->SetGuidance("\tSet rotation angles for the volume Cavity (X Y Z).");
  Rot_CavityCmd->SetUnitCategory("Angle");
  Rot_CavityCmd->SetDefaultUnit("deg");
  Rot_CavityCmd->SetParameterName("RotX", "RotY", "RotZ", false);
  Rot_CavityCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  MaterialCavityDensityCmd = new G4UIcmdWithADoubleAndUnit("/user/MaterialCavityDensity",this);  
  MaterialCavityDensityCmd->SetGuidance("\tDensity of core material.");
  MaterialCavityDensityCmd->SetDefaultValue (10);
  MaterialCavityDensityCmd->SetDefaultUnit("g/cm3");
  MaterialCavityDensityCmd->SetUnitCategory("Volumic Mass");
  MaterialCavityDensityCmd->SetParameterName("MaterialCavityDensity",omittable=false);
  MaterialCavityDensityCmd->SetRange("MaterialCavityDensity>0."); 
  MaterialCavityDensityCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  MaterialCavityElementNameCmd = new G4UIcmdWithAString("/user/MaterialCavityElementName",this);  
  MaterialCavityElementNameCmd->SetGuidance("\tName of chemical element.");
  MaterialCavityElementNameCmd->SetDefaultValue ("Cu");
  MaterialCavityElementNameCmd->SetCandidates("H He Li Be B C N O F Ne Na Mg Al Si P S Cl Ar K Ca Sc Ti V Cr Mn Fe Co Ni Cu Zn Ga Ge As Se Br Kr Rb Sr Y Zr Nb Mo Tc Ru Rh Pd Ag Cd In Sn Sb Te I Xe Cs Ba La Ce Pr Nd Pm Sm Eu Gd Tb Dy Ho Er Tm Yb Lu Hf Ta W Re Os Ir Pt Au Hg Tl Pb Bi Po At Rn Fr Ra Ac Th Pa U Np Pu Am Cm Bk Cf Es Fm");
  MaterialCavityElementNameCmd->SetParameterName("MaterialCavityElementName",omittable=false);
  MaterialCavityElementNameCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  MaterialCavityWeightCmd = new G4UIcmdWithAString("/user/MaterialCavityWeight", this);
  MaterialCavityWeightCmd->SetGuidance("\tProvide element-weight pairs. Example: Cd 1000 W 100 O 10");
  MaterialCavityWeightCmd->SetParameterName("MaterialCavityWeight", false);
  MaterialCavityWeightCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  MaterialCavityFormulaNumCmd = new G4UIcmdWithAnInteger("/user/MaterialCavityFormulaNum",this);  
  MaterialCavityFormulaNumCmd->SetGuidance("\tNumber of atoms of chemical element in the formula.");
  MaterialCavityFormulaNumCmd->SetDefaultValue (1);
  MaterialCavityFormulaNumCmd->SetParameterName("MaterialCavityFormulaNum",omittable=false);
  MaterialCavityFormulaNumCmd->SetRange("MaterialCavityFormulaNum>=0"); 
  MaterialCavityFormulaNumCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

//=======Top1:================
  Detector_Top1Cmd = new G4UIcmdWithAnInteger("/user/isTop1aDetector",this);  
  Detector_Top1Cmd->SetGuidance("\tIs top1 a detector?");
  Detector_Top1Cmd->SetDefaultValue (0);
  // Detector_Top1Cmd->SetUnitCategory("Boolean");
  Detector_Top1Cmd->SetParameterName("isTop1aDetector",omittable=false);
  Detector_Top1Cmd->SetRange("isTop1aDetector==0 || isTop1aDetector==1"); 
  Detector_Top1Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);



  D_Top1Cmd = new G4UIcmdWithADoubleAndUnit("/user/D_Top1",this);  
  D_Top1Cmd->SetGuidance("\tDiameter of the Top1 volume.");
  D_Top1Cmd->SetDefaultValue (0.001);
  D_Top1Cmd->SetDefaultUnit("mm");
  D_Top1Cmd->SetUnitCategory("Length");
  D_Top1Cmd->SetParameterName("D_Top1",omittable=false);
  D_Top1Cmd->SetRange("D_Top1>=0."); 
  D_Top1Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  d_Top1Cmd = new G4UIcmdWithADoubleAndUnit("/user/d_Top1",this);  
  d_Top1Cmd->SetGuidance("\tDiameter of the Top1 volume.");
  d_Top1Cmd->SetDefaultValue (0.001);
  d_Top1Cmd->SetDefaultUnit("mm");
  d_Top1Cmd->SetUnitCategory("Length");
  d_Top1Cmd->SetParameterName("d_Top1",omittable=false);
  d_Top1Cmd->SetRange("d_Top1>=0."); 
  d_Top1Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  ZL_Top1Cmd = new G4UIcmdWithADoubleAndUnit("/user/ZL_Top1",this);  
  ZL_Top1Cmd->SetGuidance("\tZ size (height) of the Top1 volume.");
  ZL_Top1Cmd->SetDefaultValue (0.001);
  ZL_Top1Cmd->SetDefaultUnit("mm");
  ZL_Top1Cmd->SetUnitCategory("Length");
  ZL_Top1Cmd->SetParameterName("ZL_Top1",omittable=false);
  ZL_Top1Cmd->SetRange("ZL_Top1>=0."); 
  ZL_Top1Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  Z_Top1Cmd = new G4UIcmdWithADoubleAndUnit("/user/Z_Top1",this);  
  Z_Top1Cmd->SetGuidance("\tZ coordinate of the Top1 volume center.");
  Z_Top1Cmd->SetDefaultValue (31);
  Z_Top1Cmd->SetDefaultUnit("mm");
  Z_Top1Cmd->SetUnitCategory("Length");
  Z_Top1Cmd->SetParameterName("Z_Top1",omittable=false);
  Z_Top1Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  X_Top1Cmd = new G4UIcmdWithADoubleAndUnit("/user/X_Top1",this);  
  X_Top1Cmd->SetGuidance("\tX coordinate of the Top1 volume center.");
  X_Top1Cmd->SetDefaultValue (0);
  X_Top1Cmd->SetDefaultUnit("mm");
  X_Top1Cmd->SetUnitCategory("Length");
  X_Top1Cmd->SetParameterName("X_Top1",omittable=false);
  X_Top1Cmd->AvailableForStates(G4State_PreInit,G4State_Idle); 

  Y_Top1Cmd = new G4UIcmdWithADoubleAndUnit("/user/Y_Top1",this);  
  Y_Top1Cmd->SetGuidance("\tY coordinate of the Top1 volume center.");
  Y_Top1Cmd->SetDefaultValue (0);
  Y_Top1Cmd->SetDefaultUnit("mm");
  Y_Top1Cmd->SetUnitCategory("Length");
  Y_Top1Cmd->SetParameterName("Y_Top1",omittable=false);
  Y_Top1Cmd->AvailableForStates(G4State_PreInit,G4State_Idle); 

  Rot_Top1Cmd = new G4UIcmdWith3VectorAndUnit("/user/Rot_Top1", this);
  Rot_Top1Cmd->SetGuidance("\tSet rotation angles for the volume Top1 (X Y Z).");
  Rot_Top1Cmd->SetUnitCategory("Angle");
  Rot_Top1Cmd->SetDefaultUnit("deg");
  Rot_Top1Cmd->SetParameterName("RotX", "RotY", "RotZ", false);
  Rot_Top1Cmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  MaterialTop1DensityCmd = new G4UIcmdWithADoubleAndUnit("/user/MaterialTop1Density",this);  
  MaterialTop1DensityCmd->SetGuidance("\tDensity of core material.");
  MaterialTop1DensityCmd->SetDefaultValue (10);
  MaterialTop1DensityCmd->SetDefaultUnit("g/cm3");
  MaterialTop1DensityCmd->SetUnitCategory("Volumic Mass");
  MaterialTop1DensityCmd->SetParameterName("MaterialTop1Density",omittable=false);
  MaterialTop1DensityCmd->SetRange("MaterialTop1Density>0."); 
  MaterialTop1DensityCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  MaterialTop1ElementNameCmd = new G4UIcmdWithAString("/user/MaterialTop1ElementName",this);  
  MaterialTop1ElementNameCmd->SetGuidance("\tName of chemical element.");
  MaterialTop1ElementNameCmd->SetDefaultValue ("Cu");
  MaterialTop1ElementNameCmd->SetCandidates("H He Li Be B C N O F Ne Na Mg Al Si P S Cl Ar K Ca Sc Ti V Cr Mn Fe Co Ni Cu Zn Ga Ge As Se Br Kr Rb Sr Y Zr Nb Mo Tc Ru Rh Pd Ag Cd In Sn Sb Te I Xe Cs Ba La Ce Pr Nd Pm Sm Eu Gd Tb Dy Ho Er Tm Yb Lu Hf Ta W Re Os Ir Pt Au Hg Tl Pb Bi Po At Rn Fr Ra Ac Th Pa U Np Pu Am Cm Bk Cf Es Fm");
  MaterialTop1ElementNameCmd->SetParameterName("MaterialTop1ElementName",omittable=false);
  MaterialTop1ElementNameCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  MaterialTop1WeightCmd = new G4UIcmdWithAString("/user/MaterialTop1Weight", this);
  MaterialTop1WeightCmd->SetGuidance("\tProvide element-weight pairs. Example: Cd 1000 W 100 O 10");
  MaterialTop1WeightCmd->SetParameterName("MaterialTop1Weight", false);
  MaterialTop1WeightCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  MaterialTop1FormulaNumCmd = new G4UIcmdWithAnInteger("/user/MaterialTop1FormulaNum",this);  
  MaterialTop1FormulaNumCmd->SetGuidance("\tNumber of atoms of chemical element in the formula.");
  MaterialTop1FormulaNumCmd->SetDefaultValue (1);
  MaterialTop1FormulaNumCmd->SetParameterName("MaterialTop1FormulaNum",omittable=false);
  MaterialTop1FormulaNumCmd->SetRange("MaterialTop1FormulaNum>=0"); 
  MaterialTop1FormulaNumCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

//=======Top2:================
  Detector_Top2Cmd = new G4UIcmdWithAnInteger("/user/isTop2aDetector",this);  
  Detector_Top2Cmd->SetGuidance("\tIs Top2 a detector?");
  Detector_Top2Cmd->SetDefaultValue (0);
  // Detector_Top2Cmd->SetUnitCategory("Boolean");
  Detector_Top2Cmd->SetParameterName("isTop2aDetector",omittable=false);
  Detector_Top2Cmd->SetRange("isTop2aDetector==0 || isTop2aDetector==1"); 
  Detector_Top2Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  D_Top2Cmd = new G4UIcmdWithADoubleAndUnit("/user/D_Top2",this);  
  D_Top2Cmd->SetGuidance("\tDiameter of the Top2 volume.");
  D_Top2Cmd->SetDefaultValue (0.001);
  D_Top2Cmd->SetDefaultUnit("mm");
  D_Top2Cmd->SetUnitCategory("Length");
  D_Top2Cmd->SetParameterName("D_Top2",omittable=false);
  D_Top2Cmd->SetRange("D_Top2>=0."); 
  D_Top2Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  d_Top2Cmd = new G4UIcmdWithADoubleAndUnit("/user/d_Top2",this);  
  d_Top2Cmd->SetGuidance("\tDiameter of the Top2 volume.");
  d_Top2Cmd->SetDefaultValue (0.001);
  d_Top2Cmd->SetDefaultUnit("mm");
  d_Top2Cmd->SetUnitCategory("Length");
  d_Top2Cmd->SetParameterName("d_Top2",omittable=false);
  d_Top2Cmd->SetRange("d_Top2>=0."); 
  d_Top2Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);


  ZL_Top2Cmd = new G4UIcmdWithADoubleAndUnit("/user/ZL_Top2",this);  
  ZL_Top2Cmd->SetGuidance("\tZ size (height) of the Top2 volume.");
  ZL_Top2Cmd->SetDefaultValue (0.001);
  ZL_Top2Cmd->SetDefaultUnit("mm");
  ZL_Top2Cmd->SetUnitCategory("Length");
  ZL_Top2Cmd->SetParameterName("ZL_Top2",omittable=false);
  ZL_Top2Cmd->SetRange("ZL_Top2>=0."); 
  ZL_Top2Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  Z_Top2Cmd = new G4UIcmdWithADoubleAndUnit("/user/Z_Top2",this);  
  Z_Top2Cmd->SetGuidance("\tZ coordinate of the Top2 volume center.");
  Z_Top2Cmd->SetDefaultValue (32);
  Z_Top2Cmd->SetDefaultUnit("mm");
  Z_Top2Cmd->SetUnitCategory("Length");
  Z_Top2Cmd->SetParameterName("Z_Top2",omittable=false);
  Z_Top2Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  X_Top2Cmd = new G4UIcmdWithADoubleAndUnit("/user/X_Top2",this);  
  X_Top2Cmd->SetGuidance("\tX coordinate of the Top2 volume center.");
  X_Top2Cmd->SetDefaultValue (0);
  X_Top2Cmd->SetDefaultUnit("mm");
  X_Top2Cmd->SetUnitCategory("Length");
  X_Top2Cmd->SetParameterName("X_Top2",omittable=false);
  X_Top2Cmd->AvailableForStates(G4State_PreInit,G4State_Idle); 

  Y_Top2Cmd = new G4UIcmdWithADoubleAndUnit("/user/Y_Top2",this);  
  Y_Top2Cmd->SetGuidance("\tY coordinate of the Top2 volume center.");
  Y_Top2Cmd->SetDefaultValue (0);
  Y_Top2Cmd->SetDefaultUnit("mm");
  Y_Top2Cmd->SetUnitCategory("Length");
  Y_Top2Cmd->SetParameterName("Y_Top2",omittable=false);
  Y_Top2Cmd->AvailableForStates(G4State_PreInit,G4State_Idle); 

  Rot_Top2Cmd = new G4UIcmdWith3VectorAndUnit("/user/Rot_Top2", this);
  Rot_Top2Cmd->SetGuidance("\tSet rotation angles for the volume Top2 (X Y Z).");
  Rot_Top2Cmd->SetUnitCategory("Angle");
  Rot_Top2Cmd->SetDefaultUnit("deg");
  Rot_Top2Cmd->SetParameterName("RotX", "RotY", "RotZ", false);
  Rot_Top2Cmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  MaterialTop2DensityCmd = new G4UIcmdWithADoubleAndUnit("/user/MaterialTop2Density",this);  
  MaterialTop2DensityCmd->SetGuidance("\tDensity of core material.");
  MaterialTop2DensityCmd->SetDefaultValue (10);
  MaterialTop2DensityCmd->SetDefaultUnit("g/cm3");
  MaterialTop2DensityCmd->SetUnitCategory("Volumic Mass");
  MaterialTop2DensityCmd->SetParameterName("MaterialTop2Density",omittable=false);
  MaterialTop2DensityCmd->SetRange("MaterialTop2Density>0."); 
  MaterialTop2DensityCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  MaterialTop2ElementNameCmd = new G4UIcmdWithAString("/user/MaterialTop2ElementName",this);  
  MaterialTop2ElementNameCmd->SetGuidance("\tName of chemical element.");
  MaterialTop2ElementNameCmd->SetDefaultValue ("Cu");
  MaterialTop2ElementNameCmd->SetCandidates("H He Li Be B C N O F Ne Na Mg Al Si P S Cl Ar K Ca Sc Ti V Cr Mn Fe Co Ni Cu Zn Ga Ge As Se Br Kr Rb Sr Y Zr Nb Mo Tc Ru Rh Pd Ag Cd In Sn Sb Te I Xe Cs Ba La Ce Pr Nd Pm Sm Eu Gd Tb Dy Ho Er Tm Yb Lu Hf Ta W Re Os Ir Pt Au Hg Tl Pb Bi Po At Rn Fr Ra Ac Th Pa U Np Pu Am Cm Bk Cf Es Fm");
  MaterialTop2ElementNameCmd->SetParameterName("MaterialTop2ElementName",omittable=false);
  MaterialTop2ElementNameCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  MaterialTop2WeightCmd = new G4UIcmdWithAString("/user/MaterialTop2Weight", this);
  MaterialTop2WeightCmd->SetGuidance("\tProvide element-weight pairs. Example: Cd 1000 W 100 O 10");
  MaterialTop2WeightCmd->SetParameterName("MaterialTop2Weight", false);
  MaterialTop2WeightCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  MaterialTop2FormulaNumCmd = new G4UIcmdWithAnInteger("/user/MaterialTop2FormulaNum",this);  
  MaterialTop2FormulaNumCmd->SetGuidance("\tNumber of atoms of chemical element in the formula.");
  MaterialTop2FormulaNumCmd->SetDefaultValue (1);
  MaterialTop2FormulaNumCmd->SetParameterName("MaterialTop2FormulaNum",omittable=false);
  MaterialTop2FormulaNumCmd->SetRange("MaterialTop2FormulaNum>=0"); 
  MaterialTop2FormulaNumCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

//=======Top3:================
  Detector_Top3Cmd = new G4UIcmdWithAnInteger("/user/isTop3aDetector",this);  
  Detector_Top3Cmd->SetGuidance("\tIs Top3 a detector?");
  Detector_Top3Cmd->SetDefaultValue (0);
  // Detector_Top3Cmd->SetUnitCategory("Boolean");
  Detector_Top3Cmd->SetParameterName("isTop3aDetector",omittable=false);
  Detector_Top3Cmd->SetRange("isTop3aDetector==0 || isTop3aDetector==1"); 
  Detector_Top3Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);


  D_Top3Cmd = new G4UIcmdWithADoubleAndUnit("/user/D_Top3",this);  
  D_Top3Cmd->SetGuidance("\tDiameter of the Top3 volume.");
  D_Top3Cmd->SetDefaultValue (0.001);
  D_Top3Cmd->SetDefaultUnit("mm");
  D_Top3Cmd->SetUnitCategory("Length");
  D_Top3Cmd->SetParameterName("D_Top3",omittable=false);
  D_Top3Cmd->SetRange("D_Top3>=0."); 
  D_Top3Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  d_Top3Cmd = new G4UIcmdWithADoubleAndUnit("/user/d_Top3",this);  
  d_Top3Cmd->SetGuidance("\tInner diameter of the Top3 volume.");
  d_Top3Cmd->SetDefaultValue (0.001);
  d_Top3Cmd->SetDefaultUnit("mm");
  d_Top3Cmd->SetUnitCategory("Length");
  d_Top3Cmd->SetParameterName("d_Top3",omittable=false);
  d_Top3Cmd->SetRange("d_Top3>=0."); 
  d_Top3Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  ZL_Top3Cmd = new G4UIcmdWithADoubleAndUnit("/user/ZL_Top3",this);  
  ZL_Top3Cmd->SetGuidance("\tZ size (height) of the Top3 volume.");
  ZL_Top3Cmd->SetDefaultValue (0.001);
  ZL_Top3Cmd->SetDefaultUnit("mm");
  ZL_Top3Cmd->SetUnitCategory("Length");
  ZL_Top3Cmd->SetParameterName("ZL_Top3",omittable=false);
  ZL_Top3Cmd->SetRange("ZL_Top3>=0."); 
  ZL_Top3Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  Z_Top3Cmd = new G4UIcmdWithADoubleAndUnit("/user/Z_Top3",this);  
  Z_Top3Cmd->SetGuidance("\tZ coordinate of the Top3 volume center.");
  Z_Top3Cmd->SetDefaultValue (33);
  Z_Top3Cmd->SetDefaultUnit("mm");
  Z_Top3Cmd->SetUnitCategory("Length");
  Z_Top3Cmd->SetParameterName("Z_Top3",omittable=false);
  Z_Top3Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  X_Top3Cmd = new G4UIcmdWithADoubleAndUnit("/user/X_Top3",this);  
  X_Top3Cmd->SetGuidance("\tX coordinate of the Top3 volume center.");
  X_Top3Cmd->SetDefaultValue (0);
  X_Top3Cmd->SetDefaultUnit("mm");
  X_Top3Cmd->SetUnitCategory("Length");
  X_Top3Cmd->SetParameterName("X_Top3",omittable=false);
  X_Top3Cmd->AvailableForStates(G4State_PreInit,G4State_Idle); 

  Y_Top3Cmd = new G4UIcmdWithADoubleAndUnit("/user/Y_Top3",this);  
  Y_Top3Cmd->SetGuidance("\tY coordinate of the Top3 volume center.");
  Y_Top3Cmd->SetDefaultValue (0);
  Y_Top3Cmd->SetDefaultUnit("mm");
  Y_Top3Cmd->SetUnitCategory("Length");
  Y_Top3Cmd->SetParameterName("Y_Top3",omittable=false);
  Y_Top3Cmd->AvailableForStates(G4State_PreInit,G4State_Idle); 

  Rot_Top3Cmd = new G4UIcmdWith3VectorAndUnit("/user/Rot_Top3", this);
  Rot_Top3Cmd->SetGuidance("\tSet rotation angles for the volume Top3 (X Y Z).");
  Rot_Top3Cmd->SetUnitCategory("Angle");
  Rot_Top3Cmd->SetDefaultUnit("deg");
  Rot_Top3Cmd->SetParameterName("RotX", "RotY", "RotZ", false);
  Rot_Top3Cmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  MaterialTop3DensityCmd = new G4UIcmdWithADoubleAndUnit("/user/MaterialTop3Density",this);  
  MaterialTop3DensityCmd->SetGuidance("\tDensity of core material.");
  MaterialTop3DensityCmd->SetDefaultValue (10);
  MaterialTop3DensityCmd->SetDefaultUnit("g/cm3");
  MaterialTop3DensityCmd->SetUnitCategory("Volumic Mass");
  MaterialTop3DensityCmd->SetParameterName("MaterialTop3Density",omittable=false);
  MaterialTop3DensityCmd->SetRange("MaterialTop3Density>0."); 
  MaterialTop3DensityCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  MaterialTop3ElementNameCmd = new G4UIcmdWithAString("/user/MaterialTop3ElementName",this);  
  MaterialTop3ElementNameCmd->SetGuidance("\tName of chemical element.");
  MaterialTop3ElementNameCmd->SetDefaultValue ("Cu");
  MaterialTop3ElementNameCmd->SetCandidates("H He Li Be B C N O F Ne Na Mg Al Si P S Cl Ar K Ca Sc Ti V Cr Mn Fe Co Ni Cu Zn Ga Ge As Se Br Kr Rb Sr Y Zr Nb Mo Tc Ru Rh Pd Ag Cd In Sn Sb Te I Xe Cs Ba La Ce Pr Nd Pm Sm Eu Gd Tb Dy Ho Er Tm Yb Lu Hf Ta W Re Os Ir Pt Au Hg Tl Pb Bi Po At Rn Fr Ra Ac Th Pa U Np Pu Am Cm Bk Cf Es Fm");
  MaterialTop3ElementNameCmd->SetParameterName("MaterialTop3ElementName",omittable=false);
  MaterialTop3ElementNameCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  MaterialTop3WeightCmd = new G4UIcmdWithAString("/user/MaterialTop3Weight", this);
  MaterialTop3WeightCmd->SetGuidance("\tProvide element-weight pairs. Example: Cd 1000 W 100 O 10");
  MaterialTop3WeightCmd->SetParameterName("MaterialTop3Weight", false);
  MaterialTop3WeightCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  MaterialTop3FormulaNumCmd = new G4UIcmdWithAnInteger("/user/MaterialTop3FormulaNum",this);  
  MaterialTop3FormulaNumCmd->SetGuidance("\tNumber of atoms of chemical element in the formula.");
  MaterialTop3FormulaNumCmd->SetDefaultValue (1);
  MaterialTop3FormulaNumCmd->SetParameterName("MaterialTop3FormulaNum",omittable=false);
  MaterialTop3FormulaNumCmd->SetRange("MaterialTop3FormulaNum>=0"); 
  MaterialTop3FormulaNumCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

//=======Bot1:================
  Detector_Bot1Cmd = new G4UIcmdWithAnInteger("/user/isBot1aDetector",this);  
  Detector_Bot1Cmd->SetGuidance("\tIs Bot1 a detector?");
  Detector_Bot1Cmd->SetDefaultValue (0);
  // Detector_Bot1Cmd->SetUnitCategory("Boolean");
  Detector_Bot1Cmd->SetParameterName("isBot1aDetector",omittable=false);
  Detector_Bot1Cmd->SetRange("isBot1aDetector==0 || isBot1aDetector==1"); 
  Detector_Bot1Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  D_Bot1Cmd = new G4UIcmdWithADoubleAndUnit("/user/D_Bot1",this);  
  D_Bot1Cmd->SetGuidance("\tDiameter of the Bot1 volume.");
  D_Bot1Cmd->SetDefaultValue (0.001);
  D_Bot1Cmd->SetDefaultUnit("mm");
  D_Bot1Cmd->SetUnitCategory("Length");
  D_Bot1Cmd->SetParameterName("D_Bot1",omittable=false);
  D_Bot1Cmd->SetRange("D_Bot1>=0."); 
  D_Bot1Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  d_Bot1Cmd = new G4UIcmdWithADoubleAndUnit("/user/d_Bot1",this);  
  d_Bot1Cmd->SetGuidance("\tInner diameter of the Bot1 volume.");
  d_Bot1Cmd->SetDefaultValue (0.001);
  d_Bot1Cmd->SetDefaultUnit("mm");
  d_Bot1Cmd->SetUnitCategory("Length");
  d_Bot1Cmd->SetParameterName("d_Bot1",omittable=false);
  d_Bot1Cmd->SetRange("d_Bot1>=0."); 
  d_Bot1Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  ZL_Bot1Cmd = new G4UIcmdWithADoubleAndUnit("/user/ZL_Bot1",this);  
  ZL_Bot1Cmd->SetGuidance("\tZ size (height) of the Bot1 volume.");
  ZL_Bot1Cmd->SetDefaultValue (0.001);
  ZL_Bot1Cmd->SetDefaultUnit("mm");
  ZL_Bot1Cmd->SetUnitCategory("Length");
  ZL_Bot1Cmd->SetParameterName("ZL_Bot1",omittable=false);
  ZL_Bot1Cmd->SetRange("ZL_Bot1>=0."); 
  ZL_Bot1Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  Z_Bot1Cmd = new G4UIcmdWithADoubleAndUnit("/user/Z_Bot1",this);  
  Z_Bot1Cmd->SetGuidance("\tZ coordinate of the Bot1 volume center.");
  Z_Bot1Cmd->SetDefaultValue (-31);
  Z_Bot1Cmd->SetDefaultUnit("mm");
  Z_Bot1Cmd->SetUnitCategory("Length");
  Z_Bot1Cmd->SetParameterName("Z_Bot1",omittable=false);
  Z_Bot1Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  X_Bot1Cmd = new G4UIcmdWithADoubleAndUnit("/user/X_Bot1",this);  
  X_Bot1Cmd->SetGuidance("\tX coordinate of the Bot1 volume center.");
  X_Bot1Cmd->SetDefaultValue (0);
  X_Bot1Cmd->SetDefaultUnit("mm");
  X_Bot1Cmd->SetUnitCategory("Length");
  X_Bot1Cmd->SetParameterName("X_Bot1",omittable=false);
  X_Bot1Cmd->AvailableForStates(G4State_PreInit,G4State_Idle); 

  Y_Bot1Cmd = new G4UIcmdWithADoubleAndUnit("/user/Y_Bot1",this);  
  Y_Bot1Cmd->SetGuidance("\tY coordinate of the Bot1 volume center.");
  Y_Bot1Cmd->SetDefaultValue (0);
  Y_Bot1Cmd->SetDefaultUnit("mm");
  Y_Bot1Cmd->SetUnitCategory("Length");
  Y_Bot1Cmd->SetParameterName("Y_Bot1",omittable=false);
  Y_Bot1Cmd->AvailableForStates(G4State_PreInit,G4State_Idle); 

  Rot_Bot1Cmd = new G4UIcmdWith3VectorAndUnit("/user/Rot_Bot1", this);
  Rot_Bot1Cmd->SetGuidance("\tSet rotation angles for the volume Bot1 (X Y Z).");
  Rot_Bot1Cmd->SetUnitCategory("Angle");
  Rot_Bot1Cmd->SetDefaultUnit("deg");
  Rot_Bot1Cmd->SetParameterName("RotX", "RotY", "RotZ", false);
  Rot_Bot1Cmd->AvailableForStates(G4State_PreInit, G4State_Idle);  

  MaterialBot1DensityCmd = new G4UIcmdWithADoubleAndUnit("/user/MaterialBot1Density",this);  
  MaterialBot1DensityCmd->SetGuidance("\tDensity of core material.");
  MaterialBot1DensityCmd->SetDefaultValue (10);
  MaterialBot1DensityCmd->SetDefaultUnit("g/cm3");
  MaterialBot1DensityCmd->SetUnitCategory("Volumic Mass");
  MaterialBot1DensityCmd->SetParameterName("MaterialBot1Density",omittable=false);
  MaterialBot1DensityCmd->SetRange("MaterialBot1Density>0."); 
  MaterialBot1DensityCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  MaterialBot1ElementNameCmd = new G4UIcmdWithAString("/user/MaterialBot1ElementName",this);  
  MaterialBot1ElementNameCmd->SetGuidance("\tName of chemical element.");
  MaterialBot1ElementNameCmd->SetDefaultValue ("Cu");
  MaterialBot1ElementNameCmd->SetCandidates("H He Li Be B C N O F Ne Na Mg Al Si P S Cl Ar K Ca Sc Ti V Cr Mn Fe Co Ni Cu Zn Ga Ge As Se Br Kr Rb Sr Y Zr Nb Mo Tc Ru Rh Pd Ag Cd In Sn Sb Te I Xe Cs Ba La Ce Pr Nd Pm Sm Eu Gd Tb Dy Ho Er Tm Yb Lu Hf Ta W Re Os Ir Pt Au Hg Tl Pb Bi Po At Rn Fr Ra Ac Th Pa U Np Pu Am Cm Bk Cf Es Fm");
  MaterialBot1ElementNameCmd->SetParameterName("MaterialBot1ElementName",omittable=false);
  MaterialBot1ElementNameCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  MaterialBot1WeightCmd = new G4UIcmdWithAString("/user/MaterialBot1Weight", this);
  MaterialBot1WeightCmd->SetGuidance("\tProvide element-weight pairs. Example: Cd 1000 W 100 O 10");
  MaterialBot1WeightCmd->SetParameterName("MaterialBot1Weight", false);
  MaterialBot1WeightCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  MaterialBot1FormulaNumCmd = new G4UIcmdWithAnInteger("/user/MaterialBot1FormulaNum",this);  
  MaterialBot1FormulaNumCmd->SetGuidance("\tNumber of atoms of chemical element in the formula.");
  MaterialBot1FormulaNumCmd->SetDefaultValue (1);
  MaterialBot1FormulaNumCmd->SetParameterName("MaterialBot1FormulaNum",omittable=false);
  MaterialBot1FormulaNumCmd->SetRange("MaterialBot1FormulaNum>=0"); 
  MaterialBot1FormulaNumCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

//=======Bot2:================
  Detector_Bot2Cmd = new G4UIcmdWithAnInteger("/user/isBot2aDetector",this);  
  Detector_Bot2Cmd->SetGuidance("\tIs Bot2 a detector?");
  Detector_Bot2Cmd->SetDefaultValue (0);
  // Detector_Bot2Cmd->SetUnitCategory("Boolean");
  Detector_Bot2Cmd->SetParameterName("isBot2aDetector",omittable=false);
  Detector_Bot2Cmd->SetRange("isBot2aDetector==0 || isBot2aDetector==1"); 
  Detector_Bot2Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  D_Bot2Cmd = new G4UIcmdWithADoubleAndUnit("/user/D_Bot2",this);  
  D_Bot2Cmd->SetGuidance("\tDiameter of the Bot2 volume.");
  D_Bot2Cmd->SetDefaultValue (0.001);
  D_Bot2Cmd->SetDefaultUnit("mm");
  D_Bot2Cmd->SetUnitCategory("Length");
  D_Bot2Cmd->SetParameterName("D_Bot2",omittable=false);
  D_Bot2Cmd->SetRange("D_Bot2>=0."); 
  D_Bot2Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  d_Bot2Cmd = new G4UIcmdWithADoubleAndUnit("/user/d_Bot2",this);  
  d_Bot2Cmd->SetGuidance("\tInner diameter of the Bot2 volume.");
  d_Bot2Cmd->SetDefaultValue (0.001);
  d_Bot2Cmd->SetDefaultUnit("mm");
  d_Bot2Cmd->SetUnitCategory("Length");
  d_Bot2Cmd->SetParameterName("d_Bot2",omittable=false);
  d_Bot2Cmd->SetRange("d_Bot2>=0."); 
  d_Bot2Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);    

  ZL_Bot2Cmd = new G4UIcmdWithADoubleAndUnit("/user/ZL_Bot2",this);  
  ZL_Bot2Cmd->SetGuidance("\tZ size (height) of the Bot2 volume.");
  ZL_Bot2Cmd->SetDefaultValue (0.001);
  ZL_Bot2Cmd->SetDefaultUnit("mm");
  ZL_Bot2Cmd->SetUnitCategory("Length");
  ZL_Bot2Cmd->SetParameterName("ZL_Bot2",omittable=false);
  ZL_Bot2Cmd->SetRange("ZL_Bot2>=0."); 
  ZL_Bot2Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  Z_Bot2Cmd = new G4UIcmdWithADoubleAndUnit("/user/Z_Bot2",this);  
  Z_Bot2Cmd->SetGuidance("\tZ coordinate of the Bot2 volume center.");
  Z_Bot2Cmd->SetDefaultValue (-32);
  Z_Bot2Cmd->SetDefaultUnit("mm");
  Z_Bot2Cmd->SetUnitCategory("Length");
  Z_Bot2Cmd->SetParameterName("Z_Bot2",omittable=false);
  Z_Bot2Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  X_Bot2Cmd = new G4UIcmdWithADoubleAndUnit("/user/X_Bot2",this);  
  X_Bot2Cmd->SetGuidance("\tX coordinate of the Bot2 volume center.");
  X_Bot2Cmd->SetDefaultValue (0);
  X_Bot2Cmd->SetDefaultUnit("mm");
  X_Bot2Cmd->SetUnitCategory("Length");
  X_Bot2Cmd->SetParameterName("X_Bot2",omittable=false);
  X_Bot2Cmd->AvailableForStates(G4State_PreInit,G4State_Idle); 

  Y_Bot2Cmd = new G4UIcmdWithADoubleAndUnit("/user/Y_Bot2",this);  
  Y_Bot2Cmd->SetGuidance("\tY coordinate of the Bot2 volume center.");
  Y_Bot2Cmd->SetDefaultValue (0);
  Y_Bot2Cmd->SetDefaultUnit("mm");
  Y_Bot2Cmd->SetUnitCategory("Length");
  Y_Bot2Cmd->SetParameterName("Y_Bot2",omittable=false);
  Y_Bot2Cmd->AvailableForStates(G4State_PreInit,G4State_Idle); 

  Rot_Bot2Cmd = new G4UIcmdWith3VectorAndUnit("/user/Rot_Bot2", this);
  Rot_Bot2Cmd->SetGuidance("\tSet rotation angles for the volume Bot2 (X Y Z).");
  Rot_Bot2Cmd->SetUnitCategory("Angle");
  Rot_Bot2Cmd->SetDefaultUnit("deg");
  Rot_Bot2Cmd->SetParameterName("RotX", "RotY", "RotZ", false);
  Rot_Bot2Cmd->AvailableForStates(G4State_PreInit, G4State_Idle); 

  MaterialBot2DensityCmd = new G4UIcmdWithADoubleAndUnit("/user/MaterialBot2Density",this);  
  MaterialBot2DensityCmd->SetGuidance("\tDensity of core material.");
  MaterialBot2DensityCmd->SetDefaultValue (10);
  MaterialBot2DensityCmd->SetDefaultUnit("g/cm3");
  MaterialBot2DensityCmd->SetUnitCategory("Volumic Mass");
  MaterialBot2DensityCmd->SetParameterName("MaterialBot2Density",omittable=false);
  MaterialBot2DensityCmd->SetRange("MaterialBot2Density>0."); 
  MaterialBot2DensityCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  MaterialBot2ElementNameCmd = new G4UIcmdWithAString("/user/MaterialBot2ElementName",this);  
  MaterialBot2ElementNameCmd->SetGuidance("\tName of chemical element.");
  MaterialBot2ElementNameCmd->SetDefaultValue ("Cu");
  MaterialBot2ElementNameCmd->SetCandidates("H He Li Be B C N O F Ne Na Mg Al Si P S Cl Ar K Ca Sc Ti V Cr Mn Fe Co Ni Cu Zn Ga Ge As Se Br Kr Rb Sr Y Zr Nb Mo Tc Ru Rh Pd Ag Cd In Sn Sb Te I Xe Cs Ba La Ce Pr Nd Pm Sm Eu Gd Tb Dy Ho Er Tm Yb Lu Hf Ta W Re Os Ir Pt Au Hg Tl Pb Bi Po At Rn Fr Ra Ac Th Pa U Np Pu Am Cm Bk Cf Es Fm");
  MaterialBot2ElementNameCmd->SetParameterName("MaterialBot2ElementName",omittable=false);
  MaterialBot2ElementNameCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  MaterialBot2WeightCmd = new G4UIcmdWithAString("/user/MaterialBot2Weight", this);
  MaterialBot2WeightCmd->SetGuidance("\tProvide element-weight pairs. Example: Cd 1000 W 100 O 10");
  MaterialBot2WeightCmd->SetParameterName("MaterialBot2Weight", false);
  MaterialBot2WeightCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  MaterialBot2FormulaNumCmd = new G4UIcmdWithAnInteger("/user/MaterialBot2FormulaNum",this);  
  MaterialBot2FormulaNumCmd->SetGuidance("\tNumber of atoms of chemical element in the formula.");
  MaterialBot2FormulaNumCmd->SetDefaultValue (1);
  MaterialBot2FormulaNumCmd->SetParameterName("MaterialBot2FormulaNum",omittable=false);
  MaterialBot2FormulaNumCmd->SetRange("MaterialBot2FormulaNum>=0"); 
  MaterialBot2FormulaNumCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

//=======Bot3:================
  Detector_Bot3Cmd = new G4UIcmdWithAnInteger("/user/isBot3aDetector",this);  
  Detector_Bot3Cmd->SetGuidance("\tIs Bot3 a detector?");
  Detector_Bot3Cmd->SetDefaultValue (0);
  // Detector_Bot3Cmd->SetUnitCategory("Boolean");
  Detector_Bot3Cmd->SetParameterName("isBot3aDetector",omittable=false);
  Detector_Bot3Cmd->SetRange("isBot3aDetector==0 || isBot3aDetector==1"); 
  Detector_Bot3Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  D_Bot3Cmd = new G4UIcmdWithADoubleAndUnit("/user/D_Bot3",this);  
  D_Bot3Cmd->SetGuidance("\tDiameter of the Bot3 volume.");
  D_Bot3Cmd->SetDefaultValue (0.001);
  D_Bot3Cmd->SetDefaultUnit("mm");
  D_Bot3Cmd->SetUnitCategory("Length");
  D_Bot3Cmd->SetParameterName("D_Bot3",omittable=false);
  D_Bot3Cmd->SetRange("D_Bot3>=0."); 
  D_Bot3Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  d_Bot3Cmd = new G4UIcmdWithADoubleAndUnit("/user/d_Bot3",this);  
  d_Bot3Cmd->SetGuidance("\tInner diameter of the Bot3 volume.");
  d_Bot3Cmd->SetDefaultValue (0.001);
  d_Bot3Cmd->SetDefaultUnit("mm");
  d_Bot3Cmd->SetUnitCategory("Length");
  d_Bot3Cmd->SetParameterName("d_Bot3",omittable=false);
  d_Bot3Cmd->SetRange("d_Bot3>=0."); 
  d_Bot3Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  ZL_Bot3Cmd = new G4UIcmdWithADoubleAndUnit("/user/ZL_Bot3",this);  
  ZL_Bot3Cmd->SetGuidance("\tZ size (height) of the Bot3 volume.");
  ZL_Bot3Cmd->SetDefaultValue (0.001);
  ZL_Bot3Cmd->SetDefaultUnit("mm");
  ZL_Bot3Cmd->SetUnitCategory("Length");
  ZL_Bot3Cmd->SetParameterName("ZL_Bot3",omittable=false);
  ZL_Bot3Cmd->SetRange("ZL_Bot3>=0."); 
  ZL_Bot3Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  Z_Bot3Cmd = new G4UIcmdWithADoubleAndUnit("/user/Z_Bot3",this);  
  Z_Bot3Cmd->SetGuidance("\tZ coordinate of the Bot3 volume center.");
  Z_Bot3Cmd->SetDefaultValue (-33);
  Z_Bot3Cmd->SetDefaultUnit("mm");
  Z_Bot3Cmd->SetUnitCategory("Length");
  Z_Bot3Cmd->SetParameterName("Z_Bot3",omittable=false);
  Z_Bot3Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  X_Bot3Cmd = new G4UIcmdWithADoubleAndUnit("/user/X_Bot3",this);  
  X_Bot3Cmd->SetGuidance("\tX coordinate of the Bot3 volume center.");
  X_Bot3Cmd->SetDefaultValue (0);
  X_Bot3Cmd->SetDefaultUnit("mm");
  X_Bot3Cmd->SetUnitCategory("Length");
  X_Bot3Cmd->SetParameterName("X_Bot3",omittable=false);
  X_Bot3Cmd->AvailableForStates(G4State_PreInit,G4State_Idle); 

  Y_Bot3Cmd = new G4UIcmdWithADoubleAndUnit("/user/Y_Bot3",this);  
  Y_Bot3Cmd->SetGuidance("\tY coordinate of the Bot3 volume center.");
  Y_Bot3Cmd->SetDefaultValue (0);
  Y_Bot3Cmd->SetDefaultUnit("mm");
  Y_Bot3Cmd->SetUnitCategory("Length");
  Y_Bot3Cmd->SetParameterName("Y_Bot3",omittable=false);
  Y_Bot3Cmd->AvailableForStates(G4State_PreInit,G4State_Idle); 

  Rot_Bot3Cmd = new G4UIcmdWith3VectorAndUnit("/user/Rot_Bot3", this);
  Rot_Bot3Cmd->SetGuidance("\tSet rotation angles for the volume Bot3 (X Y Z).");
  Rot_Bot3Cmd->SetUnitCategory("Angle");
  Rot_Bot3Cmd->SetDefaultUnit("deg");
  Rot_Bot3Cmd->SetParameterName("RotX", "RotY", "RotZ", false);
  Rot_Bot3Cmd->AvailableForStates(G4State_PreInit, G4State_Idle);  

  MaterialBot3DensityCmd = new G4UIcmdWithADoubleAndUnit("/user/MaterialBot3Density",this);  
  MaterialBot3DensityCmd->SetGuidance("\tDensity of core material.");
  MaterialBot3DensityCmd->SetDefaultValue (10);
  MaterialBot3DensityCmd->SetDefaultUnit("g/cm3");
  MaterialBot3DensityCmd->SetUnitCategory("Volumic Mass");
  MaterialBot3DensityCmd->SetParameterName("MaterialBot3Density",omittable=false);
  MaterialBot3DensityCmd->SetRange("MaterialBot3Density>0."); 
  MaterialBot3DensityCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  MaterialBot3ElementNameCmd = new G4UIcmdWithAString("/user/MaterialBot3ElementName",this);  
  MaterialBot3ElementNameCmd->SetGuidance("\tName of chemical element.");
  MaterialBot3ElementNameCmd->SetDefaultValue ("Cu");
  MaterialBot3ElementNameCmd->SetCandidates("H He Li Be B C N O F Ne Na Mg Al Si P S Cl Ar K Ca Sc Ti V Cr Mn Fe Co Ni Cu Zn Ga Ge As Se Br Kr Rb Sr Y Zr Nb Mo Tc Ru Rh Pd Ag Cd In Sn Sb Te I Xe Cs Ba La Ce Pr Nd Pm Sm Eu Gd Tb Dy Ho Er Tm Yb Lu Hf Ta W Re Os Ir Pt Au Hg Tl Pb Bi Po At Rn Fr Ra Ac Th Pa U Np Pu Am Cm Bk Cf Es Fm");
  MaterialBot3ElementNameCmd->SetParameterName("MaterialBot3ElementName",omittable=false);
  MaterialBot3ElementNameCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  MaterialBot3WeightCmd = new G4UIcmdWithAString("/user/MaterialBot3Weight", this);
  MaterialBot3WeightCmd->SetGuidance("\tProvide element-weight pairs. Example: Cd 1000 W 100 O 10");
  MaterialBot3WeightCmd->SetParameterName("MaterialBot3Weight", false);
  MaterialBot3WeightCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  MaterialBot3FormulaNumCmd = new G4UIcmdWithAnInteger("/user/MaterialBot3FormulaNum",this);  
  MaterialBot3FormulaNumCmd->SetGuidance("\tNumber of atoms of chemical element in the formula.");
  MaterialBot3FormulaNumCmd->SetDefaultValue (1);
  MaterialBot3FormulaNumCmd->SetParameterName("MaterialBot3FormulaNum",omittable=false);
  MaterialBot3FormulaNumCmd->SetRange("MaterialBot3FormulaNum>=0"); 
  MaterialBot3FormulaNumCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

//=======Source:================
  Detector_SrcCmd = new G4UIcmdWithAnInteger("/user/isSrcaDetector",this);  
  Detector_SrcCmd->SetGuidance("\tIs Src a detector?");
  Detector_SrcCmd->SetDefaultValue (0);
  // Detector_SrcCmd->SetUnitCategory("Boolean");
  Detector_SrcCmd->SetParameterName("isSrcaDetector",omittable=false);
  Detector_SrcCmd->SetRange("isSrcaDetector==0 || isSrcaDetector==1"); 
  Detector_SrcCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  D_SrcCmd = new G4UIcmdWithADoubleAndUnit("/user/D_Src",this);  
  D_SrcCmd->SetGuidance("\tDiameter of the Src volume (if it is a cylinder).");
  D_SrcCmd->SetDefaultValue (0.001);
  D_SrcCmd->SetDefaultUnit("mm");
  D_SrcCmd->SetUnitCategory("Length");
  D_SrcCmd->SetParameterName("D_Src",omittable=false);
  D_SrcCmd->SetRange("D_Src>=0."); 
  D_SrcCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  XL_SrcCmd = new G4UIcmdWithADoubleAndUnit("/user/XL_Src",this);  
  XL_SrcCmd->SetGuidance("\tX size of the Src volume (if it is a prism).");
  XL_SrcCmd->SetDefaultValue (0.001);
  XL_SrcCmd->SetDefaultUnit("mm");
  XL_SrcCmd->SetUnitCategory("Length");
  XL_SrcCmd->SetParameterName("XL_Src",omittable=false);
  XL_SrcCmd->SetRange("XL_Src>=0."); 
  XL_SrcCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  YL_SrcCmd = new G4UIcmdWithADoubleAndUnit("/user/YL_Src",this);  
  YL_SrcCmd->SetGuidance("\tY size of the Src volume (if it is a prism).");
  YL_SrcCmd->SetDefaultValue (0.001);
  YL_SrcCmd->SetDefaultUnit("mm");
  YL_SrcCmd->SetUnitCategory("Length");
  YL_SrcCmd->SetParameterName("YL_Src",omittable=false);
  YL_SrcCmd->SetRange("YL_Src>=0."); 
  YL_SrcCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  ZL_SrcCmd = new G4UIcmdWithADoubleAndUnit("/user/ZL_Src",this);  
  ZL_SrcCmd->SetGuidance("\tZ size (height) of the Src volume.");
  ZL_SrcCmd->SetDefaultValue (0.001);
  ZL_SrcCmd->SetDefaultUnit("mm");
  ZL_SrcCmd->SetUnitCategory("Length");
  ZL_SrcCmd->SetParameterName("ZL_Src",omittable=false);
  ZL_SrcCmd->SetRange("ZL_Src>=0."); 
  ZL_SrcCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  X_SrcCmd = new G4UIcmdWithADoubleAndUnit("/user/X_Src",this);  
  X_SrcCmd->SetGuidance("\tZ coordinate of the Src volume center.");
  X_SrcCmd->SetDefaultValue (35);
  X_SrcCmd->SetDefaultUnit("mm");
  X_SrcCmd->SetUnitCategory("Length");
  X_SrcCmd->SetParameterName("X_Src",omittable=false);
  X_SrcCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  Y_SrcCmd = new G4UIcmdWithADoubleAndUnit("/user/Y_Src",this);  
  Y_SrcCmd->SetGuidance("\tZ coordinate of the Src volume center.");
  Y_SrcCmd->SetDefaultValue (0);
  Y_SrcCmd->SetDefaultUnit("mm");
  Y_SrcCmd->SetUnitCategory("Length");
  Y_SrcCmd->SetParameterName("Y_Src",omittable=false);
  Y_SrcCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  Z_SrcCmd = new G4UIcmdWithADoubleAndUnit("/user/Z_Src",this);  
  Z_SrcCmd->SetGuidance("\tZ coordinate of the Src volume center.");
  Z_SrcCmd->SetDefaultValue (0);
  Z_SrcCmd->SetDefaultUnit("mm");
  Z_SrcCmd->SetUnitCategory("Length");
  Z_SrcCmd->SetParameterName("Z_Src",omittable=false);
  Z_SrcCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  Rot_SrcCmd = new G4UIcmdWith3VectorAndUnit("/user/Rot_Src", this);
  Rot_SrcCmd->SetGuidance("\tSet rotation angles for the volume Src (X Y Z).");
  Rot_SrcCmd->SetUnitCategory("Angle");
  Rot_SrcCmd->SetDefaultUnit("deg");
  Rot_SrcCmd->SetParameterName("RotX", "RotY", "RotZ", false);
  Rot_SrcCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  VolumeSrcCmd = new G4UIcmdWithAString("/user/VolumeSrc",this);
  VolumeSrcCmd->SetGuidance("\tSrc is set equal to volume: SHLD, Cover2 (aka Marinelli), Cover1 (aka Core), Det, Cavity, Top1-Top3, Bot1-Bot3.");
  VolumeSrcCmd->SetDefaultValue ("Det");
  VolumeSrcCmd->SetCandidates(
    "SHLD Cover2 Marinelli Cover1 Core Det Cavity Top1 Top2 Top3 Bot1 Bot2 Bot3 ");
  VolumeSrcCmd->SetParameterName("VolumeSrc",omittable=false);
  VolumeSrcCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

//=======UnSource:================
  Detector_UnSrcCmd = new G4UIcmdWithAnInteger("/user/isUnSrcaDetector",this);  
  Detector_UnSrcCmd->SetGuidance("\tIs UnSrc a detector?");
  Detector_UnSrcCmd->SetDefaultValue (0);
  // Detector_UnSrcCmd->SetUnitCategory("Boolean");
  Detector_UnSrcCmd->SetParameterName("isUnSrcaDetector",omittable=false);
  Detector_UnSrcCmd->SetRange("isUnSrcaDetector==0 || isUnSrcaDetector==1"); 
  Detector_UnSrcCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  D_UnSrcCmd = new G4UIcmdWithADoubleAndUnit("/user/D_UnSrc",this);  
  D_UnSrcCmd->SetGuidance("\tDiameter of the UnSrc volume (if it is a cylinder).");
  D_UnSrcCmd->SetDefaultValue (0.001);
  D_UnSrcCmd->SetDefaultUnit("mm");
  D_UnSrcCmd->SetUnitCategory("Length");
  D_UnSrcCmd->SetParameterName("D_UnSrc",omittable=false);
  D_UnSrcCmd->SetRange("D_UnSrc>=0."); 
  D_UnSrcCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  XL_UnSrcCmd = new G4UIcmdWithADoubleAndUnit("/user/XL_UnSrc",this);  
  XL_UnSrcCmd->SetGuidance("\tX size of the UnSrc volume (if it is a prism).");
  XL_UnSrcCmd->SetDefaultValue (0.001);
  XL_UnSrcCmd->SetDefaultUnit("mm");
  XL_UnSrcCmd->SetUnitCategory("Length");
  XL_UnSrcCmd->SetParameterName("XL_UnSrc",omittable=false);
  XL_UnSrcCmd->SetRange("XL_UnSrc>=0."); 
  XL_UnSrcCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  YL_UnSrcCmd = new G4UIcmdWithADoubleAndUnit("/user/YL_UnSrc",this);  
  YL_UnSrcCmd->SetGuidance("\tY size of the UnSrc volume (if it is a prism).");
  YL_UnSrcCmd->SetDefaultValue (0.001);
  YL_UnSrcCmd->SetDefaultUnit("mm");
  YL_UnSrcCmd->SetUnitCategory("Length");
  YL_UnSrcCmd->SetParameterName("YL_UnSrc",omittable=false);
  YL_UnSrcCmd->SetRange("YL_UnSrc>=0."); 
  YL_UnSrcCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  ZL_UnSrcCmd = new G4UIcmdWithADoubleAndUnit("/user/ZL_UnSrc",this);  
  ZL_UnSrcCmd->SetGuidance("\tZ size (height) of the UnSrc volume.");
  ZL_UnSrcCmd->SetDefaultValue (0.001);
  ZL_UnSrcCmd->SetDefaultUnit("mm");
  ZL_UnSrcCmd->SetUnitCategory("Length");
  ZL_UnSrcCmd->SetParameterName("ZL_UnSrc",omittable=false);
  ZL_UnSrcCmd->SetRange("ZL_UnSrc>=0."); 
  ZL_UnSrcCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  X_UnSrcCmd = new G4UIcmdWithADoubleAndUnit("/user/X_UnSrc",this);  
  X_UnSrcCmd->SetGuidance("\tZ coordinate of the UnSrc volume center.");
  X_UnSrcCmd->SetDefaultValue (35);
  X_UnSrcCmd->SetDefaultUnit("mm");
  X_UnSrcCmd->SetUnitCategory("Length");
  X_UnSrcCmd->SetParameterName("X_UnSrc",omittable=false);
  X_UnSrcCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  Y_UnSrcCmd = new G4UIcmdWithADoubleAndUnit("/user/Y_UnSrc",this);  
  Y_UnSrcCmd->SetGuidance("\tZ coordinate of the UnSrc volume center.");
  Y_UnSrcCmd->SetDefaultValue (0);
  Y_UnSrcCmd->SetDefaultUnit("mm");
  Y_UnSrcCmd->SetUnitCategory("Length");
  Y_UnSrcCmd->SetParameterName("Y_UnSrc",omittable=false);
  Y_UnSrcCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  Z_UnSrcCmd = new G4UIcmdWithADoubleAndUnit("/user/Z_UnSrc",this);  
  Z_UnSrcCmd->SetGuidance("\tZ coordinate of the UnSrc volume center.");
  Z_UnSrcCmd->SetDefaultValue (0);
  Z_UnSrcCmd->SetDefaultUnit("mm");
  Z_UnSrcCmd->SetUnitCategory("Length");
  Z_UnSrcCmd->SetParameterName("Z_UnSrc",omittable=false);
  Z_UnSrcCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  Rot_UnSrcCmd = new G4UIcmdWith3VectorAndUnit("/user/Rot_UnSrc", this);
  Rot_UnSrcCmd->SetGuidance("\tSet rotation angles for the volume UnSrc (X Y Z).");
  Rot_UnSrcCmd->SetUnitCategory("Angle");
  Rot_UnSrcCmd->SetDefaultUnit("deg");
  Rot_UnSrcCmd->SetParameterName("RotX", "RotY", "RotZ", false);
  Rot_UnSrcCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

	VolumeUnSrcCmd = new G4UIcmdWithAString("/user/VolumeUnSrc",this);
  VolumeUnSrcCmd->SetGuidance("\tUnSrc is set equal to volume: Cover2 (aka Marinelli), Cover1 (aka Core), Det, Cavity, Top1-Top3, Bot1-Bot3.");
  VolumeUnSrcCmd->SetDefaultValue ("Cavity");
  VolumeUnSrcCmd->SetCandidates(
    "Cover2 Marinelli Cover1 Core Det Cavity Top1 Top2 Top3 Bot1 Bot2 Bot3 ");
  VolumeUnSrcCmd->SetParameterName("VolumeUnSrc",omittable=false);
  VolumeUnSrcCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

//======================================
  //=======Shield:============
  SaveToCmd = new G4UIcmdWithAnInteger("/user/saveTo",this);  
  SaveToCmd->SetGuidance("\tSave to ROOT (0) or CSV (1)?");
  SaveToCmd->SetDefaultValue (0);
  // Detector_SHLDCmd->SetUnitCategory("Boolean");
  SaveToCmd->SetParameterName("saveTo",omittable=false);
  SaveToCmd->SetRange("saveTo==0 || saveTo==1"); 
  SaveToCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  //=======Shield:============
  wrlFilesQuantityCmd = new G4UIcmdWithAnInteger("/user/wrlFilesQuantity",this);  
  wrlFilesQuantityCmd->SetGuidance("\tHow many wrl files to save?");
  wrlFilesQuantityCmd->SetDefaultValue (10);
  wrlFilesQuantityCmd->SetParameterName("wrlFilesQuantity",omittable=false);
  wrlFilesQuantityCmd->SetRange("wrlFilesQuantity>=0"); 
  wrlFilesQuantityCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  EGammaCmd = new G4UIcmdWithADoubleAndUnit("/user/EGamma",this);  
  EGammaCmd->SetGuidance("\t\tLower cut for particle energy");
  EGammaCmd->SetDefaultValue (1000);
  EGammaCmd->SetDefaultUnit("keV");
  EGammaCmd->SetUnitCategory("Energy");
  EGammaCmd->SetParameterName("EGamma",omittable=true);
  EGammaCmd->SetRange("EGamma>0."); 
  EGammaCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  FWHM1Cmd = new G4UIcmdWithADouble("/user/FWHM1",this);  
  FWHM1Cmd->SetGuidance("\tFWHM1 coefficient of the detector:");
  FWHM1Cmd->SetGuidance("\tFWHM[keV]=sqrt(FWHM1[keV^2] + FWHM2[keV]*Egamma[keV])");
  FWHM1Cmd->SetDefaultValue (1);
  FWHM1Cmd->SetParameterName("FWHM1",omittable=false);
  FWHM1Cmd->AvailableForStates(G4State_PreInit,G4State_Idle); 

  FWHM2Cmd = new G4UIcmdWithADouble("/user/FWHM2",this);  
  FWHM2Cmd->SetGuidance("\tFWHM2 coefficient of the detector:");
  FWHM2Cmd->SetGuidance("\tFWHM[keV]=sqrt(FWHM1[keV^2] + FWHM2[keV]*Egamma[keV])");
  FWHM2Cmd->SetParameterName("FWHM2",omittable=false);
  FWHM2Cmd->SetDefaultValue (0);
  FWHM2Cmd->SetRange("FWHM2>=0."); 
  FWHM2Cmd->AvailableForStates(G4State_PreInit,G4State_Idle); 

	AlphaBetaCmd = new G4UIcmdWithADouble("/user/AlphaBeta",this);  
  AlphaBetaCmd->SetGuidance("\tAlphaBeta coefficient of the detector (typically < 1):");
  AlphaBetaCmd->SetGuidance("\tEobserved = Ereleased * AlphaBeta");
  AlphaBetaCmd->SetParameterName("AlphaBeta",omittable=false);
  AlphaBetaCmd->SetDefaultValue (1.);
  AlphaBetaCmd->SetRange("AlphaBeta>=0."); 
  AlphaBetaCmd->AvailableForStates(G4State_PreInit,G4State_Idle); 

  ThresholdCmd = new G4UIcmdWithADoubleAndUnit("/user/Threshold",this);  
  ThresholdCmd->SetGuidance("\tEnergy threshold of the detector");
  ThresholdCmd->SetDefaultValue (0);
  ThresholdCmd->SetDefaultUnit("keV");
  ThresholdCmd->SetUnitCategory("Energy");
  ThresholdCmd->SetParameterName("Threshold",omittable=false);
  ThresholdCmd->SetRange("Threshold>=0."); 
  ThresholdCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  tMinCmd = new G4UIcmdWithADoubleAndUnit("/user/tMin",this);  
  tMinCmd->SetGuidance("\tMinimal time of a particle emission since the start of event");
  tMinCmd->SetDefaultValue (0);
  tMinCmd->SetDefaultUnit("s");
  tMinCmd->SetUnitCategory("Time");
  tMinCmd->SetParameterName("tMin",omittable=false);
  tMinCmd->SetRange("tMin>=0."); 
	tMinCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

	tMaxCmd = new G4UIcmdWithADoubleAndUnit("/user/tMax",this);  
  tMaxCmd->SetGuidance("\tMaximal time of a particle emission since the start of event");
  tMaxCmd->SetDefaultValue (1.e50);
  tMaxCmd->SetDefaultUnit("s");
  tMaxCmd->SetUnitCategory("Time");
  tMaxCmd->SetParameterName("tMax",omittable=false);
  tMaxCmd->SetRange("tMax>=0."); 
  tMaxCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  ELowLimitCmd = new G4UIcmdWithADoubleAndUnit("/user/ELowLimit",this);  
  ELowLimitCmd->SetGuidance("\t\tLower cut for particle energy");
  ELowLimitCmd->SetDefaultValue (0.1);
  ELowLimitCmd->SetDefaultUnit("keV");
  ELowLimitCmd->SetUnitCategory("Energy");
  ELowLimitCmd->SetParameterName("ELowLimit",omittable=false);
  ELowLimitCmd->SetRange("ELowLimit>0."); 
  ELowLimitCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  DELowLimitCmd = new G4UIcmdWithADoubleAndUnit("/user/DELowLimit",this);  
  DELowLimitCmd->SetGuidance("\tLower cut for e+/e- distance step");
  DELowLimitCmd->SetDefaultValue (1000.0);
  DELowLimitCmd->SetDefaultUnit("nm");
  DELowLimitCmd->SetUnitCategory("Length");
  DELowLimitCmd->SetParameterName("DELowLimit",omittable=false);
  DELowLimitCmd->SetRange("DELowLimit>0."); 
  DELowLimitCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  DGLowLimitCmd = new G4UIcmdWithADoubleAndUnit("/user/DGLowLimit",this);  
  DGLowLimitCmd->SetGuidance("\tLower cut for gamma distance step");
  DGLowLimitCmd->SetDefaultValue (1000.0);
  DGLowLimitCmd->SetDefaultUnit("nm");
  DGLowLimitCmd->SetUnitCategory("Length");
  DGLowLimitCmd->SetParameterName("DGLowLimit",omittable=false);
  DGLowLimitCmd->SetRange("DGLowLimit>0."); 
  DGLowLimitCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  ChannelWidthCmd = new G4UIcmdWithADoubleAndUnit("/user/ChannelWidth",this);  
  ChannelWidthCmd->SetGuidance("\tWidth of one channel in the spectrum");
  ChannelWidthCmd->SetDefaultValue (1.0);
  ChannelWidthCmd->SetDefaultUnit("keV");
  ChannelWidthCmd->SetUnitCategory("Energy");
  ChannelWidthCmd->SetParameterName("ChannelWidth",omittable=false);
  ChannelWidthCmd->SetRange("ChannelWidth>0."); 
  ChannelWidthCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  numberOfRunsCmd = new G4UIcmdWithAnInteger("/user/numberOfRuns",this);  
  numberOfRunsCmd->SetGuidance("\tNumber of runs (1 run is 1 decay vertex generated).");         
  numberOfRunsCmd->SetDefaultValue (1000);
  numberOfRunsCmd->SetParameterName("numberOfRuns",omittable=false);
  numberOfRunsCmd->SetRange("numberOfRuns>0"); 
  numberOfRunsCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  StepCmd = new G4UIcmdWithAnInteger("/user/Step",this);  
  StepCmd->SetGuidance("\tStep of the screen output (every Nth run).");         
  StepCmd->SetDefaultValue (1000);
  StepCmd->SetParameterName("Step",omittable=false);
  StepCmd->SetRange("Step>0"); 
  StepCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  RandomSeedCmd = new G4UIcmdWithAnInteger("/user/RandomSeed",this);  
  RandomSeedCmd->SetGuidance("\tSeed of random numbers generator.");
  RandomSeedCmd->SetDefaultValue (90115037);
  RandomSeedCmd->SetParameterName("RandomSeed",omittable=false);
  RandomSeedCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  
 
  WaitCommandCmd = new G4UIcmdWithAnInteger("/user/WaitCommand",this);  
  WaitCommandCmd->SetGuidance("\tWait for a command (1) or no (0)");         
  WaitCommandCmd->SetDefaultValue (0);
  WaitCommandCmd->SetParameterName("WaitCommand",omittable=false);
  WaitCommandCmd->SetRange("WaitCommand==0 || WaitCommand==1"); 
  WaitCommandCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  VerboseVisCmd = new G4UIcmdWithAnInteger("/user/VerboseVis",this);  
  VerboseVisCmd->SetGuidance("\tVerbose level of vizualisation (0-6)");         
  VerboseVisCmd->SetDefaultValue (0);
  VerboseVisCmd->SetParameterName("VerboseVis",omittable=false);
  VerboseVisCmd->SetRange("VerboseVis>=0 && VerboseVis<=6"); 
  VerboseVisCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  VerboseAllCmd = new G4UIcmdWithAnInteger("/user/VerboseAll",this);  
  VerboseAllCmd->SetGuidance("\tVerbose level of other (0-6)");         
  VerboseAllCmd->SetDefaultValue (0);
  VerboseAllCmd->SetParameterName("VerboseAll",omittable=false);
  VerboseAllCmd->SetRange("VerboseAll>=0 && VerboseAll<=6"); 
  VerboseAllCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  DoPictureCmd = new G4UIcmdWithAnInteger("/user/DoPicture",this);  
  DoPictureCmd->SetGuidance("\t\tTo make vrml files (1) or non (0) or open OpenGL (2)");         
  DoPictureCmd->SetDefaultValue (0);
  DoPictureCmd->SetParameterName("DoPicture",omittable=false);
  DoPictureCmd->SetRange("DoPicture==0 || DoPicture==1 || DoPicture==2"); 
  DoPictureCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  AllowIsotropicRotationCmd = new G4UIcmdWithAnInteger("/user/AllowIsotropicRotation",this);  
  AllowIsotropicRotationCmd->SetGuidance("\t\tTo allow random isotropic rotation of the init.kinematics vertex (1) or no (0)");         
  AllowIsotropicRotationCmd->SetDefaultValue (1);
  AllowIsotropicRotationCmd->SetParameterName("AllowIsotropicRotation",omittable=true);
  AllowIsotropicRotationCmd->SetRange("AllowIsotropicRotation==0 || AllowIsotropicRotation==1"); 
  AllowIsotropicRotationCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  PhysicsListCmd = new G4UIcmdWithAString("/user/PhysicsList",this);  
  PhysicsListCmd->SetGuidance("\tPhysics list in view: hadr_em, for example FTFP_BERT_LIV.\n"
    "hadr:  CHIPS, FTFP_BERT, FTFP_BERT_TRV, FTFP_BERT_HP, FTF_BIC, LBE, LHEP,\n" 
    "\tQBBC, QGSC_BERT, QGSP_BERT, QGSP_BERT_CHIPS, QGSP_BERT_HP, QGSP_BIC, QGSP_BIC_HP;\n"
    "\tQGSP_FTFP_BERT, QGS_BIC, QGSP_INCLXX, Shielding, ShieldingLEND.\n" 
    "em: nothing, _EMV, _EMX, _EMY, _EMZ, _LIV, _PEN.");
  PhysicsListCmd->SetDefaultValue ("FTFP_BERT_LIV");
  PhysicsListCmd->SetCandidates(
    "CHIPS FTFP_BERT FTFP_BERT_TRV FTFP_BERT_HP FTF_BIC LBE LHEP "
    "QBBC QGSC_BERT QGSP_BERT QGSP_BERT_CHIPS QGSP_BERT_HP QGSP_BIC QGSP_BIC_HP "
    "QGSP_FTFP_BERT QGS_BIC QGSP_INCLXX Shielding ShieldingLEND "
    "CHIPS_EMV FTFP_BERT_EMV FTFP_BERT_TRV_EMV FTFP_BERT_HP_EMV FTF_BIC_EMV LBE_EMV LHEP_EMV "
    "QBBC_EMV QGSC_BERT_EMV QGSP_BERT_EMV QGSP_BERT_CHIPS_EMV QGSP_BERT_HP_EMV QGSP_BIC_EMV QGSP_BIC_HP_EMV "
    "QGSP_FTFP_BERT_EMV QGS_BIC_EMV QGSP_INCLXX_EMV Shielding_EMV ShieldingLEND_EMV "
    "CHIPS_EMX FTFP_BERT_EMX FTFP_BERT_TRV_EMX FTFP_BERT_HP_EMX FTF_BIC_EMX LBE_EMX LHEP_EMX "
    "QBBC_EMX QGSC_BERT_EMX QGSP_BERT_EMX QGSP_BERT_CHIPS_EMX QGSP_BERT_HP_EMX QGSP_BIC_EMX QGSP_BIC_HP_EMX "
    "QGSP_FTFP_BERT_EMX QGS_BIC_EMX QGSP_INCLXX_EMX Shielding_EMX ShieldingLEND_EMX "
    "CHIPS_EMY FTFP_BERT_EMY FTFP_BERT_TRV_EMY FTFP_BERT_HP_EMY FTF_BIC_EMY LBE_EMY LHEP_EMY "
    "QBBC_EMY QGSC_BERT_EMY QGSP_BERT_EMY QGSP_BERT_CHIPS_EMY QGSP_BERT_HP_EMY QGSP_BIC_EMY QGSP_BIC_HP_EMY "
    "QGSP_FTFP_BERT_EMY QGS_BIC_EMY QGSP_INCLXX_EMY Shielding_EMY ShieldingLEND_EMY "
    "CHIPS_EMZ FTFP_BERT_EMZ FTFP_BERT_TRV_EMZ FTFP_BERT_HP_EMZ FTF_BIC_EMZ LBE_EMZ LHEP_EMZ "
    "QBBC_EMZ QGSC_BERT_EMZ QGSP_BERT_EMZ QGSP_BERT_CHIPS_EMZ QGSP_BERT_HP_EMZ QGSP_BIC_EMZ QGSP_BIC_HP_EMZ "
    "QGSP_FTFP_BERT_EMZ QGS_BIC_EMZ QGSP_INCLXX_EMZ Shielding_EMZ ShieldingLEND_EMZ "
    "CHIPS_LIV FTFP_BERT_LIV FTFP_BERT_TRV_LIV FTFP_BERT_HP_LIV FTF_BIC_LIV LBE_LIV LHEP_LIV "
    "QBBC_LIV QGSC_BERT_LIV QGSP_BERT_LIV QGSP_BERT_CHIPS_LIV QGSP_BERT_HP_LIV QGSP_BIC_LIV QGSP_BIC_HP_LIV "
    "QGSP_FTFP_BERT_LIV QGS_BIC_LIV QGSP_INCLXX_LIV Shielding_LIV ShieldingLEND_LIV "
    "CHIPS_PEN FTFP_BERT_PEN FTFP_BERT_TRV_PEN FTFP_BERT_HP_PEN FTF_BIC_PEN LBE_PEN LHEP_PEN "
    "QBBC_PEN QGSC_BERT_PEN QGSP_BERT_PEN QGSP_BERT_CHIPS_PEN QGSP_BERT_HP_PEN QGSP_BIC_PEN QGSP_BIC_HP_PEN "
    "QGSP_FTFP_BERT_PEN QGS_BIC_PEN QGSP_INCLXX_PEN Shielding_PEN ShieldingLEND_PEN ");
  PhysicsListCmd->SetParameterName("PhysicsList",omittable=false);
  PhysicsListCmd->AvailableForStates(G4State_PreInit,G4State_Idle);// Options: hadr:  CHIPS, FTFP_BERT, FTFP_BERT_TRV, FTFP_BERT_HP, FTF_BIC, LBE, LHEP, 
                    // QBBC, QGSC_BERT, QGSP_BERT, QGSP_BERT_CHIPS, QGSP_BERT_HP, QGSP_BIC, QGSP_BIC_HP,
                    // QGSP_FTFP_BERT, QGS_BIC, QGSP_INCLXX, Shielding, ShieldingLEND with add  
                    // em: {"","_EMV","_EMX","_EMY","_EMZ","_LIV","_PEN"}, for example FTFP_BERT_LIV

  Decay0FileCmd = new G4UIcmdWithAString("/user/Decay0File",this);  
  Decay0FileCmd->SetGuidance("\tPath and name of the input Decay0 file.");
  Decay0FileCmd->SetDefaultValue ("");
  Decay0FileCmd->SetParameterName("Decay0File",omittable=true);
  Decay0FileCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  


  showAllCmd = new G4UIcmdWithoutParameter("/user/showAll",this);  
  showAllCmd->SetGuidance("\t\tShow all my parameters.");         
  showAllCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  initCmd = new G4UIcmdWithoutParameter("/user/init",this);  
  initCmd->SetGuidance("\t\tInitialize the detector.");         
  initCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  resetCmd = new G4UIcmdWithoutParameter("/user/reset",this);  
  resetCmd->SetGuidance("\t\tInitialize the detector.");         
  resetCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

} // end of constructor

//..../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......

SimourgMessenger::~SimourgMessenger()
{
  delete D_SHLDCmd;
  delete Detector_SHLDCmd;  
  delete ZL_SHLDCmd;  
  delete MaterialSHLDDensityCmd;  
  delete MaterialSHLDElementNameCmd;  
  delete MaterialSHLDFormulaNumCmd;

  delete D_Cover1Cmd;
  delete Detector_Cover1Cmd;
  delete XL_Cover1Cmd;
  delete YL_Cover1Cmd;
  delete ZL_Cover1Cmd;
  delete Z_Cover1Cmd;
  delete MaterialCover1DensityCmd;
  delete MaterialCover1ElementNameCmd;
  delete MaterialCover1FormulaNumCmd;

  delete D_MarinelliCmd;
  delete XL_MarinelliCmd;
  delete YL_MarinelliCmd;
  delete ZL_MarinelliCmd;
  delete Z_MarinelliCmd;
  delete MaterialMarinelliDensityCmd;
  delete MaterialMarinelliElementNameCmd;
  delete MaterialMarinelliFormulaNumCmd;

  delete D_Cover2Cmd;
  delete Detector_Cover2Cmd;
  delete XL_Cover2Cmd;
  delete YL_Cover2Cmd;
  delete ZL_Cover2Cmd;
  delete Z_Cover2Cmd;
  delete MaterialCover2DensityCmd;
  delete MaterialCover2ElementNameCmd;
  delete MaterialCover2FormulaNumCmd;

  delete D_CoreCmd;
  delete XL_CoreCmd;
  delete YL_CoreCmd;
  delete ZL_CoreCmd;
  delete Z_CoreCmd;
  delete MaterialCoreDensityCmd;
  delete MaterialCoreElementNameCmd;
  delete MaterialCoreFormulaNumCmd;

  delete D_DetCmd;
  delete XL_DetCmd;
  delete YL_DetCmd;
  delete ZL_DetCmd;
  delete Z_DetCmd;
  delete MaterialDetDensityCmd;
  delete MaterialDetElementNameCmd;
  delete MaterialDetFormulaNumCmd;

  delete D_CavityCmd;
  delete Detector_CavityCmd;
  delete ZL_CavityCmd;
  delete Z_CavityCmd;
  delete MaterialCavityDensityCmd;
  delete MaterialCavityElementNameCmd;
  delete MaterialCavityFormulaNumCmd;

  delete D_Top1Cmd;
  delete Detector_Top1Cmd;
  delete ZL_Top1Cmd;
  delete Z_Top1Cmd;
  delete MaterialTop1DensityCmd;
  delete MaterialTop1ElementNameCmd;
  delete MaterialTop1FormulaNumCmd;

  delete D_Top2Cmd;
  delete Detector_Top2Cmd;
  delete ZL_Top2Cmd;
  delete Z_Top2Cmd;
  delete MaterialTop2DensityCmd;
  delete MaterialTop2ElementNameCmd;
  delete MaterialTop2FormulaNumCmd;

  delete D_Top3Cmd;
  delete Detector_Top3Cmd;
  delete ZL_Top3Cmd;
  delete Z_Top3Cmd;
  delete MaterialTop3DensityCmd;
  delete MaterialTop3ElementNameCmd;
  delete MaterialTop3FormulaNumCmd;

  delete D_Bot1Cmd;
  delete Detector_Bot1Cmd;
  delete ZL_Bot1Cmd;
  delete Z_Bot1Cmd;
  delete MaterialBot1DensityCmd;
  delete MaterialBot1ElementNameCmd;
  delete MaterialBot1FormulaNumCmd;

  delete D_Bot2Cmd;
  delete Detector_Bot2Cmd;
  delete ZL_Bot2Cmd;
  delete Z_Bot2Cmd;
  delete MaterialBot2DensityCmd;
  delete MaterialBot2ElementNameCmd;
  delete MaterialBot2FormulaNumCmd;

  delete D_Bot3Cmd;
  delete Detector_Bot3Cmd;
  delete ZL_Bot3Cmd;
  delete Z_Bot3Cmd;
  delete MaterialBot3DensityCmd;
  delete MaterialBot3ElementNameCmd;
  delete MaterialBot3FormulaNumCmd;

  delete XL_SrcCmd;
  delete YL_SrcCmd;
  delete ZL_SrcCmd;
  delete X_SrcCmd;
  delete Y_SrcCmd;
  delete Z_SrcCmd;
	delete VolumeSrcCmd;

  delete XL_UnSrcCmd;
  delete YL_UnSrcCmd;
  delete ZL_UnSrcCmd;
  delete X_UnSrcCmd;
  delete Y_UnSrcCmd;
  delete Z_UnSrcCmd;
	delete VolumeUnSrcCmd;

  delete EGammaCmd;
  delete FWHM1Cmd;
  delete FWHM2Cmd;
  delete AlphaBetaCmd;
  delete ThresholdCmd;
  delete SaveToCmd;
  delete wrlFilesQuantityCmd;
  delete tMinCmd;
  delete tMaxCmd;
  delete ELowLimitCmd;
  delete DELowLimitCmd;
  delete DGLowLimitCmd;
  delete ChannelWidthCmd;
  delete numberOfRunsCmd;
  delete StepCmd;
  delete RandomSeedCmd;
  delete WaitCommandCmd;
  delete VerboseVisCmd;
  delete VerboseAllCmd;
  delete DoPictureCmd;
  delete AllowIsotropicRotationCmd;
  delete PhysicsListCmd;

  delete showAllCmd;
  delete initCmd;
  delete resetCmd;
  delete userDir;
  
} // end of destructor

//..../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......
//..../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......../|\|/|\|/|\......

void SimourgMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{
  G4int i;
   


  if( command == D_SHLDCmd )
    gl.D_SHLD=D_SHLDCmd->GetNewDoubleValue(newValue);
  if( command == ZL_SHLDCmd )
    gl.ZL_SHLD=ZL_SHLDCmd->GetNewDoubleValue(newValue);
  if( command == MaterialSHLDDensityCmd )
    gl.MaterialSHLDDensity=MaterialSHLDDensityCmd->GetNewDoubleValue(newValue);
  if( command == MaterialSHLDElementNameCmd )
  {
    if(gl.iFlag == 1)
      G4Exception("SimourgMessenger::SetNewValue()","",FatalException,
        "\n\n\n### MaterialSHLD: Bad order in formula!");
    gl.iFlag = 1;
    gl.MaterialSHLDElementName=newValue;
    gl.MaterialSHLDElementNames[gl.MaterialSHLDNComponents]=newValue;
  }
  if( command == MaterialSHLDFormulaNumCmd )
  {
    if(gl.iFlag == 0)
      G4Exception("SimourgMessenger::SetNewValue()","",FatalException,
        "\n\n\n### MaterialSHLD: Bad order in formula!");
    gl.iFlag = 0;
    gl.MaterialSHLDFormulaNum=MaterialSHLDFormulaNumCmd->GetNewIntValue(newValue);
    gl.MaterialSHLDFormulaN[gl.MaterialSHLDNComponents] = gl.MaterialSHLDFormulaNum;
    gl.MaterialSHLDNComponents++;
  }

  if (command == MaterialSHLDWeightCmd) {
  std::istringstream iss(newValue);
  G4String element;
  G4double weight;

  while (iss >> element >> weight) {
    gl.SHLDElementSolution[element] = weight;
  }
}

  if( command == ZL_SHLDCmd || command == D_SHLDCmd ||
      command == MaterialSHLDDensityCmd || command == MaterialSHLDElementNameCmd ||
      command == MaterialSHLDFormulaNumCmd ) gl.isSHLD=true;
  if( command == Detector_SHLDCmd && Detector_SHLDCmd->GetNewIntValue(newValue)==1)
      gl.DetectorsList.push_back("SHLD");//

  if( command == D_Cover2Cmd )
  {
    gl.isCover2Box=0;
    gl.D_Cover2=D_Cover2Cmd->GetNewDoubleValue(newValue);
    //gl.XL_Cover2=gl.D_Cover2;
    //gl.YL_Cover2=gl.D_Cover2;
  }
  if( command == D_MarinelliCmd )
  {
    gl.isCover2Box=0;
    gl.D_Cover2=D_MarinelliCmd->GetNewDoubleValue(newValue);
    //gl.XL_Cover2=gl.D_Cover2;
    //gl.YL_Cover2=gl.D_Cover2;
  }
  if( command == XL_Cover2Cmd )
  {
    gl.isCover2Box++;
    gl.XL_Cover2=XL_Cover2Cmd->GetNewDoubleValue(newValue);
  }
  if( command == XL_MarinelliCmd )
  {
    gl.isCover2Box++;
    gl.XL_Cover2=XL_MarinelliCmd->GetNewDoubleValue(newValue);
  }
  if( command == YL_Cover2Cmd )
  {
    gl.isCover2Box++;
    gl.YL_Cover2=YL_Cover2Cmd->GetNewDoubleValue(newValue);
  }
  if( command == YL_MarinelliCmd )
  {
    gl.isCover2Box++;
    gl.YL_Cover2=YL_MarinelliCmd->GetNewDoubleValue(newValue);
  }
  if( command == ZL_Cover2Cmd )
    gl.ZL_Cover2=ZL_Cover2Cmd->GetNewDoubleValue(newValue);
  if( command == ZL_MarinelliCmd )
    gl.ZL_Cover2=ZL_MarinelliCmd->GetNewDoubleValue(newValue);
  if( command == Z_Cover2Cmd )
    gl.Z_Cover2=Z_Cover2Cmd->GetNewDoubleValue(newValue);
  if( command == Y_Cover2Cmd )
    gl.Y_Cover2=Y_Cover2Cmd->GetNewDoubleValue(newValue);
  if( command == X_Cover2Cmd )
    gl.X_Cover2=X_Cover2Cmd->GetNewDoubleValue(newValue);
  if( command == Rot_Cover2Cmd)
    gl.Rot_Cover2 = Rot_Cover2Cmd->GetNew3VectorValue(newValue);
  if( command == Z_MarinelliCmd )
    gl.Z_Cover2=Z_MarinelliCmd->GetNewDoubleValue(newValue);
  if( command == MaterialCover2DensityCmd )
    gl.MaterialCover2Density=MaterialCover2DensityCmd->GetNewDoubleValue(newValue);
  if( command == MaterialMarinelliDensityCmd )
    gl.MaterialCover2Density=MaterialMarinelliDensityCmd->GetNewDoubleValue(newValue);
  if( command == MaterialCover2ElementNameCmd )
  {
    if(gl.iFlag == 1)
      G4Exception("SimourgMessenger::SetNewValue()","",FatalException,
        "\n\n\n### MaterialCover2: Bad order in formula!");
    gl.iFlag = 1;
    gl.MaterialCover2ElementName=newValue;
    gl.MaterialCover2ElementNames[gl.MaterialCover2NComponents]=newValue;
  }
  if( command == MaterialMarinelliElementNameCmd )
  {
    if(gl.iFlag == 1)
      G4Exception("SimourgMessenger::SetNewValue()","",FatalException,
        "\n\n\n### MaterialMarinelli: Bad order in formula!");
    gl.iFlag = 1;
    gl.MaterialCover2ElementName=newValue;
    gl.MaterialCover2ElementNames[gl.MaterialCover2NComponents]=newValue;
  }
  if( command == MaterialCover2FormulaNumCmd )
  {
    if(gl.iFlag == 0)
      G4Exception("SimourgMessenger::SetNewValue()","",FatalException,
        "\n\n\n### MaterialCover2: Bad order in formula!");
    gl.iFlag = 0;
    gl.MaterialCover2FormulaNum=MaterialCover2FormulaNumCmd->GetNewIntValue(newValue);
    gl.MaterialCover2FormulaN[gl.MaterialCover2NComponents] = gl.MaterialCover2FormulaNum;
    gl.MaterialCover2NComponents++;
  }
  if( command == MaterialMarinelliFormulaNumCmd )
  {
    if(gl.iFlag == 0)
      G4Exception("SimourgMessenger::SetNewValue()","",FatalException,
        "\n\n\n### MaterialMarinelli: Bad order in formula!");
    gl.iFlag = 0;
    gl.MaterialCover2FormulaNum=MaterialMarinelliFormulaNumCmd->GetNewIntValue(newValue);
    gl.MaterialCover2FormulaN[gl.MaterialCover2NComponents] = gl.MaterialCover2FormulaNum;
    gl.MaterialCover2NComponents++;
  }

  if (command == MaterialCover2WeightCmd) {
  std::istringstream iss(newValue);
  G4String element;
  G4double weight;

  while (iss >> element >> weight) {
    gl.Cover2ElementSolution[element] = weight;
  }
}

  if (command == MaterialMarinelliWeightCmd) {
  std::istringstream iss(newValue);
  G4String element;
  G4double weight;

  while (iss >> element >> weight) {
    gl.Cover2ElementSolution[element] = weight;
  }
}

  if( command == XL_Cover2Cmd || command == YL_Cover2Cmd || command == ZL_Cover2Cmd || 
      command == D_Cover2Cmd || command == Z_Cover2Cmd ||
      command == MaterialCover2DensityCmd || command == MaterialCover2ElementNameCmd ||
      command == MaterialCover2FormulaNumCmd ||
			command == XL_MarinelliCmd || command == YL_MarinelliCmd || command == ZL_MarinelliCmd || 
      command == D_MarinelliCmd || command == Z_MarinelliCmd ||
      command == MaterialMarinelliDensityCmd || command == MaterialMarinelliElementNameCmd ||
      command == MaterialMarinelliFormulaNumCmd) gl.isCover2=true;

  if( command == Detector_Cover2Cmd && Detector_Cover2Cmd->GetNewIntValue(newValue)==1)
      gl.DetectorsList.push_back("Cover2");//

  if( command == D_Cover1Cmd )
  {
    gl.isCover1Box=0;
    gl.D_Cover1=D_Cover1Cmd->GetNewDoubleValue(newValue);
    //gl.XL_Cover1=gl.D_Cover1;
    //gl.YL_Cover1=gl.D_Cover1;
  }
  if( command == D_CoreCmd )
  {
    gl.isCover1Box=0;
    gl.D_Cover1=D_CoreCmd->GetNewDoubleValue(newValue);
    //gl.XL_Cover1=gl.D_Cover1;
    //gl.YL_Cover1=gl.D_Cover1;
  }
  if( command == XL_Cover1Cmd )
  {
    gl.isCover1Box++;
    gl.XL_Cover1=XL_Cover1Cmd->GetNewDoubleValue(newValue);
  }
  if( command == XL_CoreCmd )
  {
    gl.isCover1Box++;
    gl.XL_Cover1=XL_CoreCmd->GetNewDoubleValue(newValue);
  }
  if( command == YL_Cover1Cmd )
  {
    gl.isCover1Box++;
    gl.YL_Cover1=YL_Cover1Cmd->GetNewDoubleValue(newValue);
  }
  if( command == YL_CoreCmd )
  {
    gl.isCover1Box++;
    gl.YL_Cover1=YL_CoreCmd->GetNewDoubleValue(newValue);
  }
  if( command == ZL_Cover1Cmd )
    gl.ZL_Cover1=ZL_Cover1Cmd->GetNewDoubleValue(newValue);
  if( command == ZL_CoreCmd )
    gl.ZL_Cover1=ZL_CoreCmd->GetNewDoubleValue(newValue);
  if( command == Z_Cover1Cmd )
    gl.Z_Cover1=Z_Cover1Cmd->GetNewDoubleValue(newValue);
  if( command == Z_CoreCmd )
    gl.Z_Cover1=Z_CoreCmd->GetNewDoubleValue(newValue);
//NEW
  if( command == Y_Cover1Cmd )
    gl.Y_Cover1=Y_Cover1Cmd->GetNewDoubleValue(newValue);
  if( command == X_Cover1Cmd )
    gl.X_Cover1=X_Cover1Cmd->GetNewDoubleValue(newValue);
  if( command == Rot_Cover1Cmd)
    gl.Rot_Cover1 = Rot_Cover1Cmd->GetNew3VectorValue(newValue);

  if( command == Y_CoreCmd )
    gl.Y_Cover1=Y_CoreCmd->GetNewDoubleValue(newValue);
  if( command == X_CoreCmd )
    gl.X_Cover1=X_CoreCmd->GetNewDoubleValue(newValue);
  if( command == Rot_CoreCmd)
    gl.Rot_Cover1 = Rot_CoreCmd->GetNew3VectorValue(newValue);

  if( command == MaterialCover1DensityCmd )
    gl.MaterialCover1Density=MaterialCover1DensityCmd->GetNewDoubleValue(newValue);
  if( command == MaterialCoreDensityCmd )
    gl.MaterialCover1Density=MaterialCoreDensityCmd->GetNewDoubleValue(newValue);
  if( command == MaterialCover1ElementNameCmd )
  {
    if(gl.iFlag == 1)
      G4Exception("SimourgMessenger::SetNewValue()","",FatalException,
        "\n\n\n### MaterialCover1: Bad order in formula!");
    gl.iFlag = 1;
    gl.MaterialCover1ElementName=newValue;
    gl.MaterialCover1ElementNames[gl.MaterialCover1NComponents]=newValue;
  }
  if( command == MaterialCoreElementNameCmd )
  {
    if(gl.iFlag == 1)
      G4Exception("SimourgMessenger::SetNewValue()","",FatalException,
        "\n\n\n### MaterialCore: Bad order in formula!");
    gl.iFlag = 1;
    gl.MaterialCover1ElementName=newValue;
    gl.MaterialCover1ElementNames[gl.MaterialCover1NComponents]=newValue;
  }
  if( command == MaterialCover1FormulaNumCmd )
  {
    if(gl.iFlag == 0)
      G4Exception("SimourgMessenger::SetNewValue()","",FatalException,
        "\n\n\n### MaterialCover1: Bad order in formula!");
    gl.iFlag = 0;
    gl.MaterialCover1FormulaNum=MaterialCover1FormulaNumCmd->GetNewIntValue(newValue);
    gl.MaterialCover1FormulaN[gl.MaterialCover1NComponents] = gl.MaterialCover1FormulaNum;
    gl.MaterialCover1NComponents++;
  }

 

  if( command == MaterialCoreFormulaNumCmd )
  {
    if(gl.iFlag == 0)
      G4Exception("SimourgMessenger::SetNewValue()","",FatalException,
        "\n\n\n### MaterialCore: Bad order in formula!");
    gl.iFlag = 0;
    gl.MaterialCover1FormulaNum=MaterialCoreFormulaNumCmd->GetNewIntValue(newValue);
    gl.MaterialCover1FormulaN[gl.MaterialCover1NComponents] = gl.MaterialCover1FormulaNum;
    gl.MaterialCover1NComponents++;
  }

 if (command == MaterialCover1WeightCmd) {
  std::istringstream iss(newValue);
  G4String element;
  G4double weight;

  while (iss >> element >> weight) {
    gl.Cover1ElementSolution[element] = weight;
  }
}

  if (command == MaterialCoreWeightCmd) {
  std::istringstream iss(newValue);
  G4String element;
  G4double weight;

  while (iss >> element >> weight) {
    gl.Cover1ElementSolution[element] = weight;
  }
}

  if( command == XL_Cover1Cmd || command == YL_Cover1Cmd || command == ZL_Cover1Cmd || 
      command == D_Cover1Cmd || command == Z_Cover1Cmd ||
      command == MaterialCover1DensityCmd || command == MaterialCover1ElementNameCmd ||
      command == MaterialCover1FormulaNumCmd ||
			command == XL_CoreCmd || command == YL_CoreCmd || command == ZL_CoreCmd || 
      command == D_CoreCmd || command == Z_CoreCmd ||
      command == MaterialCoreDensityCmd || command == MaterialCoreElementNameCmd ||
      command == MaterialCoreFormulaNumCmd  ) gl.isCover1=true;
  if( command == Detector_Cover1Cmd && Detector_Cover1Cmd->GetNewIntValue(newValue)==1)
      gl.DetectorsList.push_back("Cover1");//


  if( command == D_DetCmd )
  {
    gl.isDetBox=0;
    gl.D_Det=D_DetCmd->GetNewDoubleValue(newValue);
    //gl.XL_Det=gl.D_Det;
    //gl.YL_Det=gl.D_Det;
  }
  if( command == XL_DetCmd )
  {
    gl.isDetBox++;
    gl.XL_Det=XL_DetCmd->GetNewDoubleValue(newValue);
  }
  if( command == YL_DetCmd )
  {
    gl.isDetBox++;
    gl.YL_Det=YL_DetCmd->GetNewDoubleValue(newValue);
  }
  if( command == ZL_DetCmd )
    gl.ZL_Det=ZL_DetCmd->GetNewDoubleValue(newValue);
  if( command == Z_DetCmd )
    gl.Z_Det=Z_DetCmd->GetNewDoubleValue(newValue);
//NEW
  if( command == Y_DetCmd )
    gl.Y_Det=Y_DetCmd->GetNewDoubleValue(newValue);
  if( command == X_DetCmd )
    gl.X_Det=X_DetCmd->GetNewDoubleValue(newValue);
  if( command == Rot_DetCmd)
    gl.Rot_Det = Rot_DetCmd->GetNew3VectorValue(newValue);

  if( command == MaterialDetDensityCmd )
    gl.MaterialDetDensity=MaterialDetDensityCmd->GetNewDoubleValue(newValue);
  if( command == MaterialDetElementNameCmd )
  {
    if(gl.iFlag == 1)
      G4Exception("SimourgMessenger::SetNewValue()","",FatalException,
        "\n\n\n### MaterialDet: Bad order in formula!");
    gl.iFlag = 1;
    gl.MaterialDetElementName=newValue;
    gl.MaterialDetElementNames[gl.MaterialDetNComponents]=newValue;
  }
  if( command == MaterialDetFormulaNumCmd )
  {
    if(gl.iFlag == 0)
      G4Exception("SimourgMessenger::SetNewValue()","",FatalException,
        "\n\n\n### MaterialDet: Bad order in formula!");
    gl.iFlag = 0;
    gl.MaterialDetFormulaNum=MaterialDetFormulaNumCmd->GetNewIntValue(newValue);
    gl.MaterialDetFormulaN[gl.MaterialDetNComponents] = gl.MaterialDetFormulaNum;
    gl.MaterialDetNComponents++;
  }

  if (command == MaterialDetWeightCmd) {
  std::istringstream iss(newValue);
  G4String element;
  G4double weight;

  while (iss >> element >> weight) {
    gl.DetElementSolution[element] = weight;
  }
}

  if( command == XL_DetCmd || command == YL_DetCmd || command == ZL_DetCmd || 
      command == D_DetCmd || command == Z_DetCmd ||
      command == MaterialDetDensityCmd || command == MaterialDetElementNameCmd ||
      command == MaterialDetFormulaNumCmd ) gl.isDet=true;

	if( command == D_CavityCmd )
	{
		gl.isCavityBox=0;
    gl.D_Cavity=D_CavityCmd->GetNewDoubleValue(newValue);
	}
  if( command == XL_CavityCmd )
  {
    gl.isCavityBox++;
    gl.XL_Cavity=XL_CavityCmd->GetNewDoubleValue(newValue);
  }
  if( command == YL_CavityCmd )
  {
    gl.isCavityBox++;
    gl.YL_Cavity=YL_CavityCmd->GetNewDoubleValue(newValue);
  }
  if( command == ZL_CavityCmd )
    gl.ZL_Cavity=ZL_CavityCmd->GetNewDoubleValue(newValue);
  if( command == Z_CavityCmd )
    gl.Z_Cavity=Z_CavityCmd->GetNewDoubleValue(newValue);
//NEW
  if( command == Y_CavityCmd )
    gl.Y_Cavity=Y_CavityCmd->GetNewDoubleValue(newValue);
  if( command == X_CavityCmd )
    gl.X_Cavity=X_CavityCmd->GetNewDoubleValue(newValue);
  if( command == Rot_CavityCmd)
    gl.Rot_Cavity = Rot_CavityCmd->GetNew3VectorValue(newValue);

  if( command == MaterialCavityDensityCmd )
    gl.MaterialCavityDensity=MaterialCavityDensityCmd->GetNewDoubleValue(newValue);
  if( command == MaterialCavityElementNameCmd )
  {
    if(gl.iFlag == 1)
      G4Exception("SimourgMessenger::SetNewValue()","",FatalException,
        "\n\n\n### MaterialCavity: Bad order in formula!");
    gl.iFlag = 1;
    gl.MaterialCavityElementName=newValue;
    gl.MaterialCavityElementNames[gl.MaterialCavityNComponents]=newValue;
  }
  if( command == MaterialCavityFormulaNumCmd )
  {
    if(gl.iFlag == 0)
      G4Exception("SimourgMessenger::SetNewValue()","",FatalException,
        "\n\n\n### MaterialCavity: Bad order in formula!");
    gl.iFlag = 0;
    gl.MaterialCavityFormulaNum=MaterialCavityFormulaNumCmd->GetNewIntValue(newValue);
    gl.MaterialCavityFormulaN[gl.MaterialCavityNComponents] = gl.MaterialCavityFormulaNum;
    gl.MaterialCavityNComponents++;
  }

  if (command == MaterialCavityWeightCmd) {
  std::istringstream iss(newValue);
  G4String element;
  G4double weight;

  while (iss >> element >> weight) {
    gl.CavityElementSolution[element] = weight;
  }
}

  if( command == XL_CavityCmd || command == YL_CavityCmd || command == ZL_CavityCmd ||
			command == D_CavityCmd || command == Z_CavityCmd ||
      command == MaterialCavityDensityCmd || command == MaterialCavityElementNameCmd ||
      command == MaterialCavityFormulaNumCmd ) gl.isCavity=true;
  if( command == Detector_CavityCmd && Detector_CavityCmd->GetNewIntValue(newValue)==1)
      gl.DetectorsList.push_back("Cavity");//


  if( command == D_Top1Cmd )
    gl.D_Top1=D_Top1Cmd->GetNewDoubleValue(newValue);
  if( command == d_Top1Cmd )
    gl.d_Top1=d_Top1Cmd->GetNewDoubleValue(newValue);
  if( command == ZL_Top1Cmd )
    gl.ZL_Top1=ZL_Top1Cmd->GetNewDoubleValue(newValue);
  if( command == Z_Top1Cmd )
    gl.Z_Top1=Z_Top1Cmd->GetNewDoubleValue(newValue);
//NEW
  if( command == Y_Top1Cmd )
    gl.Y_Top1=Y_Top1Cmd->GetNewDoubleValue(newValue);
  if( command == X_Top1Cmd )
    gl.X_Top1=X_Top1Cmd->GetNewDoubleValue(newValue);
  if( command == Rot_Top1Cmd)
    gl.Rot_Top1 = Rot_Top1Cmd->GetNew3VectorValue(newValue);

  if( command == MaterialTop1DensityCmd )
    gl.MaterialTop1Density=MaterialTop1DensityCmd->GetNewDoubleValue(newValue);
  if( command == MaterialTop1ElementNameCmd )
  {
    if(gl.iFlag == 1)
      G4Exception("SimourgMessenger::SetNewValue()","",FatalException,
        "\n\n\n### MaterialTop1: Bad order in formula!");
    gl.iFlag = 1;
    gl.MaterialTop1ElementName=newValue;
    gl.MaterialTop1ElementNames[gl.MaterialTop1NComponents]=newValue;
  }
  if( command == MaterialTop1FormulaNumCmd )
  {
    if(gl.iFlag == 0)
      G4Exception("SimourgMessenger::SetNewValue()","",FatalException,
        "\n\n\n### MaterialTop1: Bad order in formula!");
    gl.iFlag = 0;
    gl.MaterialTop1FormulaNum=MaterialTop1FormulaNumCmd->GetNewIntValue(newValue);
    gl.MaterialTop1FormulaN[gl.MaterialTop1NComponents] = gl.MaterialTop1FormulaNum;
    gl.MaterialTop1NComponents++;
  }

  if (command == MaterialTop1WeightCmd) {
  std::istringstream iss(newValue);
  G4String element;
  G4double weight;

  while (iss >> element >> weight) {
    gl.Top1ElementSolution[element] = weight;
  }
}

  if( command == D_Top1Cmd || command == ZL_Top1Cmd || command == Z_Top1Cmd ||
      command == MaterialTop1DensityCmd || command == MaterialTop1ElementNameCmd ||
      command == MaterialTop1FormulaNumCmd ) gl.isTop1=true; 
  
  if( command == Detector_Top1Cmd && Detector_Top1Cmd->GetNewIntValue(newValue)==1)
      gl.DetectorsList.push_back("Top1");//

  if( command == D_Top2Cmd )
    gl.D_Top2=D_Top2Cmd->GetNewDoubleValue(newValue);
  if( command == d_Top2Cmd )
    gl.d_Top2=d_Top2Cmd->GetNewDoubleValue(newValue);
  if( command == ZL_Top2Cmd )
    gl.ZL_Top2=ZL_Top2Cmd->GetNewDoubleValue(newValue);
  if( command == Z_Top2Cmd )
    gl.Z_Top2=Z_Top2Cmd->GetNewDoubleValue(newValue);
//NEW
  if( command == Y_Top2Cmd )
    gl.Y_Top2=Y_Top2Cmd->GetNewDoubleValue(newValue);
  if( command == X_Top2Cmd )
    gl.X_Top2=X_Top2Cmd->GetNewDoubleValue(newValue);
  if( command == Rot_Top2Cmd)
    gl.Rot_Top2 = Rot_Top2Cmd->GetNew3VectorValue(newValue);

  if( command == MaterialTop2DensityCmd )
    gl.MaterialTop2Density=MaterialTop2DensityCmd->GetNewDoubleValue(newValue);
  if( command == MaterialTop2ElementNameCmd )
  {
    if(gl.iFlag == 1)
      G4Exception("SimourgMessenger::SetNewValue()","",FatalException,
        "\n\n\n### MaterialTop2: Bad order in formula!");
    gl.iFlag = 1;
    gl.MaterialTop2ElementName=newValue;
    gl.MaterialTop2ElementNames[gl.MaterialTop2NComponents]=newValue;
  }
  if( command == MaterialTop2FormulaNumCmd )
  {
    if(gl.iFlag == 0)
      G4Exception("SimourgMessenger::SetNewValue()","",FatalException,
        "\n\n\n### MaterialTop2: Bad order in formula!");
    gl.iFlag = 0;
    gl.MaterialTop2FormulaNum=MaterialTop2FormulaNumCmd->GetNewIntValue(newValue);
    gl.MaterialTop2FormulaN[gl.MaterialTop2NComponents] = gl.MaterialTop2FormulaNum;
    gl.MaterialTop2NComponents++;
  }
    if (command == MaterialTop2WeightCmd) {
  std::istringstream iss(newValue);
  G4String element;
  G4double weight;

  while (iss >> element >> weight) {
    gl.Top2ElementSolution[element] = weight;
  }
}
  if( command == D_Top2Cmd || command == ZL_Top2Cmd || command == Z_Top2Cmd ||
      command == MaterialTop2DensityCmd || command == MaterialTop2ElementNameCmd ||
      command == MaterialTop2FormulaNumCmd ) gl.isTop2=true;
  if( command == Detector_Top2Cmd && Detector_Top2Cmd->GetNewIntValue(newValue)==1)
      gl.DetectorsList.push_back("Top2");//

  if( command == D_Top3Cmd )
    gl.D_Top3=D_Top3Cmd->GetNewDoubleValue(newValue);
  if( command == d_Top3Cmd )
    gl.d_Top3=d_Top3Cmd->GetNewDoubleValue(newValue);
  if( command == ZL_Top3Cmd )
    gl.ZL_Top3=ZL_Top3Cmd->GetNewDoubleValue(newValue);
  if( command == Z_Top3Cmd )
    gl.Z_Top3=Z_Top3Cmd->GetNewDoubleValue(newValue);
//NEW
  if( command == Y_Top3Cmd )
    gl.Y_Top3=Y_Top3Cmd->GetNewDoubleValue(newValue);
  if( command == X_Top3Cmd )
    gl.X_Top3=X_Top3Cmd->GetNewDoubleValue(newValue);
  if( command == Rot_Top3Cmd)
    gl.Rot_Top3 = Rot_Top3Cmd->GetNew3VectorValue(newValue);

  if( command == MaterialTop3DensityCmd )
    gl.MaterialTop3Density=MaterialTop3DensityCmd->GetNewDoubleValue(newValue);
  if( command == MaterialTop3ElementNameCmd )
  {
    if(gl.iFlag == 1)
      G4Exception("SimourgMessenger::SetNewValue()","",FatalException,
        "\n\n\n### MaterialTop3: Bad order in formula!");
    gl.iFlag = 1;
    gl.MaterialTop3ElementName=newValue;
    gl.MaterialTop3ElementNames[gl.MaterialTop3NComponents]=newValue;
  }
  if( command == MaterialTop3FormulaNumCmd )
  {
    if(gl.iFlag == 0)
      G4Exception("SimourgMessenger::SetNewValue()","",FatalException,
        "\n\n\n### MaterialTop3: Bad order in formula!");
    gl.iFlag = 0;
    gl.MaterialTop3FormulaNum=MaterialTop3FormulaNumCmd->GetNewIntValue(newValue);
    gl.MaterialTop3FormulaN[gl.MaterialTop3NComponents] = gl.MaterialTop3FormulaNum;
    gl.MaterialTop3NComponents++;
  }
  if (command == MaterialTop3WeightCmd) {
  std::istringstream iss(newValue);
  G4String element;
  G4double weight;

  while (iss >> element >> weight) {
    gl.Top3ElementSolution[element] = weight;
  }
}

  if( command == D_Top3Cmd || command == ZL_Top3Cmd || command == Z_Top3Cmd ||
      command == MaterialTop3DensityCmd || command == MaterialTop3ElementNameCmd ||
      command == MaterialTop3FormulaNumCmd ) gl.isTop3=true;
  if( command == Detector_Top3Cmd && Detector_Top3Cmd->GetNewIntValue(newValue)==1)
      gl.DetectorsList.push_back("Top3");//

  if( command == D_Bot1Cmd )
    gl.D_Bot1=D_Bot1Cmd->GetNewDoubleValue(newValue);
  if( command == d_Bot1Cmd )
    gl.d_Bot1=d_Bot1Cmd->GetNewDoubleValue(newValue);
  if( command == ZL_Bot1Cmd )
    gl.ZL_Bot1=ZL_Bot1Cmd->GetNewDoubleValue(newValue);
  if( command == Z_Bot1Cmd )
    gl.Z_Bot1=Z_Bot1Cmd->GetNewDoubleValue(newValue);
//NEW
  if( command == Y_Bot1Cmd )
    gl.Y_Bot1=Y_Bot1Cmd->GetNewDoubleValue(newValue);
  if( command == X_Bot1Cmd )
    gl.X_Bot1=X_Bot1Cmd->GetNewDoubleValue(newValue);
  if( command == Rot_Bot1Cmd)
    gl.Rot_Bot1 = Rot_Bot1Cmd->GetNew3VectorValue(newValue);

  if( command == MaterialBot1DensityCmd )
    gl.MaterialBot1Density=MaterialBot1DensityCmd->GetNewDoubleValue(newValue);
  if( command == MaterialBot1ElementNameCmd )
  {
    if(gl.iFlag == 1)
      G4Exception("SimourgMessenger::SetNewValue()","",FatalException,
        "\n\n\n### MaterialBot1: Bad order in formula!");
    gl.iFlag = 1;
    gl.MaterialBot1ElementName=newValue;
    gl.MaterialBot1ElementNames[gl.MaterialBot1NComponents]=newValue;
  }
  if( command == MaterialBot1FormulaNumCmd )
  {
    if(gl.iFlag == 0)
      G4Exception("SimourgMessenger::SetNewValue()","",FatalException,
        "\n\n\n### MaterialBot1: Bad order in formula!");
    gl.iFlag = 0;
    gl.MaterialBot1FormulaNum=MaterialBot1FormulaNumCmd->GetNewIntValue(newValue);
    gl.MaterialBot1FormulaN[gl.MaterialBot1NComponents] = gl.MaterialBot1FormulaNum;
    gl.MaterialBot1NComponents++;
  }

  if (command == MaterialBot1WeightCmd) {
  std::istringstream iss(newValue);
  G4String element;
  G4double weight;

  while (iss >> element >> weight) {
    gl.Bot1ElementSolution[element] = weight;
  }
}


  if( command == D_Bot1Cmd || command == ZL_Bot1Cmd || command == Z_Bot1Cmd ||
      command == MaterialBot1DensityCmd || command == MaterialBot1ElementNameCmd ||
      command == MaterialBot1FormulaNumCmd ) gl.isBot1=true;
  if( command == Detector_Bot1Cmd && Detector_Bot1Cmd->GetNewIntValue(newValue)==1)
      gl.DetectorsList.push_back("Bot1");//

  if( command == D_Bot2Cmd )
    gl.D_Bot2=D_Bot2Cmd->GetNewDoubleValue(newValue);
    if( command == d_Bot2Cmd )
    gl.d_Bot2=d_Bot2Cmd->GetNewDoubleValue(newValue);
  if( command == ZL_Bot2Cmd )
    gl.ZL_Bot2=ZL_Bot2Cmd->GetNewDoubleValue(newValue);
  if( command == Z_Bot2Cmd )
    gl.Z_Bot2=Z_Bot2Cmd->GetNewDoubleValue(newValue);
//NEW
  if( command == Y_Bot2Cmd )
    gl.Y_Bot2=Y_Bot2Cmd->GetNewDoubleValue(newValue);
  if( command == X_Bot2Cmd )
    gl.X_Bot2=X_Bot2Cmd->GetNewDoubleValue(newValue);
  if( command == Rot_Bot2Cmd)
    gl.Rot_Bot2 = Rot_Bot2Cmd->GetNew3VectorValue(newValue);


  if( command == MaterialBot2DensityCmd )
    gl.MaterialBot2Density=MaterialBot2DensityCmd->GetNewDoubleValue(newValue);
  if( command == MaterialBot2ElementNameCmd )
  {
    if(gl.iFlag == 1)
      G4Exception("SimourgMessenger::SetNewValue()","",FatalException,
        "\n\n\n### MaterialBot2: Bad order in formula!");
    gl.iFlag = 1;
    gl.MaterialBot2ElementName=newValue;
    gl.MaterialBot2ElementNames[gl.MaterialBot2NComponents]=newValue;
  }
  if( command == MaterialBot2FormulaNumCmd )
  {
    if(gl.iFlag == 0)
      G4Exception("SimourgMessenger::SetNewValue()","",FatalException,
        "\n\n\n### MaterialBot2: Bad order in formula!");
    gl.iFlag = 0;
    gl.MaterialBot2FormulaNum=MaterialBot2FormulaNumCmd->GetNewIntValue(newValue);
    gl.MaterialBot2FormulaN[gl.MaterialBot2NComponents] = gl.MaterialBot2FormulaNum;
    gl.MaterialBot2NComponents++;
  }

  if (command == MaterialBot2WeightCmd) {
  std::istringstream iss(newValue);
  G4String element;
  G4double weight;

  while (iss >> element >> weight) {
    gl.Bot2ElementSolution[element] = weight;
  }
}


  if( command == D_Bot2Cmd || command == ZL_Bot2Cmd || command == Z_Bot2Cmd ||
      command == MaterialBot2DensityCmd || command == MaterialBot2ElementNameCmd ||
      command == MaterialBot2FormulaNumCmd ) gl.isBot2=true;
  if( command == Detector_Bot2Cmd && Detector_Bot2Cmd->GetNewIntValue(newValue)==1)
      gl.DetectorsList.push_back("Bot2");//

  if( command == D_Bot3Cmd )
    gl.D_Bot3=D_Bot3Cmd->GetNewDoubleValue(newValue);
  if( command == d_Bot3Cmd )
    gl.d_Bot3=d_Bot3Cmd->GetNewDoubleValue(newValue);

  if( command == ZL_Bot3Cmd )
    gl.ZL_Bot3=ZL_Bot3Cmd->GetNewDoubleValue(newValue);
  if( command == Z_Bot3Cmd )
    gl.Z_Bot3=Z_Bot3Cmd->GetNewDoubleValue(newValue);
//NEW
  if( command == Y_Bot3Cmd )
    gl.Y_Bot3=Y_Bot3Cmd->GetNewDoubleValue(newValue);
  if( command == X_Bot3Cmd )
    gl.X_Bot3=X_Bot3Cmd->GetNewDoubleValue(newValue);
  if( command == Rot_Bot3Cmd)
    gl.Rot_Bot3 = Rot_Bot3Cmd->GetNew3VectorValue(newValue);

  if( command == MaterialBot3DensityCmd )
    gl.MaterialBot3Density=MaterialBot3DensityCmd->GetNewDoubleValue(newValue);
  if( command == MaterialBot3ElementNameCmd )
  {
    if(gl.iFlag == 1)
      G4Exception("SimourgMessenger::SetNewValue()","",FatalException,
        "\n\n\n### MaterialBot3: Bad order in formula!");
    gl.iFlag = 1;
    gl.MaterialBot3ElementName=newValue;
    gl.MaterialBot3ElementNames[gl.MaterialBot3NComponents]=newValue;
  }
  if( command == MaterialBot3FormulaNumCmd )
  {
    if(gl.iFlag == 0)
      G4Exception("SimourgMessenger::SetNewValue()","",FatalException,
        "\n\n\n### MaterialBot3: Bad order in formula!");
    gl.iFlag = 0;
    gl.MaterialBot3FormulaNum=MaterialBot3FormulaNumCmd->GetNewIntValue(newValue);
    gl.MaterialBot3FormulaN[gl.MaterialBot3NComponents] = gl.MaterialBot3FormulaNum;
    gl.MaterialBot3NComponents++;
  }

  if (command == MaterialBot3WeightCmd) {
  std::istringstream iss(newValue);
  G4String element;
  G4double weight;

  while (iss >> element >> weight) {
    gl.Bot3ElementSolution[element] = weight;
  }
}

  if( command == D_Bot3Cmd || command == ZL_Bot3Cmd || command == Z_Bot3Cmd ||
      command == MaterialBot3DensityCmd || command == MaterialBot3ElementNameCmd ||
      command == MaterialBot3FormulaNumCmd ) gl.isBot3=true; 
  if( gl.isBot3==true && Detector_Bot3Cmd->GetNewIntValue(newValue)==1)
      gl.DetectorsList.push_back("Bot3");//

  if( command == D_SrcCmd )
  {  
    gl.isSrcBox=0;
    gl.D_Src=D_SrcCmd->GetNewDoubleValue(newValue);
    gl.Src_Radius2 = (gl.D_Src*gl.D_Src)/4.; // Radius^2 of the source
  }
  if( command == XL_SrcCmd )
  {
    gl.isSrcBox++;
    gl.XL_Src=XL_SrcCmd->GetNewDoubleValue(newValue);
    if(gl.isSrcBox == 1) gl.YL_Src = gl.XL_Src;
    gl.Src_Radius2 = (gl.XL_Src*gl.XL_Src + gl.YL_Src*gl.YL_Src)/4.; // Radius^2 of the source
  }
  if( command == YL_SrcCmd )
  {
    gl.isSrcBox++;
    gl.YL_Src=YL_SrcCmd->GetNewDoubleValue(newValue);
    if(gl.isSrcBox == 1) gl.XL_Src = gl.YL_Src;
    gl.Src_Radius2 = (gl.XL_Src*gl.XL_Src + gl.YL_Src*gl.YL_Src)/4.; // Radius^2 of the source
  }
  if( command == ZL_SrcCmd )
    gl.ZL_Src=ZL_SrcCmd->GetNewDoubleValue(newValue);
  if( command == X_SrcCmd )
    gl.X_Src=X_SrcCmd->GetNewDoubleValue(newValue);
  if( command == Y_SrcCmd )
    gl.Y_Src=Y_SrcCmd->GetNewDoubleValue(newValue);
  if( command == Z_SrcCmd )
    gl.Z_Src=Z_SrcCmd->GetNewDoubleValue(newValue);
	if( command == VolumeSrcCmd )
	{
		gl.SrcVolume = newValue;
		if(gl.SrcVolume == "SHLD")
		{
			gl.isSrcBox=0;
			gl.D_Src = gl.D_SHLD;
			gl.ZL_Src = gl.ZL_SHLD;
			gl.X_Src = gl.Y_Src = gl.Z_Src = 0.;
		} else if (gl.SrcVolume == "Cover2" || gl.SrcVolume == "Marinelli")
		{
			if(!gl.isCover2) G4Exception("SimourgMessenger::SetNewValue()","",FatalException,
        "\n\n\n### VolumeSrcCmd: Cover2/Marinelli is not defined!");
			gl.isSrcBox = gl.isCover2Box;
			gl.D_Src = gl.D_Cover2;
			gl.XL_Src = gl.XL_Cover2;
			gl.YL_Src = gl.YL_Cover2;
			gl.ZL_Src = gl.ZL_Cover2;
			gl.X_Src = gl.Y_Src = 0.;
			gl.Z_Src = gl.Z_Cover2;
		} else if (gl.SrcVolume == "Cover1" || gl.SrcVolume == "Core")
		{
			if(!gl.isCover1) G4Exception("SimourgMessenger::SetNewValue()","",FatalException,
        "\n\n\n### VolumeSrcCmd: Cover1/Core is not defined!");
			gl.isSrcBox = gl.isCover1Box;
			gl.D_Src = gl.D_Cover1;
			gl.XL_Src = gl.XL_Cover1;
			gl.YL_Src = gl.YL_Cover1;
			gl.ZL_Src = gl.ZL_Cover1;
			gl.X_Src = gl.Y_Src = 0.;
			gl.Z_Src = gl.Z_Cover1;
		} else if (gl.SrcVolume == "Det")
		{
			gl.isSrcBox = gl.isDetBox;
			gl.D_Src = gl.D_Det;
			gl.XL_Src = gl.XL_Det;
			gl.YL_Src = gl.YL_Det;
			gl.ZL_Src = gl.ZL_Det;
			gl.X_Src = gl.Y_Src = 0.;
			gl.Z_Src = gl.Z_Det;
		} else if (gl.SrcVolume == "Cavity")
		{
			if(!gl.isCavity) G4Exception("SimourgMessenger::SetNewValue()","",FatalException,
        "\n\n\n### VolumeSrcCmd: Cavity is not defined!");
			gl.isSrcBox = gl.isCavityBox;
			gl.D_Src = gl.D_Cavity;
			gl.XL_Src = gl.XL_Cavity;
			gl.YL_Src = gl.YL_Cavity;
			gl.ZL_Src = gl.ZL_Cavity;
			gl.X_Src = gl.Y_Src = 0.;
			gl.Z_Src = gl.Z_Cavity;
		} else if (gl.SrcVolume == "Top1")
		{
			if(!gl.isTop1) G4Exception("SimourgMessenger::SetNewValue()","",FatalException,
        "\n\n\n### VolumeSrcCmd: Top1 is not defined!");
			gl.isSrcBox = 0;//gl.isTop1Box;
			gl.D_Src = gl.D_Top1;
			//gl.XL_Src = gl.XL_Top1;
			//gl.YL_Src = gl.YL_Top1;
			gl.ZL_Src = gl.ZL_Top1;
			gl.X_Src = gl.Y_Src = 0.;
			gl.Z_Src = gl.Z_Top1;
		} else if (gl.SrcVolume == "Top2")
		{
			if(!gl.isTop2) G4Exception("SimourgMessenger::SetNewValue()","",FatalException,
        "\n\n\n### VolumeSrcCmd: Top2 is not defined!");
			gl.isSrcBox = 0;//gl.isTop2Box;
			gl.D_Src = gl.D_Top2;
			//gl.XL_Src = gl.XL_Top2;
			//gl.YL_Src = gl.YL_Top2;
			gl.ZL_Src = gl.ZL_Top2;
			gl.X_Src = gl.Y_Src = 0.;
			gl.Z_Src = gl.Z_Top2;
		} else if (gl.SrcVolume == "Top3")
		{
			if(!gl.isTop3) G4Exception("SimourgMessenger::SetNewValue()","",FatalException,
        "\n\n\n### VolumeSrcCmd: Top3 is not defined!");
			gl.isSrcBox = 0;//gl.isTop3Box;
			gl.D_Src = gl.D_Top3;
			//gl.XL_Src = gl.XL_Top3;
			//gl.YL_Src = gl.YL_Top3;
			gl.ZL_Src = gl.ZL_Top3;
			gl.X_Src = gl.Y_Src = 0.;
			gl.Z_Src = gl.Z_Top3;
		} else if (gl.SrcVolume == "Bot1")
		{
			if(!gl.isBot1) G4Exception("SimourgMessenger::SetNewValue()","",FatalException,
        "\n\n\n### VolumeSrcCmd: Bot1 is not defined!");
			gl.isSrcBox = 0;//gl.isBot1Box;
			gl.D_Src = gl.D_Bot1;
			//gl.XL_Src = gl.XL_Bot1;
			//gl.YL_Src = gl.YL_Bot1;
			gl.ZL_Src = gl.ZL_Bot1;
			gl.X_Src = gl.Y_Src = 0.;
			gl.Z_Src = gl.Z_Bot1;
		} else if (gl.SrcVolume == "Bot2")
		{
			if(!gl.isBot2) G4Exception("SimourgMessenger::SetNewValue()","",FatalException,
        "\n\n\n### VolumeSrcCmd: Bot2 is not defined!");
			gl.isSrcBox = 0;// gl.isBot2Box;
			gl.D_Src = gl.D_Bot2;
			//gl.XL_Src = gl.XL_Bot2;
			//gl.YL_Src = gl.YL_Bot2;
			gl.ZL_Src = gl.ZL_Bot2;
			gl.X_Src = gl.Y_Src = 0.;
			gl.Z_Src = gl.Z_Bot2;
		} else if (gl.SrcVolume == "Bot3")
		{
			if(!gl.isBot3) G4Exception("SimourgMessenger::SetNewValue()","",FatalException,
        "\n\n\n### VolumeSrcCmd: Bot3 is not defined!");
			gl.isSrcBox = 0;//gl.isBot3Box;
			gl.D_Src = gl.D_Bot3;
			//gl.XL_Src = gl.XL_Bot3;
			//gl.YL_Src = gl.YL_Bot3;
			gl.ZL_Src = gl.ZL_Bot3;
			gl.X_Src = gl.Y_Src = 0.;
			gl.Z_Src = gl.Z_Bot3;
		} else
		{
			G4Exception("SimourgMessenger::SetNewValue()","",FatalException,
        "\n\n\n### VolumeSrcCmd: unknown volume!");
		}

		if(gl.isSrcBox == 0)
		{
			gl.Src_Radius2 = (gl.D_Src*gl.D_Src)/4.; // Radius^2 of the source
		} else
		{
			gl.Src_Radius2 = (gl.XL_Src*gl.XL_Src + gl.YL_Src*gl.YL_Src)/4.; // Radius^2 of the source
		}
	}

  if( command == XL_SrcCmd || command == YL_SrcCmd || command == ZL_SrcCmd || 
      command == D_SrcCmd ||
      command == X_SrcCmd || command == Y_SrcCmd || command == Z_SrcCmd || command == VolumeSrcCmd) gl.isSrc=true;
  if( command == Detector_SrcCmd && Detector_SrcCmd->GetNewIntValue(newValue)==1)
      gl.DetectorsList.push_back("Src");//


  if( command == D_UnSrcCmd )
  {  
    gl.isUnSrcBox=0;
    gl.D_UnSrc=D_UnSrcCmd->GetNewDoubleValue(newValue);
    gl.UnSrc_Radius2 = (gl.D_UnSrc*gl.D_UnSrc)/4.; // Radius^2 of the UnSource
  }
  if( command == XL_UnSrcCmd )
  {
    gl.isUnSrcBox++;
    gl.XL_UnSrc=XL_UnSrcCmd->GetNewDoubleValue(newValue);
    if(gl.isUnSrcBox == 1) gl.YL_UnSrc = gl.XL_UnSrc;
    gl.UnSrc_Radius2 = (gl.XL_UnSrc*gl.XL_UnSrc + gl.YL_UnSrc*gl.YL_UnSrc)/4.; // Radius^2 of the UnSource
  }
  if( command == YL_UnSrcCmd )
  {
    gl.isUnSrcBox++;
    gl.YL_UnSrc=YL_UnSrcCmd->GetNewDoubleValue(newValue);
    if(gl.isUnSrcBox == 1) gl.XL_UnSrc = gl.YL_UnSrc;
    gl.UnSrc_Radius2 = (gl.XL_UnSrc*gl.XL_UnSrc + gl.YL_UnSrc*gl.YL_UnSrc)/4.; // Radius^2 of the UnSource
  }
  if( command == ZL_UnSrcCmd )
    gl.ZL_UnSrc=ZL_UnSrcCmd->GetNewDoubleValue(newValue);
  if( command == X_UnSrcCmd )
    gl.X_UnSrc=X_UnSrcCmd->GetNewDoubleValue(newValue);
  if( command == Y_UnSrcCmd )
    gl.Y_UnSrc=Y_UnSrcCmd->GetNewDoubleValue(newValue);
  if( command == Z_UnSrcCmd )
    gl.Z_UnSrc=Z_UnSrcCmd->GetNewDoubleValue(newValue);
	if( command == VolumeUnSrcCmd )
	{
		gl.UnSrcVolume = newValue;
		if(gl.UnSrcVolume == "SHLD")
		{
			G4Exception("SimourgMessenger::SetNewValue()","",FatalException,
        "\n\n\n### VolumeUnSrcCmd: UnSrc cannot be SHLD! UnSrc (if defined) should be inside Src.");
		} else if (gl.UnSrcVolume == "Cover2" || gl.UnSrcVolume == "Marinelli")
		{
			if(!gl.isCover2) G4Exception("SimourgMessenger::SetNewValue()","",FatalException,
        "\n\n\n### VolumeUnSrcCmd: Cover2/Marinelli is not defined!");
			gl.isUnSrcBox = gl.isCover2Box;
			gl.D_UnSrc = gl.D_Cover2;
			gl.XL_UnSrc = gl.XL_Cover2;
			gl.YL_UnSrc = gl.YL_Cover2;
			gl.ZL_UnSrc = gl.ZL_Cover2;
			gl.X_UnSrc = gl.Y_UnSrc = 0.;
			gl.Z_UnSrc = gl.Z_Cover2;
		} else if (gl.UnSrcVolume == "Cover1" || gl.UnSrcVolume == "Core")
		{
			if(!gl.isCover1) G4Exception("SimourgMessenger::SetNewValue()","",FatalException,
        "\n\n\n### VolumeUnSrcCmd: Cover1/Core is not defined!");
			gl.isUnSrcBox = gl.isCover1Box;
			gl.D_UnSrc = gl.D_Cover1;
			gl.XL_UnSrc = gl.XL_Cover1;
			gl.YL_UnSrc = gl.YL_Cover1;
			gl.ZL_UnSrc = gl.ZL_Cover1;
			gl.X_UnSrc = gl.Y_UnSrc = 0.;
			gl.Z_UnSrc = gl.Z_Cover1;
		} else if (gl.UnSrcVolume == "Det")
		{
			gl.isUnSrcBox = gl.isDetBox;
			gl.D_UnSrc = gl.D_Det;
			gl.XL_UnSrc = gl.XL_Det;
			gl.YL_UnSrc = gl.YL_Det;
			gl.ZL_UnSrc = gl.ZL_Det;
			gl.X_UnSrc = gl.Y_UnSrc = 0.;
			gl.Z_UnSrc = gl.Z_Det;
		} else if (gl.UnSrcVolume == "Cavity")
		{
			if(!gl.isCavity) G4Exception("SimourgMessenger::SetNewValue()","",FatalException,
        "\n\n\n### VolumeUnSrcCmd: Cavity is not defined!");
			gl.isUnSrcBox = gl.isCavityBox;
			gl.D_UnSrc = gl.D_Cavity;
			gl.XL_UnSrc = gl.XL_Cavity;
			gl.YL_UnSrc = gl.YL_Cavity;
			gl.ZL_UnSrc = gl.ZL_Cavity;
			gl.X_UnSrc = gl.Y_UnSrc = 0.;
			gl.Z_UnSrc = gl.Z_Cavity;
		} else if (gl.UnSrcVolume == "Top1")
		{
			if(!gl.isTop1) G4Exception("SimourgMessenger::SetNewValue()","",FatalException,
        "\n\n\n### VolumeUnSrcCmd: Top1 is not defined!");
			gl.isUnSrcBox = 0;//gl.isTop1Box;
			gl.D_UnSrc = gl.D_Top1;
			//gl.XL_UnSrc = gl.XL_Top1;
			//gl.YL_UnSrc = gl.YL_Top1;
			gl.ZL_UnSrc = gl.ZL_Top1;
			gl.X_UnSrc = gl.Y_UnSrc = 0.;
			gl.Z_UnSrc = gl.Z_Top1;
		} else if (gl.UnSrcVolume == "Top2")
		{
			if(!gl.isTop2) G4Exception("SimourgMessenger::SetNewValue()","",FatalException,
        "\n\n\n### VolumeUnSrcCmd: Top2 is not defined!");
			gl.isUnSrcBox = 0;//gl.isTop2Box;
			gl.D_UnSrc = gl.D_Top2;
			//gl.XL_UnSrc = gl.XL_Top2;
			//gl.YL_UnSrc = gl.YL_Top2;
			gl.ZL_UnSrc = gl.ZL_Top2;
			gl.X_UnSrc = gl.Y_UnSrc = 0.;
			gl.Z_UnSrc = gl.Z_Top2;
		} else if (gl.UnSrcVolume == "Top3")
		{
			if(!gl.isTop3) G4Exception("SimourgMessenger::SetNewValue()","",FatalException,
        "\n\n\n### VolumeUnSrcCmd: Top3 is not defined!");
			gl.isUnSrcBox = 0;//gl.isTop3Box;
			gl.D_UnSrc = gl.D_Top3;
			//gl.XL_UnSrc = gl.XL_Top3;
			//gl.YL_UnSrc = gl.YL_Top3;
			gl.ZL_UnSrc = gl.ZL_Top3;
			gl.X_UnSrc = gl.Y_UnSrc = 0.;
			gl.Z_UnSrc = gl.Z_Top3;
		} else if (gl.UnSrcVolume == "Bot1")
		{
			if(!gl.isBot1) G4Exception("SimourgMessenger::SetNewValue()","",FatalException,
        "\n\n\n### VolumeUnSrcCmd: Bot1 is not defined!");
			gl.isUnSrcBox = 0;//gl.isBot1Box;
			gl.D_UnSrc = gl.D_Bot1;
			//gl.XL_UnSrc = gl.XL_Bot1;
			//gl.YL_UnSrc = gl.YL_Bot1;
			gl.ZL_UnSrc = gl.ZL_Bot1;
			gl.X_UnSrc = gl.Y_UnSrc = 0.;
			gl.Z_UnSrc = gl.Z_Bot1;
		} else if (gl.UnSrcVolume == "Bot2")
		{
			if(!gl.isBot2) G4Exception("SimourgMessenger::SetNewValue()","",FatalException,
        "\n\n\n### VolumeUnSrcCmd: Bot2 is not defined!");
			gl.isUnSrcBox = 0;// gl.isBot2Box;
			gl.D_UnSrc = gl.D_Bot2;
			//gl.XL_UnSrc = gl.XL_Bot2;
			//gl.YL_UnSrc = gl.YL_Bot2;
			gl.ZL_UnSrc = gl.ZL_Bot2;
			gl.X_UnSrc = gl.Y_UnSrc = 0.;
			gl.Z_UnSrc = gl.Z_Bot2;
		} else if (gl.UnSrcVolume == "Bot3")
		{
			if(!gl.isBot3) G4Exception("SimourgMessenger::SetNewValue()","",FatalException,
        "\n\n\n### VolumeUnSrcCmd: Bot3 is not defined!");
			gl.isUnSrcBox = 0;//gl.isBot3Box;
			gl.D_UnSrc = gl.D_Bot3;
			//gl.XL_UnSrc = gl.XL_Bot3;
			//gl.YL_UnSrc = gl.YL_Bot3;
			gl.ZL_UnSrc = gl.ZL_Bot3;
			gl.X_UnSrc = gl.Y_UnSrc = 0.;
			gl.Z_UnSrc = gl.Z_Bot3;
		} else
		{
			G4Exception("SimourgMessenger::SetNewValue()","",FatalException,
        "\n\n\n### VolumeUnSrcCmd: unknown volume!");
		}

		if(gl.isUnSrcBox == 0)
		{
			gl.UnSrc_Radius2 = (gl.D_UnSrc*gl.D_UnSrc)/4.; // Radius^2 of the source
		} else
		{
			gl.UnSrc_Radius2 = (gl.XL_UnSrc*gl.XL_UnSrc + gl.YL_UnSrc*gl.YL_UnSrc)/4.; // Radius^2 of the source
		}
	}

  if( command == XL_UnSrcCmd || command == YL_UnSrcCmd || command == ZL_UnSrcCmd || 
      command == D_UnSrcCmd ||
      command == X_UnSrcCmd || command == Y_UnSrcCmd || command == Z_UnSrcCmd || command == VolumeUnSrcCmd ) gl.isUnSrc=true;

  if( command == Detector_UnSrcCmd && Detector_UnSrcCmd->GetNewIntValue(newValue)==1)
      gl.DetectorsList.push_back("UnSrc");//
//////////////////////

  if( command == EGammaCmd )
  {
    gl.EGamma=EGammaCmd->GetNewDoubleValue(newValue);
    gl.isEGamma=true;
  }
  if( command == FWHM1Cmd )
    gl.FWHM1=FWHM1Cmd->GetNewDoubleValue(newValue);
  if( command == FWHM2Cmd )
    gl.FWHM2=FWHM2Cmd->GetNewDoubleValue(newValue);
  if( command == FWHM1Cmd || command == FWHM2Cmd )
    gl.isBlur=true;

  if( command == AlphaBetaCmd )
    gl.AlphaBeta=AlphaBetaCmd->GetNewDoubleValue(newValue);

  if( command == ThresholdCmd )
    gl.Threshold=ThresholdCmd->GetNewDoubleValue(newValue);
  if( command == wrlFilesQuantityCmd )
    gl.wrlFilesQuantity=wrlFilesQuantityCmd->GetNewIntValue(newValue);
  if( command == SaveToCmd )
    gl.saveTo=SaveToCmd->GetNewIntValue(newValue);
  if( command == tMinCmd )
    gl.tMin=tMinCmd->GetNewDoubleValue(newValue)/1e9;
  if( command == tMaxCmd )
    gl.tMax=tMaxCmd->GetNewDoubleValue(newValue)/1e9;
  if( command == ELowLimitCmd )
    gl.ELowLimit=ELowLimitCmd->GetNewDoubleValue(newValue);
  if( command == DELowLimitCmd )
    gl.DELowLimit=DELowLimitCmd->GetNewDoubleValue(newValue);
  if( command == DGLowLimitCmd )
    gl.DGLowLimit=DGLowLimitCmd->GetNewDoubleValue(newValue);
  if( command == ChannelWidthCmd )
    gl.ChannelWidth=ChannelWidthCmd->GetNewDoubleValue(newValue);
  if( command == numberOfRunsCmd )
    gl.numberOfRuns=numberOfRunsCmd->GetNewIntValue(newValue);
  if( command == StepCmd )
    gl.Step=StepCmd->GetNewIntValue(newValue);
  if( command == RandomSeedCmd )
  {
    gl.RandomSeed=RandomSeedCmd->GetNewIntValue(newValue);
    CLHEP::HepRandom::setTheSeed(gl.RandomSeed);
  }
  if( command == WaitCommandCmd )
    gl.WaitCommand=WaitCommandCmd->GetNewIntValue(newValue);
  if( command == VerboseVisCmd )
    gl.VerboseVis=VerboseVisCmd->GetNewIntValue(newValue);
  if( command == VerboseAllCmd )
    gl.VerboseAll=VerboseAllCmd->GetNewIntValue(newValue);
  if( command == DoPictureCmd )
    gl.DoPicture=DoPictureCmd->GetNewIntValue(newValue);
  if( command == AllowIsotropicRotationCmd )
    gl.AllowIsotropicRotation=AllowIsotropicRotationCmd->GetNewIntValue(newValue);

  if( command == Decay0FileCmd )
  {  
    gl.Decay0FileName=newValue;
    gl.isDecay0=true;
    gl.in.open( gl.Decay0FileName );
    if(!gl.in)  {G4cerr << "### Failed to open file " << gl.Decay0FileName << G4endl; exit(1);}
  }

  if( command == PhysicsListCmd ) 
    gl.PhysicsList=newValue;

  if( command == showAllCmd )
  { 
    G4cout<<G4endl;
    G4cout<<"D_SHLD \t=\t"<<(gl.D_SHLD/mm)<<"\tmm"<<G4endl;
    G4cout<<"ZL_SHLD \t=\t"<<(gl.ZL_SHLD/mm)<<"\tmm"<<G4endl;  
    G4cout<<"MaterialSHLDDensity \t=\t"<<(gl.MaterialSHLDDensity/(g/cm3))<<"\tg/cm3"<<G4endl; 
    G4cout<<"MaterialSHLDFormula:\t";
    for(i = 0; i < (gl.MaterialSHLDNComponents); i++)
      G4cout << gl.MaterialSHLDElementNames[i] << " "
              << gl.MaterialSHLDFormulaN[i] << " ";
    G4cout<<G4endl;

    if(gl.isCover2Box>0)
    {
      G4cout<<"XL_Cover2 \t=\t"<<(gl.XL_Cover2/mm)<<"\tmm"<<G4endl; 
      G4cout<<"YL_Cover2 \t=\t"<<(gl.YL_Cover2/mm)<<"\tmm"<<G4endl; 
    } else
    {
      G4cout<<"D_Cover2 \t=\t"<<(gl.D_Cover2/mm)<<"\tmm"<<G4endl; 
    }
    G4cout<<"ZL_Cover2 \t=\t"<<(gl.ZL_Cover2/mm)<<"\tmm"<<G4endl;  
    G4cout<<"Z_Cover2 \t=\t"<<(gl.Z_Cover2/mm)<<"\tmm"<<G4endl;  
    G4cout<<"MaterialCover2Density \t=\t"<<(gl.MaterialCover2Density/(g/cm3))<<"\tg/cm3"<<G4endl; 
    G4cout<<"MaterialCover2Formula:\t";
    for(i = 0; i < (gl.MaterialCover2NComponents); i++)
        G4cout << gl.MaterialCover2ElementNames[i] << " "
              << gl.MaterialCover2FormulaN[i] << " ";
    G4cout<<G4endl;

    if(gl.isCover1Box>0)
    {
      G4cout<<"XL_Cover1 \t=\t"<<(gl.XL_Cover1/mm)<<"\tmm"<<G4endl; 
      G4cout<<"YL_Cover1 \t=\t"<<(gl.YL_Cover1/mm)<<"\tmm"<<G4endl; 
    } else
    {
      G4cout<<"D_Cover1 \t=\t"<<(gl.D_Cover1/mm)<<"\tmm"<<G4endl; 
    }
    G4cout<<"ZL_Cover1 \t=\t"<<(gl.ZL_Cover1/mm)<<"\tmm"<<G4endl;  
    G4cout<<"Z_Cover1 \t=\t"<<(gl.Z_Cover1/mm)<<"\tmm"<<G4endl;  
    G4cout<<"MaterialCover1Density \t=\t"<<(gl.MaterialCover1Density/(g/cm3))<<"\tg/cm3"<<G4endl; 
    G4cout<<"MaterialCover1Formula:\t";
    for(i = 0; i < (gl.MaterialCover1NComponents); i++)
        G4cout << gl.MaterialCover1ElementNames[i] << " "
              << gl.MaterialCover1FormulaN[i] << " ";
    G4cout<<G4endl;

    if(gl.isDetBox>0)
    {
      G4cout<<"XL_Det \t=\t"<<(gl.XL_Det/mm)<<"\tmm"<<G4endl; 
      G4cout<<"YL_Det \t=\t"<<(gl.YL_Det/mm)<<"\tmm"<<G4endl; 
    } else
    {
      G4cout<<"D_Det \t=\t"<<(gl.D_Det/mm)<<"\tmm"<<G4endl; 
    }
    G4cout<<"ZL_Det \t=\t"<<(gl.ZL_Det/mm)<<"\tmm"<<G4endl;  
    G4cout<<"Z_Det \t=\t"<<(gl.Z_Det/mm)<<"\tmm"<<G4endl;  
    G4cout<<"MaterialDetDensity \t=\t"<<(gl.MaterialDetDensity/(g/cm3))<<"\tg/cm3"<<G4endl; 
    G4cout<<"MaterialDetFormula:\t";
    for(i = 0; i < (gl.MaterialDetNComponents); i++)
        G4cout << gl.MaterialDetElementNames[i] << " "
              << gl.MaterialDetFormulaN[i] << " ";
    G4cout<<G4endl;

    if(gl.isCavity)
    {
      G4cout<<"isCavity \t=\t"<< gl.isCavity <<G4endl;  
      G4cout<<"D_Cavity \t=\t"<<(gl.D_Cavity/mm)<<"\tmm"<<G4endl;  
      G4cout<<"ZL_Cavity \t=\t"<<(gl.ZL_Cavity/mm)<<"\tmm"<<G4endl;  
      G4cout<<"Z_Cavity \t=\t"<<(gl.Z_Cavity/mm)<<"\tmm"<<G4endl;  
      G4cout<<"MaterialCavityDensity \t=\t"<<(gl.MaterialCavityDensity/(g/cm3))<<"\tg/cm3"<<G4endl; 
      G4cout<<"MaterialCavityFormula:\t";
      for(i = 0; i < (gl.MaterialCavityNComponents); i++)
          G4cout << gl.MaterialCavityElementNames[i] << " "
                << gl.MaterialCavityFormulaN[i] << " ";
      G4cout<<G4endl;
    }

    if(gl.isTop1)
    {
      G4cout<<"isTop1 \t=\t"<< gl.isTop1 <<G4endl;  
      G4cout<<"D_Top1 \t=\t"<<(gl.D_Top1/mm)<<"\tmm"<<G4endl;  
      G4cout<<"ZL_Top1 \t=\t"<<(gl.ZL_Top1/mm)<<"\tmm"<<G4endl;  
      G4cout<<"Z_Top1 \t=\t"<<(gl.Z_Top1/mm)<<"\tmm"<<G4endl;  
      G4cout<<"MaterialTop1Density \t=\t"<<(gl.MaterialTop1Density/(g/cm3))<<"\tg/cm3"<<G4endl; 
      G4cout<<"MaterialTop1Formula:\t";
      for(i = 0; i < (gl.MaterialTop1NComponents); i++)
          G4cout << gl.MaterialTop1ElementNames[i] << " "
                << gl.MaterialTop1FormulaN[i] << " ";
      G4cout<<G4endl;
    }

    if(gl.isTop2)
    {
      G4cout<<"isTop2 \t=\t"<< gl.isTop2 <<G4endl;  
      G4cout<<"D_Top2 \t=\t"<<(gl.D_Top2/mm)<<"\tmm"<<G4endl;  
      G4cout<<"ZL_Top2 \t=\t"<<(gl.ZL_Top2/mm)<<"\tmm"<<G4endl;  
      G4cout<<"Z_Top2 \t=\t"<<(gl.Z_Top2/mm)<<"\tmm"<<G4endl;  
      G4cout<<"MaterialTop2Density \t=\t"<<(gl.MaterialTop2Density/(g/cm3))<<"\tg/cm3"<<G4endl; 
      G4cout<<"MaterialTop2Formula:\t";
      for(i = 0; i < (gl.MaterialTop2NComponents); i++)
          G4cout << gl.MaterialTop2ElementNames[i] << " "
                << gl.MaterialTop2FormulaN[i] << " ";
      G4cout<<G4endl;
    }

    if(gl.isTop3)
    {
      G4cout<<"isTop3 \t=\t"<< gl.isTop3 <<G4endl;  
      G4cout<<"D_Top3 \t=\t"<<(gl.D_Top3/mm)<<"\tmm"<<G4endl;  
      G4cout<<"ZL_Top3 \t=\t"<<(gl.ZL_Top3/mm)<<"\tmm"<<G4endl;  
      G4cout<<"Z_Top3 \t=\t"<<(gl.Z_Top3/mm)<<"\tmm"<<G4endl;  
      G4cout<<"MaterialTop3Density \t=\t"<<(gl.MaterialTop3Density/(g/cm3))<<"\tg/cm3"<<G4endl; 
      G4cout<<"MaterialTop3Formula:\t";
      for(i = 0; i < (gl.MaterialTop3NComponents); i++)
          G4cout << gl.MaterialTop3ElementNames[i] << " "
                << gl.MaterialTop3FormulaN[i] << " ";
      G4cout<<G4endl;
    }

    if(gl.isBot1)
    {
      G4cout<<"isBot1 \t=\t"<< gl.isBot1 <<G4endl;  
      G4cout<<"D_Bot1 \t=\t"<<(gl.D_Bot1/mm)<<"\tmm"<<G4endl;  
      G4cout<<"ZL_Bot1 \t=\t"<<(gl.ZL_Bot1/mm)<<"\tmm"<<G4endl;  
      G4cout<<"Z_Bot1 \t=\t"<<(gl.Z_Bot1/mm)<<"\tmm"<<G4endl;  
      G4cout<<"MaterialBot1Density \t=\t"<<(gl.MaterialBot1Density/(g/cm3))<<"\tg/cm3"<<G4endl; 
      G4cout<<"MaterialBot1Formula:\t";
      for(i = 0; i < (gl.MaterialBot1NComponents); i++)
          G4cout << gl.MaterialBot1ElementNames[i] << " "
                << gl.MaterialBot1FormulaN[i] << " ";
      G4cout<<G4endl;
    }

    if(gl.isBot2)
    {
      G4cout<<"isBot2 \t=\t"<< gl.isBot2 <<G4endl;  
      G4cout<<"D_Bot2 \t=\t"<<(gl.D_Bot2/mm)<<"\tmm"<<G4endl;  
      G4cout<<"ZL_Bot2 \t=\t"<<(gl.ZL_Bot2/mm)<<"\tmm"<<G4endl;  
      G4cout<<"Z_Bot2 \t=\t"<<(gl.Z_Bot2/mm)<<"\tmm"<<G4endl;  
      G4cout<<"MaterialBot2Density \t=\t"<<(gl.MaterialBot2Density/(g/cm3))<<"\tg/cm3"<<G4endl; 
      G4cout<<"MaterialBot2Formula:\t";
      for(i = 0; i < (gl.MaterialBot2NComponents); i++)
          G4cout << gl.MaterialBot2ElementNames[i] << " "
                << gl.MaterialBot2FormulaN[i] << " ";
      G4cout<<G4endl;
    }

    if(gl.isBot3)
    {
      G4cout<<"isBot3 \t=\t"<< gl.isBot3 <<G4endl;  
      G4cout<<"D_Bot3 \t=\t"<<(gl.D_Bot3/mm)<<"\tmm"<<G4endl;  
      G4cout<<"ZL_Bot3 \t=\t"<<(gl.ZL_Bot3/mm)<<"\tmm"<<G4endl;  
      G4cout<<"Z_Bot3 \t=\t"<<(gl.Z_Bot3/mm)<<"\tmm"<<G4endl;  
      G4cout<<"MaterialBot3Density \t=\t"<<(gl.MaterialBot3Density/(g/cm3))<<"\tg/cm3"<<G4endl; 
      G4cout<<"MaterialBot3Formula:\t";
      for(i = 0; i < (gl.MaterialBot3NComponents); i++)
          G4cout << gl.MaterialBot3ElementNames[i] << " "
                << gl.MaterialBot3FormulaN[i] << " ";
      G4cout<<G4endl;
    }

    if(gl.isSrcBox>0)
    {
      G4cout<<"XL_Src \t=\t"<<(gl.XL_Src/mm)<<"\tmm"<<G4endl; 
      G4cout<<"YL_Src \t=\t"<<(gl.YL_Src/mm)<<"\tmm"<<G4endl; 
    } else
    {
      G4cout<<"D_Src \t=\t"<<(gl.D_Src/mm)<<"\tmm"<<G4endl; 
    }
    G4cout<<"ZL_Src \t=\t"<<(gl.ZL_Src/mm)<<"\tmm"<<G4endl;  
    G4cout<<"X_Src \t=\t"<<(gl.X_Src/mm)<<"\tmm"<<G4endl;  
    G4cout<<"Y_Src \t=\t"<<(gl.Y_Src/mm)<<"\tmm"<<G4endl;  
    G4cout<<"Z_Src \t=\t"<<(gl.Z_Src/mm)<<"\tmm"<<G4endl;  
		if(gl.SrcVolume!="") G4cout << "Src is equal to " << gl.SrcVolume <<G4endl;


    if(gl.isUnSrc)
    {
	    if(gl.isUnSrcBox>0)
		  {
			  G4cout<<"XL_UnSrc \t=\t"<<(gl.XL_UnSrc/mm)<<"\tmm"<<G4endl; 
				G4cout<<"YL_UnSrc \t=\t"<<(gl.YL_UnSrc/mm)<<"\tmm"<<G4endl; 
	    } else
		  {
			  G4cout<<"D_UnSrc \t=\t"<<(gl.D_UnSrc/mm)<<"\tmm"<<G4endl; 
	    }
		  G4cout<<"ZL_UnSrc \t=\t"<<(gl.ZL_UnSrc/mm)<<"\tmm"<<G4endl;  
			G4cout<<"X_UnSrc \t=\t"<<(gl.X_UnSrc/mm)<<"\tmm"<<G4endl;  
	    G4cout<<"Y_UnSrc \t=\t"<<(gl.Y_UnSrc/mm)<<"\tmm"<<G4endl;  
		  G4cout<<"Z_UnSrc \t=\t"<<(gl.Z_UnSrc/mm)<<"\tmm"<<G4endl;  
			if(gl.UnSrcVolume!="") G4cout << "UnSrc is equal to " << gl.UnSrcVolume <<G4endl;
		}

    if(gl.isEGamma)
    {
      G4cout<<"EGamma \t=\t"<<(gl.EGamma/keV)<<"\tkeV"<<G4endl;
    }
    G4cout<<"FWHM1 \t=\t"<<(gl.FWHM1)<<"\tkeV^2"<<G4endl;
    G4cout<<"FWHM2 \t=\t"<<(gl.FWHM2)<<"\tkeV"<<G4endl;
    G4cout<<"AlphaBeta \t=\t"<<(gl.AlphaBeta)<<G4endl;

    G4cout<<"Threshold =\t"<<(gl.Threshold/keV)<<"\tkeV"<<G4endl;
    G4cout<<"tMin =\t"<<(gl.tMin/s)<<"\ts"<<G4endl;
    G4cout<<"tMax =\t"<<(gl.tMax/s)<<"\ts"<<G4endl;
    G4cout<<"ELowLimit \t=\t"<<(gl.ELowLimit/keV)<<"\tkeV"<<G4endl;  
    G4cout<<"DELowLimit \t=\t"<<(gl.DELowLimit/nm)<<"\tnm"<<G4endl;
    G4cout<<"DGLowLimit \t=\t"<<(gl.DGLowLimit/nm)<<"\tnm"<<G4endl;
    G4cout<<"ChannelWidth\t=\t"<<(gl.ChannelWidth/keV)<<"\tkeV"<<G4endl;
    G4cout<<"numberOfRuns \t=\t"<<(gl.numberOfRuns)<<G4endl;
    G4cout<<"Step \t\t=\t"<<(gl.Step)<<G4endl;
    G4cout<<"RandomSeed \t=\t"<<(gl.RandomSeed)<<G4endl;
    G4cout<<"WaitCommand \t=\t"<<(gl.WaitCommand)<<G4endl;
    G4cout<<"VerboseVis \t=\t"<<(gl.VerboseVis)<<G4endl;
    G4cout<<"VerboseAll \t=\t"<<(gl.VerboseAll)<<G4endl;
    G4cout<<"DoPicture \t=\t"<<(gl.DoPicture)<<G4endl;
    G4cout<<"AllowIsotropicRotation \t=\t"<<(gl.AllowIsotropicRotation)<<G4endl;

    if(gl.isDecay0)
    {
      G4cout<<"isDecay0 \t=\t"<< gl.isDecay0 <<G4endl;  
      G4cout<<"Decay0FileName:\t";
      G4cout<<gl.Decay0FileName<<G4endl;
    }
    G4cout<<"PhysicsList:\t"<<gl.PhysicsList<<G4endl;


  }

  if( command == initCmd || command == resetCmd)
  { // reset all values to initial
    gl.iFlag=0;
    gl.isDetBox = 0;
    gl.isCover2Box = 0;
    gl.isCover1Box = 0;
    gl.isSrcBox = 0;
    gl.isUnSrcBox = 0;

    gl.isSHLD=false;// Do the mandatory volumes exist? Default -- false.
    gl.isDet=false;
    gl.isSrc=false;
    gl.isUnSrc=false;
    gl.isCover2=false;// Do the optional volumes exist? Default -- false.
    gl.isCover1=false;//
		gl.isCavity=false;//
    gl.isTop1=false;//
    gl.isTop2=false;//
    gl.isTop3=false;//
    gl.isBot1=false;//
    gl.isBot2=false;//
    gl.isBot3=false;//
		gl.isBlur = false;

    gl.MaterialSHLDDensity = 1.e-10*g/cm3;
    gl.MaterialSHLDElementNames[0] = "N";
    gl.MaterialSHLDFormulaN[0] = 1;
    gl.MaterialSHLDNComponents = 0;
    gl.MaterialDetDensity = 1.e-10*g/cm3;
    gl.MaterialDetElementNames[0] = "N";
    gl.MaterialDetFormulaN[0] = 1;
    gl.MaterialDetNComponents = 0;
    gl.D_Cavity = 0.001*mm;
    gl.ZL_Cavity = 0.001*mm;
    gl.MaterialCavityDensity = 1.e-10*g/cm3;
    gl.MaterialCavityElementNames[0] = "N";
    gl.MaterialCavityFormulaN[0] = 1;
    gl.MaterialCavityNComponents = 0;
    gl.D_Cover2 = 0.000*mm;
    gl.ZL_Cover2 = 0.000*mm;
    gl.MaterialCover2Density = 1.e-10*g/cm3;
    gl.MaterialCover2ElementNames[0] = "N";
    gl.MaterialCover2FormulaN[0] = 1;
    gl.MaterialCover2NComponents = 0;
		gl.D_Cover1 = 0.000*mm;
    gl.ZL_Cover1 = 0.000*mm;
    gl.MaterialCover1Density = 1.e-10*g/cm3;
    gl.MaterialCover1ElementNames[0] = "N";
    gl.MaterialCover1FormulaN[0] = 1;
    gl.MaterialCover1NComponents = 0;
    gl.D_Top1 = 0.001*mm;
    gl.ZL_Top1 = 0.001*mm;
    gl.MaterialTop1Density = 1.e-10*g/cm3;
    gl.MaterialTop1ElementNames[0] = "N";
    gl.MaterialTop1FormulaN[0] = 1;
    gl.MaterialTop1NComponents = 0;
    gl.D_Top2 = 0.001*mm;
    gl.ZL_Top2 = 0.001*mm;
    gl.MaterialTop2Density = 1.e-10*g/cm3;
    gl.MaterialTop2ElementNames[0] = "N";
    gl.MaterialTop2FormulaN[0] = 1;
    gl.MaterialTop2NComponents = 0;
    gl.D_Top3 = 0.001*mm;
    gl.ZL_Top3 = 0.001*mm;
    gl.MaterialTop3Density = 1.e-10*g/cm3;
    gl.MaterialTop3ElementNames[0] = "N";
    gl.MaterialTop3FormulaN[0] = 1;
    gl.MaterialTop3NComponents = 0;
    gl.D_Bot1 = 0.001*mm;
    gl.ZL_Bot1 = 0.001*mm;
    gl.MaterialBot1Density = 1.e-10*g/cm3;
    gl.MaterialBot1ElementNames[0] = "N";
    gl.MaterialBot1FormulaN[0] = 1;
    gl.MaterialBot1NComponents = 0;
    gl.D_Bot2 = 0.001*mm;
    gl.ZL_Bot2 = 0.001*mm;
    gl.MaterialBot2Density = 1.e-10*g/cm3;
    gl.MaterialBot2ElementNames[0] = "N";
    gl.MaterialBot2FormulaN[0] = 1;
    gl.MaterialBot2NComponents = 0;
    gl.D_Bot3 = 0.001*mm;
    gl.ZL_Bot3 = 0.001*mm;
    gl.MaterialBot3Density = 1.e-10*g/cm3;
    gl.MaterialBot3ElementNames[0] = "N";
    // gl.MaterialBot3FormulaN[0] = 1;
    gl.MaterialBot3NComponents = 0;

    gl.X_Src = 0;
    gl.Y_Src = 0;
    gl.X_UnSrc = 0;
    gl.Y_UnSrc = 0;
  }
} //end of SimourgMessenger::SetNewValue()

