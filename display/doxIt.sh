#! /bin/bash

##list='CImg.Program CImg.PlugIn PCO LaVision raw Hiris CImg.Tool NetCDF.Tool CImg'
list='display'
#move code versions to temporary directory
for d in $list
do
  mkdir -p ../DoxIt.tmp/$d
  mv ../$d/*.v?.?.?.* ../DoxIt.tmp/$d
done
#get display help output (xterm-color unformated)
##dir=../display
##bin=$dir/CImg.display.linux32
dir=../display
bin=$dir/CImg.display
out=CImg.display.help
$bin -h 2> $dir/$out; cat -v $dir/$out | sed 's/\^\[\[//g' | sed 's/1m//g' | sed 's/0;0;0m//g' | sed 's/0;35;59m//g' | sed 's/4;31;59m//g' | sed 's/0;32;59m//g' > $dir/$out.output; rm $dir/$out
#create documentation
doxygen CImg.display.Doxygen
#put back code versions
for d in $list
do
  mv ../DoxIt.tmp/$d/* ../$d/
  rmdir ../DoxIt.tmp/$d
done
rmdir ../DoxIt.tmp

