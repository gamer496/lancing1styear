#include<bits/stdc++.h>
using namespace std;

struct node
{
	string data;
	struct node *left,*right;
	int count;
};

struct mpair
{
	int count;
	string data;

	mpair()
	{
		data="";
		count=0;
	}

	void push(string dt,int cnt)
	{
		this->data=dt;
		this->count=cnt;
	}
};


node *nnode(string data)
{
	node *n=(struct node*)malloc(sizeof(struct node));
	n->data=data;
	n->left=NULL;
	n->right=NULL;
	n->count=1;
	return n;
}

node *mmax;

void inorder(node *temp,mpair mp[])
{
	static int i=0;
	if(temp==NULL)
	{
		return ;
	}
	else
	{
		mp[i].push(temp->data,temp->count);
		i++;
		inorder(temp->left,mp);
		inorder(temp->right,mp);
	}
}


bool comp(mpair &m1,mpair &m2)
{
	return m2.count<m1.count;
}


int main()
{
	ios::sync_with_stdio(false);
	node *root=NULL;
	char file_name[200];
	cout<<"Enter the filename with extension"<<endl;
	cin>>file_name;
	ifstream file(file_name);
	if(!file)
	{
		cout<<"Unable to open file\n";
		exit(1);
	}
	string data;
	string line;
	int cnt=0;

	// create the bst
	while(getline(file,line))
	{
		cout<<line<<endl;
		stringstream ss(line);
		char delim=' ';
		while(getline(ss,data,delim))
		{
			if(root==NULL)
			{
				root=nnode(data);
				continue;
			}
			node *temp1,*temp2;
			temp1=root;
			bool flag=false;
			while(temp1!=NULL)
			{
				temp2=temp1;
				if(data>temp1->data)
				{
					temp1=temp1->right;
				}
				else if(data<temp1->data)
				{
					temp1=temp1->left;
				}
				else if(data==temp1->data)
				{
					temp1->count+=1;
					flag=true;
					break;
				}
			}
			if(flag!=true)
			{
				cnt++;
				if(data>temp2->data)
				{
					temp2->right=nnode(data);
				}
				else
				{
					temp2->left=nnode(data);
				}
			}
		}
	}
	mmax=root;
	// travel it in inorder and build the vector
	mpair mp[cnt+10];
	inorder(root,mp);
	sort(mp,mp+cnt,comp);
	for(int i=0;i<min(cnt,5);i++)
	{
		cout<<mp[i].data<<" "<<mp[i].count<<"\n";
	}
	return 0;
}