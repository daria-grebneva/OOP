set PROGRAM="%~1"

REM запуск программы без параметров           
REM %PROGRAM%                            
REM IF NOT ERRORLEVEL 1 GOTO err  

REM запуск программы с пустой строкой в качестве одного из параметров 
REM %PROGRAM% ""   
REM IF NOT ERRORLEVEL 1 GOTO err  

REM 6 96 
%PROGRAM% 6 > output.txt                                 
IF ERRORLEVEL 1 GOTO err 
FC output.txt out1.txt 
IF ERRORLEVEL 1 GOTO err  

REM выход за границы диапазона 
%PROGRAM% 256 > output.txt                                 
IF ERRORLEVEL 1 GOTO err 
FC output.txt out2.txt 
IF ERRORLEVEL 1 GOTO err

REM передача нечислового параметра 
%PROGRAM% a > output.txt                                 
IF ERRORLEVEL 1 GOTO err 
FC output.txt out3.txt 
IF ERRORLEVEL 1 GOTO err

REM 200 19 
%PROGRAM% 200 > output.txt                                 
IF ERRORLEVEL 1 GOTO err 
FC output.txt out4.txt 
IF ERRORLEVEL 1 GOTO err      

                     
ECHO Program testing succeeded :-)                  
EXIT                                                
:err                                                
ECHO Program testing failed :-(                     
EXIT