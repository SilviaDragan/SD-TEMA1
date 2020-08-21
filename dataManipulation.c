#include "structures.h"
/*DRAGAN Silvia - 311CB*/


//functii de alocare a liniilor si celulelor in functie de tipul lor
t_intLine *Aloc_intLine()
{
	t_intLine *aux=(t_intLine *)malloc(sizeof(t_intLine));
	if(!aux)
	{
		printf("EROARE LA ALOCARE.\n");
		return NULL;
	}
	aux->cells=NULL;
	aux->next=NULL;
	return aux;
}

t_intCell *Aloc_intCell(int x)
{
	t_intCell *aux=(t_intCell *)malloc(sizeof(t_intCell));
	if(!aux)
	{
		printf("EROARE LA ALOCARE\n");
		return NULL;
	}
	aux->value=x;
	aux->next=NULL;
	return aux;
}

t_floatLine *Aloc_floatLine()
{
	t_floatLine *aux=(t_floatLine *)malloc(sizeof(t_floatLine));
	if(!aux)
	{
		printf("EROARE LA ALOCARE.\n");
		return NULL;
	}
	aux->cells=NULL;
	aux->next=NULL;
	return aux;
}

t_floatCell *Aloc_floatCell(float x)
{
	t_floatCell *aux=(t_floatCell *)malloc(sizeof(t_floatCell));
	if(!aux)
	{
		printf("EROARE LA ALOCARE\n");
		return NULL;
	}
	aux->value=x;
	aux->next=NULL;
	return aux;
}

t_stringLine *Aloc_stringLine()
{
	t_stringLine *aux=(t_stringLine *)malloc(sizeof(t_stringLine));
	if(!aux)
	{
		printf("EROARE LA ALOCARE.\n");
		return NULL;
	}
	aux->cells=NULL;
	aux->next=NULL;
	return aux;
}

t_stringCell *Aloc_stringCell(char *x)
{
	t_stringCell *aux=(t_stringCell *)malloc(sizeof(t_stringCell));
	if(!aux)
	{
		printf("EROARE LA ALOCARE\n");
		return NULL;
	}
	aux->value=(char *)malloc((strlen(x)+1)*sizeof(char));
	memset(aux->value, 0, strlen(x)+1);
	strncpy(aux->value, x, strlen(x));
	aux->next=NULL;
	return aux;
}

