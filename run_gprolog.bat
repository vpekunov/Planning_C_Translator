@echo off
set MAXSZ=16384
gprolog.exe --query-goal change_directory('%1') --query-goal consult('%2') --query-goal tell('%3') --query-goal %4 --query-goal told --query-goal end_of_file >%5
rem @cls