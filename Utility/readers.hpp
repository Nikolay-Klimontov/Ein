// Copyright © 2018 | Nikolay Klimontov | klimontov.nikolay@gmail.com
//----------------------------------------------------------------------
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the LICENSE file for more details.
//----------------------------------------------------------------------
#ifndef EIN_READERS_HPP
#define EIN_READERS_HPP

#include <string>
#include <logger.hpp>
#include "types.hpp"

namespace Utils
{
    std::string load_text(const std::string& path) noexcept;

}

#endif //EIN_READERS_HPP
