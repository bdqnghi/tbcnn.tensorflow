#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<stdbool.h>

typedef struct elemento{
	int num;
	struct elemento *ant;
	struct elemento *drt;
	struct elemento *eqd;
}El;

void inicializa(El **v){
	*v = NULL;
}

void insere_primeiro(El **v, int numaux){
	elemento *e;
	e = (elemento*) malloc(sizeof(elemento));
	e->num = numaux;
	e->ant = NULL;
	e->drt = NULL;
	e->eqd = NULL;
	*v = e;
}

void volta(El **v){
	for(;;){
		if((*v)->ant!=NULL){
			(*v)=(*v)->ant;
		}else{
			break;
		}
	}
}

void percorre(El **v, int numaux){
	for(;;){
		if((*v)->num>numaux){
			if((*v)->eqd!=NULL){
				(*v) = (*v)->eqd;
			}else{
				break;
			}
		}else{
			if((*v)->drt!=NULL){
				(*v) = (*v)->drt;
			}else{
				break;
			}
		}
	}
}

bool lado(El **v, int numaux){
	for(;;){
		if((*v)->ant!=NULL){
			(*v)=(*v)->ant;
		}else{
			if((*v)->num>numaux){
				return true;
			}else{
				return false;
			}
		}
	}
	
}


void insere(El **v, int numaux){
	elemento *e;
	e =((elemento*)malloc(sizeof(elemento)));
	
	if((*v)->num>numaux){
		
		e->num = numaux;
		e->ant= (*v); 
		e->drt = NULL;
		e->eqd = NULL; 
		(*v)->eqd = e;
		
	}else{
		
		e->num = numaux;
		e->ant= (*v); 
		e->drt = NULL;
		e->eqd = NULL; 
		(*v)->drt = e;
	}
	
	
	
	*v = e;
		
}

