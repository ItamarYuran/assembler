#include "data.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
int cur;
char * name = malloc(sizeof(char)*20);

for ( cur = 1; cur < argc; cur++)
{

	strcpy(name, argv[cur]);
	strcat(name,".am");
	spread(argv[cur]);
 	firstPass(name);  
   	printSymbols();
	secondPass(name); 
  	buildOutPuts(argv[cur]);
  	printDataImage();
   	printSymbols();
   	freeDataImage(); 
   	freeSymbols();  
}
   return 1;
}


