#include "data.h"
#include <math.h>

struct actions actions_struct[16] = {
{"mov",0,0,2},{"cmp",1,0,2},{"add",2,10,2},{"sub",2,11,2}, {"lea",4,0,2},
{"clr",5,10,1},{"not",5,11,1}, {"inc",5,12,1},{"dec",5,13,1},{"jmp",9,10,1},{"bne",9,11,1},{"jsr",9,12,1},
{"red",12,0,1},{"prn",13,0,1},{"rts",14,0,0}, {"stop",15,0,0}
};


int firstPass(char * file)
{
	char *line;
	FILE * file_ptr;
	IC = 100;
	DC = 0;

	file_ptr = fopen(file, "r");
	if (!file_ptr)
		printf("ERROR: file %s can't open", file);
	    while (1)
	    {
	    line = (char*)malloc(sizeof(char)*MAX);
	        if (fgets(line, MAX, file_ptr) == NULL)
	        	{break;}
        	
	        line = skipspace(line);
	        if (ignoreLine(line) == 1)
	            {continue;}
        
	        else 
	        {handleLine(line);}
	        free(line);
	     }
	ICF = IC;
	DCF = DC;
	updateaddress(ICF);
	return 0;
}



int handleLine(char * line)
{

	char *l;
	int lableDef = OFF;
	char * action;
	char *lable = malloc(sizeof(int)*MAX);
	l = (char*)malloc(sizeof(int)*MAX);
	strcpy(l, line);
	
	if (isLableDef(line) == 1)
	        {
	        strcpy(lable, getword(l));
	     	l= l+strlen(lable);
	     	l++;
	        l = skipspace(l);
	            
	            lableDef = ON;
	         }
	           if (isData(l) > 0)
	        {
	               if (lableDef)
	        		{
	            		addSymbol(lable, "data", IC, IC - (IC%16), IC%16);
	           		free(lable);
            			}

            		if (isData(l) == 1)
            			{
            			l = skipword(l);            
            			handleData(l);
            			 return 1;
            			}
            		if (isData(l) == 2)
            			{
             			handleAscii(skipword(l));
             			return 1;
            			}
        	   }
       	 if (entryOrExtern(l) > 0)
        	 {
            		if (entryOrExtern(l) >1)
               	 	{return 1;}
            		strcpy(l ,skipword(l));
            		strcpy(lable, getword(l));
           		addSymbol(lable, ".extern", 0, 0, 0);
            		return 1;
        	 }
       	 if (lableDef == ON) 
       	 {addSymbol(lable, "code", IC, IC - (IC%16), IC % 16);}
       	 action = getword(l);
       	 strcpy(l, skipword(l));
       	 handleAction(l, action);
		
return 1;
}

int handleAction(char *line, char * action)
{

	int i;
	for (i = 0; i < 16; i++) 
	{
		if (strcmp(actions_struct[i].word, action) == 0) 
		{
			 processAction(line, actions_struct[i]);
		}
	}
return 1;
}


void processAction(char *line, actions command) {
	
	switch (command.args) {
	
	case 2:
		two(command, line);
		break;
	case 1:
		one(command, line);
		break;
	case 0:
		zero(command);
		break;
	default:
		break;
	}
}



char * getword(char * line)
{
    int i =0;
    char * word;
    line = skipspace(line);
    word = (char*)malloc(sizeof(MAX));
    while (line != NULL && isspace(*line)==0 && *line != '\0' && *line != '\n'&& *line!= ',')
    {
        word[i++] = *line;
        line++;
    }
    if (word[i-1] == ','|| word[i-1] == ':')
    	{
    	word[i-1] = '\0';
    	return word;
    	}
    word[i] = '\0';
    return word;
}

int isLableDef(char * word)
{
    strcpy(word , skipspace(word));
    while (!(isspace(*word)))
    {
        if (*word == ':')
            {return 1;}
        word++;
    }
    return 0;
}

int ignoreLine(char * line)
{
	if (*line == ';')
		{return 1;}
   	 while (*line != '\0' && *line != '\n')
   		 {
   		 if (*line != ';' || *line != ' ' || *line != '\t')
      			  {return 0;}
   		 line++;
   		 } 
    	return 1;
}

int isData(char * line)
{

    line =skipspace(line);
    if (strncmp(line, ".data",5) == 0)
    	{return 1;}
    if (strncmp(line, ".string",7) == 0)
  	  {
           return 2;
    	  }
    return 0;
}

