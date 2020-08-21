#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
/*DRAGAN Silvia - 311CB*/


#ifndef __STRUCTURES__
#define __STRUCTURES__

#define MAX_COLUMN_NAME_LEN 30
#define MAX_TABLE_NAME_LEN  30
#define MAX_DB_NAME_LEN     30
#define MAX_CMD_LEN         300

// int
typedef struct intCell {
	int    value;
	struct intCell* next;
} t_intCell;

typedef struct intLine {
	t_intCell*      cells;
	struct intLine* next;
} t_intLine;

// float
typedef struct floatCell {
	float  value;
	struct floatCell* next;
} t_floatCell;

typedef struct floatLine {
	t_floatCell*      cells;
	struct floatLine* next;
} t_floatLine;

// string
typedef struct stringCell {
	char*  value;
	struct stringCell* next;
} t_stringCell;

typedef struct stringLine {
	t_stringCell*       cells;
	struct stringLine* next;
} t_stringLine;

// cell type
typedef enum {
	INT,
	FLOAT,
	STRING
} t_cellType;

// column
typedef struct column {
	char name[MAX_COLUMN_NAME_LEN];
	struct column* next;
} t_column;

// table
typedef struct table {
	char name[MAX_TABLE_NAME_LEN];
	t_cellType    type;
	t_column*     columns;
	void*         lines;  // t_intLine* | t_floatLine* | t_stringLine*
	struct table* next;
} t_table;

// database
typedef struct db {
	char name[MAX_DB_NAME_LEN];
	t_table* tables;
} t_db;



t_db InitDB(char *s);
t_column *Aloc_Column(char *name);
t_table *CreateTable(char *Table_name);
void PrintDB(t_db DB);
void PrintTable(t_table *T);
void DeleteDB(t_db *DB);
void DeleteTable(t_table **LT, char *T_name);
t_intLine *Aloc_intLine();
t_floatLine *Aloc_floatLine();
t_stringLine *Aloc_stringLine();
t_intCell *Aloc_intCell(int x);
t_floatCell *Aloc_floatCell(float x);
t_stringCell *Aloc_stringCell(char* x);
void AddLine(t_table *T);
void CompareINT(t_table *T,char *relatie, int v, int column_no);
void CompareFLOAT(t_table *T, char* relatie, float v, int column_no);
void CompareSTRING(t_table *T, char* relatie, char *v, int column_no);
void Search(t_table *T, char *column, char *relatie, char *v);
void DeleteINT(t_table *T, char* relatie, int v, int column_no);
void DeleteFLOAT(t_table *T, char* relatie, float v, int column_no);
void DeleteSTRING(t_table *T, char* relatie, char *v, int column_no);
void Delete(t_table *T, char *column, char *relatie, char *val);
void ClearTable(t_table **p);
int nrcif(int x);











#endif