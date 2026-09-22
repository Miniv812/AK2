OUTPUT_FILE="top_outputLB1.txt"

N=${1:-5}

top -b -n 1 > "$OUTPUT_FILE"

head -n "$N" "$OUTPUT_FILE" > "${OUTPUT_FILE}.tmp" && mv "${OUTPUT_FILE}.tmp" "$OUTPUT_FILE"

echo "Результат сохранен в $OUTPUT_FILE (первые $N строк)."
