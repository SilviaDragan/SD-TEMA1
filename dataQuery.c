#include "structures.h"
/*DRAGAN Silvia - 311CB*/


void PrintDB(t_db DB)
{
	DB.name[strlen(DB.name)]='\0';
	printf("DATABASE: %s\n", DB.name);
	printf("\n");
	t_table *p=NULL;
	for(p=DB.tables; p!=NULL; p=p->next)
	{
		//afisare tabele
		printf("TABLE: %s\n", p->name); 
		//afisare coloane
		t_column *c=NULL;
		int name_length=0, columns_no=0;
		for(c=p->columns; c!=NULL; c=c->next)
		{
			name_length=strlen(c->name);
			c->name[name_length]='\0';
			printf("%s", c->name);
			for(int i=0; i<=(MAX_COLUMN_NAME_LEN-name_length); i++)
				printf(" ");
			columns_no++;
		}
		printf("\n");
		for(int j=0; j<columns_no; j++)
		{
			for(int i=0; i<MAX_COLUMN_NAME_LEN; i++)
			{
				printf("-");
			}
			printf(" ");
		}
		printf("\n");
		
		//afisare linii
		if(p->type==INT)
		{
			t_intLine *l=NULL;
			for(l=p->lines; l!=NULL; l=l->next)
			{
				t_intCell *c=NULL; int nrcif=0;
				for(c=l->cells; c!=NULL; c=c->next)
				{
					printf("%d", c->value);
					nrcif=(int)log10(c->value)+1;
					if(c->value==0) nrcif=1;
					for(int i=0; i<=(MAX_COLUMN_NAME_LEN-
						nrcif); i++)
							printf(" ");
				}
				printf("\n");	
			}
		}
		else if(p->type==FLOAT)
		{
			t_floatLine *l=NULL;
			for(l=p->lines; l!=NULL; l=l->next)
			{
				t_floatCell *c=NULL; int nrcif=0;
				for(c=l->cells; c!=NULL; c=c->next)
				{
					printf("%.6f", c->value);
					nrcif=(int)log10(floor(c->value))+1;
					if(floor(c->value)==0) nrcif=1;
					for(int i=0; i<=(MAX_COLUMN_NAME_LEN-
						nrcif-7); i++)
							printf(" ");
				}	
				printf("\n");	
			}
		}
		else if(p->type==STRING)
		{
			t_stringLine *l=NULL;
			for(l=p->lines; l!=NULL; l=l->next)
			{
				t_stringCell *c=NULL;
				for(c=l->cells; c!=NULL; c=c->next)
				{
					int x=strlen(c->value);
					c->value[x]='\0';
					printf("%s", c->value);
					for(int i=0; i<=(MAX_COLUMN_NAME_LEN-
						strlen((char *)(c->value)) ); i++)
							printf(" ");
				}
				printf("\n");
			}
		}
		printf("\n");
	}
}

