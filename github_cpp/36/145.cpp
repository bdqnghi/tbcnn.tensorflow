#include "b-treenode.h"
#include "b-tree.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

BTree::BTree(int tamano, char nombre[25]){
    this->tamano = tamano;
    this->root = NULL;
    create(nombre);
}

BTree::~BTree(){

}

BTreeNode* BTree::busqueda(int llaveBusqueda){
    if(root == NULL)
        return NULL;
    return root->busqueda(llaveBusqueda);
}

BTreeNode* BTree::busqueda(char* llaveBusqueda){
    if(root == NULL)
        return NULL;
    return root->busqueda(llaveBusqueda);
}

bool BTree::insert(Key llave){
     if (root == NULL){                                                            //Si no existe raiz
        root = new BTreeNode(tamano, true);                                     //Se crea la raiz
        root->llaves[0] = llave;
        root->tamano = 1;
    } else{
        if (root->tamano == root->maximo){                                      //Mira si la raiz no tiene el tamano maximo
            BTreeNode *neo = new BTreeNode(false, tamano);
            neo->hijos[0] = root;                                               //Crea un nuevo nodo que contendra a la raiz actul como hijo
 
            neo->split(0, root);                                                
 
            int i = 0;
            if (neo->llaves[0].llave < llave.llave)                             //Decidir cual de los dos hijos de la raiz tendra los hijos
                i++;
            if (neo->hijos[i]->insert(llave))
                root = neo;                                                     //Actualizar la raiz
            else
                return false;
        }
        else 
             return root->insert(llave);                                        //Insertar normal
    }
    return true;
}

bool BTree::insert(KeyChar llave){
    if (root == NULL){                                                          //Si no existe raiz
        root = new BTreeNode(tamano, true);                                     //Se crea la raiz
        root->llavesChar[0] = llave;
        root->tamano = 1;
    } else{
        if (root->tamano == root->maximo){                                      //Mira si la raiz no tiene el tamano maximo
            BTreeNode *neo = new BTreeNode(false, tamano);
            neo->hijos[0] = root;                                               //Crea un nuevo nodo que contendra a la raiz actul como hijo
 
            neo->split(0, root);                                                
 
            int i = 0;
            if (strncmp(neo->llavesChar[0].llave, llave.llave, 14) < 0 )                //Decidir cual de los dos hijos de la raiz tendra los hijos
                i++;
            if (neo->hijos[i]->insert(llave))
                root = neo;                                                     //Actualizar la raiz    
            else        
                return false;                                           
        }
        else 
             return root->insert(llave);                                        //Insertar normal
    }
    return true;
}

bool BTree::Remove(Key llave){
    if (!root){
        cout << "El árbol esta vacío\n";
        return false;
    }
    bool retornar;
    retornar = root->Remove(llave);
    if (root->tamano==0){
        BTreeNode *tmp = root;
        if (root->hoja){
            root = NULL;
        }else{
            root = root->hijos[0];
        }
        delete tmp;
    }
    if (retornar)
        return true;
    return false;
}

bool BTree::Remove(KeyChar llave){
    if (!root){
        cout << "El árbol esta vacío\n";
        return false;
    }
    bool retornar;
    retornar = root->Remove(llave);
    root->Remove(llave);
    if (root->tamano==0){
        BTreeNode *tmp = root;
        if (root->hoja){
            root = NULL;
        }else{
            root = root->hijos[0];
        }
        delete tmp;
    }
    if (retornar)
        return true;
    return false;
}

void BTree::inorder(char nombre[25]){
    bool tipo;
    bool tipo2 = false;
    if(strncmp(nombre, "indexCiudades.bin", 25) == 0 )
        tipo = true;
    else if(strncmp(nombre, "indexClientes.bin", 25) == 0 )
        tipo = false;
    else
        tipo2 = true;
    if (root != NULL) 
        root->inorder(tipo); 
}

void BTree::create(char nombre[25]){
    if(strncmp(nombre, "indexCiudades.bin", 25) == 0 )
        createCiudadArboles();
    else if(strncmp(nombre, "indexClientes.bin", 25) == 0 )
        createClienteArbols();
    else
        createLineas();
}

