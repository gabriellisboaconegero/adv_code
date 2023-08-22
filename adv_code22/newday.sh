#! /usr/bin/bash

echo "Qual dia criar folder?"
read dia
dia="dia_$dia"
if [[ ! -d $dia ]]; then
    echo "Qual extensão usar?"
    read ext
    echo "Qual linguagem será usada?"
    read ling

    file="main.$ext"

    mkdir $dia
    touch $dia/$file
    touch $dia/input.txt
    touch $dia/teste.txt
    touch $dia/.info
    echo -e "$dia:\n    $ling: .$ext" > $dia/.info
    echo -e "\nDias e linguagens:\n"
    ./update.sh
else
    echo "Dia ja criado"
fi