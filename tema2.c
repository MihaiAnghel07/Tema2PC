//ANGHEL MIHAI-GABRIEL 313CD

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util/task_helper.h"

int toupper(int c);
int tolower(int c);


void uppercase(char poem[4000])
{ 	
	
	int i;

	if(poem[0]>='a' && poem[0]<='z') 
		poem[0]=poem[0]-32;
	
	for(i=1;poem[i]!='\0'; i++)
	{
		if(poem[i-1]=='\n')
		{
			if(poem[i]>='a' && poem[i]<='z')
				poem[i]=poem[i]-32;	/*se converteste din litera 
										mica in litera mare*/		
		}
		else
		{
			if(poem[i]>='A' && poem[i]<='Z')
				poem[i] = poem[i]+32; /*se converteste din litera
										mare in litera mica*/
		}
	}
}

void trimming(char poem[4000])
{	

	char separatori[10]=" .,;!?:",*p,aux[4000]="";
	int i;

	p=strtok(poem,separatori);
	while(p){					

		strcat(aux,p);
		strcat(aux," ");
		p=strtok(NULL,separatori);

	}
	
	for(i=0; aux[i]!='\0'; i++)
	{
		if((aux[i]==' ' && aux[i+1]=='\n') || (aux[i]==' ' && aux[i+1]=='\0')){
			memmove(&aux[i],&aux[i+1],strlen(aux)-i);
		}
	}

	strcpy(poem,aux);
}

void silly(char poem[4000],float prob)
{
	
	float sample;
	char *p,separatori[10]=" .,;!?:\n";
	int i;

	for(i=0;poem[i]!='\0';i++)
	{
		if((poem[i]>='a' && poem[i]<='z') || (poem[i]>='A' && poem[i]<='Z'))
		{
			sample = rand() % 100 / 99.0;
			if(prob>sample)
				if(poem[i]>='a' && poem[i]<='z')
					poem[i]=poem[i]-32;
				else
					poem[i]=poem[i]+32;
				
		}
	}
}

void replace(char poem[4000], int i, char *word1, char *word2)
{	
	char aux[4000];

	strcpy(aux,poem+i+strlen(word1));
	strcpy(poem+i,word2);
	strcpy(poem+i+strlen(word2),aux);

}

void friendly(char poem[4000])
{	
	char aux[4000]="",*p,separatori[10]="\n .,;!?:";
	char *word;
	int i;

	for(i=0; poem[i]!='\0'; i++)
	{
		if(!strchr(separatori,poem[i]) && strchr(separatori,poem[i-1]))
		{
			strcpy(aux,poem+i);
			p=strtok(aux,separatori);
			if(p!=NULL)
			{
				get_friendly_word(p,&word);
				if(word!=NULL)
				{
					replace(poem,i,p,word);
				}
			}
		}
	}
	

}

void ordonare(int n, char **word_list)
{	
	char aux[50];
	int i,j;

	for(i=0; i<n-1; i++)
	{
		for(j=i+1; j<n; j++)
		{
			if(strcmp(word_list[i], word_list[j]) > 0)
			{
               	strcpy(aux, word_list[i]);
               	strcpy(word_list[i], word_list[j]);
               	strcpy(word_list[j], aux);
           	}
		}
	}

}


void prelucrare(char poem[4000], char *word1, char *word2, int ind1, int ind2)
{	
	char **word_list,aux[50],ch1,ch2;
	int n,i,j;

	get_synonym(word1,&n,&word_list);

	if(n != -1)	//se verifica daca exista sinonime pentru primul cuvant primit
	{								//si se prelucreaza in caz afirmativ
		ordonare(n,word_list);
		ch1=tolower(word2[strlen(word2)-1]);
		for(i=0; i<n; i++)
		{
			ch2=tolower(word_list[i][strlen(word_list[i])-1]);
			if(ch1 == ch2)
			{
				replace(poem,ind1,word1,word_list[i]);
				break;
			}
		}
	}
	else	//altfel se cauta pentru cuvantul2 si se prelucreaza
	{	
		get_synonym(word2,&n,&word_list);
		ordonare(n,word_list);
		ch1=tolower(word1[strlen(word1)-1]);
		for(i=0; i<n; i++)
		{
			ch2=tolower(word_list[i][strlen(word_list[i])-1]);
			if(ch1 == ch2)
			{
				replace(poem,ind2,word2,word_list[i]);
				break;
			}
		}
	}


}

