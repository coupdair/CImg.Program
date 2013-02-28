//warping
/*-----------------------------------------------------------------------
  File        : CImg.mapping.cpp
  Description : GUI for marker selection
  Authors     : Sebastien COUDERT
-----------------------------------------------------------------------*/

/*Additional documentation for the generation of the reference page (using doxygen)*/
/** \todo warping user page
 *
 *
**/
//standard library
#include <iostream>
#include <string>
//CImg Library
#include "../../CImg/CImg.h"

//! GUI to select point using mouse
template<typename Timg, typename Tpts>
int get_point(cimg_library::CImg<Timg> &color_image,cimg_library::CImg<Tpts> &point,
  cimg_library::CImgDisplay &display)
{
  //selection of a point
  cimg_library::CImg<int> selection=color_image.get_select(display,1);
  //transfer point
  point(0)=selection(0);
  point(1)=selection(1);
//selection.print("selection");//size = (1,6,1,1), data = [ 253 ; 214 ; 0 ; 253 ; 214 ; 0 ]
  //draw selected point
  const Timg color[3]={0,255,0};
  color_image.draw_point(point(0),point(1),color);
  display.display(color_image);
  return 0;
}//get_point

//! window of interest (i.e. region around marker)
template<typename Timg, typename Tpts, typename Troi,typename Tcolor>
int get_roi(const cimg_library::CImg<Timg> &binary_image,const cimg_library::CImg<Tpts> &point,cimg_library::CImg<Troi> &rectangle,
  cimg_library::CImg<Tcolor> &color_image,cimg_library::CImgDisplay &display)
{
  //set start point for searching window around marker
  int x0,y0,x1,y1,s=2;
  x0=x1=point(0);x0-=s;x1+=s;
  y0=y1=point(1);y0-=s;y1+=s;
  cimg_library::CImg<Timg> roi;
  cimg_library::CImg<bool> expand(4,1,1,1,false);
//! \todo [low] done could be removed for expand only in the while condition
  bool done=false;
  do
  {//expand ROI along y axis in upper direction
//! \todo [low] better use count instead of max/min
    roi=binary_image.get_crop(x0,y0,x1,y1);
    if((roi.get_shared_line(0)).max()==1
     &&(roi.get_shared_line(0)).min()==1) expand(0)=true;
    else y0-=s;
    if((roi.get_shared_line(roi.height()-1)).max()==1
     &&(roi.get_shared_line(roi.height()-1)).min()==1) expand(1)=true;
    else y1+=s;
    if((roi.get_crop(0,0,0,roi.height()-1)).max()==1
     &&(roi.get_crop(0,0,0,roi.height()-1)).min()==1) expand(2)=true;
    else x0-=s;
    if((roi.get_crop(roi.width()-1,0,roi.width()-1,roi.height()-1)).max()==1
     &&(roi.get_crop(roi.width()-1,0,roi.width()-1,roi.height()-1)).min()==1) expand(3)=true;
    else x1+=s;
    if(expand.max()==true&&expand.min()==true) done=true;
//roi.display("ROI");
  }while(!done);
  rectangle(0,0)=x0;
  rectangle(1,0)=x1;
  rectangle(0,1)=y0;
  rectangle(1,1)=y1;
const int color[3]={255,0,0};//red
color_image.draw_rectangle(x0,y0,x1,y1,color,0.5);
display.display(color_image);
  return 0;
}//get_roi

//! binary gravity center
template<typename Timg, typename Tpts, typename Troi,typename Tcolor>
int get_position_binary(const cimg_library::CImg<Timg> &binary_image,const cimg_library::CImg<Troi> &rectangle,cimg_library::CImg<Tpts> &point,
  cimg_library::CImg<Tcolor> &color_image,cimg_library::CImgDisplay &display)
{
  cimg_library::CImg<int> window=binary_image.get_crop(rectangle(0,0),rectangle(0,1),rectangle(1,0),rectangle(1,1));
//rectangle.print("rectangle");
//window.display("marker");
  window.normalize(1,0);
//window.display("marker as negate");
//window.print("marker as binary negate");
  //binary gravity center
  float xg=0,yg=0;int n=0;
  cimg_forXY(window,x,y) if(window(x,y)==1) {xg+=x;yg+=y;++n;}
  xg/=n;yg/=n;
  point(0)=rectangle(0,0)+xg;
  point(1)=rectangle(0,1)+yg;
//std::cout<<"position: xg="<<xg<<" yg="<<yg<<" rectangle(0,0)="<<rectangle(0,0)<<" rectangle(0,1)="<<rectangle(0,1)<<std::endl;
const int color[3]={0,0,255};//blue
color_image.draw_point(point(0),point(1),color);
display.display(color_image);
  return 0;
}//get_position_binary

