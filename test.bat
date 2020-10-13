@echo off

set repBuild=./bin

for %%A in (%repBuild%\*.gb) do (
    bgb %repBuild%/%%~nxA
)