#include "baseProperty.h"
DWORD Property::parseCmdLine( const std::string &cmdLine )
{
	std::vector<std::string> sv;
	for( std::vector<std::string>::const_iterator it = sv.begin();it != sv.end();++it )
	{
		std::vector<std::string> ssv;
		StringTool::split(*it,'=',ssv,2);
		if( ssv.size() == 2 )
		{
			propertyMap[ssv[0]] = ssv[1];
		}
	}
	return propertyMap.size();
}

DWORD Property::parseCmdLine( const char *cmdLine )
{
	std::vector<std::string> sv;
	StringTool::split_while_space( cmdLine,sv );
	for( std::vector<std::string>::const_iterator it = sv.begin();it != sv.end();++it )
	{
		std::vector<std::string> ssv;
		StringTool::split( *it,'=',ssv,2 );
		if( ssv.size() == 2 )
		{
			propertyMap[ssv[0]] = ssv[1];
		}
	}
	return propertyMap.size();
}

