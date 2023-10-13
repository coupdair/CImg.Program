#!/bin/bash

#create the TOC (i.e. Table Of Contents) of a MarkDown file
#usage: ./ReadMe_TOC.sh
#usage: ./ReadMe_TOC.sh > ReadMe_TOC.md; cat ReadMe_TOC.md ReadMe.md > ReadMe_with_TOC.md; mv ReadMe_with_TOC.md ReadMe.md

version="v0.0.6"

f=ReadMe.md
ft=`basename $0 .sh`.tmp
fo=ReadMe_newTOC.txt

#remove previous TOC
sed -i 's/begin@of@TOC/place@of@TOC --->\n<!--- begin@of@TOC --->/' $f
sed -i '/begin@of@TOC/,/end@of@TOC/d' $f

#get TOC
grep '# ' $f | grep -v '(#' > $ft

#header
echo '<!--- begin@of@TOC --->' | tee $fo
echo '# Table of contents' | tee -a $fo
echo | tee -a $fo

#MarkDown links
while read l
do
#echo ":$l:"
  #title
  t=`echo "$l" | sed 's/# //;s/#//g'`
  #rank and link
  k=`echo "$l" | sed 's/# /#@/;s/  / /g;s/  / /g;s/  / /g;s/ /-/g;s/\.//g' | tr [:upper:] [:lower:]`
#echo "$t $k"
  #gather
  /bin/echo -e -n $k | sed "s/@/@[$t](/" | sed 's/#@/# /;s/###/          1./;s/##/     1./;s/#/1./;'
  echo ')'
done < $ft | sed 's/(/(\#/' | tee -a $fo

#footer
echo '<!--- end@of@TOC --->' | tee -a $fo

#clean
rm $ft

#replace place@of@TOC
cnt=`grep 'place@of@TOC' $f | wc -l`
##exit if no place for TOC
if((cnt==0)); then exit; fi
##extract before and after TOC
fb=ReadMe_newContent_begin.txt
fe=ReadMe_newContent_end.txt

grep 'place@of@TOC' $f --color
line=`grep -n 'place@of@TOC' $f | cut -d':' -f1`
#echo $line
if((line>0))
then
  tl=`cat $f | wc -l`
  ((b=line-1))
  ((e=tl-line))
#echo $tl'='$b'+'$e
  head -n $b $f > $fb
  tail -n $e $f > $fe
fi
##concat
cat $fb $fo $fe > $f

#clean
rm $fo $fb $fe

exit

tail $fb
echo 'TOC'
head $fe
echo '...'
