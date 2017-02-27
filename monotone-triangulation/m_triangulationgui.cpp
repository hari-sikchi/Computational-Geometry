#include <bits/stdc++.h>
#include"opencv/cv.h"
#include<opencv2/highgui/highgui.hpp>
//Implementation of x-monotone polygon triangulations

using namespace std;
using namespace cv;

//#define imsize 1000;

Mat img(1000,1000,CV_8UC3,Scalar(255,255,255));
std::vector<pair<int,int> > ip_points;


struct Node{
	int x,y;
	Node * next;
	int label;

};
typedef Node Node;

struct _list{
	int nvertices;
	Node * head;
};
typedef _list _list;


typedef pair<pair<int,int>,int> tuple;

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
     if  ( event == EVENT_LBUTTONDOWN )
     {
          cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
          ip_points.push_back(make_pair(x,y));
          circle( img, Point(x,y), 32.0, Scalar( 0, 0, 255 ), 1, 1 );
          circle( img, Point(x,y), 32.0, Scalar( 0, 0, 255 ), 1, 5 );
     }
     
}


long long int Area2( tuple a,tuple  b, tuple  c)

	{

		return
			(b.first.first-a.first.first)*(c.first.second-a.first.second)-(c.first.first-a.first.first)*(b.first.second-a.first.second);
	}

int left(tuple a,tuple b,tuple c)
	{
		//cout<<"Area2"<<Area2(a,b,c)<<endl;
		if( Area2(a,b,c)>0)
		{
			return 1;

		}
		else return 0;
	}

_list insertpoints(int nvertices)
{

	
	_list polygon;
	polygon.head=NULL;
	polygon.nvertices=nvertices;

	
	int x,y;
	//cin>>x>>y;
	x=ip_points[0].first;
	y=ip_points[0].second;
	Node* current;
	polygon.head=new Node;
	polygon.head->x=x;
	polygon.head->y=y;
	polygon.head->next=NULL;
	
	current=polygon.head;
	int temp=nvertices-1;
	int ctr=1;
	while(temp)
	{
		x=ip_points[ctr].first;
	y=ip_points[ctr].second;
		//cin>>x>>y;
		Node* node1=new Node;
		current->next=node1;
		node1->x=x;
		node1->y=y;
		node1->next=NULL;
		
		current=current->next;


		temp--;
		ctr++;
	}
	current->next=polygon.head;
	
	return polygon;


}

