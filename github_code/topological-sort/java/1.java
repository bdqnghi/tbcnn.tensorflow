package test.companies.apple.experience;

import utils.Test;
import utils.Utils;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * @author: mizhang
 * @time: 3/25/15 11:36 AM
 */
public class TopologicalSort {
    public static void test(String packageName, String className, String methodName) throws InvocationTargetException, IllegalAccessException {
        try {
            Method method = Class.forName(packageName + "." + className).getMethod(methodName, Map.class);
            List<List<String>> expected = new ArrayList<List<String>>();
            expected.add(Utils.getList(new String[]{"A", "B", "D"}));
            expected.add(Utils.getList(new String[]{"A", "C", "D"}));
            expected.add(Utils.getList(new String[]{"A", "C", "E"}));

            Map<String, List<String>> dependencies = new HashMap<String, List<String>>();
            List<String> dependency = new ArrayList<String>();
            dependency.add("B");
            dependency.add("C");
            dependencies.put("A", dependency);

            dependency = new ArrayList<String>();
            dependency.add("D");
            dependencies.put("B", dependency);

            dependency = new ArrayList<String>();
            dependency.add("D");
            dependency.add("E");
            dependencies.put("C", dependency);

            Test.assertEquals(expected, method.invoke(null, dependencies));


            expected.clear();
            expected.add(Utils.getList(new String[]{"A", "B", "C"}));

            dependencies.clear();
            dependency = new ArrayList<String>();
            dependency.add("B");
            dependency.add("C");
            dependencies.put("A", dependency);

            dependency = new ArrayList<String>();
            dependency.add("C");
            dependencies.put("B", dependency);

            Test.assertEquals(expected, method.invoke(null, dependencies));


            expected.clear();
            expected.add(Utils.getList(new String[]{"A", "B", "C"}));

            dependencies.clear();
            dependency = new ArrayList<String>();
            dependency.add("B");
            dependencies.put("A", dependency);

            dependency = new ArrayList<String>();
            dependency.add("D");
            dependencies.put("B", dependency);

            dependency = new ArrayList<String>();
            dependency.add("D");
            dependencies.put("C", dependency);

            Test.assertEquals(expected, method.invoke(null, dependencies));
        } catch (Exception e) {
            System.err.println("Cannot find method " + methodName + " for class " + packageName + "." + className);
            e.printStackTrace();
        }
    }
}
