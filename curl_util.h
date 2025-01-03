/*curl_util.h*/

//
// CURL utility functions for calling a web server.
//   https://everything.curl.dev/libcurl
//

#pragma once

#include <iostream>
#include <string>

#include <curl/curl.h>

using namespace std;

//
//
bool callWebServer(CURL* curl, string url, string& response);
