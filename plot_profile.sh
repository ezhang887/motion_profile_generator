#!/bin/bash

file="$1"
if [ -n "$file" ]; then
	echo "Plotting from $file"
	gnuplot -persist <<-EOFMarker
		plot "$file" using 1:2 with lines,\
		"$file" using 1:3 with lines,\
		"$file" using 1:4 with lines
	EOFMarker
else
	echo "ERROR: Please pass input file"
fi
