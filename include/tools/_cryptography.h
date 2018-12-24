#ifndef ANGRU_CRYPTOGRAPHY_H_
#define ANGRU_CRYPTOGRAPHY_H_

#include <iostream>

class _cryptography
{
public:
	static std::string get_base64(const std::string&);
	static std::string get_md5(const std::string&);
	static std::string get_sha1(const std::string&);
	static std::string get_sha256(const std::string&);
	static std::string get_jwt(const std::string&, const std::string&);
};

#endif // ANGRU_CRYPTOGRAPHY_H_