void AddLine(t_table *T)
{
	//citesc valorile de adaugat
	char line[MAX_CMD_LEN];
	memset(line, 0, MAX_CMD_LEN);
	fgets(line, MAX_CMD_LEN, stdin);
	line[strlen(line)-1]='\0';
	if(T->type==INT)
	{
		t_intLine *p=NULL, *last_line=NULL, *aux=NULL;
		for(p=T->lines; p!=NULL; last_line=p, p=p->next);
		//aloc spatiu pentru o linie noua si o inserez la sfarsitul listei
		aux=Aloc_intLine();
		if(!aux) return;
		//verific daca tabela are lista de linii vida
		if(!last_line) T->lines=aux;
		else last_line->next=aux;

		//aloc si adaug celule cu informatiile corespunzatoare
		char *token=strtok(line, " ");
		t_intCell *c=NULL, *last_cell=NULL;
		while(token)
		{
			c=Aloc_intCell(atoi(token));
			if(last_cell==NULL)
			{
				aux->cells=c;
				last_cell=c;
			}
			else
			{
				last_cell->next=c;
				last_cell=c;
			}
			token=strtok(NULL, " ");
		}
	}
	else if(T->type==FLOAT)
	{
		t_floatLine *p=NULL, *last_line=NULL, *aux=NULL;
		for(p=T->lines; p!=NULL; last_line=p, p=p->next);
		aux=Aloc_floatLine();
		if(!aux) return;
		if(!last_line) T->lines=aux;
		else last_line->next=aux;

		char *token=strtok(line, " ");
		t_floatCell *c=NULL, *last_cell=NULL;
		while(token)
		{
			c=Aloc_floatCell(atof(token));
			if(last_cell==NULL)
			{
				aux->cells=c;
				last_cell=c;
			}
			else
			{
				last_cell->next=c;
				last_cell=c;
			}
			token=strtok(NULL, " ");
		}
	}
	else if(T->type==STRING)
	{
		t_stringLine *p=NULL, *last_line=NULL, *aux=NULL;
		for(p=T->lines; p!=NULL; last_line=p, p=p->next);
		aux=Aloc_stringLine();
		if(!aux) return;
		if(!last_line) T->lines=aux;
		else last_line->next=aux;

		char *token=strtok(line, " ");
		t_stringCell *c=NULL, *last_cell=NULL;
		while(token)
		{
			c=Aloc_stringCell(token);
			if(last_cell==NULL)
			{
				aux->cells=c;
				last_cell=c;
			}
			else
			{
				last_cell->next=c;
				last_cell=c;
			}
			token=strtok(NULL, " ");
		}
	}
	return;
}
//functii de stergere a liniilor dupa conditia data, in functie de tip
void DeleteINT(t_table *T, char* relatie, int v, int column_no)
{
	if(strcmp(relatie,"<")==0)
	{
		t_intLine *l=NULL, *ant=NULL, *aux_l=NULL;
		int i=0;
		for(l=T->lines; l!=NULL; )
		{
			t_intCell *p=NULL, *q=NULL, *aux=NULL;
			//gasesc celula de pe coloana data
			for(p=l->cells; p!=NULL&&i!=column_no; i++, p=p->next);
			//daca a fost gasita
			if(p!=NULL)
			{
				//verific daca indeplineste conditia
				if((p->value)<v)
				{
					//elimin linia din tabel si eliberez memoria
					if(ant==NULL) T->lines=l->next;
					else ant->next=l->next;
					aux_l=l;
					l=l->next;
					for(q=aux_l->cells; q!=NULL; )
					{
						aux=q;
						q=q->next;
						free(aux);
					}
					free(aux_l);
				}
				else {ant=l; l=l->next;}
			}
			i=0;
		}
	}
	else if(strcmp(relatie,"<=")==0)
	{
		t_intLine *l=NULL, *ant=NULL, *aux_l=NULL;
		int i=0;
		for(l=T->lines; l!=NULL; )
		{
			t_intCell *p=NULL, *q=NULL, *aux=NULL;
			for(p=l->cells; p!=NULL&&i!=column_no; i++, p=p->next);
			if(p!=NULL)
			{
				if((p->value)<=v)
				{
					if(ant==NULL) T->lines=l->next;
					else ant->next=l->next;
					aux_l=l;
					l=l->next;
					for(q=aux_l->cells; q!=NULL; )
					{
						aux=q;
						q=q->next;
						free(aux);
					}
					free(aux_l);
				}
				else {ant=l; l=l->next;}
			}
			i=0;
		}
	}
	else if(strcmp(relatie,"==")==0)
	{
		t_intLine *l=NULL, *ant=NULL, *aux_l=NULL;
		int i=0;
		for(l=T->lines; l!=NULL; )
		{
			t_intCell *p=NULL, *q=NULL, *aux=NULL;
			for(p=l->cells; p!=NULL&&i!=column_no; i++, p=p->next);
			if(p!=NULL)
			{
				if((p->value)==v)
				{
					if(ant==NULL) T->lines=l->next;
					else ant->next=l->next;
					aux_l=l;
					l=l->next;
					for(q=aux_l->cells; q!=NULL; )
					{
						aux=q;
						q=q->next;
						free(aux);
					}
					free(aux_l);
				}
				else {ant=l; l=l->next;}
			}
			i=0;
		}
	}
	else if(strcmp(relatie,"!=")==0)
	{
		t_intLine *l=NULL, *ant=NULL, *aux_l=NULL;
		int i=0;
		for(l=T->lines; l!=NULL; )
		{
			t_intCell *p=NULL, *q=NULL, *aux=NULL;
			for(p=l->cells; p!=NULL&&i!=column_no; i++, p=p->next);
			if(p!=NULL)
			{
				if((p->value)!=v)
				{
					if(ant==NULL) T->lines=l->next;
					else ant->next=l->next;
					aux_l=l;
					l=l->next;
					for(q=aux_l->cells; q!=NULL; )
					{
						aux=q;
						q=q->next;
						free(aux);
					}
					free(aux_l);
				}
				else {ant=l; l=l->next;}
			}
			i=0;
		}
	}
	else if(strcmp(relatie,">=")==0)
	{
		t_intLine *l=NULL, *ant=NULL, *aux_l=NULL;
		int i=0;
		for(l=T->lines; l!=NULL; )
		{
			t_intCell *p=NULL, *q=NULL, *aux=NULL;
			for(p=l->cells; p!=NULL&&i!=column_no; i++, p=p->next);
			if(p!=NULL)
			{
				if((p->value)>=v)
				{
					if(ant==NULL) T->lines=l->next;
					else ant->next=l->next;
					aux_l=l;
					l=l->next;
					for(q=aux_l->cells; q!=NULL; )
					{
						aux=q;
						q=q->next;
						free(aux);
					}
					free(aux_l);
				}
				else {ant=l; l=l->next;}
			}
			i=0;
		}
	}
	else if(strcmp(relatie,">")==0)
	{
		t_intLine *l=NULL, *ant=NULL, *aux_l=NULL;
		int i=0;
		for(l=T->lines; l!=NULL; )
		{
			t_intCell *p=NULL, *q=NULL, *aux=NULL;
			for(p=l->cells; p!=NULL&&i!=column_no; i++, p=p->next);
			if(p!=NULL)
			{
				if((p->value)>v)
				{
					if(ant==NULL) T->lines=l->next;
					else ant->next=l->next;
					aux_l=l;
					l=l->next;
					for(q=aux_l->cells; q!=NULL; )
					{
						aux=q;
						q=q->next;
						free(aux);
					}
					free(aux_l);
				}
				else {ant=l; l=l->next;}
			}
			i=0;
		}
	}
}

