// Simourg_1.4.cc :
//
// cylindric or box detector within cylindric or box cavity within cylindric passive shield
// 6 additional cylindric volumes (along axis)
// calculation of responce function for a gamma source or Decay0 source (point-like or 
//   cylindric or box, placed in arbitrary point, with subtraction of a volume, if necessary)
//
// Based on Simourg_1.4 and SimourgQuasi:  
//

// switch on/off visualization:
// #ifdef G4VIS_USE
// # define G4VIS_USEi 1
// #endif

// #define G4VIS_USE


//////////////////////////////
#include "G4RunManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4UImanager.hh"
#include "G4UIterminal.hh"
#include "G4PhysListFactory.hh"
#include "G4VModularPhysicsList.hh"
#include "G4SystemOfUnits.hh"
#include "G4AnalysisManager.hh"

#include <CLHEP/Random/Randomize.h>

#include <stdlib.h>
#include <cstdlib> 
#include <time.h>
#include <chrono>
#include <ctime>
#include <fstream>
#include <numeric>
#include <map>
#include <vector>
#include <string>
#include <numeric>  // for std::accumulate
#include <iostream>

#include "SimourgDetectorConstruction.h"
//#include "SimourgPhysicsList.h"
#include "SimourgPrimaryGeneratorAction.h"
#include "SimourgEventAction.h"
#include "SimourgSensDet.h"
#include "SimourgMessenger.h"



// #define SpectrumLengthDet 5000
constexpr int SpectrumLengthDet = 5000;



#include "SimourgGlobal.h"
SimourgGlobal gl;



