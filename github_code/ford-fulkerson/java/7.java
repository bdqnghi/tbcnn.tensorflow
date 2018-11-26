package main.console;

import main.api.FordFulkersonAlgorythm;
import main.api.Graph;
import main.data.DataObject;
import main.data.DataReader;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Main {

    public static void main(String[] args) {
        DataReader dr = new DataReader("task_4_01_n2_m2_T2.txt");
        DataObject dao = dr.getDataFromFile();
        System.out.println("Содержимое файла:");
        dao.printData();
        Graph g = new Graph(dao);
        System.out.println("Матричный вид графа:");
        g.printMatrix();
        FordFulkersonAlgorythm ffa = new FordFulkersonAlgorythm(g);
        System.out.println("Максимальный поток: " + ffa.maxFlow());
        ffa.checkSystem();
        System.out.println("Минимальный объем склада для обеспечения совместности системы: " + findMinStorageSize(dao));
        System.out.println("Минимальное количество складов для обеспечения совместности системы: " + findMinStorageNum(dao));
    }

    public static boolean checkSystemByStorageSize(Graph g, int value) {
        g.createStoragesForAllBuyers(value);
        FordFulkersonAlgorythm ffa = new FordFulkersonAlgorythm(g);
        int flow = ffa.maxFlow();
        if (flow == g.getCheckSystem()) {
            return true;
        } else {
            return false;
        }
    }

    public static int findMinStorageSize(DataObject dao) {
        int mid = 0;
        Graph g = new Graph(dao);
        int num = g.getMaxValue();
        int low = 1;
        int high = num;
        while (low != high) {
            mid = (low + high) / 2;
            g = new Graph(dao);
            if (checkSystemByStorageSize(g, mid)) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }
        return mid;
    }

    public static int findMinStorageNum(DataObject dao) {
        boolean flag = true;
        int buyerSize = dao.getM();
        while (true) {
            Graph g = new Graph(dao);
            for (int i = 0; i < buyerSize; i++) {
                g.addStorage(g.getMaxValue(),i);
            }
            FordFulkersonAlgorythm ffa = new FordFulkersonAlgorythm(g);
            ffa.maxFlow();
            flag = ffa.checkSystemToBool();
            if (flag) {
                buyerSize--;
            } else {
                return ++buyerSize;
            }
        }
    }
}