#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
struct lote{
    int numlot;
    int mes;
    int dia;
    int anno;
    int cantidad;
    int exitencia;
    lote *sig;
};

struct productos{
    int codigo;
    char desc[21];
    char ramo[11];
    productos *sig;
    lote *aba;
};

struct factura{
	int numfactura;
	int cantvendido;
	int dia;
	int mes;
	int anno;
	int ci;
	long int total;
	char desc[21];
	int numlote;
	int precio;
};

struct cliente{
	int ci;
	char nomapellido[20];
	char direc[15];
	int numerotlf[12];
	cliente *sig;
	factura *aba;
};

void insertarProductos(productos**p,char desc[20],char ramo[10],int cod){
		productos *t= new productos;
		strcpy(t->ramo,ramo);
		strcpy(t->desc,desc);
		t->codigo = cod;
		t->sig = *p;
		t->aba = NULL;
		*p = t;
}

void agregarProductos(productos **p){
	int cod; char desc[21],ramo[11];
	printf("\tNombre del producto.(descripcion):\n");
	printf("\t"); scanf("%s",&desc); printf(" \n");
	printf("\n\tRamo del producto:\n ");
	printf("\t"); scanf("%s",&ramo); printf(" \n");
	printf("\n\tCodigo del producto\n ");
	printf("\t"); scanf("%i",&cod); printf(" \n");
	insertarProductos(&*p,desc,ramo,cod);
}

void mostrarproductos(productos *p){
	productos *t = p;
	printf(" CAB-> ");
	while(p){
		printf("[%i,%s,%s]->",p->codigo,p->desc,p->ramo);
		p=p->sig;
	}
	printf(" NULL");
}

productos *buscarProducto(productos*p,int cod){
	productos*t=p;
	while(t){
		if(t->codigo == cod)
			return t;
		else 
			t=t->sig;
	}
	return NULL;
}

/*
void Ventas(productos*p){
	int cod,ci,uni;
	productos *t;
	printf(" \t Codigo del cliente (C.I): \n");
	scanf("%i",ci);
	//buscarcliente;
	while (cod){
		printf(" \t Inserte codigo del producto: \n ");
		printf("0.Listo.\n");
		scanf("%i",&cod);
		*t = buscarProducto(p,cod);
		if(t)
				//print("No existe el producto. \n");
		printf("\t Inserte unidades a vender. \n");
		scanf("%i",&uni);
		//vender();
	}
	
	
	
} */

/*void consultarporcodigo(productos *p, int codigo){
	productos *auxp=p;
	int igual;
	while (auxp){
		if(codigo==auxp->codigo){
			printf("\t"); printf(" El producto de codigo %i", codigo, "si se encuentra en existencia \n\n");
			lote *t=auxp->aba;
			while (t){
				printf("\t"); printf("El numero del lote del producto es %i", t->numlot, "\n");
				printf("\t"); printf("La cantidad del lote del producto es %i", t->cantidad, "\n\n");
				t=t->aba;
			}
			break;
		}
	}
	if (!auxp)
		printf("\t"); printf(" El producto de codigo %i", codigo, "no esta registrado \n\n");
}*/

void consultapornombre(productos *p, char produc1[]){
	productos *auxp=p;
	int igual=0;
	while (auxp){
       for (int i=0;produc1[i]!='\0'; i++){
          if(produc1[i]!=auxp->desc[i])
            igual=-1;
	   }
    if(igual==0){
		printf("\t"); printf("El codigo del producto %s", produc1);
		printf(" es %i",auxp->codigo);
		printf(" \n\n");
	    break;
	}
	auxp=auxp->sig;
	igual=0;
	}
	if (!auxp){
		printf("\t"); printf("El codigo del producto %s",produc1);
		printf(" no existe, \n");
	    printf("\t"); printf(" el producto %s",produc1);
		printf(" no esta registrado \n\n");
	}
}

