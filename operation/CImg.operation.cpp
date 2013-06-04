//STL
#include <string>
// Include CImg library file and use its main namespace
///PlugIns
#define cimg_plugin           "../CImg.PlugIn/PlugIn.CImg.h"
//#define cimgnamespace_plugin  "../CImg.PlugIn/PlugIn.CImgLibrary.h"
///CImg lib
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
  cimg_usage("operation between 2 images: either maximum or subtraction.");
  //Read image filename from the command line
  const char* file_i1=cimg_option("-i1","image1.PNG","Input  image 1");
  const char* file_i2=cimg_option("-i2","image2.PNG","Input  image 2");
  const std::string operation=cimg_option("--operation","maximum","image operation either maximum or subtraction");
  const char* file_o =cimg_option("-o" ,"imageS.PNG","Output image: either maximum R=max(1,2) or substraction R=1-2");
  //help
  const bool help=cimg_option("-h",false,"display this help.");
  //exit on help request '-h' command line option
  if(help) return 0;
  //Load an image
  const CImg<int> image1(file_i1);
        CImg<int> image2(file_i2);
  if(operation=="maximum")
  {
    image2.max(image1);
    image2.save(file_o);
  }
  else
  {
    CImg<int> image(image1-image2);
    image.save(file_o);
  }
  return 0;
}

