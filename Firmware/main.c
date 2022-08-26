#include <REGX52.H>
#include "send.h"


void main ()
{ 
	char a[]={"HelloRobocon"};
	
	while(1)
	{
			SendString(&a);
	}
}

