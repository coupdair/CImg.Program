// Include CImg library file and use its main namespace
#include "CImg.h"
using namespace cimg_library;

#include <iostream>
//debug macro
#if cimg_verbosity>=3
#define PR(value) std::cerr<<#value<<"="<<value<<std::endl<<std::flush;
#else
#define PR(value) ;
#endif

// Main procedure
int main(int argc,char **argv) {
  cimg_usage("mem\n"
  "  examples:\n"
  "  ./CImg.mem -x 1024 -y 1024 -z 1024 -s 1\n"
  );
  const int w = cimg_option("-x",1024,"width");
  const int h = cimg_option("-y",1024,"height");
  const int d = cimg_option("-z",12,"depth");
  const int c = cimg_option("-c",1,"spectrum");
  const unsigned char v = cimg_option("-v",123,"value");
  //help
  const bool help=cimg_option("-h",false,"display this help.");
  //exit on help request '-h' command line option
  if(help) return 0;
  cimg::tic();
  CImg<unsigned char> image(w,h,d,c,v);
  cimg::toc();  cimg::tic();
  image.print("mem");
  cimg::toc();  cimg::tic();
  image.fill(v);
  cimg::toc();  cimg::tic();
  image.print("fill");
  cimg::toc();  cimg::tic();
  image.fill(v*2);
  cimg::toc();  cimg::tic();
  image.print("fill*2");
  cimg::toc();
  return 0;
}

