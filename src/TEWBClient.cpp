#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <cstdlib>

#include "TEWBClient.h"
#include "Common.h"

namespace TEWB {

	TEWBClient::TEWBClient() {
	}

	TEWBClient::~TEWBClient() {
		//we should restore the options of the serial device first
		if ( -1 == tcsetattr(this->fd, TCSANOW, &(this->oldterm)) ) {
			printf("Error resetting device options: %s\n", strerror(errno));
		}

		//and then we close the device
		if ( -1 == close(this->fd) ) {
			printf("Error closing device: %s\n", strerror(errno));
		}
	}

	bool TEWBClient::Connect(const char *device) {
		//open the device
		//read + write
		//don't allow device to become proc's controlling terminal
		if ( -1 == (this->fd = open(device, O_RDWR | O_NOCTTY )) ) {
			printf("Error opening device %s: %s\n", device, strerror(errno));
			return false;
		}

		//grab the current term settings and save them
		//we will restore them upon exit of this class
		if ( -1 == tcgetattr(this->fd, &(this->oldterm)) ) {
			printf("Error saving device options: %s\n", strerror(errno));
			return false;
		}

		//lets get some options together to
		//make this terminal as basic as possible
		//we'll also set the BAUDRATE which comes from Common.h
		struct termios termopts;
		bzero(&termopts, sizeof(struct termios));
		cfsetispeed(&termopts, BAUDRATE);
		cfsetospeed(&termopts, BAUDRATE);
		cfmakeraw(&termopts);

		//and now lets activate those options...
		if ( -1 == tcsetattr(this->fd, TCSANOW, &termopts) ) {
			printf("Error setting device options: %s\n", strerror(errno));
		    return false;
		}

		return true;
	}

	unsigned char *TEWBClient::GetFrame() {
		int br = 0;
		int current = 0;
		unsigned char byte;
		bool syncd = false;
		unsigned char *pkt = (unsigned char *)malloc(FRAMESIZE);
		bzero(pkt, sizeof(FRAMESIZE));


		//make sure we are sync'd
		while (!syncd) {
			if ( 1 != (br = read(this->fd, &byte, 1)) ) {
				printf("bad read: %s, %d\n", strerror(errno), br);
				//return this packet because it's zeros
				return pkt;
			}

			if ( byte == HEADER0 ) {
				pkt[0] = byte;
				if ( 1 != read(this->fd, &byte, 1) ) {
					printf("bad read: %s, %d\n", strerror(errno), br);
					return pkt;
				}
				if ( byte == HEADER1 ) {
					pkt[1] = byte;
					syncd = true;
				}
			}
		}

		//grab the rest of the data
		for ( current = 2; current < FRAMESIZE; current++ ) {
			if ( 1 != read(this->fd, &(pkt[current]), 1) ) {
				return pkt;
			}
		}

		//perform CRC check before sending packet back
		unsigned char crcsum = 0;
		for ( current = 0; current < FRAMESIZE; current++ ) {
			crcsum += pkt[current];
		}

		//if crc fails, then don't return the faulty packet
		if ( crcsum != 0xFF ) {
			bzero(pkt, sizeof(FRAMESIZE));
			return pkt;
		}

		return pkt;
	}

	void TEWBClient::DumpStatus() {
		unsigned char *frame = this->GetFrame();

		char state1Desc[6][15] = {
			"Null/Off/Debug",
			"WBo2 Discover",
			"Booting",
			"Ready",
			"Config/Test",
			"N/A"
		};

		char state2Desc[7][15] = {
			"Normal State",
			"vBatt High",
			"vBatt Low",
			"Heater Short",
			"Heater Open",
			"FET Failure",
			"N/A"
		};

		printf("  Unit State: %d (%s)\n", frame[25], state1Desc[frame[25]]);
		printf("Sensor State: %d (%s)\n", frame[26], state2Desc[frame[26]]);
	}

	unsigned int TEWBClient::Debug() {
		unsigned char *frame = this->GetFrame();
		unsigned int Tick	= 0;
		unsigned int WBRaw	= 0;
		unsigned int Ipx	= 0;
		unsigned int User1	= 0;
		unsigned int User2	= 0;
		unsigned int User3	= 0;
		unsigned int TC1	= 0;
		unsigned int TC2	= 0;
		unsigned int TC3	= 0;
		unsigned int Therm	= 0;
		unsigned int RPM	= 0;

		Tick	= ( frame[3] << 8 ) | frame[4];
		WBRaw	= ( frame[5] << 8 ) | frame[6];
		Ipx		= ( frame[7] << 8 ) | frame[8];
		User1	= ( frame[9] << 8 ) | frame[10];
		User2	= ( frame[11] << 8 ) | frame[12];
		User3	= ( frame[13] << 8 ) | frame[14];
		TC1		= ( frame[15] << 8 ) | frame[16];
		TC2		= ( frame[17] << 8 ) | frame[18];
		TC3		= ( frame[19] << 8 ) | frame[20];
		Therm	= ( frame[21] << 8 ) | frame[22];
		RPM		= ( frame[23] << 8 ) | frame[24];

		return Tick;
	}

