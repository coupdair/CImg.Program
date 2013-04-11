//mapping
/*-----------------------------------------------------------------------
  File        : CImg.mapping.cpp
  Description : image mapping (noGUI; might be .display())
  Authors     : Sebastien COUDERT
-----------------------------------------------------------------------*/

/*Additional documentation for the generation of the reference page (using doxygen)*/
/** \mainpage
 *
 *  index:
 *  \li \ref sectionCommandLine
 *  \li \ref sectionMappingDocumentation
 *  \li \ref sectionDoxygenSyntax
 *
 *  \section sectionCommandLine command line options
 *
 *  \verbinclude "CImg.warping.help.output"
 *
 *  \verbinclude "CImg.mapping.help.output"
 *  
 *  \section sectionMappingDocumentation documentation outline
 *  This is the reference documentation of <a href="http://www.meol.cnrs.fr/">mapping</a>, from the <a href="http://www.univ-lille1.fr/lml/">LML</a>.\n\n
 *  image distorsion correction using warping then mapping software suite. The main function is in <a href="CImg_8warping_8cpp.html">CImg.warping.cpp</a> source file for warping and in <a href="CImg_8mapping_8cpp.html">CImg.mapping.cpp</a> source file for mapping.\n\n
 *  This documentation has been automatically generated from the sources, 
 *  using the tool <a href="http://www.doxygen.org">doxygen</a>. It should be readed as HTML, LaTex and man page.\n
 *  It contains both
 *  \li a detailed description of all classes and functions
 *  \li TODO: a user guide (cf. \ref pages.html "related pages")
 *
 *  that as been documented in the sources.
 *
 *  \par Additional needed libraries:
 *
 *  \li <a href="http://cimg.sourceforge.net">the CImg Library</a> (v1.?.?) for command line options only.
 *
 *  \section sectionDoxygenSyntax make documentation using Doxygen syntax
 *  Each function in the source code should be commented using \b doxygen \b syntax in the same file.
 *  The documentation need to be written before the function.
 *  The basic syntax is presented in this part.
 *  \verbinclude "doxygen.example1.txt"
 *
 *  Two kind of comments are needed for \b declaration and \b explanation \b parts of the function:
 *  Standart documentation should the following (\b sample of code documentation):
 *  \verbinclude "doxygen.example2.txt"
 *
 *  In both declaration and explanation part, \b writting and \b highlithing syntax can be the following:\n\n
 *  \li \c \\code to get\n
 *
 *  \li \c \\n    a new line
 *  \li \c \\li   a list (dot list)
 *
 *  \li \c \\b    bold style
 *  \li \c \\c    code style
 *  \li \c \\e    enhanced style (italic)
 *
 *  For making \b shortcut please use:\n
 *  \li \c \\see to make a shortcut to a related function or variable
 *  \li \c \\link to make a shortcut to a file or a function
 *  \note this keyword needs to be closed using \c \\end*
 *
 *  \li \c \\todo to add a thing to do in the list of <a href="todo.html">ToDo</a> for the whole program
 *
 *  In explanation part, \b paragraph style can be the following:\n
 *  \li \c \\code for an example of the function use
 *  \li \c \\note to add a few notes
 *  \li \c \\attention for SOMETHING NOT FULLY DEFINED YET
 *  \li \c \\warning to give a few warning on the function
 *  \note these keywords need to be closed using \c \\end*
 *
 *  \verbinclude "doxygen.example3.txt"
 *
 *  Many other keywords are defined, so please read the documentation of <a href="http://www.doxygen.org/commands.html">doxygen</a>.
 *
**/
/** \todo mapping user page
 *
 *
**/

//standard library
#include <iostream>
#include <string>
//CImg Library
#include "../../CImg/CImg.h"

