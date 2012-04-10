//std
#include <iostream>
#define PR(value) std::cerr<<#value<<"="<<value<<std::endl<<std::flush;
//CImg
#include "CImg.h"
using namespace cimg_library;
#ifndef cimg_imagepath
#define cimg_imagepath "img/"
#endif

//main function
int main(int argc,char **argv)
{
////initialisation
  cimg_usage("object displacement");
  //get file name path
  std::string file_name=cimg_option("-i","image.png","input image [in]");
  std::string bg_file_name=cimg_option("-b","background.png","background image [in]");
////image
  //load image from file
  CImg<int> image(file_name.c_str());
  //display image
  image.display("loaded image");
////background removal 1
  //load background image from file
//  CImg<int> background(bg_file_name.c_str());
  //background removal
//  image-=background;
  //display image
//  image.display("image-background");
  //negate
//  image.normalize(image.max(),image.min());
  //display image
//    image.display("negate image");
////background removal 2
  //ramp illumination removal
//  image-=image.get_erode(3);
  //display image
//  image.display("image-erosion");
////threshold
  //threshold
//  image.threshold(3);
  //display image
//  image.display("threshold");
////mass center
  float pos_x,pos_y;
  pos_x=pos_y=0;
  {
  int n=0;
  cimg_forXY(image,x,y){ if(image(x,y)==1){pos_x+=x;pos_y+=y;n++;} }
  pos_x/=n;pos_y/=n;
  }
//  PR(pos_x);PR(pos_y);
////print result
//  std::cout<<file_name<<"\t"<<pos_x<<"\t"<<pos_y<<"\t"<<"\n";
  return 0;
}

