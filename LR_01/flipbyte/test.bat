set PROGRAM="%~1"

REM ����� �ணࠬ�� ��� ��ࠬ��஢           
%PROGRAM%                            
IF NOT ERRORLEVEL 1 GOTO err  

REM ����� �ணࠬ�� � ���⮩ ��ப�� � ����⢥ ������ �� ��ࠬ��஢ 
%PROGRAM% ""   
IF NOT ERRORLEVEL 1 GOTO err  

REM ��室 �� �࠭��� ��������� 
%PROGRAM% 256 > output.txt                                 
IF NOT ERRORLEVEL 1 GOTO err

REM ��९������� 
%PROGRAM% 252939393393928272936 > output.txt                                 
IF NOT ERRORLEVEL 1 GOTO err

REM ����⥫쭮� ���祭�� 
%PROGRAM% -151 > output.txt                                 
IF NOT ERRORLEVEL 1 GOTO err

REM ��।�� ���᫮���� ��ࠬ��� 
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