void DeleteFLOAT(t_table *T, char* relatie, float v, int column_no)
{
	if(strcmp(relatie,"<")==0)
	{
		t_floatLine *l=NULL, *ant=NULL, *aux_l=NULL;
		int i=0;
		for(l=T->lines; l!=NULL; )
		{
			t_floatCell *p=NULL, *q=NULL, *aux=NULL;
			for(p=l->cells; p!=NULL&&i!=column_no; i++, p=p->next);
			if(p!=NULL)
			{
				if((p->value)<v)
				{
					if(ant==NULL) T->lines=l->next;
					else ant->next=l->next;
					aux_l=l;
					l=l->next;
					for(q=aux_l->cells; q!=NULL; )
					{
						aux=q;
						q=q->next;
						free(aux);
					}
					free(aux_l);
				}
				else {ant=l; l=l->next;}
			}
			i=0;
		}
	}
	else if(strcmp(relatie,"<=")==0)
	{
		t_floatLine *l=NULL, *ant=NULL, *aux_l=NULL;
		int i=0;
		for(l=T->lines; l!=NULL; )
		{
			t_floatCell *p=NULL, *q=NULL, *aux=NULL;
			for(p=l->cells; p!=NULL&&i!=column_no; i++, p=p->next);
			if(p!=NULL)
			{
				if((p->value)<=v)
				{
					if(ant==NULL) T->lines=l->next;
					else ant->next=l->next;
					aux_l=l;
					l=l->next;
					for(q=aux_l->cells; q!=NULL; )
					{
						aux=q;
						q=q->next;
						free(aux);
					}
					free(aux_l);
				}
				else {ant=l; l=l->next;}
			}
			i=0;
		}
	}
	else if(strcmp(relatie,"==")==0)
	{
		t_floatLine *l=NULL, *ant=NULL, *aux_l=NULL;
		int i=0;
		for(l=T->lines; l!=NULL; )
		{
			t_floatCell *p=NULL, *q=NULL, *aux=NULL;
			for(p=l->cells; p!=NULL&&i!=column_no; i++, p=p->next);
			if(p!=NULL)
			{
				if((p->value)==v)
				{
					if(ant==NULL) T->lines=l->next;
					else ant->next=l->next;
					aux_l=l;
					l=l->next;
					for(q=aux_l->cells; q!=NULL; )
					{
						aux=q;
						q=q->next;
						free(aux);
					}
					free(aux_l);
				}
				else {ant=l; l=l->next;}
			}
			i=0;
		}
	}
	else if(strcmp(relatie,"!=")==0)
	{
		t_floatLine *l=NULL, *ant=NULL, *aux_l=NULL;
		int i=0;
		for(l=T->lines; l!=NULL; )
		{
			t_floatCell *p=NULL, *q=NULL, *aux=NULL;
			for(p=l->cells; p!=NULL&&i!=column_no; i++, p=p->next);
			if(p!=NULL)
			{
				if((p->value)!=v)
				{
					if(ant==NULL) T->lines=l->next;
					else ant->next=l->next;
					aux_l=l;
					l=l->next;
					for(q=aux_l->cells; q!=NULL; )
					{
						aux=q;
						q=q->next;
						free(aux);
					}
					free(aux_l);
				}
				else {ant=l; l=l->next;}
			}
			i=0;
		}
	}
	else if(strcmp(relatie,">=")==0)
	{
		t_floatLine *l=NULL, *ant=NULL, *aux_l=NULL;
		int i=0;
		for(l=T->lines; l!=NULL; )
		{
			t_floatCell *p=NULL, *q=NULL, *aux=NULL;
			for(p=l->cells; p!=NULL&&i!=column_no; i++, p=p->next);
			if(p!=NULL)
			{
				if((p->value)>=v)
				{
					if(ant==NULL) T->lines=l->next;
					else ant->next=l->next;
					aux_l=l;
					l=l->next;
					for(q=aux_l->cells; q!=NULL; )
					{
						aux=q;
						q=q->next;
						free(aux);
					}
					free(aux_l);
				}
				else {ant=l; l=l->next;}
			}
			i=0;
		}
	}
	else if(strcmp(relatie,">")==0)
	{
		t_floatLine *l=NULL, *ant=NULL, *aux_l=NULL;
		int i=0;
		for(l=T->lines; l!=NULL; )
		{
			t_floatCell *p=NULL, *q=NULL, *aux=NULL;
			for(p=l->cells; p!=NULL&&i!=column_no; i++, p=p->next);
			if(p!=NULL)
			{
				if((p->value)>v)
				{
					if(ant==NULL) T->lines=l->next;
					else ant->next=l->next;
					aux_l=l;
					l=l->next;
					for(q=aux_l->cells; q!=NULL; )
					{
						aux=q;
						q=q->next;
						free(aux);
					}
					free(aux_l);
				}
				else {ant=l; l=l->next;}
			}
			i=0;
		}
	}
}

