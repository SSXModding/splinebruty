#ifndef SK_UTIL_H
#define SK_UTIL_H

#include <iostream>
#include <cstdio>
#include <string>
#include <string_view>


template<class T>
bool ReadInto(std::istream& is, T& t) {
	is.read(reinterpret_cast<char*>(&t), sizeof(T));
	return is.good();
}

template<class... Args>
std::string strfmt(const std::string_view format, Args&&... args) {
	static char buf[1024]{};
	std::snprintf(&buf[0], sizeof(buf), format.data(), std::forward<Args>(args)...);
	return &buf[0];
}


#endif // SK_UTIL_H