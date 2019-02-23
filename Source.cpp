#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct lote{
	int numlot;
	int	mes;
	int dia;
	int anno;
	int precio;
	int cantidad;
	int exitencia;
	lote* sig;
};
struct productos{
	int codigo;
	char desc[21];
	char ramo[11];
	productos *sig;
	lote *aba;
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
	printf("\tNombre del producto.(descripcion):\n\t");
	scanf("%s",&desc);
	printf("\n\tRamo del producto:\n ");
	scanf("%s",&ramo);
	printf("\n\tCodigo del producto\n ");
	scanf("%i",&cod);
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

productos buscarProducto(productos*p,int cod){
	productos*t=p;
	while(t){
		if(t->codigo == cod)
			return *t;
		else 
			t=t->sig;
	}
	return *t;
};
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

void menuClientes(){
	int op=-1;
	system("cls");
	while (op){
		printf("\t\tMENU CLIENTES. \n\n ");
		printf("\t1.Agregar cliente. \n ");
		printf("\t2.Consultar cliente. \n ");
		printf("\t3.Eliminar cliente. \n\n ");
		printf("0. Salir al menu principal.\n\n");

		scanf("%i",&op);
		
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


void menuConsultas(){
	int op=-1;
	system("cls");
	while(op){
		printf("\t\tMENU CONSULTAS. \n\n ");
		printf("\t1.Consultar el codigo de un producto. \n ");
		printf("\t2.Consultar la exitencia de un producto. \n ");
		printf("\t3.Consultar las ventas de un producto entre dos fechas. \n ");
		printf("\t4.Consultar las ventas de un producto para un cliente. \n\n ");
		printf("0. Salir.\n\n");

		scanf("%i",&op);

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

void menuProductos(){
	int op=-1; productos *p=NULL;
	system("cls");
	while(op){
		printf("\t\tMENU PRODUCTOS. \n\n ");
		printf("\t1.Agregar producto.\n ");
		printf("\t2.Agregar existencia de producto.\n ");
		printf("\t3.Consultar existencia de producto.\n ");
		printf("\t4.Modificar producto.\n ");
		printf("\t5.Eliminar producto.\n\n ");
		printf("0. Salir al menu principal.\n\n");

		scanf("%i",&op);
		
		switch(op){
			case 1: agregarProductos(&p);
					mostrarproductos(p);
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
		system ("pause");
		system("cls");

	}
}

void main(){
	int op=-1;
	productos *p=NULL;
	while (op){
		printf("\t\tMENU. \n\n ");
		printf("\t1.Productos.\n ");
		printf("\t2.Clientes.\n ");
		printf("\t3.Ventas.\n ");
		printf("\t4.Consultas.\n ");
		printf("\t5.Guardar/Cargar datos de archivo.\n\n");
		printf("0. Salir. \n\n");


		scanf("%i",&op);

		switch(op){
			case 1: menuProductos();
					break;
			case 2: menuClientes();
					break;
			case 3:	
					break;
			case 4: menuConsultas();
					break;
			case 5:
					break;

		}
		system("pause");
		system("cls");
	}
}
