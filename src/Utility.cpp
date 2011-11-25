//system stuff
#include <sys/types.h>
#include <sys/stat.h>
#include "unistd.h"
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include "stdio.h"
#include "errno.h"

//common
#include "Common.h"

//stdlib stuff
#include <list>
#include <string>
using namespace std;

//program stuff
#include "Utility.h"

namespace Utility {
	list<string> SerialUtility::GetSerials() {
		//open /dev
		DIR *slashDev;
		slashDev = opendir("/dev");
		
		//loop through entries and add ttyS* ttyUSB* to list
		list<string> serialList;
		struct dirent *entry;
		string temp;
		temp.empty();
		while ( NULL != (entry = readdir(slashDev)) ) {
			if ( (0 == strncmp(entry->d_name, "ttyS", 4)) || (0 == strncmp(entry->d_name, "ttyUSB", 6)) ) {
				temp.assign("/dev/");
				temp.append(entry->d_name);
				serialList.push_front(temp);
				temp.empty();
			}
		}
		
		if ( serialList.size() == 0 ) {
			temp.empty();
			temp = "Not found!";
			serialList.push_front(temp);
		}
		
		return serialList;
	}
	
	bool SerialUtility::TestSerial(const char *device) {
		if ( device == NULL ) {
			return false;
		}
		
		int fd = 0;
		if ( -1 == (fd = open(device, O_RDONLY)) ) {
			printf("Failure connecting to (%s): %s\n", device, strerror(errno));
			return false;
		}
		
		close(fd);
		
		return true;
	}
	
	double DataUtility::LambdaLookup(unsigned int value) {
		//lambda conversion table
		double LambdaTable[LAMBDA_TABLE_SIZE] = {
			0.6090909,
			0.6194399,
			0.6297890,
			0.6401380,
			0.6504870,
			0.6608360,
			0.6711851,
			0.6815341,
			0.6918831,
			0.7022321,
			0.7125812,
			0.7229302,
			0.7332792,
			0.7436282,
			0.7539773,
			0.7643263,
			0.7746753,
			0.7850244,
			0.7953734,
			0.8068848,
			0.8193359,
			0.8317871,
			0.8428318,
			0.8581955,
			0.8727295,
			0.8861441,
			0.8987359,
			0.9112542,
			0.9247264,
			0.9402781,
			0.9589708,
			0.9816769,
			1.0090000,
			1.0412468,
			1.0784486,
			1.1204268,
			1.1668906,
			1.2175537,
			1.2722518,
			1.3310412,
			1.3942620,
			1.4625494,
			1.5367892,
			1.6180211,
			1.7073194,
			1.8057041,
			1.9141808,
			2.0340606,
			2.1677944,
			2.3206609,
			2.5038020,
			2.7393036,
			3.0683068,
			3.5635231,
			4.3480558,
			5.6231434,
			7.7083941,
			11.0993449,
			16.5488420,
			25.1809044,
			38.6485324,
			59.3505045,
			90.7267620,
			137.6577167,
			207.0000000
		};
        //linear interpolation of a non-linear function
        //First, we need to figure out the difference between the current cell and the next cell (ti - t)
        //
        //Based on that information, we're able to figure out how much each ADC point is worth by 
        //diving by ival.  Dividing by ival (instead of current Ipx) is necessary to ensure linear
        //interpolation ONLY against the current and next cell (vs linear interpolation of the ENTIRE range)
        //We only need to do this because the Ipx -vs- Lambda curve is complete non-linear and can't
        //be represented by any reasonable algorithm.
        //
        //Now that we know how much each ADC point is worth, we multiply it by the cell position
        //relative to the table resolution.  Since we're working cell-by-cell, the modulo helps
        //"reset" our multiplier when we enter a new cell because there isn't a linear relation between
        //cells.
        //
        //lastly, we add this adjustment value to the base Lambda value and continue from there
        //
        //Yes, this is dirty.  Does it work?  sorta.
        //In order to improve this interpolation, I could try to come up with a complex exponential
        //equation to represent the curve, but I feel that it's unnecessasry.
		
		//figure out what the interval size is
		int ival	= 8192 / (LAMBDA_TABLE_SIZE - 1);
		//figure out what index of the lookup array we're on based on ival
		int idx		= value / ival;
		//bounce any indexes that are out of bounds
		if ( idx < 0 || idx > (LAMBDA_TABLE_SIZE - 1) ) {
			return 0;
		}
		//get the current lambda and the next lambda
		//if we're already on the last cell, there is no next-lambda
		double l1 = LambdaTable[idx];
		double l2 = LambdaTable[idx >= LAMBDA_TABLE_SIZE ? idx : idx + 1];
		double lambda = l1 + (((l2 - l1) / ival) * (value % ival));
		
		return lambda;
	}
	
	double DataUtility::AFRLookup(unsigned int value) {
		return LambdaLookup(value) * 14.7;
	}
	
	double DataUtility::ToRealValue(unsigned int value, unsigned char type) {
		double x = 0;
		
		switch (type) {
			case TEWB_TICK:
				x = (double)value;
				break;
			
			case TEWB_AFR_RAW:
				x = (double)value;
				break;
			
			case TEWB_AFR_IPX:
				x = LambdaLookup(value);
				break;
			
			case TEWB_U1:
				x = ((double)value / TEWB_UMAX) * 200;
				break;
			
			case TEWB_U2:
				x = ((double)value / TEWB_UMAX) * 200;
				break;
			
			case TEWB_U3:
				x = ((double)value / TEWB_UMAX) * 200;
				break;
			
			case TEWB_T1:
				x = ((double)value / TEWB_UMAX) * 200;
				break;
			
			case TEWB_T2:
				x = ((double)value / TEWB_UMAX) * 200;
				break;
			
			case TEWB_T3:
				x = ((double)value / TEWB_UMAX) * 200;
				break;
			
			case TEWB_THERM:
				x = ((double)value / TEWB_UMAX) * 200;
				break;
			
			case TEWB_RPM:
				x = ((double)value / TEWB_UMAX) * 200;
				break;
			
			default:
				break;
		}
		
		return x;
	}
}
