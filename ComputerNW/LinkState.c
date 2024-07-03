#include <stdio.h>

#define LIMIT 10
#define INFINITY 10000

int numNodes, distance, i, j, distances[LIMIT][LIMIT], srcNode, destNode, minDist = 0;

struct Node {
    int helloPackets[LIMIT];
    int neighborCount;
    int adjacency[LIMIT];
} nodes[LIMIT];

int shortestPath(int source, int target, int min) {
    struct State {
        int predecessor;
        int length;
        enum { permanent, tentative } label;
    } state[LIMIT];

    int currentNode, i;
    struct State *p;

    for (p = &state[1]; p <= &state[numNodes]; p++) {
        p->predecessor = 0;
        p->length = INFINITY;
        p->label = tentative;
    }

    state[target].length = 0;
    state[target].label = permanent;
    currentNode = target;

    do {
        for (i = 1; i <= numNodes; i++) {
            if (distances[currentNode][i] != 0 && state[i].label == tentative) {
                if (state[currentNode].length + distances[currentNode][i] < state[i].length) {
                    state[i].predecessor = currentNode;
                    state[i].length = state[currentNode].length + distances[currentNode][i];
                }
            }
        }
        currentNode = 0;
        min = INFINITY;
        for (i = 1; i <= numNodes; i++) {
            if (state[i].label == tentative && state[i].length < min) {
                min = state[i].length;
                currentNode = i;
            }
        }
        state[currentNode].label = permanent;
    } while (currentNode != source);

    return min;
}

int main() {
    printf("Enter the number of nodes: ");
    scanf("%d", &numNodes);

    // Initialize distance matrix
    for (i = 1; i <= numNodes; i++)
        for (j = 1; j <= numNodes; j++)
            distances[i][j] = -1;

    // Input distances between nodes
    for (i = 1; i <= numNodes; i++) {
        printf("Enter distance for node %d: ", i);
        for (j = 1; j <= numNodes; j++) {
            if (distances[i][j] == -1) {
                if (i == j) {
                    distances[i][j] = 0;
                    printf("0 ");
                } else {
                    scanf("%d", &distance);
                    distances[i][j] = distances[j][i] = distance;
                }
            } else {
                printf("%d ", distances[i][j]);
            }
        }
    }

    printf("\nDistance matrix:\n");
    for (i = 1; i <= numNodes; i++) {
        nodes[i].neighborCount = 0;
        for (j = 1; j <= numNodes; j++) {
            printf("%d\t", distances[i][j]);
        }
        printf("\n");
    }

    printf("\nSending hello packets\n");
    for (i = 1; i <= numNodes; i++) {
        int k = 1;
        for (j = 1; j <= numNodes; j++) {
            if (distances[i][j] > 0)
                nodes[i].neighborCount++;
            if (distances[j][i] > 0)
                nodes[i].helloPackets[k++] = j;
        }
    }

    for (i = 1; i <= numNodes; i++) {
        printf("Hello packets to node %d: ", i);
        for (j = 1; j <= nodes[i].neighborCount; j++)
            printf("%d ", nodes[i].helloPackets[j]);
        printf("\n");
    }

    printf("Sending echo packets\n");
    for (i = 1; i <= numNodes; i++) {
        for (j = 1; j <= numNodes; j++) {
            if (distances[i][j] > 0)
                printf("From %d to %d, the distance is: %d\n", i, j, distances[i][j]);
        }
    }

    printf("Construction of link state packets\n");
    for (i = 1; i <= numNodes; i++) {
        printf("Link state packet for node %d\n", i);
        printf("|-------------|\n| %d |\n|-------------|\n| Seq |\n|-------------|\n| Age |\n|-------------|\n", i);
        for (j = 1; j <= numNodes; j++) {
            if (distances[i][j] > 0) {
                printf("| %d %d |\n|-------------|\n", j, distances[i][j]);
            }
        }
    }

    printf("Distributing the link state packets\n");
    for (i = 1; i <= numNodes; i++) {
        printf("Neighbors for node %d are: ", i);
        for (j = 1; j <= numNodes; j++) {
            if (distances[i][j] > 0)
                printf("%d ", j);
        }
        for (j = 1; j <= nodes[i].neighborCount; j++) {
            printf("\nThe distance from %d to %d is %d", i, nodes[i].helloPackets[j], distances[i][nodes[i].helloPackets[j]]);
        }
        printf("\n");
    }

    printf("Computing the shortest path\n");
    printf("Enter source and destination: ");
    scanf("%d %d", &srcNode, &destNode);
    minDist = shortestPath(srcNode, destNode, minDist);
    printf("Minimum distance: %d\n", minDist);

    return 0;
}