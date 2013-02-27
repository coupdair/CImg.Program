#! /bin/bash

##list='distorsion CImg'
list='distorsion'
#move code versions to temporary directory
for d in $list
do
  mkdir -p ../DoxIt.tmp/$d
  mv ../$d/*.v?.?.?.* ../DoxIt.tmp/$d
done
#stepper help output (xterm-color unformated)
dir=../distorsion
for fb in CImg.mapping
do
  bin=$dir/$fb
  out=$fb.help
  $bin -h 2> $dir/$out; cat -v $dir/$out | sed 's/\^\[\[//g' | sed 's/1m//g' | sed 's/0;0;0m//g' | sed 's/0;35;59m//g' | sed 's/0;32;59m//g' | sed 's/4;31;59m//g' > $dir/$out.output;rm $dir/$out
done
#create documentation
cat distorsion.Doxygen | sed 's/\ VERSION/warping.'`cat VERSION_WARPING`',mapping.'`cat VERSION_MAPPING`',warpingFormat.'`cat VERSION_WARPING_FORMAT`'/g' > distorsion.Doxygen.version
doxygen distorsion.Doxygen.version
rm distorsion.Doxygen.version
#put back code versions
for d in $list
do
  mv ../DoxIt.tmp/$d/* ../$d/
  rmdir ../DoxIt.tmp/$d
done
rmdir ../DoxIt.tmp

