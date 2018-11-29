package prehandle;



import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.HashMap;
import java.util.Map;
import java.util.Properties;

/**
 * Created by 张超 on 2017/9/21.
 */
public class Min_Edit_Distance {
    //源路径
    private static String inputUrl;
    //输出路径
    private static String outputUrl;
    //加载配置文件
    static {
        InputStream inputStream=Min_Edit_Distance.class.getClassLoader().getResourceAsStream("configuration.properties");
        Properties prop = new Properties();
        try {
            prop.load(inputStream);
            inputStream.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
        inputUrl = prop.getProperty("inputUrl").trim();
        outputUrl = prop.getProperty("outputUrl").trim();
    }

    //主方法
    public  void start(){
        Map<String, File> inputFiles=getAllPath(inputUrl);
        for (String cFileName : inputFiles.keySet()) {
            try {
//                FileInputStream fis = new FileInputStream(inputFiles.get(cFileName));
//                HWPFDocument doc = new HWPFDocument(fis);
//                String doc1 = doc.getDocumentText();
//                System.out.println(doc1);
//                StringBuilder doc2 = doc.getText();
//                System.out.println(doc2);
//                Range rang = doc.getRange();
//                String doc3 = rang.text();
//                System.out.println(doc3);
//                fis.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

    // 根据文件路径查找该路径下的所有文件并返回所有文件的路径
    public static Map<String, File> getAllPath(String filePath) {
        File file = new File(filePath);
        Map<String, File> fileMap = new HashMap<String, File>();
        if (file.exists()) {
            File[] files = file.listFiles();
            for (File file2 : files) {
                fileMap.put(file2.getName(), file2);
            }

        }
        return fileMap;

    }
    //编辑距离算法
    private static int cost = 0;
    public static int minEdit_distance(String source, String target)
    {
        final int n = target.length();
        final int m = source.length();
        if(m == 0 )return m;
        if(n == 0)return n;
        int[][] distance_matrix = new int[m+1][n+1];
        distance_matrix[0][0] = 0;
        for(int i=0;i <= n;i++){
            distance_matrix[0][i] = i;
        }
        for(int j=0;j <= m;j++){
            distance_matrix[j][0] = j;
        }
        for(int i=1;i <= m;i++){
            char ci = source.charAt(i - 1);
            for(int j=1;j <= n;j++){
                char cj = target.charAt(j - 1);
                if(ci == cj){
                    cost = 0;
                }else{
                    cost = 2;
                }
                distance_matrix[i][j] = Math.min(distance_matrix[i-1][j-1]+cost, Math.min(distance_matrix[i-1][j]+1, distance_matrix[i][j-1]+1));
            }
        }

        return distance_matrix[m][n];
    }

    //取最长
    int max(String source,String target){
        int sourceL=source.length();
        int targetL=target.length();
        if(sourceL>targetL){
            return sourceL;
        }
        return targetL;
    }

    //获取两字符串相似度
    public float getSimilarityRatio(String source, String target){
        return 1-(float)minEdit_distance(source,target)/this.max(source,target);
    }

//    public static void main(String[] args){
//
//        String source = "chin";
//        String target = "china";
//
//        System.out.println("最小编辑距离是："+minEdit_distance(source,target));
//        Min_Edit_Distance min=new Min_Edit_Distance();
//        float similarityRadio=1-(float)minEdit_distance(source,target)/min.max(source,target);
//        System.out.println("相似度是："+similarityRadio);
//    }
}