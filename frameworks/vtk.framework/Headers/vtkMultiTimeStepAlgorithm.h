/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkMultiTimeStepAlgorithm.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkMultiTimeStepAlgorithm - Superclass for algorithms that would like to
//  make multiple time requests
// .SECTION Description
// This class can be inherited by any algorithm that wishes to make multiple
// time requests upstream.
// The child class uses UPDATE_TIME_STEPS to make the time requests and
// use set of time-stamped data objects are stored in time order
// in a vtkMultiBlockDataSet object.


#ifndef __vtkMultiTimeStepAlgorithm_h
#define __vtkMultiTimeStepAlgorithm_h

#include "vtkCommonExecutionModelModule.h" // For export macro
#include "vtkAlgorithm.h"
#include "vtkSmartPointer.h" //needed for a private variable

#include <vector> //needed for a private variable

class vtkInformationDoubleVectorKey;
class vtkMultiBlockDataSet;
class VTKCOMMONEXECUTIONMODEL_EXPORT vtkMultiTimeStepAlgorithm : public vtkAlgorithm
{
public:
  static vtkMultiTimeStepAlgorithm *New();
  vtkTypeMacro(vtkMultiTimeStepAlgorithm,vtkAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent);


protected:
  vtkMultiTimeStepAlgorithm();

  ~vtkMultiTimeStepAlgorithm()
  {
  };

  // Description:
  // This is filled by the child class to request multiple time steps
  static vtkInformationDoubleVectorKey* UPDATE_TIME_STEPS();


  // Description:
  // This is called by the superclass.
  // This is the method you should override.
  virtual int RequestDataObject(vtkInformation*, vtkInformationVector**,  vtkInformationVector*)
  {
    return 1;
  };

  // Description:
  // This is called by the superclass.
  // This is the method you should override.
  virtual int RequestInformation(vtkInformation*, vtkInformationVector**, vtkInformationVector*)
  {
    return 1;
  };

  // Description:
  // This is called by the superclass.
  // This is the method you should override.
  virtual int RequestData(vtkInformation*, vtkInformationVector**, vtkInformationVector*)
  {
    return 1;
  }

  // Description:
  // This is called by the superclass.
  // This is the method you should override.
  virtual int RequestUpdateExtent(vtkInformation*, vtkInformationVector**, vtkInformationVector*)
  {
    return 1;
  }

  int ProcessRequest(vtkInformation*, vtkInformationVector**, vtkInformationVector*);

private:
  vtkMultiTimeStepAlgorithm(const vtkMultiTimeStepAlgorithm&);  // Not implemented.
  void operator=(const vtkMultiTimeStepAlgorithm&);  // Not implemented.


  vtkSmartPointer<vtkMultiBlockDataSet> MDataSet; //stores all the temporal data sets
  int RequestUpdateIndex; //keep track of the time looping index
  std::vector<double> UpdateTimeSteps;  //store the requested time steps
};

#endif
