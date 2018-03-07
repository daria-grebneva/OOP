set PROGRAM="%~1"

REM запуск программы без параметров           
%PROGRAM%                            
IF NOT ERRORLEVEL 1 GOTO err  

REM запуск программы с пустой строкой в качестве одного из параметров 
%PROGRAM% ""   
IF NOT ERRORLEVEL 1 GOTO err  

REM выход за границы диапазона 
%PROGRAM% 256 > output.txt                                 
IF NOT ERRORLEVEL 1 GOTO err

REM переполнение 
%PROGRAM% 252939393393928272936 > output.txt                                 
IF NOT ERRORLEVEL 1 GOTO err

REM отрицательное значение 
%PROGRAM% -151 > output.txt                                 
IF NOT ERRORLEVEL 1 GOTO err

REM передача нечислового параметра 
%PROGRAM% a > output.txt                                 
IF NOT ERRORLEVEL 1 GOTO err

REM 6 96 
%PROGRAM% 6 > output.txt                                 
IF ERRORLEVEL 1 GOTO err 
FC output.txt out1.txt 
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