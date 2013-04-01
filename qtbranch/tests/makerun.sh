#!/bin/sh
IMAGES="../../data/Test-input/low-light.avi"
SCALES="1.1 1.2 1.3 1.4"
CASCADES="/usr/haarcascade.xml /usr/share/OpenCV/haarcascades/haarcascade_frontalface_default.xml /usr/share/OpenCV/haarcascades/haarcascade_frontalface_alt.xml /usr/share/OpenCV/haarcascades/haarcascade_frontalface_alt2.xml /usr/share/OpenCV/haarcascades/haarcascade_frontalface_alt_tree.xml"

[ -n $1 ] && IMAGES=$1
[ -n $2 ] && CASCADES=$2
[ -n $3 ] && SCALES=$3

for x in $SCALES
do
	for y in $IMAGES
	do
		for z in $CASCADES
		do
			SCALE=$x
			IMAGE=`basename $y .avi` 
			CASCADE=`basename $z .xml` 
			RUN="$IMAGE/$CASCADE/$SCALE"
			rm -rf $RUN
			time ./findf2 $y $z $x > results 2> errors
			mkdir -p $RUN
			mv results errors $RUN
			mv *.jpg $RUN
			md5sum $z > $RUN/cascade.md5
			echo $RUN completed
		done
	done
done
