/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkCastToConcrete.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkCastToConcrete - works around type-checking limitations
// .SECTION Description
// vtkCastToConcrete is a filter that works around type-checking limitations
// in the filter classes. Some filters generate abstract types on output,
// and cannot be connected to the input of filters requiring a concrete
// input type. For example, vtkElevationFilter generates vtkDataSet for output,
// and cannot be connected to vtkDecimate, because vtkDecimate requires
// vtkPolyData as input. This is true even though (in this example) the input
// to vtkElevationFilter is of type vtkPolyData, and you know the output of
// vtkElevationFilter is the same type as its input.
//
// vtkCastToConcrete performs run-time checking to insure that output type
// is of the right type. An error message will result if you try to cast
// an input type improperly. Otherwise, the filter performs the appropriate
// cast and returns the data.

// .SECTION Caveats
// You must specify the input before you can get the output. Otherwise an
// error results.

// .SECTION See Also
// vtkDataSetAlgorithm vtkPointSetToPointSetFilter

#ifndef __vtkCastToConcrete_h
#define __vtkCastToConcrete_h

#include "vtkCommonExecutionModelModule.h" // For export macro
#include "vtkDataSetAlgorithm.h"

class VTKCOMMONEXECUTIONMODEL_EXPORT vtkCastToConcrete : public vtkDataSetAlgorithm
{

public:
  static vtkCastToConcrete *New();
  vtkTypeMacro(vtkCastToConcrete,vtkDataSetAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent);

protected:
  vtkCastToConcrete() {};
  ~vtkCastToConcrete() {};

  virtual int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *); //insures compatibility; satisfies abstract api in vtkFilter
  virtual int RequestInformation(vtkInformation *, vtkInformationVector **, vtkInformationVector *);
private:
  vtkCastToConcrete(const vtkCastToConcrete&);  // Not implemented.
  void operator=(const vtkCastToConcrete&);  // Not implemented.
};

#endif
