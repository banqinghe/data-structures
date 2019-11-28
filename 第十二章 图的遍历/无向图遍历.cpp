#include <iostream>
#include <list>
#include <queue>
using namespace std;

const int max_set=505;

typedef int Vertex;
class Digraph {
private:
    int count;
    list<Vertex> neighbors[max_set];
public:
	void set_count(int num);
    void add_edge(int v1, int v2);
    void sort_vertex();

	void depth_first(void (*visit)(Vertex &));
	void traverse(Vertex &v,bool visited[],void (*visit)(Vertex &)) ;

	void breadth_first(void (*visit)(Vertex &));
};

void Digraph::set_count(int num) {
	count=num;
}

void Digraph::add_edge(int v1, int v2) {
    neighbors[v1].push_back(v2);
    neighbors[v2].push_back(v1);
}

void Digraph::sort_vertex() {
    for(Vertex v=0;v<count;v++) {
        neighbors[v].sort();
    }
}

void Digraph::depth_first(void (*visit)(Vertex &)) {
	bool visited[max_set];
	Vertex v;
	for(v=0;v<count;v++)
		visited[v]=false;
	for(v=0;v<count;v++) {
		if(!visited[v])
			traverse(v,visited,visit);
	}
	cout<<endl;
}

void Digraph::traverse(Vertex &v,bool visited[],void (*visit)(Vertex &)) {
	visited[v]=true;
	(*visit)(v);
	for(list<Vertex>::iterator it=neighbors[v].begin();it!=neighbors[v].end();it++) {
		if(!visited[(*it)])
			traverse((*it),visited,visit);
	}
}

void Digraph::breadth_first(void (*visit)(Vertex &)){
	queue<Vertex> q;
	bool visited[max_set];
	Vertex v,w;
	for(v=0;v<count;v++) 
		visited[v]=false;
	for(v=0;v<count;v++) {
		if(!visited[v]) {
            q.push(v);
            while(!q.empty()) {
                w=q.front();
                if(!visited[w]) {
                    visited[w]=true;
                    (*visit)(w);
                    list<Vertex>::iterator it=neighbors[w].begin();
                    for(;it!=neighbors[w].end();it++) {
                        q.push(*it);
                    }
                }
                q.pop();
            }
        }
	}
}

void Print(Vertex &x) {
	cout<<x<<' ';
}

int main()
{
	int v,e,v1,v2;
	cin>>v>>e;
	Digraph p;
	p.set_count(v);
	for(int i=0;i<e;i++) {
		cin>>v1>>v2;
		p.add_edge(v1,v2);
	}
    p.sort_vertex();
	p.depth_first(Print);
    p.breadth_first(Print);
    cout<<endl;
	return 0;
}