void remover(El **v){ //Falta remover valores a direita da arvore
	elemento *e;
	e = *v;
	bool flag;
	
	
	
	if((*v)->ant == NULL){ //Raiz
		if((*v)->eqd == NULL){ //N�o Tem Valor � esquerda
			if((*v)->drt != NULL){ //Tem Valor � direita
				(*v)->drt->ant = NULL;
				e = (*v)->drt;
				free(*v);
				(*v) = e;
			}else{
				free(*v);
			}
		
		}else{
			if((*v)->drt != NULL){
				if((*v)->eqd->drt == NULL){
					(*v)->eqd->ant = NULL;
					e = (*v)->eqd;
					(*v)->eqd->drt = (*v)->drt;
					(*v)->drt->ant = (*v)->eqd;
					free(*v);
					*v = e;
				}else{
					e = (*v)->eqd->drt;
					for(;;){
						if (e->drt != NULL){
							e = e->drt;
						}else{
							break;
						}
					}
					e->eqd = (*v)->eqd;
					e->drt = (*v)->drt;
					e->ant->drt = NULL;
					e->ant = NULL;
					(*v)->drt->ant = e;
					(*v)->eqd->ant = e;
					free(*v);
					*v = e;
				}
			}else{
				if((*v)->eqd->drt == NULL){
					(*v)->eqd->ant = NULL;
					e = (*v)->eqd;
					free(*v);
					*v = e;
				}else{
					e = (*v)->eqd->drt;
					for(;;){
						if (e->drt != NULL){
							e = e->drt;
						}else{
							break;
						}
					}
					e->eqd = (*v)->eqd;
					e->drt = NULL;
					e->ant->drt = NULL;
					e->ant = NULL;
					free(*v);
					*v = e;
				}
			}
			
		}
	}else{ //N�o � raiz
		flag = (&e, e->num);
		if(flag == true){// Verifica Se esta a Direita ou esquerda -- true = direita / false = esquerda
			if((*v)->drt == NULL){ // Se o que esta a direita � null
				if((*v)->eqd != NULL){
					(*v)->eqd->ant = (*v)->ant;
					e = (*v)->eqd;
					
					if((*v)->ant->num > (*v)->num){ //Para saber se esta a Direita ou a esquerda do anterior
						(*v)->ant->eqd = e;
					}else{
						(*v)->ant->drt = e;
					}
					
					free(*v);
					*v = e;
				}else{
					
					if((*v)->ant->num > (*v)->num){ //Para saber se esta a Direita ou a esquerda do anterior
						(*v)->ant->eqd = NULL;
					}else{
						(*v)->ant->drt = NULL;
					}

					e = (*v)->ant;
					free(*v);
					*v = e;
				}
			
			}else{ // Se o que esta a direita n�o � null
				if((*v)->drt->eqd == NULL){// Verifica se o proximo a direita possui um a esquerda
					(*v)->drt->ant = (*v)->ant;
					e = (*v)->drt;
					
					if((*v)->ant->num > (*v)->num){ //Para saber se esta a Direita ou a esquerda do anterior
						(*v)->ant->eqd = e;
					}else{
						(*v)->ant->drt = e;
					}
					
					free(*v);
					*v = e;
				}else{ // Se tem um a esquerda
					e = (*v)->drt->eqd;
					for(;;){
						if (e->eqd != NULL){
							e = e->eqd;
						}else{
							break;
						}
					}
					e->eqd = (*v)->eqd;
					e->drt = (*v)->drt;
					e->ant->eqd = NULL;
					e->ant = (*v)->ant;
					
					if((*v)->ant->num > (*v)->num){ //Para saber se esta a Direita ou a esquerda do anterior
						(*v)->ant->eqd = e;
					}else{
						(*v)->ant->drt = e;
					}
					
					if((*v)->eqd != NULL){ // Se tem um filho a esquerda do que vai ser retirado
						(*v)->eqd->ant = e;
					}
					
					(*v)->drt->ant = e;
					
					free(*v);
					*v = e;
				}
			}
		}else{ // A esquerda Da raiz
			if((*v)->eqd == NULL){
				if((*v)->drt != NULL){
					(*v)->drt->ant = (*v)->ant;
					e = (*v)->drt;
					
					if((*v)->ant->num > (*v)->num){ //Para saber se esta a Direita ou a esquerda do anterior
						(*v)->ant->eqd = e;
					}else{
						(*v)->ant->drt = e;
					}
					
					
					free(*v);
					*v = e;
				}else{
					
					if((*v)->ant->num > (*v)->num){ //Para saber se esta a Direita ou a esquerda do anterior
						(*v)->ant->eqd = NULL;
					}else{
						(*v)->ant->drt = NULL;
					}
					
					e = (*v)->ant;
					free(*v);
					*v = e;
				}
			
			}else{
				if((*v)->eqd->drt == NULL){
					(*v)->eqd->ant = (*v)->ant;
					e = (*v)->eqd;
					(*v)->ant->eqd = e;
					free(*v);
					*v = e;
				}else{
					e = (*v)->eqd->drt;
					for(;;){
						if (e->drt != NULL){
							e = e->drt;
						}else{
							break;
						}
					}
					e->eqd = (*v)->eqd;
					e->drt = (*v)->drt;
					e->ant->drt = NULL;
					e->ant = (*v)->ant;
					(*v)->ant->eqd = e;
					
					if((*v)->drt != NULL){
						(*v)->drt->ant = e;
					}
					(*v)->eqd->ant = e;
					free(*v);
					*v = e;
				}
			}
		}
	}
	
	
}



int main(){
	
	int i = 0;
	El *n;
	int op;
	int tam = 0;
	inicializa(&n);
	
	while(1){
	
		if(tam==0){
			
			tam++;
			
			printf("Adicione um valor: ");
			scanf("%i", &i);
			fflush(stdin);
			
			system("cls");
			
			insere_primeiro(&n, i);
	
		}else{
			
			printf("Escolha uma opcao\n1-Adicionar Valor\n2-Retirar Valor\n3-Para Cima(^)\n4-Para Direita(>)\n5-Para Esquerda(<)\n6-Sair\n\n\n%d\n\n\n", n->num);
			scanf("%i", &op);
			fflush(stdin);
		
			system("cls");
			
			if(op==1){
			
				tam++;
				printf("Adicione um valor: ");
				scanf("%i", &i);
				fflush(stdin);
				
				volta(&n);
				percorre(&n, i);
				insere(&n, i);
				
					
			
				system("cls");
				
				
			}else if(op==2){
				tam--;
				remover(&n);
			}else if(op==3){
				if(n->ant!=NULL){
					n = n->ant;
				}
			}else if(op==4){
				if(n->drt!=NULL){
					n = n->drt;
				}
			}else if(op==5){
				if(n->eqd!=NULL){
					n = n->eqd;
				}
			}else if(op==6){
				break;	
			}else{
				
				printf("Comando Invalido");
				
				Sleep(2000);
				system("cls");
				
			} 	
		}
		
			
	}
	
	return 0;
}

