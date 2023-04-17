@echo off
set MAXSZ=16384
start /wait cmd /c prolog_micro_brain.exe --query-goal change_directory('%1') --query-goal consult('%2') --query-goal tell('%3') --query-goal %4 --query-goal told --query-goal tell('_alive.pl') --query-goal saveLF --query-goal told --query-goal end_of_file ^>%5
rem @cls