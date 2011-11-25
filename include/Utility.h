#ifndef UTILITY_H_
#define UTILITY_H_

#include <list>
#include <string>
using namespace std;



namespace Utility {
	class SerialUtility {
		public:
			static list<string> GetSerials();
			static bool TestSerial(const char *);			
	};
	
	class DataUtility {
		public:
			static double ToRealValue(unsigned int value, unsigned char type);
			static double LambdaLookup(unsigned int value);
			static double AFRLookup(unsigned int value);
	};
}

#endif /*UTILITY_H_*/
