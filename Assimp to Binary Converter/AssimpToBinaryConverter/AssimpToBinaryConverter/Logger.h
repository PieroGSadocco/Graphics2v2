#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <iostream>
#include <string>

class Logger
{
public:
	static void Log(std::string _text);
	static void Log(unsigned short _num, std::string _text);

	static void Log(int _text);
	static void Log(unsigned short _num, int _text);

	static void Clear();
};

#endif