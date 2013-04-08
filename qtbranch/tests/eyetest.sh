#!/bin/sh

DIR=`date "+%Y%m%d%H%M"`

time ../eyedf . > eye_results 2>> eye_errors
../../eyes.pl eye_results > eye_results.csv 2>> eye_errors
git diff > diffs
[ ! -e $DIR ] && mkdir $DIR && mv diffs eye_results eye_errors eye_results.csv $DIR/