/*handelind lines in the form of - .data -5,5*/
void handleData (char * line)
{
	int temp;
	char * num;
	char * code;
	int l = 0;
	while(*line)
	{
		num = getword(line);
		temp = atoi(num);
		line = line + strlen(num);
		while ((isspace(*line) && *line!= '\0') || *line == ',')
		{line++;}
		if(!(*line))	
			{break;}
		if(*line == ',')	
			{line ++;}
		code = firstField(temp);
		addToDataImage(DC+l,code,1,DC,0);
		l++;
	}
	code = firstField(temp);
	addToDataImage(DC+l,code,1,DC,0);
	DC = DC + l +1;

}
/*handelind lines taht contains strins. had a lot of problems with that function
when i wanted to submitt the task. tried everything */
void handleAscii(char *line)
 {
 	int l;
	char *temp;
	char value;
	l = 0;
	line++;
	while (*line != '"') {
		if (*line == '\0') {
		break;
	printf("ERROR: illigel ascii");
		}
		if (*line == '\"') 
		{break;}
		value = *line;
		temp = firstField(value);
		data_image = addToDataImage(DC+l,temp ,1, DC, 0);
		l++;
		line++;
	}
	temp = firstField(0);
	data_image = addToDataImage(DC+l,temp ,1, DC, 0);
	DC = DC + l + 1;
}


int entryOrExtern(char * line)
{
	strcpy(line,skipspace(line));
	if (strncmp(line,"code",4) == 0 || strncmp(line,"data",4) == 0)
	{
	line = line + 4;
	line = skipspace(line);
	}
		if (strncmp(line,".extern",7) == 0)
		{return 1;}
		
		if (strncmp(line,".entry",6) == 0)
		{return 2;}
	return 0;
}

char * skipword(char * line)
{
    line = skipspace(line);
    while (!(isspace(*line))) {line++;}
    line = skipspace(line);
    return line;
}

char * skipspace(char *line) 
{
	if (line == NULL)
	 {return NULL;}
	 
	while (isspace(*line) != 0 && *line != '\n' && *line != '\0')
	 {line++;}
	return line;
}

/*function to handle two parrameters actions*/
void two(actions  command, char *line)
{

	char * first_par, *sec_par, *one_dir ,*two_dir;
	char * first,*sec;
	int idx_one,idx_two, one_direction, two_direction,l,cnt;
	int one_reg,two_reg;
	one_reg = two_reg = -1;
	idx_one = idx_two = 0;
	l = cnt = 2;
	first_par = getword(line);
	line = line+strlen(first_par);
	line = skipspace(line);
	
	/*first parameter is register*/
	if((one_reg = isReg(first_par)) != -1){;}
	
		else
		{

			one_dir = isDirect(first_par);
			if(*one_dir) 
			{/*first parameter is value*/
				one_reg = -1;
				one_direction = atoi(one_dir);
				l = l+1;
			}	
			else	
			{
				l = l+2;
				one_reg = isIdx(first_par);
				if(one_reg != -1)
				{idx_one = 1;}
				else 
				{idx_one = 0;}
			}
		}
	if(*line == ',')
	{line++;}
	
	line = skipspace(line);
	sec_par = getword(line);
	line = line + strlen(sec_par);
	if((two_reg = isReg(sec_par)) != -1) {}/*second parameter is a register*/
	else 
	{	
			two_dir = isDirect(sec_par);
			if(*two_dir)
			{
				two_reg = -1;
				two_direction = atoi(two_dir);
				l = l+1;
			}
			/*second parameter is a value*/
			else
			{
				l = l+2;
				two_reg = isIdx(sec_par);	
				if(two_reg != -1)
					{idx_two = 1;} /*second parameter is a index*/
				else 
				{idx_two = 0;}/*second parameter is a label*/
			}
	}
	line = skipspace(line);
	
	first = firstField(pow(2.0,(double)command.op_code));
	sec = secField(command.func_code,one_reg,one_dir,two_reg,two_dir,2,idx_one,idx_two);
	addToDataImage(IC,first,0,0,IC);
	addToDataImage(IC+1,sec,0,0,IC);
	
	if(one_reg == -1 && !isdigit(*one_dir) && *one_dir != '-')/* first parameter one is a lable*/
	{
		addToDataImage(IC+2, "?", 0, 0,IC);
		addToDataImage(IC+3,"?", 0, 0,IC);
		cnt = 4;
	}
	if(isdigit(1))/*first parameter is a value*/
	{
		addToDataImage(IC+2,firstField(one_direction),0,0,IC);
		cnt = 3;
	}
	
	if(idx_one == 1)
	{
		addToDataImage(IC+2,"?",0,0,IC);
		addToDataImage(IC+3,"?",0,0,IC);
	}

	if(two_reg == -1 && !isdigit(*two_dir) && *two_dir != '-') /*second parameter is a lable*/
	{
		addToDataImage(IC+cnt,"?",0,0,IC);
		addToDataImage(IC+cnt+1,"?",0,0,IC);
	}
	if(isdigit(*two_dir)|| *two_dir == '-') /*second parameter is a value*/
	{
		addToDataImage(IC+cnt,firstField(two_direction),0,0,IC);
	}
	if(idx_two == 1)
	{
		addToDataImage(IC+cnt,"?",0,0,IC);
		addToDataImage(IC+cnt+1,"?",0,0,IC);
	}
	IC = IC+l;

}