int check_monotonocity(_list polygon)
{
	
	int miny=999999;
		int maxy=-10;
		Node* minnode=NULL; 
		Node*current=polygon.head;
		for(int i=0;i<polygon.nvertices;i++)
		{
			if(current->y<miny)
			{

				miny=current->y;
				minnode=current;
			}
			if(current->y>maxy)
				maxy=current->y;

		}

		current=minnode;
		int temp=polygon.nvertices;

		int ctr=0;

		while(1)
	{
		if(current->next->y>current->y)
			{
				
				ctr++;
			}
			else break;
			current=current->next;
	}

		while(1)
	{
		if(current->next->y<current->y)
			{
				
				ctr++;
			}
			else break;
			current=current->next;
	}
	cout<<"no of counter:"<<ctr<<endl;

	if(ctr==polygon.nvertices)	
		return 1;
	else return 0;


}
void label_vertices(_list polygon)
	{	
		int miny=999999;
		int maxy=-10;
		Node* minnode=NULL; 
		Node*current=polygon.head;
		for(int i=0;i<polygon.nvertices;i++)
		{
			if(current->y<miny)
			{

				miny=current->y;
				minnode=current;
			}
			if(current->y>maxy)
				maxy=current->y;

		}

		current=minnode;
		int temp=polygon.nvertices;

		std::vector<pair<pair<int,int>,int> > list1;
		std::vector<pair<pair<int,int>,int> > list2;
		
		
		int flag=0;
		if(current->next->x>current->x)
			{
				flag=1;
			}
			//If flag=1 means that list1 is right side list and list2 is left otherwise vice-versa

		while(temp--)
	{
		if(current->next->y>current->y)
			{
				
				current->label=1;
				
			
				pair<pair<int,int>,int> p;
				p=make_pair(make_pair(current->x,current->y),1);
				list1.push_back(p);
			}
		else
			{
				pair<pair<int,int>,int> p;
				p=make_pair(make_pair(current->x,current->y),2);
				list2.push_back(p);
					
				current->label=2;
			}
			current=current->next;
	}

	reverse(list1.begin(),list1.end());
	//cout<<"hello"<<endl;
	cout<<list1.size()<<list2.size()<<endl;

	//sort vertices by merging two lists
	std::vector<pair<pair<int,int>,int> > flist;
	while(list1.size()!=0||list2.size()!=0)
	{
		if(list1.size()>0&&list2.size()>0)
		{
			if((list1.back()).first.second<(list2.back()).first.second)
			{
				flist.push_back(list1.back());
				list1.pop_back();
			}
			else if((list1.back()).first.second>(list2.back()).first.second)
			{
				flist.push_back(list2.back());
				list2.pop_back();
			}
		}
		else if(list1.size()==0)
		{
			flist.push_back(list2.back());
				list2.pop_back();
		}
		else if(list2.size()==0)
		{
			flist.push_back(list1.back());
				list1.pop_back();

		}
	}

cout<<flist.size()<<endl;
	for(int i=0;i<flist.size();i++)
	{

		cout<<flist[i].first.first<<" "<<flist[i].first.second<<" ||"<<flist[i].second<<endl;
	}

cout<<"Flag:"<<flag<<endl;
	reverse(flist.begin(),flist.end());

	//got the sorted order with labels
	stack<pair<pair<int,int>,int> >s;
	s.push(flist.back());
	flist.pop_back();
	s.push(flist.back());
	flist.pop_back();
	
	while(flist.size()!=0)
	{
		pair<pair<int,int>,int> first,second,temp;
		
		if(flag==1)
		{

		if(flist.back().second==1 && s.top().second==1)
		{	
		

			
					while(s.size()>1)
					{
						first=s.top();
						s.pop();
						second=s.top();
						s.push(first);
						if(left(flist.back(),second,first)==1)
						{
							cout<<flist.back().first.first<<" "<<flist.back().first.second<<" ||"<<second.first.first<<" "<<second.first.second<<endl;
							line( img, Point( flist.back().first.first,flist.back().first.second  ), Point( second.first.first, second.first.second), Scalar( 110, 220, 0 ),  2, 8 );
							s.pop();
						}
						else 
							{
								break;
							}

					}
				
		}
		else if(flist.back().second==2&&s.top().second==2)
		{
		
			
			while(s.size()>1)
					{
						first=s.top();
						s.pop();
						second=s.top();
						s.push(first);
						if(left(flist.back(),second,first)==0)
						{
							cout<<flist.back().first.first<<" "<<flist.back().first.second<<" ||"<<second.first.first<<" "<<second.first.second<<endl;
							line( img, Point( flist.back().first.first,flist.back().first.second  ), Point( second.first.first, second.first.second), Scalar( 110, 220, 0 ),  2, 8 );
							s.pop();
						}
						else 
							{
								break;
							}

					}

		}
		else if(flist.back().second==1&&s.top().second==2||flist.back().second==2&&s.top().second==1)
		{
			temp=s.top();
			cout<<"-----------"<<endl;
			while(!s.empty(	))

			{
				cout<<flist.back().first.first<<" "<<flist.back().first.second<<" ||"<<s.top().first.first<<" "<<s.top().first.second<<endl;
				line( img, Point( flist.back().first.first,flist.back().first.second  ), Point( s.top().first.first, s.top().first.second), Scalar( 110, 220, 0 ),  2, 8 );		
				s.pop();


			}
			cout<<"-----------"<<endl;
			s.push(temp);
			line( img, Point( flist.back().first.first,flist.back().first.second  ), Point( temp.first.first,temp.first.second), Scalar( 110, 220, 0 ),  2, 8 );


		}
		
		s.push(flist.back());
		flist.pop_back();	
	}

	else
	{
		if(flist.back().second==1 && s.top().second==1)
		{		
			
					while(s.size()>1)
					{
						first=s.top();
						s.pop();
						second=s.top();
						s.push(first);
						if(left(flist.back(),second,first)==0)
						{
							cout<<flist.back().first.first<<" "<<flist.back().first.second<<" ||"<<second.first.first<<" "<<second.first.second<<endl;
							line( img, Point( flist.back().first.first,flist.back().first.second  ), Point( second.first.first, second.first.second), Scalar( 110, 220, 0 ),  2, 8 );
							s.pop();
						}
						else 
							{
								break;
							}

					}
				
		}
		else if(flist.back().second==2&&s.top().second==2)
		{
			
			first=s.top();
						s.pop();
						second=s.top();
						s.push(first);

			
			while(s.size()>1)
					{
						first=s.top();
						s.pop();
						second=s.top();
						s.push(first);
						if(left(flist.back(),second,first)==1)
						{
							cout<<flist.back().first.first<<" "<<flist.back().first.second<<" ||"<<second.first.first<<" "<<second.first.second<<endl;
							line( img, Point( flist.back().first.first,flist.back().first.second  ), Point( second.first.first, second.first.second), Scalar( 110, 220, 0 ),  2, 8 );
							s.pop();
						}
						else 
							{
								break;
							}

					}
				

		}
		else if(flist.back().second==1&&s.top().second==2||flist.back().second==2&&s.top().second==1)
		{
			temp=s.top();
			cout<<"-----------"<<endl;
			while(!s.empty(	))

			{
				cout<<flist.back().first.first<<" "<<flist.back().first.second<<" ||"<<s.top().first.first<<" "<<s.top().first.second<<endl;
				line( img, Point( flist.back().first.first,flist.back().first.second  ), Point( s.top().first.first, s.top().first.second), Scalar( 110, 220, 0 ),  2, 8 );		
				s.pop();


			}
			cout<<"-----------"<<endl;

			line( img, Point( flist.back().first.first,flist.back().first.second  ), Point( temp.first.first,temp.first.second), Scalar( 110, 220, 0 ),  2, 8 );

			s.push(temp);


		}
		
		s.push(flist.back());
		flist.pop_back();
	}

}
}




