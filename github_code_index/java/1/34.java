package br.com.mertins.ufpel.fia.exaustiva;

import br.com.mertins.ufpel.fia.util.BasicSearch;
import br.com.mertins.ufpel.fia.util.BoardState;
import br.com.mertins.ufpel.fia.util.Element;
import br.com.mertins.ufpel.fia.util.Observator;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.Set;

/**
 * Busca em amplitude no quebra-cabeça deslizante
 *
 * @author mertins
 */
public class BreadthFirstSearch extends BasicSearch {

    /**
     * Construtor para realizar busca em amplitude no quebra-cabeça deslizante
     *
     * @param observator classe responsável em receber as informações que
     * servirão ao relatório
     * @param isShuffle embaralhar qual candidato é visitável primeiro (reduz a
     * repetição de ir e vir da mesma peça)
     * @param withHash usa tabela de hash para evitar movimentos já avaliados
     */
    public BreadthFirstSearch(Observator observator, boolean isShuffle, boolean withHash) {
        super(observator, isShuffle, withHash);
    }

    @Override
    public List<BoardState> run() {
        Queue<BoardState> lista = new LinkedList<>();
        lista.add(beginState);
        int nivel = 0;
        long hashColision = 0;
        try {
            while (!lista.isEmpty()) {
                if (observator.isTimeOver()) {
                    observator.errSolution(nivel);
                    throw new RuntimeException(String.format("Tempo excedido! Nivel atingido [%s]", nivel));
                }
                BoardState testState = lista.poll();
//            this.board.print(testState);    // informações parciais
                if (!this.board.isTheSolution(testState)) {
                    nivel = testState.getHeight() + 1;
                    Element[] findCandidates = this.board.findCandidates(testState, isShuffle);
                    for (Element possibilidade : findCandidates) {
                        BoardState move = this.board.move(possibilidade, testState);
                        if (!withHash || !this.hashTable.contains(move)) {
                            move.setHeight(nivel);
                            move.setFather(testState);
                            if (withHash) {
                                this.hashTable.add(move);
                            }
                            lista.add(move);
                        } else {
                            observator.setHashColision(hashColision++);
                        }
                    }
                    observator.setChangePath(nivel);
                } else {
                    observator.okSolution();
                    lista.clear();
                    return this.makeSolution(testState);
                }
            }
        } catch (OutOfMemoryError ex) {
            observator.errSolution(nivel);
            lista.clear();
            throw new RuntimeException(String.format("Memory full! Nivel atingido [%s]", nivel));
        }
        observator.errSolution(nivel);
        throw new RuntimeException("Falha! Não encontrou solução e Collection vazia");
    }
}
