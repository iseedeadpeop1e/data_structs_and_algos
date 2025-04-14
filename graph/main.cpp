#include <iostream>
#include <vector>
#include <stack>
#include <climits>
#include <algorithm>

using namespace std;

// Класс для хранения графа
class Graph {
private:
    int vertexCount;  // число вершин
    vector<vector<pair<int, int>>> adjacencyList;  // список смежности
    bool isDirected;  // направленный или нет

public:
    // Создание графа
    Graph(int vertices, bool directed = false) : vertexCount(vertices), isDirected(directed) {
        adjacencyList.resize(vertexCount);
    }

    // Добавление ребра
    void addEdge(int from, int to, int weight) {
        adjacencyList[from].push_back({to, weight});
        if (!isDirected) {
            adjacencyList[to].push_back({from, weight});
        }
    }

    // Поиск в глубину
    vector<int> dfs(int start) {
        // Шаг 1: Поместить начальную вершину в стек, пометить вершину как посещенную
        vector<int> path;  // ответ - путь
        vector<bool> visited(vertexCount, false);  // посещенные вершины
        stack<int> vertexStack;  // стек

        vertexStack.push(start);
        visited[start] = true;

        while (!vertexStack.empty()) {
            // Шаг 2: Взять вершину из стека (не удаляя!)
            int currentVertex = vertexStack.top();
            path.push_back(currentVertex);

            // Шаг 3: Найти непосещенную смежную вершину
            bool foundUnvisited = false;
            for (const auto& edge : adjacencyList[currentVertex]) {
                int neighbor = edge.first;
                if (!visited[neighbor]) {
                    // Пометить как посещенную и поместить в стек
                    visited[neighbor] = true;
                    vertexStack.push(neighbor);
                    foundUnvisited = true;
                    break;
                }
            }

            // Шаг 4: Если среди смежных вершин нет непосещенных, удалить вершину из стека
            if (!foundUnvisited) {
                vertexStack.pop();
            }
        }

        // Шаг 5: Если стек пустой, обход завершен
        return path;
    }

    // Алгоритм Дейкстры
    vector<int> deikstra(int start, int end) {
        // Шаг 1: Начальной вершине присваивается метка 0, всем остальным - бесконечность
        vector<int> distance(vertexCount, INT_MAX);  // расстояния
        vector<int> previous(vertexCount, -1);  // предки
        vector<bool> visited(vertexCount, false);  // посещенные вершины
        
        distance[start] = 0;

        for (int i = 0; i < vertexCount; i++) {
            // Шаг 2: Среди всех непосещенных вершин выбрать вершину с минимальной меткой
            int minDistance = INT_MAX;
            int currentVertex = -1;
            
            for (int j = 0; j < vertexCount; j++) {
                if (!visited[j] && distance[j] < minDistance) {
                    minDistance = distance[j];
                    currentVertex = j;
                }
            }

            // Если все непосещенные вершины имеют бесконечные метки, то граф несвязный
            if (currentVertex == -1) break;

            // Шаг 3: Перебираем все соседи текущей вершины
            visited[currentVertex] = true;

            for (const auto& edge : adjacencyList[currentVertex]) {
                int neighbor = edge.first;
                int weight = edge.second;
                
                // Шаг 4: Для каждого непосещенного соседа рассчитываем новое расстояние
                if (!visited[neighbor] && distance[currentVertex] != INT_MAX && 
                    distance[currentVertex] + weight < distance[neighbor]) {
                    // Если полученное расстояние меньше текущей метки соседа, обновляем метку
                    distance[neighbor] = distance[currentVertex] + weight;
                    previous[neighbor] = currentVertex;
                }
            }
        }

        // Шаг 5: Восстанавливаем путь от конечной вершины к начальной
        vector<int> path;
        if (distance[end] == INT_MAX) {
            return path;  // путь не найден
        }

        for (int vertex = end; vertex != -1; vertex = previous[vertex]) {
            path.push_back(vertex);
        }
        reverse(path.begin(), path.end());
        return path;
    }
};

// Вывод пути
void printPath(const vector<int>& path) {
    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i];
        if (i < path.size() - 1) {
            cout << " -> ";
        }
    }
    cout << endl;
}

int main() {
    // Ненаправленный граф
    cout << "Undirected graph:" << endl;
    Graph undirectedGraph(10, false);
    
    // Добавляем ребра
    undirectedGraph.addEdge(0, 1, 2);
    undirectedGraph.addEdge(0, 2, 3);
    undirectedGraph.addEdge(1, 3, 1);
    undirectedGraph.addEdge(1, 4, 3);
    undirectedGraph.addEdge(1, 5, 7);
    undirectedGraph.addEdge(3, 7, 4);
    undirectedGraph.addEdge(4, 7, 1);
    undirectedGraph.addEdge(2, 6, 4);
    undirectedGraph.addEdge(5, 8, 6);
    undirectedGraph.addEdge(6, 8, 5);
    undirectedGraph.addEdge(7, 9, 3);
    undirectedGraph.addEdge(8, 9, 1);

    cout << "DFS starting from vertex 0: ";
    auto dfsPath = undirectedGraph.dfs(0);
    printPath(dfsPath);

    cout << "Shortest path from 0 to 8: ";
    auto shortestPath = undirectedGraph.deikstra(0, 8);
    printPath(shortestPath);

    // Направленный граф
    cout << "\nDirected graph:" << endl;
    Graph directedGraph(10, true);
    
    // Добавляем ребра
    directedGraph.addEdge(0, 1, 2);
    directedGraph.addEdge(0, 2, 3);
    directedGraph.addEdge(1, 3, 1);
    directedGraph.addEdge(1, 4, 3);
    directedGraph.addEdge(1, 5, 7);
    directedGraph.addEdge(3, 7, 4);
    directedGraph.addEdge(4, 7, 1);
    directedGraph.addEdge(2, 6, 4);
    directedGraph.addEdge(5, 8, 6);
    directedGraph.addEdge(6, 8, 5);
    directedGraph.addEdge(7, 9, 3);
    directedGraph.addEdge(8, 9, 1);

    cout << "DFS starting from vertex 0: ";
    dfsPath = directedGraph.dfs(0);
    printPath(dfsPath);

    cout << "Shortest path from 0 to 8: ";
    shortestPath = directedGraph.deikstra(0, 8);
    printPath(shortestPath);

    return 0;
} 