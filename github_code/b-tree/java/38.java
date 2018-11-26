

import java.io.Serializable;
import java.util.ArrayList;
import java.util.LinkedList;

public class B_Plus_Tree<E extends Comparable<E>> implements Serializable {

    private static final long SerialVersioUID = 603L;
    private int Tam_hojas;
    private int Tam_interno;
    private Node<E> root;
    private int size;
    private Metodos<E> nm;
    private LinkedList<Node<E>> buff;
    private int bufferboolSize;

    public B_Plus_Tree(int tam_hoja, int tam_interno, int buffbool, long position) {
        super();
        this.Tam_hojas = tam_hoja;
        this.Tam_interno = tam_interno;
        this.root = new Node<E>(tam_hoja, true, position);
        nm = new Metodos<E>();
        buff = new LinkedList<Node<E>>();
        this.bufferboolSize = buffbool;
    }

    // ===========================INSERTAR==================================
    public void AddNode(E llave, Object data, long position) {
        // pila para guardar padre
        LinkedList<Node<E>> stack = new LinkedList<Node<E>>();
        Node<E> n = root;
        //buscar el elemento
        while (!n.isLeaf) {
            stack.push(n);
            if (llave.compareTo(n.getKeys().get(0)) < 0) {  // si esta en el primer puntero
                n = (Node<E>) n.getPointers().get(0);
            } else if (llave.compareTo(n.getKeys().get(n.getKeys().size() - 1)) >= 0) {// si esta en el ultimo puntero
                n = (Node<E>) n.getPointers().get(n.getPointers().size() - 1);
            } else {
                for (int i = 0; i < n.getKeys().size() - 1; i++) { // caso general
                    if (n.getKeys().size() > 1 && llave.compareTo(n.getKeys().get(i)) >= 0 && llave.compareTo(n.getKeys().get(i + 1)) < 0) {
                        n = (Node) n.getPointers().get(i + 1);
                        break;
                    }
                }
            }
        }
        // revisar si el elemento se encuentra en el nodo
        for (int i = 0; i < n.getKeys().size(); i++) {
            if (llave == n.getKeys().get(i)) {
                return;
            }
        }
        // si el nodo NO esta lleno
        if (n.getKeys().size() < Tam_hojas) {
            nm.sortedInsert(llave, data, n);
        } else {
            // split para generar 2 nodos hoja
            // copiar todo el contenido del nodo en un nodo temporal luego insertar el nuevo elemento en el
            Node<E> temp = new Node(Tam_hojas, true, position);
            temp.setKeys(new ArrayList<E>(n.getKeys()));
            temp.setPointers(new ArrayList<Object>(n.getPointers()));
            nm.sortedInsert(llave, data, temp);
            Node newNode = new Node(Tam_hojas, true, position);
            int j = (int) Math.ceil(n.getPointers().size() / (double) 2);
            //tomar la primera mitad del nodo temporal en el nodo actual
            n.setKeys(new ArrayList<E>(temp.getKeys().subList(0, j)));
            n.setPointers(new ArrayList<Object>(temp.getPointers().subList(0, j)));
            // setear nodo anterior y siguiente
            if (n.getNext() != null) {
                n.getNext().setPrev(newNode);
            }
            newNode.setNext(n.getNext());
            n.setNext(newNode);
            // copiar la segunda mitad del nodo temporal en un nuevo nodo
            newNode.setPrev(n);
            newNode.setKeys(new ArrayList<E>(temp.getKeys().subList(j, temp.getKeys().size())));
            newNode.setPointers(new ArrayList<Object>(temp.getPointers().subList(j, temp.getPointers().size())));
            // tomar la llave que se va a insertar en el nodo padre
            llave = temp.getKeys().get(j);
            boolean terminado = false;
            do {
                // si el nodo padre esta vacio
                if (stack.isEmpty()) {
                    root = new Node(Tam_interno, false, position);
                    ArrayList<Object> point = new ArrayList<Object>();
                    point.add(n);
                    point.add(newNode);
                    ArrayList<E> keys_ = new ArrayList<E>();
                    keys_.add(llave);
                    root.setKeys(keys_);
                    root.setPointers(point);
                    terminado = true;
                } else {
                    // si hay padre
                    n = stack.pop();
                    // si no hay necesidad de hacer split interno
                    if (n.getKeys().size() < Tam_interno) {
                        nm.sortedInsertInternal(llave, newNode, n);
                        terminado = true;
                    } else {
                        /*
                        hacer split de dos nodos internos copiandolo en un nuevo nodo
                        e insertar el nuevo elemento en el nodo temporal, luego dividirlo
                        entre el nodo actual y el nuevo nodo
                         */
                        temp.setLeaf(false);
                        temp.setKeys(new ArrayList<E>(n.getKeys()));
                        temp.setPointers(new ArrayList<Object>(n.getPointers()));

                        nm.sortedInsertInternal(llave, newNode, temp);
                        newNode = new Node(Tam_interno, false, position);
                        j = (int) Math.ceil(temp.getPointers().size() / (double) 2);

                        n.setKeys(new ArrayList<E>(temp.getKeys().subList(0, j - 1)));
                        n.setPointers(new ArrayList<Object>(temp.getPointers().subList(0, j)));
                        if (n.getNext() != null) {
                            n.getNext().setPrev(newNode);
                        }
                        newNode.setNext(n.getNext());
                        n.setNext(newNode);
                        newNode.setPrev(n);
                        newNode.setKeys(new ArrayList<E>(temp.getKeys().subList(j, temp.getKeys().size())));
                        newNode.setPointers(new ArrayList<Object>(temp.getPointers().subList(j, temp.getPointers().size())));

                        llave = temp.getKeys().get(j - 1);
                    }
                }
            } while (!terminado);
        }
    }

