@echo off
rem Check if filename is provided
if "%1"=="" (
    echo Please provide the file name.
    exit /b
)

rem Compile all source files in the src/ directory
g++ -c head+cpp\Game.cpp -Iinclude -IC:\SFML-Progs\SFML-2.5.1\SFML-2.5.1\include
g++ -c head+cpp\Level.cpp -Iinclude -IC:\SFML-Progs\SFML-2.5.1\SFML-2.5.1\include
g++ -c head+cpp\Player.cpp -Iinclude -IC:\SFML-Progs\SFML-2.5.1\SFML-2.5.1\include
g++ -c head+cpp\Timer.cpp -Iinclude -IC:\SFML-Progs\SFML-2.5.1\SFML-2.5.1\include
g++ -c head+cpp\Support.cpp -Iinclude -IC:\SFML-Progs\SFML-2.5.1\SFML-2.5.1\include
g++ -c head+cpp\%1.cpp -Iinclude -IC:\SFML-Progs\SFML-2.5.1\SFML-2.5.1\include


rem Notify if successful or failed
if %errorlevel% equ 0 (
    echo Compilation successful.
) else (
    echo Compilation failed.
)

rem Link all object files
g++ %1.o Game.o Level.o Player.o Timer.o Support.o -o %1 -LC:\SFML-Progs\SFML-2.5.1\SFML-2.5.1\lib -lsfml-graphics -lsfml-window -lsfml-system

rem Notify if successful or failed
if %errorlevel% equ 0 (
    echo Linking successful.
) else (
    echo Linking failed.
)
