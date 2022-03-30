#include "data.h"

void spread(char * file)
{
char *line, *macro , *macroname, *token;
char  name[MAX];
FILE * fpf;
FILE * fp = fopen(file,"r");
strcpy(name, file);
strcat(name,".temp");
fpf = fopen(name,"w+");
line = malloc(sizeof(int)*MAX);
macro = malloc(sizeof(int)*MAX);
	
	while (fgets(line,MAX,fp)!= NULL)
	{
		token = getword(line);
		if (strcmp(token,"macro")==0)
		{
			while (strcmp(token,"endm")!=0)
			{
			fgets(line,MAX,fp);
			token = getword(line);
			}
			fgets(line,MAX,fp);
		}
		fputs(line,fpf);
	}
	
	rewind(fp);
	rewind(fpf);
	
	
while (fgets(line,MAX,fp)!= NULL)
	{
		token = getword(line);
		if (strcmp(token,"macro")==0)
		{
		line = line+strlen(token);
		line = skipspace(line);
		macroname = getword(line);
		fgets(line,MAX,fp);
		macro = malloc(sizeof(int)*MAX);
		strcpy(macro, "");
		while (strstr(line,"endm") == NULL)
			{
			strcat(macro,line);
			fgets(line,MAX,fp);
			}
		replace(file,macroname, macro);
		}	
		}
	remove(name);
}
	
	
	
void replace(char * file, char *old, char *new)
{
	char name[MAX],name1[MAX];
	FILE * fp;
	FILE * fpf;
	char *pos, *line, *temp;
	int index = 0;
	int olen;
	strcpy(name,file);
	strcpy(name1,file);
	strcat(name, ".am");
	strcat(name1,".temp");
	temp = malloc(sizeof(int)*MAX);
	line = malloc(sizeof(int)*MAX);
    	olen = strlen(old);
    	fp = fopen(name1,"r+");
    	fpf = fopen(name,"w+");
    	while (fgets(line,MAX,fp)!= NULL)
    		{
    		while ((pos = strstr(line, old)) != NULL)
    			{
        		strcpy(temp, line);
        		index = pos - line;
        		line[index] = '\0';
        		strcat(line, new);
        		strcat(line, temp + index + olen);

    			}
   		fputs(line,fpf);
    		}
	fclose(fp);
	fclose(fpf);
  }
  

