#include <iostream>
#include <queue>
#include <vector>
#include <stack>
using namespace std;

int* dijkstra_algo(int matrix[5][5] , int src){

    int rows = 5;
    int cols = 5;

    queue<int> nextVisit;
    vector<int> precede(rows, -1);
    vector<int> dist(rows, INT_MAX);
    vector<bool> visited(rows, false);

    dist[src] = 0;

    nextVisit.push(src);

    while(!nextVisit.empty()){
        int currVertex = nextVisit.front();
        nextVisit.pop();
        if(!visited[currVertex]){
            for(int neighor=0; neighor < rows; neighor++){
                int weight = matrix[currVertex][neighor];
                if(neighor != currVertex && weight && dist[neighor] > dist[currVertex] + weight){
                    dist[neighor] = dist[currVertex] + weight;
                    nextVisit.push(neighor);
                    precede[neighor] = currVertex;
                }
            }
            visited[currVertex] = true;
        }

    }

    // to print distance
    cout<< "\ndist: ";
    for(int i=0; i<rows; i++){
        cout << dist[i] << ", ";
    }

    //to print path for each vertex
    cout<< "\nprecede:-";
    for(int i=0; i<rows; i++){
        int curr = i;
        cout<< "\nIndex" << i << ": ";
        while(precede[curr] != -1) {cout << "->" << precede[curr]; curr = precede[curr];}
    }

    return NULL;
}

void printfl(vector<float> arr){
    for(auto i: arr){
        cout << i << ", ";
    }
}

void printi(vector<int> arr){
    for(auto i: arr){
        cout << i << ", ";
    }
}

void brandes_algo(vector<vector<int>> adjMatrix, bool undirected){

    int rows = adjMatrix.size();
    int cols = adjMatrix.size();
    vector<float> CB(rows, 0);

    for(int src=0; src<rows; src++){
        cout << "\ndegug 1";
        vector<float> singleVertexDependency(rows);
        vector<vector<int>> successors(rows);
        vector<int> dist(rows, -1);
        vector<float> shortestPath(rows, 0);
        vector<bool> visited(rows, false);
        stack<int> path;
        queue<int> nextVisitQueue;

        //
        nextVisitQueue.push(src);
        shortestPath[src] = 1;
        dist[src]=0;

        while(!nextVisitQueue.empty()){
            cout << "\ndegug 2";
            int currVertex = nextVisitQueue.front();
            nextVisitQueue.pop();
            if(!visited[currVertex]){

                visited[currVertex] = true;
                vector<int> currVertexAdjList = adjMatrix[currVertex];
                path.push(currVertex);
                for(int adjVertex=0; adjVertex<cols; adjVertex++){
                    cout << "\ndegug 3";
                    if(currVertexAdjList[adjVertex]){
                        cout << "\ndegug 4";
                        if(dist[adjVertex] < 0) {
                            cout << "\ndegug 5";
                            dist[adjVertex] = dist[currVertex] + 1;
                            nextVisitQueue.push(adjVertex);
                        }

                        if(dist[adjVertex] == dist[currVertex] + 1){
                            cout << "\ndegug 6";
                            shortestPath[adjVertex] += shortestPath[currVertex];
                            successors[currVertex].push_back(adjVertex);
                        }
                    }

                }
        
            }
        }

        cout << "\n----------------------------partial CB's start: ----------------";
        while(!path.empty()){
            cout << "\ndegug 7";
            int stackTopVertex = path.top();
            cout << "\nstackTopVertex: " << stackTopVertex;
            cout << "\nsuccessors[stackTopVertex]: "; printi(successors[stackTopVertex]);
            path.pop();
            for(int successor: successors[stackTopVertex]){
                cout << "\ndegug 8";
                cout << "\nshortestPath[stackTopVertex]: " << shortestPath[stackTopVertex];
                cout << "\nsingleVertexDependency[successor]: " << singleVertexDependency[successor];
                singleVertexDependency[stackTopVertex] += (shortestPath[stackTopVertex]/shortestPath[successor]) * (1 + singleVertexDependency[successor]);
            }
            if(stackTopVertex != src){
                cout << "\ndegug 9 " << stackTopVertex << ": ";
                CB[stackTopVertex] +=  singleVertexDependency[stackTopVertex];
                cout<< CB[stackTopVertex];
            }
        }
        cout << "\n----------------------------partial CB's end: ----------------";

    }

    if(undirected) for(int i=0; i < CB.size(); i++){CB[i] /= 2.0;}

    cout << "\nCB's: ";
    for(float CBv: CB){cout << CBv << ", ";}

}

int main(){
    vector<vector<int>> adjMatrix = {
        {0, 1, 0, 0, 0},
        {1, 0, 0, 0, 1},
        {0, 0, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {0, 1, 0, 1, 0},
    };

    brandes_algo(adjMatrix, true);


    //Matrix for dijkstra algo shortest path
    // {
    //     {0, 1, 4, 0, 0},
    //     {1, 0, 0, 0, 5},
    //     {4, 0, 0, 6, 0},
    //     {0, 0, 6, 0, 2},
    //     {0, 5, 0, 2, 0},
    // }

    //dijkstra_algo(matrix, 0);

    return 0;
}