// Copyright © 2018 | Nikolay Klimontov | klimontov.nikolay@gmail.com
//----------------------------------------------------------------------
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the LICENSE file for more details.
//----------------------------------------------------------------------
#ifndef EIN_LOGGER_HPP
#define EIN_LOGGER_HPP

#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include "templates.hpp"

#include <cstring>
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define __SCOPE__ __PRETTY_FUNCTION__
#define __STR(X) std::string(#X)

namespace Utils
{
    namespace Logging
    {
        static const std::string logo = R"(
     ___ _ __  _
    | __|_|  \| |
    | _|| | | ' |
    |___|_|_|\__|

     Game engine
)";
        enum Severity{critical, error, warning, info, debug, unknown};

        //TODO: add file rotation
        class Log
        {
            std::ostream& target = std::cout;

        public:

            Log()
            {
                target<< std::endl << logo <<std::endl;
            };

            std::ostream& log(Severity severity, const char* file, const char* scope, int line)
            {
                std::time_t today_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
                target << std::ctime(&today_time)<< "[" <<to_string(severity) << "][" <<file<< ":"<<line << "] " << scope <<": ";

                return target;
            };

        protected:

            std::string to_string(Severity s) noexcept
            {
                switch (s)
                {
                    case critical: return __STR(critical);
                    case error:    return __STR(error);
                    case warning:  return __STR(warning);
                    case info:     return __STR(info);
                    case debug:    return __STR(debug);
                    default:       return __STR(unknown);
                }
            }
        };
    }
}
using Logger = Utils::Singleton<Utils::Logging::Log>;

#define LOG_DEBUG()     Logger::instance()->log(Utils::Logging::Severity::debug,    __FILENAME__, __SCOPE__, __LINE__)
#define LOG_INFO()      Logger::instance()->log(Utils::Logging::Severity::info,     __FILENAME__, __SCOPE__, __LINE__)
#define LOG_WARNING()   Logger::instance()->log(Utils::Logging::Severity::warning,  __FILENAME__, __SCOPE__, __LINE__)
#define LOG_ERROR()     Logger::instance()->log(Utils::Logging::Severity::error,    __FILENAME__, __SCOPE__, __LINE__)
#define LOG_CRITICAL()  Logger::instance()->log(Utils::Logging::Severity::critical, __FILENAME__, __SCOPE__, __LINE__)

#define LOG_FILE_WAS_READ(FILE)   LOG_INFO() <<"Reading file '"<<(FILE) <<"': SUCCESS" <<std::endl
#define LOG_FAILED_TO_READ(FILE)  LOG_ERROR()<<"Reading file '"<<(FILE) <<"': FAILED" <<std::endl


#endif //EIN_LOGGER_HPP
