#ifndef TEWBCLIENT_H_
#define TEWBCLIENT_H_

#include <termios.h>
#include "Common.h"

namespace TEWB {
	
	class TEWBClient {
		private:
			int fd;
			struct termios oldterm;
			
		private:
			unsigned char *GetFrame();
			
		public:
			TEWBClient();
			~TEWBClient();
			
			bool Connect(const char *device);
			
			unsigned int *GetHumanFrame();
			unsigned int *GetTestFrame();
			
			void DumpRawFrame();
			void DumpHumanFrame();
			void DumpStatus();
			unsigned int Debug();
	};
}

#endif /*TEWBCLIENT_H_*/
