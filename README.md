# Simourg 2.0 – GEANT4 APPLICATION FOR SIMULATION OF NUCLEAR DETECTORS WITH SIMPLE GEOMETRIES


Simourg 2.0 is a GEANT4-based Monte Carlo framework for simulating radiation detectors, shielding structures, and source configurations.
The simulation workflow is fully macro-driven, similar to GAMOS, but with a stronger focus on detector response modeling.

## Requirements

Simourg requires a GEANT4 installation compiled with data libraries, Qt support, and OpenGL visualization.
Example CMake flags for GEANT4:

-DGEANT4_INSTALL_DATA=ON
-DGEANT4_USE_QT=ON
-DGEANT4_USE_OPENGL_X11=ON

## Installation

To install Simourg, compile the source code like a GEANT4 basic example:

git clone https://github.com/YOUR_REPO/Simourg.git
cd Simourg
mkdir build
cd build
cmake ..
make -j4

This will generate the executable file Simourg.exe. More installation details are in the repository.

## Running a Simulation

Run Simourg with a macro file:

./Simourg.exe YOUR_SETUP_FILE.mac

Macro files define geometry, materials, source configuration, readout parameters, visualization options, and output formats. Examples are included in the source code, and all /user/* commands can be viewed in the Qt interface.

## Macro File Structure

### General Commands

/user/init
/user/showAll

### Geometry Blocks

Define each volume with dimensions, position, rotation, material, and detector flag:

/user/XL_Det 50 mm
/user/YL_Det 50 mm
/user/ZL_Det 50 mm
/user/Z_Det 0 mm
/user/isDetDetector 1

### Material Definition

Element-based formula

/user/MaterialDetDensity 8.0 g/cm3
/user/MaterialDetElementName Cd
/user/MaterialDetFormulaNum 1
/user/MaterialDetElementName W
/user/MaterialDetFormulaNum 1
/user/MaterialDetElementName O
/user/MaterialDetFormulaNum 4

Weight fractions

/user/MaterialTop1Density 10 g/cm3
/user/MaterialTop1Weight Cu 100 F 10 Cs 123.2

### Source and UnSource Volumes

Source volume

/user/XL_Src 1 mm
/user/YL_Src 1 mm
/user/ZL_Src 1 mm
/user/X_Src 0 mm
/user/Y_Src 0 mm
/user/Z_Src 35 mm

UnSource volume

/user/D_UnSrc 1 mm
/user/X_UnSrc 1 mm
/user/Y_UnSrc 0 mm
/user/Z_UnSrc 35 mm

### Decay file

/user/Decay0File C:/path/to/Tl208.dat

### Run and Readout Parameters

/user/Threshold 1 keV
/user/FWHM1 0.0
/user/FWHM2 1.0
/user/ELowLimit 1 keV
/user/ChannelWidth 10 keV
/user/numberOfRuns 10000
/user/Step 100
/user/RandomSeed 90115037

### Readout time window

/user/tMin 0.0 s
/user/tMax 300000 s

### Visualization

/user/DoPicture 0  # 0=no picture, 1=VRML, 2=OpenGL
/user/wrlFilesQuantity 100

### Rotation Options

/user/AllowIsotropicRotation 1  # enable random isotropic rotation
/user/Rot_Top1 30 80 30        # example fixed rotation

### Output Format

/user/saveTo 0  # 0=ROOT, 1=CSV, 2=TXT (headers in ShourtLog.txt)

### Verbosity and Interactive Options

/user/VerboseVis 0   # visualization verbosity 0-6
/user/VerboseAll 0   # general verbosity 0-6
/user/WaitCommand 0  # wait for command 0/1

### Physics List

/user/PhysicsList FTFP_BERT_LIV

Available physics lists include CHIPS, FTFP_BERT, FTFP_BERT_TRV, FTFP_BERT_HP, FTF_BIC, LBE, LHEP, QBBC, QGSC_BERT, QGSP_BERT, QGSP_BERT_CHIPS, QGSP_BERT_HP, QGSP_BIC, QGSP_BIC_HP, QGSP_FTFP_BERT, QGS_BIC, QGSP_INCLXX, Shielding, ShieldingLEND, and EM variants (_EMV, _EMX, _EMY, _EMZ, _LIV, _PEN).


Notes
	•	Keep geometry parameters grouped separately to avoid confusion.
	•	tMin and tMax define the detector readout window relative to the trigger (time moment of first energy deposition).
	•	DoPicture controls visualization mode; saveTo selects output format.
	•	Materials may be defined by atomic numbers or weight fractions.
	•	Explore /user/* commands in the Qt interface for additional options.
