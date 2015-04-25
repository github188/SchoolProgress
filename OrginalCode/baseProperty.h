#ifndef BASE_PROPERTY_H
#define BASE_PROPERTY_H

class Property
{
	public:
		const VarType &get( const std::string &key )
		{
			return propertyMap[key];
		}
		void set( const std::string &key,const VarType &value )
		{
			property[key] = value;
		}
		bool find( const std::string &key )
		{
			PropertyMap_ConstIter it = property.find( key );
			if( it == property.end() )
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		VarType& operator[] ( const std::string &key )
		{
			return property[key];
		}
		void dump( std::ostream &out ) const
		{
			for( PropertyMap_ConstIter it = property.begin();it != property.end();++it )
			{
				out << it->first << " = " << ( const char * )it->second << std::endl;
			}
		}
		DWORD parseCmdLine( const std::string &cmdLine );
		DWORD parseCmdLine( const char *cmdLine );
	private:
		struct keyHash : public std::unary_function<const std::string,size_t>
		{
			size_t operator() ( const std::string &inst ) const
			{
				std::string temp = inst;
				__gnu_cxx::hash<const char*> H;
				return H(StringTool::tolower(s).c_str());
			}
		};
		struct keyEqual : public std::binary_function<const std::string,const std::string>
		{
			bool operator() ( const std::string &s1,const std::string &s2 ) const
			{
				return strcasecmp( s1.c_str(),s2.c_str() ) == 0;
			}
		};
		typedef __gnu_cxx::hash_map<std::string,VarType,keyHash,keyEqual> PropertyMap;
		typedef PropertyMap::iterator PropertyMap_Iter;
		typedef PropertyMap::const_iterator PropertyMap_ConstIter;
		PropertyMap propertyMap;
};

#endif

