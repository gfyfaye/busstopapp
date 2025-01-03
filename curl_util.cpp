/*curl_util.cpp*/

//
// CURL utility functions for calling a web server.
// 

#include <iostream>
#include <fstream>
#include <string>

#include "curl_util.h"

using namespace std;


static size_t CURL_callback(void* contents, size_t size, size_t nmemb, std::string* output) {

  size_t total_size = size * nmemb;

  output->append((char*)contents, total_size);

  return total_size;
}


static string getURLParam(string url, string key)
{
  auto pos = url.find(key);
  if (pos == string::npos)
    return "-1";
  
  auto endpos = url.find("&", pos);
  if (endpos == string::npos)
    return "-1";
  
  size_t start = pos + key.length();
  size_t len = endpos - start;
  return url.substr(start, len);
}

bool callWebServer(CURL* curl, string url, string& response)
{


#ifdef OFFLINE
  string route = getURLParam(url, "rt=");
  string stopid = getURLParam(url, "stpid=");
  
  string filename = "cta-response-route-";
  filename = filename + route + "-stopid-";
  filename = filename + stopid + ".cta";
 
  ifstream infile(filename);
  if (!infile.is_open()) {
    cout << "**ERROR: in callWebServer, we are running offline..." << endl;
    cout << "**ERROR: you called with rt=" << route << ",stpid=" << stopid << endl;
    cout << "**ERROR: no data is available for this route/stop" << endl;
    
    return false;
  }
  
  string line;
  response = "";
  
  while (getline(infile, line))
  {
    response += line;
    response += '\n';
  }
  
  infile.close();
  
  return true;

#else
  //
  // call the online web service:
  //
  curl_easy_reset(curl);

  int rc1 = curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
  int rc2 = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CURL_callback);
  int rc3 = curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

  if (rc1 != CURLE_OK || rc2 != CURLE_OK || rc3 != CURLE_OK)
    return false;

  //
  // call web server, which triggers call to callback function when the
  // response arrives:
  //
  int rc = curl_easy_perform(curl);

  if (rc != CURLE_OK)
    return false;

  // 
  // if get here, it worked:
  //
#ifdef SAVE_ONLINE_RESPONSES
    string route = getURLParam(url, "rt=");
    string stopid = getURLParam(url, "stpid=");
   
    string filename = "cta-response-route-";
    filename = filename + route + "-stopid-";
    filename = filename + stopid + ".cta";
   
    ofstream outfile(filename);
    outfile << response << endl;
    outfile.close();
#endif
  
  return true;

#endif 
  
}

