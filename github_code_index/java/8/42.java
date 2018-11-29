package LawStandard;


import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;



//鏈�皬缂栬緫璺濈鐨勭畻娉曞姩鎬佽鍒掑疄鐜�
public class EditDistance {
	private static int cost = 0;

	public static int minEdit_distance(String source, String target) {
		final int n = target.length();//n涓虹洰鏍囦覆闀垮害
		final int m = source.length();//m涓烘簮涓查暱搴�

		if (m == 0)
			return m;      
		if (n == 0)  
			return n;

		int[][] distance_matrix = new int[m + 1][n + 1];//锛坢+1锛�锛坣+1锛夌殑璺濈鐭╅樀
		distance_matrix[0][0] = 0;

		for (int i = 0; i <= n; i++) {

			distance_matrix[0][i] = i;
		}
		for (int j = 0; j <= m; j++) {

			distance_matrix[j][0] = j;
		}

		for (int i = 1; i <= m; i++) {	//瀵规簮涓茬殑姣忎釜瀛楃杩涜閬嶅巻

			char ci = source.charAt(i - 1);    //婧愪覆鐨勭鍑犱釜瀛楃

			for (int j = 1; j <= n; j++) {

				char cj = target.charAt(j - 1);		//鐩爣涓茬殑绗嚑涓瓧绗�

				if (ci == cj) {

					cost = 0;

				} else {

					cost = 2;
				}

				distance_matrix[i][j] = Math.min(distance_matrix[i - 1][j - 1] + cost,
						Math.min(distance_matrix[i - 1][j] + 1, distance_matrix[i][j - 1] + 1));

			}
		}

		return distance_matrix[m][n];
	}

	public static String standard_law(String source) throws Exception{
		List<String> law_list=new ArrayList<String>();
		List<Integer> distance=new ArrayList<Integer>();
		BufferedReader br=new BufferedReader(new InputStreamReader(new FileInputStream("C:\\Users\\Administrator\\Desktop\\jin\\规范法条名称.txt"),"utf-8"));
		String line;
		line = br.readLine();
		
		while(line!=null){
			
			law_list.add(line);
			distance.add(minEdit_distance(source,line));
			line = br.readLine();
		}
		br.close();
		int min_index=distance.indexOf(Collections.min(distance));
		return law_list.get(min_index);
		
	}
	
	public static List<String> whole_laws(String source) throws Exception{
		source.replaceAll("[^(\\u4e00-\\u9fa5)]", "").replaceAll("(?i)[^a-zA-Z0-9\u4E00-\u9FA5]", "");
		
		String[] laws=source.split(";");
		List<String> myCorrectLaw=new ArrayList<String>();
		
		for(int i=0;i<laws.length;i++){
			String[] tempLaw=laws[i].split("第");
			String tempStandardLaw=standard_law(tempLaw[0]);
			List<String> tempTiaoMu=Fenshu.fen(laws[i].split(""));
			if(tempTiaoMu==null){
				continue;
			}
			for(int j=0;j<tempTiaoMu.size();j++){
				
				myCorrectLaw.add(tempStandardLaw+"第"+tempTiaoMu.get(j)+"条");
			}
		}
		return myCorrectLaw;
	} 
	
	
	public static void main(String[] args) throws Exception {

		String source = "中华人民币共和国>>婚姻法第三十二条第一款第三十四条第三十五条;中华人民币共和国婚姻法第三十九条";
		

		List<String> mylist=whole_laws(source);
		for(int i=0;i<mylist.size();i++){
			System.out.println(mylist.get(i));
		}
	}
}
