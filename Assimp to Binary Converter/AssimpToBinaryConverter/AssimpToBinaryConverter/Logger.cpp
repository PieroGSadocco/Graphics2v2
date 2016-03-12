#include "Logger.h"

void Logger::Log(std::string _text)
{
	std::ofstream log("_MainLog.txt", std::fstream::app);

	log << _text << '\n';
	std::cout << _text << '\n';

	log.close();
}

void Logger::Log(unsigned short _num, std::string _text)
{
	std::ofstream log("_MainLog.txt", std::fstream::app);

	for (int i = 0; i != _num; ++i)
	{
		log << '\t';
		std::cout << '\t';
	}

	log << _text << '\n';
	std::cout << _text << '\n';

	log.close();
}



void Logger::Log(int _text)
{
	std::ofstream log("_MainLog.txt", std::fstream::app);

	log << _text << '\n';
	std::cout << _text << '\n';

	log.close();
}

void Logger::Log(unsigned short _num, int _text)
{
	std::ofstream log("_MainLog.txt", std::fstream::app);

	for (int i = 0; i != _num; ++i)
	{
		log << '\t';
		std::cout << '\t';
	}

	log << _text << '\n';
	std::cout << _text << '\n';

	log.close();
}

void Logger::Clear()
{
	std::ofstream log("_MainLog.txt");

	log << "";

	log.close();
}