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
//  image.display(file_i);
  image.print("image");
  //line
  int i=image.height()/2;
  profile=image.get_shared_row(i);

  CImgDisplay disp;
 while( true )
 {
  //reset display
  disp.assign(image.width(),image.height());
  disp.set_title("live profile");
  image.display(disp);
  disp.wait(555);

  //line loop
  while( !disp.is_closed() )
  {
    disp.set_title("live profile#%d/%d",i,image.height());
    profile=image.get_shared_row(i++);
    //profile.print("image(*,i)",false);
    profimg.fill(0).draw_graph(profile,red,1,1,0,255,0).display(disp);
    //break on mouse
    if (disp.button()) break;
    //reset line
    if(i==image.height()) {i=0;}
    disp.wait(222);
  }//live loop
  
  //line (lock)
  char title[512];
  if(--i<0) i=0;
  cimg_sprintf(title,"profile#%d/%d",i,image.height());
  profile.display_graph(title);
 }//lock loop
  return 0;
}//main
