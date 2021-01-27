/*-----------------------------------------------------------------------

  File        : display.cpp

  Description : display of image program of the Laboratory of Mechanics in Lille (LML)

  Author      : Sebastien COUDERT
  
  --------------------------------------------------------------------*/

/*Additional documentation for the generation of the reference page (using doxygen)*/
/** \mainpage
 *
 *  index:
 *  \li \ref sectionCommandLine
 *  \li \ref sectionDisplayDocumentation
 *  \li \ref sectionDoxygenSyntax
 *
 *  \section sectionCommandLine command line options
 *  \verbinclude "CImg.display.help.output"
 *
 *  \section sectionDisplayDocumentation documentation outline
 *  This is the reference documentation of <a href="http://www.meol.cnrs.fr/">CImg.display</a>, from the <a href="http://www.univ-lille1.fr/lml/">LML</a>.\n\n
 *  CImg.display is a image displaying software. The program begins in the main function in the <a href="CImg_8display_8cpp.html">CImg.display.cpp</a> source file.\n\n
 *  This documentation has been automatically generated from the CImg.display sources, 
 *  using the tool <a href="http://www.doxygen.org">doxygen</a>. It should be readed as HTML, LaTex and man page.\n
 *  It contains both
 *  \li a detailed description of all classes and functions
 *  \li a <a href="user.html">user guide</a>
 *
 *  that as been documented in the sources.
 *
 *  \par Additional needed libraries:
 *
 *  \li <a href="http://cimg.sourceforge.net">the CImg Library</a> (v1.3.9) using <a href="http://www.imagemagick.org/">ImageMagick</a> for a few image format
 *
 *  \par Optional libraries:
 *
 *  \li i/o <a href="http://www.unidata.ucar.edu/software/netcdf/">NetCDF</a> (network Common Data Form)
 *  \li added to CImg raw, <a href="http://www.rd-vision.com/">Hiris</a>, <a href="http://www.pco.de/">PCO</a> and <a href="http://www.lavision.de">LaVision</a> images support
 *  \li i/o <a href="http://www.libpng.org/">libPNG</a> (Portable Network Graphics) using <a href="http://www.zlib.net/">zLib</a> (non destructive compression)
 *  \li i/o <a href="http://www.libtiff.org/">libTIFF</a> (Tag Image File Format) - need libJPEG for static linking
 *  \li v  vector image <a href="http://libboard.sourceforge.net/">Board</a> (A vector graphics C++ library: Postscript, SVG and Fig files)
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

/** \page user user guide
 *
 * \todo use section (instead of paragraphs) and add table of contents (such as in mainpage)
 *
 * \par different type of display for image
 *
 * 3 types of display in this software:
 *  \li 2D map (default)
 *  \li 1D graph (\c --1D option)
 *  \li 3D surface (\c --3D option)
 *
 * others display command line options using \c -h option
 * \verbinclude "CImg.display.help.output"
 *
 * \par 2D map (default)
 * display image as map
 * \code
 *   ./CImg.display -i image.PNG
 * \endcode
 * GUI keyboard options:
 *  \li \c Ctrl+S: save current view
 * \image html CImg_map2D.png
 *
 * \par 1D graph
 * display image as both map and 1D graph(s) (either X axis or Y axis)
 * \code
 *   ./CImg.display -i image.PNG --1D
 * \endcode
 * GUI keyboard options:
 *  \li \c c: color
 *  \li \c v: value
 *  \li \c l: luminance
 *  \li \c i: intensity
 *  \li \c Ctrl+S: save current view
 *
 * GUI mouse options:
 *  \li \c left button: X axis
 *  \li \c right button: Y axis
 * \image html CImg_map2DNgraph1D.png
 *
 * \par 3D surface
 * display image as 3D surface (e.g. Gouraud-shaded or isophotes render)
 * \code
 *   ./CImg.display -i image.PNG --3D
 * \endcode
 * GUI keyboard options:
 *  \li \c F: toggle Fullscreen
 *  \li \c Q or ESC: Quit (i.e. exit)
 *
 * load or save file:
 *  \li \c S: Save displayed image (i.e. 3D view)
 *  \li \c O: save pOse (i.e. 3D view parameters)
 *  \li \c R: Read pose (i.e. 3D view parameters)
 *
 * render type:
 *  \li \c C: color render (image or constant)
 *  \li \c T: poinTs render
 *  \li \c L: Lines render
 *  \li \c A: fAces render
 *  \li \c H: flat-sHaded faces render
 *  \li \c G: Gouraud-shaded faces render
 *  \li \c P: Phong-shaded faces render
 *  \li \c I: Isophotes render
 *  \li \c BackSpace  : change rendering type (i.e. decrement type)
 *  \li any other key  : change rendering type (i.e. increment type)
 *
 * GUI mouse options:
 *  \li \c left button: rotate
 *  \li \c middle button: move
 *  \li \c wheel or \c right button: zoom in/out
 * \image html CImg_surface3D_all.png
**/

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

