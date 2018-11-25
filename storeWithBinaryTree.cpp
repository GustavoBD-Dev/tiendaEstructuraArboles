#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <bits/stdc++.h>
using namespace std;
struct Music{
    int key;//tipo de dato
    string name;//tipo de dato, nombre de cancion
    double price;
    Music *der;
    Music *izq;
    Music *padre;
};
struct MusicBuy{
    int key;//tipo de dato
    string name;//tipo de dato, nombre de cancion
    double price;
    MusicBuy *der;
    MusicBuy *izq;
    MusicBuy *padreBuy;
};

//prootipos de arbol para las canciones
Music *crearNodo(Music*, int, string, double);
void insertarNodo(Music *&, Music *, int, string, double);
void mostrarArbol(Music *&, int);
void menu(int );
bool busqueda(Music *, int);
void eliminar(Music *, int);
void eliminarNodo(Music*);
Music *minimo(Music *);
void reemplazar(Music *, Music *);
void destruirNodo(Music *);
void postOrden(Music *);
//prototipos para arbol de canciones compradas
MusicBuy *crearNodoBuy(MusicBuy*, int, string, double);
void insertarNodoBuy(MusicBuy *&, MusicBuy *, int, string, double);
void mostrarArbolBuy(MusicBuy *&, int);
bool busquedaBuy(MusicBuy *, int);
void postOrdenBuy(MusicBuy *);
void change(Music *&, MusicBuy*&, int, int);

Music *arbol = NULL;
MusicBuy *arbolBuy = NULL;

