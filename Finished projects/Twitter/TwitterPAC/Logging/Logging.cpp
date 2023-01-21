#include "Logging.h"

Logging::Logging(std::ostream& os, Level minimumLevel)
	: m_Logfile(os), minimumLevel(minimumLevel)
{

}

void Logging::setMinimumLogLevel(Level minimumLevel)
{
	this->minimumLevel = minimumLevel;
}