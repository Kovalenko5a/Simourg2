
#include "G4SystemOfUnits.hh"
#include "SimourgMessenger.h"

#include <fstream>
#include "SimourgGlobal.h"

SimourgGlobal::SimourgGlobal()
{

  TimeStampGlob = "Executing " __FILE__ " (compiled " __DATE__ " " __TIME__ ")";
	UI = G4UImanager::GetUIpointer();

  SimMess = new SimourgMessenger(this);

  iFlag=0;
  isDetBox = 0;
  isCover1Box = 0;
  isSrcBox = 0;
	// Do the mandatory volumes exist?
  isSHLD=false;
  isDet=false;
  isSrc=false;
	// Do the optional volumes exist?
  isUnSrc=false;
  isCover2=false;  isCover2X=false;
  isCover1=false;  isCover1X=false;
  isCavity=false;//
  isTop1=false;//
  isTop2=false;//
  isTop3=false;//
  isBot1=false;//
  isBot2=false;//
  isBot3=false;//
  isEGamma=false;// is EGamma defined? 
  isDecay0=false;// is Decay0 file defined?

  saveTo = 0;
  wrlFilesQuantity=10;
  // isDetectorMap["Det"]=0;
  std::vector<std::string> volumeNames = {
        "SHLD", "Det", "Src", "UnSrc", "Cover1", 
        "Cover2", "Cavity", "Top1", "Top2", "Top3",
        "Bot1", "Bot2", "Bot3"
  };
  

  // for (const auto& volume : volumeNames) {
  //       isDetectorMap[volume] = 0;
  // }

  MaterialSHLDDensity = 1.e-20*g/cm3;
  MaterialSHLDElementNames[0] = "N";
  MaterialSHLDFormulaN[0] = 2;
  MaterialSHLDNComponents = 0;
  MaterialDetDensity = 1.e-20*g/cm3;
  MaterialDetElementNames[0] = "N";
  MaterialDetFormulaN[0] = 2;
  MaterialDetNComponents = 0;
  D_Cavity = 0.000*mm;
  ZL_Cavity = 0.000*mm;
  MaterialCavityDensity = 1.e-20*g/cm3;
  MaterialCavityElementNames[0] = "N";
  MaterialCavityFormulaN[0] = 2;
  MaterialCavityNComponents = 0;
  D_Cover1 = 0.000*mm;
  ZL_Cover1 = 0.000*mm;
  MaterialCover1Density = 1.e-20*g/cm3;
  MaterialCover1ElementNames[0] = "N";
  MaterialCover1FormulaN[0] = 2;
  MaterialCover1NComponents = 0;
  D_Cover2 = 0.000*mm;
  ZL_Cover2 = 0.000*mm;
  MaterialCover2Density = 1.e-20*g/cm3;
  MaterialCover2ElementNames[0] = "N";
  MaterialCover2FormulaN[0] = 2;
  MaterialCover2NComponents = 0;
  D_Top1 = 0.000*mm;
  ZL_Top1 = 0.000*mm;
  MaterialTop1Density = 1.e-20*g/cm3;
  MaterialTop1ElementNames[0] = "N";
  MaterialTop1FormulaN[0] = 2;
  MaterialTop1NComponents = 0;
  D_Top2 = 0.000*mm;
  ZL_Top2 = 0.000*mm;
  MaterialTop2Density = 1.e-20*g/cm3;
  MaterialTop2ElementNames[0] = "N";
  MaterialTop2FormulaN[0] = 2;
  MaterialTop2NComponents = 0;
  D_Top3 = 0.000*mm;
  ZL_Top3 = 0.000*mm;
  MaterialTop3Density = 1.e-20*g/cm3;
  MaterialTop3ElementNames[0] = "N";
  MaterialTop3FormulaN[0] = 2;
  MaterialTop3NComponents = 0;
  D_Bot1 = 0.000*mm;
  ZL_Bot1 = 0.000*mm;
  MaterialBot1Density = 1.e-20*g/cm3;
  MaterialBot1ElementNames[0] = "N";
  MaterialBot1FormulaN[0] = 2;
  MaterialBot1NComponents = 0;
  D_Bot2 = 0.000*mm;
  ZL_Bot2 = 0.000*mm;
  MaterialBot2Density = 1.e-20*g/cm3;
  MaterialBot2ElementNames[0] = "N";
  MaterialBot2FormulaN[0] = 2;
  MaterialBot2NComponents = 0;
  D_Bot3 = 0.000*mm;
  ZL_Bot3 = 0.000*mm;
  MaterialBot3Density = 1.e-20*g/cm3;
  MaterialBot3ElementNames[0] = "N";
  MaterialBot3FormulaN[0] = 2;
  MaterialBot3NComponents = 0;
	AlphaBeta=1.;
	tMin=0.*s;
	tMax=1.e50*s;
	tFirstHit=0.;

  AllowIsotropicRotation = 1;

  X_Src = 0.;
  Y_Src = 0.;
  X_UnSrc = 0.;
  Y_UnSrc = 0.;

}

