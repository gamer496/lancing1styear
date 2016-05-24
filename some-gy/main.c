#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define true 1
#define false 0

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

struct map
{
	int vertex[500];
	int weight[500];
	int ind;
};

struct queue
{
	int front;
	int back;
	int elems[500];
};


void init(struct queue *q)
{
	q->front=0;
	q->back=0;
	for(int i=0;i<500;i++)
	{
		q->elems[i]=0;
	}
}




void push(struct queue *q,int x)
{
	q->elems[q->back]=x;
	q->back+=1;
}

int empty(struct queue *q)
{
	if(q->front==q->back)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int front(struct queue *q)
{
	int x=q->elems[q->front];
	q->front+=1;
	return x;
}

struct edgeNode* pedgeNode(Edge e)
{
	struct edgeNode *en=(struct edgeNode*)malloc(sizeof(struct edgeNode));
	en->edge=e;
	en->next=NULL;
	return en;
}

int cal_in_size(Graph g[],int i)
{
	struct edgeNode *temp=g[i].edges;
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
	struct edgeNode *temp=g[i].edges;
	int k=0;
	while(k!=j)
	{
		temp=temp->next;
		k++;
	}
	return temp->edge.toVertex;
}

void generate_topo_sort(Graph g[],int n,int in_degree[],struct queue *main_queue)
{
	struct queue aux_queue;
	init(&aux_queue);
	for(int i=0;i<n;i++)
	{
		if(in_degree[i]==0)
		{
			push(&aux_queue,i);
		}
	}
	int count=n;
	while(count-- && !empty(&aux_queue))
	{
		int vertex=front(&aux_queue);
		push(main_queue,vertex);
		for(int i=0;i<cal_in_size(g,vertex);i++)
		{
			int child=get_child(g,vertex,i);
			in_degree[child]--;
			if(in_degree[child]==0)
			{
				push(&aux_queue,child);
			}
		}
	}
}


int isCyclicUtil(int v,int visited[],int *recStack,Graph g[])
{
	if(visited[v]==false)
	{
		visited[v]=true;
		recStack[v]=true;
		struct edgeNode *temp=g[v].edges;
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

int check_through_dfs(Graph g[],int n)
{
	int *visited=(int *)malloc(n*sizeof(int));
	int *recStack=(int *)malloc(n*sizeof(int));
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

int main()
{
	// cout<<"enter the number the edges\n";
	int n;
	scanf("%d",&n);
	Graph g[n+10];
	for(int i=0;i<n;i++)
	{
		g[i].V=i;
		// cout<<"enter the state\n";
		int state;
		scanf("%d",&state);
		g[i].state=state;
		int ed;
		// cout<<"number of edges\n";
		scanf("%d",&ed);
		if(ed==0)
		{
			g[i].edges=NULL;
			continue;
		}
		else
		{
			// cout<<"enter the edges\n";
			struct edgeNode *root=NULL;
			struct edgeNode *temp=NULL;
			for(int j=0;j<ed;j++)
			{
				char a[200];
				scanf("%s",a);
				struct edge edg;
				char *b;
				b=strtok(a,",");
				sscanf(b,"%d",&edg.toVertex);
				b=strtok(NULL,",");
				sscanf(b,"%d",&edg.weight);
				// printf("%d\n",edg.weight);
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
	int flag=check_through_dfs(g,n);
	if(flag==true)
	{
		printf("ERROR!!\n");
		exit(1);
	}
	int in_degree[n];
	struct map in[n];
	for(int i=0;i<n;i++)
	{
		in_degree[i]=0;
		in[i].ind=0;
	}
	for(int i=0;i<n;i++)
	{
		struct edgeNode *temp=g[i].edges;
		while(temp!=NULL)
		{
			in_degree[temp->edge.toVertex]++;
			int k=in[temp->edge.toVertex].ind;
			in[temp->edge.toVertex].vertex[k]=i;
			in[temp->edge.toVertex].weight[k]=temp->edge.weight;
			in[temp->edge.toVertex].ind+=1;
			temp=temp->next;
		}
	}
	struct queue main_queue;
	init(&main_queue);
	generate_topo_sort(g,n,in_degree,&main_queue);
	while(!empty(&main_queue))
	{
		int inp=0;
		int i=front(&main_queue);
		if(in[i].ind==0)
		{
			continue;
		}
		for(int j=0;j<in[i].ind;j++)
		{
			inp+=in[i].weight[j]*g[in[i].vertex[j]].state;
			// printf("%d %d\n",in[i].weight[j],g[in[i].vertex[j]].state);
		}
		if(inp>0)
		{
			g[i].state=1;
		}
		else
		{
			g[i].state=0;	
		}
	}
	for(int i=0;i<n;i++)
	{
		printf("%d",g[i].state);
	}
	printf("\n");
	return 0;
}