#! /bin/bash

declare -i initTime
declare -i finishTime
declare -i eleapsedTime

initTime=$(date +%s)

date "+Começo: %T"

echo -n "Quer terminar? [Y/n]"
while read answer; do
  case $answer in
    Y | y)
      finishTime=$(date +%s)
      date "+Final: %T"
      let eleapsedTime="$finishTime - $initTime"
      # echo "$eleapsedTime"
      printf "Você demorou %dh:%dm:%ds\n" $(((eleapsedTime / 3600) % 25)) $(((eleapsedTime / 60) % 60)) $((eleapsedTime % 60))
      break
    ;;
  esac
  echo -n "Quer terminar? [Y/n]"
done