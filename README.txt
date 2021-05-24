Slick explosion is an interesting program in that it is an OpenGL program with an explosion and a smoke cloud.  The cloud of particles are a collection of points drawn on the screen as points from a vertex array.  The time standard used throughout is milliseconds and there are variables for time gap and the overall scale of the displayed image.  You can find these variables in the defines in the file commonheader.h and smokecloud.h in the include directory.  They are as follows:

The define in CommonHeader (adjusts sound timing):
SlickExplosion
#define EXP_GAP 2000
The defines in SmokeCloud:
AssimpOpenGL
#define NUM_PARTICLES 10000  Total number of particles.
#define SCALE 15 			Scale of the display.
The define in CommonHeader (adjusts breakup of the object):
AssimpOpenGL
#define CHUNK_SIZE 10
You can adjust these to optimize the performance of the program on your system.  	Generally, reducing the number of particles and increasing the chunk size increases 	performance.  And, of course, you may have to adjust the library setting in 	CMakeLists.txt.
What follows is the contents of the README.txt file.

Edward C. Eberle <eberdeed@eberdeed.net>
San Diego, California USA
    
    slickexplosion is a program that displays an explosion with sound.  
    The keys are as follows.
    a right
    s back
    d left
    w forward
    r up
    f down
    x reverse view.
    z reset view.
    Space toggles the explosion.
    Escape ends the program.
    Alt+Return sets full screen.
    Up arrow zooms in.
    Down arrow zooms out.
    
    To compile the program you will need the following libraries:
    FreeImage, GLEW, SDL2, boost, pthread and GLM. 
    You must also have cmake, doxygen, graphviz and dia.
    The commands are:
    
    cd build
    cmake ..
    sudo make
    sudo make doc
    sudo make install
    
    To run the program:
    
    slickexplosion
    
    The documentation is located in:
    
    /usr/share/doc/slickexplosion-doc
    
    The sources I used to educate myself concerning OpenGL are
    as follows:
        "OpenGL ES 3.0 Programming Guide Second Edition" 
    by Dan Ginsburg and Budirijanto Purnomo published by Addison-Wesley 2014.
        www.learnopengl.com.
    GLEW http://glew.sourceforge.net, and
    CMAKE www.cmake.org.
    SDL2 https://wiki.libsdl.org/FrontPage
    pthread https://www.gnu.org/software/hurd/libpthread.html
    OpenGL is generally available on any system as part 
    of the underlying graphics subsystem and GLEW will 
    get you access to it.
    
    Documentation is available after install at:
    
    /usr/share/doc/slickexplosion-doc
    
        
    The program was written and compiled on debian linux available at:  www.debian.org.
    
    You can reach me at <eberdeed@eberdeed.net>.
    Updates will be available at www.eberdeed.net.
    Edward Charles Eberle 
    March 25th, 2021 San Diego, California United States of America
    
    This program is licensed under the Lesser GNU Public license.
    It can be found in the assimpopengl/LGPL directory 
    and once installed it will be also found at 
    /usr/share/doc/slickexplosion-doc/LGPL.  This 
    program is given as an instructional aid for learning
    and using the libraries presented and is not to 
    be considered fit for any particular use.
