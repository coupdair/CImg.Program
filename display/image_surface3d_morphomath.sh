#!/bin/bash

d=../../text/cours_traitement_d_image/

list="$d/morphomath_object_gradient.png $d/morphomath_object_gradient_erosion.png $d/morphomath_object_gradient_tophat.png $d/morphomath_object_gradient_threshold.png"

for f in $list
do
#ls $f
  ../../CImg.Program/display/CImg.display --3D -i $f -pi ../../CImg.Program/display/pose__morphomath_object_tophat.cimg --render-type 4 --color-type false &
  sleep 3
  display $f &
  read
done

