//
// Created by alecp on 6/2/2024.
//

#ifndef COLOGNE_LOG_H
#define COLOGNE_LOG_H

#include <spdlog/spdlog.h>
#include <memory>

namespace Cologne
{
    class Log
    {
    public:
        static void Init();
        inline static std::shared_ptr<spdlog::logger>& GetLogger() {return s_CoreLogger;}
    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
    };
}
#define CG_CORE_ERROR(...) ::Cologne::Log::GetLogger()->error(__VA_ARGS__)
#define CG_CORE_WARN(...) ::Cologne::Log::GetLogger()->warn(__VA_ARGS__)
#define CG_CORE_INFO(...) ::Cologne::Log::GetLogger()->info(__VA_ARGS__)
#define CG_CORE_TRACE(...) ::Cologne::Log::GetLogger()->trace(__VA_ARGS__)

#endif //COLOGNE_LOG_H


