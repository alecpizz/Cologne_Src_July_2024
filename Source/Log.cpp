//
// Created by alecp on 6/2/2024.
//

#include "Log.h"
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Cologne
{
    std::shared_ptr<spdlog::logger> Log::s_CoreLogger;

    void Log::Init()
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");
        s_CoreLogger = spdlog::stdout_color_mt("Cologne");
        s_CoreLogger->set_level(spdlog::level::trace);
    }
}