//! greylevel gravity center
template<typename Timg, typename Tpts, typename Troi,typename Tcolor>
int get_position_greylevel(const cimg_library::CImg<Timg> &image,const cimg_library::CImg<Troi> &rectangle,cimg_library::CImg<Tpts> &point,
  cimg_library::CImg<Tcolor> &color_image,cimg_library::CImgDisplay &display)
{
  cimg_library::CImg<int> window=image.get_crop(rectangle(0,0),rectangle(0,1),rectangle(1,0),rectangle(1,1));
//rectangle.print("rectangle");
//window.display("marker");
  window.normalize(window.max()-window.min(),0);
//window.display("marker as grey level negate");
window.print("marker as grey level negate");
  //grey level gravity center
  float xg=0,yg=0;int n=0;
  cimg_forXY(window,x,y) {xg+=x*window(x,y);yg+=y*window(x,y);n+=window(x,y);}
  xg/=n;yg/=n;
  point(0)=rectangle(0,0)+xg;
  point(1)=rectangle(0,1)+yg;
//std::cout<<"position: xg="<<xg<<" yg="<<yg<<" rectangle(0,0)="<<rectangle(0,0)<<" rectangle(0,1)="<<rectangle(0,1)<<std::endl;
const int color[3]={0,255,255};//cyan
color_image.draw_point(point(0),point(1),color);
display.display(color_image);
  return 0;
}//get_position_greylevel

//! local magnification
template<typename Tpts>
int local_magnification(const std::string &title, const cimg_library::CImg<Tpts> &pt0,const cimg_library::CImg<Tpts> &pt1,const int cross_nb, const float cross_step, float &magnification,float &length)
{
  const float x0=pt0(0);
  const float x1=pt1(0);
  const float y0=pt0(1);
  const float y1=pt1(1);
//std::cout<<"0=("<<x0<<","<<y0<<") pixel\n";
//std::cout<<"1=("<<x1<<","<<y1<<") pixel\n";
  const float dx=x0-x1;
  const float dy=y0-y1;
  const float dX=std::sqrt(dx*dx+dy*dy);//dX (pixel)
  const float dXr=(cross_nb-1)*cross_step;//dX (m)
std::cout<<"length along "<<title<<"="<<dX<<" pixel, i.e. "<<dXr<<" meter\n";
std::cout<<"magnification="<<dXr/dX<<" m/pixel, i.e. "<<dX/dXr<<" pixel/m\n";
  length=dX;
  magnification=dXr/dX;
}//local_magnification

