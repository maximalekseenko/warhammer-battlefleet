#include "debug.h"



#include <fstream>
#include <string>
#include <filesystem>
#include <iostream>
#include <ctime> 



namespace debug
{
    std::ofstream outputFile;

    int Init(int arg, const char** argv)
    {
        // make log folder
        std::filesystem::path __logFolderPath = std::filesystem::path(argv[0]).parent_path() / "log";
        if (!std::filesystem::exists(__logFolderPath))
            std::filesystem::create_directory(__logFolderPath);
        
        // make log file
        int __logFilePrefix = 0;
        std::filesystem::path __logFilePath = __logFolderPath / "log";
        while (std::filesystem::exists(__logFilePath))
        {
            __logFilePrefix ++;
            __logFilePath = __logFilePath.parent_path() / (std::string("log") + std::to_string(__logFilePrefix));
        }
        outputFile.open(__logFilePath);
        return true;
    }


    int Deinit()
    {
        outputFile.close();
    }


    void Log(const char* _text)
    {
        outputFile << "Log: " << _text << std::endl;
    }


    void Error(const char* _text)
    {
        outputFile << "Err: " << _text << std::endl;
    }
}