void PrintTable( t_table *T)
{
	printf("TABLE: %s\n", T->name); 
	//afisare coloane
	t_column *c=NULL;
	int name_length=0, columns_no=0;
	for(c=T->columns; c!=NULL; c=c->next)
	{
		
		name_length=strlen(c->name);
		c->name[name_length]='\0';
		printf("%s", c->name);
		for(int i=0; i<=(MAX_COLUMN_NAME_LEN-name_length); i++)
			printf(" ");
		columns_no++;
	}
	printf("\n");
	for(int j=0; j<columns_no; j++)
	{
		for(int i=0; i<MAX_COLUMN_NAME_LEN; i++)
		{
			printf("-");
		}
		printf(" ");
	}
	printf("\n");
	
	//afisare linii
	if(T->type==INT)
	{
		t_intLine *l=NULL;
		for(l=T->lines; l!=NULL; l=l->next)
		{
			t_intCell *c=NULL; int nrcif=0;
			for(c=l->cells; c!=NULL; c=c->next)
			{
				printf("%d", c->value);
				nrcif=(int)log10(c->value)+1;
				if(c->value==0) nrcif=1;
				for(int i=0; i<=(MAX_COLUMN_NAME_LEN-nrcif); i++)
						printf(" ");
			}
			printf("\n");
			
		}
	}
	else if(T->type==FLOAT)
	{
		t_floatLine *l=NULL;
		for(l=T->lines; l!=NULL; l=l->next)
		{
			t_floatCell *c=NULL; int nrcif=0;
			for(c=l->cells; c!=NULL; c=c->next)
			{
				printf("%.6f", c->value);
				nrcif=(int)log10(floor(c->value))+1;
				if(floor(c->value)==0) nrcif=1;
				for(int i=0; i<=(MAX_COLUMN_NAME_LEN-nrcif-7); i++)
							printf(" ");
			}
			printf("\n");
		}
	}
	else if(T->type==STRING)
	{
		t_stringLine *l=NULL;
		for(l=T->lines; l!=NULL; l=l->next)
		{
			t_stringCell *c=NULL;
			for(c=l->cells; c!=NULL; c=c->next)
			{
				int x=strlen(c->value);
				c->value[x]='\0';
				printf("%s", c->value);
				for(int i=0; i<=(MAX_COLUMN_NAME_LEN-
				strlen((char *)(c->value)) ); i++)
						printf(" ");
			}
			printf("\n");
		}
	}
	printf("\n");
}
//functie pentru determinarea nr de cifre ale unui numar intreg
int nrc(int x)
{
	int nrc=0;
	if(x==0) return 1;
	while(x)
	{
		nrc++;
		x=x/10;
	}
	return nrc;
}
//functie pentru determinarea nr de cifre ale unui numar real
int fnrcif(float x)
{
	int nrc=0;
	if(x==0) return 1;
	int y=floor(x);
	if(floor(y)==0) return 1;
	while(x)
	{
		nrc++;
		y=y/10;
	}
	return nrc;
}
//functii ce printeaza liniile din tabel ce satisfac relatia dorita
//in functie de tipul lor
void CompareINT(t_table *T, char* relatie, int v, int column_no)
{
	if(strcmp(relatie,"<")==0)
	{
		t_intLine *l=NULL;
		int i=0;
		for(l=T->lines; l!=NULL; l=l->next)
		{
			t_intCell *p=NULL, *pc=NULL;
			//gasesc celula de la coloana columm_no
			for(p=l->cells; p!=NULL&&i!=column_no; i++, p=p->next);
			if(p!=NULL)
			{
				//daca e indeplinita conditia printez linia
				if(p->value<v)
				{
					for(pc=l->cells; pc!=NULL;  pc=pc->next)
					{
						printf("%d", pc->value);
						int nrcif=nrc((int)pc->value);
						for(int j=0; j<=(MAX_COLUMN_NAME_LEN-nrcif); j++)
							printf(" ");
					}
					printf("\n");
				}
			}
			i=0;
		}
	}
	else if(strcmp(relatie,"<=")==0)
	{
		t_intLine *l=NULL;
		int i=0;
		for(l=T->lines; l!=NULL; l=l->next)
		{
			t_intCell *p=NULL, *pc=NULL;
			for(p=((t_intLine *)l)->cells; p!=NULL&&i!=column_no; i++, p=p->next);
			if(p!=NULL)
			{
				if((p->value)<=v)
				{
					for(pc=l->cells; pc!=NULL;  pc=pc->next)
					{
						printf("%d", pc->value);
						int nrcif=nrc((int)pc->value);
						for(int j=0; j<=(MAX_COLUMN_NAME_LEN-nrcif); j++)
							printf(" ");
					}
					printf("\n");
				}
			}
			i=0;
		}
	}
	else if(strcmp(relatie,"==")==0)
	{
		t_intLine *l=NULL;
		int i=0;
		for(l=T->lines; l!=NULL; l=l->next)
		{
			t_intCell *p=NULL, *pc=NULL;
			for(p=((t_intLine *)l)->cells; p!=NULL&&i!=column_no; i++, p=p->next);
			if(p!=NULL)
			{
				if((p->value)==v)
				{
					for(pc=l->cells; pc!=NULL;  pc=pc->next)
					{
						printf("%d", pc->value);
						int nrcif=nrc((int)pc->value);
						for(int j=0; j<=(MAX_COLUMN_NAME_LEN-nrcif); j++)
							printf(" ");
					}
					printf("\n");
				}
			}
			i=0;
		}
	}
	else if(strcmp(relatie,"!=")==0)
	{
		t_intLine *l=NULL;
		int i=0;
		for(l=T->lines; l!=NULL; l=l->next)
		{
			t_intCell *p=NULL, *pc=NULL;
			for(p=((t_intLine *)l)->cells; p!=NULL&&i!=column_no; i++, p=p->next);
			if(p!=NULL)
			{
				if((p->value)!=v)
				{
					for(pc=l->cells; pc!=NULL;  pc=pc->next)
					{
						printf("%d", pc->value);
						int nrcif=nrc((int)pc->value);
						for(int j=0; j<=(MAX_COLUMN_NAME_LEN-nrcif); j++)
							printf(" ");
					}
					printf("\n");
				}
				i=0;
			}
		}
	}
	else if(strcmp(relatie,">=")==0)
	{
		t_intLine *l=NULL;
		int i=0;
		for(l=T->lines; l!=NULL; l=l->next)
		{
			t_intCell *p=NULL, *pc=NULL;
			for(p=((t_intLine *)l)->cells; p!=NULL&&i!=column_no; i++, p=p->next);
			if(p!=NULL)
			{
				if((p->value)>=v)
				{
					for(pc=l->cells; pc!=NULL;  pc=pc->next)
					{
						printf("%d", pc->value);
						int nrcif=nrc((int)pc->value);
						for(int j=0; j<=(MAX_COLUMN_NAME_LEN-nrcif); j++)
							printf(" ");
					}
				printf("\n");
				}
			}
			i=0;
		}
	}
	else if(strcmp(relatie,">")==0)
	{
		t_intLine *l=NULL;
		int i=0;
		for(l=T->lines; l!=NULL; l=l->next)
		{
			t_intCell *p=NULL, *pc=NULL;
			for(p=((t_intLine *)l)->cells; p!=NULL&&i!=column_no; i++, p=p->next);
			if(p!=NULL)
			{
				if((p->value)>v)
				{
					for(pc=l->cells; pc!=NULL;  pc=pc->next)
					{
						printf("%d", pc->value);
						int nrcif=nrc((int)pc->value);
						for(int j=0; j<=(MAX_COLUMN_NAME_LEN-nrcif); j++)
							printf(" ");
					}
					printf("\n");
				}
			}
			i=0;
		}
	}
	printf("\n");
}

