#include "Engine.h"
#include "cgpch.h"

int main()
{
    Cologne::Log::Init();
    CG_CORE_INFO("Initializing engine...");
    Engine engine;
    int status = engine.init();
    if (status == -1)
    {
        CG_CORE_ERROR("Engine initialization failed.");
        return -1;
    }
    CG_CORE_INFO("Initializing engine successful, running.");
    engine.run();
    return 0;
}