void BTree::createCiudadArboles(){
    ifstream file;
    cout << "Alvaro" << endl;
    file.open("ciudades.bin");
    if(!file.is_open()){
        cerr << "Error al abrir el archivo. Aqui es el error" << endl;
    } else{
        HeaderArbol head;

        file.seekg(0);
        file.read(reinterpret_cast<char*>(&head), sizeof(HeaderArbol));
        int sizeRegistros = head.sizeRegistro; 
        int availList = head.availList;

        int RRN;
        int skip = 0;
        Key llave;
        
        cout << "3 sizeRegistros = " << sizeRegistros << "\tAvail = " << availList  << "\tUltimo = " << head.sizeRegistro << endl;
        for (int i = 0; i < sizeRegistros; i++){
            CiudadArbol city;
            file.read(reinterpret_cast<char*>(&city), sizeof(CiudadArbol));

            if(skip == 0)
                RRN = i;
            else
                RRN = i + skip;
            llave.llave =  city.idCiudad;
            llave.RRN = RRN;

            if(city.idCiudad != -99)
                this->insert(llave);
            if(city.idCiudad == -99){
                i--;
                skip++;
            }
        }
        /*ofstream salida("indexCiudadArboles.bin", ofstream::binary);
        for (int i = 0; i < index.size(); i++){
            salida.write(reinterpret_cast<const char*> (&index.at(i)), sizeof(Indice));
        }
        salida.close();*/
    }
    file.close();
}

void BTree::createClienteArbols(){
    ifstream file;
    file.open("clientes.bin");
    if(!file.is_open()){
        cerr << "Error al abrir el archivo. DARIO" << endl;
    } else{
        cout<<"ENTRO DONDE ES "<<endl;
        HeaderArbol head;

        file.seekg(0);
        file.read(reinterpret_cast<char*>(&head), sizeof(HeaderArbol));
        int sizeRegistros = head.sizeRegistro; 
        int availList = head.availList;

        int RRN;
        int skip = 0;
        KeyChar llave;
        for (int i = 0; i < sizeRegistros; ++i){
            ClienteArbol clienteArbol;
            file.read(reinterpret_cast<char*>(&clienteArbol), sizeof(ClienteArbol));

            if(skip == 0)
                RRN = i;
            else
                RRN = i + skip;

            strncpy(llave.llave, clienteArbol.idCliente, 14);
            llave.RRN = RRN;
            if(strncmp(clienteArbol.idCliente, "*", 1) != 0){
                this->insert(llave);
            }
            if(strncmp (clienteArbol.idCliente, "*", 1) == 0){
                i--;
                skip++;
            }

        }
        /*ofstream salida("indexLineasXClienteArbol.bin", ofstream::binary);
        for (int i = 0; i < index.size(); i++){
            salida.write(reinterpret_cast<const char*> (&index.at(i)), sizeof(IndiceLineas));
        }
        salida.close();
        */
    }
    file.close();
}

void BTree::createLineas(){
    ifstream file;
    file.open("lineaxclientes.bin");
    if(!file.is_open()){
        cerr << "Error al abrir el archivo." << endl;
    } else{
        HeaderArbol head;

        file.seekg(0);
        file.read(reinterpret_cast<char*>(&head), sizeof(HeaderArbol));
        int sizeRegistros = head.sizeRegistro; 
        int availList = head.availList;

        int RRN;
        int skip = 0;
        KeyChar llave;
        
        cout << "3 sizeRegistros = " << sizeRegistros << "\tAvail = " << availList  << "\tUltimo = " << head.sizeRegistro << endl;
        for (int i = 0; i < sizeRegistros; ++i){
            LineaxClienteArbol lineas;
            file.read(reinterpret_cast<char*>(&lineas), sizeof(LineaxClienteArbol));

            if(skip == 0)
                RRN = i;
            else
                RRN = i + skip;

            strncpy(llave.llave, lineas.numero, 14);
            llave.RRN = RRN;

            if(strncmp(lineas.numero, "-99", 14) != 0){
                this->insert(llave);
            }
            if(strncmp (lineas.numero, "-99", 9) == 0){
                i--;
                skip++;
            }

        }
        /*ofstream salida("indexLineasXClienteArbol.bin", ofstream::binary);
        for (int i = 0; i < index.size(); i++){
            salida.write(reinterpret_cast<const char*> (&index.at(i)), sizeof(IndiceLineas));
        }
        salida.close();
        */
    }
    file.close();
}