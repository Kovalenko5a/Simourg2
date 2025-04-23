rem This bat file is for start Simourg with setting the path to 
rem the datafiles (variable G4LEDATA should be set).
rem Macro file *.mac should be the first parameter in the command line;
rem here it is SimourgSampleBIG.mac, where all the possible volumes
rem are included. Your can edit this file or create your own macro files.
rem Examples of running this bat-file:
rem
rem C:\> Simourg_1.4.bat log123.txt 
rem (this will create the log file log123.txt)
rem
rem C:\> Simourg_1.4.bat con
rem (this will redirect all the output to your screen)

set G4ABLADATA=D:\Data\G4ABLA3.1
set G4ENSDFSTATEDATA=D:\Data\G4ENSDFSTATE2.3
set G4INCLDATA=D:\Data\G4INCL1.0
set G4LEDATA=D:\Data\G4EMLOW7.13
set G4LEVELGAMMADATA=D:\Data\PhotonEvaporation5.7
set G4NEUTRONHPDATA=D:\Data\G4NDL4.6
set G4PARTICLEXSDATA=D:\Data\G4PARTICLEXS3.1.1
set G4PIIDATA=D:\Data\G4PII1.3
set G4RADIOACTIVEDATA=D:\Data\RadioactiveDecay5.6
set G4REALSURFACEDATA=D:\Data\RealSurface2.2
set G4SAIDXSDATA=D:\Data\G4SAIDDATA2.0
set G4WORKDIR=D:\G4WORK

Simourg_1.4.exe SimourgSampleSMALL.mac >%1
