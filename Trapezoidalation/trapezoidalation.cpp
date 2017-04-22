#include <bits/stdc++.h>
#include "opencv/cv.h"
#include <opencv2/highgui/highgui.hpp>


using namespace std;
using namespace cv;

//#define imsize 1000;

Mat img(1000,1000,CV_8UC3,Scalar(255,255,255));
std::vector<pair<int,int> > ip_points;


struct Pointv{
	int x, y;
	pair<int,int> e1;
	pair<int,int> e2;
};
typedef Pointv Pointv;

struct edge{
	pair<int,int> p1;
	pair<int,int> p2;
};
typedef edge edge;

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

bool compareByY(const Pointv &a, const Pointv &b)
{
    return a.y < b.y;
}


bool compareByX(const Pointv &a, const Pointv &b)
{
    return a.x < b.x;
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


int main(){
	int nvertices;
	cout<<"Enter number of vertices:"<<endl;
	cin>>nvertices;
	char choice;
	cout<<"Do you want trapezoidal decomposition by x or by y(x/y):";
	cin>>choice;

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

	cout<<ip_points.size()<<endl;
	
	if(choice=='X'||choice=='x')
	{
	vector<Pointv> Pointset;
	for(int i=0;i<ip_points.size();i++)
	{
		if(i==0)
		{
			Pointv a;
			a.x=ip_points[0].first;
			a.y=ip_points[0].second;
			a.e1=make_pair(ip_points[ip_points.size()-1].first,ip_points[ip_points.size()-1].second);
			a.e2=make_pair(ip_points[1].first,ip_points[1].second);
			Pointset.push_back(a);
		}
		else if(i==ip_points.size()-1)
		{
			Pointv a;
			a.x=ip_points[i].first;
			a.y=ip_points[i].second;
			a.e1=make_pair(ip_points[ip_points.size()-2].first,ip_points[ip_points.size()-2].second);
			a.e2=make_pair(ip_points[0].first,ip_points[0].second);
			Pointset.push_back(a);
		}
		else
		{
			Pointv a;
			a.x=ip_points[i].first;
			a.y=ip_points[i].second;
			a.e1=make_pair(ip_points[i-1].first,ip_points[i-1].second);
			a.e2=make_pair(ip_points[i+1].first,ip_points[i+1].second);
			Pointset.push_back(a);
		}	
	}
	for(int i=0;i<Pointset.size();i++)
		{
			cout<<Pointset[i].x<<" "<<Pointset[i].y<<endl;
			if(i!=Pointset.size()-1)
			line( img, Point(Pointset[i].x,Pointset[i].y), Point(Pointset[i+1].x,Pointset[i+1].y ), Scalar( 110, 220, 0 ),  2, 8 );
		}
		line( img, Point(Pointset[0].x,Pointset[0].y), Point(Pointset[Pointset.size()-1].x,Pointset[Pointset.size()-1].y ), Scalar( 110, 220, 0 ),  2, 8 );
	
	sort(Pointset.begin(),Pointset.end(),compareByY);
	cout<<Pointset.size()<<endl;

	// Begin the plane sweep algorithm--------------------------
	

	/*
	Declare a map data structure

	*/
	map <int, int> gquiz1;   
	  map <int, int> :: iterator itr;
    cout << "\nThe map gquiz1 is : \n";
    cout << "\tKEY\tELEMENT\n";
    for (itr = gquiz1.begin(); itr != gquiz1.end(); ++itr)
    {
        cout  <<  '\t' << itr->first 
              <<  '\t' << itr->second << '\n';
    }
    cout << endl;
 
    // assigning the elements from gquiz1 to gquiz2
    map <int, int> gquiz2(gquiz1.begin(), gquiz1.end());
 
    // print all elements of the map gquiz2
    cout << "\nThe map gquiz2 after assign from gquiz1 is : \n";
    cout << "\tKEY\tELEMENT\n";
    for (itr = gquiz2.begin(); itr != gquiz2.end(); ++itr)
    {
        cout  <<  '\t' << itr->first 
              <<  '\t' << itr->second << '\n';
    }
    cout << endl;
 
    // remove all elements up to element with key=3 in gquiz2
    cout << "\ngquiz2 after removal of elements less than key=3 : \n";
    cout << "\tKEY\tELEMENT\n";
    gquiz2.erase(gquiz2.begin(), gquiz2.find(3));
    for (itr = gquiz2.begin(); itr != gquiz2.end(); ++itr)
    {
        cout  <<  '\t' << itr->first 
              <<  '\t' << itr->second << '\n';
    }
 

	vector<edge> edges;

	int counter=0;
	while(1){
		cout<<"---------------------------------"<<endl;
		for(int i=0;i<edges.size();i++)
		{
			cout<<edges[i].p1.first<<" "<<edges[i].p1.second<<"||"<<edges[i].p2.first<<" "<<edges[i].p2.second<<endl;
		}
		if(counter==nvertices)
			break;
		else{	
				int flag1=0;
				int flag2=0;
				for(int i=0;i<edges.size();i++)
				{
					if((edges[i].p1.first==Pointset[counter].x&&edges[i].p1.second==Pointset[counter].y &&edges[i].p2.first==Pointset[counter].e1.first&&edges[i].p2.second==Pointset[counter].e1.second)||(edges[i].p1.first==Pointset[counter].e1.first&&edges[i].p1.second==Pointset[counter].e1.second &&edges[i].p2.first==Pointset[counter].x&&edges[i].p2.second==Pointset[counter].y ))
						flag1=1;
					if((edges[i].p1.first==Pointset[counter].x&&edges[i].p1.second==Pointset[counter].y &&edges[i].p2.first==Pointset[counter].e2.first&&edges[i].p2.second==Pointset[counter].e2.second )||(edges[i].p1.first==Pointset[counter].e2.first&&edges[i].p1.second==Pointset[counter].e2.second &&edges[i].p2.first==Pointset[counter].x&&edges[i].p2.second==Pointset[counter].y ))
						flag2=1;
				}
				
				//Draw a trapezoidal line
				/*int flag=0;

				for(int i=0;i<edges.size();i++)
				{
					
					float xist= (float)((edges[i].p2.first-edges[i].p1.first)*Pointset[counter].y-((edges[i].p1.second*edges[i].p2.first)-(edges[i].p2.second*edges[i].p1.first)))/(edges[i].p2.second-edges[i].p1.second);
						if(Pointset[counter].x<(int)xist){
						if(i!=0){
							float xist2= (float)((edges[i-1].p2.first-edges[i-1].p1.first)*Pointset[counter].y-((edges[i-1].p1.second*edges[i-1].p2.first)-(edges[i-1].p2.second*edges[i-1].p1.first)))/(edges[i-1].p2.second-edges[i-1].p1.second);
							line( img, Point((int)xist2,Pointset[counter].y), Point((int)xist,Pointset[counter].y ), Scalar( 110, 220, 0 ),  2, 8 );
						break;
						}
						else if(i==0)
						{
							line( img, Point(Pointset[counter].x,Pointset[counter].y), Point((int)xist,Pointset[counter].y ), Scalar( 110, 220, 0 ),  2, 8 );	
							break;
						}
						flag=1;
					}
				}
				if(flag==0&&edges.size()!=0)
				{
					float xist= (float)((edges[edges.size()-1].p2.first-edges[edges.size()-1].p1.first)*Pointset[counter].y-((edges[edges.size()-1].p1.second*edges[edges.size()-1].p2.first)-(edges[edges.size()-1].p2.second*edges[edges.size()-1].p1.first)))/(edges[edges.size()-1].p2.second-edges[edges.size()-1].p1.second);
					line( img, Point(Pointset[counter].x,Pointset[counter].y), Point((int)xist,Pointset[counter].y ), Scalar( 110, 220, 0 ),  2, 8 );
				}*/

				//Both edges correspoding to the vertex are not seen
				
				if(flag2==0&&flag1==0)
				{
					int flag3=0;
					int ptoinsert;
					for(int i=0;i<edges.size();i++)
					{
						float xist= (float)((edges[i].p2.first-edges[i].p1.first)*Pointset[counter].y-((edges[i].p1.second*edges[i].p2.first)-(edges[i].p2.second*edges[i].p1.first)))/(edges[i].p2.second-edges[i].p1.second);
						if(xist>Pointset[counter].x){
							flag3=1;
							ptoinsert=i;
							if(i-1>=0)
							{
								float xist2= (float)((edges[i-1].p2.first-edges[i-1].p1.first)*Pointset[counter].y-((edges[i-1].p1.second*edges[i-1].p2.first)-(edges[i-1].p2.second*edges[i-1].p1.first)))/(edges[i-1].p2.second-edges[i-1].p1.second);
								line( img, Point((int)xist2,Pointset[counter].y), Point((int)xist,Pointset[counter].y ), Scalar( 110, 220, 0 ),  2, 8 );

							}
							break;
						}

					}
					if(flag3==0)
						ptoinsert=edges.size();

					//Create a new vector
					edge e1,e2,swape;
					e1.p1.first=Pointset[counter].e1.first;
					e1.p1.second=Pointset[counter].e1.second;
					e1.p2.first=Pointset[counter].x;
					e1.p2.second=Pointset[counter].y;

					e2.p1.first=Pointset[counter].e2.first;
					e2.p1.second=Pointset[counter].e2.second;
					e2.p2.first=Pointset[counter].x;
					e2.p2.second=Pointset[counter].y;
					if(e1.p1.first>e2.p1.first)
					{
						swape=e1;
						e1=e2;
						e2=swape;
					}
					

					vector<edge>temp;
					if(ptoinsert==edges.size())
					{	
						edges.push_back(e1);
						edges.push_back(e2);
						
					}
					else{
					for(int i=0;i<edges.size();i++)
					{
						if(i==ptoinsert)
						{
							temp.push_back(e1);
							temp.push_back(e2);
						}
						temp.push_back(edges[i]);
					}
					edges=temp;
				  }
				}
				//One edge corresponding to the vertex is not seen
				else if((flag2==0&&flag1==1)||(flag2==1&&flag1==0))
				{
					
					if((flag2==0&&flag1==1))
					{
						cout<<"Reached"<<endl;
						int ptoinsert;
						for(int i=0;i<edges.size();i++)
						{
							float xist= (float)((edges[i].p2.first-edges[i].p1.first)*Pointset[counter].y-((edges[i].p1.second*edges[i].p2.first)-(edges[i].p2.second*edges[i].p1.first)))/(edges[i].p2.second-edges[i].p1.second);
							if((int)xist==Pointset[counter].x){
								ptoinsert=i;
							}
						}
						cout<<ptoinsert<<endl;	
						for(int i=0;i<edges.size();i++){
							if(i==ptoinsert){
								edge e1;
							e1.p1.first=Pointset[counter].e2.first;
							e1.p1.second=Pointset[counter].e2.second;
							e1.p2.first=Pointset[counter].x;
							e1.p2.second=Pointset[counter].y;
							edges[i]=e1;
							cout<<"i:"<<i<<endl;
							float xist2= (float)((edges[i-1].p2.first-edges[i-1].p1.first)*Pointset[counter].y-((edges[i-1].p1.second*edges[i-1].p2.first)-(edges[i-1].p2.second*edges[i-1].p1.first)))/(edges[i-1].p2.second-edges[i-1].p1.second);
							float xist3= (float)((edges[i+1].p2.first-edges[i+1].p1.first)*Pointset[counter].y-((edges[i+1].p1.second*edges[i+1].p2.first)-(edges[i+1].p2.second*edges[i+1].p1.first)))/(edges[i+1].p2.second-edges[i+1].p1.second);							
							if(i-1>=0&&i%2==1)
							line( img, Point((int)xist2,Pointset[counter].y), Point((int)Pointset[counter].x,Pointset[counter].y ), Scalar( 110, 220, 0 ),  2, 8 );
							else if(i+1<edges.size())
							line( img, Point((int)xist3,Pointset[counter].y), Point((int)Pointset[counter].x,Pointset[counter].y ), Scalar( 110, 220, 0 ),  2, 8 );
								
							}
						}




						}
					
					else if((flag2==1&&flag1==0))
					{

						int ptoinsert;
						for(int i=0;i<edges.size();i++)
						{
							float xist= (float)((edges[i].p2.first-edges[i].p1.first)*Pointset[counter].y-((edges[i].p1.second*edges[i].p2.first)-(edges[i].p2.second*edges[i].p1.first)))/(edges[i].p2.second-edges[i].p1.second);
							if((int)xist==Pointset[counter].x){
								ptoinsert=i;
						}
						}
						for(int i=0;i<edges.size();i++){
							if(i==ptoinsert){
								edge e1;
							e1.p1.first=Pointset[counter].e1.first;
							e1.p1.second=Pointset[counter].e1.second;
							e1.p2.first=Pointset[counter].x;
							e1.p2.second=Pointset[counter].y;
							edges[i]=e1;
							float xist2= (float)((edges[i-1].p2.first-edges[i-1].p1.first)*Pointset[counter].y-((edges[i-1].p1.second*edges[i-1].p2.first)-(edges[i-1].p2.second*edges[i-1].p1.first)))/(edges[i-1].p2.second-edges[i-1].p1.second);
							float xist3= (float)((edges[i+1].p2.first-edges[i+1].p1.first)*Pointset[counter].y-((edges[i+1].p1.second*edges[i+1].p2.first)-(edges[i+1].p2.second*edges[i+1].p1.first)))/(edges[i+1].p2.second-edges[i+1].p1.second);							
							if(i-1>=0&&i%2==1)
							line( img, Point((int)xist2,Pointset[counter].y), Point((int)Pointset[counter].x,Pointset[counter].y ), Scalar( 110, 220, 0 ),  2, 8 );
							else if(i+1<edges.size())
							line( img, Point((int)xist3,Pointset[counter].y), Point((int)Pointset[counter].x,Pointset[counter].y ), Scalar( 110, 220, 0 ),  2, 8 );
							
							}
						}


					}
				}
			
				//Both edge corresponding to vertex are seen
				else if(flag1==1&&flag2==1)
				{
					
					int ptoinsert1,ptoinsert2;

					for(int i=0;i<edges.size();i++)
				{
					
					if((edges[i].p1.first==Pointset[counter].x&&edges[i].p1.second==Pointset[counter].y &&edges[i].p2.first==Pointset[counter].e1.first&&edges[i].p2.second==Pointset[counter].e1.second )||(edges[i].p1.first==Pointset[counter].e1.first&&edges[i].p1.second==Pointset[counter].e1.second &&edges[i].p2.first==Pointset[counter].x&&edges[i].p2.second==Pointset[counter].y ))
						{
							ptoinsert1=i;
						}
					if((edges[i].p1.first==Pointset[counter].x&&edges[i].p1.second==Pointset[counter].y &&edges[i].p2.first==Pointset[counter].e2.first&&edges[i].p2.second==Pointset[counter].e2.second )||(edges[i].p1.first==Pointset[counter].e2.first&&edges[i].p1.second==Pointset[counter].e2.second &&edges[i].p2.first==Pointset[counter].x&&edges[i].p2.second==Pointset[counter].y ))
						{
							ptoinsert2=i;
						}
				}

				std::vector<edge> temp;
					for(int i=0;i<edges.size();i++)
					{
						if(i!=ptoinsert2&&i!=ptoinsert1)
							temp.push_back(edges[i]);
					}
					edges=temp;
					cout<<"size:"<<edges.size()<<endl;
					for(int i=0;i<edges.size();i++)
					{
						float xist= (float)((edges[i].p2.first-edges[i].p1.first)*Pointset[counter].y-((edges[i].p1.second*edges[i].p2.first)-(edges[i].p2.second*edges[i].p1.first)))/(edges[i].p2.second-edges[i].p1.second);
							
						//float xist= (float)((edges[i].p2.first-edges[i].p1.first)*Pointset[counter].y-((edges[i].p1.second*edges[i].p2.first)-(edges[i].p2.second*edges[i].p1.first)))/(edges[i].p2.second-edges[i].p1.second);
						if((int)xist>Pointset[counter].x){
							if(i-1>=0)
							{
								float xist2= (float)((edges[i-1].p2.first-edges[i-1].p1.first)*Pointset[counter].y-((edges[i-1].p1.second*edges[i-1].p2.first)-(edges[i-1].p2.second*edges[i-1].p1.first)))/(edges[i-1].p2.second-edges[i-1].p1.second);
								cout<<"HIIIIIII:"<<i<<endl;
								cout<<(int)xist<<" "<<(int) xist2<<endl;
								line( img, Point((int)xist2,Pointset[counter].y), Point((int)xist,Pointset[counter].y ), Scalar( 110, 220, 0 ),  2, 8 );
							break;
							}
							
						}

					}

				}
			counter++;
		}	

	}
}
else
{
vector<Pointv> Pointset;
	for(int i=0;i<ip_points.size();i++)
	{
		if(i==0)
		{
			Pointv a;
			a.x=ip_points[0].first;
			a.y=ip_points[0].second;
			a.e1=make_pair(ip_points[ip_points.size()-1].first,ip_points[ip_points.size()-1].second);
			a.e2=make_pair(ip_points[1].first,ip_points[1].second);
			Pointset.push_back(a);
		}
		else if(i==ip_points.size()-1)
		{
			Pointv a;
			a.x=ip_points[i].first;
			a.y=ip_points[i].second;
			a.e1=make_pair(ip_points[ip_points.size()-2].first,ip_points[ip_points.size()-2].second);
			a.e2=make_pair(ip_points[0].first,ip_points[0].second);
			Pointset.push_back(a);
		}
		else
		{
			Pointv a;
			a.x=ip_points[i].first;
			a.y=ip_points[i].second;
			a.e1=make_pair(ip_points[i-1].first,ip_points[i-1].second);
			a.e2=make_pair(ip_points[i+1].first,ip_points[i+1].second);
			Pointset.push_back(a);
		}	
	}
	for(int i=0;i<Pointset.size();i++)
		{
			cout<<Pointset[i].x<<" "<<Pointset[i].y<<endl;
			if(i!=Pointset.size()-1)
			line( img, Point(Pointset[i].x,Pointset[i].y), Point(Pointset[i+1].x,Pointset[i+1].y ), Scalar( 110, 220, 0 ),  2, 8 );
		}
		line( img, Point(Pointset[0].x,Pointset[0].y), Point(Pointset[Pointset.size()-1].x,Pointset[Pointset.size()-1].y ), Scalar( 110, 220, 0 ),  2, 8 );
	
	sort(Pointset.begin(),Pointset.end(),compareByX);
	cout<<Pointset.size()<<endl;

	// Begin the plane sweep algorithm--------------------------
	

	/*
	Declare a map data structure

	*/
	map <int, int> gquiz1;   
	  map <int, int> :: iterator itr;
    cout << "\nThe map gquiz1 is : \n";
    cout << "\tKEY\tELEMENT\n";
    for (itr = gquiz1.begin(); itr != gquiz1.end(); ++itr)
    {
        cout  <<  '\t' << itr->first 
              <<  '\t' << itr->second << '\n';
    }
    cout << endl;
 
    // assigning the elements from gquiz1 to gquiz2
    map <int, int> gquiz2(gquiz1.begin(), gquiz1.end());
 
    // print all elements of the map gquiz2
    cout << "\nThe map gquiz2 after assign from gquiz1 is : \n";
    cout << "\tKEY\tELEMENT\n";
    for (itr = gquiz2.begin(); itr != gquiz2.end(); ++itr)
    {
        cout  <<  '\t' << itr->first 
              <<  '\t' << itr->second << '\n';
    }
    cout << endl;
 
    // remove all elements up to element with key=3 in gquiz2
    cout << "\ngquiz2 after removal of elements less than key=3 : \n";
    cout << "\tKEY\tELEMENT\n";
    gquiz2.erase(gquiz2.begin(), gquiz2.find(3));
    for (itr = gquiz2.begin(); itr != gquiz2.end(); ++itr)
    {
        cout  <<  '\t' << itr->first 
              <<  '\t' << itr->second << '\n';
    }
 

	vector<edge> edges;

	int counter=0;
	while(1){
		cout<<"---------------------------------"<<endl;
		for(int i=0;i<edges.size();i++)
		{
			cout<<edges[i].p1.first<<" "<<edges[i].p1.second<<"||"<<edges[i].p2.first<<" "<<edges[i].p2.second<<endl;
		}
		if(counter==nvertices)
			break;
		else{	
				int flag1=0;
				int flag2=0;
				for(int i=0;i<edges.size();i++)
				{
					if((edges[i].p1.first==Pointset[counter].x&&edges[i].p1.second==Pointset[counter].y &&edges[i].p2.first==Pointset[counter].e1.first&&edges[i].p2.second==Pointset[counter].e1.second)||(edges[i].p1.first==Pointset[counter].e1.first&&edges[i].p1.second==Pointset[counter].e1.second &&edges[i].p2.first==Pointset[counter].x&&edges[i].p2.second==Pointset[counter].y ))
						flag1=1;
					if((edges[i].p1.first==Pointset[counter].x&&edges[i].p1.second==Pointset[counter].y &&edges[i].p2.first==Pointset[counter].e2.first&&edges[i].p2.second==Pointset[counter].e2.second )||(edges[i].p1.first==Pointset[counter].e2.first&&edges[i].p1.second==Pointset[counter].e2.second &&edges[i].p2.first==Pointset[counter].x&&edges[i].p2.second==Pointset[counter].y ))
						flag2=1;
				}
				
				//Draw a trapezoidal line
				/*int flag=0;

				for(int i=0;i<edges.size();i++)
				{
					
					float xist= (float)((edges[i].p2.first-edges[i].p1.first)*Pointset[counter].y-((edges[i].p1.second*edges[i].p2.first)-(edges[i].p2.second*edges[i].p1.first)))/(edges[i].p2.second-edges[i].p1.second);
						if(Pointset[counter].x<(int)xist){
						if(i!=0){
							float xist2= (float)((edges[i-1].p2.first-edges[i-1].p1.first)*Pointset[counter].y-((edges[i-1].p1.second*edges[i-1].p2.first)-(edges[i-1].p2.second*edges[i-1].p1.first)))/(edges[i-1].p2.second-edges[i-1].p1.second);
							line( img, Point((int)xist2,Pointset[counter].y), Point((int)xist,Pointset[counter].y ), Scalar( 110, 220, 0 ),  2, 8 );
						break;
						}
						else if(i==0)
						{
							line( img, Point(Pointset[counter].x,Pointset[counter].y), Point((int)xist,Pointset[counter].y ), Scalar( 110, 220, 0 ),  2, 8 );	
							break;
						}
						flag=1;
					}
				}
				if(flag==0&&edges.size()!=0)
				{
					float xist= (float)((edges[edges.size()-1].p2.first-edges[edges.size()-1].p1.first)*Pointset[counter].y-((edges[edges.size()-1].p1.second*edges[edges.size()-1].p2.first)-(edges[edges.size()-1].p2.second*edges[edges.size()-1].p1.first)))/(edges[edges.size()-1].p2.second-edges[edges.size()-1].p1.second);
					line( img, Point(Pointset[counter].x,Pointset[counter].y), Point((int)xist,Pointset[counter].y ), Scalar( 110, 220, 0 ),  2, 8 );
				}*/

				//Both edges correspoding to the vertex are not seen
				
				if(flag2==0&&flag1==0)
				{
					int flag3=0;
					int ptoinsert;
					for(int i=0;i<edges.size();i++)
					{
						//float xist= (float)((edges[i].p2.first-edges[i].p1.first)*Pointset[counter].y-((edges[i].p1.second*edges[i].p2.first)-(edges[i].p2.second*edges[i].p1.first)))/(edges[i].p2.second-edges[i].p1.second);
						float yist= ((float)(edges[i].p2.second-edges[i].p1.second)/(edges[i].p2.first-edges[i].p1.first))*(Pointset[counter].x)+((float)(edges[i].p1.second*edges[i].p2.first-edges[i].p2.second*edges[i].p1.first)/(edges[i].p2.first-edges[i].p1.first));
						if(yist>Pointset[counter].y){
							flag3=1;
							ptoinsert=i;
							if(i-1>=0)
							{
								float yist2= ((float)(edges[i-1].p2.second-edges[i-1].p1.second)/(edges[i-1].p2.first-edges[i-1].p1.first))*(Pointset[counter].x)+((float)(edges[i-1].p1.second*edges[i-1].p2.first-edges[i-1].p2.second*edges[i-1].p1.first)/(edges[i-1].p2.first-edges[i-1].p1.first));
						
								line( img, Point(Pointset[counter].x,(int)yist2), Point(Pointset[counter].x,(int)yist ), Scalar( 110, 220, 0 ),  2, 8 );

							}
							break;
						}

					}
					if(flag3==0)
						ptoinsert=edges.size();

					//Create a new vector
					edge e1,e2,swape;
					e1.p1.first=Pointset[counter].e1.first;
					e1.p1.second=Pointset[counter].e1.second;
					e1.p2.first=Pointset[counter].x;
					e1.p2.second=Pointset[counter].y;

					e2.p1.first=Pointset[counter].e2.first;
					e2.p1.second=Pointset[counter].e2.second;
					e2.p2.first=Pointset[counter].x;
					e2.p2.second=Pointset[counter].y;
					if(e1.p1.second>e2.p1.second)
					{
						swape=e1;
						e1=e2;
						e2=swape;
					}
					

					vector<edge>temp;
					if(ptoinsert==edges.size())
					{	
						edges.push_back(e1);
						edges.push_back(e2);
						
					}
					else{
					for(int i=0;i<edges.size();i++)
					{
						if(i==ptoinsert)
						{
							temp.push_back(e1);
							temp.push_back(e2);
						}
						temp.push_back(edges[i]);
					}
					edges=temp;
				  }
				}
				//One edge corresponding to the vertex is not seen
				else if((flag2==0&&flag1==1)||(flag2==1&&flag1==0))
				{
					
					if((flag2==0&&flag1==1))
					{
						cout<<"Reached"<<endl;
						int ptoinsert;
						for(int i=0;i<edges.size();i++)
						{
							float yist= ((float)(edges[i].p2.second-edges[i].p1.second)/(edges[i].p2.first-edges[i].p1.first))*(Pointset[counter].x)+((float)(edges[i].p1.second*edges[i].p2.first-edges[i].p2.second*edges[i].p1.first)/(edges[i].p2.first-edges[i].p1.first));
							if((int)yist==Pointset[counter].y){
								ptoinsert=i;
							}
						}
						cout<<ptoinsert<<endl;	
						for(int i=0;i<edges.size();i++){
							if(i==ptoinsert){
								edge e1;
							e1.p1.first=Pointset[counter].e2.first;
							e1.p1.second=Pointset[counter].e2.second;
							e1.p2.first=Pointset[counter].x;
							e1.p2.second=Pointset[counter].y;
							edges[i]=e1;
							cout<<"i:"<<i<<endl;
							float yist2= (float)((float)(edges[i-1].p2.second-edges[i-1].p1.second)/(edges[i-1].p2.first-edges[i-1].p1.first))*(Pointset[counter].x)+((float)(edges[i-1].p1.second*edges[i-1].p2.first-edges[i-1].p2.second*edges[i-1].p1.first)/(edges[i-1].p2.first-edges[i-1].p1.first));
							float yist3= (float)((float)(edges[i+1].p2.second-edges[i+1].p1.second)/(edges[i+1].p2.first-edges[i+1].p1.first))*(Pointset[counter].x)+((float)(edges[i+1].p1.second*edges[i+1].p2.first-edges[i+1].p2.second*edges[i+1].p1.first)/(edges[i+1].p2.first-edges[i+1].p1.first));
						
							if(i-1>=0&&i%2==1)
							line( img, Point(Pointset[counter].x,(int)yist2), Point((int)Pointset[counter].x,Pointset[counter].y ), Scalar( 110, 220, 0 ),  2, 8 );
							else if(i+1<edges.size())
							line( img, Point(Pointset[counter].x,(int)yist3), Point((int)Pointset[counter].x,Pointset[counter].y ), Scalar( 110, 220, 0 ),  2, 8 );
								
							}
						}




						}
					
					else if((flag2==1&&flag1==0))
					{

						int ptoinsert;
						for(int i=0;i<edges.size();i++)
						{
							float yist= (float)((float)(edges[i].p2.second-edges[i].p1.second)/(edges[i].p2.first-edges[i].p1.first))*(Pointset[counter].x)+((float)(edges[i].p1.second*edges[i].p2.first-edges[i].p2.second*edges[i].p1.first)/(edges[i].p2.first-edges[i].p1.first));
							if((int)yist==Pointset[counter].y){
								ptoinsert=i;
						}
						}
						for(int i=0;i<edges.size();i++){
							if(i==ptoinsert){
								edge e1;
							e1.p1.first=Pointset[counter].e1.first;
							e1.p1.second=Pointset[counter].e1.second;
							e1.p2.first=Pointset[counter].x;
							e1.p2.second=Pointset[counter].y;
							edges[i]=e1;
							float yist2= (float)((float)(edges[i-1].p2.second-edges[i-1].p1.second)/(edges[i-1].p2.first-edges[i-1].p1.first))*(Pointset[counter].x)+((float)(edges[i-1].p1.second*edges[i-1].p2.first-edges[i-1].p2.second*edges[i-1].p1.first)/(edges[i-1].p2.first-edges[i-1].p1.first));
							float yist3= (float)((float)(edges[i+1].p2.second-edges[i+1].p1.second)/(edges[i+1].p2.first-edges[i+1].p1.first))*(Pointset[counter].x)+((float)(edges[i+1].p1.second*edges[i+1].p2.first-edges[i+1].p2.second*edges[i+1].p1.first)/(edges[i+1].p2.first-edges[i+1].p1.first));
						
							if(i-1>=0&&i%2==1)
							line( img, Point(Pointset[counter].x,(int)yist2), Point((int)Pointset[counter].x,Pointset[counter].y ), Scalar( 110, 220, 0 ),  2, 8 );
							else if(i+1<edges.size())
							line( img, Point(Pointset[counter].x,(int)yist3), Point((int)Pointset[counter].x,Pointset[counter].y ), Scalar( 110, 220, 0 ),  2, 8 );
							
							}
						}


					}
				}
			
				//Both edge corresponding to vertex are seen
				else if(flag1==1&&flag2==1)
				{
					
					int ptoinsert1,ptoinsert2;

					for(int i=0;i<edges.size();i++)
				{
					
					if((edges[i].p1.first==Pointset[counter].x&&edges[i].p1.second==Pointset[counter].y &&edges[i].p2.first==Pointset[counter].e1.first&&edges[i].p2.second==Pointset[counter].e1.second )||(edges[i].p1.first==Pointset[counter].e1.first&&edges[i].p1.second==Pointset[counter].e1.second &&edges[i].p2.first==Pointset[counter].x&&edges[i].p2.second==Pointset[counter].y ))
						{
							ptoinsert1=i;
						}
					if((edges[i].p1.first==Pointset[counter].x&&edges[i].p1.second==Pointset[counter].y &&edges[i].p2.first==Pointset[counter].e2.first&&edges[i].p2.second==Pointset[counter].e2.second )||(edges[i].p1.first==Pointset[counter].e2.first&&edges[i].p1.second==Pointset[counter].e2.second &&edges[i].p2.first==Pointset[counter].x&&edges[i].p2.second==Pointset[counter].y ))
						{
							ptoinsert2=i;
						}
				}

				std::vector<edge> temp;
					for(int i=0;i<edges.size();i++)
					{
						if(i!=ptoinsert2&&i!=ptoinsert1)
							temp.push_back(edges[i]);
					}
					edges=temp;
					cout<<"size:"<<edges.size()<<endl;
					for(int i=0;i<edges.size();i++)
					{
						float yist= (float)((float)(edges[i].p2.second-edges[i].p1.second)/(edges[i].p2.first-edges[i].p1.first))*(Pointset[counter].x)+((float)(edges[i].p1.second*edges[i].p2.first-edges[i].p2.second*edges[i].p1.first)/(edges[i].p2.first-edges[i].p1.first));
								
						//float xist= (float)((edges[i].p2.first-edges[i].p1.first)*Pointset[counter].y-((edges[i].p1.second*edges[i].p2.first)-(edges[i].p2.second*edges[i].p1.first)))/(edges[i].p2.second-edges[i].p1.second);
						if((int)yist>Pointset[counter].y){
							if(i>=1)
							{
								float yist2= (float)((float)(edges[i-1].p2.second-edges[i-1].p1.second)/(edges[i-1].p2.first-edges[i-1].p1.first))*(Pointset[counter].x)+((float)(edges[i-1].p1.second*edges[i-1].p2.first-edges[i-1].p2.second*edges[i-1].p1.first)/(edges[i-1].p2.first-edges[i-1].p1.first));
							cout<<"HIIIIIII:"<<i<<endl;
								
								line( img, Point(Pointset[counter].x,(int)yist2), Point(Pointset[counter].x,(int)yist ), Scalar( 110, 220, 0 ),  2, 8 );
							break;
							}
							
						}

					}

				}
			counter++;
		}	

	}


}
	imshow("Trapezoidal decomposition",img);
	waitKey(0);


}


