#include <iostream>
#include <stack>
// Anthony Cecchini

using namespace std;


// the node class is used to creat list representation
class Node {

public:

    int SID = -1;

    Node* next = NULL;

    bool visited = false;


};

// here is the graph class
// assume we work on an undirected graph of 6 nodes (fix size)
// it has a matrix representation and a list representation
// ask students to input matrix representation
// and design a function to convert that to a list representation
class Graph {

public:

    Graph();

    void SetMatrix(int a, int b); // set Matrix[a][b] = Matrix[b][a] = 1
    // a and b must be in [0,5]

    void DeleteMatrix();  // reset matrix to zero

    void Convert(); // convert matrix representation to list
    // in the list, make sure nodes are sorted in an ascending order.

    void EnumerateList(); // enumerate all nodes in the list


    int* DFS(int idx);  // depth first search based on list representation
    // idx represents the first node to visit
    // whenever there is a tie, choose the smallest node to visit first
    // return a pointer to an array of 6 nodes based on the order they are visited
    // for example, if DFS visits 3, 5, 2, 0, 1, 4; then the array should have
    // x[0]=3, x[1]=5, x[2]=2, x[3]=0, x[4]=1, x[5]=4



private:

    int Matrix[6][6];

    Node* List[6];

};


// enumerate nodes in a list
void Graph::EnumerateList() {

    Node* temp;

    for (int i = 0; i < 6; i++) {

        cout << i << " -> ";

        if (List[i] != NULL) {

            temp = List[i];

            cout << temp->SID;

            while (temp->next != NULL) {

                temp = temp->next;

                cout << " -> "<< temp->SID << ' ';
            }
            cout << endl;
        }
    }
}


// SetMatrix Function
void Graph::SetMatrix(int a, int b) {

    Matrix[a][b] = 1;

    Matrix[b][a] = 1;
}


// DeleteMatrix Function
void Graph::DeleteMatrix() {

    for (int i = 0; i < 6; i++) {

        for (int j = 0; j < 6; j++) {

            Matrix[i][j] = 0;
        }
    }
}


// constructor
Graph::Graph() {

    for (int i = 0; i < 6; i++) {

        for (int j = 0; j < 6; j++) {

            Matrix[i][j] = 0;
        }

        List[i] = NULL;
    }
}

void Graph::Convert() {
    // Go through the y of the graph
    for (int i = 0; i < 6; i++) {
        Node* current = List[i];
        // Go through the x of the graph
        for (int j = 0; j < 6; j++) {
            // if the element is 1 the then we need to add it to the List[]
            if(Matrix[i][j] == 1){
                // If the list at I index is NULL set it to the node
                if(List[i] == NULL) {
                    // If the element in List[i] is null then add that node
                    Node *node = new Node;
                    node->SID = j;
                    List[i] = node;
                    current = List[i];

                } else {
                    // Else the neighbor will need to be linked to the node
                    Node *node = new Node;
                    node->SID = j;
                    current->next = node;
                    current = node;
                }

            }


        }
    }
}



int *Graph::DFS(int idx) {
    // Create an integer list called visit that is of size 6 that will hold the state of the visit
    static int visit[6];
    // I will be the stage of the visit that we are at
    int i = 0;
    // set the element
    visit[i] = idx;
    int mark[6] = {0,0,0,0,0,0};
    //
    mark[idx] = 1;
    for(i = 1; i < 6; i++){
        Node* temp = List[idx];
        while(temp != NULL){
            if(mark[temp->SID] != 1) {
                // set idx as temp->sid
                idx = temp->SID;
                visit[i] = idx;
                mark[idx] = 1;
                break;
            } else {
                // set temp to the neighbor
                temp = temp->next;
            }
        }
        // if the temp is null then we need to check if at index j in list mark has been visited or not
        if(temp == NULL){
            for(int j = 0; j < 6; j++){
                // check if mark[j] = 0
                if(mark[j] == 0){
                    idx = j;
                    break;
                }
            }
            visit[i] = idx;
            mark[idx]  =1;
        }
    }
    return visit;
}






int main()
{
    Graph graph;
    int a, b; // the values of a and b are between 0 and 5
    int* visit;
    // always input 8 edges
    for (int i = 0; i < 8; i++) {
        cin >> a >> b;
        graph.SetMatrix(a, b);
    }
    int idx;
    cin >> idx;
    // immediately convert matrix into list
    cout << "Adjacency List" << endl;
    graph.Convert();
    graph.DeleteMatrix();
    graph.EnumerateList();
    cout << "DFS" << endl;
    visit = graph.DFS(idx);
    for (int i = 0; i < 6; i++) {
        cout << visit[i] << ' ';
    }
    return 0;
}


