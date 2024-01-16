all: run

build:
	g++ -o CImg.reduce CImg.reduce.cpp -I ../../CImg -Wall -W -lm -ansi -pedantic -O0 -fno-tree-pre -Dcimg_use_vt100 -I/usr/X11R6/include -Dcimg_use_xshm -Dcimg_use_xrandr -L/usr/X11R6/lib -lpthread -lX11 -lXext -lXrandr
	./CImg.reduce -h

run:
	./CImg.reduce -i CImg_logo.png
