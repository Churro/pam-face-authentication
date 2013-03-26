#!/bin/sh
IMAGES="../../data/Test-input/low-light.avi"
[ -n $1 ] && IMAGES=$1

for y in $IMAGES
do
	cp $y test.avi
	IMAGE=`basename $y .avi` 
	RUN="$IMAGE/"
	rm -rf $RUN
	time ./findf $y > results 2> errors
	time ./clipf $y >> results 2>> errors
	mkdir -p $RUN
	mv results errors $RUN
	mv *.jpg $RUN
	mv test.avi $RUN
	time ./eyedf $RUN >> $RUN/results 2>> $RUN/errors
	../eyes.pl $RUN/results > $RUN/eyes.csv 2>> $RUN/errors
	mv *.jpg $RUN
	echo $RUN completed
done
