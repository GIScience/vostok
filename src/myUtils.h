
#ifndef MYUTILS_H_
#define MYUTILS_H_

#include <vector>
#include <string>
#include <sstream>

std::vector<std::string> splitString(std::string str, char delimiter);


std::istream& safeGetline(std::istream& is, std::string& t);

#endif /* MYUTILS_H_ */