#ifndef __ERRORHANDLER_H
#define __ERRORHANDLER_H

#include <iostream>

#define LOGGER_ERROR 0
#define LOGGER_WARNING 1

class Logger {
private:
	int level;

public:
    Logger(int _level): level(_level) {}

    std::string getLevel() {
    	switch (this->level) {
    		case LOGGER_ERROR: return "error";
    		case LOGGER_WARNING: return "warning";
    	}
    	return "";
    }

    template<typename T>
    Logger& operator<<(const T &t) {
        std::cout << this->getLevel() << ": " << t << std::endl;
        return *this;
    }
};

#endif // __ERRORHANDLER_H