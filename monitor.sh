#!/bin/bash

D="$1"
[ -d "$D" ] || { echo "Błąd: brak katalogu"; exit 1; }
LOG="report.log"
SAFE=0
REM=0

trap 'echo "Usunięto plików: $REM"; exit' INT
trap 'SAFE=$((1-SAFE)); echo "SAFE MODE = $SAFE"' USR1

while true; do
  COUNT=$(find "$D" -maxdepth 1 -type f | wc -l)

  if [ "$COUNT" -gt 5 ]; then
    OLDEST=$(ls -t "$D" | tail -n 1)

    if [ "$SAFE" -eq 0 ]; then
      rm "$D/$OLDEST"
      echo "[$(date)] Usunięto: $(basename "$OLDEST")" >> "$LOG"
      REM=$((REM+1))
    else
      echo "SAFE MODE: za dużo plików"
    fi
  fi

  sleep 2
done