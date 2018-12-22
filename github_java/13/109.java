/*
 * Hola!
 */
package shellsort;

import java.awt.event.ActionEvent;
import java.util.ArrayList;
import javax.swing.*;

/**
 *
 * @author Sebastián Méndez <ITCH>
 */
public class Shellsort extends JFrame {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        Shellsort ven = new Shellsort();
        ven.setVisible(true);
    }

    public Shellsort() {
        initIU();
    }

    //Trabajo
    public String imprimirListaDesordenada() {
        String salida = "";

        for (int i = 0; i < listaDesordenada.size(); i++) {
            salida += "  " + listaDesordenada.get(i) + "\n";
        }

        return salida;
    }

    public String imprimirLista() {
        String salida = "";

        for (int i = 0; i < lista.size(); i++) {
            salida += "  " + lista.get(i) + "\n";
        }

        return salida;
    }

    public static void intercambiar(int i, int j) {
        int aux = lista.get(i);
        lista.set(i, lista.get(j));
        lista.set(j, aux);
    }
    //Metodo Shellsort

    public void shellsort() {
        int intervalo, i, j, k;
        int n = lista.size();
        intervalo = n / 2;
        while (intervalo > 0) {
            for (i = intervalo; i < n; i++) {
                j = i - intervalo;
                while (j >= 0) {
                    k = j + intervalo;
                    if (lista.get(j) <= lista.get(k)) {
                        j = -1; // par de elementos ordenado
                    } else {
                        intercambiar(j, j + 1);
                        j -= intervalo;
                    }
                }
            }
            intervalo = intervalo / 2;
        }
    }

    //Ventana
    public void initIU() {
        setSize(470, 480);
        setLocationRelativeTo(null);
        setTitle("Metodo Shellsort");
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        setLayout(null);

        texto1.setBounds(20, 20, 150, 25);
        dato.setBounds(20, 50, 100, 25);
        ingresar.setBounds(130, 50, 90, 25);
        reiniciar.setBounds(130, 90, 90, 25);
        desordenados.setBounds(240, 20, 190, 190);
        ordenados.setBounds(240, 230, 190, 190);
        ordenar.setBounds(60, 320, 90, 25);

        ingresar.addActionListener((ActionEvent e) -> {
            int nom = Integer.parseInt(dato.getText());
            listaDesordenada.add(nom);
            dato.setText("");
            desordenados.setText(imprimirListaDesordenada());
        });

        ordenar.addActionListener((ActionEvent e) -> {
            lista = listaDesordenada;
            shellsort();
            ordenados.setText(imprimirLista());
            ingresar.setEnabled(false);
        });
        
        reiniciar.addActionListener((ActionEvent e)->{
            listaDesordenada = new ArrayList();
            ordenados.setText("");
            desordenados.setText("");
            ingresar.setEnabled(true);
        });
        
        //add
        add(texto1);
        add(dato);
        add(ingresar);
        add(desordenados);
        add(ordenados);
        add(ordenar);
        add(reiniciar);
    }

    //Declaracion de atributos y objetos
    JLabel texto1 = new JLabel("Ingrese un número");
    JTextField dato = new JTextField("");
    JButton ingresar = new JButton("Ingresar");
    JButton ordenar = new JButton("ORDENAR");
    JButton reiniciar = new JButton("Reiniciar");
    JTextArea desordenados = new JTextArea();
    JTextArea ordenados = new JTextArea();
    static ArrayList<Integer> lista = new ArrayList<>();
    static ArrayList<Integer> listaDesordenada = new ArrayList<>();

}
