set PROGRAM="%~1"

REM запуск программы без параметров           
%PROGRAM%                            
IF NOT ERRORLEVEL 1 GOTO err  

REM запуск программы с пустой строкой в качестве одного из параметров 
%PROGRAM% ""   
IF NOT ERRORLEVEL 1 GOTO err  
                                  
REM  
%PROGRAM% test\in1.txt output.txt                                 
IF ERRORLEVEL 1 GOTO err 
FC output.txt test\out1.txt 
IF ERRORLEVEL 1 GOTO err  
     
REM  
%PROGRAM% test\in2.txt output.txt                                 
IF ERRORLEVEL 1 GOTO err 
FC output.txt test\out2.txt 
IF ERRORLEVEL 1 GOTO err  
  
REM  
%PROGRAM% test\in3.txt output.txt                                 
IF ERRORLEVEL 1 GOTO err 
FC output.txt test\out3.txt 
IF ERRORLEVEL 1 GOTO err  
   
REM  
%PROGRAM% test\in4.txt output.txt                                 
IF ERRORLEVEL 1 GOTO err 
FC output.txt test\out4.txt 
IF ERRORLEVEL 1 GOTO err  
                             
                                                 
ECHO Program testing succeeded :-)                  
EXIT                                                
:err                                                
ECHO Program testing failed :-(                     
EXIT