/**
 * @file helper.hpp
 * @author Rick Waasdorp (r.waasdorp@tudelft.nl)
 * @brief
 * @version 0.1
 * @date 2023-04-20
 *
 * @copyright Copyright (c) 2023
 *
 */
#define _CRT_SECURE_NO_WARNINGS
#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>

/**
 * @brief returns the current date and time with milliseconds as a string
 *
 * @return std::string
 */
std::string timestamp()
{
    using namespace std::chrono;
    using clock = system_clock;
    const auto current_time_point{clock::now()};
    const auto current_time{clock::to_time_t(current_time_point)};
    const auto current_localtime{*std::localtime(&current_time)};
    const auto current_time_since_epoch{current_time_point.time_since_epoch()};
    const auto current_milliseconds{duration_cast<milliseconds>(current_time_since_epoch).count() % 1000};
    std::ostringstream stream;
    stream << std::put_time(&current_localtime, "%T") << "." << std::setw(3) << std::setfill('0') << current_milliseconds;
    return stream.str();
}

/**
 * @brief returns the current time since epoch in milliseconds
 *
 * @return size_t
 */
size_t timestamp_ms()
{
    using namespace std::chrono;
    milliseconds ms = duration_cast<milliseconds>(
        system_clock::now().time_since_epoch());
    return ms.count();
}