SimourgGlobal::~SimourgGlobal()
{
  if(isDecay0) in.close();
  delete SimMess;
}



void SimourgGlobal::Dump(void)
{
  G4cout << "### nOfRuns:    " << numberOfRuns << "   " << G4endl;
  G4cout << "### RandomSeed: " << RandomSeed << "   " << G4endl;
  if(isDecay0)
  {
    G4cout << "### InFileName: " << Decay0FileName << "   " << G4endl;
  } else
  {
    G4cout << "### EGamma: " << EGamma << "   " << G4endl;
  }
  G4cout << "### " << TimeStampMain << G4endl;
  G4cout << "### " << TimeStampEvAct << G4endl;
  G4cout << "### " << TimeStampGlob << G4endl;
  G4cout << "### " << TimeStampPhyLis << G4endl;
  G4cout << "### " << TimeStampPhyLisEmS << G4endl;
  G4cout << "### " << TimeStampPriGenAct << G4endl;
  G4cout << "### " << TimeStampSensDet << G4endl;
  #ifdef G4VIS_USE
    G4cout << "### " << TimeStampVisMan << G4endl;
  #endif
}

void SimourgGlobal::Dump1(int k)
{

  G4cout << "\noooooooooooooooooooooooooooooo " << k << G4endl;
  G4cout << "### ELowLimit:" << ELowLimit << " keV" << G4endl;
//  G4cout << "### DALowLimit:" << DALowLimit << " nm" << G4endl;
  G4cout << "### DELowLimit:" << DELowLimit << " nm" << G4endl;
  G4cout << "### DGLowLimit:" << DGLowLimit << " nm" << G4endl;

  G4cout << "### nOfRuns:    " << numberOfRuns << "   " << G4endl;
  G4cout << "### RandomSeed: " << RandomSeed << "   " << G4endl;
  G4cout << "oooooooooooooooooooooooooooooo" << G4endl;
}

