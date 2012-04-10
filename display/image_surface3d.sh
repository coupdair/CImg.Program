#!/bin/bash

d=../../text/cours_traitement_d_image/

f="$d/morphomath_object_gradient_threshold.png "

#1D graph
echo 'SHOW: 1D graph of CIRCLE only'
../../CImg.Program/display/CImg.display -i $f --1D
echo 'press a key to continue ...'
read

#3D graph
../../CImg.Program/display/CImg.display --3D -i $f -pi ../../CImg.Program/display/pose__morphomath_object_tophat.cimg --render-type 4 --color-type false &
sleep 3
echo 'SHOW: 3D SURFACE and ISOPHYTE (i), and both i and p after C'
display $f &

