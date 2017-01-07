
#ifndef LIBFREENECT2_EXPORT_H
#define LIBFREENECT2_EXPORT_H

#ifdef LIBFREENECT2_STATIC_DEFINE
#  define LIBFREENECT2_EXPORT
#  define LIBFREENECT2_NO_EXPORT
#else
#  ifndef LIBFREENECT2_EXPORT
#    ifdef freenect2_EXPORTS
        /* We are building this library */
#      define LIBFREENECT2_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define LIBFREENECT2_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef LIBFREENECT2_NO_EXPORT
#    define LIBFREENECT2_NO_EXPORT 
#  endif
#endif

#ifndef LIBFREENECT2_DEPRECATED
#  define LIBFREENECT2_DEPRECATED __declspec(deprecated)
#endif

#ifndef LIBFREENECT2_DEPRECATED_EXPORT
#  define LIBFREENECT2_DEPRECATED_EXPORT LIBFREENECT2_EXPORT LIBFREENECT2_DEPRECATED
#endif

#ifndef LIBFREENECT2_DEPRECATED_NO_EXPORT
#  define LIBFREENECT2_DEPRECATED_NO_EXPORT LIBFREENECT2_NO_EXPORT LIBFREENECT2_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef LIBFREENECT2_NO_DEPRECATED
#    define LIBFREENECT2_NO_DEPRECATED
#  endif
#endif

#endif
