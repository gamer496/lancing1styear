#include<bits/stdc++.h>
using namespace std;

typedef struct edge
{
	int toVertex;
	int weight;
}Edge;

typedef struct edgeNode
{
	Edge edge;
	struct edgeNode *next;
}*EdgeList;

typedef struct graph
{
	int V;
	int state;
	EdgeList edges;
}Graph;


vector<string> split(string s, char delim)
{
    stringstream ss(s);
    string item;
    vector<string> tokens;
    while (getline(ss, item, delim))
    {
        tokens.push_back(item);
    }
    return tokens;
}

int str2int (const string &str) {
  stringstream ss(str);
  int num;
  if((ss >> num).fail())
  {
      cout<<"an error came make sure extra spaces are stripped.";
      exit(1);
  }
  return num;
}

edgeNode* pedgeNode(Edge e)
{
	edgeNode *en=(struct edgeNode*)malloc(sizeof(struct edgeNode));
	en->edge=e;
	en->next=NULL;
	return en;
}

bool isCyclicUtil(int v,bool visited[],bool *recStack,Graph g[])
{
	if(visited[v]==false)
	{
		visited[v]=true;
		recStack[v]=true;
		edgeNode *temp=g[v].edges;
		while(temp!=NULL)
		{
			if(!visited[temp->edge.toVertex] && isCyclicUtil(temp->edge.toVertex,visited,recStack,g))
			{
				return true;
			}
			else if(recStack[temp->edge.toVertex])
			{
				return true;
			}
			temp=temp->next;
		}
	}
	recStack[v]=false;
	return false;
}

bool check_through_dfs(Graph g[],int n)
{
	bool *visited=new bool[n];
	bool *recStack=new bool[n];
	for(int i=0;i<n;i++)
	{
		visited[i]=false;
		recStack[i]=false;
	}
	for(int i=0;i<n;i++)
	{
		if(isCyclicUtil(i,visited,recStack,g))
		{
			return true;
		}
	}
	return false;
}

int cal_in_size(Graph g[],int i)
{
	edgeNode *temp=g[i].edges;
	int j=0;
	while(temp!=NULL)
	{
		temp=temp->next;
		j++;
	}
	return j;
}

int get_child(Graph g[],int i,int j)
{
	edgeNode *temp=g[i].edges;
	int k=0;
	while(k!=j)
	{
		temp=temp->next;
		k++;
	}
	return temp->edge.toVertex;
}

queue<int> generate_topo_sort(Graph g[],int n,vector<int>in_degree)
{
	queue<int>q,q1;
	for(int i=0;i<n;i++)
	{
		if(in_degree[i]==0)
		{
			q.push(i);
		}
	}
	int count=n;
	while(count-- && !q.empty())
	{
		int vertex=q.front();
		q.pop();
		q1.push(vertex);
		for(int i=0;i<cal_in_size(g,vertex);i++)
		{
			int child=get_child(g,vertex,i);
			in_degree[child]--;
			if(in_degree[child]==0)
			{
				q.push(child);
			}
		}
	}
	return q1;
}

queue<int> reverse(queue<int>q)
{
	  stack <int> st;
	  while (!q.empty()){
        st.push(q.front());
        q.pop();
    }

   //pop elements from st and enQueue again Q
    while (!st.empty()){
        q.push(st.top());
        st.pop();
    }
    return q;
}

int main()
{
	ios::sync_with_stdio(false);
	// cout<<"enter the number the edges\n";
	int n;
	cin>>n;
	Graph g[n+10];
	for(int i=0;i<n;i++)
	{
		g[i].V=i;
		// cout<<"enter the state\n";
		int state;
		cin>>state;
		g[i].state=state;
		int ed;
		// cout<<"number of edges\n";
		cin>>ed;
		if(ed==0)
		{
			g[i].edges=NULL;
			continue;
		}
		else
		{
			// cout<<"enter the edges\n";
			string s;
			edgeNode *root=NULL;
			edgeNode *temp=NULL;
			for(int j=0;j<ed;j++)
			{
				cin>>s;
				vector<string>v=split(s,',');
				int toVertex=str2int(v[0]);
				int weight=str2int(v[1]);
				Edge edg;
				edg.toVertex=toVertex;
				edg.weight=weight;
				if(root==NULL)
				{
					root=pedgeNode(edg);
					g[i].edges=root;
					temp=root;
				}
				else
				{
					temp->next=pedgeNode(edg);
					temp=temp->next;
				}
			}
		}
	}
	bool flag=check_through_dfs(g,n);
	if(flag==true)
	{
		cout<<"ERROR!!\n";
		exit(1);
	}
	vector<int>in_degree;
	map<int, vector< pair<int,int> > >in;
	for(int i=0;i<n;i++)
	{
		in_degree.push_back(0);
	}
	for(int i=0;i<n;i++)
	{
		edgeNode *temp=g[i].edges;
		while(temp!=NULL)
		{
			in_degree[temp->edge.toVertex]++;
			in[temp->edge.toVertex].push_back(make_pair(i,temp->edge.weight));
			temp=temp->next;
		}
	}
	queue<int>q=generate_topo_sort(g,n,in_degree);
	while(!q.empty())
	{
		int inp=0;
		int i=q.front();
		if(in[i].size()==0)
		{
			q.pop();
			continue;
		}
		vector< pair<int,int> >::iterator iter;
		for(iter=in[i].begin();iter!=in[i].end();iter++)
		{
			inp+=iter->second*g[iter->first].state;
			cout<<iter->second<<" "<<g[iter->first].state<<"\n";
		}
		if(inp>0)
		{
			g[i].state=1;
		}
		else
		{
			g[i].state=0;
		}
		q.pop();
	}
	for(int i=0;i<n;i++)
	{
		cout<<g[i].state;
	}
	cout<<"\n";
	return 0;
}
