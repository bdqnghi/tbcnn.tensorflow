















#include <xnetwork.hpp> 
from collections import deque

static const auto __all__ = ["bfs_edges", "bfs_tree", "bfs_predecessors", "bfs_successors"];


auto generic_bfs_edges(G, source, neighbors=None) {
    
    visited = {source}
    queue = deque([(source, neighbors(source))]);
    while (queue) {
        parent, children = queue[0];
        try {
            child = next(children);
            if (child not : visited) {
                yield parent, child
                visited.add(child);
                queue.append((child, neighbors(child)));
        } catch (StopIteration) {
            queue.popleft();


auto bfs_edges(G, source, reverse=false) {
    
    if (reverse && G.is_directed() {
        successors = G.predecessors
    } else {
        successors = G.neighbors
    
    for (auto e : generic_bfs_edges(G, source, successors) {
        yield e


auto bfs_tree(G, source, reverse=false) {
    
    T = xn::DiGraph();
    T.add_node(source);
    T.add_edges_from(bfs_edges(G, source, reverse=reverse));
    return T


auto bfs_predecessors(G, source) {
    
    for (auto s, t : bfs_edges(G, source) {
        yield (t, s);


auto bfs_successors(G, source) {
    
    parent = source
    children = [];
    for (auto p, c : bfs_edges(G, source) {
        if (p == parent) {
            children.append(c);
            continue;
        yield (parent, children);
        children = [c];
        parent = p
    yield (parent, children);
