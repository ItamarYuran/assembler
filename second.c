#include "data.h"

int secondPass(char * file)
{
	char line[MAX];
	FILE * file_ptr;
	IC = 100;
	file_ptr = fopen(file, "r");
	if (!file_ptr)
		{printf("ERROR: file %s can't open", file);}
	 while (1)
	    {
	
	        if (fgets(line, MAX, file_ptr) == NULL)	
        		{break;}
        	
        	strcpy(line,skipspace(line));
        	
        	if (ignoreLine(line) == 1)
        	    {continue;}
        
       	else 
        	{handleLineTwo(line);}
     	   }

return 0;
}

int handleLineTwo(char * line)
{
char * lable;
char * command;
if (isLableDef(line) == 1)
        {

            strcpy(line ,skipword(line));
            strcpy(line, skipspace(line));
        }
if (isData(line) > 0)
	{return 0;}
	
if (entryOrExtern(line) == 1)
	{return 0;}
	
if (entryOrExtern(line) == 2)
	{
	line = skipword(line);
	line = skipspace(line);
	lable = getword(line);
	strcat(findSymbol(lable)->attributes, " .entry");
	return 1;
	}
	
command = getword(line);
line = line+strlen(command);
line = skipspace(line);
if (parNum(command) == 2)
	{
	IC += 2;
	twoPar(line);
	return 1;
	}
if (parNum(command) == 1)
	{
	IC += 2;
	onePar(line);
	return 1;
	}
return 0;
}

int parNum(char * command)
{
if (strcmp(command,"mov")==0) {return 2;}
if (strcmp(command,"cmp")==0) {return 2;}
if (strcmp(command,"add")==0) {return 2;}
if (strcmp(command,"sub")==0) {return 2;}
if (strcmp(command,"lea")==0) {return 2;}

if (strcmp(command,"clr")==0) {return 1;}
if (strcmp(command,"not")==0) {return 1;}
if (strcmp(command,"inc")==0) {return 1;}
if (strcmp(command,"dec")==0) {return 1;}
if (strcmp(command,"jmp")==0) {return 1;}
if (strcmp(command,"bne")==0) {return 1;}
if (strcmp(command,"jsr")==0) {return 1;}
if (strcmp(command,"red")==0) {return 1;}
if (strcmp(command,"prn")==0) {return 1;}

return 0;
}



void onePar(char * line)
{
char * par;
int a;
par = (char*)malloc(sizeof(int)*MAX);
par = getword(line);
a = promote(par);
if(a == 3)
	{
		updateDataImage(getlable(par), IC);
		IC += 2;	
	}
	else 
	{
	if(a == 2)
	{
		updateDataImage(par, IC);
		IC += a;
	}
	else 
	{
	IC += a;
	}
	}
}

void twoPar(char * line)
{
	char * par_one;
	char * par_two;
	char * temp;
	int a = 0;
	par_one = malloc(sizeof(char)*MAX);
	par_two = malloc(sizeof(char)*MAX);
	temp= malloc(sizeof(char)*MAX);
	par_one = getword(line);
	a = promote(par_one);
	if(a == 3)
	{
	strcpy(temp,getlable(par_one));
		updateDataImage(getlable(par_one), IC);
		IC += 2;
			            
	}
	else	
	{
	if(a == 2)
	{
		updateDataImage(par_one, IC);

		IC += a;
	}
	else	
		{IC += a;}
	
	
	line = line + strlen(par_one);
	line = skipspace(line);
	if(*line != ',')	
		{return;}
	line++;
	par_two = getword(line);
	a = promote(par_two);
	if(a == 3)
	{
		updateDataImage(getlable(par_two), IC);
		IC += 2;
	}
	else 
	{
		if(a == 2)
		{
		updateDataImage(par_two, IC);
		IC += a;
		}
	else	
		{IC += a;}
	}

}
}


int promote(char * par)
{
	char * is_par_direct;
	is_par_direct = isDirect(par);
	if(isReg(par) != -1)
		{return 0;}
	if(isdigit(*is_par_direct)|| *is_par_direct == '-')
		{return 1;}
	if(isIdx(par) != -1)
		{return 3;}
	return 2;
}


char * getlable(char * line)
{
int i;
char * code = malloc(sizeof(int)*MAX);
i = 0;

while (*line != '[')
	{
	*(code++) = *(line++);
	i++;
	}
return code-i;
}


void updateDataImage(char * sym,int ic)
{
	
	char * code;
	symbols * temp;
	code = malloc(sizeof(char)*MAX);
	temp = findSymbol(sym);
	if(entryOrExtern(temp->attributes)== 1)
	{
		strcpy(code,intToBin(1,4));
		strcat(code, intToBin(0,16));
		updateData(code,ic);
		strcpy(code,"");
		strcpy(code,intToBin(1,4));
		strcat(code, intToBin(0,16));
		updateData(code,ic+1);
		updateSymbol(sym,ic);
		return;
	}

	strcpy(code,intToBin(2,4));
	strcat(code, intToBin(temp->base,16));
	updateData(code,ic);
	strcpy(code,"");
	strcpy(code,intToBin(1,4));
	strcat(code, intToBin(temp->offset,16));
	updateData(code,ic+1);

return;}




























