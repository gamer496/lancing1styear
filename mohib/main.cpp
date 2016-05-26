#include<iostream>
#include<cstdlib>
using namespace std;

void conversion();
void arithematic();

int main()
{
	cout<<"Welcome to the CSCI114 Lab Test\n";
	bool flag=true;
	while(1)
	{
		cout<<"1. Arithematic expression\n2. Conversion of numbers\n9. I am tired, quit now.\n";
		int choice;
		cin>>choice;
		switch(choice)
		{
			case 1: arithematic();
					break;
			case 2: conversion();
					break;
			case 9: flag=false;
					break;
			default: cout<<"invalid option\n.";
					break;
		}
		if(flag==false)
		{
			break;
		}
	}
}

void conversion()
{
	cout<<"conversion function called.\n";
}


void getInt(int &a)
{
	a=rand()%101;
}

char getOperation()
{
	int i=rand()%3;
	if(i==0)
	{
		return '+';
	}
	else if(i==1)
	{
		return '-';
	}
	else
	{
		return '=';
	}
}

void arithematic()
{
	cout<<"arithematic function called.\n";
	for(int i=0;i<10;i++)
	{
		cout<<"Expression "<<i<<"\n";
		int a;
		getInt(a);
		char b;
		cout<<a<<" ";
		int result=a;
		b=getOperation();
		while(b!='=')
		{
			cout<<b<<" ";
			cout<<a<<" ";
			if(b=='+')
			{
				result+=a;
			}
			else if(b=='-')
			{
				result-=a;
			}
			getInt(a);
			b=getOperation();
		}
		cout<<b<<" ";
		cout<<result<<"\n";
		cout<<"\n";
	}
}