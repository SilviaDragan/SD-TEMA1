#include "structures.h"
/*DRAGAN Silvia - 311CB*/


//functie ce gaseste un tabel dupa numele dat
t_table *FindTable(t_db DB, char *Table_name)
{
	t_table *p=NULL;
	for(p=DB.tables; p!=NULL; p=p->next)
	{
		if(strncmp(p->name, Table_name, strlen(Table_name))==0)
			return p;
	}
	return NULL;
}

int main()
{
	//aloc spatiu si initializez comanda, numele bazei de date si al tabelului
	char *command=(char *)malloc(MAX_CMD_LEN*sizeof(char));
	if(!command) { printf("EROARE LA ALOCARE\n");exit(-1);}
	memset(command, 0, MAX_CMD_LEN);

	char *DB_name=(char *)malloc(MAX_DB_NAME_LEN*sizeof(char));
	if(!DB_name){ printf("EROARE LA ALOCARE\n");exit(-1);}
	memset(DB_name, 0, MAX_DB_NAME_LEN);

	char *Table_name=(char *)malloc(MAX_TABLE_NAME_LEN*sizeof(char));
	if(!Table_name){ printf("EROARE LA ALOCARE\n");exit(-1);}
	memset(Table_name, 0, MAX_TABLE_NAME_LEN);

	t_db DB;
	//initializez pointeri la lista de tabele 
	//si ultimul/penultimul tabel din lista
	t_table *LT=NULL, *ultimLT=NULL, *p=NULL;
	for(;;)
	{
		//citesc o comanda
		scanf("%s", command);
		if(strncmp(command, "DELETE_DB", strlen("DELETE_DB"))==0)
		{
			DeleteDB(&DB);
			break;
		}
		else if(strncmp(command, "INIT_DB", strlen("INIT_DB"))==0)
		{
			//obtin numele DB din comanda
			scanf("%s", DB_name);
			DB=InitDB(DB_name);
			DB.tables=NULL;
		}
		else if(strncmp(command, "CREATE", strlen("CREATE"))==0)
		{
			scanf("%s", Table_name);
			if(FindTable(DB, Table_name)!=NULL)
			{
				printf("Table \"%s\" already exists.\n", Table_name);
			}
			//creez tabelul si il adaug in lista de tabele corespunzatoare bazei de date
			else
			{
				t_table *aux=CreateTable(Table_name);
				if(LT==NULL) LT=aux;
				else {ultimLT->next=aux; }
				ultimLT=aux;
				DB.tables=LT;
			}
		}
		else if(strncmp(command, "PRINT_DB", strlen("PRINT_DB"))==0)
		{
			PrintDB(DB);
		}
		else if(strncmp(command, "PRINT", strlen("PRINT"))==0)
		{
			scanf("%s", Table_name);
			t_table *t=FindTable(DB, Table_name);
			if(t==NULL)
			{
				printf("Table \"%s\" not found in database.\n", Table_name);
			}
			else PrintTable(t);
		}
		else if(strncmp(command, "DELETE", strlen("DELETE"))==0)
		{	
			char line[MAX_CMD_LEN];
			memset(line, 0, MAX_CMD_LEN);
			fgets(line, MAX_CMD_LEN, stdin);
			line[strlen(line)-1]='\0';
			char line_c[MAX_CMD_LEN];
			memset(line_c, 0, MAX_CMD_LEN);
			strncpy(line_c, line, strlen(line));
			char *token=strtok(line, " ");
			memset(Table_name, 0, MAX_TABLE_NAME_LEN);
			strncpy(Table_name, token, strlen(token));
			t_table *t=FindTable(DB, Table_name);
			//sunt in cazul de a sterge un tabel
			if(line_c[strlen(Table_name)+1]=='\0')
			{
				if(t==NULL)
				{
					printf("Table \"%s\" not found in database.\n", Table_name);
				}
				else 
				{
					DeleteTable(&LT, Table_name);
					DB.tables=LT;
					//daca nu am eliminat ultimul tabel
					if(LT)
					{
						for(p=LT; (p->next)!=NULL; p=p->next);
						ultimLT=p;
					}
					else
						ultimLT=NULL;
				}
			}
			//sunt in cazul de a sterge o linie
			else
			{
				for(int i=0; i<strlen(line_c); i++)
				{
					line_c[i]=line_c[i+strlen(Table_name)+2];	
				}
				line_c[strlen(line_c)]='\0';
				char *token1=strtok(line_c, " ");
				char *column_name=(char *)
					malloc(MAX_COLUMN_NAME_LEN*sizeof(char));
				memset(column_name, 0 ,MAX_COLUMN_NAME_LEN);
				char *relatie=(char *)malloc(5*sizeof(char));
				memset(relatie, 0, 5);
				char *val=(char *)malloc(MAX_COLUMN_NAME_LEN*sizeof(char));
				memset(val, 0, MAX_COLUMN_NAME_LEN);
				int i=3;
				//obtin instructiunile date
				while(token1 && i)
				{
					token1[strlen(token1)]='\0';
					if(i==3) strncpy(column_name, token1, strlen(token1));
					else if(i==2) strncpy(relatie, token1, strlen(token1));
					else if(i==1) strncpy(val, token1, strlen(token1));
					i--;
					token1=strtok(NULL, " ");					
				}
				if(t==NULL)
				{
					printf("Table \"%s\" not found in database.\n", Table_name);
				}
				else Delete(t, column_name, relatie, val);
				free(column_name);
				free(relatie);
				free(val);
			}

		}
		else if(strncmp(command, "ADD", strlen("ADD"))==0)
		{
			scanf("%s", Table_name);
			t_table *t=FindTable(DB, Table_name);
			if(!t)
			{
				printf("Table \"%s\" not found in database.\n", Table_name);
				char line[MAX_CMD_LEN];
				fgets(line, MAX_CMD_LEN, stdin);
			}
			else AddLine(t);
		}
		else if(strncmp(command, "SEARCH", strlen("SEARCH"))==0)
		{
			char line[MAX_CMD_LEN];
			memset(line, 0, MAX_CMD_LEN);
			fgets(line, MAX_CMD_LEN, stdin);
			line[strlen(line)-1]='\0';
			char line_c[MAX_CMD_LEN];
			memset(line_c,0, MAX_CMD_LEN);
			strncpy(line_c, line, strlen(line));
			char *Table_name=strtok(line, " ");
			for(int i=0; i<strlen(line_c); i++)
			{
				line_c[i]=line_c[i+strlen(Table_name)+2];	
			}
			line_c[strlen(line_c)+1]='\0';
		
			t_table *t=FindTable(DB, Table_name);
			if(!t)
			{
				printf("Table \"%s\" not found in database.\n", Table_name);
			}
			else
			{
				char *token1=strtok(line_c, " ");
				char *column_name=(char *)
					malloc(MAX_COLUMN_NAME_LEN*sizeof(char));
				memset(column_name, 0 ,MAX_COLUMN_NAME_LEN);
				char *relatie=(char *)malloc(5*sizeof(char));
				memset(relatie, 0, 5);
				char *val=(char *)malloc(MAX_COLUMN_NAME_LEN*sizeof(char));
				memset(val, 0, MAX_COLUMN_NAME_LEN);
				int i=3;
				while(token1 && i)
				{
					token1[strlen(token1)]='\0';
					if(i==3) strncpy(column_name, token1, strlen(token1));
					else if(i==2) strncpy(relatie, token1, strlen(token1));
					else if(i==1) strncpy(val, token1, strlen(token1));
					i--;
					token1=strtok(NULL, " ");					
				}
				Search(t, column_name, relatie, val);
				free(column_name);
				free(relatie);
				free(val);
			}
		}
		else if(strncmp(command, "CLEAR", strlen("CLEAR"))==0)
		{
			scanf("%s", Table_name);
			t_table *t=FindTable(DB, Table_name);
			if(!t)
			{
				printf("Table \"%s\" not found in database.\n", Table_name);
			}
			else
				ClearTable(&t);
		}
		else 
		{
			char *line=NULL;
			size_t len=0;
			getline(&line, &len, stdin);
			line[strlen(line)-1]='\0';
			printf("Unknown command:\"%s%s\".\n", command, line);
		}
	}
	free(command);
	free(DB_name);
	free(Table_name);
	return 0;
}