int main(){
    int credit = 100;
    menu(credit);
    getch();
	return 0;
}//funcion pra crear un nuevo nodo
Music *crearNodo(Music *padre, int key, string name, double price){
    Music *nuevo_nodo = new Music();
    //asignamos los valores
    nuevo_nodo->key = key;
    nuevo_nodo->name = name;
    nuevo_nodo->price = price;
    nuevo_nodo->der = NULL;
    nuevo_nodo->izq = NULL;
    nuevo_nodo->padre = padre;
    return nuevo_nodo;
}
MusicBuy *crearNodoBuy(MusicBuy *padreBuy, int key, string name, double price){
    MusicBuy *nuevo_nodoBuy = new MusicBuy();
    //asignamos los valores
    nuevo_nodoBuy->key = key;
    nuevo_nodoBuy->name = name;
    nuevo_nodoBuy->price = price;
    nuevo_nodoBuy->der = NULL;
    nuevo_nodoBuy->izq = NULL;
    nuevo_nodoBuy->padreBuy = padreBuy;
    return nuevo_nodoBuy;
}
void insertarNodo(Music *&arbol,Music *padre, int key, string name, double price){
    if(arbol == NULL){//si el arbol esta vacio
        Music *nuevo_nodo = crearNodo(padre, key, name, price);//se crera un nuevo nodo
        arbol = nuevo_nodo;//almacenarlo en la raiz del arbol
    }else{//si el arbol tiene un nodo o mas de un nodo
        int valorRaiz = arbol->key;//obtenemos el valor de la raiz
        if(key < valorRaiz){//se manda al lado izquierdo
            insertarNodo(arbol->izq, arbol, key, name, price);
        }else{//si es mayor se inserta en el lado derecho
            insertarNodo(arbol->der, arbol, key, name, price);
        }
    }
}
void insertarNodoBuy(MusicBuy *&arbolBuy,MusicBuy *padreBuy, int key, string name, double price){
    if(arbolBuy == NULL){//si el arbol esta vacio
        MusicBuy *nuevo_nodoBuy = crearNodoBuy(padreBuy, key, name, price);//se crera un nuevo nodo
        arbolBuy = nuevo_nodoBuy;//almacenarlo en la raiz del arbol
    }else{//si el arbol tiene un nodo o mas de un nodo
        int valorRaiz = arbolBuy->key;//obtenemos el valor de la raiz
        if(key < valorRaiz){//se manda al lado izquierdo
            insertarNodoBuy(arbolBuy->izq, arbolBuy, key, name, price);
        }else{//si es mayor se inserta en el lado derecho
            insertarNodoBuy(arbolBuy->der, arbolBuy, key, name, price);
        }
    }
}
void menu(int credit){
    int dato, opcion, contador=0;
    //datos de las canciones
    int key;
    string name;
    double price;
    //
    do{
            system("cls");
        cout << "   INICIO " << endl;
	cout << "1.-Agregar canciones al arbol" << endl;
	cout << "2.-Comprar canciones" << endl;
	cout << "3.-ver canciones en el arbol" << endl;
	cout << "4.-ver canciones compradas" << endl;
	cout << "5.-consultar Credito " << endl;
	cout << "6.-salir" << endl;
	cout << "inserta tu opcion: " ;
        cin >> opcion;
        switch(opcion){
            case 1:
                cout << "NEW MUSIC: \n";
                cout << "Inserte clave de cancion:     ";
                cin >> key;
                cout << "Inserte nombre de la cancion: ";
                cin.ignore();
                getline(cin, name);
                cout << "Inserte precio de la cancion: ";
                cin >> price;
                insertarNodo(arbol,NULL, key, name, price);
                cout << endl;
                system("cls");
                break;
            case 2:
                system("cls");
                int optionKey, songPlace;
                cout << endl;
                cout << setw(6) << "TRACK"
                    << setw(20) << "NAME"
                    << setw(15) << "PRICE" << endl;
                postOrden(arbol);
                cout << endl;
                cout << "inserte clave de la cancion a comprar: ";
                cin >> optionKey;
                if(busqueda(arbol, optionKey) == false){//se busca la cancion
                    cout << " No Encontrado " << endl;
                }else if(busqueda(arbol, optionKey) == true){
                    if (busquedaBuy(arbolBuy, optionKey == true)){//productos en la lista comprada
                        cout << "ya tienes comprada esta cancion" << endl;
                        system("pause");
                    }else if(busquedaBuy(arbolBuy, optionKey) ==  false){//si no se tiene comprada
                        change(arbol, arbolBuy, optionKey, credit);
                    }
                }
                system("pause");
                system("cls");
                break;
            case 3:
                cout << "\t\tALBUM\n" << endl;
                mostrarArbol(arbol, contador);
                cout << endl;
                cout << setw(6) << "TRACK"
                    << setw(20) << "NAME"
                    << setw(15) << "PRICE" << endl;
                postOrden(arbol);
                system("pause");
                break;
            case 4:
                cout << "\t\tMI ALBUM\n" << endl;
                mostrarArbolBuy(arbolBuy, contador);
                cout << endl;
                cout << setw(6) << "TRACK"
                    << setw(20) << "NAME"
                    << setw(15) << "PRICE" << endl;
                postOrdenBuy(arbolBuy);
                system("pause");
                cout << "\n";
                system("pause");
                break;
            case 5:
                cout << "CREDIO DISPONIBLE:  " << credit << endl;
                system("pause");
                system("cls");
                break;
            case 6:
                break;
            default:
                continue;
        }//fin de switch
        system("cls");
    }while(opcion != 6);
}
void mostrarArbol(Music *&arbol, int cont){
    if(arbol==NULL){
        return;
    }else{
        mostrarArbol(arbol->der, cont+1);
        for(int i=0; i<cont; i++){
            cout << "   ";
        }
        cout<< arbol->key <<endl;
            mostrarArbol(arbol->izq, cont+1);
    }
}//para mostrar arbol de canciones compradas
void mostrarArbolBuy(MusicBuy *&arbolBuy, int cont){
    if(arbolBuy==NULL){
        return;
    }else{
        mostrarArbolBuy(arbolBuy->der, cont+1);
        for(int i=0; i<cont; i++){
            cout << "   ";
        }
        cout<< arbolBuy->key <<endl;
            mostrarArbolBuy(arbolBuy->izq, cont+1);
    }
}

