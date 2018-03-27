set PROGRAM="%~1"

REM ����� �ணࠬ�� ��� ��ࠬ��஢           
%PROGRAM%                            
IF NOT ERRORLEVEL 1 GOTO err  

REM ����� �ணࠬ�� � ���⮩ ��ப�� � ����⢥ ������ �� ��ࠬ��஢ 
%PROGRAM% ""   
IF NOT ERRORLEVEL 1 GOTO err  

REM ����� �ணࠬ�� � ���������騬 ��������� input 䠩��
%PROGRAM% inputNotExist.txt
IF NOT ERRORLEVEL 1 GOTO err  

REM ����� ��ࢮ�� ��� 
%PROGRAM% test\input1.txt > output.txt                                  
IF ERRORLEVEL 1 GOTO err 
FC output.txt test\output1.txt 
IF ERRORLEVEL 1 GOTO err  

REM ����� ��ண� ��� 
%PROGRAM% test\input2.txt > output.txt                                 
IF ERRORLEVEL 1 GOTO err 
FC output.txt test\output2.txt 
IF ERRORLEVEL 1 GOTO err  
                              
REM ����� ���쥣� ��� 
%PROGRAM% test\input3.txt > output.txt                                 
IF ERRORLEVEL 1 GOTO err 
FC output.txt test\output3.txt 
IF ERRORLEVEL 1 GOTO err  
    
REM ��� �� ���ନ����, ࠢ�� 0 
%PROGRAM% test\input4.txt > output.txt                                 
IF ERRORLEVEL 1 GOTO err 
FC output.txt test\output4.txt 
IF ERRORLEVEL 1 GOTO err  
                           
ECHO Program testing succeeded :-)                  
EXIT                                                
:err                                                
ECHO Program testing failed :-(                     
EXIT