    // =============================BUSCAR================================
    @SuppressWarnings("unchecked")
    public Node<E> search(E key) {
        // buscar en el buffer array si el elemento esta ahi o no
        for (int i = 0; i < buff.size(); i++) {
            ArrayList<E> find = buff.get(i).getKeys();
            if (find.contains(key)) {
                return buff.get(i);
            }
        }
        // si el elemento NO esta
        Node<E> n = root;
        while (!n.isLeaf) {
            //buscar el elemento
            if (key.compareTo(n.getKeys().get(0)) < 0) {// si esta en el primer puntero
                n = (Node<E>) n.getPointers().get(0);
            } else if (key.compareTo(n.getKeys().get(n.getKeys().size() - 1)) >= 0) {// si esta en el ultimo puntero
                n = (Node<E>) n.getPointers().get(n.getPointers().size() - 1);
            } else {
                for (int i = 0; i < n.getKeys().size() - 1; i++) {
                    if (n.getKeys().size() > 1 && key.compareTo(n.getKeys().get(i)) >= 0 && key.compareTo(n.getKeys().get(i + 1)) < 0) {// caso general
                        n = (Node) n.getPointers().get(i + 1);
                        break;
                    }
                }
            }
        }
        // añadiendo nuevo nodo al buffer
        for (int i = 0; i < n.getKeys().size(); i++) {
            if (key.compareTo(n.getKeys().get(i)) == 0) {
                if (buff.size() == bufferboolSize) {
                    buff.removeFirst();
                    buff.add(n);
                } else {
                    buff.add(n);
                }
                return n;
            }
        }
        return null;
    }

