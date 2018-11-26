package inteligenca;



import logika.Igra;
import logika.Igralec;
import logika.Plosca;


public class Ocena {
	public static final int ZMAGA = (1 << 20); // vrednost zmage, več kot vsaka druga ocena pozicije
	public static final int ZGUBA = -ZMAGA;
	
	public static int oceniPozicijo(Igralec jaz, Igra igra) {
		int ocena, pretokRdeci, pretokModri;
		switch (igra.stanje()) {
		case ZMAGA_MODRI:
			return (jaz == Igralec.MODRI ? ZMAGA : ZGUBA);
		case ZMAGA_RDECI:
			return (jaz == Igralec.RDECI ? ZMAGA : ZGUBA);
		case POTEZA_MODRI:
			pretokRdeci = FordFulkerson.fordFulkerson(igra.matrikaRdeci, 0, Plosca.N*Plosca.N + 1);
			pretokModri = FordFulkerson.fordFulkerson(igra.matrikaModri, 0, Plosca.N*Plosca.N + 1);
			if (igra.stPotez < Plosca.N) {
				ocena = 2 * pretokRdeci - 1 * pretokModri;
			} else {
				ocena = 7 * pretokRdeci - 1 * pretokModri;
			}
			return (jaz == Igralec.MODRI ? ocena : -ocena);
		case POTEZA_RDECI:
			pretokRdeci = FordFulkerson.fordFulkerson(igra.matrikaRdeci, 0, Plosca.N*Plosca.N + 1);
			pretokModri = FordFulkerson.fordFulkerson(igra.matrikaModri, 0, Plosca.N*Plosca.N + 1);
			if (igra.stPotez < Plosca.N) {
				ocena = 2 * pretokModri - 1 * pretokRdeci;
			} else {
				ocena = 7 * pretokModri - 1 * pretokRdeci;
			}
			return (jaz == Igralec.RDECI ? ocena : -ocena);
		}
		assert false;
		return 42; // Java je blesava
	}

}



/*
 * Spodaj so zakomentirani prvi poskusi hevristik.
 */


//PAZI!! SEDAJ SO RAZLICNE OCENE ZA MODREGA IN RDECEGA IGRALCA

	/*public static int oceniPozicijo(Igralec jaz, Igra igra) {
		switch (igra.stanje()) {
		case ZMAGA_MODRI:
			return (jaz == Igralec.MODRI ? ZMAGA : ZGUBA);
		case ZMAGA_RDECI:
			return (jaz == Igralec.RDECI ? ZMAGA : ZGUBA);
		case POTEZA_MODRI:
			int ocena_trenutne_plosce_za_modrega = 0;
			for (int x = 1; x <= Plosca.N; x ++) {
				for (int y = 1; y <= Plosca.N; y ++) {
					if (igra.plosca.matrikaPolj[y][x] == Polje.MODRO) {
						int stevec_bridge_sosedov = 0;
						for (Tuple b_sosed : Plosca.sosedi_bridge(x,y)) {
							if (igra.plosca.matrikaPolj[b_sosed.getY()][b_sosed.getX()] == Polje.MODRO) {
								stevec_bridge_sosedov++;
								if (Math.abs(y - b_sosed.getY()) == 2) {
									ocena_trenutne_plosce_za_modrega += 1200;
								} else {
									ocena_trenutne_plosce_za_modrega += 100;
								}
								ocena_trenutne_plosce_za_modrega -= 100 * (stevec_bridge_sosedov-1);
								List<Tuple> presek = Plosca.sosedi(x, y);
								presek.retainAll(Plosca.sosedi(b_sosed.getX(), b_sosed.getY()));
								int tmp = 0;
								for (Tuple t : presek) {
									if (igra.plosca.matrikaPolj[t.getY()][t.getX()] == Polje.MODRO) {
										ocena_trenutne_plosce_za_modrega += 1100;
									} else if (igra.plosca.matrikaPolj[t.getY()][t.getX()] == Polje.RDECE) {
										tmp += 1;
									} 
								}
								if (tmp == 2) {
									ocena_trenutne_plosce_za_modrega -=500;
								} 
							}
						}
					} 
				}
			}
			return ocena_trenutne_plosce_za_modrega;
		case POTEZA_RDECI:
			int ocena_trenutne_plosce_za_rdecega = 0;
			for (int x = 1; x <= Plosca.N; x ++) {
				for (int y = 1; y <= Plosca.N; y ++) {
					if (igra.plosca.matrikaPolj[y][x] == Polje.RDECE) {
						for (Tuple b_sosed : Plosca.sosedi_bridge(x,y)) {
							if (igra.plosca.matrikaPolj[b_sosed.getY()][b_sosed.getX()] == Polje.RDECE) {
								if (Math.abs(x - b_sosed.getX()) == 2) {
									ocena_trenutne_plosce_za_rdecega += 1000;
								} else {
									ocena_trenutne_plosce_za_rdecega += 500;
								}
								List<Tuple> presek = Plosca.sosedi(x, y);
								presek.retainAll(Plosca.sosedi(b_sosed.getX(), b_sosed.getY()));
								int tmp = 0;
								for (Tuple t : presek) {
									if (igra.plosca.matrikaPolj[t.getY()][t.getX()] == Polje.RDECE) {
										ocena_trenutne_plosce_za_rdecega += 200;
									} else if (igra.plosca.matrikaPolj[t.getY()][t.getX()] == Polje.MODRO) {
										tmp += 1;
									} 
								}
								if (tmp == 2) {
									ocena_trenutne_plosce_za_rdecega -= 1000;
								}
							}
						}
					}
				}
			}
			return ocena_trenutne_plosce_za_rdecega;
		}
		assert false;
		return 42; // Java je blesava
	} */




