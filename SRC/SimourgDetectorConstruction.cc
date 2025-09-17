#include <numeric>

#include "G4Element.hh"
#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4MaterialPropertiesTable.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"

#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"

#ifdef G4VIS_USE
#  include "G4VisManager.hh"
#endif

#include "globals.hh"

#include "SimourgSensDet.h"
#include "SimourgDetectorConstruction.h"
#include "SimourgGlobal.h"

extern SimourgGlobal gl;

SimourgDetectorConstruction::SimourgDetectorConstruction()
{
  gl.TimeStampDetConstr = "Executing " __FILE__ " (compiled " __DATE__ " " __TIME__ ")";
  std::map<G4String, G4LogicalVolume*> logicalVolumeMap;

}

SimourgDetectorConstruction::~SimourgDetectorConstruction()
{;}

G4VPhysicalVolume* SimourgDetectorConstruction::Construct()
{
G4RotationMatrix* rotation = new G4RotationMatrix();
  G4cout << "### Material construction started " << G4endl;

//------------------------------------------------------ materials

  G4double a;  // atomic mass
  G4double z;  // atomic number
  G4double density;
  G4String name, symbol;
  G4int ncomponents, natoms;
  G4double fractionmass;
	G4int i;
	G4NistManager* NIST = G4NistManager::Instance();


  G4cout << "### Chemical elements created " << G4endl;

//   G4Material* MaterialSHLD = new G4Material(name="MaterialSHLD", 
// 		density=gl.MaterialSHLDDensity, ncomponents=gl.MaterialSHLDNComponents);
// 	for(i=0; i < ncomponents; i++)
// 	{

// 		MaterialSHLD->AddElement( NIST->FindOrBuildElement(gl.MaterialSHLDElementNames[i], true), 
// 		natoms=gl.MaterialSHLDFormulaN[i]);
// 	}
// 	if(gl.VerboseAll > 0)
// 		G4cout << "### MaterialSHLD created with " << ncomponents << " components"  << G4endl;


///////////////SHLD Material Init
	G4Material* MaterialSHLD = new G4Material(name="MaterialSHLD", 
		density=(gl.isSHLD ? gl.MaterialSHLDDensity : 1.0*g/cm3 ), 
		ncomponents=(gl.MaterialSHLDNComponents!=0 ? gl.MaterialSHLDNComponents : 
		 !gl.SHLDElementSolution.empty()?  gl.SHLDElementSolution.size():1));
	if(gl.MaterialSHLDNComponents!=0){
	for(i=0; i < ncomponents; i++)
	{
		MaterialSHLD->AddElement( NIST->FindOrBuildElement(gl.MaterialSHLDElementNames[i], true), 
			natoms=gl.MaterialSHLDFormulaN[i]);
	}
	if(gl.VerboseAll > 0) {G4cout << "### MaterialSHLD created with " << ncomponents << " atomic components"  << G4endl;
			const G4ElementVector* elems = MaterialSHLD->GetElementVector();
			const G4int* fracs = MaterialSHLD->GetAtomsVector();
			for (G4int i=0; i<MaterialSHLD->GetNumberOfElements(); ++i) {
    		std::cout << "  " << (*elems)[i]->GetName()
              << " Z=" << (*elems)[i]->GetZ()
              << ", Atoms =" << fracs[i] << "\n";
			}
		}
	
	}
	else if(!gl.SHLDElementSolution.empty()){
	G4cout << "Parsed MaterialSHLDWeight values:\n";
	double sum = std::accumulate(
        gl.SHLDElementSolution.begin(), gl.SHLDElementSolution.end(), 0.0,
        [](double total, const std::pair<const std::string, double>& p){
            return total + p.second;
        }
    );
	for (const auto& entry : gl.SHLDElementSolution) 
	{
  		G4cout << "\tElement: " << entry.first << ", Weight: " << entry.second << G4endl;
		MaterialSHLD->AddElement( NIST->FindOrBuildElement(entry.first, true), 
		entry.second/sum);
	}
	if(gl.VerboseAll > 0) {G4cout << "### MaterialSHLD created with " << ncomponents << " mass components"  << G4endl;
		const G4ElementVector* elems = MaterialSHLD->GetElementVector();
		const G4double* fracs = MaterialSHLD->GetFractionVector();
		for (G4int i=0; i<MaterialSHLD->GetNumberOfElements(); ++i) {
    		std::cout << "  " << (*elems)[i]->GetName()
              << " Z=" << (*elems)[i]->GetZ()
              << ", fractionMass=" << fracs[i] << "\n";
			}
		}
	}
///////////////SHLD Material Fin

//   G4Material* MaterialCover2 = new G4Material(name="MaterialCover2", 
// 		density=gl.MaterialCover2Density, ncomponents=gl.MaterialCover2NComponents);
// 	for(i=0; i < ncomponents; i++)
// 	{
// 		MaterialCover2->AddElement( NIST->FindOrBuildElement(gl.MaterialCover2ElementNames[i], true), 
// 			natoms=gl.MaterialCover2FormulaN[i]);
// 	}
//   if(gl.VerboseAll > 0)
// 		G4cout << "### MaterialCover2 created with " << ncomponents << " components"  << G4endl;

///////////////Cover2 Material Init
	G4Material* MaterialCover2 = new G4Material(name="MaterialCover2", 
		density=(gl.isCover2 ? gl.MaterialCover2Density : 1.0*g/cm3 ), 
		ncomponents=(gl.MaterialCover2NComponents!=0 ? gl.MaterialCover2NComponents : 
		 !gl.Cover2ElementSolution.empty()?  gl.Cover2ElementSolution.size():1));
	if(gl.MaterialCover2NComponents!=0){
	for(i=0; i < ncomponents; i++)
	{
		MaterialCover2->AddElement( NIST->FindOrBuildElement(gl.MaterialCover2ElementNames[i], true), 
			natoms=gl.MaterialCover2FormulaN[i]);
	}
	if(gl.VerboseAll > 0) {G4cout << "### MaterialCover2 created with " << ncomponents << " atomic components"  << G4endl;
			const G4ElementVector* elems = MaterialCover2->GetElementVector();
			const G4int* fracs = MaterialCover2->GetAtomsVector();
			for (G4int i=0; i<MaterialCover2->GetNumberOfElements(); ++i) {
    		std::cout << "  " << (*elems)[i]->GetName()
              << " Z=" << (*elems)[i]->GetZ()
              << ", Atoms =" << fracs[i] << "\n";
			}
		}
	
	}
	else if(!gl.Cover2ElementSolution.empty()){
	G4cout << "Parsed MaterialCover2Weight values:\n";
	double sum = std::accumulate(
        gl.Cover2ElementSolution.begin(), gl.Cover2ElementSolution.end(), 0.0,
        [](double total, const std::pair<const std::string, double>& p){
            return total + p.second;
        }
    );
	for (const auto& entry : gl.Cover2ElementSolution) 
	{
  		G4cout << "\tElement: " << entry.first << ", Weight: " << entry.second << G4endl;
		MaterialCover2->AddElement( NIST->FindOrBuildElement(entry.first, true), 
		entry.second/sum);
	}
	if(gl.VerboseAll > 0) {G4cout << "### MaterialCover2 created with " << ncomponents << " mass components"  << G4endl;
		const G4ElementVector* elems = MaterialCover2->GetElementVector();
		const G4double* fracs = MaterialCover2->GetFractionVector();
		for (G4int i=0; i<MaterialCover2->GetNumberOfElements(); ++i) {
    		std::cout << "  " << (*elems)[i]->GetName()
              << " Z=" << (*elems)[i]->GetZ()
              << ", fractionMass=" << fracs[i] << "\n";
			}
		}
	}
///////////////Cover2 Material Fin


//   G4Material* MaterialCover1 = new G4Material(name="MaterialCover1", 
// 		density=gl.MaterialCover1Density, ncomponents=gl.MaterialCover1NComponents);
// 	for(i=0; i < ncomponents; i++)
// 	{
// 		MaterialCover1->AddElement( NIST->FindOrBuildElement(gl.MaterialCover1ElementNames[i], true), 
// 			natoms=gl.MaterialCover1FormulaN[i]);
// 	}
//   if(gl.VerboseAll > 0)
// 		G4cout << "### MaterialCover1 created with " << ncomponents << " components"  << G4endl;

///////////////Cover1 Material Init
	G4Material* MaterialCover1 = new G4Material(name="MaterialCover1", 
		density=(gl.isCover1 ? gl.MaterialCover1Density : 1.0*g/cm3 ), 
		ncomponents=(gl.MaterialCover1NComponents!=0 ? gl.MaterialCover1NComponents : 
		 !gl.Cover1ElementSolution.empty()?  gl.Cover1ElementSolution.size():1));
	if(gl.MaterialCover1NComponents!=0){
	for(i=0; i < ncomponents; i++)
	{
		MaterialCover1->AddElement( NIST->FindOrBuildElement(gl.MaterialCover1ElementNames[i], true), 
			natoms=gl.MaterialCover1FormulaN[i]);
	}
	if(gl.VerboseAll > 0) {G4cout << "### MaterialCover1 created with " << ncomponents << " atomic components"  << G4endl;
			const G4ElementVector* elems = MaterialCover1->GetElementVector();
			const G4int* fracs = MaterialCover1->GetAtomsVector();
			for (G4int i=0; i<MaterialCover1->GetNumberOfElements(); ++i) {
    		std::cout << "  " << (*elems)[i]->GetName()
              << " Z=" << (*elems)[i]->GetZ()
              << ", Atoms =" << fracs[i] << "\n";
			}
		}
	
	}
	else if(!gl.Cover1ElementSolution.empty()){
	G4cout << "Parsed MaterialCover1Weight values:\n";
	double sum = std::accumulate(
        gl.Cover1ElementSolution.begin(), gl.Cover1ElementSolution.end(), 0.0,
        [](double total, const std::pair<const std::string, double>& p){
            return total + p.second;
        }
    );
	for (const auto& entry : gl.Cover1ElementSolution) 
	{
  		G4cout << "\tElement: " << entry.first << ", Weight: " << entry.second << G4endl;
		MaterialCover1->AddElement( NIST->FindOrBuildElement(entry.first, true), 
		entry.second/sum);
	}
	if(gl.VerboseAll > 0) {G4cout << "### MaterialCover1 created with " << ncomponents << " mass components"  << G4endl;
		const G4ElementVector* elems = MaterialCover1->GetElementVector();
		const G4double* fracs = MaterialCover1->GetFractionVector();
		for (G4int i=0; i<MaterialCover1->GetNumberOfElements(); ++i) {
    		std::cout << "  " << (*elems)[i]->GetName()
              << " Z=" << (*elems)[i]->GetZ()
              << ", fractionMass=" << fracs[i] << "\n";
			}
		}
	}
///////////////Cover1 Material Fin


	// G4Material* MaterialDet = new G4Material(name="MaterialDet", 
	// 	density=gl.MaterialDetDensity, ncomponents=gl.MaterialDetNComponents);
	// for(i=0; i < ncomponents; i++)
	// {
	// 	MaterialDet->AddElement( NIST->FindOrBuildElement(gl.MaterialDetElementNames[i], true), 
	// 		natoms=gl.MaterialDetFormulaN[i]);
	// }
	// if(gl.VerboseAll > 0)
	// 	G4cout << "### MaterialDet  created with " << ncomponents << " components"  << G4endl;

///////////////Det Material Init
	G4Material* MaterialDet = new G4Material(name="MaterialDet", 
		density=(gl.isDet ? gl.MaterialDetDensity : 1.0*g/cm3 ), 
		ncomponents=(gl.MaterialDetNComponents!=0 ? gl.MaterialDetNComponents : 
		 !gl.DetElementSolution.empty()?  gl.DetElementSolution.size():1));
	if(gl.MaterialDetNComponents!=0){
	for(i=0; i < ncomponents; i++)
	{
		MaterialDet->AddElement( NIST->FindOrBuildElement(gl.MaterialDetElementNames[i], true), 
			natoms=gl.MaterialDetFormulaN[i]);
	}
	if(gl.VerboseAll > 0) {G4cout << "### MaterialDet created with " << ncomponents << " atomic components"  << G4endl;
			const G4ElementVector* elems = MaterialDet->GetElementVector();
			const G4int* fracs = MaterialDet->GetAtomsVector();
			for (G4int i=0; i<MaterialDet->GetNumberOfElements(); ++i) {
    		std::cout << "  " << (*elems)[i]->GetName()
              << " Z=" << (*elems)[i]->GetZ()
              << ", Atoms =" << fracs[i] << "\n";
			}
		}
	
	}
	else if(!gl.DetElementSolution.empty()){
	G4cout << "Parsed MaterialDetWeight values:\n";
	double sum = std::accumulate(
        gl.DetElementSolution.begin(), gl.DetElementSolution.end(), 0.0,
        [](double total, const std::pair<const std::string, double>& p){
            return total + p.second;
        }
    );
	for (const auto& entry : gl.DetElementSolution) 
	{
  		G4cout << "\tElement: " << entry.first << ", Weight: " << entry.second << G4endl;
		MaterialDet->AddElement( NIST->FindOrBuildElement(entry.first, true), 
		entry.second/sum);
	}
	if(gl.VerboseAll > 0) {G4cout << "### MaterialDet created with " << ncomponents << " mass components"  << G4endl;
		const G4ElementVector* elems = MaterialDet->GetElementVector();
		const G4double* fracs = MaterialDet->GetFractionVector();
		for (G4int i=0; i<MaterialDet->GetNumberOfElements(); ++i) {
    		std::cout << "  " << (*elems)[i]->GetName()
              << " Z=" << (*elems)[i]->GetZ()
              << ", fractionMass=" << fracs[i] << "\n";
			}
		}
	}
///////////////Det Material Fin

	// G4Material* MaterialCavity = new G4Material(name="MaterialCavity", 
	// 	density=(gl.isCavity ? gl.MaterialCavityDensity : 1.0*g/cm3 ), 
	// 	ncomponents=(gl.isCavity ? gl.MaterialCavityNComponents : 1));
	// for(i=0; i < ncomponents; i++)
	// {
	// 	MaterialCavity->AddElement( NIST->FindOrBuildElement(gl.MaterialCavityElementNames[i], true), 
	// 		natoms=gl.MaterialCavityFormulaN[i]);
	// }
	// if(gl.VerboseAll > 0 && gl.isCavity)
	//   G4cout << "### MaterialCavity created with " << ncomponents << " components"  << G4endl;

///////////////Cavity Material Init
	G4Material* MaterialCavity = new G4Material(name="MaterialCavity", 
		density=(gl.isCavity ? gl.MaterialCavityDensity : 1.0*g/cm3 ), 
		ncomponents=(gl.MaterialCavityNComponents!=0 ? gl.MaterialCavityNComponents : 
		 !gl.CavityElementSolution.empty()?  gl.CavityElementSolution.size():1));
	if(gl.MaterialCavityNComponents!=0){
	for(i=0; i < ncomponents; i++)
	{
		MaterialCavity->AddElement( NIST->FindOrBuildElement(gl.MaterialCavityElementNames[i], true), 
			natoms=gl.MaterialCavityFormulaN[i]);
	}
	if(gl.VerboseAll > 0) {G4cout << "### MaterialCavity created with " << ncomponents << " atomic components"  << G4endl;
			const G4ElementVector* elems = MaterialCavity->GetElementVector();
			const G4int* fracs = MaterialCavity->GetAtomsVector();
			for (G4int i=0; i<MaterialCavity->GetNumberOfElements(); ++i) {
    		std::cout << "  " << (*elems)[i]->GetName()
              << " Z=" << (*elems)[i]->GetZ()
              << ", Atoms =" << fracs[i] << "\n";
			}
		}
	
	}
	else if(!gl.CavityElementSolution.empty()){
	G4cout << "Parsed MaterialCavityWeight values:\n";
	double sum = std::accumulate(
        gl.CavityElementSolution.begin(), gl.CavityElementSolution.end(), 0.0,
        [](double total, const std::pair<const std::string, double>& p){
            return total + p.second;
        }
    );
	for (const auto& entry : gl.CavityElementSolution) 
	{
  		G4cout << "\tElement: " << entry.first << ", Weight: " << entry.second << G4endl;
		MaterialCavity->AddElement( NIST->FindOrBuildElement(entry.first, true), 
		entry.second/sum);
	}
	if(gl.VerboseAll > 0) {G4cout << "### MaterialCavity created with " << ncomponents << " mass components"  << G4endl;
		const G4ElementVector* elems = MaterialCavity->GetElementVector();
		const G4double* fracs = MaterialCavity->GetFractionVector();
		for (G4int i=0; i<MaterialCavity->GetNumberOfElements(); ++i) {
    		std::cout << "  " << (*elems)[i]->GetName()
              << " Z=" << (*elems)[i]->GetZ()
              << ", fractionMass=" << fracs[i] << "\n";
			}
		}
	}
///////////////Cavity Material Fin


	// G4Material* MaterialTop1 = new G4Material(name="MaterialTop1", 
	// 	density=(gl.isTop1 ? gl.MaterialTop1Density : 1.0*g/cm3 ), 
	// 	ncomponents=(gl.isTop1 ? gl.MaterialTop1NComponents : 1));
	// for(i=0; i < ncomponents; i++)
	// {
	// 	MaterialTop1->AddElement( NIST->FindOrBuildElement(gl.MaterialTop1ElementNames[i], true), 
	// 		natoms=gl.MaterialTop1FormulaN[i]);
	// }
	// if(gl.VerboseAll > 0 && gl.isTop1)
	//   G4cout << "### MaterialTop1 created with " << ncomponents << " components"  << G4endl;
///////////////Top1 Material Init
	G4Material* MaterialTop1 = new G4Material(name="MaterialTop1", 
		density=(gl.isTop1 ? gl.MaterialTop1Density : 1.0*g/cm3 ), 
		ncomponents=(gl.MaterialTop1NComponents!=0 ? gl.MaterialTop1NComponents : 
		 !gl.Top1ElementSolution.empty()?  gl.Top1ElementSolution.size():1));
	if(gl.MaterialTop1NComponents!=0){
	for(i=0; i < ncomponents; i++)
	{
		MaterialTop1->AddElement( NIST->FindOrBuildElement(gl.MaterialTop1ElementNames[i], true), 
			natoms=gl.MaterialTop1FormulaN[i]);
	}
	if(gl.VerboseAll > 0) {G4cout << "### MaterialTop1 created with " << ncomponents << " atomic components"  << G4endl;
			const G4ElementVector* elems = MaterialTop1->GetElementVector();
			const G4int* fracs = MaterialTop1->GetAtomsVector();
			for (G4int i=0; i<MaterialTop1->GetNumberOfElements(); ++i) {
    		std::cout << "  " << (*elems)[i]->GetName()
              << " Z=" << (*elems)[i]->GetZ()
              << ", Atoms =" << fracs[i] << "\n";
			}
		}
	
	}
	else if(!gl.Top1ElementSolution.empty()){
	G4cout << "Parsed MaterialTop1Weight values:\n";
	double sum = std::accumulate(
        gl.Top1ElementSolution.begin(), gl.Top1ElementSolution.end(), 0.0,
        [](double total, const std::pair<const std::string, double>& p){
            return total + p.second;
        }
    );
	for (const auto& entry : gl.Top1ElementSolution) 
	{
  		G4cout << "\tElement: " << entry.first << ", Weight: " << entry.second << G4endl;
		MaterialTop1->AddElement( NIST->FindOrBuildElement(entry.first, true), 
		entry.second/sum);
	}
	if(gl.VerboseAll > 0) {G4cout << "### MaterialTop1 created with " << ncomponents << " mass components"  << G4endl;
		const G4ElementVector* elems = MaterialTop1->GetElementVector();
		const G4double* fracs = MaterialTop1->GetFractionVector();
		for (G4int i=0; i<MaterialTop1->GetNumberOfElements(); ++i) {
    		std::cout << "  " << (*elems)[i]->GetName()
              << " Z=" << (*elems)[i]->GetZ()
              << ", fractionMass=" << fracs[i] << "\n";
			}
		}
	}
///////////////Top1 Material Fin
	// G4Material* MaterialTop2 = new G4Material(name="MaterialTop2", 
	// 	density=(gl.isTop2 ? gl.MaterialTop2Density : 1.0*g/cm3 ), 
	// 	ncomponents=(gl.isTop2 ? gl.MaterialTop2NComponents : 1));
	// for(i=0; i < ncomponents; i++)
	// {
	// 	MaterialTop2->AddElement( NIST->FindOrBuildElement(gl.MaterialTop2ElementNames[i], true), 
	// 		natoms=gl.MaterialTop2FormulaN[i]);
	// }
	// if(gl.VerboseAll > 0 && gl.isTop2)
	//   G4cout << "### MaterialTop2 created with " << ncomponents << " components"  << G4endl;
///////////////Top2 Material Init
	G4Material* MaterialTop2 = new G4Material(name="MaterialTop2", 
		density=(gl.isTop2 ? gl.MaterialTop2Density : 1.0*g/cm3 ), 
		ncomponents=(gl.MaterialTop2NComponents!=0 ? gl.MaterialTop2NComponents : 
		 !gl.Top2ElementSolution.empty()?  gl.Top2ElementSolution.size():1));
	if(gl.MaterialTop2NComponents!=0){
	for(i=0; i < ncomponents; i++)
	{
		MaterialTop2->AddElement( NIST->FindOrBuildElement(gl.MaterialTop2ElementNames[i], true), 
			natoms=gl.MaterialTop2FormulaN[i]);
	}
	if(gl.VerboseAll > 0) {G4cout << "### MaterialTop2 created with " << ncomponents << " atomic components"  << G4endl;
			const G4ElementVector* elems = MaterialTop2->GetElementVector();
			const G4int* fracs = MaterialTop2->GetAtomsVector();
			for (G4int i=0; i<MaterialTop2->GetNumberOfElements(); ++i) {
    		std::cout << "  " << (*elems)[i]->GetName()
              << " Z=" << (*elems)[i]->GetZ()
              << ", Atoms =" << fracs[i] << "\n";
			}
		}
	
	}
	else if(!gl.Top2ElementSolution.empty()){
	G4cout << "Parsed MaterialTop2Weight values:\n";
	double sum = std::accumulate(
        gl.Top2ElementSolution.begin(), gl.Top2ElementSolution.end(), 0.0,
        [](double total, const std::pair<const std::string, double>& p){
            return total + p.second;
        }
    );
	for (const auto& entry : gl.Top2ElementSolution) 
	{
  		G4cout << "\tElement: " << entry.first << ", Weight: " << entry.second << G4endl;
		MaterialTop2->AddElement( NIST->FindOrBuildElement(entry.first, true), 
		entry.second/sum);
	}
	if(gl.VerboseAll > 0) {G4cout << "### MaterialTop2 created with " << ncomponents << " mass components"  << G4endl;
		const G4ElementVector* elems = MaterialTop2->GetElementVector();
		const G4double* fracs = MaterialTop2->GetFractionVector();
		for (G4int i=0; i<MaterialTop2->GetNumberOfElements(); ++i) {
    		std::cout << "  " << (*elems)[i]->GetName()
              << " Z=" << (*elems)[i]->GetZ()
              << ", fractionMass=" << fracs[i] << "\n";
			}
		}
	}
///////////////Top2 Material Fin

	// G4Material* MaterialTop3 = new G4Material(name="MaterialTop3", 
	// 	density=(gl.isTop3 ? gl.MaterialTop3Density : 1.0*g/cm3 ), 
	// 	ncomponents=(gl.isTop3 ? gl.MaterialTop3NComponents : 1));
	// for(i=0; i < ncomponents; i++)
	// {
	// 	MaterialTop3->AddElement( NIST->FindOrBuildElement(gl.MaterialTop3ElementNames[i], true), 
	// 		natoms=gl.MaterialTop3FormulaN[i]);
	// }
	// if(gl.VerboseAll > 0 && gl.isTop3)
	//   G4cout << "### MaterialTop3 created with " << ncomponents << " components"  << G4endl;
///////////////Top3 Material Init
	G4Material* MaterialTop3 = new G4Material(name="MaterialTop3", 
		density=(gl.isTop3 ? gl.MaterialTop3Density : 1.0*g/cm3 ), 
		ncomponents=(gl.MaterialTop3NComponents!=0 ? gl.MaterialTop3NComponents : 
		 !gl.Top3ElementSolution.empty()?  gl.Top3ElementSolution.size():1));
	if(gl.MaterialTop3NComponents!=0){
	for(i=0; i < ncomponents; i++)
	{
		MaterialTop3->AddElement( NIST->FindOrBuildElement(gl.MaterialTop3ElementNames[i], true), 
			natoms=gl.MaterialTop3FormulaN[i]);
	}
	if(gl.VerboseAll > 0) {G4cout << "### MaterialTop3 created with " << ncomponents << " atomic components"  << G4endl;
			const G4ElementVector* elems = MaterialTop3->GetElementVector();
			const G4int* fracs = MaterialTop3->GetAtomsVector();
			for (G4int i=0; i<MaterialTop3->GetNumberOfElements(); ++i) {
    		std::cout << "  " << (*elems)[i]->GetName()
              << " Z=" << (*elems)[i]->GetZ()
              << ", Atoms =" << fracs[i] << "\n";
			}
		}
	
	}
	else if(!gl.Top3ElementSolution.empty()){
	G4cout << "Parsed MaterialTop3Weight values:\n";
	double sum = std::accumulate(
        gl.Top3ElementSolution.begin(), gl.Top3ElementSolution.end(), 0.0,
        [](double total, const std::pair<const std::string, double>& p){
            return total + p.second;
        }
    );
	for (const auto& entry : gl.Top3ElementSolution) 
	{
  		G4cout << "\tElement: " << entry.first << ", Weight: " << entry.second << G4endl;
		MaterialTop3->AddElement( NIST->FindOrBuildElement(entry.first, true), 
		entry.second/sum);
	}
	if(gl.VerboseAll > 0) {G4cout << "### MaterialTop3 created with " << ncomponents << " mass components"  << G4endl;
		const G4ElementVector* elems = MaterialTop3->GetElementVector();
		const G4double* fracs = MaterialTop3->GetFractionVector();
		for (G4int i=0; i<MaterialTop3->GetNumberOfElements(); ++i) {
    		std::cout << "  " << (*elems)[i]->GetName()
              << " Z=" << (*elems)[i]->GetZ()
              << ", fractionMass=" << fracs[i] << "\n";
			}
		}
	}
///////////////Top3 Material Fin

	// G4Material* MaterialBot1 = new G4Material(name="MaterialBot1", 
	// 	density=(gl.isBot1 ? gl.MaterialBot1Density : 1.0*g/cm3 ), 
	// 	ncomponents=(gl.isBot1 ? gl.MaterialBot1NComponents : 1));
	// for(i=0; i < ncomponents; i++)
	// {
	// 	MaterialBot1->AddElement( NIST->FindOrBuildElement(gl.MaterialBot1ElementNames[i], true), 
	// 		natoms=gl.MaterialBot1FormulaN[i]);
	// }
	// if(gl.VerboseAll > 0 && gl.isBot1)
	//   G4cout << "### MaterialBot1 created with " << ncomponents << " components"  << G4endl;
///////////////Bot1 Material Init
	G4Material* MaterialBot1 = new G4Material(name="MaterialBot1", 
		density=(gl.isBot1 ? gl.MaterialBot1Density : 1.0*g/cm3 ), 
		ncomponents=(gl.MaterialBot1NComponents!=0 ? gl.MaterialBot1NComponents : 
		 !gl.Bot1ElementSolution.empty()?  gl.Bot1ElementSolution.size():1));
	if(gl.MaterialBot1NComponents!=0){
	for(i=0; i < ncomponents; i++)
	{
		MaterialBot1->AddElement( NIST->FindOrBuildElement(gl.MaterialBot1ElementNames[i], true), 
			natoms=gl.MaterialBot1FormulaN[i]);
	}
	if(gl.VerboseAll > 0) {G4cout << "### MaterialBot1 created with " << ncomponents << " atomic components"  << G4endl;
			const G4ElementVector* elems = MaterialBot1->GetElementVector();
			const G4int* fracs = MaterialBot1->GetAtomsVector();
			for (G4int i=0; i<MaterialBot1->GetNumberOfElements(); ++i) {
    		std::cout << "  " << (*elems)[i]->GetName()
              << " Z=" << (*elems)[i]->GetZ()
              << ", Atoms =" << fracs[i] << "\n";
			}
		}
	
	}
	else if(!gl.Bot1ElementSolution.empty()){
	G4cout << "Parsed MaterialBot1Weight values:\n";
	double sum = std::accumulate(
        gl.Bot1ElementSolution.begin(), gl.Bot1ElementSolution.end(), 0.0,
        [](double total, const std::pair<const std::string, double>& p){
            return total + p.second;
        }
    );
	for (const auto& entry : gl.Bot1ElementSolution) 
	{
  		G4cout << "\tElement: " << entry.first << ", Weight: " << entry.second << G4endl;
		MaterialBot1->AddElement( NIST->FindOrBuildElement(entry.first, true), 
		entry.second/sum);
	}
	if(gl.VerboseAll > 0) {G4cout << "### MaterialBot1 created with " << ncomponents << " mass components"  << G4endl;
		const G4ElementVector* elems = MaterialBot1->GetElementVector();
		const G4double* fracs = MaterialBot1->GetFractionVector();
		for (G4int i=0; i<MaterialBot1->GetNumberOfElements(); ++i) {
    		std::cout << "  " << (*elems)[i]->GetName()
              << " Z=" << (*elems)[i]->GetZ()
              << ", fractionMass=" << fracs[i] << "\n";
			}
		}
	}
///////////////Bot1 Material Fin

///////////////Bot2 Material Init
	G4Material* MaterialBot2 = new G4Material(name="MaterialBot2", 
		density=(gl.isBot2 ? gl.MaterialBot2Density : 1.0*g/cm3 ), 
		ncomponents=(gl.MaterialBot2NComponents!=0 ? gl.MaterialBot2NComponents : 
		 !gl.Bot2ElementSolution.empty()?  gl.Bot2ElementSolution.size():1));
	if(gl.MaterialBot2NComponents!=0){
	for(i=0; i < ncomponents; i++)
	{
		MaterialBot2->AddElement( NIST->FindOrBuildElement(gl.MaterialBot2ElementNames[i], true), 
			natoms=gl.MaterialBot2FormulaN[i]);
	}
	if(gl.VerboseAll > 0) {G4cout << "### MaterialBot2 created with " << ncomponents << " atomic components"  << G4endl;
			const G4ElementVector* elems = MaterialBot2->GetElementVector();
			const G4int* fracs = MaterialBot2->GetAtomsVector();
			for (G4int i=0; i<MaterialBot2->GetNumberOfElements(); ++i) {
    		std::cout << "  " << (*elems)[i]->GetName()
              << " Z=" << (*elems)[i]->GetZ()
              << ", Atoms =" << fracs[i] << "\n";
			}
		}
	
	}
	else if(!gl.Bot2ElementSolution.empty()){
	G4cout << "Parsed MaterialBot2Weight values:\n";
	double sum = std::accumulate(
        gl.Bot2ElementSolution.begin(), gl.Bot2ElementSolution.end(), 0.0,
        [](double total, const std::pair<const std::string, double>& p){
            return total + p.second;
        }
    );
	for (const auto& entry : gl.Bot2ElementSolution) 
	{
  		G4cout << "\tElement: " << entry.first << ", Weight: " << entry.second << G4endl;
		MaterialBot2->AddElement( NIST->FindOrBuildElement(entry.first, true), 
		entry.second/sum);
	}
	if(gl.VerboseAll > 0) {G4cout << "### MaterialBot2 created with " << ncomponents << " mass components"  << G4endl;
		const G4ElementVector* elems = MaterialBot2->GetElementVector();
		const G4double* fracs = MaterialBot2->GetFractionVector();
		for (G4int i=0; i<MaterialBot2->GetNumberOfElements(); ++i) {
    		std::cout << "  " << (*elems)[i]->GetName()
              << " Z=" << (*elems)[i]->GetZ()
              << ", fractionMass=" << fracs[i] << "\n";
			}
		}
	}
///////////////Bot2 Material Fin
///////////////Bot3 Meterial Init
	G4Material* MaterialBot3 = new G4Material(name="MaterialBot3", 
		density=(gl.isBot3 ? gl.MaterialBot3Density : 1.0*g/cm3 ), 
		ncomponents=(gl.MaterialBot3NComponents!=0 ? gl.MaterialBot3NComponents : 
		 !gl.Bot3ElementSolution.empty()?  gl.Bot3ElementSolution.size():1));
	if(gl.MaterialBot3NComponents!=0){
	for(i=0; i < ncomponents; i++)
	{
		MaterialBot3->AddElement( NIST->FindOrBuildElement(gl.MaterialBot3ElementNames[i], true), 
			natoms=gl.MaterialBot3FormulaN[i]);
	}
	if(gl.VerboseAll > 0) G4cout << "### MaterialBot3 created with " << ncomponents << " atomic components"  << G4endl;
	}
	else if(!gl.Bot3ElementSolution.empty()){
	G4cout << "Parsed MaterialBot3Weight values:\n";
	double sum = std::accumulate(
        gl.Bot3ElementSolution.begin(), gl.Bot3ElementSolution.end(), 0.0,
        [](double total, const std::pair<const std::string, double>& p){
            return total + p.second;
        }
    );
	for (const auto& entry : gl.Bot3ElementSolution) 
	{
  		G4cout << "\tElement: " << entry.first << ", Weight: " << entry.second << G4endl;
		MaterialBot3->AddElement( NIST->FindOrBuildElement(entry.first, true), 
		entry.second/sum);
	}
	if(gl.VerboseAll > 0) {G4cout << "### MaterialBot3 created with " << ncomponents << " mass components"  << G4endl;
		const G4ElementVector* elems = MaterialBot3->GetElementVector();
		const G4double* fracs = MaterialBot3->GetFractionVector();
		for (G4int i=0; i<MaterialBot3->GetNumberOfElements(); ++i) {
    		std::cout << "  " << (*elems)[i]->GetName()
              << " Z=" << (*elems)[i]->GetZ()
              << ", fractionMass=" << fracs[i] << "\n";
			}
		}
	}
////////////////////Bot3 Material Fin


  G4cout << "### Materials created " << G4endl;
////////////////////


  if(gl.VerboseAll>0) 
		G4cout << *(G4Material::GetMaterialTable()) << G4endl; // print the list of materials

  G4cout << "[OK]" << G4endl;

 

//------------------------------------------------------ volumes
  G4cout << "### Volumes construction started:" << G4endl;


  //------------------------------ experimental hall (world volume)
  G4cout << "### Experimental Hall construction started:     ";
  // global space volume - the cylinder

  G4Tubs* experimentalHall = new G4Tubs("expHall",
    0.0,// internal radius
    gl.D_SHLD/2., // external radius
    gl.ZL_SHLD/2.,
    0.*deg, 360.*deg);

  // logical volume filled with MaterialSHLD
  G4LogicalVolume* experimentalHall_log
	= new G4LogicalVolume(experimentalHall,MaterialSHLD,"expHall_log",0,0,0);
	logicalVolumeMap["SHLD"]= experimentalHall_log;

#ifdef G4VIS_USE
  G4VisAttributes* hallVisAttr = new G4VisAttributes(G4Color(1.,1.,0.,0.));
  hallVisAttr->SetVisibility(true);
  hallVisAttr->SetForceWireframe(true);

  experimentalHall_log->SetVisAttributes(hallVisAttr);
#endif

  // physical volume of global space
  G4VPhysicalVolume* experimentalHall_phys
    = new G4PVPlacement(0,			// don't rotate
						// position of volume center:
			G4ThreeVector(),
			experimentalHall_log,	// logical volume object
			"expHall",		// volume's name
			0,			// parent volume
			false,			// bool operations
			0);			// number of copy of object

  G4cout << "[OK]" << G4endl;
        /*/
       /*/
      /*/
     /*/
    /*/
   /*/
  /*/
 /*/
/*/
*/

//===============Cover2 (alias: Marinelli) ===================================================
//=============== External envelope of Det ===================================================
	G4LogicalVolume* Cover2_log;
	if(gl.isCover2 == true)
	{
		G4cout << "### Cover2 construction started:                  ";
  
		G4Box* Cover2Box = new G4Box("Cover2Box",gl.XL_Cover2/2., gl.YL_Cover2/2., gl.ZL_Cover2/2.);
		G4Tubs* Cover2Cyl = new G4Tubs("Cover2Cyl",
			0.,
			gl.D_Cover2 /2.,
			gl.ZL_Cover2 /2.,
			0.*deg, 360.*deg);

		G4VSolid* Cover2;
		if(gl.isCover2Box >= 1) 
		{
			Cover2 = Cover2Box;
		} else 
		{
			Cover2 = Cover2Cyl;
			if(gl.XL_Cover2 != gl.YL_Cover2) 
				G4Exception("SimourgDetectorConstruction::Construct()","",FatalException,
					"### XL_Cover2 and YL_Cover2 for cylindric core volume should be equal.");
		}
  

		// logical volume filled with MaterialCover2
		Cover2_log	= new G4LogicalVolume(Cover2,MaterialCover2,"Cover2_log",0,0,0);
		logicalVolumeMap["Cover2"]= Cover2_log;

#ifdef G4VIS_USE
		G4VisAttributes* Cover2VisAttr = new G4VisAttributes(G4Color(0.,1.,1.,0.));
		Cover2VisAttr->SetVisibility(true);
//		Cover2VisAttr->SetForceWireframe(true);
		Cover2VisAttr->SetForceSolid(true);

		Cover2_log->SetVisAttributes(Cover2VisAttr);
#endif

		// physical volume 
		// center of volume in parent coordinate system

		G4VPhysicalVolume* Cover2_phys = new G4PVPlacement(0,			// don't rotate
                                // position of volume center:
				G4ThreeVector(gl.X_Cover2,gl.Y_Cover2,gl.Z_Cover2), // 
				Cover2_log,	// logical volume object
				"Cover2",		// volume's name
				experimentalHall_log,			// parent volume
				false,			// bool operations
				0);			// number of copy of object
		G4cout << "### Z_Cover2:" << gl.Z_Cover2 << G4endl;
		G4cout << "[OK]" << G4endl;
	} // endif(gl.isCover2 == true)

//===============Cover1 (alias:Core) =========================================================
//=============== Internal envelope of Det ===================================================
	G4LogicalVolume* Cover1_log;
	if(gl.isCover1 == true)
	{
		G4cout << "### Cover1 construction started:                  ";
  
		G4Box* Cover1Box = new G4Box("Cover1Box",gl.XL_Cover1/2., gl.YL_Cover1/2., gl.ZL_Cover1/2.);
		G4Tubs* Cover1Cyl = new G4Tubs("Cover1Cyl",
			0.,
			gl.D_Cover1 /2.,
			gl.ZL_Cover1 /2.,
			0.*deg, 360.*deg);

		G4VSolid* Cover1;
		if(gl.isCover1Box >= 1) 
		{
			Cover1 = Cover1Box;
		} else 
		{
			Cover1 = Cover1Cyl;
			if(gl.XL_Cover1 != gl.YL_Cover1) 
				G4Exception("SimourgDetectorConstruction::Construct()","",FatalException,
					"### XL_Cover1 and YL_Cover1 for cylindric core volume should be equal.");
		}
  

		// logical volume filled with MaterialCover1
		Cover1_log = new G4LogicalVolume(Cover1,MaterialCover1,"Cover1_log",0,0,0);
		logicalVolumeMap["Cover1"]= Cover1_log;

#ifdef G4VIS_USE
		G4VisAttributes* Cover1VisAttr = new G4VisAttributes(G4Color(0.,0.,1.,1.));
		Cover1VisAttr->SetVisibility(true);
//	 Cover1VisAttr->SetForceWireframe(true);
		Cover1VisAttr->SetForceSolid(true);

		Cover1_log->SetVisAttributes(Cover1VisAttr);
#endif

  // physical volume 
  // center of volume in parent coordinate system

		G4VPhysicalVolume* Cover1_phys
			= new G4PVPlacement(0,			// don't rotate
			                           // position of volume center:
				G4ThreeVector(
					((gl.isCover2 == true) ? (gl.X_Cover1 - gl.X_Cover2) :	// if Core is placed in Marinelli
							gl.X_Cover1																					// if Core is placed in ExpHall
					),
					((gl.isCover2 == true) ? (gl.Y_Cover1 - gl.Y_Cover2) :	// if Core is placed in Marinelli
							gl.Y_Cover1																					// if Core is placed in ExpHall
					),
					((gl.isCover2 == true) ? (gl.Z_Cover1 - gl.Z_Cover2) :	// if Core is placed in Marinelli
							gl.Z_Cover1																					// if Core is placed in ExpHall
					)
				), // 
				Cover1_log,	// logical volume object
				"Cover1",		// volume's name
				((gl.isCover2 == true) ? Cover2_log : experimentalHall_log),			// parent volume
				false,			// bool operations
				0);			// number of copy of object

		G4cout << "### Z_Cover1:" << gl.Z_Cover1 << G4endl;
		G4cout << "[OK]" << G4endl;
	}// endif(gl.isCover1 == true)

//===============Detector ===================================================
  
  G4Box* DetBox = new G4Box("DetBox",gl.XL_Det/2., gl.YL_Det/2., gl.ZL_Det/2.);
  G4Tubs* DetCyl = new G4Tubs("DetCyl",0.,gl.D_Det/2., gl.ZL_Det/2., 0.*deg, 360.*deg);

	G4VSolid* Det;
	if(gl.isDetBox >= 1) 
	{
		Det = DetBox;
	} else 
	{
		Det = DetCyl;
		if(gl.XL_Det != gl.YL_Det) 
      G4Exception("SimourgDetectorConstruction::Construct()","",FatalException,
        "### XL_Det and YL_Det for cylindric detector should be equal.");
	}

  // logical volume filled with MaterialDet
  G4LogicalVolume* Det_log
	= new G4LogicalVolume(Det,MaterialDet,"Det_log",0,0,0);


#ifdef G4VIS_USE
  G4VisAttributes* DetVisAttr = new G4VisAttributes(G4Color(1.,1.,0.,1.));
  DetVisAttr->SetVisibility(true);
//  DetVisAttr->SetForceWireframe(true);
  DetVisAttr->SetForceSolid(true);

  Det_log->SetVisAttributes(DetVisAttr);
#endif

  // physical volume 
  // center of volume in parent coordinate system
	rotation = new G4RotationMatrix();
	rotation->rotateX(gl.Rot_Det.x());
	rotation->rotateY(gl.Rot_Det.y());
	rotation->rotateZ(gl.Rot_Det.z());
  G4VPhysicalVolume* Det_phys
    = new G4PVPlacement(
		rotation, //rotate
		// 0,			// don't rotate
                                // position of volume center:
			G4ThreeVector(
								((gl.isCover1 == true) ? (gl.X_Det - gl.X_Cover1) :														// if Det is placed in Core
																((gl.isCover2 == true) ?	(gl.X_Det - gl.X_Cover2) :	// if Det is placed in Marinelli 
																													 gl.X_Det										// if Det is placed in ExpHall
																)
				)	,
								((gl.isCover1 == true) ? (gl.Y_Det - gl.Y_Cover1) :														// if Det is placed in Core
																((gl.isCover2 == true) ?	(gl.Y_Det - gl.Y_Cover2) :	// if Det is placed in Marinelli 
																													 gl.Y_Det										// if Det is placed in ExpHall
																)
				)	,
								((gl.isCover1 == true) ? (gl.Z_Det - gl.Z_Cover1) :														// if Det is placed in Core
																((gl.isCover2 == true) ?	(gl.Z_Det - gl.Z_Cover2) :	// if Det is placed in Marinelli 
																													 gl.Z_Det										// if Det is placed in ExpHall
																)
				)	
			), // 
			Det_log,	// logical volume object
			"Det",		// volume's name
			((gl.isCover1 == true) ? Cover1_log : ((gl.isCover2 == true) ? Cover2_log : experimentalHall_log) ),			// parent volume
			false,			// bool operations
			0);			// number of copy of object
  
  G4cout << "### Z_Det:" << gl.Z_Det << G4endl;
  G4cout << "[OK]" << G4endl;

//===============Cavity===================================================
  
	G4Tubs* CavityCyl = new G4Tubs("CavityCyl",
		0.,
		gl.D_Cavity /2.,
		gl.ZL_Cavity /2.,
		0.*deg, 360.*deg);

	// logical volume filled with MaterialCavity
	G4LogicalVolume* Cavity_log
		= new G4LogicalVolume(CavityCyl,MaterialCavity,"Cavity_log",0,0,0);
		logicalVolumeMap["Cavity"]= Cavity_log;

#ifdef G4VIS_USE
	G4VisAttributes* CavityVisAttr = new G4VisAttributes(G4Color(1.,1.,1.,1.));
	CavityVisAttr->SetVisibility(true);
//	CavityVisAttr->SetForceWireframe(true);
	CavityVisAttr->SetForceSolid(true);

	Cavity_log->SetVisAttributes(CavityVisAttr);
#endif

		// physical volume 
		// center of volume in parent coordinate system
	rotation = new G4RotationMatrix();
	rotation->rotateX(gl.Rot_Cavity.x());
	rotation->rotateY(gl.Rot_Cavity.y());
	rotation->rotateZ(gl.Rot_Cavity.z());
	G4VPhysicalVolume* Cavity_phys;
	if(gl.isCavity)
	{
		Cavity_phys = new G4PVPlacement(
			rotation, //rotate
			// 0,			// don't rotate
                               // position of volume center:
			G4ThreeVector(gl.X_Cavity-gl.X_Det,gl.Y_Cavity-gl.Y_Det,gl.Z_Cavity-gl.Z_Det), // 
			Cavity_log,	// logical volume object
			"Cavity",		// volume's name
			Det_log,			// parent volume
			false,			// bool operations
			0);			// number of copy of object
	  G4cout << "### Cavity placed:                  ";

		G4cout << "### Z_Cavity:" << gl.Z_Cavity;
		G4cout << "[OK]" << G4endl;
	}

//===============Top1===================================================
  
  G4Tubs* Top1Cyl = new G4Tubs("Top1Cyl",
   gl.d_Top1/2.,
    gl.D_Top1 /2.,
    gl.ZL_Top1 /2.,
    0.*deg, 360.*deg);

  // logical volume filled with MaterialTop1
  G4LogicalVolume* Top1_log
	= new G4LogicalVolume(Top1Cyl,MaterialTop1,"Top1_log",0,0,0);
	logicalVolumeMap["Top1"]= Top1_log;

#ifdef G4VIS_USE
  G4VisAttributes* Top1VisAttr = new G4VisAttributes(G4Color(1.,1.,1.,1.));
  Top1VisAttr->SetVisibility(true);
//  Top1VisAttr->SetForceWireframe(true);
  Top1VisAttr->SetForceSolid(true);

  Top1_log->SetVisAttributes(Top1VisAttr);
#endif

  // physical volume 
  // center of volume in parent coordinate system
	// Create rotation matrix
	rotation = new G4RotationMatrix();
	rotation->rotateX(gl.Rot_Top1.x());
	rotation->rotateY(gl.Rot_Top1.y());
	rotation->rotateZ(gl.Rot_Top1.z());
  G4VPhysicalVolume* Top1_phys;
	if(gl.isTop1)
	{
		Top1_phys = new G4PVPlacement(
			// 0, //no rotation
			rotation,			// rotate
                                // position of volume center:
			G4ThreeVector(gl.X_Top1,gl.Y_Top1,gl.Z_Top1), // 
			Top1_log,	// logical volume object
			"Top1",		// volume's name
			experimentalHall_log,			// parent volume
			false,			// bool operations
			0);			// number of copy of object
	  G4cout << "### Top1 placed:                  ";

		G4cout << "### Z_Top1:" << gl.Z_Top1;
		G4cout << "[OK]" << G4endl;
	} 

//===============Top2===================================================
  
  G4Tubs* Top2Cyl = new G4Tubs("Top2Cyl",
    gl.d_Top2/2.,
    gl.D_Top2 /2.,
    gl.ZL_Top2 /2.,
    0.*deg, 360.*deg);

  // logical volume filled with MaterialTop2
  G4LogicalVolume* Top2_log
	= new G4LogicalVolume(Top2Cyl,MaterialTop2,"Top2_log",0,0,0);
	logicalVolumeMap["Top2"]= Top2_log;

#ifdef G4VIS_USE
  G4VisAttributes* Top2VisAttr = new G4VisAttributes(G4Color(1.,1.,1.,1.));
  Top2VisAttr->SetVisibility(true);
//  Top2VisAttr->SetForceWireframe(true);
  Top2VisAttr->SetForceSolid(true);

  Top2_log->SetVisAttributes(Top2VisAttr);
#endif

  // physical volume 
  // center of volume in parent coordinate system
	rotation = new G4RotationMatrix();
	rotation->rotateX(gl.Rot_Top2.x());
	rotation->rotateY(gl.Rot_Top2.y());
	rotation->rotateZ(gl.Rot_Top2.z());
  G4VPhysicalVolume* Top2_phys;
	if(gl.isTop2)
	{
		Top2_phys = new G4PVPlacement(
			// 0, //no rotation
			rotation,			// rotate
                                // position of volume center:
			G4ThreeVector(gl.X_Top2,gl.Y_Top2,gl.Z_Top2), // 
			Top2_log,	// logical volume object
			"Top2",		// volume's name
			experimentalHall_log,			// parent volume
			false,			// bool operations
			0);			// number of copy of object
	  G4cout << "### Top2 placed:                  ";

		G4cout << "### Z_Top2:" << gl.Z_Top2;
		G4cout << "[OK]" << G4endl;
	} 

//===============Top3===================================================
  
  G4Tubs* Top3Cyl = new G4Tubs("Top3Cyl",
    gl.d_Top3/2.,
    gl.D_Top3 /2.,
    gl.ZL_Top3 /2.,
    0.*deg, 360.*deg);

  // logical volume filled with MaterialTop3
  G4LogicalVolume* Top3_log
	= new G4LogicalVolume(Top3Cyl,MaterialTop3,"Top3_log",0,0,0);
	logicalVolumeMap["Top3"]= Top3_log;

#ifdef G4VIS_USE
  G4VisAttributes* Top3VisAttr = new G4VisAttributes(G4Color(1.,1.,1.,1.));
  Top3VisAttr->SetVisibility(true);
//  Top3VisAttr->SetForceWireframe(true);
  Top3VisAttr->SetForceSolid(true);

  Top3_log->SetVisAttributes(Top3VisAttr);
#endif

  // physical volume 
  // center of volume in parent coordinate system
	rotation = new G4RotationMatrix();
	rotation->rotateX(gl.Rot_Top3.x());
	rotation->rotateY(gl.Rot_Top3.y());
	rotation->rotateZ(gl.Rot_Top3.z());
  G4VPhysicalVolume* Top3_phys;
	if(gl.isTop3)
	{
		Top3_phys = new G4PVPlacement(
			// 0, //no rotation
			rotation,			// rotate
                                // position of volume center:
			G4ThreeVector(gl.X_Top3,gl.Y_Top3,gl.Z_Top3), // 
			Top3_log,	// logical volume object
			"Top3",		// volume's name
			experimentalHall_log,			// parent volume
			false,			// bool operations
			0);			// number of copy of object
	  G4cout << "### Top3 placed:                  ";

		G4cout << "### Z_Top3:" << gl.Z_Top3;
		G4cout << "[OK]" << G4endl;
	} 

//===============Bot1===================================================
  
  G4Tubs* Bot1Cyl = new G4Tubs("Bot1Cyl",
    gl.d_Bot1 /2.,
    gl.D_Bot1 /2.,
    gl.ZL_Bot1 /2.,
    0.*deg, 360.*deg);

  // logical volume filled with MaterialBot1
  G4LogicalVolume* Bot1_log
	= new G4LogicalVolume(Bot1Cyl,MaterialBot1,"Bot1_log",0,0,0);
	logicalVolumeMap["Bot1"]= Bot1_log;

#ifdef G4VIS_USE
  G4VisAttributes* Bot1VisAttr = new G4VisAttributes(G4Color(1.,1.,1.,1.));
  Bot1VisAttr->SetVisibility(true);
//  Bot1VisAttr->SetForceWireframe(true);
  Bot1VisAttr->SetForceSolid(true);

  Bot1_log->SetVisAttributes(Bot1VisAttr);
#endif

  // physical volume 
  // center of volume in parent coordinate system
	rotation = new G4RotationMatrix();
	rotation->rotateX(gl.Rot_Bot1.x());
	rotation->rotateY(gl.Rot_Bot1.y());
	rotation->rotateZ(gl.Rot_Bot1.z());
  G4VPhysicalVolume* Bot1_phys;
	if(gl.isBot1)
	{
		Bot1_phys = new G4PVPlacement(
			// 0, //no rotation
			rotation,			// rotate
                                // position of volume center:
			G4ThreeVector(gl.X_Bot1,gl.Y_Bot1,gl.Z_Bot1), // 
			Bot1_log,	// logical volume object
			"Bot1",		// volume's name
			experimentalHall_log,			// parent volume
			false,			// bool operations
			0);			// number of copy of object
	  G4cout << "### Bot1 placed:                  ";

		G4cout << "### Z_Bot1:" << gl.Z_Bot1;
		G4cout << "[OK]" << G4endl;
	} 

//===============Bot2===================================================
  
  G4Tubs* Bot2Cyl = new G4Tubs("Bot2Cyl",
    gl.d_Bot2 /2.,
    gl.D_Bot2 /2.,
    gl.ZL_Bot2 /2.,
    0.*deg, 360.*deg);

  // logical volume filled with MaterialBot2
  G4LogicalVolume* Bot2_log
	= new G4LogicalVolume(Bot2Cyl,MaterialBot2,"Bot2_log",0,0,0);
	logicalVolumeMap["Bot2"]= Bot2_log;

#ifdef G4VIS_USE
  G4VisAttributes* Bot2VisAttr = new G4VisAttributes(G4Color(1.,1.,1.,1.));
  Bot2VisAttr->SetVisibility(true);
//  Bot2VisAttr->SetForceWireframe(true);
  Bot2VisAttr->SetForceSolid(true);

  Bot2_log->SetVisAttributes(Bot2VisAttr);
#endif

  // physical volume 
  // center of volume in parent coordinate system

	rotation = new G4RotationMatrix();
	rotation->rotateX(gl.Rot_Bot2.x());
	rotation->rotateY(gl.Rot_Bot2.y());
	rotation->rotateZ(gl.Rot_Bot2.z());

  G4VPhysicalVolume* Bot2_phys;
	if(gl.isBot2)
	{
		Bot2_phys = new G4PVPlacement(
			rotation, // rotate
			// 0,			// don't rotate
                                // position of volume center:
			G4ThreeVector(gl.X_Bot2,gl.Y_Bot2,gl.Z_Bot2), // 
			Bot2_log,	// logical volume object
			"Bot2",		// volume's name
			experimentalHall_log,			// parent volume
			false,			// bool operations
			0);			// number of copy of object
	  G4cout << "### Bot2 placed:                  ";

		G4cout << "### Z_Bot2:" << gl.Z_Bot2;
		G4cout << "[OK]" << G4endl;
	} 

//===============Bot3===================================================
  
  G4Tubs* Bot3Cyl = new G4Tubs("Bot3Cyl",
    gl.d_Bot3 /2.,
    gl.D_Bot3 /2.,
    gl.ZL_Bot3 /2.,
    0.*deg, 360.*deg);

  // logical volume filled with MaterialBot3
  
  G4LogicalVolume* Bot3_log
	= new G4LogicalVolume(Bot3Cyl,MaterialBot3,"Bot3_log",0,0,0);
	logicalVolumeMap["Bot3"]= Bot3_log;

#ifdef G4VIS_USE
  G4VisAttributes* Bot3VisAttr = new G4VisAttributes(G4Color(1.,1.,1.,1.));
  Bot3VisAttr->SetVisibility(true);
//  Bot3VisAttr->SetForceWireframe(true);
  Bot3VisAttr->SetForceSolid(true);

  Bot3_log->SetVisAttributes(Bot3VisAttr);
#endif

  // physical volume 
  // center of volume in parent coordinate system
	rotation = new G4RotationMatrix();
	rotation->rotateX(gl.Rot_Bot3.x());
	rotation->rotateY(gl.Rot_Bot3.y());
	rotation->rotateZ(gl.Rot_Bot3.z());
  G4VPhysicalVolume* Bot3_phys;
	if(gl.isBot3)
	{
		Bot3_phys = new G4PVPlacement(
			rotation, //rotate
			// 0,			// don't rotate
                                // position of volume center:
			G4ThreeVector(gl.X_Bot3,gl.Y_Bot3,gl.Z_Bot3), // 
			Bot3_log,	// logical volume object
			"Bot3",		// volume's name
			experimentalHall_log,			// parent volume
			false,			// bool operations
			0);			// number of copy of object
	  G4cout << "### Bot3 placed:                  ";

		G4cout << "### Z_Bot3:" << gl.Z_Bot3;
		G4cout << "[OK]" << G4endl;
	} 


  //------------------------------------------------
  // Sensitive detector
  //------------------------------------------------

  G4SDManager* SDman = G4SDManager::GetSDMpointer();

  G4String Det_SDname = "Det/DetSD";

  SimourgSensDet* Det_SD = new SimourgSensDet(Det_SDname,this);
 

  SDman->AddNewDetector( Det_SD );
  Det_log->SetSensitiveDetector( Det_SD );

    for (G4String Detector : gl.DetectorsList) {
        std::cout << Detector << " Is detector " << std::endl;
		SimourgSensDet* temp = new SimourgSensDet(Detector,this);
		SDman->AddNewDetector( temp );
		G4LogicalVolume* it = logicalVolumeMap[Detector];
		it->SetSensitiveDetector( temp );
    }

//  if(gl.isTop1aDetector==1)
//   {
// 	SimourgSensDet* Top1_SD = new SimourgSensDet("Top1_SD",this);
// 	SDman->AddNewDetector( Top1_SD );
// 	Top1_log->SetSensitiveDetector( Top1_SD );
//   }

  G4cout << "### Detector constructed                        " << "[OK]" << G4endl;
  
  return experimentalHall_phys;
}