//! set plane equation from 
template<typename T>
cimg_library::CImg<T> plane_by_1_point_and_2_vectors(cimg_library::CImg<T> p0,cimg_library::CImg<T> u,cimg_library::CImg<T> v)
{
  cimg_library::CImg<T> plane;//plane equation: ax+by+cz+d=0
  //check sizes
  if(p0.width()!=1 || p0.height()<3 ||
     u.is_sameXY(p0) || v.is_sameXY(p0)
    )
  {
    std::cerr<<__func__<<" error: specified point or vector are not 3d vectors.\n"<<std::flush;
    return plane;
/* throw CImgInstanceException(_cimg_instance
                                    "plane_by_*() : specified point or vector (%u,%u,%u,%u,%p) are not 3d vectors.",
                                    cimg_instance,
                                    p0._width,p0._height,p0._depth,p0._spectrum,p0._data);*/
  }//check
  //compute plane equation
  plane.assign(1,4,1,1,0);//plane equation: ax+by+cz+d=0
  cimg_forY(u,i) plane[i]=u[i];//(a,b,c)=u^v
  T d=0;
  cimg_forY(p0,i) d+=plane[i]*p0[i];
  plane[3]=-d;//d=-(a*x0+b*y0+c*z0)
  return plane;
}//plane_by_1_point_and_2_vectors

//! set plane equation from 3 points
template<typename T>
cimg_library::CImg<T> plane_by_3_points(cimg_library::CImg<T> p0,cimg_library::CImg<T> p1,cimg_library::CImg<T> p2)
{
  cimg_library::CImg<T> u(p1-p0);
  cimg_library::CImg<T> v(p2-p0);
  return plane_by_1_point_and_2_vectors(p0,u,v);
}//plane_by_3_points

//! set plane equation from 3 points
template<typename T>
CImg<T> plane_by_3_points(cimg_library::CImg<T> points)
{
//plane defined by 3 points: (point,0,0,x/y/z) x/y/z components in [pixel,pixel,plane] units
  cimg_library::CImg<T> p0(1,3,1,1, points(0,0,0,0),points(0,0,0,1),points(0,0,0,2));
  cimg_library::CImg<T> p1(1,3,1,1, points(1,0,0,0),points(1,0,0,1),points(1,0,0,2));
  cimg_library::CImg<T> p2(1,3,1,1, points(2,0,0,0),points(2,0,0,1),points(2,0,0,2));
  return plane_by_1_point_and_2_vectors(p0,p1,p2);
}//plane_by_3_points

