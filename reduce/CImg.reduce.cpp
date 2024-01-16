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

int main(int argc,char **argv)
{
  //Display program usage, when invoked from the command line with option '-h'.
  cimg_usage("reduce image along one direction.");
  //Read image filename from the command line
  const char* file_i=cimg_option("-i","image.PNG","Input image");
  const char* file_o=cimg_option("-o","profile123.PNG","Output profile");
  //help
  const bool help=cimg_option("-h",false,"display this help.");
  //exit on help request '-h' command line option
  if(help) return 0;
  //Load an image
  const CImg<int> image(file_i);
        CImg<float> profile(image.width(),1,1,1,0);//fill 0
  image.display(file_i);
  profile=image.get_shared_row(image.width()/2);
  profile.display_graph("profile");
  return 0;
}