int main(int argc, char *argv[])
{ 
//commmand line options
 ///usage
  cimg_usage(std::string("warping program is intended to select 4 markers for warping coefficients (i.e. 4 corner points), \
it uses different GNU libraries (see --info option)\n\n \
GUI usage: 1. use black marker over white background image.\n \
           2. select 4 markers along X axis first and then Y\n \
              (e.g. firstly top/left, secondly top/right, thridly bottom/left and finally bottom/right).\n \
        note: selection of a black marker done using left button of mouse (i.e. click on black area any where on marker)\n\n \
usage: ./CImg.warping -h -I #help and compilation information\n \
       ./CImg.warping -i image.TIF -o warping.cimg -d 0\n \
       ./CImg.warping -i image.TIF -o warping.cimg -nx 9 -ny 9 -s 0.123\n \
       ./CImg.warping -i camera2_calib.TIF -ob camera2_ -nx 21 -ny 12 -s 0.321\n \
version: "+std::string(WARPING_VERSION)+"\t(library version: warpingFormat."+std::string(WARPING_FORMAT_VERSION)+")\n compilation date: " \
            ).c_str());//cimg_usage
  ///information and help
  const bool show_h   =cimg_option("-h",    false,NULL);//-h hidden option
        bool show_help=cimg_option("--help",show_h,"help (or -h option)");show_help=show_h|show_help;//same --help or -h option
  bool show_info=cimg_option("-I",false,NULL);//-I hidden option
  if( cimg_option("--info",show_info,"show compilation options (or -I option)") ) {show_info=true;cimg_library::cimg::info();}//same --info or -I option
  ///image files
  const std::string input_file_name= cimg_option("-i","image.TIF","calibration image [input].");
  std::string warping_file_name=cimg_option("-o","warping_points.cimg","warping coefficient (i.e. 4 corner points on image) [output].");
  const std::string  base_file_name=cimg_option("-ob","","output basename (e.g. \"-ob camera2_\" will output \"-os camera2_image_size.cimg\" and so on for -gx, -gy and -o options).");
  std::string  size_file_name=cimg_option("-os","image_size.cimg","image size in pixel [output for mapping].");
  std::string gridx_file_name=cimg_option("-gx","grid_x.cimg","grid of X axis in meter [output].");
  std::string gridy_file_name=cimg_option("-gy","grid_y.cimg","grid of Y axis in meter [output].");
  const int   cross_x_nb=cimg_option("-nx",11,"number of markers along X axis.");
  const int   cross_y_nb=cimg_option("-ny", 8,"number of markers along Y axis.");
  const float cross_step=cimg_option("-s",0.005,"step between crosses (meter).");
  const int GUI_delay=cimg_option("-d",2345,"delay to check result on display at the end of the program in ms (e.g. 0 no wait, but result can be seen in \"color.png\" image file).");
  ///stop if help requested
  if(show_help) {/*print_help(std::cerr);*/return 0;}
  //basename
  if(base_file_name!="")
  {
    std::cerr<<"information: using basename (i.e. -ob option as prefix) for all output files.\n";
    warping_file_name=base_file_name+warping_file_name;
    size_file_name=base_file_name+size_file_name;
    gridx_file_name=base_file_name+gridx_file_name;
    gridy_file_name=base_file_name+gridy_file_name;
  }//basename

  //calibration image
  cimg_library::CImg<int> img(input_file_name.c_str());
  ///force grey level image
  img.channel(0);
//img.display("img");
  //color image (for selection and point drawing)
  cimg_library::CImg<unsigned char> color_img(img.width(),img.height(),1,3);
  {
  cimg_library::CImg<unsigned char> image=img.get_normalize(0,255);
//image.print("image");
  cimg_forC(color_img,c) color_img.draw_image(0,0,0,c,image);
  color_img.print("color");
  }
  //color display (GUI)
  cimg_library::CImgDisplay disp;
  disp.display(color_img);

  //warping points
  cimg_library::CImg<float> pts(2);
  cimg_library::CImg<float> hand_map(2,1,1,4);//4 coner points of source image: x=(x,y),c=(tl,tr,bl,br) by hand
  cimg_library::CImg<float>      map(2,1,1,4);//4 coner points of source image: x=(x,y),c=(tl,tr,bl,br) by image processing
  cimg_forC(hand_map,c)
  {
    get_point(color_img,pts,disp);//or get_channel(c)
    //write point to map
    hand_map.draw_image(0,0,0,c,pts);
  }//get points
  //detect center
  ///threshold (using last clicked point)
  int min=img(pts(0),pts(1));
  int max=img.max();
  cimg_library::CImg<int> bin_img=img.get_threshold((max-min)/2);
//bin_img.display("binary");
  ///ROI around marker
  cimg_library::CImg<int> roi(2,2,1,4);//4 coner window corresponding to marker in source image: x,y=(x,y),c=(tl,tr,bl,br)
  cimg_forC(roi,c)
  {
    cimg_library::CImg<int> rectangle=roi.get_shared_channel(c);
    get_roi(bin_img,hand_map.get_shared_channel(c),rectangle,
      color_img,disp);
  }//get ROIs
  ///centroid
  cimg_forC(roi,c)
  {
    cimg_library::CImg<int> rectangle=roi.get_shared_channel(c);
    //binary gravity center
    get_position_binary(bin_img,rectangle,pts,color_img,disp);
    //grey level gravity center
    get_position_greylevel(img, rectangle,pts,color_img,disp);
    //write point to map
    map.draw_image(0,0,0,c,pts);
  }//get ROIs
  //average size i.e. X and Y average length and pixel size
  cimg_library::CImg<float> size(2,1,1,2);//image size and pixel size along X and Y axes.
  {
  float magn,len;
  local_magnification("X top",    map.get_shared_channel(0),map.get_shared_channel(1), cross_x_nb,cross_step, magn,len);//top    points i.e. magnification along X
  size(0,0)=magn; size(0,1)=len;
  local_magnification("X bottom", map.get_shared_channel(2),map.get_shared_channel(3), cross_x_nb,cross_step, magn,len);//bottom points i.e. magnification along X
  size(0,0)+=magn;size(0,1)+=len;
  local_magnification("Y left",   map.get_shared_channel(0),map.get_shared_channel(2), cross_y_nb,cross_step, magn,len);//left   points i.e. magnification along Y
  size(1,0)=magn; size(1,1)=len;
  local_magnification("Y right",  map.get_shared_channel(1),map.get_shared_channel(3), cross_y_nb,cross_step, magn,len);//right  points i.e. magnification along Y
  size(1,0)+=magn;size(1,1)+=len;
  size/=2;//average
  }//average size
  //save GUI display
std::cerr<<"information: saving \"color.png\"\r"<<std::flush;
  color_img.save("color.png");
  //reshape map: (x,y)=(tl,tr,bl,br), c=(x,y)
  map.permute_axes("zcyx");
  map.assign(2,2,1,2);
  //save warping
map.print("map");
std::cerr<<"information: saving \""<<warping_file_name.c_str()<<"\"\r"<<std::flush;
  map.save(warping_file_name.c_str());
  //save size
std::cerr<<"information: saving \""<<size_file_name.c_str()<<"\"\r"<<std::flush;
  size.save(size_file_name.c_str());
  //save grid
  {
  cimg_library::CImgList<float> grid(2);
  cimglist_for(grid,l) {grid[l].assign(size(l,1)); cimg_forX(grid[l],x) grid[l](x)=x*size(l,0);}
std::cerr<<"information: saving \""<<gridx_file_name.c_str()<<"\" and \""<<gridy_file_name.c_str()<<"\".\n"<<std::flush;
  grid[0].save(gridx_file_name.c_str());
  grid[1].save(gridy_file_name.c_str());
  }//save grid
cimg_library::cimg::sleep(GUI_delay);
  return 0;
}//main

