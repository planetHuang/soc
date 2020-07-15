***This file is a brief documentation of the NDP026C data archive.                         
The full documentation is contained in the file ndp026c.pdf, requiring
Adobe Acrobat Reader.  Another file, ndp026c.txt, a flat ASCII file, 
contains all of the text documentation of ndp026c.pdf, without any 
tables and figures.***

PLEASE NOTE:

On March 20, 2000 this page and the global
cloudiness data set were updated to reflect the addition of 12 monthly files of
ship reports for 1996.  Previously, the ship data extended only through 1995.

On April 28, 2009 - This page and the global
cloudiness data set and documentation updated with an additional 11 years
(through 2008) of ship reports.  Added a new data directory
(ship_199801_200812) containing the reports.
Please see the new APPENDIX U in ndp026c.pdf for important
details regarding record format differences of these new data files.

------------------------------------------------------------------------------

Hahn, C.J., and S.G. Warren, 1999: Extended Edited Synoptic Cloud Reports from  
Ships and Land Stations Over the Globe, 1952-1996.  ORNL/CDIAC-123, NDP026C,     
Carbon Dioxide Information Analysis Center, Oak Ridge National Laboratory,
Oak Ridge, Tennessee. doi: 10.3334/CDIAC/cli.ndp026c      
(Also available from Data Support Section, National Center for Atmospheric      
Research, Boulder, CO.)                                                         
                                                                                
Abstract:                                                                       

Surface synoptic weather reports for the entire globe, gathered from various  
available data sets, were processed, edited, and rewritten to provide a single  
dataset of individual observations of clouds, spanning the 45 years 1952-1996   
for ship data and the 26 years 1971-1996 for land station data.  In addition    
to the cloud portion of the synoptic report, each edited report also includes   
the associated pressure, present weather, wind, air temperature, and dew point  
(and sea surface temperature over oceans).  This data set is called the         
"Extended Edited Cloud Report Archive" (EECRA).                                 
                                                                                
Reports from the source data sets that did not meet certain quality control     
standards were rejected for the EECRA.  Minor correctable inconsistencies       
within reports were edited for consistency.  Cases of "sky obscured" were       
interpreted by reference to the present-weather code as to whether they         
indicated fog, rain, snow, or thunderstorm.  Special coding was added to        
indicate probable nimbostratus clouds which are not specifically coded for in   
the standard synoptic code.  Any changes made to an original report are also    
noted in the archived edited report so that the original report can be          
reconstructed if desired.  This "extended edited cloud report" also includes    
the amounts, either inferred or directly reported, of low, middle, and          
high clouds, both overlapped and non-overlapped amounts.  The relative lunar    
illuminance and the solar zenith angle associated with each report are also     
given, as well as an indicator that tells whether our recommended               
illuminance criterion was satisfied so that the "night-detection bias"          
for clouds can be minimized.                                                    
                                                                                
The EECRA contains over 72 million cloud observations from ships and 311 million     
from land stations.  Each report is 80 characters in length.  The archive       
consists of 841 files of edited synoptic reports, one file for each month of    
data for land and ocean separately, and 4 ancillary files which provide         
important information about reporting characteristics of the land stations.     
                                                                                
  This data set will be useful for applications such as:  (1) development of    
user-defined cloud climatologies for particular subtypes of clouds, or for      
different temporal and spatial resolution than we have chosen for our atlases,  
(2) in comparison of satellite cloud retrievals with surface observations, to   
help diagnose difficulties in cloud identification from satellite, and (3) to   
relate formation of individual types of clouds to their meteorological          
environments.                                                                   
_____                                                                               
It is important that the user obtain the full documentation from:               
                                                                                
  Carbon Dioxide Information Analysis Center                                    
  Oak Ridge National Laboratory                                                 
  Post Office Box 2008                                                          
  Oak Ridge, TN  37831-6335, U.S.A.                                             
  Telephone (423) 574-3645                                                      
  http://cdiac.ess-dive.lbl.gov/epubs/ndp/ndp026c/ndp026c.html
                                                                                
             or                                                                 
                                                                                
  Data Support Section                                                          
  National Center for Atmospheric Research                                      
  Boulder, CO  80307, U.S.A.                                                    
  Telephone (303) 497-1215                                                      
_____                                                                               
The full documentation contains important information about:                     
  avoiding the clear-sky and sky-obscured biases for cloud types,               
  computation of cloud type frequencies and amount-when-present,                
  amount-when-present of altostratus clouds for regions of China, 1971-79, and  
  illuminance criteria for avoiding the night-detection bias.                   
