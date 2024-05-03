@echo off
@set PATH="C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.29.30133\bin\HostX64\x86";"C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE";%PATH%
@set IPATH=C:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0\shared
@set IPATH2=C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\include
@set IPATH3=C:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0\ucrt
@set IPATH4=C:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0\um
@set IPATHMPI=C:\Program Files (x86)\MPICH2\include
@set IPATHOCL=C:\Program Files (x86)\AMD APP SDK\2.9-1\include
@set LPATH=C:\Program Files (x86)\Windows Kits\10\Lib\10.0.22621.0\um\x86
@set LPATH2=C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\lib
@set LPATH3=C:\Program Files (x86)\Windows Kits\10\Lib\10.0.22621.0\ucrt\x86
@set LPATHMPI=C:\Program Files (x86)\MPICH2\lib
@set LPATHOCL=C:\Program Files (x86)\AMD APP SDK\2.9-1\lib\x86
@cl.exe /O2 -o %2 %1 mpi.lib OpenCL.lib wsock32.lib /Fa /MTd /EHsc /openmp /I"%IPATH%" /I"%IPATH2%" /I"%IPATH3%" /I"%IPATH4%" /I"%IPATHMPI%" /I "%IPATHOCL%" /link /LIBPATH:"%LPATH%" /LIBPATH:"%LPATH2%" /LIBPATH:"%LPATH3%" /LIBPATH:"%LPATHMPI%" /LIBPATH:"%LPATHOCL%" >_.err

