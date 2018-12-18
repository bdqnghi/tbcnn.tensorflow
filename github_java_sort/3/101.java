

package br.imd.grafos.tad;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Queue;
import java.util.Set;
import java.util.Stack;


public class Grafo {
	public static final int BRANCO = 0;
	public static final int CINZA = 1;
	public static final int PRETO = 2;

	private List<Vertice> vertices;
	private boolean dirigido;

	private int tempoBusca;

	public Grafo(boolean dirigido) {
		this.dirigido = dirigido;
		this.vertices = new ArrayList<Vertice>();
	}

	public void adicionarVertice(Vertice novo) {
		
		novo.limparAdjacentes();
		vertices.add(novo);
	}

	public void removerVertice(Vertice vertice) {
		
		vertices.remove(vertice);
		
		for (Vertice v : vertices) {
			if (v.temAdjacente(vertice)) {
				v.removerAdjacente(vertice);
			}
		}

	}

	public void adicionarAresta(Vertice origem, Vertice destino) {
		if (!dirigido) {
			destino.adicionarAdjacente(origem,1);
		}
		origem.adicionarAdjacente(destino,1);
	}
	
	public void adicionarAresta(Vertice origem, Vertice destino, int peso) {
		if (!dirigido) {
			destino.adicionarAdjacente(origem,peso);
		}
		origem.adicionarAdjacente(destino,peso);
	}

	public void removerAresta(Vertice origem, Vertice destino) {
		if (!dirigido) {
			destino.removerAdjacente(origem);
		}

		origem.removerAdjacente(destino);
	}

	public void imprimirGrafo() {
		for (Vertice vertice : vertices) {
			System.out.print(vertice.getId() + " -> ");
			for (Vertice adjacente : vertice.getAdj().keySet()) {
				System.out.print(adjacente.getId() + ", ");

			}
			System.out.println();
		}
	}

	public void imprimirCoresGrafo() {
		for (Vertice vertice : vertices)
			System.out.println(vertice.getId() + " -> " + vertice.getCorToString());
	}

	public void imprimirDistanciasGrafo() {
		for (Vertice vertice : vertices){
			System.out.print(vertice.getId() + " -> ");
			if(vertice.getDistancia()== Integer.MAX_VALUE){
				System.out.println("inf");
			}else{
				System.out.println(vertice.getDistancia());
				
			}
		}
			
	}

	public void imprimirTemposGrafo() {
		for (Vertice vertice : vertices)
			System.out.println(vertice.getId() + " -> " + vertice.getDistancia() + "/" + vertice.getTempoFim());
		;
	}

	private void inicializaVertices() {
		for (Vertice vertice : vertices) {
			vertice.setCor(BRANCO);
			vertice.setDistancia(Integer.MAX_VALUE);
			vertice.setPai(null);
		}

	}

	
	public boolean buscaEmLargura(Vertice fonte) {

		
		inicializaVertices();

		if (fonte == null) {
			return false;
		}
		fonte.setCor(CINZA);
		fonte.setDistancia(0);

		Queue<Vertice> fila = new LinkedList<Vertice>();
		fila.add(fonte);
		Vertice u;

		
		while (!fila.isEmpty()) {
			u = fila.remove();
			Set<Vertice> adj = u.getAdj().keySet();
			
			for (Vertice v : adj) {
				if (v.getCor() == BRANCO) {
					v.setCor(CINZA);
					v.setDistancia(u.getDistancia() + 1);
					v.setPai(u);
					fila.add(v);
				}
			}
			
			u.setCor(PRETO);

		}

		return true;
	}

	
	public void imprimirCaminho(Vertice s, Vertice v) {
		if (s.equals(v)) {
			System.out.println("1");
			System.out.println(s.getId());
		} else if (v.getPai() == null) {
			System.out.println("2");
			System.out.println("não tem caminho de " + s.getId() + " até " + v.getId());
		} else {
			System.out.println("3");
			imprimirCaminho(s, v.getPai());
		}
	}

	
	public boolean buscaEmProfundidade(Vertice fonte) {
		if (fonte == null) {
			return false;
		}
		
		inicializaVertices();

		tempoBusca = 0;

		for (Vertice u : vertices) {
			if (u.getCor() == BRANCO) {
				buscaEmProfundidadeVisit(u);
			}
		}
		return true;
	}

	
	private void buscaEmProfundidadeVisit(Vertice u) {
		
		tempoBusca += 1;
		u.setDistancia(tempoBusca);
		u.setCor(CINZA);
		
		for (Vertice v : u.getAdj().keySet()) {
			if (v.getCor() == BRANCO) {
				v.setPai(u);
				buscaEmProfundidadeVisit(v);
			}
		}
		
		u.setCor(PRETO);
		tempoBusca += 1;
		u.setTempoFim(tempoBusca);

	}

	
	public void ordenacaoTopologica() {

		
		Stack<Vertice> filaOrdemTopologica = new Stack<Vertice>();
		
		
		inicializaVertices();
		
		
		tempoBusca = 0;

		for (Vertice u : vertices) {
			
			if (u.getCor() == BRANCO) {
				
				ordenacaoTopologicaVisit(u, filaOrdemTopologica);
				
			}
		}
		
		
        while (filaOrdemTopologica.empty()==false)
            System.out.print(filaOrdemTopologica.pop().getId() + " ");
	}

	
	private void ordenacaoTopologicaVisit(Vertice u, Stack<Vertice> ordemTopologica) {
		
		tempoBusca += 1;
		u.setDistancia(tempoBusca);
		u.setCor(CINZA);
		
		
		for (Vertice v : u.getAdj().keySet()) {
			if (v.getCor() == BRANCO) {
				v.setPai(u);
				ordenacaoTopologicaVisit(v, ordemTopologica);
			}
		}
		
		u.setCor(PRETO);
		tempoBusca += 1;
		u.setTempoFim(tempoBusca);
		ordemTopologica.push(u);

	}

	
	private void inicializaFonteUnica(Vertice fonte){
		for (Vertice vertice : vertices) {
			vertice.setDistancia(Integer.MAX_VALUE);
			vertice.setPai(null);
		}
		fonte.setDistancia(0);
	}
	
	
	private void relaxamento(Vertice u, Vertice v){
		int peso = u.getAdj().get(v);
		if(v.getDistancia()>(u.getDistancia()+peso)){
			v.setDistancia(u.getDistancia()+peso);
			v.setPai(u);
		}			
	}
	
	
	public boolean caminhoMinimoFonteUnica(Vertice fonte){
		this.inicializaFonteUnica(fonte);
		System.out.println(vertices.size());
		for (int i = 0; i < vertices.size(); i++) {
			
			System.out.println("Passagem "+i+":");
			this.imprimirDistanciasGrafo();
			
			for (Vertice u: vertices){
				for (Vertice v : u.getAdj().keySet()) {
					this.relaxamento(u, v);
				}			
			}
		}		
		
		for (Vertice u: vertices){
			for (Vertice v : u.getAdj().keySet()) {
				int peso = u.getAdj().get(v);
				if(v.getDistancia()>(u.getDistancia()+peso)){
					return false;
				}			
			}
		}
		return true;
		
		
	}
	
	
}
