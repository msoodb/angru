// This is start of the header guard.  INC_cryptography_H can be any unique name.  By convention, we use the name of the header file.
#ifndef INC_cryptography_H
#define INC_cryptography_H

// This is the content of the .h file, which is where the declarations go
class _cryptography
{
public:
	static std::string get_md5(const std::string& p_arg);
	static std::string get_sha1(const std::string& p_arg);
	static std::string get_sha256(const std::string& p_arg);
};
// This is the end of the header guard
#endif
