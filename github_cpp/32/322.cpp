// Obtiene el arbol de expansion minima de un
// grafo bidireccional. Para obtener el arbol
// de expansion maxima descomentar el reverse.
// En caso de tener varias componentes conexas,
// obtiene el bosque de expansion minima.
vector<Ponderada> Kruskal() {
  vector<Ponderada> todas;
  for (int u = 0; u < NODOS; ++u)
    for (CostoNodo arista : grafoCosto[u])
      todas.push_back(Ponderada(u, arista.second, arista.first) );
  sort(todas.begin(), todas.end());
  // reverse(todas.begin(), todas.end());
  vector<Ponderada> mst;
  UnionFind componentes(NODOS);
  for (Ponderada arista : todas) {
    int u = arista.x;
    int v = arista.y;
    if (!componentes.SonConexos(u, v))
      componentes.Unir(u, v), 
          mst.push_back(arista);
  }
  return mst;
}