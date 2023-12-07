#! /usr/bin/env bash
# Após completar o dia <x> execute esse comando para dar git push
# Usage:
#   complete-day.sh <dia>
#   <dia> é um número

re='^[0-9]+$'
if [[ -z $1 ]]; then
    echo "Usage: complete-day.sh <dia>"
    exit 1
elif ! [[ $1 =~ $re ]]; then
    echo "Usage: <dia> deve ser um número, ($1 não é um número)"
    exit 1
fi

str="dia $(printf '%02d/23' $1) feito "
for i in $(seq $1); do
    str+='!'
done

git status
echo $str
echo "Quer continuar?[Y/n]"
read res
case $res in
    y|Y|'') ;;
    *) exit ;;
esac
git add .
git commit -m "$str"
