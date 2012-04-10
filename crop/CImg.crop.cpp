/*
 #
 #  File        : tutorial.cpp
 #                ( C++ source file )
 #
 #  Description : View the color profile of an image, along the X-axis.
 #                This file is a part of the CImg Library project.
 #                ( http://cimg.sourceforge.net )
 #
 #  Copyright   : David Tschumperle
 #                ( http://www.greyc.ensicaen.fr/~dtschump/ )
 #
 #  License     : CeCILL v2.0
 #                ( http://www.cecill.info/licences/Licence_CeCILL_V2-en.html )
 #
 #  This software is governed by the CeCILL  license under French law and
 #  abiding by the rules of distribution of free software.  You can  use,
 #  modify and/ or redistribute the software under the terms of the CeCILL
 #  license as circulated by CEA, CNRS and INRIA at the following URL
 #  "http://www.cecill.info".
 #
 #  As a counterpart to the access to the source code and  rights to copy,
 #  modify and redistribute granted by the license, users are provided only
 #  with a limited warranty  and the software's author,  the holder of the
 #  economic rights,  and the successive licensors  have only  limited
 #  liability.
 #
 #  In this respect, the user's attention is drawn to the risks associated
 #  with loading,  using,  modifying and/or developing or reproducing the
 #  software by the user in light of its specific status of free software,
 #  that may mean  that it is complicated to manipulate,  and  that  also
 #  therefore means  that it is reserved for developers  and  experienced
 #  professionals having in-depth computer knowledge. Users are therefore
 #  encouraged to load and test the software's suitability as regards their
 #  requirements in conditions enabling the security of their systems and/or
 #  data to be ensured and,  more generally, to use and operate it in the
 #  same conditions as regards security.
 #
 #  The fact that you are presently reading this means that you have had
 #  knowledge of the CeCILL license and that you accept its terms.
 #
*/
//! \todo [low] add doxygen documentation

// Include CImg library file and use its main namespace
#include "CImg.h"
using namespace cimg_library;

#ifndef cimg_imagepath
#define cimg_imagepath "img/"
#endif

#include <iostream>
//debug macro
#if cimg_verbosity>=3
#define PR(value) std::cerr<<#value<<"="<<value<<std::endl<<std::flush;
#else
#define PR(value) ;
#endif

// Main procedure
int main(int argc,char **argv) {
  cimg_usage("crop\n"
  "  examples:\n"
  "  ./CImg.crop -i logo -e .png -x 111 -y 55 -o _ #crop 4 quadrant\n"
  "  ./CImg.crop -i logo.png     -x 111 -y 55 -sx 128 -sy 64 -o logo_crop.png #crop rectangle\n"
  );
//! \todo [see _info] add usage examples: 1. add borders, 2. convert .PNG to .TIF
//! \todo [low] add percentage crop -x% -sx%
  const char* file_i = cimg_option("-i","image","Input image");
  const char* file_e = cimg_option("-e",".PNG","image extention");
  const char* file_o = cimg_option("-o","_","Output image UBLR");
  const int x = cimg_option("-x",666,"x crop");
  const int y = cimg_option("-y",730,"y crop");
  const int sx = cimg_option("-sx",0,"x size (default 4 quadrants otherwize crop)");
  const int sy = cimg_option("-sy",0,"y size");
  //help
  const bool help=cimg_option("-h",false,"display this help.");
  //exit on help request '-h' command line option
  if(help) return 0;
  if(sx==0||sy==0)
  {//4 quadrant
  //load source image
  std::string tmp;
  tmp=std::string(file_i)+file_e;
  CImg<unsigned char> image(tmp.c_str());
  CImg<unsigned char> img;
  //crop upper left and save it
  tmp=std::string(file_i)+file_o+std::string("UL")+file_e;
  img=image.get_crop(0,0,x,y);//image.width()-1,image.height()-1);
  img.save(tmp.c_str());
  //crop upper right and save it
  tmp=std::string(file_i)+file_o+std::string("UR")+file_e;
  img=image.get_crop(x,0,image.width()-1,y);
  img.save(tmp.c_str());
  //crop bottom left and save it
  tmp=std::string(file_i)+file_o+std::string("BL")+file_e;
  img=image.get_crop(0,y,x,image.height()-1);
  img.save(tmp.c_str());
  //crop bottom right and save it
  tmp=std::string(file_i)+file_o+std::string("BR")+file_e;
  img=image.get_crop(x,y,image.width()-1,image.height()-1);
  img.save(tmp.c_str());
  }//4 quadrant
  else
  {//crop
  //load source image
  CImg<unsigned char> image(file_i);
  //crop and save
  image.crop(x,y,x+sx,y+sy).save(file_o);
  }//crop
  return 0;
}