It also contains valuable information about reporting characteristics of land   
stations and describes the four ancillary files provided with this data set.    
                                                                                
This brief documentation consists of Tables 1,2,3,9 from the full documentation:
  Table 1. Cloud Information Contained in Synoptic Weather Reports              
  Table 2. Cloud and Weather Type Definitions Used                              
  Table 3. Change Codes for Edited Cloud Reports                                
  Table 9. Contents and Format of the 80-character Extended Edited Cloud Report.
                                                                                
*********-*********-*********-*********-*********-*********-*********-*********-
       Table 1. Cloud Information Contained in Synoptic Weather Reports         
       ________________________________________________________________         
        Symbol       Meaning                       Codes#                       
       ________________________________________________________________         
          N          total cloud cover             0-8 oktas                    
                                                    9= sky obscured             
          Nh         lower* cloud amount           0-8 oktas                    
          h          lower* cloud base height      0-9                          
          CL         low cloud type                0-9                          
          CM         middle cloud type             0-9                          
          CH         high cloud type               0-9                          
          ww         present weather               00-99                        
          Ix         present weather indicator     1-6                          
       ________________________________________________________________         
       # Any category for which information is lacking to the observer          
         is coded as "/" (and converted to "-1" in the EECRA).                  
       * The "lower" cloud is the middle level if there are no low clouds.      
                                                                                
*********-*********-*********-*********-*********-*********-*********-*********-
Table 2.  Cloud and Weather Type Definitions Used                               
________________________________________________________________________________
      Shorthand                                                         Extended
Level notation   Meaning                 Synoptic codes                  codes# 
________________________________________________________________________________
                                                                                
      Tcc        total cloud cover        N = 0-9                         0-8   
                                                                                
      Clr        completely clear sky     N = 0                                 
                                                                                
      Ppt        precipitation            ww= 50-75,77,79,80-99                 
        D          drizzle                    50-59                             
        R          rain                       60-69                             
        S          snow                       70-75,77,79                       
        Ts         thunderstorm,shower                    80-99                 
                                                                                
Low                                       CL=                                   
      Fo         sky obscured by fog         / with N=9 and ww=F*          11   
      St         stratus                     6,7                                
      Sc         stratocumulus               4,5,8                              
      Cu         cumulus                     1,2                                
      Cb         cumulonimbus                3,9,                               
                                                  or N=9 with ww=Ts        10   
                                                                                
Mid                                       CM=                                   
      Ns         nimbostratus                2,7, or N=9, with ww=DRS   12,11,10
                                             /  with ww=DRS and CL=0,7     10   
                                             /  with ww= RS and CL=4-8     10   
      As         altostratus                 1; 2 if not DRS                    
      Ac         altocumulus                 3,4,5,6,8,9; 7 if not DRS          
                                                                                
High                                      CH=                                   
      Cs         cirrostratus                5,6,7,8                            
      Cic        cirrus, cirrocumulus        1,4,9                              
      Cid        dense cirrus                2,3                                
                                                                                
________________________________________________________________________________
# Extended codes shown where they differ from synoptic codes.  In the extended  
  code the value "-1", rather than "/", is used to signify missing information. 
* F represents the fog codes ww=10-12,40-49.                                    
                                                                                
*********-*********-*********-*********-*********-*********-*********-*********-
 Table 3. Change Codes for Edited Cloud Reports                                 
 _________________________________________________________________________      
                                                        Occurrence (%)          
                                                        Land      Ocean         
 IC* Case (brief description**)       Changes made#   all light  all light      
 __  ________________________________ ______________ __________ __________      
  0                                   none##          87.4 87.4  87.2 86.9      
  1  N=9 with ppt or fog              N=8; CL=10,11    1.6  1.6   2.6  2.6      
                                           or CM=10                             
  2  Nh=0 with CM>0 and CL=0          Nh=N             0.8  0.8   0.5  0.5      
  3  Nh=N with CH>0 and CL=CM=0       Nh=0             0.1  0.1   0.2  0.2      
  4  Nh<N where should be Nh=N        Nh=/             0.3  0.4   0.6  0.6      
  5  CL =/ with CM or CH              CM,CH =/         0.1  0.1   0.5  0.5      
  6  CM or CH miscoded as 0           CM or CH =/      3.2  3.5   3.7  4.1      
  7  CM=7,2 for Ns                    CM=11,12         3.7  3.5   1.1  1.2      
  8  CM=/   for Ns                    CM=10            2.4  2.2   1.8  1.9      
  9  CM or CH miscoded as /           CM or CH =0      0.3  0.3   1.8  1.5      
 _________________________________________________________________________      
  * Also order in which changes are made, but IC=9 is recorded only if no       
      previous change was made.                                                 
 ** See Table 4 of full documentation for details.                              
  # In the EECRA the value "-1" is used to signify "/".                         
 ## Cases of Nh=CL=CM=CH=/ with N=0 were set to Nh=CL=CM=CH=0 in post-1981 data.
    These were not considered to be changes.                                    
                                                                                
