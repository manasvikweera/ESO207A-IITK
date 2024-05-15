#include <stdio.h>
#include <stdlib.h>

#define INF 99999
#define MAX_NODES 1000

typedef struct Edge {
     int weight;
     int src;
     int dest;
} Edge;

typedef struct MinHeapNode {
     int v;
     int key;
} MinHeapNode;

typedef struct MinHeap {
     int size;
     int capacity;
     int *pos;
     MinHeapNode **nodes;
} MinHeap;

int r;
int V;
int E;
int graph[MAX_NODES][MAX_NODES];
MinHeap *heap;
int *parent;
Edge *MST;

void init_min_heap(int capacity) {
     heap = (MinHeap *) malloc(sizeof(MinHeap));
     heap->size = 0;
     heap->capacity = capacity;
     heap->pos = (int *) malloc(capacity * sizeof(int));
     heap->nodes = (MinHeapNode **) malloc(capacity * sizeof(MinHeapNode 
*));
}

void destroy_min_heap() {
     free(heap->pos);
     free(heap->nodes);
     free(heap);
}

MinHeapNode *create_min_heap_node(int v, int key) {
     MinHeapNode *node = (MinHeapNode *) malloc(sizeof(MinHeapNode));
     node->v = v;
     node->key = key;
     return node;
}

void swap_nodes(MinHeapNode **a, MinHeapNode **b) {
     MinHeapNode *t = *a;
     *a = *b;
     *b = t;
}

void min_heapify(int idx) {
     int smallest = idx;
     int left = r * idx + 1;
     int right = r * idx + r;
     for (int i = left; i < heap->size && i <= right; i++) {
         if (heap->nodes[i]->key < heap->nodes[smallest]->key) {
             smallest = i;
         }
     }
     if (smallest != idx) {
         MinHeapNode *smallest_node = heap->nodes[smallest];
         MinHeapNode *idx_node = heap->nodes[idx];
         heap->pos[smallest_node->v] = idx;
         heap->pos[idx_node->v] = smallest;
         swap_nodes(&heap->nodes[smallest], &heap->nodes[idx]);
         min_heapify(smallest);
     }
}

int is_min_heap_empty() {
     return heap->size == 0;
}

MinHeapNode *extract_min() {
     MinHeapNode *min_node = heap->nodes[0];
     MinHeapNode *last_node = heap->nodes[heap->size - 1];
     heap->nodes[0] = last_node;
     heap->pos[min_node->v] = heap->size - 1;
     heap->pos[last_node->v] = 0;
     heap->size--;
     min_heapify(0);
     return min_node;
}

void decrease_key(int v, int key) {
     int idx = heap->pos[v];
     heap->nodes[idx]->key = key;
     while (idx && heap->nodes[idx]->key < heap->nodes[(idx - 1) / 
r]->key) {
         MinHeapNode *curr_node = heap->nodes[idx];
         MinHeapNode *parent_node = heap->nodes[(idx - 1) / r];
         heap->pos[curr_node->v] = (idx - 1) / r;
         heap->pos[parent_node->v] = idx;
         swap_nodes(&heap->nodes[idx], &heap->nodes[(idx - 1) / r]);
         idx = (idx -1);
}
}
void add_edge_to_mst(Edge e, int idx) {
MST[idx].src = e.src;
MST[idx].dest = e.dest;
MST[idx].weight = e.weight;
}

void prim_mst() {
parent[0] = -1;
decrease_key(0, 0);
while (!is_min_heap_empty()) {
MinHeapNode *min_node = extract_min();
int u = min_node->v;
for (int v = 0; v < V; v++) {
if (graph[u][v] && heap->pos[v] < heap->size && graph[u][v] < 
heap->nodes[heap->pos[v]]->key) {
parent[v] = u;
decrease_key(v, graph[u][v]);
}
}
}

for (int i = 1; i < V; i++) {
Edge e;
e.src = parent[i];
e.dest = i;
e.weight = graph[i][parent[i]];
add_edge_to_mst(e, i - 1);
}
}

void print_mst() {
int total_weight = 0;
printf("Minimum Spanning Tree:\n");
for (int i = 0; i < V - 1; i++) {
printf("(%d, %d) - %d\n", MST[i].src, MST[i].dest, MST[i].weight);

total_weight += MST[i].weight;
}
printf("Total weight: %d\n", total_weight);
}

int main() {printf("Enter the number of vertices and edges in the graph: ");
scanf("%d %d", &V, &E);
r = 2 + (E / V);
for (int i = 0; i < V; i++) {
for (int j = 0; j < V; j++) {
graph[i][j] = 0;
}
}
for (int i = 0; i < E; i++) {
int src, dest, weight;
printf("Enter the source, destination and weight of edge %d: ", i + 1);
scanf("%d %d %d", &src, &dest, &weight);
graph[src][dest] = weight;
graph[dest][src] = weight;
}
parent = (int *) malloc(V * sizeof(int));
MST = (Edge *) malloc((V - 1) * sizeof(Edge));
init_min_heap(V);
for (int v = 1; v < V; v++) {
parent[v] = -1; heap->nodes[v] = create_min_heap_node(v, INF);
heap->pos[v] = v;
}
heap->nodes[0] = create_min_heap_node(0, 0);
heap->pos[0] = 0;
heap->size = V;
prim_mst();
print_mst();
destroy_min_heap();
free(parent);
free(MST);
return 0;
}
