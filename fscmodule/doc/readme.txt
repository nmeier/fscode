FSCModule - a skeleton for flight-sim modules

Compiler

/Od /I "fscode\fscair\src" /I "fscode\fscmodule\src" /I "fscode\fscmodule\contrib" /D "_WINDLL" /FD /EHsc /MT /nologo /c /ZI /TP /errorReport:prompt

Linker

/OUT:"realtrim.dll" /NOLOGO /DLL /ERRORREPORT:PROMPT version.lib dinput.lib dinput8.lib dxguid.lib  kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib