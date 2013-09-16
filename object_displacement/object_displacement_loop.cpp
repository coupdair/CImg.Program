//std
#include <iostream>
#define PR(value) std::cerr<<#value<<"="<<value<<std::endl<<std::flush;
//CImg
#include "CImg.h"
using namespace cimg_library;
#ifndef cimg_imagepath
#define cimg_imagepath "img/"
#endif

//image processing function
int position(CImg<int> &image,float &pos_x,float &pos_y)
{
//background removal 1
  //load background image from file
//  CImg<int> background(bg_file_name.c_str());
  //background removal
//  image-=background;
  //display image
//  image.display("image-background");
//background removal 2
  //ramp illumination removal
//  image-=image.get_erode(3);
  //display image
//  image.display("image-erosion");
//threshold
  //threshold
//  image.threshold(3);
  //display image
//  image.display("threshold");
//mass center
  pos_x=pos_y=0;
  {
  int n=0;
  cimg_forXY(image,x,y){ if(image(x,y)==1){pos_x+=x;pos_y+=y;n++;} }
  pos_x/=n;pos_y/=n;
  }
//  PR(pos_x);PR(pos_y);
  return 0;
}

//main function
int main(int argc,char **argv)
{
//initialisation
  cimg_usage("object displacement\n\nexample: ls object_??.png | object_displacement -i sdtin");
  //get file name path
  std::string file_name=cimg_option("-i","image.png","input image [in] (e.g. -i stdin)");
//  std::string bg_file_name=cimg_option("-b","background.png","background image [in]");
  //set file name number (1 if -i, otherwise max)
  int file_name_number;
  if(file_name!="stdin") file_name_number=1;
  else
  {
    file_name_number=1<<23;//signed 32bit-max 08bit: 31-8
    std::cin>>file_name;
  }
//image
  CImg<int> image;
//position (may be over sized)
  CImg<float> pos(file_name_number,2);//position i: (i,0)=x, (i,1)=y
//image loop
  CImg<int> images;
  int n=0;
  for(int i=0;i<file_name_number;i++,n++)
  {
    //load image from file
    image.load(file_name.c_str());
    //image sum for a kind of all image one one
    if(n==0) images=image; else images+=image;
    //display image
//    image.display("loaded image");
    //negate
    image.normalize(image.max(),image.min());
    //display image
//    image.display("negate image");
    //position from image processing
    position(image,pos(i,0),pos(i,1));
    //print result
    std::cout<<file_name<<"\t"<<pos(i,0)<<"\t"<<pos(i,1)<<"\t"<<"\n";
    //next file name
    if(file_name_number>1)
    {
      std::string tmp_file_name;
      std::cin>>tmp_file_name;
      if(tmp_file_name.empty()) {n++;break;}
      file_name=tmp_file_name;
    }//next file name
  }//for images
PR(n);
  //resize to exact number of images
  pos.crop(0,0,n-1,1);
pos.print("position(x,y)");
  //display x and y position for all images
  images/=n;
  cimg_forX(pos,i) images(pos(i,0),pos(i,1),0,1)=255;
  images.display("images and positions");
  //display graph of x and y position
  if(n>1)
  {
    (pos.get_shared_row(0)).display_graph("x position");
    (pos.get_shared_row(1)).display_graph("y position");
  }
  return 0;
}

