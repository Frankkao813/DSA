// Graph in C++

// for more description of the data structure, see the "Program in C++" section in
// https://www.notion.so/Graph-Traversal-BFS-DFS-c260108618604c1ab5a11ec08f9b3e3a
# include<iostream>
# include<list>
# include<vector>
# include<queue>
# include<stack>


class Graph {
	private:
		int V; // number of vertices
		// several vector, each vector entry is a list
		std::vector<std::list<int>> adjList;

		void DFSutil(int vertex, std::vector<bool>& visited){
			// 1. record the visited node
			visited[vertex] = true;
			// 2. print the node visited
			std::cout << vertex << " ";
			for (int adjVertex: adjList[vertex]){
				if (!visited[adjVertex]) {
						// 3. explore the neighbors if it is not visited.
            DFSutil(adjVertex, visited);
        }
			}
		}

	public:
		Graph(int V){
			this -> V = V;
			adjList.resize(V);
		}

		void addEdge(int u, int v){
			adjList[u].push_back(v);
		}

		void printGraph() const {
			for (int i = 0; i < V; i++){
				std::cout << "Element " << i  <<  " "<< std::endl;
				for (auto x: adjList[i]) {
					std::cout << x << " ";
				}
				std::cout << std::endl;
			}
		}


        void BFS(int startVertex) {
            std::queue<int> q;
            std::vector<bool> visited(V, false); // Initialized with 'false' for all vertices.
                

            // 1. visit the node
            visited[startVertex] = true;
            // 2. push the node onto the queue
            q.push(startVertex); 

            while (!q.empty()) {
                // 3. pop the node from the queue
                int u = q.front();
                q.pop();
                // 4. after popping from the queue, print it
                std::cout << u << " "; 

                for (auto v: adjList[u]) {
                    if (!visited[v]) { // Check if 'v' has not been visited before enqueueing.
                        visited[v] = true; // Mark 'v' as visited right before pushing to the queue.
                        q.push(v);
                    }
                }
            }
            std::cout << std::endl; // Print a newline at the end for better formatting.
        }

        void DFSRecursion(int startVertex){
            std::vector<bool> visited(V, false);
            DFSutil(startVertex, visited);
            std::cout << std::endl;
        }

        void DFSIter(int startNode) {
        std::stack<int> stack;
        std::vector<bool> visited(V, false);

        visited[startNode] = true;
        stack.push(startNode);

        while (!stack.empty()) {
            int u = stack.top(); // Correction: Use stack.top() followed by stack.pop()
            stack.pop();
            std::cout << u << " "; // Process the node

            for (auto v: adjList[u]) {
                if (!visited[v]) { 
                    visited[v] = true; // Mark 'v' as visited right before pushing to the queue.
                    stack.push(v);
                }
            }
        }
    }

};

int main() {
    // Create a graph with 6 vertices
    Graph g(6);

    // Add edges
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(3, 5);

	g.addEdge(1, 0);
    g.addEdge(2, 0);
    g.addEdge(3, 1);
    g.addEdge(3, 2);
    g.addEdge(4, 3);
    g.addEdge(5, 3);
    

    // Print the adjacency list representation of the graph
    g.printGraph();
    
    // start BFS and DFS operation on graph from position 0
	g.BFS(0);
	g.DFSRecursion(0);

    return 0;
}