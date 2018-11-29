package vn.me.ui.common;

import java.io.*;
import javax.microedition.lcdui.Image;

public class Resource {

    public static int BFS_EOF;
    private static String bfs_filename;
    private static byte[] preloaded_data_file = null;
    private static int[] bfs_files;
    public static int percent = 0;

    public static void setFileTable(String filename) {
        Resource.bfs_files = null;
        Resource.bfs_filename = filename;
    }

    public static Image createImage(String resourceFile, int imageIndex) {
        String oldResourceFile = bfs_filename;
        Resource.setFileTable(resourceFile);
        Image img = Resource.createImage(imageIndex);
        Resource.setFileTable(oldResourceFile);
        return img;
    }

    private static void getFileTable() {
        if (bfs_files == null) {
            try {
                //#if Android
//#                 InputStream is = Resource.class.getResourceAsStream(bfs_filename);
                //#else
                InputStream is = ResourceManager.getInputStreamFromFile(bfs_filename);
                //#endif
                DataInputStream din = new DataInputStream(is);
                int num_files = din.readInt();
                bfs_files = new int[num_files];
                int offset = 0;
                int header_size = (num_files << 2) + 4;
                for (int i = 0; i < num_files; i++) {
                    offset = din.readInt();
                    bfs_files[i] = offset + header_size;
                }
                din.close();
            } catch (Exception e) {
//                System.out.println("BamFS getFileTable error: " + e.toString());
            }
        }
    }

    public static InputStream getFileAsStream(int file_id) {
        getFileTable();
        if (preloaded_data_file == null) {

            byte[] file = getFile(file_id);
            ByteArrayInputStream bis = new ByteArrayInputStream(file);
            return bis;
        } else {
            int size = bfs_files[file_id + 1] - bfs_files[file_id];
            int offset = bfs_files[file_id];
            ByteArrayInputStream bis = new ByteArrayInputStream(preloaded_data_file, offset, size);
            return bis;
        }
    }

    public static void preload_files(int numberOfFile) {
        BFS_EOF = numberOfFile;
        getFileTable();
        if (preloaded_data_file == null) {
//            byte[] file = new byte[1];
            try {
                //#if Android
//#                 InputStream is = Resource.class.getResourceAsStream(bfs_filename);
//#                 BufferedInputStream din = new BufferedInputStream(is);
                //#else
                InputStream is = ResourceManager.getInputStreamFromFile(bfs_filename);
                DataInputStream din = new DataInputStream(is);
                //#endif
                preloaded_data_file = new byte[bfs_files[numberOfFile]];
                din.read(preloaded_data_file);
                din.close();
            } catch (Exception e) {
//                System.out.println("BamFS preload_files error: " + e.toString());
            }

        }
    }

    public static void free_preloaded_files() {
        preloaded_data_file = null;
        //System.gc();
    }

    public static byte[] getFile(int file_id) {
        getFileTable();
        byte[] file = new byte[1];
        try {
            //#if Android
//#             InputStream is = Resource.class.getResourceAsStream(bfs_filename);
//#             BufferedInputStream din = new BufferedInputStream(is);
            //#else
            InputStream is = ResourceManager.getInputStreamFromFile(bfs_filename);
            DataInputStream din = new DataInputStream(is);
            //#endif
            int size = bfs_files[file_id + 1] - bfs_files[file_id];
            int offset = bfs_files[file_id];
            file = new byte[size];
            din.skip(offset);
            din.read(file);
            din.close();
        } catch (Exception e) {
//            System.out.println("BamFS getFile error: " + e.toString());
        }
        percent++;
        return file;
    }

    public static Image createImage(int file_id) {
        getFileTable();
        //  Image return_img = null;
        Image return_img = Image.createImage(1, 1);
        try {
            if (preloaded_data_file == null) {
                byte[] img = getFile(file_id);
                return_img = Image.createImage(img, 0, img.length);
                img = null;
            } else {
                int size = bfs_files[file_id + 1] - bfs_files[file_id];
                int offset = bfs_files[file_id];
                return_img = Image.createImage(preloaded_data_file, offset, size);

            }
        } catch (Exception e) {
//            System.out.println("BamFS createImage error:" + e.toString());
        }
        percent++;
        return return_img;
    }
}