void DeleteSTRING(t_table *T, char* relatie, char *v, int column_no)
{
	if(strcmp(relatie,"<")==0)
	{
		t_stringLine *l=NULL, *ant=NULL, *aux_l=NULL;
		int i=0;
		for(l=T->lines; l!=NULL; )
		{
			t_stringCell *p=NULL, *q=NULL, *aux=NULL;
			for(p=l->cells; p!=NULL&&i!=column_no; i++, p=p->next);
			if(p!=NULL)
			{
				if(strncmp(p->value,v,strlen(v))<0)
				{
					if(ant==NULL) T->lines=l->next;
					else ant->next=l->next;
					aux_l=l;
					l=l->next;
					aux_l->next=NULL;
					for(q=aux_l->cells; q!=NULL;)
					{
						aux=q;
						q=q->next;
						free(aux->value);
						free(aux);
					}
					free(aux_l);
				}

				else {ant=l; l=l->next;}
			}
			i=0;
		}
	}
	else if(strcmp(relatie,"<=")==0)
	{
		t_stringLine *l=NULL, *ant=NULL, *aux_l=NULL;
		int i=0;
		for(l=T->lines; l!=NULL; )
		{
			t_stringCell *p=NULL, *q=NULL, *aux=NULL;
			for(p=l->cells; p!=NULL&&i!=column_no; i++, p=p->next);
			if(p!=NULL)
			{
				if(strncmp(p->value,v,strlen(v))<=0)
				{
					if(ant==NULL) T->lines=l->next;
					else ant->next=l->next;
					aux_l=l;
					l=l->next;
					aux_l->next=NULL;
					for(q=aux_l->cells; q!=NULL;)
					{
						aux=q;
						q=q->next;
						free(aux->value);
						free(aux);
					}
					free(aux_l);
				}

				else {ant=l; l=l->next;}
			}
			i=0;
		}
	}
	else if(strcmp(relatie,"==")==0)
	{
		t_stringLine *l=NULL, *ant=NULL, *aux_l=NULL;
		int i=0;
		for(l=T->lines; l!=NULL; )
		{
			t_stringCell *p=NULL, *q=NULL, *aux=NULL;
			for(p=l->cells; p!=NULL&&i!=column_no; i++, p=p->next);
			if(p!=NULL)
			{
				if(strncmp(p->value,v,strlen(v))==0)
				{
					if(ant==NULL) T->lines=l->next;
					else ant->next=l->next;
					aux_l=l;
					l=l->next;
					aux_l->next=NULL;
					for(q=aux_l->cells; q!=NULL;)
					{
						aux=q;
						q=q->next;
						free(aux->value);
						free(aux);
					}
					free(aux_l);
				}

				else {ant=l; l=l->next;}
			}
			i=0;
		}
	}
	else if(strcmp(relatie,"!=")==0)
	{
		t_stringLine *l=NULL, *ant=NULL, *aux_l=NULL;
		int i=0;
		for(l=T->lines; l!=NULL; )
		{
			t_stringCell *p=NULL, *q=NULL, *aux=NULL;
			for(p=l->cells; p!=NULL&&i!=column_no; i++, p=p->next);
			if(p!=NULL)
			{
				if(strncmp(p->value,v,strlen(v))!=0)
				{
					if(ant==NULL) T->lines=l->next;
					else ant->next=l->next;
					aux_l=l;
					l=l->next;
					aux_l->next=NULL;
					for(q=aux_l->cells; q!=NULL;)
					{
						aux=q;
						q=q->next;
						free(aux->value);
						free(aux);
					}
					free(aux_l);
				}

				else {ant=l; l=l->next;}
			}
			i=0;
		}
	}
	else if(strcmp(relatie,">=")==0)
	{
		t_stringLine *l=NULL, *ant=NULL, *aux_l=NULL;
		int i=0;
		for(l=T->lines; l!=NULL; )
		{
			t_stringCell *p=NULL, *q=NULL, *aux=NULL;
			for(p=l->cells; p!=NULL&&i!=column_no; i++, p=p->next);
			if(p!=NULL)
			{
				if(strncmp(p->value,v,strlen(v))>=0)
				{
					if(ant==NULL) T->lines=l->next;
					else ant->next=l->next;
					aux_l=l;
					l=l->next;
					aux_l->next=NULL;
					for(q=aux_l->cells; q!=NULL;)
					{
						aux=q;
						q=q->next;
						free(aux->value);
						free(aux);
					}
					free(aux_l);
				}

				else {ant=l; l=l->next;}
			}
			i=0;
		}
	}
	else if(strcmp(relatie,">")==0)
	{
		t_stringLine *l=NULL, *ant=NULL, *aux_l=NULL;
		int i=0;
		for(l=T->lines; l!=NULL; )
		{
			t_stringCell *p=NULL, *q=NULL, *aux=NULL;
			for(p=l->cells; p!=NULL&&i!=column_no; i++, p=p->next);
			if(p!=NULL)
			{
				if(strncmp(p->value,v,strlen(v))>0)
				{
					if(ant==NULL) T->lines=l->next;
					else ant->next=l->next;
					aux_l=l;
					l=l->next;
					aux_l->next=NULL;
					for(q=aux_l->cells; q!=NULL;)
					{
						aux=q;
						q=q->next;
						free(aux->value);
						free(aux);
					}
					free(aux_l);
				}

				else {ant=l; l=l->next;}
			}
			i=0;
		}
	}
}