char * firstField(int val)
{
	char * code = intToBin(4,4);
	strcat(code,intToBin(val,16));
	return code;
}
char * secField (int func_code, int reg_one, char * direct_one, int reg_two, char * direct_two, int param_num, int idx_one, int idx_two)
{

	char * code = malloc(sizeof(int)*20);
	strcat(code,intToBin(4,4));
	strcat(code,intToBin(func_code,4));
	if(reg_one != -1 || idx_one != 0)
	{
		strcat(code, intToBin(reg_one,4));
		if(idx_one == 1)
			{strcat(code,intToBin(2,2));} 
		else	
			{strcat(code,intToBin(3,2));}
	}
	else
	{
		if(isdigit(*direct_one) || *direct_one == '-')
			{strcat(code,intToBin(0,6));}
		else
		{
			if(param_num > 1)	
				{strcat(code,intToBin(1,6));}
			else	
				{strcat(code,intToBin(0,6));}
		}
	}
	if(reg_two != -1 || idx_two != 0) 
	{
		strcat(code, intToBin(abs(reg_two),4));
		if(idx_two == 1)
			{strcat(code,intToBin(2,2));}
		else 	
			{strcat(code,intToBin(3,2));}}
	else 
	{
		if(isdigit(*direct_two)|| *direct_two == '-')
			{strcat(code,intToBin(0,6));}
		else	
		{
			if(param_num > 0)	
				{strcat(code,intToBin(1,6));}
			else	
				{strcat(code,intToBin(1,6));}
		}
	}

	return code;
}

int isIdx(char * line)
{
	int a = 0;
	while(*line!='\0')
	{
		if(*line == '[')
		{
			line++;
			if((*line == 'r') && isdigit(*++line))
			{
	    			while (*line != ']') 
	    			{
	     				a = a*10;
					a += (*line++) - '0';
				}
				if(a > 15)
				{printf("ERROR: unknown register.\n");}
				return a;
			}	
		}
		line++;
	}
	return -1;
}

char * isDirect (char * line)
{
	char * code = malloc(sizeof(int) * 20);
	int val = 0;
	int neg = 1;
	if(*line++ == '#')
	{
		if(*line == '-'){neg = -1; line++;}
    		while (*line) 
    		{
   			if (!(isdigit(*line)))	{return "\0";} 
     			val = val*10; 
			val += (*line++) - '0';
		}
		sprintf(code,"%d",val*neg);
		return code;
	}
	return "\0";
}
int isReg(char * line)
{

	int reg = 0;
	if((*line == 'r') && isdigit(*++line))
	{
    		while (*line) 
    		{
   			if (!(isdigit(*line)))	{return -1;} 
     			reg = reg*10; 
			reg += (*line++) - '0';
		}
		if(reg > 15) {printf("ERROR: not a valid register\n");	}
		return reg;
	}
	return -1;
}

/*function to handle lines with action that demand one parammeter*/
void one(actions command, char * line)
{
	char * sec_par, *first, *sec, * two_dir;
	int l = 2;
	int two_reg = 0;
	int two_direction = 0;
	int idx_two = 0;
	sec_par = getword(line);
	line = skipword(line);
	line = skipspace(line);
	if((two_reg = isReg(sec_par)) != -1) {}/* second parameter is a register*/
	
	else
	{
		two_dir = isDirect(sec_par);

		if(isdigit(*two_dir)) /*second parameter isa value*/
		{
			two_direction = atoi(two_dir);
			two_reg = -1;
		}	
		else /* second parameter is a lable*/
		{
			two_reg = isIdx(sec_par);
			if(two_reg != -1)
			{
				idx_two = 1;
			}
			else 
			{
				idx_two = 0;
			}
		}
	}
	first = firstField(pow(2.0,(double)command.op_code));
	sec = secField(command.func_code,-1,"\0",two_reg,two_dir,1, 0, idx_two);
	addToDataImage(IC,first,0,0,IC);
	addToDataImage(IC+1,sec,0,0,IC);

	if(two_reg == -1 && !isdigit(*two_dir)) 
	{

		addToDataImage(IC+2,"?",0,0,IC);
		addToDataImage(IC+3,"?",0,0,IC);
		l = l + 2;
	}


	if((isdigit(two_direction))) 
	{
		addToDataImage(IC+2,firstField(two_direction),0,0,IC);
		l = l + 1;
	}

	if(idx_two == 1)
	{

		addToDataImage(IC+2,"?",0,0,IC);
		addToDataImage(IC+3,"?",0,0,IC);
		l = l + 2;
	}
	
	two_direction++;
	IC = IC+l;
}

void zero(actions command)
{
char * code;
code = firstField(pow(2.0,(double)command.op_code));
addToDataImage(IC,code,0,0,IC);
IC++;
}

