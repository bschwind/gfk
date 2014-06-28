#include <string>
#include <iostream>
#include <GFK/System/Logger.hpp>

using namespace gfk;

int main()
{
	// These checks are made to guarantee the types are at least a certain size.
	// The network code relies on data types being at least a certain size
	static_assert(sizeof(bool) >= 1, "bool is not one byte");
	static_assert(sizeof(signed short int) >= 2, "signed short int is not two bytes");
	static_assert(sizeof(unsigned short int) >= 2, "unsigned short int is not two bytes");
	static_assert(sizeof(signed int) >= 4, "signed int is not four bytes");
	static_assert(sizeof(unsigned int) >= 4, "unsigned int is not four bytes");
	static_assert(sizeof(signed long int) >= 8, "signed long int is not eight bytes");
	static_assert(sizeof(unsigned long int) >= 8, "unsigned long int is not eight bytes");
	static_assert(sizeof(float) >= 4, "float is not four bytes");
	static_assert(sizeof(double) >= 8, "double is not eight bytes");

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
