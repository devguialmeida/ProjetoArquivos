@echo off
if not exist bin mkdir bin

for %%f in (src\*.c) do (
    echo Compilando %%f...
    gcc -Wall -Wextra -O2 "%%f" -o "bin\%%~nf.exe"
)

echo.
echo Compila��o finalizada.
pause
