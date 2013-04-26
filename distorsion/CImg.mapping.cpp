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

//mapping library (CImg)
#include "mapping.h"

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

  int ret;
  //source image
  const cimg_library::CImg<int> src_img(input_file_name.c_str());
//! \todo _ mkfct: init_map(...) load_map,map_image,map_expansion
  //warping grid
  cimg_library::CImg<float> map;
  if(( ret=load_map(warping_file_name,map) )!=0) return ret;

  //mapped image
  cimg_library::CImg<int> map_img;
  if(( ret=map_image(size_file_name,width,height,map_img) )!=0) return ret;

  //warping grid expansion related to mapped image sizes
  if(( ret=map_expansion(width,height,map) )!=0) return ret;

  //depth map of mapping plane
  cimg_library::CImg<float> z_map;
//! \todo . map any plane (passing through 3 points for example).
  if(( ret=map_plane(z0,map_img,z_map) )!=0) return ret;
  //image mapping
  if(( ret=mapping(map,z_map,src_img,map_img) )!=0) return ret;
  ///save
std::cerr<<"information: saving \""<<output_file_name.c_str()<<"\".\n"<<std::flush;
  map_img.save(output_file_name.c_str());
  return 0;
}//main

