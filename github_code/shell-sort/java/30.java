package UVA;

import java.util.Scanner;

public class shellsort 
{
	public static void main(String [] args)
	{
		Scanner sc = new Scanner(System.in);
		int ncasos = sc.nextInt();
		sc.nextLine();
		for(int i = 0; i < ncasos; i++)
		{
			int ntortugas = sc.nextInt();
			sc.nextLine();
			String tortugas [] = new String[ntortugas];
			String tortugasO [] = new String[ntortugas];
			for(int j = 0; j < ntortugas; j++)
			{
				tortugas[j] = sc.nextLine();
			}
			for(int j = 0; j < ntortugas; j++)
			{
				tortugasO[j] = sc.nextLine();
			}
			int tortugaActual = -1;
			for(int j = 0; j < ntortugas; j++)
			{
				if(tortugas[ntortugas - 1 - j].equals(tortugasO[ntortugas - 2 - tortugaActual]))
				{
					tortugaActual++;
				}
			}
			for(tortugaActual++; tortugaActual < ntortugas; tortugaActual++)
			{
				System.out.println(tortugasO[ntortugas - 1 - tortugaActual]);
			}
			System.out.println();
		}
	}
}
