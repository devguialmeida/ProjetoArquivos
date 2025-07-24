@echo off
:inicio
cls
echo ==========================
echo       PROGRAMAS
echo ==========================
echo [1] buscaBinCEP
echo [2] buscaBinIndiceCEP
echo [3] geraIndice
echo [4] hashAgg
echo [5] procCsv
echo [6] ordena
echo [0] Sair
echo ==========================
set "programa="
set /p escolha=Digite o número do programa: 

if "%escolha%"=="0" goto fim
if "%escolha%"=="1" set programa=buscaBinCEP
if "%escolha%"=="2" set programa=buscaBinIndiceCEP
if "%escolha%"=="3" set programa=geraIndice
if "%escolha%"=="4" set programa=hashAgg
if "%escolha%"=="5" set programa=procCsv
if "%escolha%"=="6" set programa=ordena

if not defined programa (
    echo.
    echo Opcao invalida!
    pause
    goto inicio
)

echo.
set /p args=Digite os argumentos para %programa% (ou deixe em branco): 

if exist bin\%programa%.exe (
    echo.
    echo Executando: %programa% %args%
    echo ------------------------------------
    bin\%programa%.exe %args%
    echo ------------------------------------
) else (
    echo.
    echo ERRO: bin\%programa%.exe nao encontrado!
)

set programa=
set args=
echo.
pause
goto inicio

:fim
echo Encerrando...
pause
