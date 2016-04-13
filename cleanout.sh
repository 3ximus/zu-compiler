#!/bin/bash
# Isto foi feito para ajudar o pessoal a correr testes de compiladores automaticamente
# Qualquer coisa agradeçam ao Miguel Ventura, ou então deixem lá isso

# Mudar o caminho da variavel DIR para o directorio onde estao os testes
DIR="tests-zu/tests/"

#--------------------------------------------------------------------------------------#
echo
echo ">> Bora lá eliminar os *.out, *.output *.asm, *.xml, *.o e *exec todos:"
echo 

#--------------------------------------------------------------------------------------#
cd $DIR
rm *.out *.output *.asm *.xml *.o *exec


#--------------------------------------------------------------------------------------#
echo ">> Já está!"
echo 
