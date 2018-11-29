package Chapter1;


import java.util.HashMap;
import java.util.LinkedList;
import java.util.Map;
import java.util.Queue;

public class BFS {

    /**
     * 广度优先搜索（Java 简单实现）
     * 找我的朋友圈是否有芒果经销商
     */

    public static boolean BFS() {
        // 用Map 构造一个图
        Map<String, String[]> map = new HashMap<String, String[]>();
        map.put("you", new String[]{"alice", "bob", "claire"});
        map.put("bob", new String[]{"anuj", "peggy"});
        map.put("alice", new String[]{"peggy"});
        map.put("claire", new String[]{"thom", "jonny"});
        map.put("anuj", new String[]{});
        map.put("peggy", new String[]{});
        map.put("thom", new String[]{});
        map.put("jonny", new String[]{});

        //把每个节点放进队列中
        Queue<String> queue = new LinkedList<String>();
        //先把出发节点放入
        queue.offer("you");
        //队列不为空则取出节点
        while (!queue.isEmpty()) {
            //从map中获取相邻节点,加入队列
            String start = queue.element();
            if (start.equals("anuj")) {
                System.out.println(start + "is a mango seller!");
                break;
            } else {
                String[] arr = map.get(start);
                //出队伍
                queue.poll();
                for (int i = 0; i < arr.length; i++) {
                    queue.offer(arr[i]);
                }
            }
        }
        System.out.println("no one is a mango seller ");
        return false;
    }

}