void rhimy(char poem[4000],char *p)
{	
	int vers=0,i,j,n,indice1=-1,indice2=-1,indice3=-1,indice4=-1;
	char separatori[10]="\n .,;!?:",aux[4000]="",**word_list;
	char word3[50],word4[50],ch1,ch2,ch3,ch4,word1[50],word2[50];

	if(strcmp(p,"imperecheata")==0)
	{
		for(i=0; poem[i]!='\0'; i++)
		{
			if(!strchr(separatori,poem[i]) && strchr(separatori,poem[i-1]))
			{
				strcpy(aux,poem+i);
				p=strtok(aux,separatori);
				if(p!=NULL)
				{
					j=i+strlen(p);
					while(strchr(separatori,poem[j])) //se parcurg caracterele
					{								//pana la urmatorul cuvant
						j++;
					}
					if((poem[j-1]=='\n' && vers<2) || (poem[j-1]=='\0'))
					{								 //daca e ultimul cuvant 
													//din vers, se prelucreaza 					
						vers++;
						if(vers==1 && indice1 == -1)
						{
							strcpy(word1,p);
							ch1=tolower(word1[strlen(word1)-1]);
							indice1=i;
						}
						if(vers==2 && indice2 == -1)
						{
							strcpy(word2,p);
							ch2=tolower(word2[strlen(word2)-1]);
							indice2=i;
							if(ch1 != ch2)
							{
								prelucrare(poem,word1,word2,indice1,indice2);
								
							}
							indice1=-1;
							indice2=-1;
							vers=0;
						}
					}
			    }
			}
		}

	}
//acelasi algoritm se aplica si la urmatoarele tipuri de rima, cu mici 
//schimbari in functie de rima
	if(strcmp(p,"incrucisata")==0)
	{
		for(i=0; poem[i]!='\0'; i++)
		{
			if(!strchr(separatori,poem[i]) && strchr(separatori,poem[i-1]))
			{ 
				strcpy(aux,poem+i);
				p=strtok(aux,separatori);
				if(p!=NULL)
				{
					j=i+strlen(p);
					while(strchr(separatori,poem[j]))
					{
						j++;
					}
					if((poem[j-1]=='\n') || (poem[j-1]=='\0'))
					{
						vers++;
						if(vers==1 && indice1 == -1)
						{
							strcpy(word1,p);
							ch1=tolower(word1[strlen(word1)-1]);
							indice1=i;
						}
						if(vers==2 && indice2 == -1)
						{
							strcpy(word2,p);
							ch2=tolower(word2[strlen(word2)-1]);
							indice2=i;
						}
						if(vers==3 && indice3 == -1)
						{
							strcpy(word3,p);
							ch3=tolower(word3[strlen(word3)-1]);
							indice3=i;
						}
						if(vers==4 && indice4 == -1)
						{
							strcpy(word4,p);
							ch4=tolower(word4[strlen(word4)-1]);
							indice4=i;
							
							if(ch1 != ch3)
							{
								prelucrare(poem,word1,word3,indice1,indice3);
							}

							if(ch2 != ch4)
							{
								prelucrare(poem,word2,word4,indice2,indice4);
							}

							indice1=-1;
							indice2=-1;
							indice3=-1;
							indice4=-1;
							vers=0;
						}
					}
			    }
			}
		}
	}

	if(strcmp(p,"imbratisata")==0)
	{
		for(i=0; poem[i]!='\0'; i++)
		{
			if(!strchr(separatori,poem[i]) && strchr(separatori,poem[i-1]))
			{ 
				strcpy(aux,poem+i);
				p=strtok(aux,separatori);
				if(p!=NULL)
				{
					j=i+strlen(p);
					while(strchr(separatori,poem[j]))
					{
						j++;
					}
					if((poem[j-1]=='\n') || (poem[j-1]=='\0'))
					{
						vers++;
						if(vers==1 && indice1 == -1)
						{
							strcpy(word1,p);
							ch1=tolower(word1[strlen(word1)-1]);
							indice1=i;
						}
						if(vers==2 && indice2 == -1)
						{
							strcpy(word2,p);
							ch2=tolower(word2[strlen(word2)-1]);
							indice2=i;
						
						}
						if(vers==3 && indice3 == -1)
						{
							strcpy(word3,p);
							ch3=tolower(word3[strlen(word3)-1]);
							indice3=i;
							
						}
						if(vers==4 && indice4 == -1)
						{
							strcpy(word4,p);
							ch4=tolower(word4[strlen(word4)-1]);
							indice4=i;
							
							if(ch1 != ch4)
							{
								prelucrare(poem,word1,word4,indice1,indice4);
							}

							if(ch2 != ch3)
							{
								prelucrare(poem,word2,word3,indice2,indice3);
							}
							indice1=-1;
							indice2=-1;
							indice3=-1;
							indice4=-1;
							vers=0;
						}
					}
			    }
			}
		}
	}

}

void print(char poem[4000])
{
	printf("%s\n\n",poem);
}

int main(void)
{	
	char poem[4000],*p,comanda[50];
	int i,lungime=0;
	float prob;
	
	srand(42);
	
	while(1)
	{
		fgets(comanda,50,stdin);
		if(strstr(comanda,"quit"))
		{
			comanda[strlen(comanda)-1]='\0';
			break;
		}
		if(strstr(comanda,"load"))
		{
			p=comanda+5;
			*(p+strlen(p)-1)='\0';
			load_file(p,poem);
		}	
		if(strstr(comanda,"uppercase"))
		{
			uppercase(poem);	
		}
		if(strstr(comanda,"trimming"))
		{
			trimming(poem);	
		}
		if(strstr(comanda,"make_it_silly"))
		{
			p=comanda+14;
			prob=atof(p);
			silly(poem,prob);
		}
		if(strstr(comanda,"make_it_friendlier"))
		{
			friendly(poem);
		}
		if(strstr(comanda,"make_it_rhyme"))
		{
			p=comanda+14;
			*(p+strlen(p)-1)='\0';
			rhimy(poem,p);
		}
		if(strstr(comanda,"print"))
		{
			comanda[strlen(comanda)-1]='\0';
			print(poem);
		}	
	}

	return 0;

}
