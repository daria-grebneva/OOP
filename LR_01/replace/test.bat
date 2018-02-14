set PROGRAM="%~1"

REM ����� �ணࠬ�� ��� ��ࠬ��஢           
%PROGRAM%                            
IF NOT ERRORLEVEL 1 GOTO err  

REM ����� �ணࠬ�� � ���⮩ ��ப�� � ����⢥ ������ �� ��ࠬ��஢ 
%PROGRAM% ""   
IF NOT ERRORLEVEL 1 GOTO err  

REM ����� �ணࠬ�� � ���������騬 ��������� input 䠩��
%PROGRAM% inputNotExist.txt output.txt "lala" "zuzuz"
IF NOT ERRORLEVEL 1 GOTO err  

REM ����� �ணࠬ�� � �㫥��� �᪮��� ��ப�� 
%PROGRAM% test\input1.txt output.txt "" "zuzuz"                                  
IF ERRORLEVEL 1 GOTO err 
FC output.txt test\outputEmptyString.txt 
IF ERRORLEVEL 1 GOTO err  

REM ����� �ணࠬ�� � ������� �᪮��� ��ப� �� ������� ��ப� 
%PROGRAM% test\input1.txt output.txt "ma" "zuzuz"                                  
IF ERRORLEVEL 1 GOTO err 
FC output.txt test\outputMaToZuzuz.txt 
IF ERRORLEVEL 1 GOTO err  

REM ����� �ணࠬ�� � ������� �᪮��� ��ப� �� ������� ��ப� 
%PROGRAM% test\input1.txt output.txt "ma" "1"                                  
IF ERRORLEVEL 1 GOTO err 
FC output.txt test\outputMaTo1.txt 
IF ERRORLEVEL 1 GOTO err 

REM ����� �ணࠬ�� � ������� �᪮��� ��ப� �� �㫥��� ��ப� 
%PROGRAM% test\input1.txt output.txt "ma" ""                                  
IF ERRORLEVEL 1 GOTO err 
FC output.txt test\outputMaToEmptyString.txt 
IF ERRORLEVEL 1 GOTO err 

REM ����� �ணࠬ�� � ������� �᪮��� ��ப� �� �㫥��� ��ப� 
%PROGRAM% test\input2.txt output.txt "1231234" " I'm happy! "                                  
IF ERRORLEVEL 1 GOTO err 
FC output.txt test\outputStringOfNumbers.txt 
IF ERRORLEVEL 1 GOTO err 
                         



                           
ECHO Program testing succeeded :-)                  
EXIT                                                
:err                                                
ECHO Program testing failed :-(                     
EXIT