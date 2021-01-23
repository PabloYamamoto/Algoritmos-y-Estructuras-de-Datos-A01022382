#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <stack>

template <class T>
class GraphVertex
{
private:
    T val;
    std::vector<int> adj;

public:
    ~GraphVertex(){};
    GraphVertex(){};
    GraphVertex(T _val)
    {
        val = _val;
    };

    T get_val() { return val; };
    void set_val(T _val) { val = _val; };

    std::vector<int> get_adj() { return adj; };
    void add_to_adj(int idx) { adj.push_back(idx); };
};

template <class T>
class Graph
{
private:
    std::vector<GraphVertex<T>> nodes;
    bool is_directed;

public:
    ~Graph(){};
    Graph() { is_directed = true; };

    void add_node(T val)
    {
        GraphVertex<T> node(val);
        nodes.push_back(node);
    };

    void add_edge(int src, int dst)
    {
        bool encontrada = false;
        for (auto val : nodes[src].get_adj())
        {
            if (val == dst)
            {
                encontrada = true;
            }
        }
        if (!encontrada)
        {
            nodes[src].add_to_adj(dst);
            if (!is_directed)
                nodes[dst].add_to_adj(src);
        }
    };

    void BFS(int start_vertex)
    {
        // Create vector for visited flag
        std::vector<bool> visited(nodes.size(), false);

        // Create a queue for BFS
        std::queue<int> queue;

        // Mark the current node as visited and enqueue it
        visited[start_vertex] = true;
        queue.push(start_vertex);

        while (!queue.empty())
        {
            // Dequeue a vertex from queue and print it
            int s = queue.front();
            // Do something with the vertex
            std::cout << nodes[s].get_val() << " ";
            queue.pop();

            // Get all adjacent vertices of the dequeued
            // vertex s. If a adjacent has not been visited,
            // then mark it visited and enqueue it
            for (std::vector<int>::iterator i = nodes[s].get_adj().begin();
                 i != nodes[s].get_adj().end(); ++i)
            {
                if (!visited[*i])
                {
                    visited[*i] = true;
                    queue.push(*i);
                }
            }
        }
        std::cout << std::endl;
    };

    void DFS(int start_vertex)
    {
        // Create vector for visited flag
        std::vector<bool> visited(nodes.size(), false);

        // Create a stack for DFS
        std::stack<int> stack;

        stack.push(start_vertex);

        while (!stack.empty())
        {
            // Dequeue a vertex from queue and print it
            int s = stack.top();
            stack.pop();

            if (!visited[s])
            {
                visited[s] = true;
                // Do something with the vertex
                std::cout << nodes[s].get_val() << " ";
            }

            // Get all adjacent vertices of the dequeued
            // vertex s. If a adjacent has not been visited,
            // then mark it visited and enqueue it
            for (std::vector<int>::iterator i = nodes[s].get_adj().begin();
                 i != nodes[s].get_adj().end(); ++i)
            {
                if (!visited[*i])
                {
                    stack.push(*i);
                }
            }
        }
        std::cout << std::endl;
    };

    vector<GraphVertex<T>> get_nodes() { return nodes; }

    void print_edges()
    {
        for (auto node : nodes)
        {
            cout << node.get_val() << " : ";
            for (auto edge : node.get_adj())
            {
                cout << nodes[edge].get_val() << " -> ";
            }
            cout << node.get_adj().size();
            cout << endl;
        }
    }

    int count_edges(T val)
    {
        // for (std::vector<GraphVertex<T> >::iterator it = nodes.begin(); it != nodes.end(); it++)
        // {
        //     if (it->get_val() == val)
        //         return it->get_adj().size();
        // }
        for (auto node : nodes)
        {
            if (node.get_val() == val)
                return node.get_adj().size();
        }
        return -1;
    }

    bool compare_edges(T val)
    {
        int temp = this->count_edges(val);
        for (auto node : nodes)
        {
            if (node.get_adj().size() > temp)
                return false;
        }
        return true;
    }

    int count_edges_per_val(T val)
    {
        int count = 0;
        for (auto node : nodes)
        {
            for (auto adj : node.get_adj())
            {
                if (nodes[adj].get_val() == val)
                    count++;
            }
        }
        return count;
    }
};