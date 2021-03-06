// Copyright © 2018 | Nikolay Klimontov | klimontov.nikolay@gmail.com
//----------------------------------------------------------------------
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the LICENSE file for more details.
//----------------------------------------------------------------------
#ifndef EIN_TEMPALTES_HPP
#define EIN_TEMPALTES_HPP

#include <memory>

namespace Utils
{
    template<typename T>
    class Singleton
    {
    public:

        static T* instance() noexcept
        {
            static T class_instance;
            return &class_instance;
        }

        Singleton(const Singleton& root) = delete;
        Singleton& operator=(const Singleton&) = delete;

    private:

        Singleton() = default;
    };


}
#endif //EIN_TEMPALTES_HPP
