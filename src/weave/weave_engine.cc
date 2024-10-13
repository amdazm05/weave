#include <weave/weave_engine.hpp>
using namespace weave;


WeaveEngine::WeaveEngine()
{
    spdlog::set_level(spdlog::level::info);
    spdlog::log(spdlog::level::info, "Weave Engine Initialised");
    CURLcode err = curl_global_init(CURL_GLOBAL_ALL);
    curl_error_reporter.check_error(err);
}

WeaveEngine::~WeaveEngine()
{

}
WeaveEngine & WeaveEngine::init(size_t curlpool_size,size_t threadpool)
{
    static WeaveEngine _inst{};
    return _inst;
}