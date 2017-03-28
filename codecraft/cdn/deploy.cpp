#include "deploy.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//你要完成的功能总入口

int *cost_all;
	int *cost_server;
	int *cost_flow;
	//	int shortestcost[50][50];//this array will be update later .just for test

	int (*shortestcost)[MATVEX/2];

	shortestcost = (int (*)[MATVEX/2]) malloc (sizeof(int)*MATVEX*MATVEX/4);

	cost_all = (int *) malloc(sizeof(int)*MATVEX/2);
	cost_server = (int *) malloc(sizeof(int)*MATVEX/2);
	cost_flow = (int *) malloc(sizeof(int)*MATVEX/2);

	*cost_all = *cost_server+*cost_flow;

	Graph *GM;//GM is a pointer which point to a Graph type struct.

	GM = (Graph *) malloc(sizeof(Graph));
void deploy_server(char * topo[MAX_EDGE_NUM], int line_num,char * filename)
{

	

	if(GM==NULL)
	{
		printf("Malloc fail");
	}

	//	Consume *GC[MATVEX/2];//	
	//	GC = (Consume *[MATVEX/2]) malloc(2*sizeof(Consume));
	Consume *GC; //GC is a pointer which point to  consume point;
	GC = (Consume *) malloc (sizeof(Consume)*MATVEX/2);



	Patharc *Px[MATVEX];
	ShortPathTable *Dx;
	for(int i=0;i<MATVEX/2;i++)
			Px[i] =(Patharc *) malloc(MATVEX*MATVEX*MATVEX/2);
	Dx = (ShortPathTable * ) malloc(MATVEX*MATVEX);
printf("SSSSSSSSSSSSSSSSSSSSSS");

	int node_num;

	int net_link;
	int consume_num;
	int server_pri;




	int *point_f;
	int *point_t;
	int *pri;
	int *consume_n;

	point_f = (int *)malloc(sizeof(int));
	point_t = (int *)malloc(sizeof(int));
	pri = (int *)malloc(sizeof(int));
	consume_n= (int *)malloc(sizeof(int));

	consume_n = &consume_num;
	//#################################################baseline#################################
	sscanf(topo[0],"%d %d %d",&node_num,&net_link,&consume_num);
	sscanf(topo[2],"%d",&server_pri);


	*cost_server = consume_num * server_pri;
	*cost_flow = 0;


	printf("\nCost:%d\n",*cost_server);

	printf("node_num=%d, net_link=%d, consume_num=%d\nserver_pri=%d\n",node_num,net_link,consume_num,server_pri);


	CreatMGraph(GM,node_num,net_link,topo);//creat the Graph of all the net links


	for(int i=net_link+5;i<net_link+consume_num+5;i++)//creat the list of consume
	{
		int j,k,l;

		sscanf(topo[i],"%d %d %d",&j,&k,&l);
		(GC+i-net_link-5)->consume_point=j;
		(GC+i-net_link-5)->net_point=k;
		(GC+i-net_link-5)->capacity_request=l;
	}

	for(int i=0;i<consume_num;i++)  //print the consume information
	{

		printf("NO.%5d Node:%d Cost:%d\n",(GC+i)->consume_point,(GC+i)->net_point,(GC+i)->capacity_request);
	}


	//	PrintMGraph(GM);

	//	ShortestPath_Dijkstra(*GM,0,Px,Dx);

	for(int i=0;i<consume_num;i++)
	{


		printf("show GC:%d\n",(GC+i)->net_point);
		ShortestPath_Dijkstra(*GM,(GC+i)->net_point,Px[i],Dx);//shortest cost between 2 node points
		for(int j=0;j<node_num;j++)
		{
			for(int k=0;k<consume_num;k++)
			{
//				printf("k=%d net_point:%d\n",k,(GC+k)->net_point);
				if((GC+k)->net_point == j)
				{
					shortestcost[i][k] = (*Dx)[j];//shortest cost between 2 consume points
				}
			}


		}
	}



	printf("\n\%d\n\n",*(shortestcost+7)[7]);

	printf("print shortestcost:\n");
	for(int i=0;i<consume_num;i++)
	{
		for(int j=0;j<consume_num;j++)
		{
			printf("%5d",(*(shortestcost+i))[j]);

		}
		printf("\n");

	}

	findshortestlink(shortestcost,consume_n,point_f,point_t,pri);//find the shortest consume points.
	printf("\nthe shortestlink is :%d to %d, and price is :%d\n",*point_f,*point_t,*pri);
printf("146\n");
	
	printf("the path from %d to %d is:",*point_f,*point_t);

	int(*shortestcostpath)[MATVEX];

	shortestcostpath=(int( *)[MATVEX]) malloc(sizeof(int)*MATVEX*MATVEX);





	for(int i=0;i<node_num;i++)
	{
		printf("%d to ",(*(Px[*point_f]))[(GC+*point_t)->net_point]);

	}
	printf("\n\n\n");
	
	
	//#########################################################

	//	printf("###%d##",GM->price[0][0]);


	// 需要输出的内容
	//	char * topo_file = (char *)"17\n\n0 8 0 20\n21 8 0 20\n9 11 1 13\n21 22 2 20\n23 22 2 8\n1 3 3 11\n24 3 3 17\n27 3 3 26\n24 3 3 10\n18 17 4 11\n1 19 5 26\n1 16 6 15\n15 13 7 13\n4 5 8 18\n2 25 9 15\n0 7 10 10\n23 24 11 23";

	printf("malloc ok");


	char *topo_file;
	char *consume_link;
	topo_file = (char*) malloc(20*sizeof(char));
	consume_link = (char*) malloc(20*sizeof(char));


	printf("malloc ok");
	sprintf(topo_file,"%s\n\n",*(topo+net_link+5));
	for(int i=net_link+5;i<net_link+consume_num+5;i++)
	{
		sprintf(consume_link,"%s %s %s\n",(GC+i-net_link-5)->net_point,(GC+i-net_link-5)->consume_point,(GC+i-net_link-5)->capacity_request);

		strcat(topo_file,consume_link);
	}


	// 直接调用输出文件的方法输出到指定文件中(ps请注意格式的正确性，如果有解，第一行只有一个数据；第二行为空；第三行开始才是具体的数据，数据之间用一个空格分隔开)
	write_result(topo_file, filename);

	free(GM);
	free(GC);
	free(cost_all);
	free(cost_server);
	free(cost_flow);

}





