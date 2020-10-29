#define FREEGLUT_BUILDING_LIB
#include <GL/freeglut.h>
#include "fg_internal.h"
#ifdef VITA
#include <pib.h>
#endif

/*
 * A call to this function should initialize all the display stuff...
 */
void fghPlatformInitializeEGL()
{
#ifdef VITA
  pibInit(PIB_SHACCCG);
#endif
  /* CreateDisplay */
  /* Using EGL_DEFAULT_DISPLAY, or a specific native display */
#ifdef FREEGLUT_WAYLAND
  fgDisplay.pDisplay.egl.Display = eglGetDisplay(
              (EGLNativeDisplayType)fgDisplay.pDisplay.display);
#else
  EGLNativeDisplayType nativeDisplay = EGL_DEFAULT_DISPLAY;
  fgDisplay.pDisplay.egl.Display = eglGetDisplay(nativeDisplay);
#endif

  FREEGLUT_INTERNAL_ERROR_EXIT(fgDisplay.pDisplay.egl.Display != EGL_NO_DISPLAY,
			       "No display available", "fgPlatformInitialize");
  if (eglInitialize(fgDisplay.pDisplay.egl.Display, &fgDisplay.pDisplay.egl.MajorVersion, &fgDisplay.pDisplay.egl.MinorVersion) != EGL_TRUE)
    fgError("eglInitialize: error %x\n", eglGetError());

# ifdef GL_VERSION_1_1  /* or later */
  eglBindAPI(EGL_OPENGL_API);
# else
  eglBindAPI(EGL_OPENGL_ES_API);
# endif

  /* fgDisplay.ScreenWidth = ...; */
  /* fgDisplay.ScreenHeight = ...; */
  /* fgDisplay.ScreenWidthMM = ...; */
  /* fgDisplay.ScreenHeightMM = ...; */
}

void fghPlatformCloseDisplayEGL()
{
  if (fgDisplay.pDisplay.egl.Display != EGL_NO_DISPLAY) {
    eglTerminate(fgDisplay.pDisplay.egl.Display);
    fgDisplay.pDisplay.egl.Display = EGL_NO_DISPLAY;
    fgDisplay.pDisplay.egl.MajorVersion = 0;
    fgDisplay.pDisplay.egl.MinorVersion = 0;
  }
}

/**
 * Destroy a menu context
 */
void fgPlatformDestroyContext ( SFG_PlatformDisplay pDisplay, SFG_WindowContextType MContext )
{
  if (MContext != EGL_NO_CONTEXT)
    eglDestroyContext(pDisplay.egl.Display, MContext);
}
