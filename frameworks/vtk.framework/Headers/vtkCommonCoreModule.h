
#ifndef VTKCOMMONCORE_EXPORT_H
#define VTKCOMMONCORE_EXPORT_H

#ifdef VTKCOMMONCORE_STATIC_DEFINE
#  define VTKCOMMONCORE_EXPORT
#  define VTKCOMMONCORE_NO_EXPORT
#else
#  ifndef VTKCOMMONCORE_EXPORT
#    ifdef vtkCommonCore_EXPORTS
        /* We are building this library */
#      define VTKCOMMONCORE_EXPORT 
#    else
        /* We are using this library */
#      define VTKCOMMONCORE_EXPORT 
#    endif
#  endif

#  ifndef VTKCOMMONCORE_NO_EXPORT
#    define VTKCOMMONCORE_NO_EXPORT 
#  endif
#endif

#ifndef VTKCOMMONCORE_DEPRECATED
#  define VTKCOMMONCORE_DEPRECATED __attribute__ ((__deprecated__))
#  define VTKCOMMONCORE_DEPRECATED_EXPORT VTKCOMMONCORE_EXPORT __attribute__ ((__deprecated__))
#  define VTKCOMMONCORE_DEPRECATED_NO_EXPORT VTKCOMMONCORE_NO_EXPORT __attribute__ ((__deprecated__))
#endif

#define DEFINE_NO_DEPRECATED 0
#if DEFINE_NO_DEPRECATED
# define VTKCOMMONCORE_NO_DEPRECATED
#endif



#endif
