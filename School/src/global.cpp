#include"global.h"
namespace Global
{
	int randBetween(int min,int max)
	{
		int grap = 0;
		if( min == max )
		{
			return min;
		}
		if( min > max )
		{
			grap = min - max;
			return max +  rand() % (grap + 1);
		}
		else
		{
			grap = max - min;
			return min + rand() % (grap + 1);
		}
	}
}