    // ==============================ELIMINAR================================
    @SuppressWarnings("unchecked")
    public void delete(E key) {
        LinkedList<Node<E>> stack = new LinkedList<Node<E>>();
        Node<E> n = root;
        // buscando el nodo
        while (!n.isLeaf) {
            stack.push(n);
            if (key.compareTo(n.getKeys().get(0)) < 0) {
                n = (Node<E>) n.getPointers().get(0);
            } else if (key.compareTo(n.getKeys().get(n.getKeys().size() - 1)) >= 0) {
                n = (Node) n.getPointers().get(n.getPointers().size() - 1);
            } else {
                for (int i = 0; i < n.getKeys().size(); i++) {
                    if (key.compareTo(n.getKeys().get(i)) >= 0 && key.compareTo(n.getKeys().get(i + 1)) < 0) {
                        n = (Node) n.getPointers().get(i + 1);
                        break;
                    }
                }
            }
        }
        boolean band = false;
        for (int i = 0; i < n.getKeys().size(); i++) {
            if (n == root && key == n.getKeys().get(i)) {
                nm.deleteNode(n, key);
                return;
            } else if (key == n.getKeys().get(i)) {
                band = true;
                break;
            }
        }
        //buscando para determinar si el elemento se encontro en un nodo hoja o no
        if (band) {
            //si NO hay underflow en el nodo
            if (n.getKeys().size() - 1 >= Math.ceil(Tam_hojas / 2.0)) {
                nm.deleteNode(n, key);
                Node<E> parent = stack.peek();
                for (int i = 0; i < parent.getKeys().size(); i++) {
                    if (key.compareTo(parent.getKeys().get(i)) == 0) {
                        parent.getKeys().set(i, n.getKeys().get(0));
                        break;
                    }
                }
            } else {
                // SI hay underflow en el nodo
                Node<E> parent = stack.peek();
                // determinar si el siguiente nodo es del mismo padre o no para prestar de el
                int deter = nm.sameParent(n, stack.peek(), Tam_hojas);
                // si el siguiente nodo es del mismo padre
                if (deter == 1) {
                    // eliminar el nodo
                    nm.deleteNode(n, key);
                    // prestar del siguiente nodo hoja
                    E element = n.getNext().getKeys().remove(0);
                    Object obj = n.getNext().getPointers().remove(0);
                    n.getKeys().add(element);
                    n.getPointers().add(obj);
                    for (int i = 0; i < parent.getKeys().size(); i++) {
                        if (element.compareTo(parent.getKeys().get(i)) == 0) {
                            parent.getKeys().set(i, n.getNext().getKeys().get(0));
                            break;
                        }
                    }
                    for (int i = 0; i < parent.getKeys().size(); i++) {
                        if (key.compareTo(parent.getKeys().get(i)) == 0) {
                            parent.getKeys().set(i, n.getKeys().get(0));
                            break;
                        }
                    }
                    return;
                } else if (deter == 2) {
                    // prestar del nodo anterior
                    nm.deleteNode(n, key);
                    E element = n.getPrev().getKeys().remove(n.getPrev().getKeys().size() - 1);
                    Object obj = n.getPrev().getPointers().remove(n.getPrev().getPointers().size() - 1);
                    n.getKeys().add(0, element);
                    n.getPointers().add(0, obj);
                    for (int i = 0; i < parent.getKeys().size(); i++) {
                        if (element.compareTo(parent.getKeys().get(i)) == 0) {
                            parent.getKeys().set(i, n.getPrev().getKeys().get(n.getPrev().getKeys().size() - 1));
                            break;
                        }
                    }
                    for (int i = 0; i < parent.getKeys().size(); i++) {
                        if (key.compareTo(parent.getKeys().get(i)) == 0) {
                            parent.getKeys().set(i, n.getKeys().get(0));
                            break;
                        }
                    }
                    return;
                } else {
                    // habrá merge para nodos internos
                    boolean prevB = true;
                    if (key == n.getKeys().get(0)) {
                        prevB = false;
                    }

                    nm.deleteNode(n, key);
                    int tempKey = 0;
                    int tempPointer = 0;
                    /*
                    si el merge está con el siguiente nodo entonces copiar todos
                    los elementos del nodo actual en el siguiente nodo.
                    Eliminar el primer elemento del siguiente nodo en el nodo padre
                     */
                    if (nm.sameParent2(parent, n)) {
                        Node<E> next = n.getNext();
                        if (n.getPrev() != null) {
                            n.getPrev().setNext(next);
                        }
                        if (next != null) {
                            next.setPrev(n.getPrev());
                        }
                        n.setNext(null);
                        n.setPrev(null);
                        next.getKeys().addAll(0, n.getKeys());
                        next.getPointers().addAll(0, n.getPointers());
                        for (int i = 0; i < parent.getKeys().size(); i++) {
                            if (next.getKeys().get(n.getKeys().size()).compareTo(parent.getKeys().get(i)) == 0) {
                                tempKey = i;
                                tempPointer = i;
                                break;
                            }
                        }
                        if (tempKey > 0 && parent.getKeys().get(tempKey - 1) == key) {
                            parent.getKeys().set(tempKey - 1, next.getKeys().get(0));
                        }
                    } else {
                        /*
                        Si el merge está en el nodo anterior, entonces copiar todos los elementos
                        del nodo en el nodo anterior.
                        Eliminar el primer elemento del nodo actual en el nodo padre
                         */
                        Node<E> prev = n.getPrev();
                        if (prev != null) {
                            prev.setNext(n.getNext());
                        }
                        if (n.getNext() != null) {
                            n.getNext().setPrev(prev);
                        }
                        n.setNext(null);
                        n.setPrev(null);
                        prev.getKeys().addAll(n.getKeys());
                        prev.getPointers().addAll(n.getPointers());
                        if (prevB) {
                            for (int i = 0; i < parent.getKeys().size(); i++) {
                                if (n.getKeys().get(0).compareTo(parent.getKeys().get(i)) == 0) {
                                    tempKey = i;
                                    tempPointer = i + 1;
                                    break;
                                }
                            }
                        } else {
                            for (int i = 0; i < parent.getKeys().size(); i++) {
                                if (key.compareTo(parent.getKeys().get(i)) == 0) {
                                    tempKey = i;
                                    tempPointer = i + 1;
                                    break;
                                }
                            }
                        }
                    }
                    boolean finished = false;
                    do {
                        // si tenemos la raiz
                        if (stack.isEmpty()) {
                            root.getKeys().remove(tempKey);
                            root.getPointers().remove(tempPointer);
                            finished = true;
                        } else {
                            n = stack.pop();
                            if (n.getKeys().size() - 1 >= 1) {
                                n.getKeys().remove(tempKey);
                                n.getPointers().remove(tempPointer);
                                finished = true;
                            } else {
                                // el arbol decrece en un nivel
                                if (n == root) {
                                    n.getKeys().remove(tempKey);
                                    n.getPointers().remove(tempPointer);
                                    if (n.getPointers().size() == 1) {
                                        root = (Node<E>) n.getPointers().get(0);
                                    }
                                    finished = true;
                                } else {
                                    n.getKeys().remove(tempKey);
                                    n.getPointers().remove(tempPointer);
                                    deter = nm.nexOrprev(n, stack.peek(), Tam_interno);
                                    parent = stack.peek();
                                    // prestar del siguiente nodo interno
                                    if (deter == 1) {
                                        int index = -1;
                                        for (int i = 0; i < parent.getPointers().size(); i++) {
                                            if (parent.getPointers().get(i) == n.getNext()) {
                                                index = i;
                                                break;
                                            }
                                        }
                                        E tempkey = parent.getKeys().remove(index - 1);
                                        n.getKeys().add(tempkey);
                                        Node<E> tempNext = (Node<E>) n.getNext().getPointers().remove(0);
                                        E nextKey = n.getNext().getKeys().remove(0);
                                        n.getPointers().add(tempNext);
                                        parent.getKeys().add(index - 1, nextKey);
                                        finished = true;
                                        // prestar del nodo interno anterior
                                    } else if (deter == 2) {
                                        int index = -1;
                                        for (int i = 0; i < parent.getPointers().size(); i++) {
                                            if (parent.getPointers().get(i) == n) {
                                                index = i;
                                                break;
                                            }
                                        }
                                        E tempkey = parent.getKeys().remove(index - 1);
                                        n.getKeys().add(0, tempkey);
                                        Node<E> tempPrev = (Node<E>) n.getPrev().getPointers().remove(n.getPrev().getPointers().size() - 1);
                                        E prevKey = n.getPrev().getKeys().remove(n.getPrev().getKeys().size() - 1);
                                        n.getPointers().add(0, tempPrev);
                                        parent.getKeys().add(index - 1, prevKey);
                                        finished = true;
                                    } else {
                                        // merge entre dos nodos internos
                                        if (nm.sameParent2(parent, n)) {
                                            for (int i = 0; i < parent.getPointers().size(); i++) {
                                                if (n == parent.getPointers().get(i)) {
                                                    tempKey = i;
                                                    tempPointer = i;
                                                    break;
                                                }
                                            }
                                            Node<E> next = n.getNext();
                                            if (n.getPrev() != null) {
                                                n.getPrev().setNext(next);
                                            }
                                            if (next != null) {
                                                next.setPrev(n.getPrev());
                                            }
                                            next.getKeys().add(0, parent.getKeys().get(tempKey));
                                            next.getKeys().addAll(0, n.getKeys());
                                            next.getPointers().addAll(0, n.getPointers());

                                        } else {
                                            for (int i = 0; i < parent.getPointers().size(); i++) {
                                                if (n == parent.getPointers().get(i)) {
                                                    tempKey = i - 1;
                                                    tempPointer = i;
                                                    break;
                                                }
                                            }
                                            Node<E> prev = n.getPrev();
                                            if (prev != null) {
                                                prev.setNext(n.getNext());
                                            }
                                            if (n.getNext() != null) {
                                                n.getNext().setPrev(prev);
                                            }
                                            prev.getKeys().add(parent.getKeys().get(tempKey));
                                            prev.getKeys().addAll(n.getKeys());
                                            prev.getPointers().addAll(n.getPointers());
                                        }
                                    }
                                }
                            }
                        }
                    } while (!finished);

                }
            }
            System.out.println("finalizo");
        } else { // si el elemento no se encontró
            return;
        }
    }

//----------------------------------------------------------
    public int getLeafSize() {
        return Tam_hojas;
    }

    public void setLeafSize(int leafSize) {
        this.Tam_hojas = leafSize;
    }

    public int getInternalSize() {
        return Tam_interno;
    }

    public void setInternalSize(int internalSize) {
        this.Tam_interno = internalSize;
    }

    public Node<E> getRoot() {
        return root;
    }

    public void setRoot(Node<E> root) {
        this.root = root;
    }

    public int getSize() {
        return size;
    }

    public void setSize(int size) {
        this.size = size;

    }

    @SuppressWarnings("unchecked")

    // ===========================IMPRIMIR==================================
    public String print() {
        String s = "";
        LinkedList<Node<E>> view = new LinkedList<Node<E>>();
        view.add(root);
        while (!view.isEmpty()) {
            Node<E> e = view.pop();
            for (int i = 0; i
                    < e.getKeys().size(); i++) {
                s += (e.getKeys().get(i) + " ");
            }
            for (int i = 0; i < e.getPointers().size(); i++) {
                try {
                    view.add((Node<E>) e.getPointers().get(i));
                } catch (Exception e1) {
                }
            }
            s += "\n";
        }
        return s;
    }
}
