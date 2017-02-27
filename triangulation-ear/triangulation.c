#include <stdio.h>


	#define X 0
	#define Y 1
	typedef enum {FALSE,TRUE} bool;
	#define DIM 2
	typedef int tPointi[DIM];

	typedef struct tVertexStructure tsVertex;
	typedef tsVertex *tVertex;
	typedef struct tVertexStructure{
		int vnum;
		tPointi v;
		bool ear;
		tVertex next,prev;

	};
	int nvertices;

	tVertex vertices=NULL;

	#define EXIT_FAILURE 1 
	char *malloc();//??

	#define NEW(p,type) \
		if((p=(type*)malloc(sizeof(type)))==NULL){\
		printf( "NEW:Out of Memory! \n");\
		exit(EXIT_FAILURE);\
			}


	#define ADD(head, p) if(head){\
	p->next=head;\
	p->prev=head->prev;\
	head->prev=p;\
	p->prev->next=p;\
	}\
	else{\
		head=p;\
		head->next=head->prev=p;\
	}


	#define FREE(p)  if (p) {free((char *)p) ; p=NULL;}


	int Area2(tPointi a,tPointi b, tPointi c)
	{

		return
			(b[X]-a[X])*(c[Y]-a[Y])-(c[X]-a[X])*(b[Y]-a[Y]);
	}

	int AreaPoly2(void){

		int sum=0;
		tVertex p,a;
		p=vertices;
		a=p->next;
		while(a->next!=vertices)
		{
			sum = sum+ Area2(p->v,a->v,a->next->v);
			a=a->next;
			}

		return sum;
	}

	bool Left(tPointi a,tPointi b,tPointi c)
	{

		return Area2(a,b,c)>0;
	}

	bool LeftOn(tPointi a,tPointi b,tPointi c)
	{

		return Area2(a,b,c)>=0;
	}

	bool Collinear(tPointi a,tPointi b,tPointi c)
	{

		return Area2(a,b,c)==0;
	}
	bool Xor(bool x,bool y)
	{
		return !x ^ !y;
	}

	bool IntersectProp(tPointi a,tPointi b,tPointi c,tPointi d)
	{
		if(
			Collinear(a,b,c)||
			Collinear(a,b,d)||
			Collinear(c,d,a)||
			Collinear(c,d,b))
			return FALSE;

		return
			Xor(Left(a,b,c),Left(a,b,d))
			&& Xor(Left(c,d,a),Left(c,d,b));
	}

	bool Between(tPointi a,	tPointi b,	tPointi c)
		{

			tPointi ba,ca;
			if(!Collinear(a,b,c))
					return FALSE;
			if(a[X]!=b[X])
				return((a[X]<=c[X])&&(c[X]<=b[X]))||((a[X]>=c[X])&&(c[X]>=b[X]));
				else
				return ((a[Y]<=c[Y])&&(c[Y]<=b[Y]))||((a[Y]>=c[Y])&&(c[Y]>=b[Y]));	
		}

	bool Intersect(tPointi a,tPointi b,tPointi c,tPointi d)
	{
		if(IntersectProp(a,b,c,d))
			return TRUE;
		else if(Between(a,b,c)||
			Between(a,b,d)
			||Between(c,d,a)
			||Between(c,d,b)
			)
			return TRUE;
		else return FALSE;

	}

	bool Diagonalie(tVertex a,tVertex b)
	{
		tVertex c,c1;

		c=vertices;
		do{
			c1=c->next;
			if((c!=a)&&(c1!=a)&&(c!=b)&&(c1!=b)&&Intersect(a->v,b->v,c->v,c1->v))
				return FALSE;
			c=c->next;
		}while(c!=vertices);
		return TRUE;

	}
	

	bool InCone(tVertex a,tVertex b)
		{

			tVertex a0,a1;
			a1=a->next;
			a0=a->prev;

			if(LeftOn(a->v,a1->v,a0->v))
				return Left(a->v,b->v,a0->v)
						&& Left(b->v,a->v,a1->v);

			return!(LeftOn(a->v,b->v,a1->v)&&LeftOn(b->v,a->v,a0->v));
						
		}

	bool Diagonal(tVertex a,tVertex b)
		{

			return InCone(a,b) &&InCone(b,a) &&Diagonalie(a,b);
		}	


	void EarInit(void)
	{
		tVertex v0,v1,v2;
		v1=vertices;
		do{
			v2=v1->next;
			v0=v1->prev;
			v1->ear=Diagonal(v0,v2);
			v1=v1->next;

		}while(v1!=vertices);

	}

	void Triangulate(void)
		{
			tVertex v0,v1,v2,v3,v4;
			int n=nvertices;
			
			EarInit();
			
			while(n>3){

				v2=vertices;
				do{
					if(v2->ear){
						v3=v2->next;v4=v3->next;
						v1=v2->prev;v0=v1->prev;

						printf("%d \t%d || %d\t %d\n",v1->v[X],v1->v[Y],v3->v[X],v3->v[Y] );

						v1->ear=(Diagonal(v0,v3));
						v3->ear=Diagonal(v1,v4);
						v1->next=v3;
						v3->prev=v1;
						vertices=v3;
						n--;
						break;
					}
					v2=v2->next;

				}while(v2!=vertices);
			}

		}


void ReadVertices(void)
	{
		printf("Number of vertices:- \n");
		scanf("%d",&nvertices);
		printf("Enter points:- \n");
		int temp=nvertices;
		int cnt=1;
		tsVertex *head;
		NEW(head,tsVertex);
		head=NULL;

		while(temp--)
		{
		tPointi a;
		float x,y;
		scanf("%f %f",&x,&y);
		a[X]=(int)x;
		a[Y]=(int)y;
		//printf("%d\n%d \n",a[X],a[Y] );
		tsVertex *p;
		NEW(p,tsVertex);
		p->vnum=cnt;
		(p->v)[X]=a[X];
		(p->v)[Y]=a[Y];

		ADD(head,p);

		cnt++;
		}

		vertices=head;
	}

	void PrintVertices(void)
	{
		tVertex v;
		v=vertices;
		do{
			printf("%d > %d \t %d \n",v->vnum,v->v[X],v->v[Y] );
			v=v->next;
		}while(v!=vertices);

	}

int main(){

	//only takes integer inputs

	ReadVertices();
	
	PrintVertices();
	
	printf("Diagonals:- \n");
	
	Triangulate();



}