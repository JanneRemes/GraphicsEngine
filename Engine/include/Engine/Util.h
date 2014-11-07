
#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <codecvt>

class Util
{
public:
	static bool ReadTextFile(const std::string& filepath, std::string& out)
	{
		std::ifstream in(filepath);

		if (in.is_open())
		{
			std::stringstream ss;

			while (!in.eof())
			{
				if (in.fail())
					return false; // Error: Unable to read file
				
				ss << in.get();
			}

			out = ss.str();
			return true; // Success
		}

		return false; // Error: Unable to open file
	}

	static bool ReadTextFile(const std::string& filepath, const char* out)
	{
		std::ifstream in(filepath);

		if (in.is_open())
		{
			std::stringstream ss;

			while (!in.eof())
			{
				if (in.fail())
					return false; // Error: Unable to read file

				ss << in.get();
			}

			out = ss.str().c_str();
			return true; // Success
		}

		return false; // Error: Unable to open file
	}

	static std::wstring&& Convert(const std::string& str)
	{
		return std::move(std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t>().from_bytes(str));
	}

	static std::string&& Convert(const std::wstring& wstr)
	{
		return std::move(std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t>().to_bytes(wstr));
	}
};

#endif // Include guard