//! main function begins program
int main(int argc, char *argv[])
{ 
//commmand line options
 ///usage
  cimg_usage(std::string("mapping program is intended to make mapping image base on warping coefficients (i.e. 4 corner points), \
it uses different GNU libraries (see --info option)\n\n \
usage: ./CImg.mapping -h -I #help and compilation information\n \
       ./CImg.mapping -i image.TIF -m warping.cimg -o mapped.png\n \
       ./CImg.mapping -i image.TIF -m warping.cimg -is image_size.cimg -o mapped.png\n \
version: "+std::string(MAPPING_VERSION)+"\t(other library versions: warpingFormat."+std::string(WARPING_FORMAT_VERSION)+")\n compilation date: " \
            ).c_str());//cimg_usage
  ///information and help
  const bool show_h   =cimg_option("-h",    false,NULL);//-h hidden option
        bool show_help=cimg_option("--help",show_h,"help (or -h option)");show_help=show_h|show_help;//same --help or -h option
  bool show_info=cimg_option("-I",false,NULL);//-I hidden option
  if( cimg_option("--info",show_info,"show compilation options (or -I option)") ) {show_info=true;cimg_library::cimg::info();}//same --info or -I option
  ///image files
  const std::string input_file_name= cimg_option("-i","image.TIF","image to map (i.e. source).");
  const std::string warping_file_name=cimg_option("-m","warping_coefficient.cimg","warping coefficient (i.e. 4 corner points on source image).");
  const float z0=cimg_option("-z",0.0,"z position of mapping plane in the 3D warped volume (e.g. -z 1.23 ; should be inside 3D warping indexes e.g. in range [0.0-1.0[ for 2 planes).");
  const std::string output_file_name=cimg_option("-o","mapped_image.PNG","mapped image (i.e. destination).");
  ////mapped image size: w,h
  int width= cimg_option("-W",321,"mapped image width.");
  int height=cimg_option("-H",123,"mapped image height.");
  const std::string size_file_name=cimg_option("-is","","image size in pixel [input from warping] (e.g. \"-is image_size.cimg\"; -W and -H ignored).");
  ///stop if help requested
  if(show_help) {/*print_help(std::cerr);*/return 0;}

  //source image
  const cimg_library::CImg<int> src_img(input_file_name.c_str());
  //warping grid
  cimg_library::CImg<float> map(warping_file_name.c_str());//(2,2,>0,>2)
map.print("map");
  ///check dimensions, i.e. 4 corner points: topleft, topright, bottomleft, bottomright in 2D connectivity
  if(map.width()!=2)   return -1;//x connectivity
  if(map.height()!=2)  return -2;//y connectivity
  if(map.depth()<1)    return -3;//z connectivity =1 for 2D warping and >1 for 3D warping
  if(map.spectrum()<2) return -4;//(x,y(,z)) coordinates, i.e. x and y components for 2D warping or x, y and z for 3D warping

  //mapped image
  cimg_library::CImg<int> map_img;
  if(size_file_name=="")//user size
    map_img.assign(width,height);
  else
  {//warping size (i.e. sizes from warping program)
    cimg_library::CImg<float> size(size_file_name.c_str());//(2,1,1,2);
size.print("size");
    //check dimensions
    if(size.width()!=2)    return -11;//(x,y)
    if(size.height()!=1)   return -22;
    if(size.depth()!=1)    return -33;
    if(size.spectrum()!=2) return -44;//(pixel_size,image_size)
    //get image size
    width= size(0,1);//image size along x
    height=size(1,1);//image size along y
    map_img.assign(width,height);
  }//warping size

  //warping grid expansion
  map.resize(width,height,-100,-100,3/*bilinear*/);
map.print("map grid");

  //depth map of mapping plane
//! \todo . map any plane (passing through 3 points for example).
  cimg_library::CImg<float> z_map(map_img.width(),map_img.height());
  cimg_library::CImg<float> points(3,1,1,3);//plane defined by 3 points: (point,0,0,x/y/z) x/y/z components in [pixel,pixel,plane] units
//set z0 plane
{
points.fill(0);//set all to 0 by default, e.g. origin i.e. (0,0)
points(1,0,0,0)=;//x axis i.e. (1,0)
points(2,0,0,1)=;//y axis i.e. (0,1)
cimg_forX(points,i) points(i,0,0,2)=z0;//set all z to z0
points.print("points at z0")
}
  cimg_library::CImg<float> plane=plane_by_3_points(points);
plane.print("plane");
  //bilinear(x,y) from 3 z positions
  cimg_forXY(z_map,x,y)
    z_map(x,y)=z0;//plane z=cst
//    z_map(x,y)=-(ax+by+d)/c;//! \todo . by 3 points: ax+by+cz+d=0
z_map.print("z map of plane");
  //image mapping
  cimg_forXY(map_img,x,y)
    map_img(x,y)=src_img(map.linear_atXYZ(x,y,z_map(x,y),0),map.linear_atXYZ(x,y,z_map(x,y),1)); //closest
//! \todo [medium] there is no need of z in map presently, but needs will come with any plane especially in real coordinates (see _ToDo.txt file content)
//    map_img(x,y)=src_img.linear_atXY(map.linear_atXYZ(x,y,z0,0),map.linear_atXYZ(x,y,z0,1)); //bilinear
  ///save
std::cerr<<"information: saving \""<<output_file_name.c_str()<<"\".\n"<<std::flush;
  map_img.save(output_file_name.c_str());
  return 0;
}//main

