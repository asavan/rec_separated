#pragma once

#include <string>
#include <iosfwd>

namespace Codec {

	void SaveStringToFile( std::ostream& os, const std::string& str_in );
	std::string LoadStringFromFile( std::istream& is);

} // namespace Codec

void SaveStringToTextFile(std::ostream& os, const std::string& str);
std::string IntToString(int n, int field_size = 0);
