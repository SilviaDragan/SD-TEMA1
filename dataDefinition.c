#include "structures.h"
/*DRAGAN Silvia - 311CB*/

//initializez baza de date cu nume dat 
t_db InitDB(char *s)
{
	t_db DB;
	strcpy(DB.name, s);
	DB.tables=NULL;
	return DB;
}

void DeleteDB(t_db *DB)
{
	t_table *p=NULL, *aux_p=NULL;
	for(p=DB->tables; p!=NULL; )
	{
		//eliberare coloane
		t_column *c=NULL, *aux=NULL;
		for(c=p->columns; c!=NULL; )
		{
			aux=c;
			c=c->next;
			free(aux);
		}
		//eliberare linii pe fiecare caz: int, float, string
		if(p->type==INT)
		{
			//eliberez intai celulele liniei
			t_intLine *l=NULL, *aux_l=NULL;
			for(l=p->lines; l!=NULL; )
			{
				t_intCell *c=NULL, *aux=NULL;
				for(c=l->cells; c!=NULL; )
				{
					aux=c;
					c=c->next;
					free(aux);
				}
				aux_l=l;
				l=l->next;
				free(aux_l);
			}
			
		}
		else if(p->type==FLOAT)
		{
			t_floatLine *l=NULL, *aux_l=NULL;
			for(l=p->lines; l!=NULL; )
			{
				t_floatCell *c=NULL, *aux=NULL;
				for(c=l->cells; c!=NULL; )
				{
					aux=c;
					c=c->next;
					free(aux);
				}
				aux_l=l;
				l=l->next;
				free(aux_l);
			}

		}
		else if(p->type==STRING)
		{
			t_stringLine *l=NULL, *aux_l=NULL;
			for(l=p->lines; l!=NULL; )
			{
				t_stringCell *c=NULL, *aux=NULL;
				for(c=l->cells; c!=NULL; )
				{
					aux=c;
					c=c->next;
					free(aux->value);
					free(aux);
				}
				aux_l=l;
				l=l->next;
				free(aux_l);
			}

		}
		aux_p=p;
		p=p->next;
		free(aux_p);
	}
}
//functie de alocare memorie pt coloana
t_column *Aloc_Column(char *name)
{
	t_column *aux=(t_column *)malloc(sizeof(t_column));
	if(!aux) 
	{
		printf("EROARE LA ALOCARE!\n");
		return NULL;
	}
	memset(aux->name, 0, MAX_COLUMN_NAME_LEN);
	strncpy(aux->name, name, strlen(name));
	aux->next=NULL;
	return aux;
}

t_table *CreateTable(char *Table_name)
{
	t_table *T=(t_table *)malloc(sizeof(t_table));
	T->lines=NULL;
	T->columns=NULL;
	T->next=NULL;
	memset(T->name, 0, MAX_TABLE_NAME_LEN);
	strncpy(T->name, Table_name, strlen(Table_name));
	t_cellType type;
	char *str=(char *)malloc(10*sizeof(char));
	scanf("%s", str);
	int ok=1;
	if(strcmp(str, "INT")==0)
	{
		type=INT;
	}
	else if(strcmp(str, "FLOAT")==0)
	{
		type=FLOAT;
	}
	else if(strcmp(str, "STRING")==0)
	{
		type=STRING;
	}
	else {printf("Unknown data type: \"%s\".", str); ok=0;} 
	T->type=type;
	free(str);
	char line[MAX_CMD_LEN];
	memset(line, 0, MAX_CMD_LEN);
	fgets(line, MAX_CMD_LEN, stdin);
	line[strlen(line)-1]='\0';
	if(ok==0) return NULL;

	t_column *c, *ultim=NULL;
	char *token=strtok(line, " ");
	//creez cate o coloana folosind functia anterioara si o leg in lista 
	while(token)
	{
		c=Aloc_Column(token);
		if(ultim==NULL)
		{
			T->columns=c;
			ultim=c;
		}
		else
		{
			ultim->next=c;
			ultim=c;
		}
		token=strtok(NULL, " ");
	}
	return T;

}

void DeleteTable(t_table **LT, char *T_name)
{
	
	t_table *p=NULL, *ant=NULL;
	for(p=*LT; p->next!=NULL; ant=p, p=p->next)
	{
		//am gasit tabelul de eliminat
		if(strcmp(p->name, T_name)==0) break;		
	}		
	if(p==NULL) //nu am gasit tabelul de eliminat
	{
		printf("Table \"%s\" not found in database.\n", T_name );
		return;
	}
	//verific daca tabelul de eliminat este primul
	//rup legaturile catre tabelul de eliminat
	if(ant==NULL) *LT=(*LT)->next;
	else ant->next=p->next;

	
	//eliberez memoria ocupata de informatiile din tabel:

	//eliberez memoria coloanelor:
	t_column *c=NULL, *aux=NULL;
	for(c=p->columns; c!=NULL; )
		{
			aux=c;
			c=c->next;
			free(aux);
		}

	//eliberez celulele corespuzatoare liniilor
	if(p->type==INT)
	{
		t_intLine *l=NULL, *aux_l=NULL;
		for(l=p->lines; l!=NULL; )
		{
			//eliberez intai celulele liniei
			t_intCell *c=NULL, *aux=NULL;
			for(c=l->cells; c!=NULL; )
			{
				aux=c;
				c=c->next;
				free(aux);
			}
			//eliberez linia
			aux_l=l;
			l=l->next;
			free(aux_l);
		}
	}
	else if(p->type==FLOAT)
	{
		t_floatLine *l=NULL, *aux_l=NULL;
		for(l=p->lines; l!=NULL; )
		{
			t_floatCell *c=NULL, *aux=NULL;
			for(c=l->cells; c!=NULL; )
			{
				aux=c;
				c=c->next;
				free(aux);
			}
			aux_l=l;
			l=l->next;
			free(aux_l);
		}
	}
	else if(p->type==STRING)
	{
		t_stringLine *l=NULL, *aux_l=NULL;
		for(l=p->lines; l!=NULL; )
		{
			t_stringCell *c=NULL, *aux=NULL;
			for(c=l->cells; c!=NULL; )
			{
				free(c->value);
				aux=c;
				c=c->next;
				free(aux);
			}
			aux_l=l;
			l=l->next;
			free(aux_l);
		}
	}
	//eliberez tabela
	free(p);
}