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
{/*
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
        CImg<int> profile(image.width(),1,1,1,0);//fill 0
  image.display(file_i);
  image.print("image");
//  profile=image.get_shared_row(image.width()/2);
  CImgDisplay disp;
  disp.assign(image.width(),image.height());
  disp.set_title("live display");
  image.display(disp);

  image.print("image+displ");
  image.display("image");

  profile.display_graph("profile");
  disp.wait(555);

  //line loop
  int i=0;
  while( !disp.is_closed() )
  {
    disp.wait(555);
    image.print("image loop");
    profile=image.get_shared_row(i++);
    profile.print("image[i]",false);
    image.display(disp);
    if(i==image.width()) {i=0;}
  }
  */
  	  CImg<unsigned char> image("CImg_logo.png"), visu(500,400,1,3,0);
  const unsigned char red[] = { 255,0,0 }, green[] = { 0,255,0 }, blue[] = { 0,0,255 };
  image.blur(2.5);
  CImgDisplay main_disp(image,"loop over lines"), draw_disp(visu,"Intensity profile");
  int i=0;
  while (!main_disp.is_closed() && !draw_disp.is_closed()) {
    main_disp.wait(222);
    
      visu.fill(0).draw_graph(image.get_shared_row(i++),red,1,1,0,255,0).display(draw_disp);
      if(i==image.width()) {i=0;}
    }

  return 0;
}//main
