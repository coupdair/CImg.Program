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

enum display_space_index {REAL_SPACE=0,FILTERED_SPACE,FOURIER_SPACE};

// Main procedure
//----------------
int main(int argc,char **argv) {

  // Define program usage and read command line parameters
  //-------------------------------------------------------

  // Display program usage, when invoked from the command line with option '-h'.
  cimg_usage("Compute fourier transform (FT) and filter in Fourier space");

  // Read image filename from the command line (or set it to "img/lena.pgm" if option '-i' is not provided).
  const char* file_i = cimg_option("-i",cimg_imagepath "lena.pgm","Input image");

  // Read pre-blurring variance from the command line (or set it to 1.0 if option '-blur' is not provided).
  const float zoom = cimg_option("--zoom",1.0,"zoom for displaying images");

  const int rstep=cimg_option("--r_step",1,"step for incrementing r (both r_min and r_max using arrow keys)");

  // Init variables
  //----------------

  //load an image, transform it to a grey level image (if necessary)
  CImg<unsigned char> img(file_i);
  if(img.spectrum()==3) img.RGBtoHSI().channel(2)*255;
  //get Fourier tranform image
  CImgList<float> F = img.get_FFT();
  cimglist_apply(F,shift)(img.width()/2,img.height()/2,0,0,2);
  //magnitude
  const CImg<unsigned char> mag = ((F[0].get_pow(2) + F[1].get_pow(2)).sqrt() + 1).log().normalize(0,255);
  //image list for GUI
  CImgList<unsigned char> visu(3);
//! \todo V add zoom
  visu[REAL_SPACE]=img.get_resize(zoom*-100,zoom*-100);
  visu[FOURIER_SPACE]=mag.get_resize(zoom*-100,zoom*-100);
  visu[FILTERED_SPACE]=img.get_resize(zoom*-100,zoom*-100);
  //display image for GUI
  CImgDisplay disp(visu,"Fourier Filtering (click on Fourier space to set filter, try both left and right button)");
  bool refresh_draw=true;
  //filter image (i.e. mask for Fourier space)
  CImg<unsigned char> mask(img.width(),img.height(),1,1,1);
  const unsigned char one[] = { 1 }, zero[] = { 0 }, white[] = { 255 };
  //filtering radius in Fourier space
  int rmin=0,rmax=std::sqrt(img.width()*img.width()+img.height()*img.height());
//display keyboard information:
  std::cout<<"keyboard control\n";
  std::cout<<"  'S' key: save Fourier image in \"fourier.png\"\n";
  std::cout<<"  maximum radius\n";
  std::cout<<"    keypad 0 to 9: set  0 to 90 pixel\n";
  std::cout<<"    up or down arrows:    in(or de)crement radius by step (defined by --r_step option)\n";
  std::cout<<"  minimum radius\n";
  std::cout<<"    character 0 to 9: set  0 to 90 pixel\n";
  std::cout<<"    left or right arrows: in(or de)crement radius by step (defined by --r_step option)\n";
  std::cout<<std::flush;
  //mouse position in image space (i.e. not display space)
  int xm=rmax,ym=0;
  while (!disp.is_closed() && !disp.is_keyQ() && !disp.is_keyESC()) {
    disp.wait();
PR(disp.mouse_x());
PR(disp.mouse_y());
PR(xm);
PR(ym);
    //save image
    switch(disp.key())
    {
      case 's':
      case 'S':visu[FILTERED_SPACE].save("fourier.png");break;
    }
    //minimum filter
    if(disp.is_keyARROWRIGHT()||disp.is_keyARROWLEFT())
    {
PR("keyARROW");
PR(disp.key());
      switch(disp.key())
      {
        case cimg::keyARROWLEFT :rmin-=rstep;break;
        case cimg::keyARROWRIGHT:rmin+=rstep;break;
      }
      if(rmin<0) rmin=0;
      //reset key and mouse events
      disp.flush();
      refresh_draw=true;
    }//if keyARROW
    if(disp.is_key0()||disp.is_key1()||disp.is_key2()||disp.is_key3()||disp.is_key4()||disp.is_key5()||disp.is_key6()||disp.is_key7()||disp.is_key8()||disp.is_key9())
    {
PR("key");
PR(disp.key());
      switch(disp.key())
      {
        case '0': rmin=0;PR("rmin=0"); break;
        case '1': rmin=10;PR("rmin=1"); break;
        case '2': rmin=20;PR("rmin=2"); break;
        case '3': rmin=30;PR("rmin=3"); break;
        case '4': rmin=40;PR("rmin=4"); break;
        case '5': rmin=50;PR("rmin=5"); break;
        case '6': rmin=60;PR("rmin=6"); break;
        case '7': rmin=70;PR("rmin=7"); break;
        case '8': rmin=80;PR("rmin=8"); break;
        case '9': rmin=90;PR("rmin=9"); break;
      }//switch key0-9
      if(rmin<0) rmin=0;
      //reset key and mouse events
      disp.flush();
      refresh_draw=true;
    }//if key0-9
    //maximum filter
    if(disp.is_keyARROWDOWN()||disp.is_keyARROWUP())
    {
PR("keyARROW");
PR(disp.key());
      switch(disp.key())
      {
        case cimg::keyARROWDOWN :rmax-=rstep;break;
        case cimg::keyARROWUP   :rmax+=rstep;break;
      }
      if(rmax<0) rmax=0;
      //reset key and mouse events
      disp.flush();
      refresh_draw=true;
    }//if keyARROW
    if(disp.is_keyPAD0()||disp.is_keyPAD1()||disp.is_keyPAD2()||disp.is_keyPAD3()||disp.is_keyPAD4()||disp.is_keyPAD5()||disp.is_keyPAD6()||disp.is_keyPAD7()||disp.is_keyPAD8()||disp.is_keyPAD9())
    {
PR("keyPAD");
PR(disp.key());
      switch(disp.key())
      {
        case cimg::keyPAD0: rmax=0;PR("rmax=0"); break;
        case cimg::keyPAD1: rmax=10;PR("rmax=1"); break;
        case cimg::keyPAD2: rmax=20;PR("rmax=2"); break;
        case cimg::keyPAD3: rmax=30;PR("rmax=3"); break;
        case cimg::keyPAD4: rmax=40;PR("rmax=4"); break;
        case cimg::keyPAD5: rmax=50;PR("rmax=5"); break;
        case cimg::keyPAD6: rmax=60;PR("rmax=6"); break;
        case cimg::keyPAD7: rmax=70;PR("rmax=7"); break;
        case cimg::keyPAD8: rmax=80;PR("rmax=8"); break;
        case cimg::keyPAD9: rmax=90;PR("rmax=9"); break;
      }//switch keyPAD0-9
      //reset key and mouse events
      disp.flush();
      refresh_draw=true;
    }//if keyPAD0-9
    //filter on mouse button click
    if(disp.button())
    {
//! \todo . add zoom
      xm=disp.mouse_x()/zoom-img.width()*FOURIER_SPACE,
      ym=disp.mouse_y()/zoom;//*img.height()/disp.height();
      const int x=xm-img.width()/2, y=ym-img.height()/2;
      const int r = (int)cimg::max(0.0f,(float)std::sqrt((float)x*x + y*y) - 3);
      if (disp.button()&1) rmax=r;
      if (disp.button()&2) rmin=r;
      refresh_draw=true;
    }
    //refresh draw
    if(refresh_draw && xm>=0 && ym>=0)
    {
//PR(rmin);
      if (rmin>=rmax) rmin = cimg::max(rmax - 1,0);
PR(rmin);
PR(rmax);
      mask.fill(0).draw_circle(mag.width()/2,mag.height()/2,rmax,one).
        draw_circle(mag.width()/2,mag.height()/2,rmin,zero);
      CImgList<float> nF(F);
      cimglist_for(F,l) nF[l].mul(mask).shift(-img.width()/2,-img.height()/2,0,0,2);
//! \todo V add zoom
      visu[FILTERED_SPACE]=nF.FFT(true)[0].normalize(0,255).get_resize(zoom*-100,zoom*-100);
    }//if button
    if (disp.is_resized()) disp.resize(disp.window_width(),disp.window_width()/2).display(visu);
    //
//! \todo V add zoom
    visu[FOURIER_SPACE]=mag.get_mul(mask).draw_text(5,5,"Freq Min/Max = %d / %d",white,zero,0.6f,13,(int)rmin,(int)rmax).get_resize(zoom*-100,zoom*-100);
    //update display
    visu.display(disp);
    refresh_draw=false;
  }
//! \todo [high] add curves display (R=original, G=filtered)

/*
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
          draw_graph(image_pp.get_shared_line(y,0,0),red,1,1,0,255,1).
          draw_graph(image_pp.get_shared_line(y,0,1),green,1,1,0,255,1).
          draw_graph(image_pp.get_shared_line(y,0,2),blue,1,1,0,255,1).
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
*/
  return 0;
}

