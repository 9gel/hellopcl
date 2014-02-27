/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkTrivialProducer.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkTrivialProducer - Producer for stand-alone data objects.
// .SECTION Description
// vtkTrivialProducer allows stand-alone data objects to be connected
// as inputs in a pipeline.  All data objects that are connected to a
// pipeline involving vtkAlgorithm must have a producer.  This trivial
// producer allows data objects that are hand-constructed in a program
// without another vtk producer to be connected.

#ifndef __vtkTrivialProducer_h
#define __vtkTrivialProducer_h

#include "vtkCommonExecutionModelModule.h" // For export macro
#include "vtkAlgorithm.h"

class vtkDataObject;

class VTKCOMMONEXECUTIONMODEL_EXPORT vtkTrivialProducer : public vtkAlgorithm
{
public:
  static vtkTrivialProducer *New();
  vtkTypeMacro(vtkTrivialProducer,vtkAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Process upstream/downstream requests trivially.  The associated
  // output data object is never modified, but it is queried to
  // fulfill requests.
  virtual int ProcessRequest(vtkInformation*,
                             vtkInformationVector**,
                             vtkInformationVector*);

  // Description:
  // Set the data object that is "produced" by this producer.  It is
  // never really modified.
  virtual void SetOutput(vtkDataObject* output);

  // Description:
  // The modified time of this producer is the newer of this object or
  // the assigned output.
  virtual unsigned long GetMTime();
protected:
  vtkTrivialProducer();
  ~vtkTrivialProducer();

  virtual int FillInputPortInformation(int, vtkInformation*);
  virtual int FillOutputPortInformation(int, vtkInformation*);
  virtual vtkExecutive* CreateDefaultExecutive();

  // The real data object.
  vtkDataObject* Output;

  virtual void ReportReferences(vtkGarbageCollector*);
private:
  vtkTrivialProducer(const vtkTrivialProducer&);  // Not implemented.
  void operator=(const vtkTrivialProducer&);  // Not implemented.
};

#endif
