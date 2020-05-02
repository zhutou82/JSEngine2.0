#pragma once

namespace JSEngine
{
    template <typename T>
    class Singleton
    {
    public:
        static T& GetInstance()
        {
            static T singleton;
            return singleton;
        }

        Singleton(const Singleton&) = delete;
        const Singleton& operator=(const Singleton&) = delete;

    protected:
        Singleton() {}
        ~Singleton() {}

    private:
    };
}