//New functions from Nanjsun.


void CreatMGraph(Graph *G,int node_num,int net_link,char *topo[MAX_EDGE_NUM])
{
	int i,j,k,price,capacity;

	G->numVertexes = node_num;
	G->numEdges = net_link;

	for(i = 0;i<G->numVertexes;i++)
		for(j = 0;j <G->numVertexes;j++)
		{	
			G->price[i][j]=INFINITY; //set the default price to 65535
			G->capacity[i][j]=0; //set the default capacity to 0

		}
	for(k = 4;k < net_link+5 ;k++)
	{
		//		printf("输入边（vi,vj）上的下标i,下标j和权w:\n");


		sscanf(topo[k],"%d %d %d %d",&i,&j,&capacity,&price);


		G->price[i][j]=price;
		G->price[j][i]=price;
		G->capacity[i][j] = capacity;
		G->capacity[j][i] = capacity;

	}

}

void PrintMGraph(Graph *G)
{

	printf("MGraph as:\n");


	int i,j;
	for (i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
		{
			printf("%10d",G->price[i][j]);
		}
		printf("\n");
	}
}

void ShortestPath_Dijkstra (Graph G, int v0, Patharc *P,ShortPathTable *D)
{
	int v,w,k,min;
	k=0;
	int final[MATVEX];//final[w]=1 reprent geting the shortestpath from vo to vw

	for(v=0; v<G.numVertexes; v++)//initial data
	{
		final[v] = 0;
		(*D)[v] = G.price[v0][v];
		(*P)[v] = 0;
	}
	(*D)[v0] = 0;// v0 to v0 cost 0; 
	final[v0] = 1;//vo to vo had got the best result.

	for (v=1; v<G.numVertexes;v++)
	{
		min = INFINITY ;
		for (w = 0;w < G.numVertexes; w++)
		{
			if (!final[w] && (*D)[w]<min)
			{
				k=w;
				min = (*D)[w];
			}
		}
		final[k] = 1;
		for(w = 0;w < G.numVertexes; w++)
		{
			if (!final[w] && (min+G.price[k][w] < (*D)[w]))
			{
				(*D)[w] = min +G.price[k][w];
				(*P)[w]=k;
			}
		}
	}

}
void findshortestlink(int (*table)[MATVEX/2],int* consume_num,int* point_from,int* point_to,int* price)
{
	//price=(*table)[0];

	*price = 10000;
	printf("\nfindshortestlink\n");


	for(int i=0;i<*consume_num;i++)
	{

		printf("#####%d\n",i);
		for(int j=0;j<*consume_num;j++)
		{
			printf("_______%d\n",j);
			if( (*(table+i))[j]<*price &&((*(table+i))[j] != 0) )
			{
				*point_from = i;

				*point_to = j;
				*price=(*(table+i))[j];

				printf("point_from:%d",*point_from);
				printf("to:%d",*point_to);
				printf("cost:%d\n",*price);
			}
		}
	}
}

