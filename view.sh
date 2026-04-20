#!/usr/bin/env bash

INPUT="../image_result.ppm"
OUTPUT="../image_result.png"

if [ ! -f "$INPUT" ]; then
    echo "Error: $INPUT not found"
    exit 1
fi

magick "$INPUT" "$OUTPUT"

echo "Converted to $OUTPUT"

xdg-open "$OUTPUT" >/dev/null 2>&1 &
