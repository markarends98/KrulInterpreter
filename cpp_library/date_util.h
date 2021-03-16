#ifndef DATE_UTIL_H
#define DATE_UTIL_H

#include <chrono>
#include <filesystem>
#include <iomanip>
#include <iosfwd>
#include <sstream>
#include <string>

namespace dateUtil
{
	template <typename timeType>
	static inline time_t toTimeT(const timeType time)
	{
		const auto chrono = std::chrono::time_point_cast<std::chrono::system_clock::duration>(time - timeType::clock::now() + std::chrono::system_clock::now());
		return std::chrono::system_clock::to_time_t(chrono);
	}

	static inline std::string format(const time_t& time, const std::string& stringFormat)
	{
		tm gmt{};
		gmtime_s(&gmt, &time);
		std::stringstream buffer;
		buffer << std::put_time(&gmt, stringFormat.c_str());
		return buffer.str();
	}
	
	static inline std::string format(const std::filesystem::file_time_type& time, const std::string& stringFormat)
	{
		const time_t converted = toTimeT(time);
		return format(converted, stringFormat);
	}
}
#endif // DATE_UTIL_H
