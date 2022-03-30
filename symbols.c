#include "data.h"
#include <stdio.h>
#include <stdlib.h>
 

symbols * symbol_table = NULL;

symbols* addSymbol(char * name, char *attributes, int value, int base, int offset)
{
    if (symbol_table == NULL)
    {
        symbols* list = (symbols*)malloc(sizeof(symbols));
        if (list == NULL)
        {
            printf("ERROR: new symbol allocation went wrong\n");
            return NULL;
        }
        list->next = (symbols*)malloc(sizeof(symbols));
        strcpy(list->name, name);
        strcpy(list->attributes, attributes);
        list->value = value;
        list->offset = offset;
        list->base = base;
        symbol_table = list;

    }
    else 
    {
        symbols * temp = symbol_table;
        while (temp->next != NULL)
        {
            temp = temp->next;
            if (strcmp(name,temp->name)==0)
            {printf("\nERROR: symbol exsists already\n");}
        }
        temp->next = (symbols*)malloc(sizeof(symbols));
        strcpy(temp->name, name);
        strcpy(temp->attributes, attributes);
        temp->value = value;
        temp->offset = value % 16;
        temp->base = value - offset;
        
    }

    return symbol_table;
}

symbols* searchSymbol(char* name)
{
    symbols* temp = symbol_table;
    while (strcmp(temp->name, name)!= 0)
    {
        temp = temp->next;
    }
    return temp;
}

void printSymbols()
{
    symbols* temp = symbol_table;
    while (temp->next != NULL)
    {
        printf("symbol: %6s value: %3d base: %5d offset: %5d attributes: %10s\n",temp->name,temp->value,temp->base,temp->offset,temp->attributes);
        temp = temp->next;
    }
}

void freeSymbols() 
{
	symbols *temp = (symbols*)malloc(sizeof(symbols));
	while (symbol_table != NULL) {
		temp = symbol_table;
		symbol_table = symbol_table->next;
		free(temp);
	}
}

symbols * findSymbol(char * symbol)
{
symbols * temp = symbol_table;

while (temp->next != NULL)
	{
	if (strcmp(symbol, temp->name) == 0)
		return temp;
	temp = temp->next;
	}	
	if (strcmp(symbol, temp->name) == 0)
	return temp;
printf("can't find symbol");
return NULL;
}


void updateSymbol(char * sym, int ic)
{
symbols * temp;
temp = symbol_table;
while (temp != NULL)
{
	if (strcmp(temp->name,sym)==0)
	{
	temp->base = ic;
	temp->offset = ic+1;
	}
temp = temp->next;
}
return;
}


