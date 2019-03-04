#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctime>

struct lote{
    int numlot;
    int mes;
    int dia;
    int anno;
    int cant;
    int exist;
    int precio;
    lote *aba;
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
    factura *aba;
};

struct cliente{
    int ci;
    cliente *sig;
    factura *aba;
};

void tiempo(){
    time_t tiemp;
    struct tm *info;
    time(&tiemp);
    info = localtime(&tiemp);
    printf("Fecha: %i/%i/%i\n",info->tm_mday,info->tm_mon,info->tm_year%100);
    printf("Hora:");
    
}

void insertarProductos(productos**p,char desc[20],char ramo[10],int cod){ //Inserta Producto por cabeza
    productos *t= new productos;
    strcpy(t->ramo,ramo);
    strcpy(t->desc,desc);
    t->codigo = cod;
    t->sig = *p;
    t->aba = NULL;
    *p = t;
}
int codRep(productos *p,int x){ //Arroja 1 si hay un codigo rep, 0 si no hay.
    while(p){
        if(p->codigo == x)
            return 1;
        p=p->sig;
    }
    return 0;
}

void agregarProductos(productos **p){
    int cod,f=0; char desc[21],ramo[11];    //tp1
    printf("\tNombre del producto.(descripcion):\n");
    printf("\t"); scanf("%s",&desc); printf(" \n");
    printf("\n\tRamo del producto:\n ");
    printf("\t"); scanf("%s",&ramo); printf(" \n");
    printf("\n\tCodigo del producto\n ");
    printf("\t");
    do{
        if(f) printf("\tCodigo en uso...\n\t");
        scanf("%i",&cod);
        f=1;
    }while(codRep(*p, cod));
    printf(" \n");
        
    insertarProductos(&*p,desc,ramo,cod);
}

void mostrarproductos(productos *p){ //Muestra los productos con su CODIGO,DESCRIPCION,RAMO.
    printf(" CAB-> ");
    while(p){
        printf("[%i,%s,%s]->",p->codigo,p->desc,p->ramo);
        p=p->sig;
    }
    printf(" NULL \n");
}

void mostrarSub(productos *p){ //Muestra la sub lista de un producto (p apunta al producto)
    if(p){
        lote*t = p->aba;
        printf("[%s] \n\t",p->desc);
        while(t){
            printf("[%i,%i]->",t->numlot,t->cant);
            t=t->aba;
        }
    }
    printf("[NULL] \n");
}

