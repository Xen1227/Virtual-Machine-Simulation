#pragma once
#include <exception>

class NonFatal : public std::exception
{
    public:

    NonFatal(int code)
    {
        exceptionCode = code;
    }

    int getCode() {return exceptionCode;}

    private:

    int exceptionCode;
};

class Fatal : public std::exception
{
    public:

    Fatal(int code)
    {
        exceptionCode = code;
    }

    int getCode() {return exceptionCode;}

    private:

    int exceptionCode;
};