#include <iostream>
#include <string>
#include <boost/uuid/sha1.hpp>
#include "_cryptography.h"

std::string _cryptography::get_md5(const std::string& p_arg){

}
std::string _cryptography::get_sha1(const std::string& p_arg){
  std::cout << "--------------------------------------" << '\n';
  std::cout << p_arg << '\n';
  boost::uuids::detail::sha1 sha1;
      sha1.process_bytes(p_arg.data(), p_arg.size());
      unsigned hash[5] = {0};
      sha1.get_digest(hash);

      // Back to string
      char buf[41] = {0};

      for (int i = 0; i < 5; i++)
      {
          std::sprintf(buf + (i << 3), "%08x", hash[i]);
      }
      std::cout << std::string(buf) << '\n';
      return std::string(buf);
}
std::string _cryptography::get_sha256(const std::string& p_arg){

}
