PROGRAMS = version warping mapping
DOCUMENTATIONS = doc

version_warping = v0.0.6
version_mapping = v0.0.4
version_format=v0.0.2
#version_cimg = 125
version_cimg = 139
OPT_LIBRARY = -DMAPPING_VERSION=\"$(version_mapping)\" -DWARPING_FORMAT_VERSION=\"$(version_format)\" -DWARPING_VERSION=\"$(version_warping)\"
OPT_FORMAT = -Dcimg_use_jpeg -ljpeg -Dcimg_use_png -lpng -lz -Dcimg_use_tiff -ltiff
OPT_XWINDOWS = -I/usr/X11R6/include -Dcimg_use_xshm -L/usr/X11R6/lib -lpthread -lX11 -lXext
#OPT = -Dcimg_display=0 -Dcimg_debug=2 -Dcimg_use_vt100 $(OPT_LIBRARY) $(OPT_FORMAT) -Dversion_cimg=$(version_cimg)
OPT = $(OPT_XWINDOWS) -Dcimg_debug=2 -Dcimg_use_vt100 $(OPT_LIBRARY) $(OPT_FORMAT) -Dversion_cimg=$(version_cimg)
CC = gcc
CPP = g++ -O0

all: $(PROGRAMS) $(DOCUMENTATIONS)

prog:$(PROGRAMS)

version: Makefile
	echo ${version_warping} > VERSION_WARPING
	echo ${version_mapping} > VERSION_MAPPING
	echo ${version_format} > VERSION_WARPING_FORMAT
#	cd ../..; rm CImg; ln -s CImg-1.2.5 CImg; cd ./CImg.Program/distorsion/
	cd ../..; rm CImg; ln -s CImg-1.3.9 CImg; cd ./CImg.Program/distorsion/

warping: CImg.warping.cpp Makefile
	$(CPP) CImg.$@.cpp -o CImg.$@ $(OPT) $(VER)

mapping: CImg.mapping.cpp Makefile
	$(CPP) CImg.$@.cpp -o CImg.$@ $(OPT) $(VER)

doc: distorsion.Doxygen Makefile CImg.warping.cpp CImg.mapping.cpp
	./doxIt.sh

clean:
	rm -rf $(DOCUMENTATIONS)/*
	rm -f *.o
	rm -rf .libs
	@list='$(PROGRAMS)'; for p in $$list; do \
	  rm -f $$p ; \
	done


