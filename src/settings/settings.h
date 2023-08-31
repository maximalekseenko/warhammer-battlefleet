#pragma once



#include <filesystem>



namespace settings
{
    struct Settings
    {
        std::filesystem::path execPath;
    };

    Settings* settings();
}