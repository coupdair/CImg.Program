#!/bin/bash
cp -p CImg.display.Doxygen CImg.display.Doxygen.old
old=/home/coudert/code.CImg/CImg.Program/display/
new=$PWD/
echo $old|sed 's/\//\\\//g' > old
echo $new|sed 's/\//\\\//g' > new
#cat old; echo 'to'; cat new
cat CImg.display.Doxygen.old | sed s/`cat old`/`cat new`/g > CImg.display.Doxygen
rm old new