void CompareFLOAT(t_table *T, char* relatie, float v, int column_no)
{
	
	if(strcmp(relatie,"<")==0)
	{
		t_floatLine *l=NULL;
		int i=0;
		for(l=T->lines; l!=NULL; l=l->next)
		{
			t_floatCell *p=NULL, *pc=NULL;
			for(p=l->cells; p!=NULL&&i!=column_no; i++, p=p->next);
			if(p!=NULL)
			{
				if((p->value)<v)
				{
					for(pc=l->cells; pc!=NULL;  pc=pc->next)
					{
						printf("%f", pc->value);
						int nrcif=fnrcif(pc->value);
						for(int j=0; j<=(MAX_COLUMN_NAME_LEN-nrcif-7); j++)
							printf(" ");
					}
					printf("\n");
				}
			}
			i=0;
		}
	}
	else if(strcmp(relatie,"<=")==0)
	{
		t_floatLine *l=NULL;
		int i=0;
		for(l=T->lines; l!=NULL; l=l->next)
		{
			t_floatCell *p=NULL, *pc=NULL;
			for(p=l->cells; p!=NULL&&i!=column_no; i++, p=p->next);
			if(p!=NULL)
			{
				if((p->value)<=v)
				{
					for(pc=l->cells; pc!=NULL;  pc=pc->next)
					{
						printf("%f", pc->value);
						int nrcif=fnrcif(pc->value);
						for(int j=0; j<=(MAX_COLUMN_NAME_LEN-nrcif-7); j++)
							printf(" ");
					}
					printf("\n");
					
				}
			}
			i=0;
		}
	}
	else if(strcmp(relatie,"==")==0)
	{
		t_floatLine *l=NULL;
		int i=0;
		for(l=T->lines; l!=NULL; l=l->next)
		{
			t_floatCell *p=NULL, *pc=NULL;
			for(p=l->cells; p!=NULL&&i!=column_no; i++, p=p->next);
			if(p!=NULL)
			{
				if((p->value)==v)
				{
					for(pc=l->cells; pc!=NULL;  pc=pc->next)
					{
						printf("%f", pc->value);
						int nrcif=fnrcif(pc->value);
						for(int j=0; j<=(MAX_COLUMN_NAME_LEN-nrcif-7); j++)
							printf(" ");
					}
					printf("\n");
				}
			}
			i=0;
		}
	}
	else if(strcmp(relatie,"!=")==0)
	{
		t_floatLine *l=NULL;
		int i=0;
		for(l=T->lines; l!=NULL; l=l->next)
		{
			t_floatCell *p=NULL, *pc=NULL;
			for(p=l->cells; p!=NULL&&i!=column_no; i++, p=p->next);
			if(p!=NULL)
			{
				if((p->value)!=v)
				{
					for(pc=l->cells; pc!=NULL;  pc=pc->next)
					{
						printf("%f", pc->value);
						int nrcif=fnrcif(pc->value);
						for(int j=0; j<=(MAX_COLUMN_NAME_LEN-nrcif-7); j++)
							printf(" ");
					}
					printf("\n");
				}
			}
			i=0;
		}
	}
	else if(strcmp(relatie,">=")==0)
	{
		t_floatLine *l=NULL;
		int i=0;
		for(l=T->lines; l!=NULL; l=l->next)
		{
			t_floatCell *p=NULL, *pc=NULL;
			for(p=l->cells; p!=NULL&&i!=column_no; i++, p=p->next);
			if(p!=NULL)
			{
				if((p->value)>=v)
				{
					for(pc=l->cells; pc!=NULL;  pc=pc->next)
					{
						printf("%f", pc->value);
						int nrcif=fnrcif(pc->value);
						for(int j=0; j<=(MAX_COLUMN_NAME_LEN-nrcif-7); j++)
							printf(" ");
					}
					printf("\n");
				}
			}
			i=0;
		}
	}
	else if(strcmp(relatie,">")==0)
	{
		t_floatLine *l=NULL;
		int i=0;
		for(l=T->lines; l!=NULL; l=l->next)
		{
			t_floatCell *p=NULL, *pc=NULL;
			for(p=l->cells; p!=NULL&&i!=column_no; i++, p=p->next);
			if(p!=NULL)
			{
				if((p->value)>v)
				{
					for(pc=l->cells; pc!=NULL;  pc=pc->next)
					{
						printf("%f", pc->value);
						int nrcif=fnrcif(pc->value);
						for(int j=0; j<=(MAX_COLUMN_NAME_LEN-nrcif-7); j++)
							printf(" ");
					}
					printf("\n");
				}
			}
			i=0;
		}
	}
	printf("\n");
}