bool busqueda(Music *arbol, int n){
    if(arbol == NULL){
        return false;
    }else if(arbol->key == n){
        return true;
    }else if(n < arbol->key){
        return busqueda(arbol->izq, n);
    }else{
        return busqueda(arbol->der, n);
    }
}
//busqueda de canciones compradas
bool busquedaBuy(MusicBuy *arbolBuy, int n){
    if(arbolBuy == NULL){
        return false;
    }else if(arbolBuy->key == n){
        return true;
    }else if(n < arbolBuy->key){
        return busquedaBuy(arbolBuy->izq, n);
    }else{
        return busquedaBuy(arbolBuy->der, n);
    }
}
//eliminar un nodo del arbol
void eliminar(Music *arbol, int n){
    if(arbol == NULL){
        return;
    }else if(n < arbol->key){
        eliminar(arbol->izq, n);
    }else if(n > arbol->key){
        eliminar(arbol->der, n);
    }else{//si ya se encontro el elemento
        eliminarNodo(arbol);
    }
}
Music *minimo(Music *arbol){
    if(arbol == NULL){
        return NULL;
    }
    if(arbol->izq){
        return minimo(arbol->izq);
    }else{
        return arbol;
    }
}

void eliminarNodo(Music *musicEliminar){
    if(musicEliminar->izq && musicEliminar->der){
        Music *menor = minimo(musicEliminar->der);
        musicEliminar->key = menor->key;
        eliminarNodo(menor);
    }else if(musicEliminar->izq){
        reemplazar(musicEliminar,musicEliminar->izq);
        destruirNodo(musicEliminar);
    }else if(musicEliminar->der){
        reemplazar(musicEliminar, musicEliminar->der);
        destruirNodo(musicEliminar);
    }else{
        reemplazar(musicEliminar, NULL);
        destruirNodo(musicEliminar);
    }
}

void reemplazar(Music *arbol, Music* nuevoNodo){
    if(arbol->padre){
        if(arbol->key == arbol->padre->izq->key){
            arbol->padre->izq = nuevoNodo;
        }else if (arbol->key == arbol->padre->der->key){
            arbol->padre->der = nuevoNodo;
        }
    }
    if(nuevoNodo){
        nuevoNodo->padre = arbol->padre;
    }
}

void destruirNodo(Music *Nodo){
    Nodo->izq = NULL;
    Nodo->der = NULL;
    delete Nodo;
}

void postOrden(Music *arbol){
    if(arbol == NULL){
        return;
    }else{
        postOrden(arbol->izq);
        postOrden(arbol->der);
        cout << setw(6) << arbol->key
            << setw(20) << arbol->name
            << setw(15) << arbol->price << endl;;
    }
}
//para las canciones compradas
void postOrdenBuy(MusicBuy *arbolBuy){
    if(arbolBuy == NULL){
        return;
    }else{
        postOrdenBuy(arbolBuy->izq);
        postOrdenBuy(arbolBuy->der);
        cout << setw(6) << arbol->key
            << setw(20) << arbol->name
            << setw(15) << arbol->price << endl;;
    }
}

void change(Music *&arbol, MusicBuy*& arbolBuy, int n, int credit){
    int keyx;
    string namex;
    double pricex;
    if(arbol->key == n){
        //restal el saldo
        keyx = arbol->key;
        namex = arbol->name;
        pricex =  arbol->price;
        credit = credit -(pricex);
        insertarNodoBuy(arbolBuy, NULL, keyx, namex, pricex);
        cout << "elemento comprado" << endl;
        system("pause");
        //se elimina el nodo dle arbol
        eliminar(arbol, n);
        return;
    }else if(n < arbolBuy->key){
        return change(arbol->izq, arbolBuy, n, credit);
    }else{
        return change(arbol->der, arbolBuy, n, credit);
    }
}