	unsigned int *TEWBClient::GetHumanFrame() {
		unsigned char *frame = this->GetFrame();

		unsigned int Tick	= 0;
		unsigned int WBRaw	= 0;
		unsigned int Ipx	= 0;
		unsigned int User1	= 0;
		unsigned int User2	= 0;
		unsigned int User3	= 0;
		unsigned int Tc1	= 0;
		unsigned int Tc2	= 0;
		unsigned int Tc3	= 0;
		unsigned int Therm	= 0;
		unsigned int RPM	= 0;

		Tick	= ( frame[3]	<< 8 ) | frame[4];
		WBRaw	= ( frame[5]	<< 8 ) | frame[6];
		Ipx		= ( frame[7]	<< 8 ) | frame[8];
		User1	= ( frame[9]	<< 8 ) | frame[10];
		User2	= ( frame[11]	<< 8 ) | frame[12];
		User3	= ( frame[13]	<< 8 ) | frame[14];
		Tc1		= ( frame[15]	<< 8 ) | frame[16];
		Tc2		= ( frame[17]	<< 8 ) | frame[18];
		Tc3		= ( frame[19]	<< 8 ) | frame[20];
		Therm	= ( frame[21]	<< 8 ) | frame[22];
		RPM		= ( frame[23]	<< 8 ) | frame[24];

		unsigned int packet[FRAMESIZE];
		packet[0]	= Tick;
		packet[1]	= WBRaw;
		packet[2]	= Ipx;
		packet[3]	= User1;
		packet[4]	= User2;
		packet[5]	= User3;
		packet[6]	= Tc1;
		packet[7]	= Tc2;
		packet[8]	= Tc3;
		packet[9]	= Therm;
		packet[10]	= RPM;

		delete frame;

		unsigned int *rpkt = (unsigned int *)malloc(FRAMESIZE);
		memcpy(rpkt, packet, FRAMESIZE);

		return rpkt;
	}

	unsigned int *TEWBClient::GetTestFrame() {

		srand((unsigned)time(0));

		unsigned int packet[FRAMESIZE];
		packet[0]	= (unsigned int)rand() % 30000;
		packet[1]	= (unsigned int)rand() % 4095;
		packet[2]	= (unsigned int)rand() % 8191;
		packet[3]	= (unsigned int)rand() % 8184;
		packet[4]	= (unsigned int)rand() % 8184;
		packet[5]	= (unsigned int)rand() % 8184;
		packet[6]	= (unsigned int)rand() % 1023;
		packet[7]	= (unsigned int)rand() % 1023;
		packet[8]	= (unsigned int)rand() % 1023;
		packet[9]	= 0;
		packet[10]	= (unsigned int)rand() % 512;

		unsigned int *rpkt = (unsigned int *)malloc(FRAMESIZE);
		memcpy(rpkt, packet, FRAMESIZE);

		return rpkt;
	}


	void TEWBClient::DumpHumanFrame() {
		unsigned char *frame = this->GetFrame();
		unsigned int Tick	= 0;
		unsigned int WBRaw	= 0;
		unsigned int Ipx	= 0;
		unsigned int User1	= 0;
		unsigned int User2	= 0;
		unsigned int User3	= 0;
		unsigned int TC1	= 0;
		unsigned int TC2	= 0;
		unsigned int TC3	= 0;
		unsigned int Therm	= 0;
		unsigned int RPM	= 0;

		Tick	= ( frame[3] << 8 ) | frame[4];
		WBRaw	= ( frame[5] << 8 ) | frame[6];
		Ipx		= ( frame[7] << 8 ) | frame[8];
		User1	= ( frame[9] << 8 ) | frame[10];
		User2	= ( frame[11] << 8 ) | frame[12];
		User3	= ( frame[13] << 8 ) | frame[14];
		TC1		= ( frame[15] << 8 ) | frame[16];
		TC2		= ( frame[17] << 8 ) | frame[18];
		TC3		= ( frame[19] << 8 ) | frame[20];
		Therm	= ( frame[21] << 8 ) | frame[22];
		RPM		= ( frame[23] << 8 ) | frame[24];

		printf("Tick:  %d\n", Tick);
		printf("WBRaw: %d\n", WBRaw);
		printf("Ipx:   %d\n", Ipx);
		printf("User1: %d\n", User1);
		printf("User2: %d\n", User2);
		printf("User3: %d\n", User3);
		printf("TC1:   %d\n", TC1);
		printf("TC2:   %d\n", TC2);
		printf("TC3:   %d\n", TC3);
		printf("Therm: %d\n", Therm);
		printf("RPM:   %d\n", RPM);
	}

	void TEWBClient::DumpRawFrame() {
		unsigned char *frame = this->GetFrame();

		//packet descriptions
		char pktDesc[FRAMESIZE][10] = {
			"Header 1",
			"Header 2",
			"Sequence",
			"Tick Hi",
			"Tick Lo",
			"WB Hi",
			"WB Lo",
			"Ipx Hi",
			"Ipx Lo",
			"U1 Hi",
			"U1 Lo",
			"U2 Hi",
			"U2 Lo",
			"U3 Hi",
			"U3 Lo",
			"T1 Hi",
			"T1 Lo",
			"T2 Hi",
			"T2 Lo",
			"T3 Hi",
			"T3 Lo",
			"Thrm Hi",
			"Thrm Lo",
			"RPM Hi",
			"RPM Lo",
			"State 1",
			"State 2",
			"CRC"
		};

		int current = 0;
		for ( current = 0; current < FRAMESIZE; current++ ) {
			printf("%10s = %u\n", pktDesc[current], frame[current]);
		}
	}
}