void Delete(t_table *T, char *column, char *relatie, char *val)
{
	int column_no=0;
	t_column *c=NULL;
	//gasesc numarul coloanei dorite dupa nume
	for(c=T->columns; c!=NULL; c=c->next, column_no++)
	{
		if(strcmp(c->name, column)==0) break;
	}

	if(c==NULL) 
	{
		printf("Table \"%s\" does not contain column \"%s\".\n", T->name, column);
		return;
	}
	if(T->type==INT)
	{
		int v=atoi(val);
		DeleteINT(T, relatie ,v, column_no);
	}
	
	else if(T->type==FLOAT)
	{
		float v=atof(val);
		DeleteFLOAT(T, relatie, v, column_no);
	}
	else if(T->type==STRING)
	{
		DeleteSTRING(T, relatie, val, column_no);
	}
	
}

void ClearTable(t_table **p)
{
	if((*p)->type==INT)
	{
		t_intLine *l=NULL, *aux_l=NULL;
		for(l=(*p)->lines; l!=NULL; )
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
	else if((*p)->type==FLOAT)
	{
		t_floatLine *l=NULL, *aux_l=NULL;
		for(l=(*p)->lines; l!=NULL; )
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
	else if((*p)->type==STRING)
	{
		t_stringLine *l=NULL, *aux_l=NULL;
		for(l=(*p)->lines; l!=NULL; )
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
	(*p)->lines=NULL;

}