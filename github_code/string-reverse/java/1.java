package br.com.stf.treinamento.exercicios.java;

import java.util.Scanner;

public final class JavaStringReverse {

	private JavaStringReverse() {
	}

	public static void executar() {
		Scanner scanner = new Scanner(System.in);
		String a = scanner.next();
		scanner.close();

		if (inverter(a).equals(a)) {
			System.out.println("Sim");
		} 
		else {
			System.out.println("Não");
		}
	}

	private static String inverter(String palavra) {
		return new StringBuilder(palavra).reverse().toString();
	}
}
