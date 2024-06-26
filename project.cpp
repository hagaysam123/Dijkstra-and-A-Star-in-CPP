
#include <iostream>
#include <cstring>
#include <typeinfo>
#include <fstream>
#include <string>
#include <list>
#include <iterator> 
#include <limits>
#include <queue> 




using namespace std;
class Node
{
public:
	int value; // this is the degree for bfs
	string color;
	string name;
	Node* father; // pai
	int degree; // d
	int finish_time; // this is for dfs, we dont need it now
	int undirected;
	list < std::pair< Node*, int > >neighbors;
	Node::Node()
	{
		this->undirected = 0;
		this->value = 0;
		this->color = "White";
		this->father = NULL;
		this->degree = 0;
		this->finish_time = 0;
	}
};

class Graph
{
public:
	std::list < std::pair< Node*, int >> allnodes;
};

void funcd(Graph* graph)
{
	list <std::pair<Node*, int>> ::iterator it = graph->allnodes.begin();
	while (it != (graph->allnodes.end()))
	{
		cout << "The degree of  " << it.operator*().first->name << "  is :  " << it.operator*().first->degree;
		cout << "" << endl;
		it++;
	}
}

void funcip(Graph* graph)
{
	list <std::pair<Node*, int>> ::iterator it = graph->allnodes.begin();
	while (it != (graph->allnodes.end()))
	{
		if (it.operator*().first->father == NULL)
			cout << it.operator*().first->name << "   has no father";
		else
			cout << "The father of  " << it.operator*().first->name << "  is :  " << it.operator*().first->father->name;
		cout << "" << endl;
		it++;
	}
}



void ethoolbfs(list < std::pair< Node*, int > > ::iterator graph)
{
	list < std::pair< Node*, int > > ::iterator it = graph.operator*().first->neighbors.begin();
	while (it.operator!=(graph.operator*().first->neighbors.end()))
	{

		it.operator*().first->father = NULL;
		it.operator*().first->color = "White";
		it.operator*().first->value = std::numeric_limits<int>::max();

		it.operator++();
	}

	return;
}
void ethool(list < std::pair< Node*, int > > ::iterator graph)
{
	if (graph.operator*().first->degree != std::numeric_limits<int>::max())
	{
		graph.operator*().first->degree = std::numeric_limits<int>::max();
		graph.operator*().first->father = NULL;
		graph.operator*().first->color = "White";
		graph.operator*().first->value = std::numeric_limits<int>::max();

		if (!graph.operator*().first->neighbors.empty())
		{
			list < std::pair< Node*, int > > ::iterator it = graph.operator*().first->neighbors.begin();
			while (it.operator!=(graph.operator*().first->neighbors.end()))
			{

				it.operator*().first->degree = std::numeric_limits<int>::max();
				it.operator*().first->father = NULL;
				it.operator*().first->color = "White";
				it.operator*().first->value = std::numeric_limits<int>::max();

				if (!it.operator*().first->neighbors.empty())
				{
					list < std::pair< Node*, int > > ::iterator it2;
					it2.operator=(it.operator*().first->neighbors.begin());
					ethool(it2);
				}

				it.operator++();
			}

		}
	}
	return;
}

void initial_single_source(list < std::pair< Node*, int > > ::iterator graph)
{
	ethool(graph);
	graph.operator*().first->degree = 0;
}

void relax(std::pair< Node*, int > father, list < std::pair< Node*, int > > ::iterator son)
{
	list < std::pair< Node*, int > > ::iterator it = father.first->neighbors.begin();
	while (it.operator!=(son))
		it.operator++();
	int weight = it.operator*().second;
	if (son.operator*().first->degree > (father.first->degree + weight))
	{
		son.operator*().first->degree = father.first->degree + weight;
		if (son.operator*().first->father == NULL)
			son.operator*().first->father = new Node();
		son.operator*().first->father->degree = father.first->degree;
		son.operator*().first->father->name = father.first->name;
		son.operator*().first->father->neighbors = father.first->neighbors;
	}
}

std::pair<Node*, int> minimali(std::list < std::pair< Node*, int >> &nodes)
{
	Node* min = new Node();
	int min_degree = nodes.begin().operator*().first->degree;
	list <std::pair<Node*, int>> ::iterator it = nodes.begin();
	list <std::pair<Node*, int>> ::iterator it2 = it;
	std::pair<Node*, int > it3;
	it3.first = new Node();


	while (it.operator!=(nodes.end()))
	{
		if (it.operator*().first->degree< min_degree)
		{
			min = it.operator*().first;
			min_degree = it.operator*().first->degree;
			it2 = it;
		}
		it.operator++();
	}
	it3.second = it2.operator*().second;
	it3.first->degree = it2.operator*().first->degree;
	it3.first->father = it2.operator*().first->father;
	it3.first->name = it2.operator*().first->name;
	it3.first->neighbors = it2.operator*().first->neighbors;
	nodes.erase(it2);
	return it3;
}

