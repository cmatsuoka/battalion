##########################################################################
# This is a slightly better Makefile than before ... but its gonna need
# an overhaul very soon as its getting out of control.
#
# Makefile for v 1.3 of battalion (OpenGL/Mesa version)
#
# ajohnson@eecs.uic.edu
#
# if you are compiling this on an SGI the makefile should work fine,
# as it is. otherwise you may have to do a little bit of tweaking.
#
# the most important thing to know before you try and use this file is
# whether you have OpenGL or Brian Paul's Mesa graphics library installed
# on your machine. Without either of these you are not going to get very
# far. 
#

# ------------------------------------------------------------


# STEP 1: CHOOSE YOUR C/C++ COMPILER HERE (e.g. DCC, cc, CC, gcc, acc)
#
# (the program should compile with no warning messages - if you
#  see a warning message please let me know about it)
# ------------------------------------------------------------
CC = cc


# STEP 2: IF YOU WANT TO COMPILE WITH THE MESA LIBRARIES THEN
#         UNCOMMENT THE NEXT LINE, ELSE LEAVE IT COMMENTED OUT
#
# ------------------------------------------------------------
#WHICHLIB = -DMESAVERSION


# STEP 3: CHOOSE WHICH GRAPHICS LIBRARIES TO COMPILE WITH:
#         MESA OR OPENGL
#
# ------------------------------------------------------------
#GLIB = -lMesaGL -lMesaGLU
# or
GLIB =  -lGL -lGLU


# STEP 4: CHOOSE WHICH HARDWARE / OS YOU ARE RUNNING
#
#	  (right now the -DSUNVERSION and -DLINUXVERSION don't alter
#	  anything in the code)
#
#         (if you are running Solaris then you should be working
#         with the other Makefile.)
#
# ------------------------------------------------------------
#OS = -DSGIVERSION
# or
#OS = -DSUNVERSION
# or
OS = -DLINUXVERSION
# or
#OS = -DHPVERSION
# or
#OS = -DAIXVERSION


# STEP 5: IF YOU ARE COMPILING FOR AN SGI AND WANT AUDIO THEN
#         UNCOMMENT THE NEXT LINES, ELSE COMMENT THEM OUT
#
# special notes on SGI audio:
#
# if you are running an early version of IRIX 5 you may not be
# able to compile the audio code (as SGI tried to sell it separately 
# for a short time - I think this affects IRIX 5.1 and possibly 5.2)
#
# if you are running Irix 6.2 (and probably other variants of 6) you
# will have problems compiling one line of audio.c because the type of
# two parameters have changed. If you make the requested change
# in audio.c then everything works fine.
#
# ------------------------------------------------------------
#AUDIOLIB = -laudio -laudiofile
#AUDIODEF = -DSGIAUDIO


# STEP 6: IF YOU ARE COMPILING FOR A SUN AND WANT (RUDIMENTARY)
#         AUDIO THEN UNCOMMENT THE NEXT LINES, ELSE COMMENT THEM OUT
#
# ------------------------------------------------------------
#AUDIOLIB = -laudio
AUDIODEF = -DLINUXAUDIO


# STEP 7: CHOOSE ANY OPTIMIZATIONS OR ADD ANY SPECIAL INCLUSIONS
# ------------------------------------------------------------
CFLAGS     = -O2  -I/usr/local/X11/include -I/usr/demo/SOUND/ -I./. $(AUDIODEF) $(OS)


# STEP 8: ADD ANY SPECIAL LIBRARY PATHS
#         (USEFUL TO POINT TO WHERE THE MESA LIBRARIES RESIDE)
# ------------------------------------------------------------
LIBFLAGS     = 

# you should now be able to type 'make' and everything should be fine ...

#-------------------------------------------------------------------

TARGET 	= battalion

OBJ 	= battalion.o audio.o net.o gprim.o graphics.o objects.o text.o update.o tk.o font.o soundIt.o
LIBS    = -L./. -L/usr/X11R6/lib -lm -lX11 -lXext

all:	$(TARGET)

#$(OBJ): $(?:.o=.c)
#	$(CC) $(CFLAGS) $(LIBFLAG) $(OS) $(WHICHLIB) $(AUDIOLIB) -c $?

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ) $(LIBFLAGS) $(GLIB) $(LIBS) $(AUDIODEF)

clean:
	rm -f $(OBJ)

#-------------------------------------------------------------------
# Here is a listing of which compilers will compile battalion on
# a variety of hardware/ OSs.
#
# YES - I have tested it and it works
# yes - someone else has apparently gotten it to work
#
# NO  - I was not able to get it to work
# no  - someone else was not able to get it to work
# 
# -   - N/A
# 
# ?   - unknown
#
# OS	          Graphics   cc   CC   DCC   acc   gcc
# ----------------------------------------------------
# SGI Irix 5.3     OpenGL   YES   YES  YES    -     ?
# SGI Irix 5.3      Mesa    YES   YES  YES    -     ?
#
# SunOS 4          OpenGL    NO    NO   -    YES   YES
# SunOS 4           Mesa     NO    NO   -    YES   YES
#
# Solaris 2        OpenGL    ?     ?    -     ?     ?
# Solaris 2         Mesa     ?     ?    -     ?     ?
#
# Linux             Mesa    YES     ?    -     -    YES
#
# HP-UX             Mesa    yes    ?    -     -     ?

# SGI compilers under 6.2 are unhappy in the audio code call for
# AFgetsampfmt(...) where two of the parameters have changed their
# type since 5.3.If you make the requested replacement everything is fine.
#
# cc under SunOS-4 gives errors on gl.h
# CC under SunOS-4 gets very unhappy about things not being exactly its own way
#
# if you have a compiler experience you would lile to share, please let me
# know and I'll pass on the knowledge in the next release. 
#
# if you need to make any modifications in the Makefike or in the code
# to get it to compile, please let me know.
#
#
# battalion first checks the environment variable BATTALIONDATADIR to
# look for the data files. Specifically it looks for the battalion.sho
# showcase file. if battalion.sho is not found in the BATTALIONDATADIR
# directory then it will check ./battalion.data/
#
# if you are running the program on an SGI you will want to leave
# battalion.sho alone as it is your on-line help. If you do not have
# an SGI then you can replace this file with any smaller file with the
# same name if you want to conserve space.
