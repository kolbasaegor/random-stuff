#define INF 9999999

#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <list>

using namespace std;

void splitEdge(string path, string & s1, string & s2){
    s1="";
    s2="";
    bool flag = false;
    for (int i = 0; i < path.size(); ++i) {
        if(path[i] == ' ') flag = true;
        else{
            if(flag) s2 += path[i];
            else s1 += path[i];
        }
    }
}

enum colors{
    WHITE, GRAY, BLACK
};

template <typename V, typename KEY>
class MinHeap{
public:
    MinHeap(){
        capacity = 1;
        data = new V[capacity];
        Size = 0;
    }

    int size(){
        return Size;
    }

    void push(KEY key,V & item){
        if(Size == capacity) increaseSize();

        data[Size] = item;
        Size++;
        int i = Size - 1;
        while(i > 0 and data[(i-1)/2].distance > key){
            std::swap(data[i], data[(i-1)/2]);
            i = (i-1)/2;
        }
    }

    V pop(){
        V itemToReturn = data[0];
        data[0] = data[Size - 1];
        Size--;

        int i = 0;
        int childIndex = findSmallerChild(i);
        while (childIndex != 0 && data[childIndex].distance < data[i].distance){
            std::swap(data[childIndex], data[i]);
            i = childIndex;
            childIndex = findSmallerChild(i);
        }

        return itemToReturn;
    }

    void decreaseKey(V & e, KEY newKey){
        int index = -1;
        for (int i = 0; i < Size; ++i) {
            if(data[i].name == e.name){
                index = i;
                data[i].distance = newKey;
                break;
            }
        }
        if(index != -1){
            int i = index;
            while(i > 0 and data[(i-1)/2].distance > data[i].distance){
                std::swap(data[i], data[(i-1)/2]);
                i = (i-1)/2;
            }
        }
    }

    V top(){
        return data[0];
    }

    bool empty(){
        return Size == 0;
    }

private:
    V *data;
    int Size, capacity;

    int findSmallerChild(int i){
        if(2*i + 1 < Size)
            if(data[2*i + 1].distance < data[2*i + 2].distance)
                return 2*i + 1;
            else return 2*i + 2;
        else if(2*i + 1 == Size)
            return 2*i + 1;
        else return 0;
    }

    void increaseSize(){
        V *buffer = new V[capacity*2];
        for(int i = 0;i<capacity;i++){
            buffer[i] = data[i];
        }
        delete []data;
        data = buffer;
        capacity = capacity*2;
    }
};


class Vertex{
public:
    bool exist = false;
    int distance;
    Vertex *pred;
    colors color;
    string name;

    Vertex() : exist(false) {}

    Vertex(string name) : name(name), exist(true) {}
};

class Edge{
public:
    bool exist = false;
    int weight;
    int bandwidth;
    Vertex *from;
    Vertex *to;

    Edge() : exist(false) {}

    Edge(Vertex *from, Vertex *to, int weight, int bandwidth){
        this->from = from;
        this->to = to;
        this->weight = weight;
        this->bandwidth = bandwidth;
        this->exist = true;
    }
};


template <typename V, typename E>
class AdjacencyMatrixGraph{
public:
    V & addVertex(string value){
        vertices.insert(pair<string, V>(value, V(value)));
        return vertices.find(value)->second;
    }

    E & addEdge(string from, string to, int weight, int bandwidth){
        if(findVertex(from) && findVertex(to)){
            E e(&vertices[from], &vertices[to], weight, bandwidth);

            adjMatrix.insert(pair<string, Edge>(from+" "+to, e));
            return adjMatrix.find(from+" "+to)->second;
        }
    }

    void removeEdge(string from, string to){
        adjMatrix.erase(from+" "+to);
    }

    void removeVertex(string value){
        vertices.erase(value);
        vector<string> keys;
        for(auto& item : adjMatrix)
        {
            string s1,s2;
            splitEdge(item.first,s1,s2);
            if(s1 == value || s2 == value) keys.push_back(item.first);
        }
        for(auto& key : keys){
            adjMatrix.erase(key);
        }
    }

