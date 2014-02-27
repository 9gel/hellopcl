/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkMultiBlockDataGroupFilter.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkMultiBlockDataGroupFilter - collects multiple inputs into one multi-group dataset
// .SECTION Description
// vtkMultiBlockDataGroupFilter is an M to 1 filter that merges multiple
// input into one multi-group dataset. It will assign each input to
// one group of the multi-group dataset and will assign each update piece
// as a sub-block. For example, if there are two inputs and four update
// pieces, the output contains two groups with four datasets each.

#ifndef __vtkMultiBlockDataGroupFilter_h
#define __vtkMultiBlockDataGroupFilter_h

#include "vtkFiltersGeneralModule.h" // For export macro
#include "vtkMultiBlockDataSetAlgorithm.h"

class VTKFILTERSGENERAL_EXPORT vtkMultiBlockDataGroupFilter : public vtkMultiBlockDataSetAlgorithm
{
public:
  vtkTypeMacro(vtkMultiBlockDataGroupFilter,vtkMultiBlockDataSetAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Construct object with PointIds and CellIds on; and ids being generated
  // as scalars.
  static vtkMultiBlockDataGroupFilter *New();

  // Description:
  // Assign a data object as input. Note that this method does not
  // establish a pipeline connection. Use AddInputConnection() to
  // setup a pipeline connection.
  void AddInputData(vtkDataObject *);
  void AddInputData(int, vtkDataObject*);

protected:
  vtkMultiBlockDataGroupFilter();
  ~vtkMultiBlockDataGroupFilter();

  virtual int RequestData(vtkInformation *,
                  vtkInformationVector **,
                  vtkInformationVector *);
  virtual int RequestInformation(vtkInformation*,
                                 vtkInformationVector**,
                                 vtkInformationVector*);

  virtual int FillInputPortInformation(int port, vtkInformation *info);

private:
  vtkMultiBlockDataGroupFilter(const vtkMultiBlockDataGroupFilter&);  // Not implemented.
  void operator=(const vtkMultiBlockDataGroupFilter&);  // Not implemented.
};

#endif