void CompareSTRING(t_table *T, char* relatie, char *v, int column_no)
{
	if(strcmp(relatie,"<")==0)
	{
		t_stringLine *l=NULL;
		int i=0;
		for(l=T->lines; l!=NULL; l=l->next)
		{
			t_stringCell *p=NULL, *pc=NULL;
			for(p=l->cells; p!=NULL && i!=column_no; i++, p=p->next);
			if(p!=NULL)
			{
				if(strncmp(p->value,v,strlen(v))<0)
				{
					for(pc=l->cells; pc!=NULL;  pc=pc->next)
					{
						int x=strlen(pc->value);
						pc->value[x]='\0';
						printf("%s", pc->value);
						for(int j=0; j<=(MAX_COLUMN_NAME_LEN-
							strlen((char *)(pc->value))); j++)
								printf(" ");
					}
					printf("\n");
				}
			}
			i=0;
			
		}
	}
	else if(strcmp(relatie,"<=")==0)
	{
		t_stringLine *l=NULL;
		int i=0;
		for(l=T->lines; l!=NULL; l=l->next)
		{
			t_stringCell *p=NULL, *pc=NULL;
			for(p=l->cells; p!=NULL && i!=column_no; i++, p=p->next);
			if(p!=NULL)
			{
				if(strncmp(p->value,v,strlen(v))<=0)
				{
					for(pc=l->cells; pc!=NULL;  pc=pc->next)
					{
						int x=strlen(pc->value);
						pc->value[x]='\0';
						printf("%s", pc->value);
						for(int j=0; j<=(MAX_COLUMN_NAME_LEN-
							strlen((char *)(pc->value))); j++)
								printf(" ");
					}
					printf("\n");
				}
			}
			i=0;
			
		}
	}
	else if(strcmp(relatie,"==")==0)
	{
		t_stringLine *l=NULL;
		int i=0;
		for(l=T->lines; l!=NULL; l=l->next)
		{
			t_stringCell *p=NULL, *pc=NULL;
			for(p=l->cells; p!=NULL && i!=column_no; i++, p=p->next);
			if(p!=NULL)
			{
				if(strncmp(p->value,v,strlen(v))==0)
				{
					for(pc=l->cells; pc!=NULL;  pc=pc->next)
					{
						int x=strlen(pc->value);
						pc->value[x]='\0';
						printf("%s", pc->value);
						for(int j=0; j<=(MAX_COLUMN_NAME_LEN-
							strlen((char *)(pc->value))); j++)
								printf(" ");
					}
					printf("\n");
				}
			}
			i=0;
			
		}	
	}
	else if(strcmp(relatie,"!=")==0)
	{
		t_stringLine *l=NULL;
		int i=0;
		for(l=T->lines; l!=NULL; l=l->next)
		{
			t_stringCell *p=NULL, *pc=NULL;
			for(p=l->cells; p!=NULL && i!=column_no; i++, p=p->next);
			if(p!=NULL)
			{
				if(strncmp(p->value,v,strlen(v))!=0)
				{
					for(pc=l->cells; pc!=NULL;  pc=pc->next)
					{
						int x=strlen(pc->value);
						pc->value[x]='\0';
						printf("%s", pc->value);
						for(int j=0; j<=(MAX_COLUMN_NAME_LEN-
							strlen((char *)(pc->value))); j++)
								printf(" ");
					}
					printf("\n");
				}
			}
			i=0;
		}
	}
	else if(strncmp(relatie,">=", strlen(">="))==0)
	{
		t_stringLine *l=NULL;
		int i=0;
		for(l=T->lines; l!=NULL; l=l->next)
		{
			t_stringCell *p=NULL, *pc=NULL;
			for(p=l->cells; p!=NULL && i!=column_no; i++, p=p->next);
			if(p!=NULL)
			{
				if(strncmp(p->value,v, strlen(v))>=0)
				{
					for(pc=l->cells; pc!=NULL;  pc=pc->next)
					{
						int x=strlen(pc->value);
						pc->value[x]='\0';
						printf("%s", pc->value);
						for(int j=0; j<=(MAX_COLUMN_NAME_LEN-
							strlen((char *)(pc->value))); j++)
								printf(" ");
					}
					printf("\n");
				}
			}
			i=0;
		}
	}
	else if(strcmp(relatie,">")==0)
	{
		t_stringLine *l=NULL;
		int i=0;
		for(l=T->lines; l!=NULL; l=l->next)
		{
			t_stringCell *p=NULL, *pc=NULL;
			for(p=l->cells; p!=NULL && i!=column_no; i++, p=p->next);
			if(p!=NULL)
			{
				if(strncmp(p->value,v,strlen(v))>0)
				{
					for(pc=l->cells; pc!=NULL;  pc=pc->next)
					{
						int x=strlen(pc->value);
						pc->value[x]='\0';
						printf("%s", pc->value);
						for(int j=0; j<=(MAX_COLUMN_NAME_LEN-
							strlen((char *)(pc->value))); j++)
								printf(" ");
					}
					printf("\n");
				}
			}
		  i=0;
		}
	}
	printf("\n");

}

