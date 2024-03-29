
// Iliana Dias C.I:26.819.056
// Arturo Lecuona C.I: 27.588.221
//Proyecto de Algoritmos y Proramacion 2 VERANO
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
    int codlote;
    lote *aba;
};


struct productos{
    int codigo;
    char desc[20];
    char ramo[30];
    productos *sig;
    lote *aba;
};

struct factura{
    int numfactura;
    int cantvendido;
    int dia;
    int mes;
    int anno;
    int codproduc;
    long int total;
    char desc[21];
    int codfac;
    int precio;
    factura *aba;
};

struct cliente{
    long int ci;
    cliente *sig;
    factura *aba;
};

void tiempo(){
    char buffer[26];
    time_t tiemp;
    struct tm *info;
    time(&tiemp);
    info = localtime(&tiemp);
    printf("Fecha: %i/%i/%i\n",info->tm_mday,info->tm_mon+1,info->tm_year%100);
    strftime(buffer, 26, "%H:%M",info);
    printf("\t\t\t\t\t\t Hora:   %s\n",buffer);
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
    int cod,f=0; char desc[21],ramo[30];    //tp1
    printf("\n\tCodigo del Producto\n ");
    do{
        if(f) printf("\tCodigo en uso...\n");
        printf("\tCodigo->");
        scanf("%i",&cod);
        f=1;
    }while(codRep(*p, cod));
    printf(" \n");
    printf("\tDescripcion del Producto:\n");
    printf("\t"); scanf("\n"); gets(desc);  //scanf("%s",&desc); printf(" \n");
    printf("\n\tRamo del Producto:\n ");
    printf("\t"); scanf("\n"); gets(ramo);  //scanf("%s",&ramo); printf(" \n");
    
    
    insertarProductos(&*p,desc,ramo,cod);
}

void mostrarproductos(productos *p){ //Muestra los productos con su CODIGO,DESCRIPCION,RAMO.
    printf(" \tProductos-> ");
    while(p){
        printf("[%i,%s,%s]->",p->codigo,p->desc,p->ramo);
        p=p->sig;
    }
    printf(" NULL \n\n");
}