//! display image as both 2D map and 1D graphs along x or y axis
/**
 * \param [in] image : image to display
**/
template<typename T>
void display1D2D(CImg<T> image)
{
  //convert image to RGB
  image.resize(-100,-100,1,3);
  // Create two display window, one for the image, the other for the color profile.
  CImgDisplay
    main_disp(image,"Color image (Click on mouse buttons: left and right)",0),
    draw_disp(image.width(),512,"Color profile along X or Y axis",0);
  bool refresh_draw=true;
  // button, X and Y-coordinate of the mouse pointer over the image
  int bm,xm,ym;bm=xm=ym=0;
  // Define colors used to plot the profile, and a hatch to draw the vertical line
  unsigned long hatch = 0xF0F0F0F0;
  const unsigned char
            // R   G   B
    red[]   = {255,  0,  0},
    green[] = {  0,255,  0},
    blue [] = {  0,  0,255},
    black[] = {  0,  0,  0},
    white[] = {255,255,255};

  //display and post process image as color or grey scale
  CImg<unsigned char> image_pp(image);

  //event loop
  //This loop ends when one of the two display window is closed or when the keys 'ESC' or 'Q' are pressed.
  while(!main_disp.is_closed() && !draw_disp.is_closed() &&
        !main_disp.is_keyESC() && !draw_disp.is_keyESC() && !main_disp.is_keyQ() && !draw_disp.is_keyQ())
  {
    // Handle display window resizing (if any)
    if (main_disp.is_resized()) main_disp.resize().display(image);
    draw_disp.resize();
    //key board
    if(main_disp.is_keyC()||main_disp.is_keyV()||main_disp.is_keyL()||main_disp.is_keyI())
    {
PR(main_disp.key());
      //post process image (color or grey scale)
      switch(main_disp.key())
      {
        //RGB color
        case 'c':
        {
          main_disp.set_title("Color image (Click on mouse buttons: left and right)");
          std::cout<<"\rswitch to color image.                        "<<std::flush;
          image_pp=image;
        } break;
        //convert to grey level
        case 'v':
        case 'l':
        case 'i':
        {
          CImg<unsigned char> grey_level;
          main_disp.set_title("Grey level image (Click on mouse buttons: left and right)");
          std::cout<<"\rswitch to grey level image based on ";
          switch(main_disp.key())
          {
            case 'v': std::cout<<"value.    ";grey_level=image.get_RGBtoHSV().get_channel(2)*255; break;
            case 'l': std::cout<<"lightness.";grey_level=image.get_RGBtoHSL().get_channel(2)*255; break;
            case 'i': std::cout<<"intensity.";grey_level=image.get_RGBtoHSI().get_channel(2)*255; break;
          }//switch grey
          std::cout<<std::flush;
          cimg_forC(image_pp,c) image_pp.get_shared_channel(c)=grey_level;
        } break;
      }//switch color or grey
      //display new image
      image_pp.display(main_disp);
      //reset key buffer
      main_disp.set_key();
      refresh_draw=true;
    }
    //mouse button
    if(main_disp.button()!=0)
    {
PR(main_disp.button());
PR(main_disp.mouse_x());PR(main_disp.mouse_y());
      if(main_disp.mouse_x()>=0 && main_disp.mouse_y()>=0)
      {// Mouse pointer is over the image
        bm=main_disp.button(); // button of the mouse over the image
        xm=main_disp.mouse_x();// X-coordinate of the mouse pointer over the image
        ym=main_disp.mouse_y();// Y-coordinate of the mouse pointer over the image
        refresh_draw=true;
      }
      else
      {
        // else display a text in the profile display window.
        CImg<unsigned char>(draw_disp.width(),draw_disp.height()).fill(255).
          draw_text(draw_disp.width()/2-110,draw_disp.height()/2-5,"Mouse pointer is outside the image",black).
          display(draw_disp);
      }
    }
    //draw graphs in draw display
    if(refresh_draw)
    {
PR(refresh_draw);
      const int
        xl=xm*draw_disp.width()/main_disp.width(),// Corresponding X-coordinate of the hatched line
        x =xm*image.width()/main_disp.width(),    // Corresponding X-coordinate of the pointed pixel in the image
        y =ym*image.height()/main_disp.height();  // Corresponding Y-coordinate of the pointex pixel in the image

      // Retrieve color component values at pixel (x,y)
      const unsigned int
        val_red   = image_pp(x,y,0),
        val_green = image_pp(x,y,1),
        val_blue  = image_pp(x,y,2);

      if(bm==1)
      {
        //display actual line on main display
        CImg<unsigned char>(image_pp).
          draw_line(0,ym,main_disp.width()-1,ym,white,0.5f,hatch=cimg::rol(hatch)).
          display(main_disp);
        //Create and display the graph of the intensity profile
        int width=image.width(),height=draw_disp.height();
        draw_disp.set_title("Color profile along X axis").resize(width,height,true);
        CImg<unsigned char>(width,height,1,3,255).
          draw_grid(-50*100.0f/width,-50*100.0f/256,0,0,false,true,black,0.2f,0xCCCCCCCC,0xCCCCCCCC).
          draw_axes(0,image.width()-1.0f,255.0f,0.0f,black).
          draw_graph(image_pp.get_shared_row(y,0,0),red,1,1,0,255,1).
          draw_graph(image_pp.get_shared_row(y,0,1),green,1,1,0,255,1).
          draw_graph(image_pp.get_shared_row(y,0,2),blue,1,1,0,255,1).
          draw_text(30,5,"Pixel (%d,%d)={%d %d %d}",black,0,1,13,xm,ym,val_red,val_green,val_blue).
          draw_line(xl,0,xl,draw_disp.height()-1,black,0.5f,hatch=cimg::rol(hatch)).
          display(draw_disp);
      }//bm==1
      if(bm==2)
      {
        //display actual line on main display
        CImg<unsigned char>(image_pp).
          draw_line(xm,0,xm,main_disp.height()-1,white,0.5f,hatch=cimg::rol(hatch)).
          display(main_disp);
        //Create and display the graph of the intensity profile
        int width=image.height(),height=draw_disp.height();
        draw_disp.set_title("Color profile along Y axis").resize(width,height,true);
        CImg<unsigned char>(width,height,1,3,255).
          draw_grid(-50*100.0f/width,-50*100.0f/256,0,0,false,true,black,0.2f,0xCCCCCCCC,0xCCCCCCCC).
          draw_axes(0,image.height()-1.0f,255.0f,0.0f,black).
          draw_graph(image_pp.get_crop(x,0,0,0,x,image.height()-1,0,0),red,1,1,0,255,1).//red graph
          draw_graph(image_pp.get_crop(x,0,0,1,x,image.height()-1,0,1),green,1,1,0,255,1).//green graph
          draw_graph(image_pp.get_crop(x,0,0,2,x,image.height()-1,0,2),blue,1,1,0,255,1).//blue graph
          draw_text(30,5,"Pixel (%d,%d)={%d %d %d}",black,0,1,13,xm,ym,val_red,val_green,val_blue).//actual position and RGB as text
          draw_line(xl,0,xl,draw_disp.height()-1,black,0.5f,hatch=cimg::rol(hatch)).
          display(draw_disp);
      }//bm==2
      refresh_draw=false;
    }//draw window
    // Temporize event loop
    cimg::wait(20);
  }//event loop
}
//! display image as 3D surface
/**
 * \param [in] image : image to display
**/
template<typename T>
void display3D(CImg<T> image,
  const char *file_o,const float ratioz,const unsigned int di,
  const char *file_pose_i,const char *file_pose_o,
  unsigned int rtype,bool color_type)
{
  std::cout<<"display image as 3D surface"<<std::flush;
  const CImg<unsigned char> norm=image.get_norm().normalize(0,255);
  // Compute surface with triangles.
  std::fprintf(stderr,"\n- Create image surface"); std::fflush(stderr);
  CImgList<unsigned int> primitives;
  ////image colors
  CImgList<unsigned char> colors;
  const CImg<> points = image.get_elevation3d(primitives,colors,norm*-ratioz);
  ////constant colors
  CImgList<unsigned char> colors2;
  colors2=colors;
  cimglist_for(colors2,l) colors2(l).fill(255);//white

  // Compute image isophotes.
  std::fprintf(stderr,"\n- Compute image isophotes"); std::fflush(stderr);
  CImgList<unsigned int> isoprimitives;
  ////image colors
  CImgList<unsigned char> isocolors;
  CImg<> isopoints;
  for (unsigned int i = 0; i<255; i+=di) {
    CImgList<> prims;
    const CImg<> pts = norm.get_isoline3d(prims,(float)i);
    isopoints.append_object3d(isoprimitives,pts,prims);
  }
  cimglist_for(isoprimitives,l) {
    const unsigned int i0 = isoprimitives(l,0);
    const float x0 = isopoints(i0,0), y0 = isopoints(i0,1);
    const unsigned char
      r = (unsigned char)image.linear_atXY(x0,y0,0),
      g = (unsigned char)image.linear_atXY(x0,y0,1),
      b = (unsigned char)image.linear_atXY(x0,y0,2);
    isocolors.insert(CImg<unsigned char>::vector(r,g,b));
  }
  cimg_forX(isopoints,l) isopoints(l,2) = -ratioz*norm.linear_atXY(isopoints(l,0),isopoints(l,1));
  ////constant colors
  CImgList<unsigned char> isocolors2;
  isocolors2=isocolors;
  cimglist_for(isocolors2,l) isocolors2(l).fill(255);//white

  // Save object if necessary
  if (file_o)
  {
    std::fprintf(stderr,"\n- Save 3d object as '%s'",cimg::basename(file_o)); std::fflush(stderr);
    points.save_off(primitives,colors,file_o);
  }

  //display GUI information
  std::fprintf(stderr,
               "\n- Enter interactive loop.\n\n"
               "GUI reminder: \n"
               " + Use mouse to rotate and zoom object\n"
               " + key 'F'          : toggle Fullscreen\n"
               " + key 'Q' or 'ESC' : Quit (i.e. exit)\n"
               " load or save file:\n"
               " + key 'S'          : Save displayed image (i.e. 3D view)\n"
               " + key 'O'          : save pOse (i.e. 3D view parameters)\n"
               " + key 'R'          : Read pose (i.e. 3D view parameters)\n"
               " render type:\n"
               " + key 'C'          : color render (image or constant)\n"
               " + key 'T'          : poinTs render\n"
               " + key 'L'          : Lines render\n"
               " + key 'A'          : fAces render\n"
               " + key 'H'          : flat-sHaded faces render\n"
               " + key 'G'          : Gouraud-shaded faces render\n"
               " + key 'P'          : Phong-shaded faces render\n"
               " + key 'I'          : Isophotes render\n"
               " + key 'BackSpace'  : change rendering type (i.e. decrement type)\n"
               " + Any other key    : change rendering type (i.e. increment type)\n\n"
               ); std::fflush(stderr);
  const char *const title = "Image viewed as a surface";
  CImgDisplay disp(800,600,title,0);
  CImg<float> pose=CImg<float>::identity_matrix(4);
  //load pose if set
  if(file_pose_i) {std::cerr<<"- read pose from file \""<<file_pose_i<<"\"\n"<<std::flush;pose.load(file_pose_i);}
//pose.print("pose");std::cerr<<std::flush;

  //GUI loop
  while (!disp.is_closed())
  {
    const unsigned char text_color[3]={123,234,234};
    CImg<unsigned char> visu(disp.width(),disp.height(),1,3,0);
    visu.draw_text(10,10,"%s",text_color,0,1,24,
                rtype==0?"Points (0,T)":(rtype==1?"Lines (1,L)":(rtype==2?"Faces (2,A)":(rtype==3?"Flat-shaded faces (3,H)":
               (rtype==4?"Gouraud-shaded faces (4,G)":(rtype==5?"Phong-shaded faces (5,P)":"Isophotes (6,I)"))))));
    static bool first_time=(file_pose_i)?false:true;
    if (rtype==6) visu.display_object3d(disp,isopoints,isoprimitives,(color_type)?isocolors:isocolors2,first_time,1,-1,true,
                                        500.0f,0.0f,0.0f,-5000.0f,0.0f,0.0f,true,pose.data());
    else visu.display_object3d(disp,points,primitives,(color_type)?colors:colors2,first_time,rtype,-1,true,
                               500.0f,0.0f,0.0f,-5000.0f,0.0f,0.0f,true,pose.data());
    first_time=false;
//pose.print("pose");std::cerr<<std::flush;
    switch (disp.key())
    {
    case 0: break;
    case cimg::keyBACKSPACE: rtype=(7+rtype-1)%7; break;
    case cimg::keyQ:
    case cimg::keyESC: disp.close(); break;
    //fullscreen display or not
    case cimg::keyF:
      if (disp.is_fullscreen()) disp.resize(800,600); else disp.resize(disp.screen_width(),disp.screen_height());
      disp.toggle_fullscreen();
      break;
    //save display
    case cimg::keyS: {std::string file_tmp="CImg_surface3D.png";std::cerr<<"saving display as image in \""<<file_tmp<<"\".\n"<<std::flush;CImg<unsigned char> tmp;disp.snapshot(tmp);tmp.save(file_tmp.c_str());} break;
    //save pose
    case cimg::keyO: {std::cerr<<"saving pose in file \""<<file_pose_o<<"\".\n"<<std::flush;pose.save(file_pose_o);}break;
    //load pose
    case cimg::keyR: {std::cerr<<"loading pose from file \""<<file_pose_i<<"\".\n"<<std::flush;pose.load(file_pose_i);}break;
    //display type
    case cimg::keyC: color_type=(color_type)?false:true;break;//color type
    case cimg::keyT: rtype=0;break;//poinTs
    case cimg::keyL: rtype=1;break;//Lines
    case cimg::keyA: rtype=2;break;//fAces
    case cimg::keyH: rtype=3;break;//flat-sHaded faces
    case cimg::keyG: rtype=4;break;//Gouraud-shaded faces
    case cimg::keyP: rtype=5;break;//Phong-shaded faces
    case cimg::keyI: rtype=6;break;//Isophotes
    default: rtype = (rtype+1)%7; break;
    }//Key switch
  }//GUI loop
}
// Main procedure
int main(int argc,char **argv)
{
//! \todo add doxygen comments for main, within the main and PR()
// Define program usage and read command line parameters
  // Display program usage, when invoked from the command line with option '-h'.
  cimg_usage("display image as 2D map or/and 1D graph(s) or 3D surface.");
  // Read image filename from the command line (or set it to "img/parrot_original.ppm" if option '-i' is not provided).
  const char* file_i = cimg_option("-i","image.png","Input image");
  //2x2D display options
  const bool display_2x2D =cimg_option("--2x2D",false,"display 2 images");
  const char* file_i1= cimg_option("-i1","image1.png","Input image 1 (e.g. image1.png)");
  const char* file_i2= cimg_option("-i2","image2.png","Input image 2 (e.g. image2.png)");
  //pre-processing options
  //// Read pre-blurring variance from the command line (or set it to 1.0 if option '-blur' is not provided).
  const double sigma = cimg_option("--blur",-1.0,"Variance of gaussian pre-blurring (e.g. --blur 2.0)");
  const bool normalize=cimg_option("--norm",false,"normalize image between 0 and 255 for 8-bit display (e.g. --norm true)");
  //1D display options
  const bool display_1D=cimg_option("--1D",false,"display also profile (i.e. 1D graph with --1D true)");
  //3D display options
  const bool display_3D=cimg_option("--3D",false,"display as 3D surface");
  const char *file_o    = cimg_option("-o",(char*)0,"Output 3D object");
  const float ratioz    = cimg_option("-z",0.25f,"Aspect ratio along z-axis");
  const unsigned int di = cimg_option("-di",10,"Step for isophote skipping");
  const char *file_pose_i    = cimg_option("-pi",(char*)0,"Input 3D pose  (e.g. pose.cimg)");
  const char *file_pose_o    = cimg_option("-po","pose.cimg","Output 3D pose (e.g. pose.cimg)");
  unsigned int rtype=cimg_option("--render-type",2,"type of rendering (E[0-6], see GUI: render type)");
  bool color_type=cimg_option("--color-type",true,"type of surface color: true image color, false constant color");
  //help
  const bool help=cimg_option("-h",false,"display this help.");
  //exit on help request '-h' command line option
  if(help) return 0;
  //display
  if(display_2x2D)
  {
    CImg<> image1(file_i1);
    CImg<> image2(file_i2);
    CImgList<> image(2);
    image[0]=image1.get_shared();
    image[1]=image2.get_shared();
    std::string title=file_i1;
    title+=" ";
    title+=file_i2;
    image.display((char*)title.c_str());
  }//display_2x2D
  else
  {
    // Load an image, transform it to a color image (if necessary) and blur it with the standard deviation sigma.
    CImg<> image(file_i);
    image.print(file_i);

///pre-processing
    if(normalize) image.normalize(0,255);
    if(sigma>0.0) image.blur((float)sigma);

    if(display_1D)
///display as image (2D map) and profiles (1D graph)
    {
      if(image.height()==1) image.display_graph(file_i);
      else display1D2D(image);
    }//display_1D
    else if(display_3D)
///display as surface (3D)
    {
      display3D(image,file_o,ratioz,di,file_pose_i,file_pose_o,rtype,color_type);
    }//display_3D
    else
///display as 2D map
    {
      image.display(file_i);
    }//display_2D
  }//display image
  return 0;
}