void menuClientes(cliente **t){
    int op=-1;
    system("cls");
    while (op){
        printf("\t\tMENU CLIENTES. \n\n ");
        printf("\t1.Agregar cliente. \n ");
        printf("\t2.Consultar cliente. \n ");
        printf("\t3.Eliminar cliente. \n\n ");
        printf("\t0. Salir al menu principal.\n\n");
 
        printf("\t"); scanf("%i",&op);
       
        switch(op){
            case 1:
                    break;
            case 2:
                    break;
            case 3:
                    break;
        }
       
        system("pause");
        system("cls");
    }
}

void menuVentas(productos **p, cliente **t){
    int op=-1;
    system("cls");
    while (op){
        printf("\t\tMENU VENTAS. \n\n ");
        printf("\t1.Agregar/Hacer una venta. \n ");
        printf("\t2.Consultar venta. \n ");
        printf("\t3.Eliminar venta. \n\n ");
        printf("\t0. Salir al menu principal.\n\n");
 
        printf("\t"); scanf("%i",&op);
       
        switch(op){
            case 1:
                    break;
            case 2:
                    break;
            case 3:
                    break;
        }
       
        system("pause");
        system("cls");
    }
}
 
void menuConsultas(productos *p, cliente *t){
    int op=-1,cod;
	char nom[20]="\0";
    system("cls");
    while(op){
        printf("\t\tMENU CONSULTAS. \n\n ");
        printf("\t1.Consultar el codigo de un producto. \n ");
        printf("\t2.Consultar la exitencia de un producto. \n ");
        printf("\t3.Consultar las ventas de un producto entre dos fechas. \n ");
        printf("\t4.Consultar las ventas de un producto para un cliente. \n\n ");
        printf("\t0. Salir al menu principal.\n\n");
 
        printf("\t"); scanf("%i",&op);
 
        switch(op){
            case 1: printf(" \n"); printf("\tIngrese el Producto que desea consultar\n ");
				    printf("\t"); scanf("%s",&nom); printf(" \n");
					consultapornombre(p,nom);
                    break;
            case 2: printf("Ingrese el codigo del Producto que desea consultar\n ");
					/*funcion que revise si se encuentra ese codigo, de lo contrario, imprima que no existe"*/
                    break;
            case 3:
                    break;
			case 4: 
				    break;
        }
       
        system("pause");
        system("cls");
 
    }
}
 
void menuProductos(productos **p){
    int op=-1;
    system("cls");
    while(op){
        printf("\t\tMENU PRODUCTOS. \n\n ");
        printf("\t1.Agregar producto.\n ");
        printf("\t2.Agregar existencia de producto.\n ");
        printf("\t3.Consultar existencia de producto.\n ");
        printf("\t4.Modificar producto.\n ");
        printf("\t5.Eliminar producto.\n\n ");
        printf("\t0. Salir al menu principal.\n\n");
 
        printf("\t"); scanf("%i",&op);
       
        switch(op){
		    case 1: printf(" \n"); agregarProductos(p);
                    break;
            case 2:
                    break;
            case 3:
                    break;
            case 4:
                    break;
            case 5:
                    break;
        }
        system("pause");
        system("cls");
 
    }
}
 
void main(){
    int op=-1; productos *p = NULL;
	cliente *t=NULL;
    while (op){
        printf("\t\tMENU. \n\n ");
        printf("\t1.Productos.\n ");
        printf("\t2.Clientes.\n ");
        printf("\t3.Ventas.\n ");
        printf("\t4.Consultas.\n ");
        printf("\t5.Guardar/Cargar datos de archivo.\n\n");
        printf("\t0. Salir al menu principal.\n\n");
 
 
        printf("\t"); scanf("%i",&op);
 
        switch(op){
            case 1: menuProductos(&p);
				    break;
            case 2: menuClientes(&t);
                    break;
            case 3: menuVentas(&p,&t);
                    break;
            case 4: menuConsultas(p,t);
                    break;
            case 5:
                    break;
 
        }
        system("pause");
        system("cls");
    }
}