//TODO: INTERSECTION CHEKER REMOVE
void SimourgGlobal::FineTuning(void)
{
  if(!isDet)  Exception("\n\n\n### Detector is not defined!");
  if(!isSrc)  Exception("\n\n\n### Source is not defined!");
  if( (isEGamma && isDecay0) || (!isEGamma && !isDecay0) )  
    Exception("\n\n\n### EGamma or Decay0File should be defined (and only one of them)!");
  if(D_Det<=0)
  {
    if(XL_Det<=0) Exception("\n\n\n### XL for Detector is not defined!");
    if(YL_Det<=0) Exception("\n\n\n### YL for Detector is not defined!");
    
    if(D_Det<0) Exception("\n\n\n### D<0 for Detector!");
    isDetBox=1;
  } else {isDetBox=0;}
  if(XL_Det<=0 && YL_Det>0) Exception("\n\n\n### XL for Detector is not defined!");
  if(YL_Det<=0 && XL_Det>0) Exception("\n\n\n### YL for Detector is not defined!");
  if(YL_Det>0 && XL_Det>0 && D_Det>0)
  {
    G4cout << "D_Det:" << D_Det << "; XL_Det:" << XL_Det << "; YL_Det:" << YL_Det << G4endl;   
    Exception("\n\n\n### D and the pair (XL, YL) shouldn't be defined simultaneously for Detector!");
  }
  if(isDetBox>=1)
  {
    D_Det=sqrt(XL_Det*XL_Det+YL_Det*YL_Det); // diameter of the circumscribed circle
  } else
  {
    XL_Det=D_Det/sqrt(2.);
    YL_Det=D_Det/sqrt(2.);
  }

  if(MaterialDetDensity <= 0.) 
    Exception("\n\n\n### Density of Detector is not defined!");

  if(MaterialDetNComponents == 0)
    Exception("\n\n\n### Material of Detector is not defined!");


  if(D_Src<=0)
  {
    if(XL_Src<=0) Exception("\n\n\n### XL for Source is not defined!");
    if(YL_Src<=0) Exception("\n\n\n### YL for Source is not defined!");
    
    if(D_Src<0) Exception("\n\n\n### D<0 for Source!");
    isSrcBox=1;
  } else {isSrcBox=0;}
  if(XL_Src<=0 && YL_Src>0) Exception("\n\n\n### XL for Source is not defined!");
  if(YL_Src<=0 && XL_Src>0) Exception("\n\n\n### YL for Source is not defined!");
  if(YL_Src>0 && XL_Src>0 && D_Src>0) 
      Exception("\n\n\n### D and the pair (XL, YL) shouldn't be defined simultaneously for Source!");
  if(isSrcBox>=1)
  {
    D_Src=sqrt(XL_Src*XL_Src+YL_Src*YL_Src); // diameter of the circumscribed circle
  } else
  {
    XL_Src=D_Src/sqrt(2.);
    YL_Src=D_Src/sqrt(2.);
  }

  Src_Radius2=D_Src*D_Src/4.;

  if(D_UnSrc<=0)
  {
    if(isUnSrc && XL_UnSrc<=0) Exception("\n\n\n### XL for UnSource is not defined!");
    if(isUnSrc && YL_UnSrc<=0) Exception("\n\n\n### YL for UnSource is not defined!");
    
    if(D_UnSrc<0) Exception("\n\n\n### D<0 for UnSource!");
    isUnSrcBox=1;
  } else {isUnSrcBox=0;}
  if(isUnSrc && XL_UnSrc<=0 && YL_UnSrc>0) Exception("\n\n\n### XL for UnSource is not defined!");
  if(isUnSrc && YL_UnSrc<=0 && XL_UnSrc>0) Exception("\n\n\n### YL for UnSource is not defined!");
  if(isUnSrc && YL_UnSrc>0 && XL_UnSrc>0 && D_UnSrc>0) 
      Exception("\n\n\n### D and the pair (XL, YL) shouldn't be defined simultaneously for UnSource!");
  if(isUnSrcBox>=1)
  {
    D_UnSrc=sqrt(XL_UnSrc*XL_UnSrc+YL_UnSrc*YL_UnSrc); // diameter of the circumscribed circle
  } else
  {
    XL_UnSrc=D_UnSrc/sqrt(2.);
    YL_UnSrc=D_UnSrc/sqrt(2.);
  }

  UnSrc_Radius2=D_UnSrc*D_UnSrc/4.;

  if(!isCover1) // if there are no explicit definitions for Cover1 in mac-file, define Cover1 as a very thin envelope around Det
  {
    isCover1Box=isDetBox;
    if ( isCover1Box >= 1)
    {

      XL_Cover1 = XL_Det + 0.000*mm;
      YL_Cover1 = YL_Det + 0.000*mm;
    } else
    {
      D_Cover1 = D_Det + 0.000*mm;
    }
    ZL_Cover1 = ZL_Det;
    D_Cover1=sqrt(XL_Cover1*XL_Cover1+YL_Cover1*YL_Cover1); // diameter of the circumscribed circle
    Z_Cover1  = Z_Det;
    MaterialCover1Density=MaterialSHLDDensity;
    for(int i=0; i<MaterialSHLDNComponents; i++)
    {
      MaterialCover1ElementNames[i]=MaterialSHLDElementNames[i];
      MaterialCover1FormulaN[i]=MaterialSHLDFormulaN[i];
    }
    MaterialCover1NComponents=MaterialSHLDNComponents;
    isCover1X=true;
  }else
  {
    if(MaterialCover1NComponents==0) Exception("\n\n\n### Material for Cover1 is not defined!");
    if(MaterialCover1Density<=0) Exception("\n\n\n### Density for Cover1 is not defined!");
    if(D_Cover1<=0)
    {
      if(XL_Cover1<=0) Exception("\n\n\n### XL for Cover1 is not defined!");
      if(YL_Cover1<=0) Exception("\n\n\n### YL for Cover1 is not defined!");
      if(D_Cover1<0) Exception("\n\n\n### D<0 for Cover1!");
      isCover1Box=1;
    } else {isCover1Box=0;}
    
    if(ZL_Cover1<=0) Exception("\n\n\n### ZL for Cover1 is not defined!");
    if(YL_Cover1>0 && XL_Cover1>0 && D_Cover1>0) 
        Exception("\n\n\n### D and the pair (XL, YL) shouldn't be defined simultaneously for Cover1!");
  }
  if(isCover1Box>=1)
  {
    D_Cover1=sqrt(XL_Cover1*XL_Cover1+YL_Cover1*YL_Cover1); // diameter of the circumscribed circle
  } else
  {
    XL_Cover1=D_Cover1/sqrt(2.);
    YL_Cover1=D_Cover1/sqrt(2.);
  }

  if(!isCover2) // if there are no explicit definitions for Cover2 in mac-file, define Cover2 as a very thin envelope around Det
  {
    isCover2Box=isCover1Box;
    if ( isCover2Box >= 1)
    {

      XL_Cover2 = XL_Cover1 + 0.000*mm;
      YL_Cover2 = YL_Cover1 + 0.000*mm;
    } else
    {
      D_Cover2 = D_Cover1 + 0.000*mm;
    }
    ZL_Cover2 = ZL_Cover1;
    D_Cover2=sqrt(XL_Cover2*XL_Cover2+YL_Cover2*YL_Cover2); // diameter of the circumscribed circle
    Z_Cover2  = Z_Cover1;
    MaterialCover2Density=MaterialSHLDDensity;
    for(int i=0; i<MaterialSHLDNComponents; i++)
    {
      MaterialCover2ElementNames[i]=MaterialSHLDElementNames[i];
      MaterialCover2FormulaN[i]=MaterialSHLDFormulaN[i];
    }
    MaterialCover2NComponents=MaterialSHLDNComponents;
    isCover2X=true;
  }else
  {
    if(MaterialCover2NComponents==0) Exception("\n\n\n### Material for Cover2 is not defined!");
    if(MaterialCover2Density<=0) Exception("\n\n\n### Density for Cover2 is not defined!");
    if(D_Cover2<=0)
    {
      if(XL_Cover2<=0) Exception("\n\n\n### XL for Cover2 is not defined!");
      if(YL_Cover2<=0) Exception("\n\n\n### YL for Cover2 is not defined!");
      if(D_Cover2<0) Exception("\n\n\n### D<0 for Cover2!");
      isCover2Box=1;
    } else {isCover2Box=0;}
    
    if(ZL_Cover2<=0) Exception("\n\n\n### ZL for Cover2 is not defined!");
    //if(YL_Cover2>0 && XL_Cover2>0 && D_Cover2>0) 
    //    Exception("\n\n\n### D and the pair (XL, YL) shouldn't be defined simultaneously for Cover2!");
  }
  if(isCover2Box>=1)
  {
    D_Cover2=sqrt(XL_Cover2*XL_Cover2+YL_Cover2*YL_Cover2); // diameter of the circumscribed circle
  } else
  {
    XL_Cover2=D_Cover2/sqrt(2.);
    YL_Cover2=D_Cover2/sqrt(2.);
  }

  if(!isSHLD) // if there are no explicit definitions for Shield in the mac-file, define Shield as 
              // a vacuum-filled cylinder containing all other volumes. In this case, the minimal distance 
              // between the external border of the Shield and the external border of any 
              // other volume is 0.5 cm.
  {
    G4double maxZL= ZL_Cover2+ 1*cm;
    G4double maxD = D_Cover2 + 1*cm;
    G4double maxX_Src= abs(X_Src) + XL_Src/2;
    G4double maxY_Src= abs(Y_Src) + YL_Src/2;
    G4double maxD_Src= 2*sqrt(maxX_Src*maxX_Src + maxY_Src*maxY_Src) + 1*cm;
    if(maxD_Src > maxD )     maxD = maxD_Src;
    if(2*abs(Z_Src) + ZL_Src + 1*cm > maxZL )       maxZL = 2*abs(Z_Src)  + ZL_Src + 1*cm;
    if(2*abs(Z_Det) + ZL_Det + 1*cm > maxZL )       maxZL = 2*abs(Z_Det)  + ZL_Det + 1*cm;
    if(isTop1)
    {
      if(2*abs(Z_Top1) + ZL_Top1 + 1*cm > maxZL/2 ) maxZL = 2*abs(Z_Top1) + ZL_Top1+ 1*cm;
      if(D_Top1 + 1*cm > maxD ) maxD = D_Top1 + 1*cm;
    }
    if(isTop2)
    {
      if(2*abs(Z_Top2) + ZL_Top2 + 1*cm > maxZL/2 ) maxZL = 2*abs(Z_Top2) + ZL_Top2+ 1*cm;
      if(D_Top2 + 1*cm > maxD ) maxD = D_Top2 + 1*cm;
    }
    if(isTop3)
    {
      if(2*abs(Z_Top3) + ZL_Top3 + 1*cm > maxZL/2 ) maxZL = 2*abs(Z_Top3) + ZL_Top3+ 1*cm;
      if(D_Top3 + 1*cm > maxD ) maxD = D_Top3 + 1*cm;
    }
    if(isBot1)
    {
      if(2*abs(Z_Bot1) + ZL_Bot1 + 1*cm > maxZL/2 ) maxZL = 2*abs(Z_Bot1) + ZL_Bot1+ 1*cm;
      if(D_Bot1 + 1*cm > maxD ) maxD = D_Bot1 + 1*cm;
    }
    if(isBot2)
    {
      if(2*abs(Z_Bot2) + ZL_Bot2 + 1*cm > maxZL/2 ) maxZL = 2*abs(Z_Bot2) + ZL_Bot2+ 1*cm;
      if(D_Bot2 + 1*cm > maxD ) maxD = D_Bot2 + 1*cm;
    }
    if(isBot3)
    {
      if(2*abs(Z_Bot3) + ZL_Bot3 + 1*cm > maxZL/2 ) maxZL = 2*abs(Z_Bot3) + ZL_Bot3+ 1*cm;
      if(D_Bot3 + 1*cm > maxD ) maxD = D_Bot3 + 1*cm;
    }

    ZL_SHLD = maxZL;
    D_SHLD  = maxD;
    isSHLD  = true;
    
  }
  if(!isCavity)
  { // create Cavity with negligible sizes and filled by material of the detector.
    /*D_Cavity  = 0.001*mm;
    ZL_Cavity = 0.001*mm;
    Z_Cavity  = Z_Det;
    MaterialCavityDensity=MaterialDetDensity;
    for(int i=0; i<MaterialDetNComponents; i++)
    {
      MaterialCavityElementNames[i]=MaterialDetElementNames[i];
      MaterialCavityFormulaN[i]=MaterialDetFormulaN[i];
    }
    MaterialCavityNComponents=MaterialDetNComponents;
    isCavity=true;*/
  }else
  { //cavity is defined, but material is not:
    if(MaterialCavityNComponents==0) MaterialCavityNComponents=1; // suppose vacuum
    //cavity is defined, but density is not:
    if(MaterialCavityDensity < 0.)
      Exception("\n\n\n### Density of Cavity is not defined!");
  }
  if(MaterialSHLDNComponents == 0) MaterialSHLDNComponents=1;
  if(MaterialCover2NComponents == 0) MaterialCover2NComponents=1;
  if(MaterialCover1NComponents == 0) MaterialCover1NComponents=1;
  if(MaterialCavityNComponents == 0) MaterialCavityNComponents=1;
  if(MaterialTop1NComponents == 0) MaterialTop1NComponents=1;
  if(MaterialTop2NComponents == 0) MaterialTop2NComponents=1;
  if(MaterialTop3NComponents == 0) MaterialTop3NComponents=1;
  if(MaterialBot1NComponents == 0) MaterialBot1NComponents=1;
  if(MaterialBot2NComponents == 0) MaterialBot2NComponents=1;
  if(MaterialBot3NComponents == 0) MaterialBot3NComponents=1;

  if(isTop1 && MaterialTop1Density <= 0)
  {
    MaterialTop1Density=MaterialSHLDDensity;
    if(VerboseAll>0) 
      G4cout<< "### Density of Top1 is not defined; assumed equal density of Shield" <<G4endl;
  }
  if(isTop2 && MaterialTop2Density <= 0)
  {
    MaterialTop2Density=MaterialSHLDDensity;
    if(VerboseAll>0) 
      G4cout<< "### Density of Top2 is not defined; assumed equal density of Shield" <<G4endl;
  }
  if(isTop3 && MaterialTop3Density <= 0)
  {
    MaterialTop3Density=MaterialSHLDDensity;
    if(VerboseAll>0) 
      G4cout<< "### Density of Top3 is not defined; assumed equal density of Shield" <<G4endl;
  }
  if(isBot1 && MaterialBot1Density <= 0)
  {
    MaterialBot1Density=MaterialSHLDDensity;
    if(VerboseAll>0) 
      G4cout<< "### Density of Bot1 is not defined; assumed equal density of Shield" <<G4endl;
  }
  if(isBot2 && MaterialBot2Density <= 0)
  {
    MaterialBot2Density=MaterialSHLDDensity;
    if(VerboseAll>0) 
      G4cout<< "### Density of Bot2 is not defined; assumed equal density of Shield" <<G4endl;
  }
  if(isBot3 && MaterialBot3Density <= 0)
  {
    MaterialBot3Density=MaterialSHLDDensity;
    if(VerboseAll>0) 
      G4cout<< "### Density of Bot3 is not defined; assumed equal density of Shield" <<G4endl;
  }

  G4cout << "### Checking geometry: " << G4endl;

  // G4double SX = abs(X_Src)+XL_Src/2;// SX, SY -- max coordinates of Src points
  // G4double SY = abs(Y_Src)+YL_Src/2;//
	// /*G4cout << "############ SX:" << SX <<" SY:" << SY << " Z_Src:" << Z_Src << " ZL_Src:" << ZL_Src << " ZL_SHLD:" << ZL_SHLD << 
	// 					" isSrcBox:" << isSrcBox << " X,Y_Src:" << X_Src <<" " << Y_Src << " D_Src:" << D_Src << " D_SHLD:" << D_SHLD << G4endl;*/
  // if( (abs(Z_Src)+ZL_Src/2 > ZL_SHLD/2) || 
  //     ((isSrcBox>=1)&&
  //       ( sqrt(SX*SX+SY*SY)>D_SHLD/2)) ||
  //     ((isSrcBox==0)&&
  //       ( sqrt(X_Src*X_Src+Y_Src*Y_Src)+D_Src/2 > D_SHLD/2)) )
  //   Exception("\n\n\n### Src: outside the shield!");

  // if( isTop1 && ((abs(Z_Top1)+ZL_Top1/2 > ZL_SHLD/2) || (D_Top1 > D_SHLD)) )
  //   Exception("\n\n\n### Top1: outside the shield!");
  // if( isTop2 && ((abs(Z_Top2)+ZL_Top2/2 > ZL_SHLD/2) || (D_Top2 > D_SHLD)) )
  //   Exception("\n\n\n### Top2: outside the shield!");
  // if( isTop3 && ((abs(Z_Top3)+ZL_Top3/2 > ZL_SHLD/2) || (D_Top3 > D_SHLD)) )
  //   Exception("\n\n\n### Top3: outside the shield!");
  // if( isBot1 && ((abs(Z_Bot1)+ZL_Bot1/2 > ZL_SHLD/2) || (D_Bot1 > D_SHLD)) )
  //   Exception("\n\n\n### Bot1: outside the shield!");
  // if( isBot2 && ((abs(Z_Bot2)+ZL_Bot2/2 > ZL_SHLD/2) || (D_Bot2 > D_SHLD)) )
  //   Exception("\n\n\n### Bot2: outside the shield!");
  // if( isBot3 && ((abs(Z_Bot3)+ZL_Bot3/2 > ZL_SHLD/2) || (D_Bot3 > D_SHLD)) )
  //   Exception("\n\n\n### Bot3: outside the shield!");

  // if( isCover2 &&
	// 		(	(abs(Z_Cover2)+ZL_Cover2/2 > ZL_SHLD/2) || 
	// 			((isCover2Box>=1)&&( sqrt(XL_Cover2*XL_Cover2+YL_Cover2*YL_Cover2)>D_SHLD))||
	// 			((isCover2Box==0)&&( XL_Cover2 > D_SHLD))
	// 		)
  //   ) Exception("\n\n\n### Cover2: outside the shield!");
  // //if( (abs(Z_Cover1)+ZL_Cover1/2 > ZL_Cover2/2) || 
  // //    ((isCover1Box>=1)&&( sqrt(XL_Cover1*XL_Cover1+YL_Cover1*YL_Cover1)>D_Cover2))||
  // //    ((isCover1Box==0)&&( XL_Cover1 > D_Cover2)) )
  // //  Exception("\n\n\n### Cover1: outside the Cover2!");
  // if( isCover1 &&
	// 		(	( Z_Cover1 + ZL_Cover1/2 > Z_Cover2 + ZL_Cover2/2) || 
	// 			( Z_Cover1 - ZL_Cover1/2 < Z_Cover2 - ZL_Cover2/2) || 
	// 			( ( ((isCover1Box>=1)&&(isCover2Box>=1)) || (isCover1Box==0) )
	// 					               &&( (XL_Cover1>XL_Cover2) || (YL_Cover1>YL_Cover2))) ||
	// 			((isCover1Box>=1)&&(isCover2Box==0)
  //                      &&( sqrt(XL_Cover1*XL_Cover1+YL_Cover1*YL_Cover1) > XL_Cover2))
	// 		)
  //   ) Exception("\n\n\n### Cover1: outside the Cover2!");
  // if(isCover1)
	// {
	// 	if(	( Z_Det + ZL_Det/2 > Z_Cover1 + ZL_Cover1/2) || 
	// 			( Z_Det - ZL_Det/2 < Z_Cover1 - ZL_Cover1/2) || 
	// 			( ( ((isDetBox>=1)&&(isCover1Box>=1)) || (isDetBox==0) )
	// 				               &&( (XL_Det>XL_Cover1) || (YL_Det>YL_Cover1))) ||
	// 			((isDetBox>=1)&&(isCover1Box==0)
	// 				               &&( sqrt(XL_Det*XL_Det+YL_Det*YL_Det) > XL_Cover1))
	// 		) Exception("\n\n\n### Detector: outside the Cover1!");
	// } else if(isCover2)
	// {
	// 	if(	( Z_Det + ZL_Det/2 > Z_Cover2 + ZL_Cover2/2) || 
	// 			( Z_Det - ZL_Det/2 < Z_Cover2 - ZL_Cover2/2) || 
	// 			( ( ((isDetBox>=1)&&(isCover2Box>=1)) || (isDetBox==0) )
	// 				               &&( (XL_Det>XL_Cover2) || (YL_Det>YL_Cover2))) ||
	// 			((isDetBox>=1)&&(isCover2Box==0)
	// 				               &&( sqrt(XL_Det*XL_Det+YL_Det*YL_Det) > XL_Cover2))
	// 		) Exception("\n\n\n### Detector: outside the Cover2!");
	// } else
	// { // no Cover2 and no Cover1
	// 	if( 	(abs(Z_Det)+ZL_Det/2 > ZL_SHLD/2) || 
	// 				((isDetBox>=1)&&( sqrt(XL_Det*XL_Det+YL_Det*YL_Det)>D_SHLD))||
	// 				((isDetBox==0)&&( XL_Det > D_SHLD))
	// 		) Exception("\n\n\n### Detector: outside the shield!");
	// }
  // if( isCavity && 
	// 		(	( Z_Cavity + ZL_Cavity/2 > Z_Det + ZL_Det/2) || 
	// 			( Z_Cavity - ZL_Cavity/2 < Z_Det - ZL_Det/2) || 
	// 			( D_Cavity > D_Det  && isDetBox==0 ) || 
	// 			( D_Cavity > XL_Det && isDetBox>=1 ) || 
	// 			( D_Cavity > YL_Det && isDetBox>=1 ) 
	// 		)
	// 	) Exception("\n\n\n### Cavity: outside the Detector!");

  // if( isTop1 && (abs(Z_Top1-Z_Cover2) < ZL_Top1/2 + ZL_Cover2/2) )
  //   Exception("\n\n\n### Top1: overlaps the Cover2!");
  // if( isTop2 && (abs(Z_Top2-Z_Cover2) < ZL_Top2/2 + ZL_Cover2/2) )
  //   Exception("\n\n\n### Top2: overlaps the Cover2!");
  // if( isTop3 && (abs(Z_Top3-Z_Cover2) < ZL_Top3/2 + ZL_Cover2/2) )
  //   Exception("\n\n\n### Top3: overlaps the Cover2!");
  // if( isBot1 && (abs(Z_Bot1-Z_Cover2) < ZL_Bot1/2 + ZL_Cover2/2) )
  //   Exception("\n\n\n### Bot1: overlaps the Cover2!");
  // if( isBot2 && (abs(Z_Bot2-Z_Cover2) < ZL_Bot2/2 + ZL_Cover2/2) )
  //   Exception("\n\n\n### Bot2: overlaps the Cover2!");
  // if( isBot3 && (abs(Z_Bot3-Z_Cover2) < ZL_Bot3/2 + ZL_Cover2/2) )
  //   Exception("\n\n\n### Bot3: overlaps the Cover2!");

  // if( isTop1 && isTop2 && (abs(Z_Top1-Z_Top2) < ZL_Top1/2 + ZL_Top2/2) )
  //   Exception("\n\n\n### Top1: overlaps the Top2!");
  // if( isTop1 && isTop3 && (abs(Z_Top1-Z_Top3) < ZL_Top1/2 + ZL_Top3/2) )
  //   Exception("\n\n\n### Top1: overlaps the Top3!");
  // if( isTop2 && isTop3 && (abs(Z_Top2-Z_Top3) < ZL_Top2/2 + ZL_Top3/2) )
  //   Exception("\n\n\n### Top2: overlaps the Top3!");
  // if( isBot1 && isBot2 && (abs(Z_Bot1-Z_Bot2) < ZL_Bot1/2 + ZL_Bot2/2) )
  //   Exception("\n\n\n### Bot1: overlaps the Bot2!");
  // if( isBot1 && isBot3 && (abs(Z_Bot1-Z_Bot3) < ZL_Bot1/2 + ZL_Bot3/2) )
  //   Exception("\n\n\n### Bot1: overlaps the Bot3!");
  // if( isBot2 && isBot3 && (abs(Z_Bot2-Z_Bot3) < ZL_Bot2/2 + ZL_Bot3/2) )
  //   Exception("\n\n\n### Bot2: overlaps the Bot3!");

  // if( isTop1 && isBot1 && (abs(Z_Top1-Z_Bot1) < ZL_Top1/2 + ZL_Bot1/2) )
  //   Exception("\n\n\n### Top1: overlaps the Bot1!");
  // if( isTop1 && isBot2 && (abs(Z_Top1-Z_Bot2) < ZL_Top1/2 + ZL_Bot2/2) )
  //   Exception("\n\n\n### Top1: overlaps the Bot2!");
  // if( isTop1 && isBot3 && (abs(Z_Top1-Z_Bot3) < ZL_Top1/2 + ZL_Bot3/2) )
  //   Exception("\n\n\n### Top1: overlaps the Bot3!");
  // if( isTop2 && isBot1 && (abs(Z_Top2-Z_Bot1) < ZL_Top2/2 + ZL_Bot1/2) )
  //   Exception("\n\n\n### Top2: overlaps the Bot1!");
  // if( isTop2 && isBot2 && (abs(Z_Top2-Z_Bot2) < ZL_Top2/2 + ZL_Bot2/2) )
  //   Exception("\n\n\n### Top2: overlaps the Bot2!");
  // if( isTop2 && isBot3 && (abs(Z_Top2-Z_Bot3) < ZL_Top2/2 + ZL_Bot3/2) )
  //   Exception("\n\n\n### Top2: overlaps the Bot3!");
  // if( isTop3 && isBot1 && (abs(Z_Top3-Z_Bot1) < ZL_Top3/2 + ZL_Bot1/2) )
  //   Exception("\n\n\n### Top3: overlaps the Bot1!");
  // if( isTop3 && isBot2 && (abs(Z_Top3-Z_Bot2) < ZL_Top3/2 + ZL_Bot2/2) )
  //   Exception("\n\n\n### Top3: overlaps the Bot2!");
  // if( isTop3 && isBot3 && (abs(Z_Top3-Z_Bot3) < ZL_Top3/2 + ZL_Bot3/2) )
  //   Exception("\n\n\n### Top3: overlaps the Bot3!");

	if( tMin > tMax)
    Exception("\n\n\n### tMin > tMax!");
  
  G4cout << "[OK]" << G4endl;

}

void SimourgGlobal::Exception(const char* comment)
{
  G4Exception( "SimourgGlobal::FineTuning()", "", FatalException, comment);

}
