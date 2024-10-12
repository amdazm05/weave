#include <weave/weave_engine.hpp>
using namespace weave;


WeaveEngine::WeaveEngine()
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