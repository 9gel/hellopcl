/*========================================================================
  VES --- VTK OpenGL ES Rendering Toolkit

      http://www.kitware.com/ves

  Copyright 2011 Kitware, Inc.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
 ========================================================================*/
/// \class vesKiwiFPSCounter
/// \ingroup KiwiPlatform
/// \brief A class for keeping a exponential moving average of frames per second.
#ifndef __vesKiwiFPSCounter_h
#define __vesKiwiFPSCounter_h

#include "vesSharedPtr.h"
#include "vesSetGet.h"

#include <vtk/vtkTimerLog.h>

class vesKiwiFPSCounter
{
public:

  vesTypeMacro(vesKiwiFPSCounter);

  vesKiwiFPSCounter()
  {
    mAlpha = 0.9;
    mTimeWindow = 1.0;
    mAverageFPS = 1.0;
    mFramesThisWindow = 0;
    mLastUpdateTime = mWindowStartTime = vtkTimerLog::GetUniversalTime();
  }

  ~vesKiwiFPSCounter()
  {
  }

  double alpha() const
  {
    return mAlpha;
  }

  void setAlpha(double alpha)
  {
    mAlpha = alpha;
  }

  double timeWindow() const
  {
    return mTimeWindow;
  }

  void setTimeWindow(double seconds)
  {
    mTimeWindow = seconds;
  }

  void update()
  {
    // update counters
    mLastUpdateTime = vtkTimerLog::GetUniversalTime();
    ++mFramesThisWindow;

    // check if a time window has elapsed
    double elapsedTime = mLastUpdateTime - mWindowStartTime;
    if (elapsedTime > mTimeWindow) {

      // compute FPS for this time window
      double averageFPSThisWindow = mFramesThisWindow / elapsedTime;

      // update moving average
      mAverageFPS = mAlpha * averageFPSThisWindow + (1.0 - mAlpha) * mAverageFPS;

      // reset counters
      mWindowStartTime = mLastUpdateTime;
      mFramesThisWindow = 0;
    }
  }

  double averageFPS() const
  {
    return mAverageFPS;
  }

private:

  vesKiwiFPSCounter(const vesKiwiFPSCounter&); // Not implemented
  void operator=(const vesKiwiFPSCounter&); // Not implemented


  double mAlpha;
  double mAverageFPS;
  double mTimeWindow;

  size_t mFramesThisWindow;

  double mLastUpdateTime;
  double mWindowStartTime;
};


#endif
