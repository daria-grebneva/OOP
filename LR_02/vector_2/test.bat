set PROGRAM="%~1"

REM запуск программы без параметров           
%PROGRAM%                            
IF NOT ERRORLEVEL 1 GOTO err  

REM запуск программы с пустой строкой в качестве одного из параметров 
%PROGRAM% ""   
IF NOT ERRORLEVEL 1 GOTO err   

REM test 1
REM %PROGRAM% 12.3 45.2 > out.txt                                  
REM IF ERRORLEVEL 1 GOTO err 
REM FC out.txt test\out1.txt 
REM IF ERRORLEVEL 1 GOTO err   

REM test 2
REM %PROGRAM% test\in2.txt > out.txt                                  
REM IF ERRORLEVEL 1 GOTO err 
REM FC out.txt test\out2.txt 
REM IF ERRORLEVEL 1 GOTO err   

REM test 3
REM %PROGRAM% test\in3.txt > out.txt                                  
REM IF ERRORLEVEL 1 GOTO err 
REM FC out.txt test\out3.txt 
REM IF ERRORLEVEL 1 GOTO err   

                           
ECHO Program testing succeeded :-)                  
EXIT                                                
:err                                                
ECHO Program testing failed :-(                     
EXIT