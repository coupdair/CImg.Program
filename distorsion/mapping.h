//mapping
/*-----------------------------------------------------------------------
  File        : mapping.h
  Description : image mapping
  Authors     : Sebastien COUDERT
-----------------------------------------------------------------------*/

/** \todo mapping developper page
 *
 *
**/

//standard library
#include <iostream>
#include <string>
//CImg Library
#include "../../CImg/CImg.h"

//! load warping grid
/**
 * \param [in] warping_file_name: file name from warping program containing warping coefficients.
 * \param [out] map: warping warping coefficients, i.e. mapping grid.
**/
template<typename T>
int load_map(const std::string &warping_file_name,cimg_library::CImg<T> &map)
{
  //warping grid
  map.load(warping_file_name.c_str());//(2,2,>0,>2)
map.print("map");
  ///check dimensions, i.e. 4 corner points: topleft, topright, bottomleft, bottomright in 2D connectivity
  if(map.width()!=2)   return -1;//x connectivity
  if(map.height()!=2)  return -2;//y connectivity
  if(map.depth()<1)    return -3;//z connectivity =1 for 2D warping and >1 for 3D warping
  if(map.spectrum()<2) return -4;//(x,y(,z)) coordinates, i.e. x and y components for 2D warping or x, y and z for 3D warping
  return 0;
}//load_map

//! load (or initialise) mapped image
/**
 * \param [in] size_file_name: file name from warping program containing image sizes.
 * \param [in/out] width: mapped image width (might be updated by file loading).
 * \param [in/out] height: mapped image height (might be updated by file loading).
 * \param [out] map_img: mapped image (initialised in this function).
**/
template<typename T>
int map_image(const std::string &size_file_name,int &width,int &height,cimg_library::CImg<T> &map_img)
{
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
  return 0;
}//map_image

//! expand map regarding to map image sizes
/**
 * \param [in] width: mapped image width.
 * \param [in] height: mapped image height.
 * \param [out] map: map grid (resized in this function).
**/
template<typename T>
int map_expansion(const int width,const int height,cimg_library::CImg<T> &map)
{
  map.resize(width,height,-100,-100,3/*bilinear*/);
map.print("map grid");
  return 0;
}//map_expansion

//! expand map regarding to map image
/**
 * \param [in] map_img: mapped image for width and height values only.
 * \param [out] map: map grid (resized in this function).
**/
template<typename T,typename Tgrid>
int map_expansion(const cimg_library::CImg<T> &map_img,cimg_library::CImg<Tgrid> &map)
{
  return map_expansion(map_img.width(),map_img.height(),map);
}//map_expansion

//! set plane equation from one point and normal vector 
template<typename T>
cimg_library::CImg<T> plane_by_1_point_and_1_normal_vector(cimg_library::CImg<T> p0,cimg_library::CImg<T> n)
{
//! \todo [high] _ check sizes (see plane_by_1_point_and_2_vectors)
  cimg_library::CImg<T> plane;//plane equation: ax+by+cz+d=0
  cimg_forY(n,i) plane[i]=n[i];//(a,b,c)=n=u^v
  T d=0;
  cimg_forY(p0,i) d+=plane[i]*p0[i];
  plane[3]=-d;//d=-(a*x0+b*y0+c*z0)
  return plane;
}//plane_by_1_point_and_1_normal_vector

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
//! \bug [high] _ make u^v as normal vector to plane
  cimg_forY(u,i) plane[i]=u[i];//(a,b,c)=u^v
  T d=0;
  cimg_forY(p0,i) d+=plane[i]*p0[i];
  plane[3]=-d;//d=-(a*x0+b*y0+c*z0)
//! \todo [high] _ call plane_by_1_point_and_1_normal_vector(p0,u^v)
  return plane;//plane_by_1_point_and_1_normal_vector(p0,u^v)
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
cimg_library::CImg<T> plane_by_3_points(cimg_library::CImg<T> points)
{
//plane defined by 3 points: (point,0,0,x/y/z) x/y/z components in [pixel,pixel,plane] units
  cimg_library::CImg<T> p0(1,3,1,1, points(0,0,0,0),points(0,0,0,1),points(0,0,0,2));
  cimg_library::CImg<T> p1(1,3,1,1, points(1,0,0,0),points(1,0,0,1),points(1,0,0,2));
  cimg_library::CImg<T> p2(1,3,1,1, points(2,0,0,0),points(2,0,0,1),points(2,0,0,2));
  return plane_by_3_points(p0,p1,p2);
}//plane_by_3_points

//! depth map of mapping plane
/**
 * \param [in] z0: z position of the plane
 * \param [in] map_img: mapped image for width and height values only.
 * \param [out] z_map: depth map set in this function.
**/
template<typename T,typename Tgrid>
int map_plane(const float/*points or */z0,const cimg_library::CImg<T> &map_img,cimg_library::CImg<Tgrid> &z_map)
{
//! \todo . map any plane (passing through 3 points for example).
  z_map.assign(map_img.width(),map_img.height());
/*
  cimg_library::CImg<float> points(3,1,1,3);//plane defined by 3 points: (point,0,0,x/y/z) x/y/z components in [pixel,pixel,plane] units
//set z0 plane
{
points.fill(0);//set all to 0 by default, e.g. origin i.e. (0,0)
points(1,0,0,0)=1;//x axis i.e. (1,0)
points(2,0,0,1)=1;//y axis i.e. (0,1)
cimg_forX(points,i) points(i,0,0,2)=z0;//set all z to z0
points.print("points at z0");
}
  //! \todo . plane by 3 points: ax+by+cz+d=0
  cimg_library::CImg<float> plane=plane_by_3_points(points);
plane.print("plane");
*/
  //bilinear(x,y) from 3 z positions
  cimg_forXY(z_map,x,y)
    z_map(x,y)=z0;//plane z=cst
  //! \todo . z map for plane
//    z_map(x,y)=-(x*plane[0]+y*plane[1]+plane[3])/plane[2];//z=-(ax+by+d)/c
z_map.print("z map of plane");
  return 0;
}//map_plane

//! image mapping
/**
 * \param [in] map: map grid.
 * \param [in] z_map: depth map.
 * \param [out] map_img: mapped image set in this function.
**/
template<typename T,typename Tgrid>
int mapping(const cimg_library::CImg<Tgrid> &map,const cimg_library::CImg<Tgrid> &z_map,const cimg_library::CImg<T> &src_img,cimg_library::CImg<T> &map_img)
{
//! \todo [low] check sizes 
  cimg_forXY(map_img,x,y)
    map_img(x,y)=src_img(map.linear_atXYZ(x,y,z_map(x,y),0),map.linear_atXYZ(x,y,z_map(x,y),1)); //closest
//    map_img(x,y)=src_img.linear_atXY(map.linear_atXYZ(x,y,z0,0),map.linear_atXYZ(x,y,z0,1)); //bilinear
  return 0;
}//mapping