void mostrarSub(productos *p){ //Muestra la sub lista de un producto (p apunta al producto)
    if(p){
        lote*t = p->aba;
        printf("[%s] \n\t",p->desc);
        while(t){
            printf("[%i,%i/%i]->",t->numlot,t->exist,t->cant);
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


void consultarporcodigo(productos *p, int codigo){ //--
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

void consultapornombre(productos *p, char produc1[]){ //--
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
void restar_lote(lote*p, int cant){ //en pruebas
    if(p){
        int exist = p->exist;
        
        while (cant != 0 && p){
            (p)->exist = exist - cant;
            if (p->exist < 0){
                cant=(p)->exist * -1;
                (p)->exist = 0;
                p=(p)->aba;
            }
            else
                cant = 0;
        }
    }
}



void agregarcliente(cliente **p,int x){ //--
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

void consultarcliente(cliente **t, int ci){ //--
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

void mostrarcliente(cliente **t){ //--
    cliente *o = *t;
    printf("\n\t Clientes-> ");
    while(o){
        printf("[%li]->",o->ci);
        o=o->sig;
    }
    printf("NULL \n\n");
}

void mostrara(factura *t){ //--
    factura *o = t;
    printf("\n\t copia-> ");
    while(o){
        printf("[%i]->",o->numfactura);
        o=o->aba;
    }
    printf("NULL \n\n");
}



lote *crearL(int dia,int mes, int anno,int cant, int precio,int codlote,int exist){ //crea un lote (solo para insertar por cola)
    lote* t = new lote;
    t->dia = dia;
    t->mes = mes;
    t->anno = anno;
    t->cant = cant;
    t->exist = exist;
    t->precio = precio;
    t->codlote = codlote;
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
    time_t tiemp;
    tm *info;
    time(&tiemp);
    info = localtime(&tiemp);
    int dia=info->tm_mday,mes=info->tm_mon+1,anno=info->tm_year%100,cant=0,precio=0,op=-1,codlote = 0,exist=0;
    productos* t = buscarProducto(p,cod);
    
    if (t){
        lote* tt= t->aba;
        while (op){
            printf("\tInsertar fecha: \n");
            printf("\t1.Fecha de hoy. (Automatico).\n");
            printf("\t2.Establecer fecha (Manual).\n\n");
            
            printf("\t"); scanf("%i",&op); printf("\n");
            
            switch (op) {
                case 1:
                    printf("\tIntroduzca cantidad del lote de %s: \n",t->desc);
                    do{
                        printf("\tCantidad-> "); scanf("%i",&cant);
                    }while(cant <=0);
                    printf("\n\tIntroduzca existencia del lote: \n");
                    do{
                        printf("\tExistencia-> "); scanf("%i",&exist);
                    }while(exist<=0 || exist>cant );
                    printf("\tIntroduzca precio del lote de %s: \n",t->desc);
                    do{
                        printf("\tPrecio-> "); scanf("%i",&precio);
                    }while(precio <= 0);
                    printf("\n\tIntroduzca numero del lote de %s:\n",t->desc);
                    scanf("%i",&codlote);
                    
                    while (tt && tt->aba)
                        tt= tt->aba;
                    if (tt){
                        tt->aba = crearL(dia,mes,anno,cant,precio,codlote,exist);
                        tt->aba->numlot = contarl(tt->aba);
                    }
                    else{
                        t->aba = crearL(dia,mes,anno,cant,precio,codlote,exist);
                        t->aba->numlot = 1;
                    }
                    break;
                    
                case 2:
                    printf("\tIntroduzca Dia/Mes/Anno : \n");
                    do{
                        printf("\tDia-> "); scanf("%i",&dia);
                    }while (dia<=0 || dia>=32);
                    do{
                        printf("\tMes-> "); scanf("%i",&mes);
                    }while(mes<=0 || mes>=13);
                    do{
                        printf("\tAnno-> "); scanf("%i",&anno);
                    }while(anno<=0 || anno>99);
                    printf("\n\tIntroduzca cantidad del lote de %s: \n",t->desc);
                    do{
                        printf("\tCantidad-> "); scanf("%i",&cant);
                    }while(cant <=0);
                    printf("\n\tIntroduzca existencia del lote: \n");
                    do{
                        printf("\tExistencia-> "); scanf("%i",&exist);
                    }while(exist<=0 || exist>cant );
                    printf("\n\tIntroduzca precio del lote de %s: \n",t->desc);
                    do{
                        printf("\tPrecio-> "); scanf("%i",&precio);
                    }while(precio <= 0);
                    printf("\n\tIntroduzca numero del lote de %s:\n",t->desc);
                    scanf("%i",&codlote);
                    while (tt && tt->aba)
                        tt= tt->aba;
                    if (tt){
                        tt->aba = crearL(dia,mes,anno,cant,precio,codlote,exist);
                        tt->aba->numlot = contarl(p->aba);
                    }
                    else{
                        t->aba = crearL(dia,mes,anno,cant,precio,codlote,exist);
                        t->aba->numlot = 1;
                    }
                    break;
            }
            system("pause");
            system("cls");
            break;
        }
    }
    else
        printf("\tProducto no encontrado... (Codigo errado)\n\n ");
    
}

void insertarfactura(long int ci, cliente *t, factura *nue){ //--
    cliente *auxt=t;
    factura *aux=t->aba;
    while (auxt->ci!=ci)
        auxt=auxt->sig;
    aux=auxt->aba;
    if (!aux)
        auxt->aba=nue;
    else{
        while (aux->aba)
            aux=aux->aba;
        aux->aba=nue;
    }
}

cliente *buscarCliente(cliente *t, long int ci){ //--
    cliente *aux=t;
    while (aux){
        if (aux->ci==ci)
            return aux;
        else
            aux=aux->sig;
    }
    return NULL;
}

int calculo_precio(int cant, int precio){
    int y;
    y=((precio*30)/100)+precio;
    return cant*y;
}

void insertarDetalle(cliente *t, productos *p,int cant,int dia, int mes, int anno,int numfac, char desc[20],int codfac){ // t parado en cliente y p en el prducto que quiere comprar
    if(p->aba){
        factura* nuevo = new factura;
        nuevo->cantvendido = cant;
        nuevo->numfactura = numfac;
        nuevo->codfac = codfac;
        strcpy(nuevo->desc, desc);
        nuevo->dia = dia;
        nuevo->mes = mes;
        // nuevo->numlote = codlote;
        nuevo->anno = anno%100;
        nuevo->codproduc = p->codigo;
        nuevo->precio = calculo_precio(cant, p->aba->precio);
        nuevo->aba = NULL;
        insertarfactura(t->ci, t, nuevo);
    }
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
void fecha(int *dia,int *mes, int *anno){
    int op;
    time_t tiemp;
    tm *info;
    time(&tiemp);
    info = localtime(&tiemp);
    printf("\t1.Fecha de hoy. (Automatico).\n");
    printf("\t2.Establecer fecha. (Manual).\n\n");
    
    printf("\t"); scanf("%i",&op); printf("\n");
    
    switch (op) {
        case 1: *dia=info->tm_mday;
            *mes=info->tm_mon+1;
            *anno=info->tm_year;
            break;
            
        case 2: printf("\tIntroduzca Dia/Mes/Anno : \n");
            printf("\tDia->");scanf("%i",dia);
            printf("\tMes->");scanf("%i",mes);
            printf("\tAnno->");scanf("%i",anno); printf("\n");
            break;
    }
}
void mostrarF(cliente*p){
    int nf=0,f=1;
    if(p){
        factura*t = p->aba;
        printf("[%li]\n",p->ci);
        while(t){
            printf("\t-------------------------\n");
            if(f){
                nf = t->numfactura;
                printf("\tFecha: %i/%i/%i\n ",t->dia,t->mes,t->anno%100);
                printf("\tFactura[%i]\n",t->numfactura);
                printf("\tNumero de factura[%i]\n",t->codfac);
                f=0;
            }
            printf("\tProducto:[%i][%s]\n",t->codproduc,t->desc);
            printf("\tCantidad:[%i]\n",t->cantvendido);
            printf("\tPrecio x %i :[%i]\n",t->cantvendido,t->precio);
            if(!t->aba || t->aba->numfactura != t->numfactura)
                printf("\tTOTAL: [%li]\n\t-------------------------\n",t->total);
            t=t->aba;
            if (t && t->numfactura != nf)
                f=1;
        }
        
    }
}

int buscarnumfactura(cliente *t){
    int x=0;
    cliente *aux=t;
    factura *b=t->aba;
    
    while (aux){
        while (b){
            if (b->numfactura>x)
                x=b->numfactura;
            else
                b=b->aba;
        }
        aux=aux->sig;
        if (aux)
            b=aux->aba;
    }
    return x;
}

int calcular_total(cliente *t,int numfac){
    int total=0, x;
    factura *p =t->aba;
    while(p){
        if (p->numfactura==numfac)
            total+=p->precio;
        p= p->aba;
    }
    return total;
}


void venta(cliente *t, productos **p){
    long int ci;
    int numfac,op=-1,f=0,cant=existenciaP(*p)+1,dia,mes,anno,cod,total=0,codfac =0;
    cliente *bc;
    productos *bp;
    printf("\tCodigo de cliente:\n");
    printf("\t");scanf("%li",&ci); printf("\n");
    bc = buscarCliente(t, ci);
    if (bc){
        numfac = buscarnumfactura(t) + 1;
        printf("\tInserte codigo de factura: \n");
        scanf("%i",&codfac);
        while (op){
            printf("\t\tFACTURA: \n");
            printf("\t1.Agregar Producto a factura.\n");
            printf("\t0.Terminar Factura (Vender).\n\n");
            
            printf("\t"); scanf("%i",&op); printf("\n");
            
            switch (op) {
                case 1:
                    printf("\tInsertar codigo del producto a vender: \n");
                    printf("\t"); scanf("%i",&cod);
                    bp = buscarProducto(*p, cod);
                    if(bp){
                        cant=existenciaP(bp)+1;
                        printf("\tInsertar cantidad a vender de %s\n",bp->desc);
                        while(cant > existenciaP(bp)){
                            if (f) printf("\t Cantidad a vender superior a la existente-> %i\n",existenciaP(bp));
                            printf("\t"); scanf("%i",&cant); printf("\n");
                            f=1;
                        }
                        f=0;
                        
                        printf("\tIntroducir fecha:\n");
                        fecha(&dia,&mes,&anno);
                        
                        
                        if(existenciaP(bp) > 0){
                            insertarDetalle(bc, bp,cant, dia, mes, anno, numfac,bp->desc,codfac); //agregar cod lote si se borran los lotes vacios..
                            restar_lote((bp->aba), cant);
                        }
                        //actualizar fecha.
                        //actualizar precio.
                    }
                case 0: total = calcular_total(bc,numfac);
                    factura*tt=bc->aba;
                    while (tt){
                        if (tt->numfactura==numfac)
                            tt->total = total;
                        tt=tt->aba;
                    }
                    break;
            }
        }
    }
}



void elimSub(lote**p){
    lote * temp;
    while(*p){
        temp = (*p);
        (*p)=(*p)->aba;
        delete temp;
    }
    
}

void elimSubC(factura **q){
    factura * temp;
    while(*q){
        temp = (*q);
        *q = (*q)->aba;
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

void elimfacturaproduct(cliente *t, int cod){
    cliente *ka=t;
    factura *aux=NULL;
    factura *temp=NULL;
    while (ka){
        while ((ka->aba) && (ka->aba->codproduc==cod)){
            temp=ka->aba;
            ka->aba=temp->aba;
            delete temp;
            factura *temp=NULL;
        }
        aux=ka->aba;
        while (aux){
            if ((aux->aba)&&(aux->aba->codproduc==cod)){
                temp=aux->aba;
                aux->aba=temp->aba;
                delete temp;
                factura *temp=NULL;
            }
            else
                aux=aux->aba;
        }
        ka=ka->sig;
    }
}

void mostrarfactura(factura *q, int cod){
    int nf=0,f=1;
    if (q->codproduc==cod){
        printf("\t-------------------------\n");
        if(f){
            nf = q->numfactura;
            printf("\tFecha: %i/%i/%i\n ",q->dia,q->mes,q->anno%100);
            printf("\tFactura[%i]\n",q->numfactura);
            f=0;
        }
        printf("\tProducto:[%i][%s]\n",q->codproduc,q->desc);
        printf("\tCantidad:[%i]\n",q->cantvendido);
        printf("\tPrecio x %i :[%i]\n",q->cantvendido,q->precio);
        if(!q->aba || q->aba->numfactura != q->numfactura)
            printf("\tTOTAL: [%li]\n",q->total);
        q=q->aba;
        if (q && q->numfactura != nf)
            f=1;
    }
}


void consultarventasproducliente(cliente *t, int cod, long int ci){
    cliente *aux=t;
    factura *tem=t->aba, *rep=t->aba;
    mostrara(tem);
    while ((aux) && (aux->ci!=ci))
        aux=aux->sig;
    if (!aux)
        printf("\tEl cliente NO existe\n ");
    if (aux){
        tem=aux->aba;
        rep=aux->aba;
        if (tem){
            while (tem->aba)
                tem=tem->aba;
            while (tem!=aux->aba){
                while (rep->aba!=tem)
                    rep=rep->aba;
                if (tem->codproduc==cod){
                    mostrarfactura(tem,cod);
                    tem=rep;
                    rep=aux->aba;
                }
                else{
                    tem=rep;
                    rep=aux->aba;
                }
            }
            if ((tem==aux->aba) && (aux->aba->codproduc==cod))
                mostrarfactura(tem,cod);
        }
        else
            printf("\tEl cliente NO posee Facturas\n ");
    }
}

void imprimirenorden(cliente *t,factura *as){ //--
    factura *aux=as;
    int x=buscarnumfactura(t);
    while (x){
        while (aux){
            if (aux->numfactura==x){
                mostrarfactura(aux,aux->codproduc);
                aux=aux->aba;
            }
            else
                aux=aux->aba;
        }
        x--;
        aux=as;
    }
}

factura *crearpopaux(factura *tem){ //--
    factura *pop=new factura;
    pop->anno=tem->anno;
    pop->dia=tem->dia;
    pop->mes=tem->mes;
    pop->cantvendido=tem->cantvendido;
    pop->codproduc=tem->codproduc;
    pop->numfactura=tem->numfactura;
    pop->codfac=tem->codfac;
    pop->precio=tem->precio;
    pop->total=tem->total;
    strcpy(pop->desc, tem->desc);
    return pop;
}

void consultarventassinfecha(cliente *t, int cod){
    cliente *aux=t;
    factura *tem=t->aba;
    factura *yu=NULL;
    factura *yuaux=NULL;
    factura *as=NULL;
    while (aux){
        while (tem){
            if (tem->codproduc==cod){
                as=crearpopaux(tem);
                if (!yu){
                    yu=as;
                    yu->aba=NULL;
                }
                else {
                    yuaux=yu;
                    while (yuaux->aba)
                        yuaux=yuaux->aba;
                    yuaux->aba=as;
                    yuaux=yuaux->aba;
                }
                tem=tem->aba;
            }
            else
                tem=tem->aba;
        }
        aux=aux->sig;
        if (aux)
            tem=aux->aba;
    }
    if (yuaux)
        yuaux->aba=NULL;
    imprimirenorden(t,yu);
}

void consultarporfecha(cliente *t, int dia, int mes, int anno, int dia1, int mes1, int anno1, int cod){
    cliente *aux=t;
    factura *tem=t->aba;
    factura *yu=NULL;
    factura *yuaux=NULL;
    factura *as=NULL;
    while (aux){
        while (tem){
            if (((tem->dia>=dia) && (tem->mes>=mes) && (tem->anno>=anno)) && ((tem->dia<=dia1) && (tem->mes<=mes1) && (tem->anno<=anno1))){
                if (tem->codproduc==cod){
                    as=crearpopaux(tem);
                    if (!yu){
                        yu=as;
                        yu->aba=NULL;
                    }
                    else {
                        yuaux=yu;
                        while (yuaux->aba)
                            yuaux=yuaux->aba;
                        yuaux->aba=as;
                        yuaux=yuaux->aba;
                    }
                    tem=tem->aba;
                }
            }
            else
                tem=tem->aba;
        }
        aux=aux->sig;
        if (aux)
            tem=aux->aba;
    }
    if (yuaux)
        yuaux->aba=NULL;
    imprimirenorden(t,yu);
}

void menufecha(cliente *t, int cod){
    int op=-1, dia,mes,anno,dia1,mes1,anno1;
    system("cls");
    while (op){
        printf("\tDesea especificar un rango de fechas? \n\n ");
        printf("\t1.SI. \n ");
        printf("\t2.NO. \n ");
        printf("\t0. Salir al menu Consultas.\n\n");
        
        printf("\t"); scanf("%i",&op); printf("\n");
        
        switch(op){
            case 1: printf("\tPrimera Fecha(inicial): \n");
                printf("\tIntroduzca Dia/Mes/Anno : \n");
                do{
                    printf("\tDia-> "); scanf("%i",&dia);
                } while (dia<0 || dia>32);
                do{
                    printf("\tMes-> "); scanf("%i",&mes);
                } while (mes<0 || mes>13);
                do{
                    printf("\tAnno-> "); scanf("%i",&anno);
                } while (anno<0||anno>99);
                printf("\n\tSegunda Fecha(final): \n");
                printf("\tIntroduzca Dia/Mes/Anno : \n");
                do{
                    printf("\tDia-> "); scanf("%i",&dia1);
                } while (dia<0 || dia>32);
                do{
                    printf("\tMes-> "); scanf("%i",&mes1);
                } while (mes<0 || mes>13);
                do{
                    printf("\tAnno-> "); scanf("%i",&anno1);
                } while (anno1<0||anno1>99);
                consultarporfecha(t,dia,mes,anno,dia1,mes1,anno1,cod); printf("\n");
                break;
                
            case 2: consultarventassinfecha(t,cod); printf("\n");
                break;
        }
        system("pause");
        system("cls");
    }
}

cliente *crearclientef(cliente *re){
    cliente *wen=new cliente;
    wen->ci=0;
    wen->sig=NULL;
    wen->aba=NULL;
    return wen;
}

void insertarfactclientef(cliente **t, factura *we){ /*adjunta las facturas al cliente fantasma*/ //--
    cliente *re=(*t)->sig;
    factura *pew=(*t)->aba;
    while (re->sig){
        if (re->ci==0)
            break;
        re=re->sig;
    }
    if (re->ci!=0){
        re->sig=crearclientef(re);
        re=re->sig;
    }
    if (re->aba){
        pew=re->aba;
        while (pew->aba)
            pew=pew->aba;
        pew->aba=we;
    }
    else
        re->aba=we;
}



void eliminarcliente(cliente **t, int ci){
    cliente *auxt=*t;
    factura *w=auxt->sig->aba, *we=NULL;
    cliente *te=auxt->sig;
    while (auxt && auxt->sig){
        if (auxt->sig->ci==ci){
            if (w)
                insertarfactclientef(t,w);
            te=auxt->sig;
            w=auxt->sig->aba;
            auxt->sig=te->sig;
            delete te;
            cliente *te=auxt->sig;
            if (auxt->aba)
                w=te->aba;
        }
        else
            auxt=auxt->sig;
    }
    if ((*t)->ci==ci){
        if ((*t)->aba)
            insertarfactclientef(t,(*t)->aba);
        te=*t;
        *t=(*t)->sig;
        delete te;
    }
}


void menuClientes(cliente **t){ //--
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
                printf("\t"); scanf("%i",&x);
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

void menuVentas(productos **p, cliente *t){ //--
    int op=-1;
    long int ci ;
    system("cls");
    while (op){
        printf("\t\tMENU VENTAS. \n\n ");
        printf("\t1.Agregar/Hacer una venta. \n ");
        printf("\t2.Consultar venta. \n\n ");
        printf("\t0. Salir al menu principal.\n\n");
        
        printf("\t"); scanf("%i",&op); printf("\n");
        
        switch(op){
            case 1: venta(t, &*p);
                system("cls");
                break;
            case 2: printf("\tInsertar CI:\n\t"); //ver facturas de un cliente
                scanf("%li",&ci);
                cliente * xx = buscarCliente(t, ci);
                mostrarF(xx);
                break;
        }
        system("pause");
        system("cls");
    }
}

void elimSaltos(char *x){
    strcpy(&x[strlen(x)-1],"\0");
}

void menuConsultas(productos *p, cliente *t){ //--
    int op=-1,cod;
    long int ci;
    char nom[20];
    system("cls");
    while(op){
        printf("\t\tMENU CONSULTAS. \n\n ");
        printf("\t1.Consultar el codigo de un producto. \n ");
        printf("\t2.Consultar la exitencia de un producto. \n ");
        printf("\t3.Consultar las ventas de un producto entre dos fechas. \n ");
        printf("\t4.Consultar las ventas de un producto para un cliente. \n\n ");
        printf("\t0. Salir al menu principal.\n\n");
        
        printf("\t"); scanf("%i",&op); printf("\n");
        
        switch(op){
            case 1: printf(" \n"); printf("\tIngrese el Producto que desea consultar\n ");
                printf("\t"); scanf("%s",&nom); printf(" \n");
                consultapornombre(p,nom);
                break;
            case 2: printf("\tIngrese el codigo del Producto que desea consultar\n ");
                /*funcion que revise si se encuentra ese codigo, de lo contrario, imprima que no existe"*/
                printf("\t"); scanf("%i",&cod); printf(" \n");
                consultarporcodigo(p,cod);
                break;
            case 3: printf("\tIngrese el Codigo del Producto que desea consultar\n ");
                printf("\t"); scanf("%i",&cod); printf(" \n");
                menufecha(t,cod);
                break;
            case 4: printf("\tIngrese el Codigo del Producto que desea consultar\n ");
                printf("\t"); scanf("%i",&cod); printf(" \n");
                printf("\tIngrese el Codigo del del Cliente que desea consultar\n ");
                printf("\t"); scanf("%li",&ci); printf(" \n");
                consultarventasproducliente(t,cod,ci);printf("\n");
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
            
            printf("\t"); scanf("%i",&op); printf("\n");
            
            switch (op) {
                case 1: printf("\tDescripcion actual-> %s \n",p->desc);
                    printf("\tDescripcion nueva-> "); scanf("%s",&(p->desc)); printf("\n");
                    break;
                    
                case 2: printf("\tRamo actual-> %s \n",p->ramo);
                    printf("\tRamo nuevo-> "); scanf("%s",&(p->ramo)); printf("\n");
                    break;
                    
                case 3: int f =0; /* el flag es para que no muestre el mensaje de cod rep en la primera
                                   iteracion */
                    printf("\tCodigo actual-> %i \n",p->codigo);
                    printf("\tCodigo nuevo-> ");
                    do{
                        if(f) printf("\n\tCodigo repetido... \n");
                        printf("\t"); scanf("%i",&(cod));
                        f = 1;
                    } while(codRep(cab,cod));
                    p->codigo = cod; printf("\n");
                    break;
            }
            system("pause");
            system("cls");
        }
    }
    else printf("\n\tProducto no encontrado (codigo errado)... \n\n");
}


void menuProductos(productos **p,cliente *t){
    int op=-1, cod;
    productos * xx = NULL;
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
        
        
        printf("\t"); scanf("%i",&op); printf(" \n");
        
        switch(op){
            case 1: agregarProductos(&*p); printf(" \n");
                break;
            case 2: printf("\tIndique el codigo del producto: \n\t");
                scanf("%i",&cod); printf(" \n");
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
                xx = buscarProducto(*p, cod); printf("\n");
                if (xx)
                    printf("\tHay %i unidades de %s \n\n",existenciaP(xx),xx->desc);
                break;
            case 4: printf("\tIndique el codigo del producto: \n\t");
                scanf("%i",&cod);
                xx = buscarProducto(*p, cod);
                system("cls");
                menuModificar(xx,*p);
                break;
            case 5: printf("\tIndique el codigo del producto: \n\t");
                scanf("%i",&cod);
                elimProducto(&*p,cod);
                elimfacturaproduct(t,cod); printf("\n");
                break;
            case 7: mostrarproductos(*p);
                break;
        }
        system("pause");
        system("cls");
        
    }
}
int guardarP(productos *p){
    FILE *apun;
    
    apun = fopen("cargarP.txt", "w");
    lote *t;
    if (apun){
        while(p){
            t= p->aba;
            fprintf(apun,"%i\n%s\n%s\n",p->codigo,p->desc,p->ramo);
            if(t)
                fprintf(apun,"0\n");
            else
                fprintf(apun,"-1");
            while(t){
                fprintf(apun,"%i\n%i\n%i\n%i\n%i\n%i\n%i\n%i\n",t->dia,t->mes,t->anno,t->exist,t->cant,t->numlot,t->precio,t->codlote);
                t=t->aba;
                if(t)
                    fprintf(apun, "0\n");
                else
                    fprintf(apun, "-1");
            }
            fprintf(apun, "\n");
            p=p->sig;
            if (p)
                fprintf(apun, "0\n");
            else
                fprintf(apun, "-1\n");
        }
        fclose(apun);
        return 1;
    }
    return 0;
}

int guardarC(cliente *p){
    FILE *apun;
    
    apun = fopen("cargarC.txt", "w"); //Cambiar ruta...
    factura *t;
    if (apun){
        while(p){
            t= p->aba;
            fprintf(apun,"%li\n",p->ci);
            if(t)
                fprintf(apun,"0\n");
            else
                fprintf(apun,"-1");
            while(t){
                fprintf(apun,"%i\n%i\n%i\n%i\n%i\n%i\n%i\n%li\n%i\n%s\n",t->dia,t->mes,t->anno,t->numfactura,t->cantvendido,t->codfac,t->precio,t->total,t->codproduc,t->desc);
                t=t->aba;
                if(t)
                    fprintf(apun, "0\n");
                else
                    fprintf(apun, "-1");
            }
            fprintf(apun, "\n");
            p=p->sig;
            if (p)
                fprintf(apun, "0\n");
            else
                fprintf(apun, "-1\n");
        }
        fclose(apun);
        return 1;
    }
    return 0;
}


void borrarproductos(productos**t){
    productos *aux;
    while(*t){
        aux = *t;
        elimSub(&(*t)->aba);
        *t = (*t)->sig;
        delete aux;
    }
}

void borrarclientes(cliente **t){
    cliente *aux;
    while(*t){
        aux = *t;
        elimSubC(&(*t)->aba);
        *t = (*t)->sig;
        delete aux;
    }
}

int CargarC(cliente **q){
    FILE *apun;
    char buffer[100];
    int ctrl = 0;
    apun = fopen("cargarC.txt", "r");//    char ruta[]; scanf("%s",&ruta);       fopen(ruta, "r");
    if (apun){
        borrarclientes(&*q);
        fscanf(apun, "\n");
        while(!feof(apun)){
            while(!ctrl){
                cliente * t = new cliente;
                t->sig = *q;
                t->aba = NULL;
                (*q) = t;
                fgets(buffer, 100, apun); //codigo
                t->ci = atol(buffer);
                fgets(buffer, 100, apun);
                ctrl = atoi(buffer);
                while (!ctrl){
                    factura*tt = new factura;
                    if (!t->aba)
                        t->aba = tt;
                    else{
                        factura *aux = t->aba;
                        while(aux->aba)
                            aux = aux->aba;
                        aux->aba = tt;
                    }
                    tt->aba = NULL;
                    fgets(buffer, 100, apun); //fprintf(apun,"%i\n%i\n%i\n%i\n%i\n%i\n%i\n%li\n",t->dia,t->mes,t->anno,t->numfactura,t->cantvendido,t->numlote,t->precio,t->total,t->codigo,t->desc);
                    tt->dia = atoi(buffer);
                    fgets(buffer, 100, apun);
                    tt->mes = atoi(buffer);
                    fgets(buffer, 100, apun);
                    tt->anno = atoi(buffer);
                    fgets(buffer, 100, apun);
                    tt->numfactura = atoi(buffer);
                    fgets(buffer, 100, apun);
                    tt->cantvendido = atoi(buffer);
                    fgets(buffer, 100, apun);
                    tt->codfac = atoi(buffer);
                    fgets(buffer, 100, apun);
                    tt->precio = atoi(buffer);
                    fgets(buffer, 100, apun);
                    tt->total = atol(buffer);
                    fgets(buffer,100,apun);
                    tt->codproduc = atoi(buffer);
                    fgets(buffer, 100, apun);
                    strcpy(tt->desc, buffer);
                    fgets(buffer,100,apun);
                    ctrl = atoi(buffer);
                    elimSaltos(tt->desc);
                }
                fgets(buffer, 100, apun);
                ctrl = atoi(buffer);
                fscanf(apun, "\n");
            }
            
            fscanf(apun,"\n");
        }
        fscanf(apun,"\n");
        fclose(apun);
    }
    return 0;
}


int CargarP(productos **q){
    FILE *apun;
    int val;
    char buffer[100];
    int ctrl = 0;
    apun = fopen("cargarP.txt", "r");
    if (apun){
        borrarproductos(&*q);
        fscanf(apun, "\n");
        while(!feof(apun)){
            while(!ctrl){
                productos * t = new productos;
                t->sig = *q;
                t->aba = NULL;
                (*q) = t;
                fgets(buffer, 100, apun); //codigo
                val = atoi(buffer);
                t->codigo = val;
                fgets(buffer, 100, apun); //desc
                elimSaltos(buffer);
                strcpy(t->desc, buffer);
                fgets(buffer, 100, apun); //ramo
                strcpy(t->ramo, buffer);
                
                //fgets(buffer, 100, apun);
                //elimSaltos(buffer);
                //strcpy(t->desc, buffer);
                fgets(buffer, 100, apun);
                ctrl = atoi(buffer);
                elimSaltos(t->ramo);
                while (!ctrl){
                    lote*tt = new lote;
                    if (!t->aba)
                        t->aba = tt;
                    else{
                        lote *aux = t->aba;
                        while(aux->aba)
                            aux = aux->aba;
                        aux->aba = tt;
                    }
                    tt->aba = NULL;
                    fgets(buffer, 100, apun); //fprintf(apun,"%i\n%i\n%i\n%i\n%i\n",t->dia,t->mes,t->anno,t->exist,t->cant,t->numlote);
                    val = atoi(buffer); tt->dia=val;
                    fgets(buffer, 100, apun);
                    val = atoi(buffer); tt->mes=val;
                    fgets(buffer, 100, apun);
                    val = atoi(buffer); tt->anno=val;
                    fgets(buffer, 100, apun);
                    val = atoi(buffer); tt->exist=val;
                    fgets(buffer, 100, apun);
                    val = atoi(buffer); tt->cant=val;
                    fgets(buffer, 100, apun);
                    val = atoi(buffer); tt->numlot = val;
                    fgets(buffer, 100, apun);
                    val = atoi(buffer); tt->precio = val;
                    fgets(buffer,100,apun);
                    val =atoi(buffer); tt->codlote = val;
                    fgets(buffer,100,apun);
                    ctrl = atoi(buffer);
                }
                fgets(buffer, 100, apun);
                ctrl = atoi(buffer);
                fscanf(apun, "\n");
            }
            
            fscanf(apun,"\n");
        }
        fscanf(apun,"\n");
        fclose(apun);
    }
    return 0;
}


void menuArch(productos **p, cliente **q){
    system("cls");
    int op = -1;
    
    printf("\t\tMENU ARCHIVOS. ");tiempo();
    printf("\t1.Guardar.\n ");
    printf("\t2.Cargar.\n\n ");
    printf("\t0.Salir al menu principal.\n");
    
    scanf("%i",&op);
    
    switch (op) {
        case 2: CargarP(&*p);
            CargarC(&*q);
            break;
            
        case 1:
            guardarP(*p);
            guardarC(*q);
            break;
    }
    
}

void cargar(productos **p, cliente**q){
    CargarP(p);
    CargarC(q);
}

int main(){
    
    int op=-1; productos *p = NULL;
    cliente *t= NULL;
    cargar(&p,&t);
    while (op){
        printf("\n\n\t\tMENU. \t\t\t ");tiempo();
        printf("\t1.Productos.\n ");
        printf("\t2.Clientes.\n ");
        printf("\t3.Ventas.\n ");
        printf("\t4.Consultas.\n ");
        printf("\t5.Guardar/Cargar datos de archivo.\n\n");
        printf("\t0. Salir.\n\n");
        
        
        printf("\t"); scanf("%i",&op);
        
        switch(op){
            case 1: menuProductos(&p,t);
                break;
            case 2: menuClientes(&t);
                break;
            case 3: menuVentas(&p,t);
                break;
            case 4: menuConsultas(p,t);
                break;
            case 5: menuArch(&p, &t);
                break;
                
                
        }
        system("pause");
        system("cls");
    }
    return 1;
}

