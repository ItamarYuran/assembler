#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "data.h"


DataImage *data_image = NULL;



DataImage* addToDataImage(int address, char * machine_code, int is_data, int dc,int ic)
{
    if (data_image == NULL)
    {
        DataImage* list = (DataImage*)malloc(sizeof(DataImage));
        if (list == NULL)
        {
            printf("new data allocation went wrong\n");
            return NULL;
        }
        list->next = (DataImage*)malloc(sizeof(DataImage));
        list->address = address;
        strcpy(list->machine_code, machine_code);
        list->is_data = is_data;
        list->dc = dc;
        list->ic = ic;
        data_image = list;
    }
    else 
    {
        DataImage * temp = data_image;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = (DataImage*)malloc(sizeof(DataImage));
        temp->address = address;
        strcpy(temp->machine_code, machine_code);
        temp->is_data = is_data;
        temp->dc = dc;
        temp->ic = ic;
    }
    return data_image;
}

void printDataImage()
{
	DataImage *temp = data_image;
	while (temp->next != NULL) {
		printf("address: %d  is data: %d  dc: %d  ic: %3d  machine code: %s\n",temp->address,temp->is_data,temp->dc,temp->ic,
			temp->machine_code);	
		temp = temp->next;
	}
		
}

void freeDataImage()
{
	DataImage *temp;
	while (data_image != NULL) {
		temp = data_image;
		data_image = data_image->next;
		free(temp);
	}
}



char * intToBin(int i, int size)
{
char *code = (char*)malloc(size);
int n, c, k;
n = i;

  for (c = size; c >= 0; c--)
  {
    k = n >> c;
    if (k & 1)
      strcat(code, "1");
    else
      strcat(code ,"0");
  }
    code++;
  return code;
}

void updateData(char * code, int ic)
{
DataImage * temp;
temp = data_image;
while (temp != NULL)
{
	if (temp->address == ic)
	{
	strcpy(temp->machine_code, code);
	}
temp = temp->next;
}
return;
}

void updateaddress(int icf)
{
DataImage * temp = data_image;
while (temp != NULL)
{
if (temp->is_data == 1)
{
	temp->address += icf;
}
temp = temp->next;
}
}




