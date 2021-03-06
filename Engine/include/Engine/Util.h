
#ifndef UTIL_H
#define UTIL_H

#pragma warning(disable:4996)	// Disable warnings for 'vsnprintf'

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <codecvt>
#include <cstdarg>
#include <algorithm>
#include <Windows.h>

enum class Severity
{
	Info,
	Warning,
	Error
};

class Util
{
public:
	/*
		StringTo<T>
	*/
	template<typename T>
	static bool StringTo(const std::string& str, T& out)
	{
		static_assert(false, "Error: Unsupported conversion. Allowed types are: int, long, ulong, llong, float, double, ldouble.");
	}

	template<>
	static bool StringTo<int>(const std::string& str, int& out)
	{
		try { out = std::stoi(str); return true; }
		catch (...) { return false; }
	}

	template<>
	static bool StringTo<long>(const std::string& str, long& out)
	{
		try { out = std::stol(str); return true; }
		catch (...) { return false; }
	}

	template<>
	static bool StringTo<unsigned long>(const std::string& str, unsigned long& out)
	{
		try { out = std::stoul(str); return true; }
		catch (...) { return false; }
	}

	template<>
	static bool StringTo<long long>(const std::string& str, long long& out)
	{
		try { out = std::stoll(str); return true; }
		catch (...) { return false; }
	}

	template<>
	static bool StringTo<float>(const std::string& str, float& out)
	{
		try { out = std::stof(str); return true; }
		catch (...) { return false; }
	}

	template<>
	static bool StringTo<double>(const std::string& str, double& out)
	{
		try { out = std::stod(str); return true; }
		catch (...) { return false; }
	}

	template<>
	static bool StringTo<long double>(const std::string& str, long double& out)
	{
		try { out = std::stold(str); return true; }
		catch (...) { return false; }
	}
	// ----- ----- -----


	template<typename T>
	static size_t GetTypeId()
	{
		static const char typeAddress;
		return reinterpret_cast<size_t>(&typeAddress);
	}

	template<typename T>
	static std::vector<T> GetUnique(const std::vector<T>& vec)
	{
		std::vector<T> copy(vec);
		std::sort(copy.begin(), copy.end());
		copy.erase(std::unique(copy.begin(), copy.end()), copy.end());
		return copy;
	}

	static fpos_t GetFileSize(std::ifstream& stream)
	{
		const fpos_t orig = stream.tellg();
		stream.seekg(0, std::ios_base::end);
		const fpos_t size = stream.tellg();
		stream.seekg(orig, std::ios_base::beg);
		return size;
	}

	static bool ReadTextFile(const std::string& filepath, std::string& out)
	{
		std::ifstream in(filepath);

		if (in.is_open())
		{
			std::stringstream ss;
			char c;

			while (true)
			{
				c = in.get();

				if (in.eof())
					break;

				if (in.fail())
					return false; // Error: Unable to read file
				
				ss << c;
			}

			out = ss.str();
			return true; // Success
		}

		return false; // Error: Unable to open file
	}

	static std::wstring Convert(const std::string& str)
	{
		return std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t>().from_bytes(str);
	}

	static std::string Convert(const std::wstring& wstr)
	{
		return std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t>().to_bytes(wstr);
	}

	static std::string Format(const char* format, ...)
	{
		va_list args;
		va_start(args, format);
		int length = vsnprintf(nullptr, 0, format, args);
		std::vector<char> buffer(length + 1);

		va_start(args, format);
		vsnprintf(buffer.data(), buffer.size(), format, args);
		return std::string(buffer.data());
	}

	static std::wstring Format(const wchar_t* format, ...)
	{
		va_list args;
		va_start(args, format);
		int length = vswprintf(nullptr, 0, format, args);
		std::vector<wchar_t> buffer(length + 1);

		va_start(args, format);
		vswprintf(buffer.data(), buffer.size(), format, args);
		return std::wstring(buffer.data());
	}

	static void ShowMessage(const std::string& msg, const std::string& title = "", size_t style = MB_ICONINFORMATION)
	{
		MessageBox(nullptr, Util::Convert(msg).c_str(), Util::Convert(title).c_str(), style);
	}

	static void ShowMessage(const std::wstring& msg, const std::wstring& title = L"", size_t style = MB_ICONINFORMATION)
	{
		MessageBox(nullptr, msg.c_str(), title.c_str(), style);
	}

	static std::string GetTimeStamp()
	{
		time_t rawtime;
		time(&rawtime);
		std::vector<char> buffer(9);
		strftime(buffer.data(), buffer.size(), "%H:%M:%S", localtime(&rawtime));
		return std::string(buffer.begin(), buffer.end());
	}

	static void LogMessage(const std::string& msg, std::ostream& stream = std::cout, Severity sev = Severity::Info)
	{
		const std::string& time = Util::GetTimeStamp();

		switch (sev)
		{
		case Severity::Info:	stream << Util::Format("[%s] [Info] %s\n", time.c_str(), msg.c_str());    return;
		case Severity::Warning: stream << Util::Format("[%s] [Warning] %s\n", time.c_str(), msg.c_str()); return;
		case Severity::Error:	stream << Util::Format("[%s] [Error] %s\n", time.c_str(), msg.c_str());   return;
		}
	}

	static void LogMessage(const std::string& msg, const std::string& filename, Severity sev = Severity::Info)
	{
		std::ofstream stream(filename, std::ios_base::app);

		if (stream.is_open())
		{
			Util::LogMessage(msg, stream, sev);
		}
	}
};

#endif // Include guard
