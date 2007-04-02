
.autodepend
#.silent

MAKE = $(MAKE) -fmakefile.mak

!ifdef _DEBUG
!ifndef _RTLDLL
    _D = -sd
!else
    _D = -d
!endif
!else
!ifndef _RTLDLL
    _D = -s
!endif
!endif

!ifdef __MT__
    _mt = -mt
!endif

# Directories
INCLUDE_DIR    = ..\..\..

# Object files
OBJS = \
    "compositeproduct.obj$(_mt)$(_D)" \
    "multiproductcomposite.obj$(_mt)$(_D)" \
    "multiproductmultistep.obj$(_mt)$(_D)" \
    "multiproductonestep.obj$(_mt)$(_D)" \
    "singleproductcomposite.obj$(_mt)$(_D)" \
    "multistep\MultiStep$(_mt)$(_D).lib" \
    "onestep\OneStep$(_mt)$(_D).lib"

# Tools to be used
CC        = bcc32
TLIB      = tlib


# Options
CC_OPTS        = -vi- -q -c -I$(INCLUDE_DIR) -w-8070

!ifdef _DEBUG
    CC_OPTS = $(CC_OPTS) -v -D_DEBUG
!else
    CC_OPTS = $(CC_OPTS) -O2 -DNDEBUG
!endif

!ifdef _RTLDLL
    CC_OPTS = $(CC_OPTS) -D_RTLDLL
!endif

!ifdef __MT__
    CC_OPTS = $(CC_OPTS) -tWM
!endif

!ifdef SAFE
    CC_OPTS = $(CC_OPTS) -DQL_EXTRA_SAFETY_CHECKS
!endif

TLIB_OPTS    = /P128
!ifdef _DEBUG
TLIB_OPTS    = /P128
!endif

# MAKE Options
!ifdef __MT__
    MAKE = $(MAKE) -D__MT__
!endif
!ifdef _RTLDLL
    MAKE = $(MAKE) -D_RTLDLL
!endif
!ifdef _DEBUG
    MAKE = $(MAKE) -D_DEBUG
!endif
!ifdef SAFE
    MAKE = $(MAKE) -DSAFE
!endif

# Generic rules
.cpp.obj:
    $(CC) $(CC_OPTS) $<
.cpp.obj$(_mt)$(_D):
    $(CC) $(CC_OPTS) -o$@ $<

# Primary target:
# static library
Products$(_mt)$(_D).lib:: SubLibraries $(OBJS)
    if exist Products$(_mt)$(_D).lib     del Products$(_mt)$(_D).lib
    $(TLIB) $(TLIB_OPTS) "Products$(_mt)$(_D).lib" /a $(OBJS)

SubLibraries:
    cd multistep
    $(MAKE)
    cd ..\onestep
    $(MAKE)
    cd ..

# Clean up
clean::
    if exist *.obj         del /q *.obj
    if exist *.obj$(_mt)$(_D)""    del /q *.obj
    if exist *.lib         del /q *.lib
    cd multistep
    $(MAKE) clean
    cd ..\onestep
    $(MAKE) clean
    cd ..