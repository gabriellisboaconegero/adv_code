#! /usr/bin/bash
input=teste.txt
flag=1
(($flag)) && input=input.txt
echo "runnig $input"

if [[ $1 == "p1" ]]; then
    big=0
    while read -r line; do
        if [[ -n $line ]]; then
            ((cal+=line))
        else
            (( $cal > $big )) && big=$cal
            cal=0
        fi
    done < $input
    echo $big
elif [[ $1 == "p2" ]]; then
    tmp_file=tmp
    sorted=tmp_sorted

    while read -r line; do
        if [[ -n $line ]]; then
            ((cal+=line))
        else
            echo $cal >> $tmp_file
            cal=0
        fi
    done < $input
    echo $cal >> $tmp_file

    sort -nr $tmp_file > $sorted
    rm $tmp_file

    total=0
    for i in {1..3}; do
        read a
        ((total+=a))
    done < $sorted

    echo $total
    rm $sorted
else
    echo -e "Escolha uma parte: \n\tp1\n\tp2"
fi
