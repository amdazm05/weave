#include <weave/curl/callbacks.hpp>

int weave_callbacks::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((const char*)contents, nmemb);
    return nmemb;
}

