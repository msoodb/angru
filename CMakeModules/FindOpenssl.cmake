#  (The MIT License)
#
#  Copyright (c) 2016 Mohammad S. Babaei
#
#  Permission is hereby granted, free of charge, to any person obtaining a copy
#  of this software and associated documentation files (the "Software"), to deal
#  in the Software without restriction, including without limitation the rights
#  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#  copies of the Software, and to permit persons to whom the Software is
#  furnished to do so, subject to the following conditions:
#
#  The above copyright notice and this permission notice shall be included in
#  all copies or substantial portions of the Software.
#
#  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
#  THE SOFTWARE.


find_package(PkgConfig REQUIRED)
pkg_search_module(OPENSSL REQUIRED openssl)

IF ( OPENSSL_FOUND )
    MESSAGE ( STATUS "Found Openssl headers in ${OPENSSL_INCLUDE_DIRS}" )
    MESSAGE ( STATUS "Found Openssl library version ${OPENSSL_VERSION}: ${OPENSSL_LIBRARIES}" )
ELSE (  )
    IF ( OPENSSL_FIND_REQUIRED )
        MESSAGE ( FATAL_ERROR "Could not find Openssl" )
    ELSE (  )
        MESSAGE ( STATUS "Could not find Openssl" )
    ENDIF (  )
ENDIF (  )
