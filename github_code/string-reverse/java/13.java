package org.ip.sesion07;
import java.util.Locale;
import java.util.Scanner;

public class ComprobarPalindromo3 {
	private static Scanner input = new Scanner(System.in);

	public static boolean esPalindromo(String cadena) {
		StringBuffer stringReverse = new StringBuffer(cadena);
		stringReverse.reverse();
		System.out.println("Cadena = " + cadena);
		System.out.println("Cadena invertida = " + stringReverse+"\n");
		String string = stringReverse.substring(0);
		if (stringReverse.equals(stringReverse)) {
			return true;
		} else {
			return false;
		}
	}


	public static void main(String[] args) {

		System.out.print("Introduzca una cadena ");
		input.useLocale(Locale.ENGLISH);
		String frase = input.nextLine();

		/** Quitar espacios **/
		String string = frase.replaceAll(" ", "");

		/** Transformar el string en mayusculas **/
		string = string.toUpperCase();
		System.out.println();
		if (esPalindromo(string) == true) {
			System.out.println(frase + " es un palindromo");
		} else {
			System.out.println(frase + " no es un palindromo");
		}
		

	}

}
