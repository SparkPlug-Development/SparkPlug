#include "Debug.h"
#include <iostream>
#include <string>

//-----------Todo/Ideas-----------//
/*

//TODO:
  1. Remove unused colors.

*/

#ifdef SP_DEBUG
#define DEBUGGING true
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"
#else
#define DEBUGGING false
#define RED   "ERR"
#define GRN   "ERR"
#define YEL   "ERR"
#define BLU   "ERR"
#define MAG   "ERR"
#define CYN   "ERR"
#define WHT   "ERR"
#define RESET "ERR"
#endif



void Debug::log(const std::string& mess, const int& level, const DEBUG_TYPE& mess_type, const std::string &caller, const Debug::CHANNEL &channel){
	if (DEBUGGING) { //This should be evaluated on compile, das ist sher guttenberger.
		if (level <= deb_level) {

			switch (mess_type) { //flush cout/cerr when printing. (may be slow)
				default: //Overflow to debug
				case Debug::DEBUG_TYPE::debug:
					std::cout << GRN<< mess << RESET << std::endl;
					Debug::to_print.append(mess + '\n');
					break;
				case Debug::DEBUG_TYPE::warning:
					std::cout << CYN << mess << RESET << std::endl;
					break;
				case Debug::DEBUG_TYPE::error: //This is not a fatal error, so 
					std::cerr << YEL << mess << RESET << std::endl;
					Debug::to_print.append("--ERROR >> " + mess + '\n');
					break;
				case Debug::DEBUG_TYPE::fatalError:
					std::cerr << RED << mess << RESET << std::endl;
					Debug::to_print.append("----------FATAL_ERROR----------\n\t" + mess + '\n');
					return;
			}
			if (to_print.size() >= Debug::buffer_size) {
				//output to debug file.

			}
		}
	}
}

bool Debug::writeFile(const std::string&){
	return false;
}

void Debug::init(const size_t& buffer_size, const int& deb_level) {
	Debug::buffer_size = buffer_size;
	Debug::deb_level = deb_level;
}