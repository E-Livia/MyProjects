#pragma once
#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>

#ifdef LOGGING_EXPORTS
	#define LOGGING_API __declspec(dllexport)
#else
	#define LOGGING_API __declspec(dllimport)
#endif //LOGGING_EXPORTS

class LOGGING_API Logging
{
public:
	enum class Level
	{
		eINFO,
		eWARNING,
		eERROR
	};
	Logging(std::ostream& os, Level minimumLevel = Level::eINFO);

	template <class T>
	void log(const T& message, Level level);

	template <class ... Args>
	void logI(Level level, Args && ...param)
	{
		switch (level)
		{
		case Logging::Level::eINFO:
			m_Logfile << "[INFO]" << std::endl;
			break;
		case Logging::Level::eWARNING:
			m_Logfile << "[WARNING]" << std::endl;
			break;
		case Logging::Level::eERROR:
			m_Logfile << "[ERROR]" << std::endl;
			break;
		}

		((m_Logfile << std::forward < Args >(param)), ...);
		m_Logfile << std::endl;
	}

	void setMinimumLogLevel(Level minimumLevel);

private:
	Level minimumLevel;
	std::ostream& m_Logfile;
};

template<class T>
inline void Logging::log(const T& message, Level level)
{
	auto timenow =std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	char buffer[26];
	ctime_s(buffer, sizeof buffer, &timenow);
	buffer[24] = '\0';
	if (level >= minimumLevel)
	{
		switch (level)
		{
		case Logging::Level::eINFO:
			m_Logfile << "[INFO]";
			break;
		case Logging::Level::eWARNING:
			m_Logfile << "[WARNING]";
			break;
		case Logging::Level::eERROR:
			m_Logfile << "[ERROR]";
			break;
		}
		m_Logfile <<"[ "<< buffer <<" ]: " << message << std::endl;
	}
}

