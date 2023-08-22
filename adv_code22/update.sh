tracker_file=linguagens

days="$(ls | grep "dia_*")"
> $tracker_file
for day in $days; do
    cat $day/.info >> $tracker_file
done
cat $tracker_file
