package week5_Max.fileSearch;

import java.io.File;
import java.util.*;

public class BreadthFirstSearch {
    private Node<File> node;
    private File root;
    private String word;
    private Queue<Node<File>> queue;
    private List<String> res;

    public BreadthFirstSearch(String path, String word) {
        node = new Node<>(new File(path));
        this.word = word;
        queue = new ArrayDeque<>();
        res = new ArrayList<>();
    }

    public void search() {
        Set<String> set = new HashSet<>();
        queue.add(node);
        do {
            root = node.getFile();
            if (root != null) {
                File[] files = root.listFiles();
                for (File file : files) {
                    if (file.isDirectory()) {
                        queue.offer(new Node<>(file));
                    }
                    if (file.getName().contains(word)) {
                        set.add(file.getAbsolutePath());
                    }
                }
            }
            node = queue.poll();
        } while (node != null);
        res.addAll(set);
        res.stream().forEach(System.out::println);
    }


    private static class Node<File> {
        private File root;

        public Node(File root) {
            this.root = root;
        }

        public File getFile() {
            return root;
        }
    }
}

