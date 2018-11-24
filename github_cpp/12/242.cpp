const int MAX = 100, INF = 12345678;

// N = Anzahl Knoten
// gr[i][j] = Kosten von Knoten i nach Knoten j
// nach Aufruf: via[i][j] = naechster Knoten auf dem kuerzesten Pfad von i nach j
int N, via[MAX][MAX], gr[MAX][MAX];

// wer nur die Distanzen braucht, nicht die tatsaechlichen Wege,
// kann auch alles mit "via" weglassen
void floydwarsh() {
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            via[i][j] = j;
    for (int k = 0; k < N; ++k)
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                if (gr[i][j] > gr[i][k] + gr[k][j]) {
                    gr[i][j] = gr[i][k] + gr[k][j];
                    via[i][j] = k;
                }
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            if (gr[i][j] < INF)
                while (via[i][j] != via[i][via[i][j]])
                    via[i][j] = via[i][via[i][j]];
}