void Search(t_table *T, char *column, char *relatie, char *v)
{
	t_column *c=NULL;
	int column_no=0;
	//gasesc numarul coloanei
	for(c=T->columns; c!=NULL; c=c->next, column_no++)
	{
		if(strcmp(c->name, column)==0) break;
	}
	if(c==NULL) 
	{
		printf("Table \"%s\" does not contain column \"%s\".\n", 
			T->name, column);
		return;
	}
	//printez head ul tabelei
	printf("TABLE: %s\n", T->name); 
	//afisare coloane
	int name_length=0, columns_no=0;
	for(c=T->columns; c!=NULL; c=c->next)
	{
		name_length=strlen(c->name);
		c->name[name_length]='\0';
		printf("%s", c->name);
		for(int i=0; i<=(MAX_COLUMN_NAME_LEN-name_length); i++)
			printf(" ");
		columns_no++;
	}
	printf("\n");
	for(int j=0; j<columns_no; j++)
	{
		for(int i=0; i<MAX_COLUMN_NAME_LEN; i++)
		{
			printf("-");
		}
		printf(" ");
	}
	printf("\n");
	
	if(T->type==INT)
	{
		int vint=atoi(v);
		CompareINT(T, relatie ,vint, column_no);
	}
	else if(T->type==FLOAT)
	{
		float vfloat=atof(v);
		CompareFLOAT(T, relatie, vfloat, column_no);
	}
	else if(T->type==STRING)
	{
		CompareSTRING(T, relatie, v, column_no);
	}
}