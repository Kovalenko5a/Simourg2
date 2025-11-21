# Simourg 2.0 – GEANT4 APPLICATION FOR SIMULATION OF NUCLEAR DETECTORS WITH SIMPLE GEOMETRIES


Simourg 2.0 is a GEANT4-based Monte Carlo framework for simulating radiation detectors, shielding structures, and source configurations.
The simulation workflow is fully macro-driven, with a strong focus on detector response modeling.

## Requirements

Simourg requires a GEANT4 installation compiled with data libraries, Qt support, and OpenGL visualization.
Example CMake flags for GEANT4:

-DGEANT4_INSTALL_DATA=ON<br>
-DGEANT4_USE_QT=ON<br>
-DGEANT4_USE_OPENGL_X11=ON<br>


## Installation

To install Simourg, compile the source code:

git clone https://github.com/YOUR_REPO/Simourg.git<br>
cd Simourg<br>
mkdir build<br>
cd build<br>
cmake ..<br>
make -j4<br>

This will generate the executable file Simourg

## Running a Simulation

Run Simourg with a macro file:

./Simourg YOUR_SETUP_FILE.mac

Macro files define geometry, materials, source configuration, readout parameters, visualization options, and output formats. Examples are included with the source code, and all /user/* commands can be viewed in the Qt interface.

# Simourg 2.0 - Geometry Definition Command refference

Simourg 2.0 defines detector geometry entirely through `/user/*` macro commands.  
Each volume supports dimensions, position, rotation, material definition, and detector flags.


## Supported Volume Types and Allowed Shapes

- **Det** — cylinder **or** parallelepiped  
- **Src** — cylinder **or** parallelepiped  
- **UnSrc** — cylinder **or** parallelepiped  
- **Cover1** — cylinder **or** parallelepiped  
- **Cover2** — cylinder **or** parallelepiped  

- **SHLD** — **cylinder only**  
- **Cavity** — **cylinder only**  

Volumes supporting **rings** (outer + inner radius):
- **Top1** — ring cylinder (R_out + R_in)  
- **Top2** — ring cylinder (R_out + R_in)  
- **Top3** — ring cylinder (R_out + R_in)  
- **Bot1** — ring cylinder (R_out + R_in)  
- **Bot2** — ring cylinder (R_out + R_in)  
- **Bot3** — ring cylinder (R_out + R_in)

## Detector Volume Example

### Dimensions
/user/D_Det — Diameter of cylindrical detector volume  
/user/XL_Det — X size of prism detector  
/user/YL_Det — Y size of prism detector  
/user/ZL_Det — Z size ( or cylindr height) of detector volume  

### Position
/user/X_Det — X coordinate of detector center  
/user/Y_Det — Y coordinate of detector center  
/user/Z_Det — Z coordinate of detector center  

### Rotation
/user/Rot_Det X Y Z — Rotation angles (deg) around X, Y, Z  

## Cavity Volume Example

### Detector Flag
/user/isCavityaDetector — Define whether cavity is treated as a detector (0/1)

### Dimensions
/user/D_Cavity — Diameter of cavity volume  
/user/ZL_Cavity — Z size (height) of cavity  

### Position
/user/X_Cavity — X coordinate of cavity center  
/user/Y_Cavity — Y coordinate of cavity center  
/user/Z_Cavity — Z coordinate of cavity center  

### Rotation
/user/Rot_Cavity X Y Z — Rotation angles (deg)  

## Material Definition Methods

Simourg supports two independent ways to define material composition for any volume:  
(1) by atomic formula (element + number of atoms), and  
(2) by weight fractions (element + mass weight).

Both methods start with a density definition.

### Density
/user/MaterialCavityDensity — Density of cavity material  

---

### 1) Material Definition by Atomic Formula

This method specifies each element and the number of atoms in the chemical formula.

#### Commands
/user/MaterialCavityElementName — Chemical element name  
/user/MaterialCavityFormulaNum — Number of atoms of last element  

#### Example: Defining WO₃  
```
/user/MaterialCavityDensity 7.16 g/cm3
/user/MaterialCavityElementName W
/user/MaterialCavityFormulaNum 1
/user/MaterialCavityElementName O
/user/MaterialCavityFormulaNum 3
```

#### Example: Defining CdWO₄  
```
/user/MaterialCavityDensity 8.0 g/cm3
/user/MaterialCavityElementName Cd
/user/MaterialCavityFormulaNum 1
/user/MaterialCavityElementName W
/user/MaterialCavityFormulaNum 1
/user/MaterialCavityElementName O
/user/MaterialCavityFormulaNum 4
```

---

### 2) Material Definition by Weight Fractions

This method specifies the material as a mixture of chemical elements with associated weights.

#### Command
/user/MaterialCavityWeight — List of element–weight pairs  

#### Example: Bronze-like mixture  
```
/user/MaterialCavityDensity 8.7 g/cm3
/user/MaterialCavityWeight Cu 900 Sn 100
```

#### Example: Multi-element mixture  
```
/user/MaterialCavityDensity 10 g/cm3
/user/MaterialCavityWeight Cd 1000 W 100 O 10
```

---

You may use **either** atomic formulas **or** weight fractions to define material composition for any Simourg volume.

# Simourg 2.0 — General Command Reference

This section lists all available `/user/*` commands and their meanings, based directly on their internal GEANT4 `SetGuidance()` descriptions.

---

## General Commands

### `/user/showAll`
Show all current parameter values.

### `/user/init`
Initialize the detector.

### `/user/reset`
Reset and re-initialize the detector.

---

## Output & File Handling

### `/user/saveTo <0|1|2>`
Save unprocessed output in one of three formats:  
- **0** — ROOT ntuple  
- **1** — CSV ntuple  
- **2** — CSV columns  

### `/user/wrlFilesQuantity <N>`
Number of **VRML (.wrl)** geometry files to save.

---

## Energy Cuts, Detector Resolution & Spectrum
Along with raw energy deposition data you will have detected spectrum in accordanse to resolution 

### `/user/ChannelWidth <value> [unit]`
Width of one channel in the output spectrum.

### `/user/FWHM1 <value>`
Detector resolution term:  
`FWHM[keV] = sqrt( FWHM1[keV²] + FWHM2[keV] * Eγ[keV] )`

### `/user/FWHM2 <value>`
Second detector resolution coefficient used in the formula above.

### `/user/AlphaBeta <value>`
For beta and gamma:
`E_observed = E_released`

For alpha you can apply energy scaling factor:  
`E_observed = E_released * AlphaBeta`  
Typically `< 1`.


### `/user/Threshold <value> [unit]`
Detector energy threshold.

---

## Time Window

### `/user/tMin <value> [unit]`
Minimal time of particle emission relative to event start (time moment when detector is triggered).

### `/user/tMax <value> [unit]`
Maximal time of particle emission relative to event start (time moment when detector time window is closing).

---

## Low-Energy & Step Limits

### `/user/ELowLimit <value> [unit]`
Lower cut for particle energy (global).

### `/user/DELowLimit <value> [unit]`
Lower cut for **electron/positron** distance step.

### `/user/DGLowLimit <value> [unit]`
Lower cut for **gamma** distance step.

---

## Run Control

### `/user/numberOfRuns <N>`
Number of runs (1 run = 1 decay vertex generated).

### `/user/Step <N>`
Print progress every *N* runs.

### `/user/RandomSeed <N>`
Set the random number generator seed.

### `/user/WaitCommand <0|1>`
Wait for an external command (1) or proceed immediately (0).

---

## Verbosity & Visualization

### `/user/VerboseVis <0–6>`
Verbosity level of visualization.

### `/user/VerboseAll <0–6>`
Verbosity level for all other outputs.

### `/user/DoPicture <0|1|2>`
Select visualization mode:  
- **0** — No visualization  
- **1** — Save VRML files  
- **2** — OpenGL viewer

---

## Rotation Options

### `/user/AllowIsotropicRotation <0|1>`
Allow random isotropic rotation of initial kinematics vertex (1 = yes).

---

## Physics

### `/user/PhysicsList <name>`
Select physics list.  
Supports GEANT4 lists such as:  
`FTFP_BERT`, `QGSP_BIC`, `Shielding`, `FTFP_BERT_LIV`, etc., and their EM extensions (`_EMV`, `_EMX`, `_LIV`, `_PEN`, etc.).

---

## Source & Decay
### `/user/EGamma <value> [unit]`
Particle energy.

### `/user/Decay0File <path>`
Specify Decay0 input file for radioactive decay simulation.

---

Notes
* Keep geometry parameters grouped separately to avoid confusion.
* tMin and tMax define the detector readout window relative to the trigger (time moment of first energy deposition).
* DoPicture controls visualization mode; saveTo selects output format.
* Materials may be defined by atomic numbers or weight fractions.
* Explore /user/* commands in the Qt interface for additional options.
