/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkPlatonicSolidSource.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkPlatonicSolidSource - produce polygonal Platonic solids
// .SECTION Description
// vtkPlatonicSolidSource can generate each of the five Platonic solids:
// tetrahedron, cube, octahedron, icosahedron, and dodecahedron. Each of the
// solids is placed inside a sphere centered at the origin with radius 1.0.
// To use this class, simply specify the solid to create. Note that this
// source object creates cell scalars that are (integral value) face numbers.

#ifndef __vtkPlatonicSolidSource_h
#define __vtkPlatonicSolidSource_h

#include "vtkFiltersSourcesModule.h" // For export macro
#include "vtkPolyDataAlgorithm.h"

#define VTK_SOLID_TETRAHEDRON  0
#define VTK_SOLID_CUBE         1
#define VTK_SOLID_OCTAHEDRON   2
#define VTK_SOLID_ICOSAHEDRON  3
#define VTK_SOLID_DODECAHEDRON 4

class VTKFILTERSSOURCES_EXPORT vtkPlatonicSolidSource : public vtkPolyDataAlgorithm
{
public:
  static vtkPlatonicSolidSource *New();
  vtkTypeMacro(vtkPlatonicSolidSource,vtkPolyDataAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Specify the type of PlatonicSolid solid to create.
  vtkSetClampMacro(SolidType,int,VTK_SOLID_TETRAHEDRON,VTK_SOLID_DODECAHEDRON);
  vtkGetMacro(SolidType,int);
  void SetSolidTypeToTetrahedron()
    {this->SetSolidType(VTK_SOLID_TETRAHEDRON);}
  void SetSolidTypeToCube()
    {this->SetSolidType(VTK_SOLID_CUBE);}
  void SetSolidTypeToOctahedron()
    {this->SetSolidType(VTK_SOLID_OCTAHEDRON);}
  void SetSolidTypeToIcosahedron()
    {this->SetSolidType(VTK_SOLID_ICOSAHEDRON);}
  void SetSolidTypeToDodecahedron()
    {this->SetSolidType(VTK_SOLID_DODECAHEDRON);}

protected:
  vtkPlatonicSolidSource();
  ~vtkPlatonicSolidSource() {}

  virtual int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *);
  int SolidType;

private:
  vtkPlatonicSolidSource(const vtkPlatonicSolidSource&);  // Not implemented.
  void operator=(const vtkPlatonicSolidSource&);  // Not implemented.

};

#endif