std::pair<Node*, int> minimali_fn(std::list < std::pair< Node*, int >> &nodes, string father)
{
	Node* min = new Node();
	int degreefaher = 0;
	list <std::pair<Node*, int>> ::iterator it = nodes.begin();
	list <std::pair<Node*, int>> ::iterator it2 = it;
	std::pair<Node*, int > it3;
	it3.first = new Node();

	while (it.operator!=(nodes.end()))
	{
		if (it.operator*().first->name == father)
		{
			degreefaher = it.operator*().first->degree;
			break;
		}
		it++;
	}
	it = nodes.begin();
	int mindegree = degreefaher + nodes.begin().operator*().second + nodes.begin().operator*().first->value;
	while (it.operator!=(nodes.end()))
	{
		if (it.operator*().first->name != (father))
		{
			

			if (degreefaher + it.operator*().second + it.operator*().first->value < mindegree)
			{
				min = it.operator*().first;
				mindegree = degreefaher + it.operator*().second + it.operator*().first->value;
				it2 = it;
			}
		}
		it++;
	}
	it2.operator*().first->degree = mindegree - it2.operator*().first->value;
	it3.second = it2.operator*().second;
	it3.first->degree = it2.operator*().first->degree;
	it3.first->father = it2.operator*().first->father;
	it3.first->name = it2.operator*().first->name;
	it3.first->neighbors = it2.operator*().first->neighbors;
	nodes.erase(it2);
	return it3;

}


Graph* dijkstra(Graph* g)
{
	initial_single_source(g->allnodes.begin());
	Graph* s = new Graph();
	std::list < std::pair< Node*, int >> q = g->allnodes;

	while (!q.empty())
	{
		std::pair<Node*, int>  u1;
		u1 = minimali(q);
		s->allnodes.push_back(u1);
		list <std::pair<Node*, int>> ::iterator it = u1.first->neighbors.begin();
		while (it.operator!=(u1.first->neighbors.end()))
		{
			relax(u1, it);
			it.operator++();
		}
	}
	funcd(s);
	funcip(s);
	return s;

}

Graph* bfs(Graph* g, list < std::pair< Node*, int > > ::iterator s)
{
	ethoolbfs(g->allnodes.begin());
	s.operator*().first->color = "Gray";
	s.operator*().first->value = 0;
	s.operator*().first->father = NULL;
	queue <std::pair< Node*, int >> q;
	q.push(s.operator*());
	while (!q.empty())
	{
		std::pair< Node*, int > u = q.front(); q.pop(); 
		list < std::pair< Node*, int > > ::iterator it = u.first->neighbors.begin();
		while (it.operator!=(u.first->neighbors.end()))
		{
			if (it.operator*().first->color == "White")
			{
				it.operator*().first->color = "Gray";
				it.operator*().first->value = u.first->value + 1;
				it.operator*().first->father = u.first;
				q.push(it.operator*());
			}
			it.operator++();
		}
		u.first->color = "Black";
	}
	return g;
}

