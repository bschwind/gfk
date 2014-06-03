#include <string>
#include <iostream>
#include <GFK/System/Logger.hpp>

using namespace gfk;

int main()
{
	std::cout << "bool                    = " << sizeof(bool) << " bytes" << std::endl;
	std::cout << "char                    = " << sizeof(char) << " bytes" << std::endl;
	std::cout << "char16_t                = " << sizeof(char16_t) << " bytes" << std::endl;
	std::cout << "char32_t                = " << sizeof(char32_t) << " bytes" << std::endl;
	std::cout << "wchar_t                 = " << sizeof(wchar_t) << " bytes" << std::endl;
	std::cout << "signed char             = " << sizeof(signed char) << " bytes" << std::endl;
	std::cout << "short int               = " << sizeof(short int) << " bytes" << std::endl;
	std::cout << "int                     = " << sizeof(int) << " bytes" << std::endl;
	std::cout << "long int                = " << sizeof(long int) << " bytes" << std::endl;
	std::cout << "long long int           = " << sizeof(long long int) << " bytes" << std::endl;
	std::cout << "unsigned char           = " << sizeof(unsigned char) << " bytes" << std::endl;
	std::cout << "unsigned short int      = " << sizeof(unsigned short int) << " bytes" << std::endl;
	std::cout << "unsigned int            = " << sizeof(unsigned int) << " bytes" << std::endl;
	std::cout << "unsigned long int       = " << sizeof(unsigned long int) << " bytes" << std::endl;
	std::cout << "unsigned long long int  = " << sizeof(unsigned long long int) << " bytes" << std::endl;
	std::cout << "float                   = " << sizeof(float) << " bytes" << std::endl;
	std::cout << "double                  = " << sizeof(double) << " bytes" << std::endl;
	std::cout << "long double             = " << sizeof(long double) << " bytes" << std::endl;
	
	return 0;
}
