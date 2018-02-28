set PROGRAM="%~1"

REM запуск программы без параметров           
%PROGRAM%                            
IF NOT ERRORLEVEL 1 GOTO err  

REM запуск программы с пустой строкой в качестве одного из параметров 
%PROGRAM% ""   
IF NOT ERRORLEVEL 1 GOTO err  

REM запуск программы с несуществующим названием input файла
%PROGRAM% inputNotExist.txt
IF NOT ERRORLEVEL 1 GOTO err  

REM запуск программы с несуществующей в тексте строкой 
%PROGRAM% test\input1.txt > output.txt                                  
IF ERRORLEVEL 1 GOTO err 
FC output.txt test\output1.txt 
IF ERRORLEVEL 1 GOTO err  

REM запуск программы с нулевой искомой строкой 
%PROGRAM% test\input2.txt > output.txt                                 
IF ERRORLEVEL 1 GOTO err 
FC output.txt test\output2.txt 
IF ERRORLEVEL 1 GOTO err  
                              
REM запуск программы с нулевой искомой строкой 
%PROGRAM% test\input3.txt > output.txt                                 
IF ERRORLEVEL 1 GOTO err 
FC output.txt test\output3.txt 
IF ERRORLEVEL 1 GOTO err  
                              

                           
ECHO Program testing succeeded :-)                  
EXIT                                                
:err                                                
ECHO Program testing failed :-(                     
EXIT