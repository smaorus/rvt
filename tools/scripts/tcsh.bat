@echo off
@REM Select the latest VS Tools
IF  EXIST %VS100COMNTOOLS% (
    CALL "%VS100COMNTOOLS%\vsvars32.bat"
    GOTO :start_term
)

IF  EXIST %VS90COMNTOOLS% (
    CALL "%VS90COMNTOOLS%\vsvars32.bat"
    GOTO :start_term
)

IF  EXIST %VS80COMNTOOLS% (
    CALL "%VS80COMNTOOLS%\vsvars32.bat"
    GOTO :start_term
)

:start_term

tcsh.exe %1 %2