*********-*********-*********-*********-*********-*********-*********-*********-
Table 9. Contents and Format* of the 80-character EXTENDED EDITED CLOUD REPORT  
________________________________________________________________________________
                                                Num   Minimum   Maximum  Missing
Item Description#                 Abbreviation  char    value     value   value 
________________________________________________________________________________
                                                                                
 !1   year,month,day,hour          yr,mn,dy,hr    8   51120100  96113021    none 
                                                                                
 2   sky brightness indicator        IB          1          0         1    none 
                                                                                
 !3   latitude  x100                  LAT         5      -9000      9000    none 
                                                                                
 !!4   longitude x100                  LON         5          0     36000    none 
                                                                                
 !5   land: station number            ID          5      01000     98999    none 
     ship: source deck, ship type                        1100      9999  none,9 
                                                                                
 6   land/ocean indicator            LO          1          1         2    none 
                                                                                
 !7   present weather                 ww          2          0        99      -1 
                                                                                
 8   total cloud cover               N           1          0         8    none 
                                                                                
 9   lower cloud amount              Nh          2         -1         8      -1 
                                                                                
10   lower cloud base height         h           2         -1         9      -1 
                                                                                
11   low cloud type                  CL          2         -1        11      -1 
                                                                                
12   middle cloud type               CM          2         -1        12      -1 
                                                                                
13   high cloud type                 CH          2         -1         9      -1 
                                                                                
!14   middle cloud amount x100        AM          3          0       800     900 
                                                                                
!15   high cloud amount x100          AH          3          0       800     900 
                                                                                
     non-overlapped amounts:                                                    
                                                                                
16     middle cloud amount           UM          1          0         8       9 
                                                                                
17     high cloud amount             UH          1          0         8       9 
                                                                                
18   change code                     IC          2          0         9    none 
                                                                                
!19   solar altitude (deg x10)        SA          4       -900       900    none 
                                                                                
!20   relative lunar illuminance x100 RI          4       -110       117    none 
--------------------------------------------------------------------------------
!21   sea level pressure (mb x10)     SLP         5       9000,L   10999,L    -1 
                                                         8700,S   10746,S       
                                                                                
!22   wind speed (ms-1 x10)           WS          3          0       999      -1 
                                                                                
23   wind direction (degrees)        WD          3          0       361      -1 
                                                                                
24   air temperature (C x10)         AT          4       -949,L     599,L   900 
                                                         -880,S     580,S       
                                                                                
25   dew point depression (C x10)    DD          3          0       700     900 
                                                                                
26   Land: station elevation (m)     EL          4       -350      4877    9000 
     Ship: sea surface temp (C x10)  SST                  -50       400         
                                                                                
27   wind speed indicator            IW          1          0         1       9 
                                                                                
!28   Land: sea level pressure flag   IP          1          0         2       9 
     Ship: cloud height indicator    IH                     0         1         
________________________________________________________________________________
* Where values differ, L=Land, S=Ship.  See Section 4.1 for detailed discussion.
# Item notes:                                                                   
 2                                                                              
   A value of 0 indicates that the night sky is too dark for adequate detection.
   of clouds; 1 indicates that the illuminance criterion is met.  (See also     
   items 19-20.)                                                                
 6                                                                              
   A value of 1 signifies land data, 2 signifies ship data.                     
14-17                                                                           
   Upper level cloud type amounts can be computed only when at most 2 levels    
   are present. AM and AH come from Nh, N, or the random-overlap equation and   
   represent "actual" cloud amount.  UM and UH are the amounts visible (the     
   non-overlapped amounts) and come from Nh, N, or N-Nh.  Amounts are given in  
   okta, AM and AH to two decimal places.  9 or 900 signifies missing data.     
19-20                                                                           
   The illuminance criterion is met (IB=1) if either SA is � -9 degrees or if   
   RI > 0.11, where RI = P sin(A) (R2/r2) {see full documentation}.             
*********-*********-*********-*********-*********-*********-*********-*********-