productos *buscarProducto(productos*p,int cod){ //Develve el apuntador del producto buscado por codigo
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

void consultarporcodigo(productos *p, int codigo){
    productos *auxp=p;
    bool cont=1;
    int cod=codigo;
    while (auxp){
        if(cod==auxp->codigo){
            printf("\t"); printf("El producto de codigo %i", cod); printf(" si se encuentra en existencia ");
            printf("\n\n ");
            lote *t=auxp->aba;
            while (t){
                printf("\t"); printf("El numero del lote del producto es %i", t->numlot);
                printf("\n ");
                printf("\t"); printf("La cantidad del lote del producto es %i", t->cant);
                printf("\n ");
                printf("\t"); printf("La existencia del lote de este producto es %i", t->exist);
                printf("\n\n ");
                t=t->aba;
            }
            cont=0;
        }
        auxp=auxp->sig;
    }
    if (cont){
        printf("\t"); printf(" El producto de codigo %i", cod); printf( " no esta registrado ");
        printf("\n\n ");
    }
}

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

void agregarcliente(cliente **p,int x){
    cliente *aux=new cliente;
    cliente *t=*p;
    aux->ci=x;
    if (!(*p)){
        *p=aux;
        (*p)->sig=NULL;
		(*p)->aba=NULL;
    }
    else{
        while (t && (t->ci!=aux->ci))
            t=t->sig;
        if (!t){
            aux->sig=*p;
            *p=aux;
			(*p)->aba=NULL;
        }
    }
    t=*p;
}

void consultarcliente(cliente **t, int ci){
	cliente *aux=*t;
	while (aux){
	   if (aux->ci==ci){
		 printf("\n\tEl cliente se encuentra registrado \n\n");
		 return;
	   }
	   else
		   aux=aux->sig;
	}
	printf("\n\tEl cliente no se encuentra registrado \n\n");
}

void mostrarcliente(cliente **t){
    cliente *o = *t;
    printf("\n\t Clientes-> ");
    while(o){
        printf("[%i]->",o->ci);
        o=o->sig;
    }
    printf("NULL \n\n");
}

lote *crearL(int dia,int mes, int anno,int cant, int precio){ //crea un lote (solo para insertar por cola)
    lote* t = new lote;
    t->dia = dia;
    t->mes = mes;
    t->anno = anno;
    t->cant = cant;
    t->exist = cant;
    t->precio = precio;
    t->aba = NULL;
    return t;
}
int contarl(lote*p){
    if (p){
        return contarl(p->aba)+1;
    }
    return 0;
}

void insertarL(productos*p,int cod){ //Inserta lote por cola.
    int dia,mes,anno,cant,precio;
    productos* t = buscarProducto(p,cod);
    if (t){
        lote* tt= t->aba;
        printf("\tIntroduzca Dia/Mes/Año : \n");
        printf("\tDia-> "); scanf("%i",&dia);
        printf("\tMes-> "); scanf("%i",&mes);
        printf("\tAño-> "); scanf("%i",&anno);
        printf("\n\tIntroduzca cantidad del lote: \n\t");
        scanf("%i",&cant);
        printf("\tIntroduzca precio del lote: \n\t");
        scanf("%i",&precio);
        while (tt && tt->aba)
            tt= tt->aba;
        if (tt){
            tt->aba = crearL(dia,mes,anno,cant,precio);
            tt->aba->numlot = contarl(p->aba);
        }
        else{
            t->aba = crearL(dia,mes,anno,cant,precio);
            t->aba->numlot = 1;
        }
    }
    else
        printf("\tProducto no encontrado... (Codigo errado) \n ");
    
}

int existenciaP(productos*p){ //Suma de las existencia de los lotes
    int sum = 0;
    if (p){
        lote *t = p->aba;
        while (t){
            sum += t->exist;
            t=t->aba;
        }
    }
    return sum;
}

void elimSub(lote**p){
    lote * temp;
    while(*p){
        temp = (*p);
        (*p)=(*p)->aba;
        delete temp;
    }
    
}

void elimProducto(productos**p,int cod){
    productos* t = buscarProducto(*p, cod);
    if (t){
        if (t->codigo == (*p)->codigo){
            (*p)=(*p)->sig;
            elimSub(&(t->aba));
            delete t;
        }
        else {
            productos *aux = *p;
            while (aux->sig != t)
                aux = aux->sig;
            aux->sig = aux->sig->sig;
            delete t;
        }
        }
}

void insertarfactclientef(cliente **t, cliente *auxt, factura *we, factura *w){ /*adjunta las facturas al cliente fantasma*/
	cliente *re=auxt->sig;
	while (re->sig)
		re=re->sig;
	if (re->aba){
		we=re->aba;
		while (we->aba)
		  we=we->aba;
		we->aba=w;
	}
	else
		re->aba=w;
}


void eliminarcliente(cliente **t, int ci){
	cliente *auxt=(*t);
	factura *w=auxt->sig->aba, *we;
	cliente *te=auxt->sig;
	while (auxt && auxt->sig){
		if (auxt->sig->ci==ci){
			te=auxt->sig;
			auxt->sig=te->sig;
			delete te;
			if (w)
				insertarfactclientef(t,auxt,we,w);
			cliente *te=auxt->sig;
		}
		else
			auxt=auxt->sig;
	}
}


void menuClientes(cliente **t){
    int op=-1, x=0;
    system("cls");
    while (op){
        printf("\t\tMENU CLIENTES. \n\n ");
        printf("\t1.Agregar cliente. \n ");
        printf("\t2.Consultar cliente. \n ");
        printf("\t3.Eliminar cliente. \n\n ");
        printf("\t0. Salir al menu principal.\n\n");
        
        printf("\t"); scanf("%i",&op);
        
        switch(op){
            case 1: printf(" \n"); printf("\tIngrese el Codigo de Cliente que desea Agregar \n ");
                    printf("\t"); scanf("%i",&x); printf("\n ");
                    agregarcliente(t,x);
                    break;
            case 2: printf(" \n"); printf("\tIngrese el Codigo de Cliente que desea Consultar \n ");
                    printf("\t"); scanf("%i",&x); printf("\n ");
				    consultarcliente(t,x);
                    break;
            case 3: printf(" \n"); printf("\tIngrese el Codigo de Cliente que desea Eliminar \n ");
                    printf("\t"); scanf("%i",&x); printf("\n ");
                    eliminarcliente(t,x);
                    break;
			case 4: mostrarcliente(t);
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
                printf("\t"); scanf("%s",&nom[20]); printf(" \n");
                consultapornombre(p,nom);
                break;
            case 2: printf("\tIngrese el codigo del Producto que desea consultar\n ");
                /*funcion que revise si se encuentra ese codigo, de lo contrario, imprima que no existe"*/
                printf("\t"); scanf("%i",&cod); printf(" \n");
                consultarporcodigo(p,cod);
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


void menuModificar(productos *p,productos *cab){ //recordar que se pasa el apuntador ya apuntando al producto...
    int op = -1, cod;
    if (p){
        while (op){
            printf("\t\tMENU MODIFICAR. \n\n");
            printf("\t1.Cambiar descripcion(nombre).\n ");
            printf("\t2.Cambiar ramo.\n ");
            printf("\t3.Cambiar codigo.\n\n ");
            printf("\t0.Salir al menu de productos..\n\n");
        
            scanf("%i",&op);
        
            switch (op) {
                case 1:
                    printf("Descripcion actual-> %s \n",p->desc);
                    printf("Descripcion nueva-> "); scanf("%s",&(p->desc));
                    break;
                
                case 2:
                    printf("Ramo actual-> %s \n",p->ramo);
                    printf("Ramo nuevo-> "); scanf("%s",&(p->ramo));
                    break;
                
                case 3:
                    int f =0; /* el flag es para que no muestre el mensaje de cod rep en la primera
                               iteracion */
                    printf("Codigo actual-> %i \n",p->codigo);
                    printf("Codigo nuevo-> ");
                    do{
                        if(f) printf("Codigo repetido... \n");
                        scanf("%i",&(cod));
                        f = 1;
                    }while(codRep(cab,cod));
                    p->codigo = cod;
                    break;
            }
     
        
            system("pause");
            system("cls");
        }
    }
    else printf("Producto no encontrado (codigo errado)... \n");
}

void menuProductos(productos **p){
    int op=-1, cod; productos * xx = NULL;
    system("cls");
    while(op){
        printf("\t\tMENU PRODUCTOS. \n\n ");
        printf("\t1.Agregar producto.\n ");
        printf("\t2.Agregar existencia de producto.\n ");
        printf("\t3.Consultar existencia de producto.\n ");
        printf("\t4.Modificar producto.\n ");
        printf("\t5.Eliminar producto.\n ");
        printf("\t6.Mostrar lotes de un producto.\n ");
        printf("\t7.Mostrar Productos. \n\n");
        printf("\t0. Salir al menu principal.\n\n");
        
        
        printf("\t"); scanf("%i",&op);
        
        switch(op){
            case 1: printf(" \n"); agregarProductos(&*p);
                    break;
            case 2: printf("\tIndique el codigo del producto: \n\t");
                    scanf("%i",&cod);
                    insertarL(*p, cod);
                    break;
            case 6: printf("\tIndique el codigo del producto: \n\t");
                    scanf("%i",&cod);
                    xx = buscarProducto(*p, cod);
                    mostrarSub(xx);
                    break;  //Esta funcion no va aca es para ver si inserto bien en la sublista
                             //deberia salir [NOMBRE] <-producto
                              //                  [numero de existencia]->...
                
            case 3: printf("\tIndique el codigo del producto: \n\t");
                    scanf("%i",&cod);
                    xx = buscarProducto(*p, cod);
                    if (xx)
                        printf("\tHay %i unidades de %s \n",existenciaP(xx),xx->desc);
                    break;
            case 4: printf("\tIndique el codigo del producto: \n\t");
                    scanf("%i",&cod);
                    xx = buscarProducto(*p, cod);
                    menuModificar(xx,*p);
                    break;
            case 5: printf("\tIndique el codigo del producto: \n\t");
                    scanf("%i",&cod);
                    elimProducto(&*p,cod);
                    break;
            case 7: mostrarproductos(*p);
                    break;
        }
        system("pause");
        system("cls");
        
    }
}
void main(){
    int op=-1; productos *p = NULL;
    cliente *t= NULL;
    while (op){
        printf("\t\tMENU. \n\n ");
        printf("\t1.Productos.\n ");
        printf("\t2.Clientes.\n ");
        printf("\t3.Ventas.\n ");
        printf("\t4.Consultas.\n ");
        printf("\t5.Guardar/Cargar datos de archivo.\n\n");
        printf("\t0. Salir.\n\n");
	printf("\t\t");
        tiempo();
        
        
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
