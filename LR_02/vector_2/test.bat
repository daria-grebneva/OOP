set PROGRAM="%~1"
                                   \
REM запуск программы с пустой строкой в качестве одного из параметров 
%PROGRAM% "" > out.txt                                  
IF ERRORLEVEL 1 GOTO err 
FC out.txt test\outEmpty.txt 
IF ERRORLEVEL 1 GOTO err 

REM test 1
%PROGRAM% < test\in1.txt > out.txt                                  
IF ERRORLEVEL 1 GOTO err 
FC out.txt test\out1.txt 
IF ERRORLEVEL 1 GOTO err   

REM test 2
%PROGRAM% < test\in2.txt > out.txt                                  
IF ERRORLEVEL 1 GOTO err 
FC out.txt test\out2.txt 
IF ERRORLEVEL 1 GOTO err   

REM test 3
%PROGRAM% < test\in3.txt > out.txt                                  
IF ERRORLEVEL 1 GOTO err 
FC out.txt test\out3.txt 
IF ERRORLEVEL 1 GOTO err   

                           
ECHO Program testing succeeded :-)                  
EXIT                                                
:err                                                
ECHO Program testing failed :-(                     
EXIT