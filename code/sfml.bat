
@echo off
rem Check if filename is provided
if "%1"=="" (
    echo Please provide the file name.
    exit /b
)

rem Compile all source files in the head+cpp/ directory
g++ -c head+cpp\Game.cpp -Iinclude -IC:\SFML-Progs\SFML-2.5.1\SFML-2.5.1\include
g++ -c head+cpp\Level.cpp -Iinclude -IC:\SFML-Progs\SFML-2.5.1\SFML-2.5.1\include
g++ -c head+cpp\Player.cpp -Iinclude -IC:\SFML-Progs\SFML-2.5.1\SFML-2.5.1\include
g++ -c head+cpp\Timer.cpp -Iinclude -IC:\SFML-Progs\SFML-2.5.1\SFML-2.5.1\include
g++ -c head+cpp\Support.cpp -Iinclude -IC:\SFML-Progs\SFML-2.5.1\SFML-2.5.1\include
g++ -c head+cpp\Overlay.cpp -Iinclude -IC:\SFML-Progs\SFML-2.5.1\SFML-2.5.1\include
g++ -c head+cpp\Sky.cpp -Iinclude -IC:\SFML-Progs\SFML-2.5.1\SFML-2.5.1\include
g++ -c head+cpp\SoilLayer.cpp -Iinclude -IC:\SFML-Progs\SFML-2.5.1\SFML-2.5.1\include
g++ -c head+cpp\SoilTile.cpp -Iinclude -IC:\SFML-Progs\SFML-2.5.1\SFML-2.5.1\include
g++ -c head+cpp\Plant.cpp -Iinclude -IC:\SFML-Progs\SFML-2.5.1\SFML-2.5.1\include
g++ -c head+cpp\Market.cpp -Iinclude -IC:\SFML-Progs\SFML-2.5.1\SFML-2.5.1\include
g++ -c head+cpp\Inventory.cpp -Iinclude -IC:\SFML-Progs\SFML-2.5.1\SFML-2.5.1\include
g++ -c head+cpp\Generic.cpp -Iinclude -IC:\SFML-Progs\SFML-2.5.1\SFML-2.5.1\include
g++ -c head+cpp\%1.cpp -Iinclude -IC:\SFML-Progs\SFML-2.5.1\SFML-2.5.1\include

rem Notify if compilation was successful or failed
if %errorlevel% equ 0 (
    echo Compilation successful.
) else (
    echo Compilation failed.
    exit /b
)

rem Link all object files
@REM g++ %1.o Game.o Level.o Player.o Timer.o Support.o Overlay.o Sky.o SoilTile.o SoilLayer.o Plant.o Inventory.o Market.o -o %1 -LC:\SFML-Progs\SFML-2.5.1\SFML-2.5.1\lib -lsfml-graphics -lsfml-window -lsfml-system -mconsole
g++ %1.o Game.o Level.o Player.o Timer.o Support.o Overlay.o Sky.o SoilTile.o SoilLayer.o Plant.o Market.o Inventory.o Generic.o -o %1 -LC:\SFML-Progs\SFML-2.5.1\SFML-2.5.1\lib -lsfml-graphics -lsfml-window -lsfml-system

rem Notify if linking was successful or failed
if %errorlevel% equ 0 (
    echo Linking successful.
) else (
    echo Linking failed.
    exit /b
)





