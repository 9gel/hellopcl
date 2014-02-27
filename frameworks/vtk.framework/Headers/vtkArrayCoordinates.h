/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkArrayCoordinates.h

-------------------------------------------------------------------------
  Copyright 2008 Sandia Corporation.
  Under the terms of Contract DE-AC04-94AL85000 with Sandia Corporation,
  the U.S. Government retains certain rights in this software.
-------------------------------------------------------------------------

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

// .NAME vtkArrayCoordinates - Stores coordinate into an N-way array.
//
// .SECTION Description
// vtkArrayCoordinates stores a collection of coordinates that can be
// used to access values in a vtkArray containing an arbitrary number of
// dimensions.
//
// Convenience constructors are provided for working with one, two, and
// three dimensions.  For higher dimensions, use the default constructor,
// SetDimensions() and operator[] to assign a coordinate value along each
// dimension.
//
// .SECTION See Also
// vtkArray, vtkArrayExtents
//
// .SECTION Thanks
// Developed by Timothy M. Shead (tshead@sandia.gov) at Sandia National
// Laboratories.

#ifndef __vtkArrayCoordinates_h
#define __vtkArrayCoordinates_h

#include "vtkCommonCoreModule.h" // For export macro
#include "vtkSystemIncludes.h"
#include <vector>

class VTKCOMMONCORE_EXPORT vtkArrayCoordinates
{
public:
  typedef vtkIdType CoordinateT;
  typedef vtkIdType DimensionT;

  // Description:
  // Create an empty set of coordinates.  Use SetDimensions() and
  // operator[] to populate the coordinates.
  vtkArrayCoordinates();

  // Description:
  // Create coordinates for a one-dimensional array.
  explicit vtkArrayCoordinates(CoordinateT i);

  // Description:
  // Create coordinates for a two-dimensional array.
  vtkArrayCoordinates(CoordinateT i, CoordinateT j);

  // Description:
  // Create coordinates for a three-dimensional array.
  vtkArrayCoordinates(CoordinateT i, CoordinateT j, CoordinateT k);

  // Description:
  // Return the number of dimensions contained in the coordinates.
  DimensionT GetDimensions() const;

  // Description:
  // Set the number of dimensions.  Note that this method resets the
  // coordinate along each dimension to zero, so you must set every
  // coordinate explicitly using operator[] after calling SetDimensions().
  void SetDimensions(DimensionT dimensions);

  // Description:
  // Returns the coordinate of the i-th dimension.
  CoordinateT& operator[](DimensionT i);

  // Description:
  // Returns the coordinate of the i-th dimension.
  const CoordinateT& operator[](DimensionT i) const;

  // Description:
  // Returns the coordinate of the i-th dimension.
  CoordinateT GetCoordinate(DimensionT i) const;

  // Description:
  // Sets the coordinate of the i-th dimension.
  void SetCoordinate(DimensionT i, const CoordinateT&);

  // Description:
  // Equality comparison
  bool operator==(const vtkArrayCoordinates& rhs) const;

  // Description:
  // Inequality comparison
  bool operator!=(const vtkArrayCoordinates& rhs) const;
  VTKCOMMONCORE_EXPORT friend ostream& operator<<(
    ostream& stream, const vtkArrayCoordinates& rhs);

private:
  //BTX
  std::vector<CoordinateT> Storage;
  //ETX
};

#endif

// VTK-HeaderTest-Exclude: vtkArrayCoordinates.h
