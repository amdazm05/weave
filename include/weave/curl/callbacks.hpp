#ifndef _WEAVE_CURL_CALLBACK
#define _WEAVE_CURL_CALLBACK

#include <iostream>

namespace weave_callbacks
{
    int WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
}

#endif