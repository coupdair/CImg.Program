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
int main(int argc,char **argv)
{
// Define program usage and read command line parameters
  // Display program usage, when invoked from the command line with option '-h'.
  cimg_usage("threshold the input image and then label it, i.e. set an index for all objects within the thresholded image."
  );
  // Read image filename from the command line (or set it to "img/lena.pgm" if option '-i' is not provided).
  const char* file_i = cimg_option("-i",cimg_imagepath "lena.pgm","Input image");
  // Read display zoom from the command line.
  const float zoom = cimg_option("--zoom",2.0,"zoom for displaying images");
  // Read threshold value from the command line, in order to binarize the image before labeling it.
  const int threshold=cimg_option("-t",128,"set threshold value for binary image");
  //help
  const bool help=cimg_option("-h",false,"display this help.");
  //exit on help request '-h' command line option
  if(help) return 0;
//load an image, transform it to a grey level image (if necessary)
  CImg<unsigned char> img(file_i);
  if(img.spectrum()==3) img.RGBtoHSI().channel(2)*255;
(img.get_resize(zoom*-100,zoom*-100)).display("source");
//threshold
  img.threshold(threshold);
(img.get_resize(zoom*-100,zoom*-100)).display("threshold");
//label
  img.label_regions();
(img.get_resize(zoom*-100,zoom*-100)).display("label");
//area (i.e. histogram use)
  CImg<int> aire;
  aire=img.get_histogram(img.max()-1,1,img.max());
aire.display_graph("Aires des objets numerotes",3,1,"numero d'object",0,0,"aire (px)",0,0);
  return 0;
}

