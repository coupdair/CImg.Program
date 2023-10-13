collection of programs using CImg library

<!--- place@of@TOC --->

# summary

all program names begin with `CImg.`.
Image processing themes and corresponding programs:

1. image displaying
     1. CImg.display

1. basic image processing
     1. CImg.autocrop
     1. CImg.crop
     1. CImg.operation
     1. CImg.labeling

1. image measurement
     1. CImg.object_displacement
     1. CImg.warping, CImg.mapping

1. statistics
     1. CImg.reduce

1. changing space
     1. CImg.fourier
     1. CImg.hough

# clone

~~~ { .bash }
#github
github=https://github.com/
github=git@github.com:

cd code/
#CImg lib.
git clone ${gitbub}coupdair/CImg
#CImg programs
git clone ${gitbub}coupdair/CImg.Program
~~~

# compile

~~~ { .bash }
#ex. auto crop
cd CImg.Program/autocrop/
cat _info.autocrop.txt 

#compile autocrop
g++ -o CImg.autocrop CImg.autocrop.cpp -I../../CImg -Wall -W -lm -ansi -pedantic -O0 -fno-tree-pre -Dcimg_use_vt100 -lpthread -Dcimg_display=0 -Dcimg_use_tiff -ltiff
#run autocrop
./CImg.autocrop -i logo.png -o logo_autocrop.png && identify logo_autocrop.png logo.png && display logo_autocrop.png
~~~
