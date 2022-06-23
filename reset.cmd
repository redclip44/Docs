@echo off 
for /l %a in (1 1 10) do type nul > "%a.txt"
REM HKEY_LOCAL_MACHINE\SOFTWARE\Classes\AppID
REM   {AppID_GUID}
REM      LocalService = name
@echo off 
REG QUERY HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Windows\

REG QUERY HKEY_LOCAL_MACHINE\SOFTWARE\Classes\AppID