// -*- c++ -*-
/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkMathConfigure.h.in

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/*----------------------------------------------------------------------------
 Copyright (c) Sandia Corporation
 See Copyright.txt or http://www.paraview.org/HTML/Copyright.html for details.
----------------------------------------------------------------------------*/

#ifndef __vtkMathConfigure_h
#define __vtkMathConfigure_h

#include <cmath>
#include <float.h>

/* #undef VTK_HAS_ISNAN */
/* #undef VTK_HAS__ISNAN */
/* #undef VTK_HAS_ISINF */
/* #undef VTK_HAS__ISINF */

// VTK_HAS_ISNAN is only defined if an actual function exists.  Also set it if
// isnan is a macro.
#if !defined(VTK_HAS_ISNAN) && defined(isnan)
# define VTK_HAS_ISNAN 1
#endif
#if !defined(VTK_HAS_ISINF) && defined(isinf)
# define VTK_HAS_ISINF 1
#endif

// Try to fake having isnan and isinf if _isnan or _isinf is available
#if !defined(VTK_HAS_ISNAN) && (defined(VTK_HAS__ISNAN) || defined(_isnan))
# define isnan(x) _isnan(x)
# define VTK_HAS_ISNAN 1
#endif
#if !defined(VTK_HAS_ISINF) && (defined(VTK_HAS__ISINF) || defined(_isinf))
# define isinf(x) _isinf(x)
# define VTK_HAS_ISINF 1
#endif

// The compiler for the G5 Apple is not including the isnan and isinf prototypes
// in its math headers even though the symbol exists in the libraries.  Just do
// a brute force to not use those functions in this case to get around compiler
// errors.
#if defined(__APPLE__) && (__GNUC__ < 4)
# undef VTK_HAS_ISNAN
# undef VTK_HAS_ISINF
#endif

// We pretty much assume that all compilers are going to provide
// std::numeric_limits methods in the limits header.  On of the Borland
// dashboard compilers failed to link in the methods, so we have a special
// case here.  If we find more platforms that do not support it correctly,
// then we should probably implement a TRY_COMPILE in the CMakeLists.txt.
#ifndef __BORLANDC__
# define VTK_HAS_STD_NUMERIC_LIMITS
#endif

// If the isnan or isinf function does not exist, then our next attempt is to
// use comparisons to determine if the number is not finite.  Although these
// comparisons should be valid, some systems raise execeptions anyway (possibly
// because exceptions for really bad operations like division by 0 are on).
// This flag will instruct vtkMath not to make these comparisons.  (The next
// fallback is to do IEEE-754 bit comparisons.)
#ifdef __BORLANDC__
# define VTK_NON_FINITE_CAUSES_EXCEPTIONS
#endif

#endif //__vtkMathConfigure_h
