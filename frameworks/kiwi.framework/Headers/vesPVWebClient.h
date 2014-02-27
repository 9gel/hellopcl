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
/// \class vesPVWebClient
/// \ingroup KiwiPlatform
#ifndef __vesPVWebClient_h
#define __vesPVWebClient_h

#include <vector>
#include <string>
#include <sstream>
#include <tr1/memory>


class vesPVWebDataSet;
typedef void CURL;
struct cJSON;

typedef std::tr1::shared_ptr<cJSON> jsonSharedPtr;

class vesPVWebClient
{
public:


  typedef std::tr1::shared_ptr<vesPVWebClient> Ptr;

  vesPVWebClient();

  ~vesPVWebClient();

  void downloadObjects();

  bool downloadObject(int objectIndex);

  bool pollSceneMetaData();

  bool parseSceneMetaData(const std::stringstream& resp);

  jsonSharedPtr rpc(const std::string& method, cJSON* params=0, int connectTimeout=0);

  bool createVisualization();

  bool endVisualization();

  jsonSharedPtr executeCommand(const std::string& command, cJSON* params=0, int connectTimeout=0);

  bool configure(int enableRendering, int imageDelivery, int enableWebGL);

  void configureOn();

  void configureOff();

  std::string errorTitle() const;

  std::string errorMessage() const;

  void resetErrorMessages();

  void setError(const std::string& errorTitle, const std::string& errorMessage);

  void defaultResponseErrorMessage();

  void defaultCurlErrorMessage();

  bool createView();

  void setHost(const std::string& host);

  void setSessionId(const std::string& sessionId);

  const std::vector<std::tr1::shared_ptr<vesPVWebDataSet> >& datasets() const;

  const std::vector<double>& lookAt() const;
  const std::vector<double>& backgroundColor() const;

private:

  int m_id;
  std::string m_viewId;
  std::string m_sessionId;
  std::string m_host;
  CURL* m_curl;

  std::vector<std::tr1::shared_ptr<vesPVWebDataSet> > m_datasets;
  std::vector<double> m_lookAt;
  std::vector<double> m_backgroundColor;

  std::string mErrorTitle;
  std::string mErrorMessage;

};


#endif
