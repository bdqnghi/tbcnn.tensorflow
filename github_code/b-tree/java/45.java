import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.TreeMap;

public class B {
	public static void main(String args[]) {

		try {
			ArrayList<StudentSubmission> list = new ArrayList<StudentSubmission>();
			String shangjiFile = "�ϻ����.csv";
			// ���ļ�
			BufferedReader readshangjifile = new BufferedReader(
					new InputStreamReader(new FileInputStream(shangjiFile)));

			TreeMap<String, Integer> errorTimesMap = new TreeMap<String, Integer>();
			String a;
			a = readshangjifile.readLine();// ignore first line
			while ((a = readshangjifile.readLine()) != null) {
				StudentSubmission stu = new StudentSubmission();
				String s[] = a.split(",");
				stu.setRunID(s[0]);
				stu.setUser(s[1]);
				stu.setProblem(s[2]);
				stu.setResult(s[3]);
				stu.setSubmitTime(s[7]);
				list.add(stu);
				if (s[3].equals("Accepted")) {
					if (!errorTimesMap.containsKey(s[1])) {
						errorTimesMap.put(s[1], 0);
					}
					continue;
				}
				if (errorTimesMap.containsKey(s[1])) {// build errorTimesMap<User,errorTimes>
					int times = errorTimesMap.get(s[1]);
					errorTimesMap.put(s[1], times + 1);
				} else {
					errorTimesMap.put(s[1], 1);
				}
			}
			// HashMap<String, ArrayList<String>> problemMap = //user,problem(ABCDE,null)
			// new HashMap<String,ArrayList<String>>();
			HashMap<String, TreeMap<String, String>> problemMap = // user,problem(ABCDE,null)
					new HashMap<String, TreeMap<String, String>>();
			StudentSubmission currentEle;
			int size = list.size();// ����
			for (int i = 0; i < size; i++) {
				currentEle = list.get(i);
				if (currentEle.getResult().equals("Accepted")) {// if accepted ,add it;
					String currentUser = currentEle.getUser();
					TreeMap<String, String> Problem = new TreeMap<String, String>();
					if (problemMap.containsKey(currentUser)) {// if same person,add problem
						Problem = problemMap.get(currentUser);
						Problem.put(currentEle.getProblem(), "");
						problemMap.put(currentUser, Problem);
					} else {// if new person
						Problem.put(currentEle.getProblem(), "");
						problemMap.put(currentUser, Problem);
					}
				}
			}
			// int size2=problemMap.size();
			TreeMap<String, Integer> acTimesMap = new TreeMap<String, Integer>();
			int correct[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
			for (Map.Entry<String, TreeMap<String, String>> entry : problemMap.entrySet()) {
				int amount = entry.getValue().size();
				acTimesMap.put(entry.getKey(), amount);
				correct[amount] += 1;
			}
			int sum = 0;
			for (int j = 1; j < 8; j++) {
				System.out.println("Accepted " + j + " problem(s) has " + correct[j] + " persons");
				int min = 100;
				String name = null;
				for (Map.Entry<String, Integer> entry : acTimesMap.entrySet()) {//to find least errors person
					if (j == entry.getValue()) {
						int nowErrorTimes = errorTimesMap.get(entry.getKey());
						if (min > nowErrorTimes) {
							min = nowErrorTimes;
							name = entry.getKey();
						}
					}
				}
				System.out.println("The least errors of " + j + " accepted is " + name);
				sum += correct[j];
				if (j == 7)
					System.out.println("The sum of accepted are " + sum);
			}

			readshangjifile.close();
		} catch (Exception e) {
			e.printStackTrace();
		}

	}
}