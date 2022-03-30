#include "data.h"
#include <stdio.h>




void buildOutPuts(char * filename)
{
	char name1[MAX],name2[MAX],name3[MAX];
	strcpy(name1,filename);
	strcpy(name2,filename);
	strcpy(name3,filename);
	strcat(name1,".ob");
	strcat(name2,".ent");
	strcat(name3,".ext");
	buildOB(name1);
	buildENT(name2);
	buildEXT(name3);
}



void buildOB(char * filename)
{
	char * line;
	char * hex;
	FILE * fp;
	DataImage *temp;
	int data_count;
	int y;
	int instructions_count;
	char * code = malloc(sizeof(int)*20);
	int i, t, hexa_val;
	data_count = instructions_count = 0;
	hexa_val = 0;
	temp = data_image;
	i = 1;
	line = malloc(sizeof(int)*MAX);
	hex = malloc(sizeof(int)*MAX);
	fp = fopen(filename, "w+");
	fputs("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\",fp);
	while (temp->next != NULL)
		{
		line = malloc(sizeof(int)*MAX);
		sprintf(line,"%d ",temp->address);
		temp->is_data == 1 ? data_count++ : instructions_count++;
		code = temp->machine_code;
	
			for (t=0;t<5;t++)
		{
		hexa_val = 0;
			for (i=8 ; i>=1 ; i=i/2)
				{
				y = (*code)-'0';
				hexa_val = hexa_val +(y * i);
				code++;
				}
			sprintf(hex,"%c-%x", 'A'+t ,hexa_val);
			strcat(line,hex);
		}
		strcat(line,"\n");
		fputs(line ,fp);
		temp = temp->next;
		line = " ";
		}
		rewind(fp);
		line = malloc(sizeof(int)*MAX);
	sprintf(line,"instructions: %d data: %d\n", instructions_count,data_count);
	fputs(line,fp);
	fclose(fp);	
	}



void buildENT(char * filename)
{
	char * line;
		FILE * fp;
	symbols *temp;
	temp = symbol_table;
	
	fp = fopen(filename, "w+");
	
	while (temp->next != NULL)
	{
	line = malloc(sizeof(int)*MAX);
	sprintf(line,"\n\n\n");
	if (entryOrExtern(temp->attributes) == 2)
		{
	sprintf(line, "\n%s , %d , %d\n",temp->name,temp->base,temp->offset);
	
	fputs(line,fp);
	line = "";
	}
	temp = temp->next;
	
	}
}


void buildEXT(char * filename)
{
	char * line;
	FILE * fp;
	symbols *temp;
	temp = symbol_table;
	
	fp = fopen(filename, "w+");
	
	while (temp->next != NULL)
	{
		line = malloc(sizeof(int)*MAX);
		sprintf(line,"\n\n\n");
		if (entryOrExtern(temp->attributes) == 1)
		{
			sprintf(line, "\n%s BASE %d \n%s OFFSET %d\n",temp->name,temp->base,temp->name,temp->offset);
			fputs(line,fp);
			line = "";
		}
		temp = temp->next;

	}
}



























