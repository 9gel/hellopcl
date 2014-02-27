/*=========================================================================

  Program:   ParaView
  Module:    vtkDelimitedTextWriter.h

  Copyright (c) Kitware, Inc.
  All rights reserved.
  See Copyright.txt or http://www.paraview.org/HTML/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/*-------------------------------------------------------------------------
  Copyright 2009 Sandia Corporation.
  Under the terms of Contract DE-AC04-94AL85000 with Sandia Corporation,
  the U.S. Government retains certain rights in this software.
-------------------------------------------------------------------------*/

// .NAME vtkDelimitedTextWriter - Delimited text writer for vtkTable
// Writes a vtkTable as a delimited text file (such as CSV).
#ifndef __vtkDelimitedTextWriter_h
#define __vtkDelimitedTextWriter_h

#include "vtkIOCoreModule.h" // For export macro
#include "vtkWriter.h"

class vtkStdString;
class vtkTable;

class VTKIOCORE_EXPORT vtkDelimitedTextWriter : public vtkWriter
{
public:
  static vtkDelimitedTextWriter* New();
  vtkTypeMacro(vtkDelimitedTextWriter, vtkWriter);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Get/Set the delimiter use to separate fields ("," by default.)
  vtkSetStringMacro(FieldDelimiter);
  vtkGetStringMacro(FieldDelimiter);

  // Description:
  // Get/Set the delimiter used for string data, if any
  // eg. double quotes(").
  vtkSetStringMacro(StringDelimiter);
  vtkGetStringMacro(StringDelimiter);

  // Description:
  // Get/Set the filename for the file.
  vtkSetStringMacro(FileName);
  vtkGetStringMacro(FileName);

  // Description:
  // Get/Set if StringDelimiter must be used for string data.
  // True by default.
  vtkSetMacro(UseStringDelimiter, bool);
  vtkGetMacro(UseStringDelimiter, bool);

  // Description:
  // Enable writing to an OutputString instead of the default, a file.
  vtkSetMacro(WriteToOutputString,bool);
  vtkGetMacro(WriteToOutputString,bool);
  vtkBooleanMacro(WriteToOutputString,bool);

  // Description:
  // This convenience method returns the string, sets the IVAR to NULL,
  // so that the user is responsible for deleting the string.
  char *RegisterAndGetOutputString();

  // Description:
  // Internal method: Returns the "string" with the "StringDelimiter" if
  // UseStringDelimiter is true.
  vtkStdString GetString(vtkStdString string);
protected:
  vtkDelimitedTextWriter();
  ~vtkDelimitedTextWriter();

  bool WriteToOutputString;
  char* OutputString;

  bool OpenStream();

  virtual void WriteData();
  virtual void WriteTable(vtkTable* rectilinearGrid);

  // see algorithm for more info.
  // This writer takes in vtkTable.
  virtual int FillInputPortInformation(int port, vtkInformation* info);

  char* FileName;
  char* FieldDelimiter;
  char* StringDelimiter;
  bool UseStringDelimiter;
//BTX
  ostream* Stream;
//ETX
private:
  vtkDelimitedTextWriter(const vtkDelimitedTextWriter&); // Not implemented.
  void operator=(const vtkDelimitedTextWriter&); // Not implemented.
};



#endif

