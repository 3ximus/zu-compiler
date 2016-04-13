#!/bin/bash
# Isto foi feito para ajudar o pessoal a correr testes de compiladores automaticamente
# Qualquer coisa agradeçam ao Miguel Ventura, ou então deixem lá isso

# Mudar o caminho da variavel DIR para o directorio onde estao os testes
DIR="tests-zu/tests/"


#--------------------------------------------------------------------------------------#

COUNTER=1

echo
echo ">> Chegou a hora, vamos gerar o xml:"
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
  { ./zu "$file" --target xml; } >& /dev/null
  
  echo $FILENAME" : xml done"
  
  let COUNTER=COUNTER+1
done
#--------------------------------------------------------------------------------------#

echo
echo ">> Já está tudo xmlizado!"
echo
echo $(($COUNTER - 1)) " ficheiros xmlizados."
echo "Agora vai lá ver os .xml para ver se não houve porcaria."
echo
