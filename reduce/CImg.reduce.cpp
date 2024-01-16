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
  const CImg<unsigned char> image(file_i);
        CImg<unsigned char> profile(image.width(),1,1,1,0);//fill 0
        CImg<unsigned char> profimg(image.width(),image.height(),1,1,0);//fill 0
  const unsigned char red[] = { 255,0,0 }, green[] = { 0,255,0 }, blue[] = { 0,0,255 };
  //image (lock)
  image.display(file_i);
  image.print("image");
  //line
  profile=image.get_shared_row(image.height()/2);

  CImgDisplay disp;
  disp.assign(image.width(),image.height());
  disp.set_title("live profile");
  image.display(disp);

  //line (lock)
  profile.display_graph("middle profile");

  //line loop
  int i=image.height()/2;
  while( !disp.is_closed() )
  {
    disp.wait(222);
    profile=image.get_shared_row(i++);
    //profile.print("image(*,i)",false);
    profimg.fill(0).draw_graph(profile,red,1,1,0,255,0).display(disp);
    if(i==image.height()) {i=0;}
  }
  return 0;
}//main
