#ifndef STRING_UTIL_H
#define STRING_UTIL_H

#include <algorithm>  
#include <cctype>
#include <iostream>
#include <locale>
#include <sstream>
#include <vector>

namespace stringUtil {
    static const char* cr{ "\r" };
    static const char* lf{ "\n" };
    static const char* crlf{ "\r\n" };
    static const char* wspc{ " " };
	
    // trim from start (in place)
    static inline void lTrim(std::string& s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](const unsigned char ch) { return !std::isspace(ch); }));
    }

    // trim from end (in place)
    static inline void rTrim(std::string& s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), [](const unsigned char ch) { return !std::isspace(ch); }).base(), s.end());
    }


    // trim from both ends (in place)
    static inline void trim(std::string& s) {
        lTrim(s);
        rTrim(s);
    }

    // trim from start (copying)
    static inline std::string lTrimCopy(std::string s) {
        lTrim(s);
        return s;
    }

    // trim from end (copying)
    static inline std::string rTrimCopy(std::string s) {
        rTrim(s);
        return s;
    }

    // trim from both ends (copying)
    static inline std::string trimCopy(std::string s) {
        trim(s);
        return s;
    }

    template <typename conversionType>
    static inline std::vector<conversionType> splitString(const std::string& string, const char delimiter = ',')
    {
        std::vector<conversionType> result;
        if (string.empty()) return result;

        std::stringstream ss(string);

        while (ss.good()) {
            std::string substr;
            getline(ss, substr, delimiter);
            std::istringstream iss(substr);
            conversionType res;
            try {
                getline(iss, res);
            }
            catch (...)
            {
                continue;
            }
            result.push_back(res);
        }
        return result;
    }

	static inline std::string findUntil(const std::string& string, const char* delimiter = {})
    {
	    const std::string::size_type pos = string.find(delimiter);
        if (pos == std::string::npos)
        {
            return string;
        }
        return trimCopy(string.substr(0, pos));
    }

	static inline std::string strip(const std::string& string, const std::string& remove)
    {
        std::string value = string;
        const size_t pos = value.find(remove);
        if (pos != std::string::npos)
        {
            value = value.erase(pos, remove.length());
            trim(value);
        }
        return value;
    }

	static inline std::string escape(const std::string& string)
    {
        std::string escaped;
        for (auto char_p = string.begin(); char_p != string.end(); ++char_p)
        {
	        const char character = *char_p;
            switch (character)
            {
            case '\a': escaped.append("\\a"); break;
            case '\b': escaped.append("\\b"); break;
            case '\f': escaped.append("\\f"); break;
            case '\n': escaped.append("\\n"); break;
            case '\r': escaped.append("\\r"); break;
            case '\t': escaped.append("\\t"); break;
            case '\v': escaped.append("\\v"); break;
            case '\'': escaped.append("\\'"); break;
            case '\"': escaped.append("\\\""); break;
            case '\?': escaped.append("\\\?"); break;
            default: escaped += character;
            }
        }
        return escaped;
    }

	static inline std::pair<bool, int> extractInteger(const std::string& string)
    {
	    std::stringstream ss;

        ss << string;

        std::string temp;
        int found;
        while (!ss.eof()) {
            ss >> temp;

            if (std::stringstream(temp) >> found)
                return {true, found};
            temp = "";
        }
        return {false, 0};
    }

	static inline bool divide(const std::string& string, const char delimiter, std::string& left, std::string& right)
    {
        const size_t found = string.find(delimiter);
        if (found != std::string::npos)
        {
            left = string.substr(0, found);
            right = string.substr(found + 1);
            return true;
        }
        return false;
    }

    static inline bool ldivide(const std::string& string, const char delimiter, std::string& left, std::string& right)
    {
        const size_t found = string.find_last_of(delimiter);
        if (found != std::string::npos)
        {
            left = string.substr(0, found);
            right = string.substr(found + 1);
            return true;
        }
        return false;
    }

    static inline bool fdivide(const std::string& string, const char delimiter, std::string& left, std::string& right)
    {
        const size_t found = string.find_first_of(delimiter);
        if (found != std::string::npos)
        {
            left = string.substr(0, found);
            right = string.substr(found + 1);
            return true;
        }
        return false;
    }


	static inline bool findBeforeLast(const std::string& string, const char delimiter, std::string& output)
    {
        const size_t found = string.find_last_of(delimiter);
        if (found != std::string::npos)
        {
            output = string.substr(0, found);
            return true;
        }
        return false;
    }

    static inline void appendIf(std::string& string, const std::string& append)
    {
        if (append.length() > string.size())
        {
            string.append(append);
            return;
        }
        if (std::equal(append.rbegin(), append.rend(), string.rbegin()))
        {
            return;
        }
        string.append(append);
    }
	
	static inline void addCrlf(std::string& string)
    {
        appendIf(string, crlf);
    }

    static inline void eraseEnd(std::string& string, const std::string& remove)
    {
        const size_t pos = string.find_last_of(remove);
        if (pos != std::string::npos)
        {
            string.erase(pos, remove.length());
        }
    }

    static inline void eraseBegin(std::string& string, const std::string& remove)
    {
	    const size_t pos = string.find(remove);
        if (pos != std::string::npos)
        {
            string.erase(pos, remove.length());
        }
    }

    static inline void eraseCrlf(std::string& string)
    {
        eraseEnd(string, crlf);
    }

    static inline void eraseCr(std::string& string)
    {
        eraseEnd(string, cr);
    }

    template <typename T>
    static T convert(const std::string& string, T default_ = {})
    {
        T res;
        if (string.empty())
        {
            return default_;
        }
        std::istringstream iss(string);
        try {
            iss >> res;
            return res;
        }
        catch (...)
        {
            return default_;
        }
    }
}

#endif // STRING_UTIL_H