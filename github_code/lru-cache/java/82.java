import java.util.HashMap;
import java.util.Map;
import java.util.Queue;
import java.util.LinkedList;

public class LRU implements Service {

  private final int capacity;
  private final Service serv;
  private final Map<String,String> cache;
  private final Timeline requestTimeline;

  private LRU(Service serv, int capacity) {
    this.serv = serv;
    this.capacity = this.capacity;
    this.cache = new HashMap<>();
    this.requestTimeline = new Timeline(capacity);
  }

  public void cacheAnswer(String request, String answer) {
    cache.put(request, answer);
    String oldRequest = requestTimeline.push(request);
    if (oldRequest != null) {
      cache.remove(oldRequest);
    }
    assert(cache.size() == requestTimeline.size());
  }

  public String answerTo(String request) {
    String answerInCache = cache.get(request);
    if (answerInCache != null) {
      return answerInCache;
    } else {
      String answer = serv.answerTo(request);
      cacheAnswer(request, answer);
      return answer;
    }
  }

  public static Service cache(Service serv, int size) {
    return new LRU(serv, size);
  }

  public static void main(String[] argv) {
    System.exit(0);
  }

}
