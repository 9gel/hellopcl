
#ifndef VTKFILTERSCORE_EXPORT_H
#define VTKFILTERSCORE_EXPORT_H

#ifdef VTKFILTERSCORE_STATIC_DEFINE
#  define VTKFILTERSCORE_EXPORT
#  define VTKFILTERSCORE_NO_EXPORT
#else
#  ifndef VTKFILTERSCORE_EXPORT
#    ifdef vtkFiltersCore_EXPORTS
        /* We are building this library */
#      define VTKFILTERSCORE_EXPORT 
#    else
        /* We are using this library */
#      define VTKFILTERSCORE_EXPORT 
#    endif
#  endif

#  ifndef VTKFILTERSCORE_NO_EXPORT
#    define VTKFILTERSCORE_NO_EXPORT 
#  endif
#endif

#ifndef VTKFILTERSCORE_DEPRECATED
#  define VTKFILTERSCORE_DEPRECATED __attribute__ ((__deprecated__))
#  define VTKFILTERSCORE_DEPRECATED_EXPORT VTKFILTERSCORE_EXPORT __attribute__ ((__deprecated__))
#  define VTKFILTERSCORE_DEPRECATED_NO_EXPORT VTKFILTERSCORE_NO_EXPORT __attribute__ ((__deprecated__))
#endif

#define DEFINE_NO_DEPRECATED 0
#if DEFINE_NO_DEPRECATED
# define VTKFILTERSCORE_NO_DEPRECATED
#endif



#endif