Graph* funcfn(Graph* g, list < std::pair< Node*, int > > ::iterator makor, list < std::pair< Node*, int > > ::iterator yaud)
{

	// g(n) + להפוך את הגרף ממכוון ללא מכוון  //
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool flag = true;
	//dijkstra(g); // g(n)
	list < std::pair< Node*, int > > ::iterator it = g->allnodes.begin();
	while (it != (g->allnodes.end()))
	{
		list < std::pair< Node*, int > > ::iterator it2 = it.operator*().first->neighbors.begin();
		while (it2 != it.operator*().first->neighbors.end())
		{
			int w = it2.operator*().second;
			list < std::pair< Node*, int > > ::iterator it3 = it2.operator*().first->neighbors.begin();
			while (it3 != it2.operator*().first->neighbors.end())
			{
				if (it3.operator*().first->name == it.operator*().first->name)
					flag = false;
				it3.operator++();
			}
			if (flag)
			{

				it2.operator*().first->neighbors.push_back(it.operator*());
				it2.operator*().first->undirected++;
				it2.operator*().first->neighbors.end().operator--().operator*().second = w;

			}
			it2.operator++();
			flag = true;
		}

		it.operator++();
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// h(n) // 
	//////////////////////////////////////////////////
	bfs(g, yaud);
	it = g->allnodes.begin();
	while (it.operator!=(g->allnodes.end()))
	{
		it.operator*().first->value = it.operator*().first->value * 10;
		it.operator++();
	}
	////////////////////////////////////////////////////////
	it = g->allnodes.begin();
	while (it.operator!=(g->allnodes.end()))
	{
		while (it.operator*().first->undirected != 0)
		{
			it.operator*().first->neighbors.pop_back();
			it.operator*().first->undirected--;
		}
		it++;
	}
	////////////////////////////////////////////////////////////

	// f(n) // 
	//////////////////////////////////////////////////////
	Graph* s = new Graph();
	it = makor;
	std::list < std::pair< Node*, int >> q = makor.operator*().first->neighbors;
	bool firsttime = true;
	string father = it.operator*().first->name;
	while (it.operator*().first->name != (yaud.operator*().first->name))
	{
		if (firsttime)
		{
			std::pair<Node*, int>  u1;
			u1 = minimali_fn(it.operator*().first->neighbors, "");
			s->allnodes.push_back(u1);
			s->allnodes.end().operator--().operator*().first->father = it.operator*().first;
			father = it.operator*().first->name;
			it.operator*() = u1;
			firsttime = false;
		}
		else
		{
			std::pair<Node*, int>  u1;
			u1 = minimali_fn(it.operator*().first->neighbors, father);
			s->allnodes.push_back(u1);
			s->allnodes.end().operator--().operator*().first->father = it.operator*().first;
			father = it.operator*().first->name;
			it.operator*() = u1;
		}


	}
	funcd(s);
	funcip(s);
	return s;
}

int main()
{
	Graph* g = new Graph();
	pair<Node*, int> s;
	s.first = new Node();
	s.first->name = "S";
	pair<Node*, int> a;
	a.first = new Node();
	a.first->name = "A";
	pair<Node*, int> b;
	b.first = new Node();
	b.first->name = "B";
	pair<Node*, int> c;
	c.first = new Node();
	c.first->name = "C";
	pair<Node*, int> d;
	d.first = new Node();
	d.first->name = "D";
	pair<Node*, int> e;
	e.first = new Node();
	e.first->name = "E";
	pair<Node*, int> f;
	f.first = new Node();
	f.first->name = "F";
	pair<Node*, int> h;
	h.first = new Node();
	h.first->name = "H";


	s.first->neighbors.push_back(a);
	s.first->neighbors.push_back(b);
	s.first->neighbors.push_back(c);
	s.first->neighbors.begin().operator*().second = 33;
	list <std::pair<Node*, int>> ::iterator it2 = s.first->neighbors.begin();
	it2++;
	it2.operator*().second = 8;
	it2++;
	it2.operator*().second = 10;

	c.first->neighbors.push_back(d);
	c.first->neighbors.begin().operator*().second = 6;
	b.first->neighbors.push_back(d);
	b.first->neighbors.begin().operator*().second = 12;
	c.first->neighbors.push_back(h);
	c.first->neighbors.push_back(f);
	list <std::pair<Node*, int>> ::iterator it = c.first->neighbors.begin();
	it++;
	it.operator*().second = 13;
	it++;
	it.operator*().second = 9;
	d.first->neighbors.push_back(h);
	d.first->neighbors.begin().operator*().second = 5;
	h.first->neighbors.push_back(f);
	h.first->neighbors.begin().operator*().second = 6;
	f.first->neighbors.push_back(a);
	f.first->neighbors.push_back(e);
	it = f.first->neighbors.begin();
	it.operator*().second = 3;
	it++;
	it.operator*().second = 25;
	a.first->neighbors.push_back(e);
	a.first->neighbors.begin().operator*().second = 11;


	g->allnodes.push_back(s);
	g->allnodes.push_back(a);
	g->allnodes.push_back(b);
	g->allnodes.push_back(c);
	g->allnodes.push_back(d);
	g->allnodes.push_back(e);
	g->allnodes.push_back(f);
	g->allnodes.push_back(h);

	cout << "DIJKSTRA" << endl;
	cout << "---------------------------------------------------------------" << endl;
	Graph* dj = new Graph();
	dj = dijkstra(g);
	cout << "---------------------------------------------------------------" << endl;

	list <std::pair<Node*, int>> ::iterator itf = g->allnodes.begin();
	itf++; itf++; itf++; itf++;
	it = g->allnodes.begin();
	it++; it++; it++; it++; it++;
	Graph* lol = new Graph();
	cout << "A*" << endl;
	cout << "---------------------------------------------------------------" << endl;
	cout << "THE PATH FROM D TO E" << endl;
	cout << "---------------------------------------------------------------" << endl;
	lol = funcfn(g, itf, it);
	cout << "---------------------------------------------------------------" << endl;

	return 0;
}
