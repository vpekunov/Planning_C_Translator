@echo off
@set PATH="C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.29.30133\bin\HostX64\x86";"C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE";%PATH%
@set IPATH="C:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0\shared"
@set IPATH2="C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\include"
@set IPATH3="C:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0\ucrt"
@set IPATH4="C:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0\um"
@set LPATH="C:\Program Files (x86)\Windows Kits\10\Lib\10.0.22621.0\um\x86"
@set LPATH2="C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\lib"
@set LPATH3="C:\Program Files (x86)\Windows Kits\10\Lib\10.0.22621.0\ucrt\x86"
@if "%1"=="nocompile" goto m1
@copy /Y %1 _.c
@cl.exe /O2 -o _.exe _.c /MTd /EHsc /I%IPATH% /I%IPATH2% /I%IPATH3% /I%IPATH4% /link /LIBPATH:%LPATH% /LIBPATH:%LPATH2% /LIBPATH:%LPATH3% >_.err
:m1
@if "%3"=="" goto noin
@_.exe >%2 <%3
@goto end
:noin
@_.exe >%2
:end
echo %errorlevel% >_.result
