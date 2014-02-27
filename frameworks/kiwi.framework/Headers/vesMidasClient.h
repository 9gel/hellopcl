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
/// \class vesMidasClient
/// \ingroup KiwiPlatform
#ifndef __vesMidasClient_h
#define __vesMidasClient_h

#include <vector>
#include <map>
#include <string>
#include <tr1/memory>


typedef void CURL;
struct cJSON;

typedef std::tr1::shared_ptr<cJSON> jsonSharedPtr;

class vesMidasClient
{
public:


  typedef std::tr1::shared_ptr<vesMidasClient> Ptr;
  typedef std::map<std::string, std::string> RequestArgs;

  vesMidasClient();

  ~vesMidasClient();

  jsonSharedPtr request(const std::string& method, const RequestArgs& args, bool tryTokenRenewal=true);

  std::string errorTitle() const;

  std::string errorMessage() const;

  void resetErrorMessages();

  void setError(const std::string& errorTitle, const std::string& errorMessage);

  void defaultResponseErrorMessage();

  void defaultCurlErrorMessage();

  void setHost(const std::string& host);

  void setToken(const std::string& token);

  const std::string& token() const;

  bool listUserFolders();

  bool listFolderChildren(const std::string& folderId);

  bool listCommunities();
  bool listCommunityChildren(const std::string& communityId);

  std::string itemDownloadUrl(const std::string& itemId);

  const std::vector<std::string>& folderNames();
  const std::vector<std::string>& folderIds();

  const std::vector<std::string>& itemNames();
  const std::vector<std::string>& itemIds();
  const std::vector<size_t>& itemBytes();

  bool login(const std::string& username, const std::string& password);

  void reset();

  bool renewToken();

  std::string methodUrl(const std::string& method);

  std::string argList(const RequestArgs& args);

private:

  std::string m_apikey;
  std::string m_token;
  std::string m_email;
  std::string m_host;
  CURL* m_curl;

  std::string mErrorTitle;
  std::string mErrorMessage;

  std::vector<std::string> m_folderNames;
  std::vector<std::string> m_folderIds;
  std::vector<std::string> m_itemNames;
  std::vector<std::string> m_itemIds;
  std::vector<size_t> m_itemBytes;

};


#endif