int main(int argc, char* argv[])
{ 
  G4cout << "=================== Simourg v1.4 ====================" << G4endl;
  G4cout << "====== Assembly: " __DATE__ " " __TIME__ " " << G4endl;
  G4cout << "====== www: http://lpd.kinr.kiev.ua/kobychev/Simourg/" << G4endl;
  gl.TimeStampMain = "Executing " __FILE__ " (compiled " __DATE__ " " __TIME__ ")";

  G4int i,ii;
  G4int SpectrumRaw[SpectrumLengthDet];
  G4int SpectrumBlur[SpectrumLengthDet];

  // G4UIterminal* session = new G4UIterminal();

  G4RunManager* runManager = new G4RunManager;

  G4UImanager* UI = G4UImanager::GetUIpointer();


 
  SimourgMessenger* Messenger = new SimourgMessenger(& gl);
 

    G4String command = "/control/execute ";

    G4String fileName = argv[1];//"SimourgSampleBIG.mac";//
    G4cout << (command+fileName) << G4endl;
    UI->ApplyCommand(command+fileName);



  gl.FineTuning();// after reading *.mac file
 if(gl.VerboseAll >= 0)
  {
    UI->ApplyCommand("/user/showAll");
  }


  if(gl.VerboseAll <= 0)
  {
    UI->ApplyCommand("/run/verbose 0");
    UI->ApplyCommand("/event/verbose 0");
    UI->ApplyCommand("/tracking/verbose 0");
    UI->ApplyCommand("/hits/verbose 0");
  }else if(gl.VerboseAll == 1)
  {
    UI->ApplyCommand("/run/verbose 1");
    UI->ApplyCommand("/event/verbose 1");
    UI->ApplyCommand("/tracking/verbose 1");
    UI->ApplyCommand("/hits/verbose 1");
  }else if(gl.VerboseAll >= 2)
  {
    UI->ApplyCommand("/run/verbose 2");
    UI->ApplyCommand("/event/verbose 2");
    UI->ApplyCommand("/tracking/verbose 2");
    UI->ApplyCommand("/hits/verbose 2");
  }

  runManager->SetRandomNumberStore(false);
  
   G4cout << "### Detector construction started               ";
  runManager->SetUserInitialization(new SimourgDetectorConstruction);
 G4cout << "[OK]" << G4endl;

  G4cout << "### Physics list construction started  with PL: " << gl.PhysicsList << G4endl;

  G4PhysListFactory factory;
  G4VModularPhysicsList* physlist = factory.GetReferencePhysList(gl.PhysicsList);//"FTFP_BERT_LIV" or other ;
  physlist->SetVerboseLevel(gl.VerboseAll);
  runManager->SetUserInitialization(physlist);
 G4cout << "[OK]" << G4endl;

  runManager->SetUserAction(new SimourgPrimaryGeneratorAction);
  runManager->SetUserAction(new SimourgEventAction);
G4cout << "runManager Initialize 1" << G4endl;
  
  runManager->Initialize();
  G4cout << "runManager Initialize 2" << G4endl;
  G4VisManager* visManager = new G4VisExecutive;
  G4cout << "visManager Initialize 1" << G4endl;
  visManager->Initialize();
  G4cout << "visManager Initialize 2" << G4endl;
 // G4cout << (command+"vis.mac") << G4endl;



  UI->ApplyCommand("/hits/activate Det/DetSD");



    UI->ApplyCommand("/tracking/storeTrajectory 1");
 // Ensure a scene is created before adding objects
    UI->ApplyCommand("/vis/scene/create");
    UI->ApplyCommand("/vis/sceneHandler/attach");
    UI->ApplyCommand("/vis/scene/add/volume");  // Add detector geometry
    UI->ApplyCommand("/vis/scene/add/axes 0 0 0 10 cm"); // Reference axes

    // Ensure trajectories are stored
    UI->ApplyCommand("/tracking/storeTrajectory 1");

    // Run an event
    // runManager->BeamOn(10);  // Try running more events

    if(gl.VerboseVis <= 0)
    {
      UI->ApplyCommand("/vis/verbose 0");
    }else if(gl.VerboseVis == 1)
    {
      UI->ApplyCommand("/vis/verbose 1");
    }else if(gl.VerboseVis == 2)
    {
      UI->ApplyCommand("/vis/verbose 2");
    }else if(gl.VerboseVis == 3)
    {
      UI->ApplyCommand("/vis/verbose 3");
    }else if(gl.VerboseVis == 4)
    {
      UI->ApplyCommand("/vis/verbose 4");
    }else if(gl.VerboseVis == 5)
    {
      UI->ApplyCommand("/vis/verbose 5");
    }else if(gl.VerboseVis >= 6)
    {
      UI->ApplyCommand("/vis/verbose 6");
    }
    if(gl.DoPicture == 1)
    {
      //todo 1: variable with limit
      //todo 2: each volume - sens detector - more than 1 detector: edep in each detector per event(run)
      // number of event, edep in 1 detecto, edep in 2 detector ....
      //#/user/VolumeSrc Det - uncomment for any detector -> perform as active detector
      //todo 3: volumes rotation on angle
      //todo 4: buildin volumes intersection procedure HIGHT PRIORITY
      // comment - simple for user
        G4String vrmlFiles = "G4VRMLFILE_MAX_FILE_NUM=" + std::to_string(gl.wrlFilesQuantity);
      #ifdef _WIN32
          std::cout << "Running on Windows" << std::endl;
        _putenv(vrmlFiles);
      #else
          std::string str = std::to_string(gl.wrlFilesQuantity);
          const char* cstr = str.c_str();
          setenv("G4VRMLFILE_MAX_FILE_NUM", cstr, 1);
      #endif

    //   G4cout << "DoPicture corresponds to "<< gl.DoPicture << G4endl;
      UI->ApplyCommand("/vis/open VRML2FILE");
      UI->ApplyCommand("/vis/sceneHandler/create");
      UI->ApplyCommand("/vis/scene/create");
      UI->ApplyCommand("/tracking/storeTrajectory 1");
      UI->ApplyCommand("/vis/scene/add/trajectories");
      UI->ApplyCommand("/vis/viewer/set/autoRefresh true");
      UI->ApplyCommand("/vis/scene/add/trajectories smooth");
      UI->ApplyCommand("/vis/scene/endOfEventAction accumulate");
      UI->ApplyCommand("/vis/scene/add/hits");
      UI->ApplyCommand("/vis/draw/axes 0 0 0 500 mm");
      UI->ApplyCommand("/vis/sceneHandler/attach");

    }
  //geometry check overlap
  //TODO exeption for intersection - only OpenGL if intersect
    // UI->ApplyCommand("/geometry/test/resolution 10000000");
    // UI->ApplyCommand("/geometry/test/run");

   
  //  // Ensure trajectories are stored & accumulated
  //   UI->ApplyCommand("/tracking/storeTrajectory 1");
 // Start Runs
        G4int nEvents=0;
        G4double EEvents;
        G4double const ChannelWidth = gl.ChannelWidth;

        G4double sigma2 = (gl.isBlur)? 
                          2*sqrt(gl.FWHM1*keV*keV + gl.FWHM2*keV*gl.EGamma)/2.355 :
                          ChannelWidth/2;
        G4double Emin = gl.EGamma - sigma2;
        G4double Emax = gl.EGamma + sigma2;
        G4int iPhotopeak = 0; // counter of events within +/- 2 sigma in the photopeak

        time_t t0, t0calc, t1;
        t0 = time((time_t *)NULL);

        G4int Count = 0;
        for (i=0; i<SpectrumLengthDet; i++)
        {
          SpectrumRaw[i]=0;
          SpectrumBlur[i]=0;
        }
std::cout << "  MARKER DO PICTURE " << gl.DoPicture << std::endl;
// std::cout << "  MARKER Top1 - is detector " << gl.isTop1aDetector << std::endl;

// std::vector<std::string> volumeNames = {
//         "SHLD", "Det", "Src", "UnSrc", "Cover1", 
//         "Cover2", "Cavity", "Top1", "Top2", "Top3",
//         "Bot1", "Bot2", "Bot3" // Add more as needed
//     };

            auto now = std::chrono::system_clock::now();
            std::time_t now_time = std::chrono::system_clock::to_time_t(now);
            std::tm* tm_ptr = std::localtime(&now_time);

            std::ostringstream oss;
            oss << std::put_time(tm_ptr, "%Y_%m_%d_%H_%M_%S"); // Safe for filenames

            G4String outName = std::string("output_")+oss.str();
            for (char& c : outName) {
              if (c == ' ' || c == ':') c = '_';
            }
          	G4AnalysisManager *man = G4AnalysisManager::Instance();
            // man->SetNtupleRowWise(true);          // optional: nicer CSV format
            // 
            if(gl.saveTo ==0)
            {
            man->OpenFile(outName + ".root");
            man->SetNtupleMerging(true);
            man->OpenFile();
            }
            if(gl.saveTo ==1)
            {
            // man->SetVerboseLevel(1);

            man->OpenFile(outName+".csv");  // Will generate output.csv
            man->OpenFile();
            }
            
            G4cout << "Opening ROOT file..." << G4endl;

    man->CreateNtuple("Det", "DetSD");
            man->CreateNtupleIColumn("RunID");
            man->CreateNtupleDColumn("Edep");
            // man->CreateNtupleDColumn("Tinit");
            // man->CreateNtupleDColumn("Tfin");
            man->SetNtupleRowWise(true);          // optional: nicer CSV format
            man->FinishNtuple(0);

for (size_t i = 1; i < gl.DetectorsList.size()+1; i++) {
    std::cout << "Detector " << i << ": " << gl.DetectorsList[i-1] << std::endl;
    man->CreateNtuple(gl.DetectorsList[i-1], gl.DetectorsList[i-1]);
            man->CreateNtupleIColumn("RunID");
            man->CreateNtupleDColumn("Edep");
            // man->CreateNtupleDColumn("Tinit");
            // man->CreateNtupleDColumn("Tfin");
            man->SetNtupleRowWise(true);          // optional: nicer CSV format
            man->FinishNtuple(i);

 
}



if(gl.DoPicture==0 || gl.DoPicture==1){
        for(G4int iRun=0;iRun<gl.numberOfRuns;iRun++)
        {
          runManager->SetNumberOfEventsToBeStored(0);
          SimourgSensDet::numOfEvents = 0;
          G4cout << "DBG INFO BEFORE BEAMON" << gl.DetectorsList.size() << G4endl;
          runManager->BeamOn(1);
#include <algorithm>
#include <numeric>

long double sumEdep = 0.0L;
          
          auto it = gl.TimeDetect.find("Det/DetSD");
          if (it != gl.TimeDetect.end()) {
              const auto &times = it->second.first;
              const auto &edeps = it->second.second;
              long double e = 0;
              if (!times.empty() && times.size() == edeps.size()) {
                  long double tMinAbs = *std::min_element(times.begin(), times.end());
                  sumEdep = std::transform_reduce(
                      times.begin(), times.end(), edeps.begin(), 0.0L,
                      std::plus<>(), [&](long double t, long double e) {
                          long double dt = t - tMinAbs;
                          return (dt >= gl.tMin && dt <= gl.tMax) ? e : 0.0L;
                      });
                      G4cout << " edep " << sumEdep << " minimum Time "<< tMinAbs << G4endl;
              }
              gl.EdepDetect["Det/DetSD"] = sumEdep;
          }
          G4double E = gl.EdepDetect["Det/DetSD"];
//TODO: save all edep from each detector in one file (different columts)
            man->FillNtupleIColumn(0, 0, iRun);
            man->FillNtupleDColumn(0, 1, gl.EdepDetect["Det/DetSD"]);
            // man->FillNtupleDColumn(0, 2, gl.TimeDetect["Det/DetSD"].first);
            // man->FillNtupleDColumn(0, 3, gl.TimeDetect["Det/DetSD"].second);
            man->AddNtupleRow(0);

            for (size_t i = 1; i < gl.DetectorsList.size()+1; i++) {
          sumEdep = 0.0L;
          auto it = gl.TimeDetect.find(gl.DetectorsList[i-1]);
          if (it != gl.TimeDetect.end()) {
            long double e = 0;
              const auto &times = it->second.first;
              const auto &edeps = it->second.second;
              
              if (!times.empty() && times.size() == edeps.size()) {
                  long double tMinAbs = *std::min_element(times.begin(), times.end());
                  sumEdep = std::transform_reduce(
                      times.begin(), times.end(), edeps.begin(), 0.0L,
                      std::plus<>(), [&](long double t, long double e) {
                          long double dt = t - tMinAbs;
                          return (dt >= gl.tMin && dt <= gl.tMax) ? e : 0.0L;
                      });
                      G4cout << " edep " << sumEdep << " minimum Time "<< tMinAbs << G4endl;
                      G4cout << " minT " << gl.tMin << " maxT "<< gl.tMax << G4endl;
                       
              }
              gl.EdepDetect[gl.DetectorsList[i-1]] = sumEdep;
          }
              if(gl.EdepDetect[gl.DetectorsList[i-1]]>0){
            man->FillNtupleIColumn(i, 0, iRun);
            man->FillNtupleDColumn(i, 1, gl.EdepDetect[gl.DetectorsList[i-1]]);
            // man->FillNtupleDColumn(i, 2, gl.TimeDetect[gl.DetectorsList[i-1]].first);
            // man->FillNtupleDColumn(i, 3, gl.TimeDetect[gl.DetectorsList[i-1]].second);
            man->AddNtupleRow(i);}
            }


            // G4cout << "Filling data... " << iRun << "  "  << gl.EdepDetect["Det/DetSD"] << G4endl;
          for (const auto& pair : gl.EdepDetect) {
          G4cout << "IN MAIN Detector: " << pair.first << " | EDEP: " << pair.second << " " << G4endl;
          }
          if (E > 0)
          {
            nEvents++;
        		gl.tFirstHit=0.;
        		G4int iRaw = int(0.5+E/ChannelWidth);
            if( iRaw < 0 ) iRaw=0;
            if( iRaw > (SpectrumLengthDet-1) ) iRaw=SpectrumLengthDet-1;
            SpectrumRaw[iRaw]++;
            
        		if(gl.isBlur)
        		{
        			G4double FWHM = sqrt(gl.FWHM1*keV*keV + gl.FWHM2*keV*E); 
        			G4double EBlur = G4RandGauss::shoot(E, FWHM/2.355); // blurred by gauss
        			if ( Emin < EBlur && EBlur < Emax ) iPhotopeak++;
        			G4int iBlur = int(0.5+EBlur/ChannelWidth);
        			if( iBlur < 0 ) iBlur=0;
        			if( iBlur > (SpectrumLengthDet-1) ) iBlur=SpectrumLengthDet-1;
        			SpectrumBlur[iBlur]++;
        		} else
        		{
        			if ( Emin <= E && E <= Emax ) iPhotopeak++;
        		}
          }

          if(iRun == 0) t0calc = time((time_t*)NULL); // end of pre-procedures, start of calculations

          if( ((iRun+1)%gl.Step == 0) || (iRun == 0) || (iRun+1 == gl.numberOfRuns) )
          {
            t1 = time((time_t *)NULL);
            G4double timeElapsed = difftime(t1,t0);
            G4cout << "###ooooooooooooooooooooooooo decay N: " << (iRun+1) << G4endl;
            G4cout << "### Time elapsed: " << timeElapsed << " seconds" << G4endl;
            G4cout << "### nEvents:    " << nEvents    << ";   EOfHit: " << E/keV << " keV" << G4endl;


          // create spectra
          // SpectrumRaw -- as is (spectrum of absorbed energy)
          // SpectrumBlur -- blurred by energy resolution

            FILE *outputFile1 = fopen("SpectrumRaw.dat", "wt");
            G4int SumDetRaw = 0;
            G4int SumDetThrRaw = 0;
            for (ii=0; ii<SpectrumLengthDet; ii++)
            { 
              G4double ChanVal    = ii*ChannelWidth;
              G4double ChanValKeV = ChanVal/keV;
              fprintf(outputFile1, " %6.1f", ChanValKeV );
              fprintf(outputFile1, " %6i\n", SpectrumRaw[ii]);
              SumDetRaw += SpectrumRaw[ii];
              if( ChanVal >= gl.Threshold ) 
              {
                SumDetThrRaw += SpectrumRaw[ii];
              }
            }
            fclose(outputFile1);

            G4int SumDetBlur = 0; 
        	  G4int SumDetThrBlur = 0;
        		if(gl.isBlur)
        		{
        			FILE *outputFile2 = fopen("SpectrumBlur.dat", "wt");
        		  for (ii=0; ii<SpectrumLengthDet; ii++)
        			{ 
        				G4double ChanVal    = ii*ChannelWidth;
        				G4double ChanValKeV = ChanVal/keV;
                fprintf(outputFile2, " %6.1f", ChanValKeV );
        	      fprintf(outputFile2, " %6i\n", SpectrumBlur[ii] );
        		    SumDetBlur += SpectrumBlur[ii];
        			  if( ChanVal >= gl.Threshold ) 
        				{
                  SumDetThrBlur += SpectrumBlur[ii];
        	      }
        			}
              fclose(outputFile2);
            }

            // ShortLog:
            FILE *outputFile3 = fopen("ShortLog.txt", "wt");

            fprintf(outputFile3, "Simourg Short Log\n");
            fprintf(outputFile3, "Collected:\n");
            fprintf(outputFile3, "%6i events (%6i above threshold) in spectrum of energy deposit;\n", 
              SumDetRaw, SumDetThrRaw );
        		if(gl.isBlur)
        		{
        			fprintf(outputFile3, "%6i events (%6i above threshold) in spectrum of responce function\n", 
        				SumDetBlur,SumDetThrBlur );
        		}
            if(gl.isDecay0) 
        		{
        			fprintf(outputFile3, "Initial decays: %d\n", iRun+1);
        		} else
        		{ // work with fixed energy gammas
        			fprintf(outputFile3, "Initial gammas: %d\n", iRun+1);
              fprintf(outputFile3, "Events in photopeak (%5.2f keV +/- 2sigma): %d between %5.2f and %5.2f keV\n", 
        	      gl.EGamma/keV, iPhotopeak, Emin/keV, Emax/keV);
              fprintf(outputFile3, "Photopeak efficiency: %1.3f\n", iPhotopeak/(iRun+1.));
        		}
            fprintf(outputFile3, "Total efficiency (resp.function): %1.3f\n", SumDetThrBlur/(iRun+1.));
            fprintf(outputFile3, "Time elapsed: %10.1f seconds\n", timeElapsed);
            fprintf(outputFile3, "Pure simulation time elapsed: %10.1f seconds\n", difftime(t1, t0calc));
            //G4cout << "### Time elapsed: " << timeElapsed << " seconds" << G4endl;

            //G4cout << "### nEvents:    " << nEvents << G4endl;

            fclose(outputFile3);
          }

        } // end of the cycle by runs
}
      // Open OpenGL Visualization & Display Tracks
if(gl.DoPicture == 2){
      // Detect interactive mode (if no arguments)
    G4UIExecutive* uiEx = nullptr;
    std::cout << "Argc" << argc << std::endl;
    if (argc == 2) {  
       uiEx = new G4UIExecutive(argc, argv);  // Start interactive mode
    }
    UI->ApplyCommand("/vis/scene/add/trajectories smooth");
    UI->ApplyCommand("/vis/open OGLSQt");
    UI->ApplyCommand("/vis/viewer/reset");
    UI->ApplyCommand("/vis/viewer/flush");
    UI->ApplyCommand("/vis/scene/endOfEventAction accumulate");
    UI->ApplyCommand("/vis/modeling/trajectories/create");  // Ensure track model exists
    UI->ApplyCommand("/vis/scene/add/trajectories smooth");        // Force trajectories to be added
    UI->ApplyCommand("/vis/viewer/update");                 // Refresh view


if (uiEx) {
        uiEx->SessionStart();  
        delete uiEx;
    }
}
  G4cout << "Writing ROOT file..." << G4endl;
man->Write();
G4cout << "File written successfully." << G4endl;
man->CloseFile();
G4cout << "Closing ROOT file..." << G4endl;
  delete visManager;
  delete runManager;
  delete UI;
  // man->Write();

}
