#include <weave/weave_engine.hpp>
using namespace weave;


WeaveEngine::WeaveEngine() : _curlHandler(CurlHandler::instance())
{
    spdlog::set_level(spdlog::level::info);
    spdlog::log(spdlog::level::info, "Weave Engine Initialised");
}

WeaveEngine::~WeaveEngine()
{

}
WeaveEngine & WeaveEngine::get_context()
{
    static WeaveEngine _inst{};
    return _inst;
}

CurlHandler & WeaveEngine::get_curl_handle()
{
    return _curlHandler;
}