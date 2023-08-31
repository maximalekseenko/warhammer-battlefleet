#include "init.h"



#include "window.h"
#include "renderer.h"
#include "debug.h"



namespace init
{
    int Init(int arg, const char** argv)
    {
        debug::Init(arg, argv);
        window::Init(arg, argv);
        renderer::Init(arg, argv);
    }


    int Deinit()
    {
        debug::Deinit();
        window::Deinit();
        renderer::Deinit();
    }
}