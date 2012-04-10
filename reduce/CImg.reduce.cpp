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
//! get maximum position in a search area around a point
/**
 * \param profile: image for maximum finding
 * \param x: estimated position
 * \param sx: half search size
 * \return measured position
**/
template<typename T>
int get_maximum_position(CImg<T> profile,int x0,int sx)
{
  CImg<T> range=profile.get_crop(x0-sx,x0+sx);
  T max=-1;
  int posx;
  cimg_forX(range,x) if(range(x)>max) {posx=x;max=range(x);}
  return x0+posx-sx;
}
//! get minimum position in a search area around a point
/**
 * \param profile: image for minimum finding
 * \param x0: start position
 * \param x1: end position
 * \return measured position
**/
template<typename T>
int get_minimum_position(CImg<T> profile,int x0,int x1)
{
  CImg<T> range=profile.get_crop(x0,x1);
  T min=65000;
  int posx;
  cimg_forX(range,x) if(range(x)<min) {posx=x;min=range(x);}
  return x0+posx;
}

int main(int argc,char **argv)
{
  //Display program usage, when invoked from the command line with option '-h'.
  cimg_usage("reduce image along one direction.");
  //Read image filename from the command line
  const char* file_i1=cimg_option("-R","image1.PNG","Input  image 1");
  const char* file_i2=cimg_option("-G","image2.PNG","Input  image 2");
  const char* file_i3=cimg_option("-B","image3.PNG","Input  image 3");
  const char* file_o =cimg_option("-o","profile123.PNG","Output profile 1, 2 and 3");
  //help
  const bool help=cimg_option("-h",false,"display this help.");
  //exit on help request '-h' command line option
  if(help) return 0;
  //Load an image
  const CImg<int> image1(file_i1);
        CImg<int> profile1(image1.width(),1,1,1,0);//fill 0
  const CImg<int> image2(file_i2);
        CImg<int> profile2(image2.width(),1,1,1,0);//fill 0
  const CImg<int> image3(file_i3);
        CImg<int> profile3(image3.width(),1,1,1,0);//fill 0
  //reduce along x direction
  cimg_forXY(image1,x,y)
  {
    profile1(x)+=image1(x,y);
  }
  profile1/=image1.height();
  cimg_forXY(image2,x,y)
  {
    profile2(x)+=image2(x,y);
  }
  profile2/=image2.height();
  cimg_forXY(image3,x,y)
  {
    profile3(x)+=image3(x,y);
  }
  profile3/=image3.height();
  //gather on single graph (RGB)
  CImg<int> profile(profile1.width(),1,1,3,0);
  profile.draw_image(0,0,0,0,profile1);//R
  profile.draw_image(0,0,0,1,profile2);//G
  profile.draw_image(0,0,0,2,profile3);//B
  profile.display_graph("RGB");
  //save graphs as image
  profile.save(file_o);
  //get maximum positions
  CImg<int> x01(3,2,1,1,0);//(RGB,peak#)//fill 0
  {
  CImg<int> range=profile.get_select("select roughly dx to measure",1/*vector*/);
  //range.display("range");
  int x0=range(0);int x1=range(3);
  //half search size
  int sx=(x1-x0)*0.4;//<0.5
  //get maximum position 0 p1
  x01(0,0)=get_maximum_position(profile1,x0,sx);
  //get maximum position 1 p1
  x01(0,1)=get_maximum_position(profile1,x1,sx);
  //get maximum position 0 p2
  x01(1,0)=get_maximum_position(profile2,x0,sx);
  //get maximum position 1 p2
  x01(1,1)=get_maximum_position(profile2,x1,sx);
  }//maximum position
  //get displacements
  CImg<int> dx(3);//(RGB)
  cimg_forX(x01,x) dx(x)=x01(x,1)-x01(x,0);
dx.print("RGB displacement",false);
  int ddx=dx(1)-dx(0);
  std::cout<<"displacement error="<<ddx<<" pixel (i.e. "<<ddx*100/(dx(1)+dx(0)/2)<<"%)\n"<<std::flush;
  //get widths
  CImg<int> wx(3,2,2,1,0);//(RGB,peak#,bfw)//fill 0
  {
  int x0=x01(0,0);//maximum
  int x1=x01(0,1);//minimum//estimated
  //get minimum position
  x1=get_minimum_position(profile1,x0,x1);
  //get edge position
  int med=profile1(x0)-profile1(x1);//=max-min
  //get edge position 0
  CImg<int> range=profile1.get_crop(x0,x1);
  int posx=-1;
  cimg_forX(range,x) if(range(x)>med) posx=x;//! \todo while loop instead
  wx(0,0,1)=posx;
  //get edge position 1
  x1=x0;x0-=wx(0,0)*1.5;
  range=profile1.get_crop(x0,x1);
  posx=-1;
  cimg_forX(range,x) if(range(x)>med) posx=x;//! \todo while loop instead
//  wx(0,0,0)=posx??;//! \todo set width
  wx(0,0,0)=-wx(0,0,1);
  //get minimum position p2
//  wx(1,0)=2*(get_minimum_position(profile2,x01(1,0),x01(1,1))-x01(1,0));
  }//width
wx.print("RGB width",false);
  std::cout<<"displacement error="<<ddx<<" pixel (i.e. "<<ddx*100/(dx(1)+dx(0)/2)<<"%)\n"<<std::flush;
  //draw peak positions
  profile3.fill(0);
  //plot minimum
  cimg_forXYZ(wx,x,y,z) profile3(x01(x,y)+wx(x,y,z))=128;
  //plot maximum
  cimg_forXY(x01,x,y) profile3(x01(x,y))=256;
  profile.draw_image(0,0,0,2,profile3);//B
  profile.display_graph("RG and peak positions");
  return 0;
}

