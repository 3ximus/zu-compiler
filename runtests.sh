#!/bin/bash
# Isto foi feito para ajudar o pessoal a correr testes de compiladores automaticamente
# Qualquer coisa agradeçam ao Miguel Ventura, ou então deixem lá isso

# Mudar o caminho da variavel DIR para o directorio onde estao os testes

#dailies
DIR="tests-zu/tests/"
EXPECTED="tests-zu/expected/"

#simple
# DIR="tests-zu-daily-201604071153/auto-tests/"
# EXPECTED="tests-zu-daily-201604071153/expected/"


#--------------------------------------------------------------------------------------#

COUNTER=1
FAILED=0
COMPILERFAIL=()
YASMFAIL=()
LDFAIL=()
DIFFFAIL=()

echo
echo ">> Ah e tal vamos lá correr os testes:"
echo 

#--------------------------------------------------------------------------------------#
for file in ${DIR}*.zu
do
  # detecta numero do teste
  FILENAME=$(basename $file)
  NUM=`echo "$FILENAME" | cut -d'-' -f3`
  
  # Se foi fornecido um intervalo
  if [[ -n "$1" && -n "$2" ]]; then
    # limite inferior
    if [ "$NUM" -lt "$1" ]; then
      continue
    fi
    
    #limite superior
    if [ "$NUM" -gt "$2" ]; then
      break
    fi
  fi
  
  # apenas 1 argumento, numero de testes a correr
  if [[ -n "$1" && -z "$2" ]]; then
    if [ "$COUNTER" -gt "$1" ]; then
        break
    fi
  fi
  

  # comando a ser executado
  NAME=`echo "$file" | cut -d'.' -f1`
  N=`echo "$FILENAME" | cut -d'.' -f1`
  
  if [[ "$COUNTER" -eq "1" ]]; then
    echo "-----------------------------------------------------"
  fi
  
  # executar o compilador
  printf "%s : %s " "$COUNTER" "$N"
  { ./zu "$file"; } >& "$NAME.output";
  if [[ "$?" -eq "0" ]]; then
    printf "..... Compiler: OK, " 
  else 
    printf "..... Compiler: Failed, ";
    COMPILERFAIL+=("$N")
    let FAILED=FAILED+1
  fi
  
  # produzir o ficheiro binario
  cd $DIR;
  { yasm -felf32 "$N.asm"; } >& /dev/null
  if [[ "$?" -eq "0" ]]; then
    printf "YASM: OK, " 
  else 
    printf "YASM: Failed, ";
      YASMFAIL+=("$N")
  fi
  
  # gerar o executavel linkando a biblioteca RTS
  { ld -m elf_i386 -o "$N"exec "$N.o" -lrts; } >& /dev/null
  if [[ "$?" -eq "0" ]]; then
    echo "LD: OK." 
  else 
    echo "LD: Failed.";
  fi
  { ./"$N"exec > "$N.out"; } >& /dev/null
  { cd ../..; } >& /dev/null
  
  echo
  echo "<<<<< Esperado: >>>>>"
  echo "$(cat $EXPECTED$N.out)"
  echo
  echo "«««««  Obtido:  »»»»»"
  echo "$(cat $NAME.out)"
  echo
  DIFF=$(diff -w -E -B "$NAME.out" "$EXPECTED$N.out") 
  if [ "$DIFF" != "" ];
  then
      let FAILEDTESTS=FAILEDTESTS+1
      echo "#ERRODIFF"
      DIFFFAIL+=("$N")
  fi
  echo "-----------------------------------------------------"
  
  let COUNTER=COUNTER+1
done
#--------------------------------------------------------------------------------------#

echo
echo
echo $(($COUNTER - 1)) " testes efectuados, falhas abaixo:"
echo
echo "COMPILADOR ZU:"
for i in "${COMPILERFAIL[@]}"
do
   echo "    !falha : " $i
done

echo "YASM:"
for i in "${YASMFAIL[@]}"
do
   echo "    !falha : " $i
done

echo "LD:"
for i in "${LDFAIL[@]}"
do
   echo "    !falha : " $i
done

echo "DIFF:"
for i in "${DIFFFAIL[@]}"
do
   echo "    !falha : " $i
done

echo
echo "Passam " $(($(($COUNTER - 1)) - $FAILED)) "/" $(($COUNTER - 1))
echo
echo "Nota: Se precisares podes ver os .output gerados para ver o que aconteceu durante o ./zu file.zu"
echo "Está tudo despachado, até à próxima!"
echo
