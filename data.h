#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


#define MAX 80
#define OFF 0
#define ON 1


/*structs*/
typedef struct symbols {  
	struct symbols *next;
	char name[MAX];
	char attributes[MAX];
	int value;
    int base;
    int offset;
}symbols;

typedef struct DataImage {
	struct DataImage *next;
	int address;
	char machine_code[20];
	int is_data;
	int dc;
	int ic;
}DataImage;

typedef struct actions{
	char *word;
	int op_code;
	int func_code;
	int args;
}actions;


/*macro spreading*/
void spread(char * file);
void replace(char * file, char *old, char *newW);

/*symbol table*/
symbols * findSymbol(char * symbol);
symbols* addSymbol(char * name, char *attributes, int value, int base, int offset);
symbols* searchSymbol(char* name);
void printSymbols();
void freeSymbols();
void updateSymbol(char * sym, int ic);

/*data image*/
DataImage* addToDataImage(int address, char machine_code[], int is_data, int dc,int ic);
void printDataImage();
void freeDataImage();
void updateData(char * code, int ic);
void updateaddress(int icf);

/*first pass*/
char * intToBin(int i,int size);
char * getword(char * line);
char * skipspace(char *line);
char * skipword(char * line);
int firstPass(char * file);
int handleLine(char * line);
int isLableDef(char * word);
int ignoreLine(char * line);
int isData(char * line);
int isEntry(char * line);
int entryOrExtern(char * line);
int handleAction(char *line, char * action);
void handleData(char * line);
void handleAscii(char * line);
void processAction(char *line, actions command);
void two(actions command, char *line);
void one(actions command, char *line);
void zero(actions command);
int isIdx(char * word);
char * firstField(int val);
char * secField (int com_num, int reg_one, char * direct_one, int reg_two, char * direct_two, int param_num, int idx_one, int idx_two);
char * isDirect (char * line);
int isReg(char * line);


/*second pass*/
int secondPass(char * file);
int handleLineTwo(char * line);
int parNum(char * command);
void onePar(char * line);
void twoPar(char * line);
int promote(char * line);
char * getlable(char * line);
void updateDataImage(char * sym,int ic);


/*outputs*/
void buildOutPuts(char * filename);
void buildOB(char * filename); 
void buildENT(char * filename);
void buildEXT(char * filename);

/*Global variables*/
int IC, DC, ICF, DCF;


extern symbols *symbol_table;
extern DataImage *data_image;
extern actions actions_struct[16];




