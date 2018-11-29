/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Arboles;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.NoSuchElementException;
import java.util.Queue;

/**
 *
 * @author Fernando Peña
 * @author Fabián Orduña
 */
public class AVLTree <T extends Comparable <T>>{
    private NodoAVL<T> raiz;
    private int cont;
    
    public AVLTree() {
        this.raiz = null;
        this.cont = 0;
    }

    public AVLTree(T dato) {
        this.raiz = new NodoAVL <> (dato);
        this.cont = 1;
    }
    
    public void insertar(T dato){
        NodoAVL <T> actual, papa, aInsertar = new NodoAVL(dato);
        boolean termine = false;
        actual = this.raiz;
        papa = actual;
        this.cont++;
        
        if(actual == null){
            this.raiz = aInsertar;
            return;
        }
        while(actual != null){
            papa = actual;
            if(dato.compareTo(actual.getElem()) < 0)
                actual = actual.getIzq();
            else
                actual = actual.getDer();
        }
        papa.cuelga(aInsertar);
        
        while(aInsertar.getPapa() != null && !termine){
            papa = aInsertar.getPapa();
            if(aInsertar.getElem().compareTo(papa.getElem()) < 0)
                papa.setFe(papa.getFe() - 1);
            else
                papa.setFe(papa.getFe() + 1);
            if(Math.abs(papa.getFe()) > 1){
                rotar(papa);
                termine = true;
            }
            if(papa.getFe() == 0)
                termine = true;
            aInsertar = papa;
        }
    }
    
    public T elimina(T dato){
        NodoAVL <T> papa, actual = this.raiz;
        NodoAVL <T> sucesor;
        boolean found = false, termine = false;
        
        while(actual != null && !found){
            if(dato.equals(actual.getElem()))
                found = true;
            else
                if(dato.compareTo(actual.getElem()) < 0)
                    actual = actual.getIzq();
                else
                    actual = actual.getDer();
        }
        if(actual == null)
            return null;
        sucesor = getSucesorInOrder(actual);
        if(sucesor == null){ //No hay sucesor
            papa = actual.getPapa();
            if(dato.compareTo(papa.getElem()) < 0)
                    papa.setIzq(actual.getIzq());
                else
                    papa.setDer(actual.getDer());
            actual.setPapa(null);
        }
        else{
            actual.setElem(sucesor.getElem());
            papa = sucesor.getPapa();
            if(actual.getDer() == sucesor)
                papa.setDer(sucesor.getDer());
            papa.setIzq(sucesor.getDer());
            
        }
        this.cont--;
        
        while(papa != null && !termine){
            int aD = papa.getDer() != null? papa.getDer().getAltura() + 1: 0;
            int aI = papa.getIzq() != null? papa.getIzq().getAltura() + 1: 0;
//            if(aD != 0 && aI != 0)
//                papa.setFe(aD - aI - 1);
//            else
                papa.setFe(aD - aI);
            if(Math.abs(papa.getFe()) > 1){
                rotar(papa);
            }
            papa = papa.getPapa();
//            if(papa != null && papa.getFe() == 0)
//                termine = true;
        }
        return actual.getElem();  
    }
    
    private NodoAVL<T> getSucesorInOrder(NodoAVL <T> nodo){
        if(nodo == null)
            return null;
        NodoAVL <T> sucesor = null;
        if(nodo.getDer() != null)
            sucesor = nodo.getDer();
        if(sucesor != null)
            while(sucesor.getIzq() != null){
                sucesor = sucesor.getIzq();
            }
        if(sucesor == null)
            return null;
        else
            return sucesor;
    }
    
    private void rotar(NodoAVL <T> nodo){
        if(nodo.getFe() == -2 && nodo.getIzq().getFe() <= 0){
            rotacionIzqIzq(nodo);
        }else if(nodo.getFe() == 2 && nodo.getDer().getFe() >= 0){
            rotacionDerDer(nodo);
        }else if(nodo.getFe() == -2 && nodo.getIzq().getFe() > 0){
            rotacionIzqDer(nodo);
        }else if(nodo.getFe() == 2 && nodo.getDer().getFe() < 0){
            rotacionDerIzq(nodo);
        }
    }
    
    private void rotacionIzqIzq(NodoAVL<T>nodo){   
        NodoAVL<T> alfa, beta, gamma, A, B, C, D, papa;
        alfa = nodo;
        beta = alfa.getIzq();
        gamma = beta.getIzq();
        A = gamma.getIzq();
        B = gamma.getDer();
        C = beta.getDer();
        D = alfa.getDer();
        papa = nodo.getPapa();
        alfa.cuelga(C);
        beta.cuelga(alfa);
        if(papa != null)
            papa.cuelga(beta);
        else{
            beta.setPapa(null);
            this.raiz = beta;
        }
        alfa.setFe((D != null? D.getAltura() : 0) - (C != null? C.getAltura() : 0));
        beta.setFe(alfa.getAltura() - gamma.getAltura());
    }
    
