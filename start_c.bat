@echo off
@set PATH="C:\Program Files\Microsoft Visual Studio 12.0\VC\bin";"C:\Program Files\Microsoft Visual Studio 12.0\Common7\IDE\";%PATH%
@set IPATH="C:\Program Files\Microsoft Visual Studio 12.0\VC\include"
@set IPATHSDK="C:\Program Files\Microsoft SDKs\Windows\v7.1A\Include"
@set LPATH="C:\Program Files\Microsoft Visual Studio 12.0\VC\lib"
@set LPATHSDK="C:\Program Files\Microsoft SDKs\Windows\v7.1A\Lib"
@if "%1"=="nocompile" goto m1
@copy /Y %1 _.c
@cl.exe /O2 -o _.exe _.c /MTd /EHsc /I%IPATH% /I%IPATHSDK% /link /LIBPATH:%LPATH% /LIBPATH:%LPATHSDK% >_.err
:m1
@if "%3"=="" goto noin
@_.exe >%2 <%3
@goto end
:noin
@_.exe >%2
:end
echo %errorlevel% >_.result
