REM ����� �ணࠬ�� ��� ��ࠬ��஢           
Debug\Task4.exe                            
IF ERRORLEVEL 1 GOTO err                     
REM ����� �ணࠬ�� � ����� ���᫮�� ��ࠬ��஬          
Debug\Task4.exe notANumber   
IF NOT ERRORLEVEL 1 GOTO err
REM ����� �ணࠬ�� � ���⮩ ��ப�� � ����⢥ ������ �� ��ࠬ��஢ 
Debug\Task4.exe ""   
IF NOT ERRORLEVEL 1 GOTO err  
REM ����� �ணࠬ�� � ����� �᫮�� ��ࠬ��஬ (� �஢��塞 १����) 
Debug\Task4.exe -123 > output.txt                                  
IF ERRORLEVEL 1 GOTO err 
FC /B output.txt test\-123.txt 
IF ERRORLEVEL 1 GOTO err  
REM ����� �ணࠬ�� � ���� �᫮�묨 ��ࠬ��ࠬ�  
Debug\Task4.exe 15 2 > output.txt                          
IF ERRORLEVEL 1 GOTO err                            
FC /B output.txt test\15+2=17.txt                        
IF ERRORLEVEL 1 GOTO err                            
REM ����� �ணࠬ�� � �६� �᫮�묨 ��ࠬ��ࠬ�  
Debug\Task4.exe 15 2 -8 > output.txt                       
IF ERRORLEVEL 1 GOTO err                            
FC /B output.txt test\15+2+-8=9.txt                      
IF ERRORLEVEL 1 GOTO err
REM ����� �ணࠬ�� � �६� �᫮�묨 ��ࠬ��ࠬ�  
Debug\Task4.exe 13 + 7 / 8 * 3.8 > output.txt                       
IF ERRORLEVEL 1 GOTO err                            
FC /B output.txt test\13+783.8=9.500.txt                      
IF ERRORLEVEL 1 GOTO err                                                        
ECHO Program testing succeeded :-)                  
EXIT                                                
:err                                                
ECHO Program testing failed :-(                     
EXIT