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
	static inline time_t toTimeT(const timeType time, const std::string& stringFormat = "%Y-%m-%d %H:%M:%S")
	{
		const auto chrono = std::chrono::time_point_cast<std::chrono::system_clock::duration>(time - timeType::clock::now() + std::chrono::system_clock::now());
		time_t tmt = std::chrono::system_clock::to_time_t(chrono);
		tm lct{};
		localtime_s(&lct, &tmt);
		return mktime(&lct);
	}

	static inline std::string format(const time_t& time, const std::string& stringFormat = "%Y-%m-%d %H:%M:%S")
	{
		tm lct{};
		localtime_s(&lct, &time);
		std::stringstream buffer;
		buffer << std::put_time(&lct, stringFormat.c_str());
		return buffer.str();
	}
	
	static inline std::string format(const std::filesystem::file_time_type& time, const std::string& stringFormat = "%Y-%m-%d %H:%M:%S")
	{
		const time_t converted = toTimeT(time);
		return format(converted, stringFormat);
	}
	
	static inline time_t toTimeT(const std::string& time, const std::string& stringFormat = "%Y-%m-%d %H:%M:%S")
	{
		struct std::tm tm;
		std::istringstream ss(time);
		ss >> std::get_time(&tm, stringFormat.c_str());
		time_t t = mktime(&tm);
		localtime_s(&tm, &t);
		return mktime(&tm);
	}
}
#endif // DATE_UTIL_H
