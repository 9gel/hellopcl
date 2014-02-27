/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkBandedPolyDataContourFilter.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkBandedPolyDataContourFilter - generate filled contours for vtkPolyData
// .SECTION Description
// vtkBandedPolyDataContourFilter is a filter that takes as input vtkPolyData
// and produces as output filled contours (also represented as vtkPolyData).
// Filled contours are bands of cells that all have the same cell scalar
// value, and can therefore be colored the same. The method is also referred
// to as filled contour generation.
//
// To use this filter you must specify one or more contour values.  You can
// either use the method SetValue() to specify each contour value, or use
// GenerateValues() to generate a series of evenly spaced contours.  Each
// contour value divides (or clips) the data into two pieces, values below
// the contour value, and values above it. The scalar values of each
// band correspond to the specified contour value.  Note that if the first and
// last contour values are not the minimum/maximum contour range, then two
// extra contour values are added corresponding to the minimum and maximum
// range values. These extra contour bands can be prevented from being output
// by turning clipping on.
//
// .SECTION See Also
// vtkClipDataSet vtkClipPolyData vtkClipVolume vtkContourFilter
//
#ifndef __vtkBandedPolyDataContourFilter_h
#define __vtkBandedPolyDataContourFilter_h

#include "vtkFiltersModelingModule.h" // For export macro
#include "vtkPolyDataAlgorithm.h"

#include "vtkContourValues.h" // Needed for inline methods

class vtkPoints;
class vtkCellArray;
class vtkPointData;
class vtkDataArray;
class vtkFloatArray;
class vtkDoubleArray;

#define VTK_SCALAR_MODE_INDEX 0
#define VTK_SCALAR_MODE_VALUE 1

class VTKFILTERSMODELING_EXPORT vtkBandedPolyDataContourFilter : public vtkPolyDataAlgorithm
{
public:
  vtkTypeMacro(vtkBandedPolyDataContourFilter,vtkPolyDataAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Construct object with no contours defined.
  static vtkBandedPolyDataContourFilter *New();

  // Description:
  // Methods to set / get contour values. A single value at a time can be
  // set with SetValue(). Multiple contour values can be set with
  // GenerateValues(). Note that GenerateValues() generates n values
  // inclusive of the start and end range values.
  void SetValue(int i, double value);
  double GetValue(int i);
  double *GetValues();
  void GetValues(double *contourValues);
  void SetNumberOfContours(int number);
  int GetNumberOfContours();
  void GenerateValues(int numContours, double range[2]);
  void GenerateValues(int numContours, double rangeStart, double rangeEnd);

  // Description:
  // Indicate whether to clip outside the range specified by the user.
  // (The range is contour value[0] to contour value[numContours-1].)
  // Clipping means all cells outside of the range specified are not
  // sent to the output.
  vtkSetMacro(Clipping,int);
  vtkGetMacro(Clipping,int);
  vtkBooleanMacro(Clipping,int);

  // Description:
  // Control whether the cell scalars are output as an integer index or
  // a scalar value. If an index, the index refers to the bands produced
  // by the clipping range. If a value, then a scalar value which is a
  // value between clip values is used.
  vtkSetClampMacro(ScalarMode,int,VTK_SCALAR_MODE_INDEX,VTK_SCALAR_MODE_VALUE);
  vtkGetMacro(ScalarMode,int);
  void SetScalarModeToIndex()
    {this->SetScalarMode(VTK_SCALAR_MODE_INDEX);}
  void SetScalarModeToValue()
    {this->SetScalarMode(VTK_SCALAR_MODE_VALUE);}

  // Description:
  // Turn on/off a flag to control whether contour edges are generated.
  // Contour edges are the edges between bands. If enabled, they are
  // generated from polygons/triangle strips and placed into the second
  // output (the ContourEdgesOutput).
  vtkSetMacro(GenerateContourEdges,int);
  vtkGetMacro(GenerateContourEdges,int);
  vtkBooleanMacro(GenerateContourEdges,int);

  // Description:
  // Get the second output which contains the edges dividing the contour
  // bands. This output is empty unless GenerateContourEdges is enabled.
  vtkPolyData *GetContourEdgesOutput();

  // Description:
  // Overload GetMTime because we delegate to vtkContourValues so its
  // modified time must be taken into account.
  unsigned long GetMTime();

protected:
  vtkBandedPolyDataContourFilter();
  ~vtkBandedPolyDataContourFilter();

  int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *);

  int ComputeScalarIndex(double);
  int IsContourValue(double val);
  int ClipEdge(int v1, int v2, vtkPoints *pts, vtkDataArray *inScalars,
               vtkDoubleArray *outScalars,
               vtkPointData *inPD, vtkPointData *outPD);
  int InsertCell(vtkCellArray *cells, int npts, vtkIdType *pts,
                 int cellId, double s, vtkFloatArray *newS);

  // data members
  vtkContourValues *ContourValues;

  int Clipping;
  int ScalarMode;

  // sorted and cleaned contour values
  double *ClipValues;
  int   NumberOfClipValues;
  int ClipIndex[2]; //indices outside of this range (inclusive) are clipped
  double ClipTolerance; //used to clean up numerical problems

  //the second output
  int GenerateContourEdges;

private:
  vtkBandedPolyDataContourFilter(const vtkBandedPolyDataContourFilter&);  // Not implemented.
  void operator=(const vtkBandedPolyDataContourFilter&);  // Not implemented.
};

// Description:
// Set a particular contour value at contour number i. The index i ranges
// between 0<=i<NumberOfContours.
inline void vtkBandedPolyDataContourFilter::SetValue(int i, double value)
  {this->ContourValues->SetValue(i,value);}

// Description:
// Get the ith contour value.
inline double vtkBandedPolyDataContourFilter::GetValue(int i)
  {return this->ContourValues->GetValue(i);}

// Description:
// Get a pointer to an array of contour values. There will be
// GetNumberOfContours() values in the list.
inline double *vtkBandedPolyDataContourFilter::GetValues()
  {return this->ContourValues->GetValues();}

// Description:
// Fill a supplied list with contour values. There will be
// GetNumberOfContours() values in the list. Make sure you allocate
// enough memory to hold the list.
inline void vtkBandedPolyDataContourFilter::GetValues(double *contourValues)
  {this->ContourValues->GetValues(contourValues);}

// Description:
// Set the number of contours to place into the list. You only really
// need to use this method to reduce list size. The method SetValue()
// will automatically increase list size as needed.
inline void vtkBandedPolyDataContourFilter::SetNumberOfContours(int number)
  {this->ContourValues->SetNumberOfContours(number);}

// Description:
// Get the number of contours in the list of contour values.
inline int vtkBandedPolyDataContourFilter::GetNumberOfContours()
  {return this->ContourValues->GetNumberOfContours();}

// Description:
// Generate numContours equally spaced contour values between specified
// range. Contour values will include min/max range values.
inline void vtkBandedPolyDataContourFilter::GenerateValues(int numContours,
                                                           double range[2])
  {this->ContourValues->GenerateValues(numContours, range);}

// Description:
// Generate numContours equally spaced contour values between specified
// range. Contour values will include min/max range values.
inline void vtkBandedPolyDataContourFilter::GenerateValues(int numContours,
                                                           double rangeStart,
                                                           double rangeEnd)
  {this->ContourValues->GenerateValues(numContours, rangeStart, rangeEnd);}


#endif
