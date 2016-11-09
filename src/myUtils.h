#include <vector>
#include <string>
#include <sstream>

std::vector<std::string> splitString(std::string str, char delimiter) {

	std::vector<std::string> internal;
	std::stringstream ss(str); // Turn the string into a stream.
	std::string tok;

	while (getline(ss, tok, delimiter)) {
		internal.push_back(tok);
	}

	return internal;
}