    private void rotacionDerDer(NodoAVL<T>nodo){
        NodoAVL<T> alfa, beta, gamma, A, B, C, D, papa;
        alfa = nodo;
        beta = alfa.getDer();
        gamma = beta.getDer();
        A = alfa.getIzq();
        B = beta.getIzq();
        C = gamma.getIzq();
        D = gamma.getDer();        
        papa = nodo.getPapa();
        if(B!=null)alfa.setDer(B);else alfa.setDer(null);
        alfa.cuelga(A);
        
        beta.cuelga(alfa);
        beta.cuelga(gamma);

        if(papa != null){
            papa.cuelga(beta);
        }
        else{
            beta.setPapa(null);
            raiz = beta;
        }
        int BH = 0,AH = 0,CH = 0,DH = 0;
        if(B != null)BH = 1 + B.getAltura();
        if(A != null)AH = 1 + A.getAltura();
        if(C != null)CH = 1 + C.getAltura();
        if(D != null)DH = 1 + D.getAltura();

        alfa.setFe(BH-AH);
        gamma.setFe(DH-CH);
        beta.setFe(gamma.getAltura()-alfa.getAltura());
    }
    
    private void rotacionIzqDer(NodoAVL<T>nodo){
        NodoAVL<T> alfa, beta, gamma, A, B, C, D, papa;
        alfa = nodo;
        beta = alfa.getIzq();
        gamma = beta.getDer();
        A = beta.getIzq();
        B = gamma.getIzq();
        C = gamma.getDer();
        D = alfa.getDer();
        papa = nodo.getPapa();
        if(B != null)beta.cuelga(B); else beta.setDer(null);
        if(C != null)alfa.cuelga(C); else alfa.setIzq(null);
        gamma.cuelga(beta);
        gamma.cuelga(alfa);
        if(papa != null)
            papa.cuelga(gamma);
        else{
            gamma.setPapa(null);
            this.raiz = gamma;
        }
        beta.setFe((B != null? B.getAltura() : 0) - (A != null? A.getAltura() : 0));
        alfa.setFe((D != null? D.getAltura() : 0) - (C != null? C.getAltura() : 0));
        gamma.setFe(alfa.getAltura() - beta.getAltura()); 
    }
    
    private void rotacionDerIzq(NodoAVL<T>nodo){
        NodoAVL<T> alfa, beta, gamma, A, B, C, D, papa;
        alfa = nodo;
        beta = alfa.getDer();
        gamma = beta.getIzq();
        A = alfa.getIzq();
        B = gamma.getIzq();
        C = gamma.getDer();
        D = beta.getDer();      
        papa = nodo.getPapa();
        if(B != null)alfa.cuelga(B); else alfa.setDer(null);
        if(C != null)beta.cuelga(C); else beta.setIzq(null);
        gamma.cuelga(alfa);
        gamma.cuelga(beta);
        if(papa != null)
            papa.cuelga(gamma);
        else{
            gamma.setPapa(null);
            this.raiz = gamma;
        }
        alfa.setFe((B != null? B.getAltura() : 0) - (A != null? A.getAltura() : 0));
        beta.setFe((D != null? D.getAltura() : 0) - (C != null? C.getAltura() : 0));
        gamma.setFe(beta.getAltura() - alfa.getAltura());
    }
    
    //Métodos buscar
    public T find(T dato) {
        NodoAVL <T> temp = find((NodoAVL<T>) raiz, dato);
        if(temp != null)
            return temp.getElem();
        throw new NoSuchElementException("El elemento no se encuentra en el árbol");
    }
    
    private NodoAVL <T> find(NodoAVL <T> actual, T dato){
        NodoAVL <T> temp;
        if(actual == null)
            return null;
        if(actual.getElem().equals(dato))
            return actual;
        temp = find(actual.getIzq(), dato);
        if(temp == null)
            return find(actual.getDer(), dato);
        else
            return temp;
    }
    
    public void imprimeArbolLevel(){
        String imp = toStringLevel(IteradoresLevelOrder());
        System.out.println(imp);
    }
    
    private String toStringLevel(Iterator[] it){
        String resp = "Elementos : ";
        Iterator <T> elementos = it[0];
        Iterator <Integer> factores = it[1];
        
        while(elementos.hasNext())
            resp += elementos.next() + ", ";
        if(resp.length() != 0)
            resp = resp.substring(0, resp.length() - 2);
        resp += "\nFactores  : ";
        while(factores.hasNext())
            resp += factores.next() + ", ";
        if(resp.length() != 0)
            resp = resp.substring(0, resp.length() - 2);
         
        return resp;
    }
     
    private Iterator[] IteradoresLevelOrder() {
        ArrayList <T> lista = new ArrayList <>();
        ArrayList <Integer> factores = levelOrder(this.raiz, lista);
        Iterator[] resp = {lista.iterator(), factores.iterator()};
        return resp;
    }
     
    private ArrayList<Integer> levelOrder(NodoAVL<T> actual, ArrayList<T> lista) {
        Queue <NodoAVL <T>> cola = new LinkedList();
        ArrayList <Integer> factores = new ArrayList();
        cola.add(actual);
        if(actual != null){
        while(!cola.isEmpty()){
            NodoAVL <T> temp = cola.remove();
            lista.add(temp.getElem());
            factores.add(temp.getFe());
            if(temp.getIzq() != null)
                cola.add(temp.getIzq());
            if(temp.getDer() != null)
                cola.add(temp.getDer());
            }
        }
        return factores;
    }
}