    bool findVertex(string value){
        return vertices.find(value) != vertices.end();
    }

    bool findEdge(string from, string to){
        return adjMatrix.find(from+" "+to) != adjMatrix.end();
    }

    int bandwidth(string v1, string v2){
        return adjMatrix.find(v1 + " " + v2)->second.bandwidth;
    }

    void showEdges(){
        for(auto& item : adjMatrix)
        {
            cout << item.second.from->name << " -[" << item.second.weight << "]- "<< item.second.to->name << endl;
        }
    }
    void showVertices(){
        for(auto& item : vertices)
        {
            cout << item.second.name << endl;
        }
    }

    vector<E> edgesFrom(string v){
        vector<E> edges;
        for(auto& item : adjMatrix)
        {
            string s1,s2;
            splitEdge(item.first,s1,s2);
            if(s1 == v) edges.push_back(item.second);
        }
        return edges;
    }

    vector<E> edgesTo(string v){
        vector<E> edges;
        for(auto& item : adjMatrix)
        {
            string s1,s2;
            splitEdge(item.first,s1,s2);
            if(s2 == v) edges.push_back(item.second);
        }
        return edges;
    }

    bool hasEdge(string from, string to){
        return findEdge(from, to);
    }

    void shortestPath(string s, string end_, int minBandwidth) {

        MinHeap<Vertex, int> PQ;
        vertices.find(s)->second.distance = 0;
        vertices.find(s)->second.pred = nullptr;

        bool toExit = false;

        for (auto &v : vertices) {
            if (v.second.name != s) {
                v.second.distance = INF;
                v.second.pred = nullptr;
            }
            PQ.push(v.second.distance, v.second);
        }

        while (!PQ.empty() && !toExit) {
            Vertex u = PQ.pop();
            if (u.name != end_) {
                for (auto &e : edgesFrom(u.name)) {
                    if (e.bandwidth >= minBandwidth) {
                        Vertex *v = e.to;
                        int alt = u.distance + e.weight;
                        if (alt < v->distance) {
                            v->distance = alt;
                            vertices.find(v->name)->second.pred = &(vertices.find(u.name)->second);
                            PQ.decreaseKey(*v, alt);
                        }
                    }
                }
            } else {
                toExit = true;
            }
        }

        list<string> path_;
        vector<string> pathFlow;

        Vertex end = vertices.find(end_)->second;
        if (!toExit || end.distance == INF) {
            cout << "IMPOSSIBLE";
        } else {
            Vertex *current = &end;
            while (current->pred != nullptr) {
                path_.push_front(current->name);
                pathFlow.insert(pathFlow.begin(), current->name);
                current = current->pred;
            }

            path_.push_front(s);
            pathFlow.insert(pathFlow.begin(), s);

            int minFlow = INF;
            for (int i = 0; i < pathFlow.size() - 1; ++i) {
                int SkeptaFastFlow_GrimeUK = bandwidth(pathFlow[i], pathFlow[i+1]);
                if (SkeptaFastFlow_GrimeUK < minFlow) minFlow = SkeptaFastFlow_GrimeUK;
            }

            cout << path_.size() << " " << end.distance << " " << minFlow << "\n";

            while (!path_.empty()) {
                if(path_.size() != 1) {
                    cout << path_.front() << " ";
                    path_.pop_front();
                } else {
                    cout << path_.front();
                    path_.pop_front();
                }
            }
        }

    }


private:
    map<string,V> vertices;
    map<string, E> adjMatrix;


};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    AdjacencyMatrixGraph<Vertex, Edge> graph;

    int n,m;
    cin >> n >> m;

    for (int i = 1; i < n+1; ++i) {
        graph.addVertex(to_string(i));
    }

    string from, to; int l, b;
    for (int i = 0; i < m; ++i) {
        cin >> from >> to >> l >> b;
        graph.addEdge(from, to, l, b);

    }

    string source, sink; int W;
    cin >> source >> sink >> W;

    graph.shortestPath(source, sink, W);

    return 0;
}