int main(){
	int nvertices;
	cout<<"Enter number of vertices:"<<endl;
	cin>>nvertices;

 namedWindow("Workspace", 1);

 while(1)
 {
 imshow("Workspace",img);
 setMouseCallback("Workspace", CallBackFunc, NULL);
 
 
 int k=waitKey(10);
 if(k==27)
 	break;
//print points
}
_list polygon;
polygon=insertpoints(nvertices);

Node* current=polygon.head;
cout<<"Points:-"<<endl;

	for(int i=0;i<nvertices;i++)
	{

		
		
		cout<<current->x<<" "<<current->y<<endl;
		
		
		current=current->next;
	}

if(check_monotonocity(polygon)==1)
{
		
	for(int i=0;i<ip_points.size()-1;i++)
	{

		line( img, Point(ip_points[i].first, ip_points[i].second ), Point(ip_points[i+1].first,ip_points[i+1].second ), Scalar( 110, 220, 0 ),  2, 8 );
	}
	line( img, Point(ip_points[0].first, ip_points[0].second ), Point(ip_points[ip_points.size()-1].first,ip_points[ip_points.size()-1].second ), Scalar( 110, 220, 0 ),  2, 8 );

	label_vertices( polygon);

	imshow("Output",img);
	waitKey(0);
}
else
{

	cout<<"The Polygon is not y-monotone"<<endl;
}

}