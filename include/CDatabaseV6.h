#ifndef CDATABASEV6_H
#define CDATABASEV6_H

#include <vector>
#include <map>
#include <NStringTool.h>

class CDatabaseV6
{
	public:

		bool Read(const char* Filename);
		bool Get(const std::string Key, std::string* Value);

  	std::vector<stringvector>          mRecords;
  	std::map<std::string, std::string> mKeyMap;
};

#endif
