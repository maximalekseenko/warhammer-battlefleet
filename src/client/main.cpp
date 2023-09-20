#include "../loop.h"
#include "../init.h"
int main(int arg, const char** argv)
{
    init::Init(arg, argv);
    loop::Run();
    init::Deinit();
}