/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkLongLongArray.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkLongLongArray - dynamic, self-adjusting array of long long
// .SECTION Description
// vtkLongLongArray is an array of values of type long long.
// It provides methods for insertion and retrieval of values and will
// automatically resize itself to hold new data.

#ifndef __vtkLongLongArray_h
#define __vtkLongLongArray_h

// Tell the template header how to give our superclass a DLL interface.
#if !defined(__vtkLongLongArray_cxx)
# define VTK_DATA_ARRAY_TEMPLATE_TYPE long long
#endif

#include "vtkCommonCoreModule.h" // For export macro
#include "vtkDataArray.h"
#include "vtkDataArrayTemplate.h" // Real Superclass

// Fake the superclass for the wrappers.
#define vtkDataArray vtkDataArrayTemplate<long long>
class VTKCOMMONCORE_EXPORT vtkLongLongArray : public vtkDataArray
#undef vtkDataArray
{
public:
  static vtkLongLongArray* New();
  vtkTypeMacro(vtkLongLongArray,vtkDataArray);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Get the data type.
  int GetDataType()
    { return VTK_LONG_LONG; }

  // Description:
  // Copy the tuple value into a user-provided array.
  void GetTupleValue(vtkIdType i, long long* tuple)
    { this->RealSuperclass::GetTupleValue(i, tuple); }

  // Description:
  // Set the tuple value at the ith location in the array.
  void SetTupleValue(vtkIdType i, const long long* tuple)
    { this->RealSuperclass::SetTupleValue(i, tuple); }

  // Description:
  // Insert (memory allocation performed) the tuple into the ith location
  // in the array.
  void InsertTupleValue(vtkIdType i, const long long* tuple)
    { this->RealSuperclass::InsertTupleValue(i, tuple); }

  // Description:
  // Insert (memory allocation performed) the tuple onto the end of the array.
  vtkIdType InsertNextTupleValue(const long long* tuple)
    { return this->RealSuperclass::InsertNextTupleValue(tuple); }

  // Description:
  // Get the data at a particular index.
  long long GetValue(vtkIdType id)
    { return this->RealSuperclass::GetValue(id); }

  // Description:
  // Set the data at a particular index. Does not do range checking. Make sure
  // you use the method SetNumberOfValues() before inserting data.
  void SetValue(vtkIdType id, long long value)
    { this->RealSuperclass::SetValue(id, value); }

  // Description:
  // Specify the number of values for this object to hold. Does an
  // allocation as well as setting the MaxId ivar. Used in conjunction with
  // SetValue() method for fast insertion.
  void SetNumberOfValues(vtkIdType number)
    { this->RealSuperclass::SetNumberOfValues(number); }

  // Description:
  // Insert data at a specified position in the array.
  void InsertValue(vtkIdType id, long long f)
    { this->RealSuperclass::InsertValue(id, f); }

  // Description:
  // Insert data at the end of the array. Return its location in the array.
  vtkIdType InsertNextValue(long long f)
    { return this->RealSuperclass::InsertNextValue(f); }

  // Description:
  // Get the range of array values for the given component in the
  // native data type.
  long long *GetValueRange(int comp)
    { return this->RealSuperclass::GetValueRange(comp); }
//BTX
  void GetValueRange(long long range[2], int comp)
    { this->RealSuperclass::GetValueRange(range, comp); }
//ETX

  // Description:
  // Get the range of array values for the 0th component in the
  // native data type.
  long long *GetValueRange()
    { return this->RealSuperclass::GetValueRange(0); }
//BTX
  void GetValueRange(long long range[2])
    { this->RealSuperclass::GetValueRange(range, 0); }
//ETX

  // Description:
  // Get the minimum data value in its native type.
  static long long GetDataTypeValueMin() { return VTK_LONG_LONG_MIN; }

  // Description:
  // Get the maximum data value in its native type.
  static long long GetDataTypeValueMax() { return VTK_LONG_LONG_MAX; }

  // Description:
  // Get the address of a particular data index. Make sure data is allocated
  // for the number of items requested. Set MaxId according to the number of
  // data values requested.
  long long* WritePointer(vtkIdType id, vtkIdType number)
    { return this->RealSuperclass::WritePointer(id, number); }

  // Description:
  // Get the address of a particular data index. Performs no checks
  // to verify that the memory has been allocated etc.
  long long* GetPointer(vtkIdType id)
    { return this->RealSuperclass::GetPointer(id); }

  // Description:
  // This method lets the user specify data to be held by the array.  The
  // array argument is a pointer to the data.  size is the size of
  // the array supplied by the user.  Set save to 1 to keep the class
  // from deleting the array when it cleans up or reallocates memory.
  // The class uses the actual array provided; it does not copy the data
  // from the suppled array.
  void SetArray(long long* array, vtkIdType size, int save)
    { this->RealSuperclass::SetArray(array, size, save); }
  void SetArray(long long* array, vtkIdType size, int save, int deleteMethod)
    { this->RealSuperclass::SetArray(array, size, save, deleteMethod); }

protected:
  vtkLongLongArray(vtkIdType numComp=1);
  ~vtkLongLongArray();

private:
  //BTX
  typedef vtkDataArrayTemplate<long long> RealSuperclass;
  //ETX
  vtkLongLongArray(const vtkLongLongArray&);  // Not implemented.
  void operator=(const vtkLongLongArray&);  // Not implemented.
};

#endif
