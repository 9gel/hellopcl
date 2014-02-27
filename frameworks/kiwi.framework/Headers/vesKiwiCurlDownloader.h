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
/// \class vesKiwiCurlDownloader
/// \ingroup KiwiPlatform
#ifndef __vesKiwiCurlDownloader_h
#define __vesKiwiCurlDownloader_h

#include <string>
#include "vesSharedPtr.h"

typedef void CURL;

class vesKiwiCurlDownloader
{
public:

  vesKiwiCurlDownloader();

  ~vesKiwiCurlDownloader();

  bool downloadUrlToFile(const std::string& url, const std::string& destFile);

  std::string downloadUrlToDirectory(const std::string& url, const std::string& downloadDir);


  class ProgressDelegate {
    public:
      virtual int downloadProgress(double totalToDownload, double nowDownloaded) = 0;
  };

  void setProgressDelegate(vesSharedPtr<ProgressDelegate> delegate)
  {
    this->mProgressDelegate = delegate;
  }

  void setAttachmentFileName(const std::string filename)
  {
    this->mAttachmentFileName = filename;
  }

  std::string attachmentFileName() const
  {
    return this->mAttachmentFileName;
  }

  std::string errorTitle() const
  {
    return this->mErrorTitle;
  }

  std::string errorMessage() const
  {
    return this->mErrorMessage;
  }

  bool renameFile(const std::string& srcFile, const std::string& destFile);

  // Computes the directory name from the given filename and creates the
  // directory if it does not exist.  Returns false if the directory cannot
  // be created.
  bool createDirectoryForFile(const std::string& filename);

protected:

  void resetErrorMessages()
  {
    this->mErrorTitle = std::string();
    this->mErrorMessage = std::string();
  }

  void setError(const std::string& errorTitle, const std::string& errorMessage)
  {
    // preserve the existing error message if one already exists
    if (this->mErrorMessage.empty()) {
      this->mErrorTitle = errorTitle;
      this->mErrorMessage = errorMessage;
    }
  }

private:

  std::string mErrorTitle;
  std::string mErrorMessage;
  std::string mAttachmentFileName;

  CURL* m_curl;

  vesSharedPtr<ProgressDelegate> mProgressDelegate;
};

#endif
