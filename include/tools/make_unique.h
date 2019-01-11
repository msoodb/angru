#ifndef ANGRU_MAKE_UNIQUE_H_
#define ANGRU_MAKE_UNIQUE_H_


#if CXX_COMPILE_MODE == CXX_COMPILE_MODE_98 \
    || CXX_COMPILE_MODE == CXX_COMPILE_MODE_03 \
    || CXX_COMPILE_MODE == CXX_COMPILE_MODE_0x \
    || CXX_COMPILE_MODE == CXX_COMPILE_MODE_11

#include <memory>
#include <utility>

namespace angru{
namespace system{

template<typename _T, typename ..._ARGS>
std::unique_ptr<_T> make_unique(_ARGS &&...args)
{
    return std::unique_ptr<_T>(new _T(std::forward<_ARGS>(args)...));
}

} // namespace system
} // namespace angru

#endif /* CXX_COMPILE_MODE == CXX_COMPILE_MODE_98 \
    || CXX_COMPILE_MODE == CXX_COMPILE_MODE_03 \
    || CXX_COMPILE_MODE == CXX_COMPILE_MODE_0x \
    || CXX_COMPILE_MODE == CXX_COMPILE_MODE_11 */


#endif // ANGRU_MAKE_UNIQUE_H_
