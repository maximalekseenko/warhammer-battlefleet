#pragma once



namespace debug
{
    int Init(int arg, const char** argv);
    int Deinit();

    void Log(const char* _text);
    void Error(const char* _text);
}