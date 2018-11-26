int pcap;

int maxflowFF(TreeMap<Integer, Integer>[] g, int source, int sink) {
  int flow = 0;
  pcap = Integer.MAX_VALUE;
  while(augmentDFS(g, source, sink, new boolean[g.length])) {
    flow += pcap;
    pcap = Integer.MAX_VALUE;
  }
  return flow;
}

boolean augmentDFS(TreeMap<Integer, Integer>[] g, int cur, int sink, boolean[] done) {
  if(cur == sink) return true;
  if(done[cur]) return false;
  done[cur] = true;
  for(Entry<Integer, Integer> e : g[cur].entrySet()) {
    if(e.getValue() > 0) {
      int oldcap = pcap;
      pcap = Math.min(pcap, e.getValue());
      if(augmentDFS(g, e.getKey(), sink, done)) {
        g[cur].put(e.getKey(), e.getValue() - pcap);
        Integer backcap = g[e.getKey()].get(cur);
        g[e.getKey()].put(cur, backcap == null? pcap : backcap + pcap);
        return true;
      } else {
        pcap = oldcap;
      }
    }
  }
  return false;
}
