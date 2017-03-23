#ifndef __ROUTE_H__
#define __ROUTE_H__

#include "lib_io.h"
#include <stdio.h>
#define MATVEX 810
#define INFINITY 65535
typedef int Patharc[MATVEX];
typedef int ShortPathTable[MATVEX];

typedef char VertexType;
typedef int EdgeType;

typedef struct
{
	int vexs[MATVEX];
	int price[MATVEX] [MATVEX];
	int capacity[MATVEX] [MATVEX];
	int numVertexes, numEdges;
}Graph;

typedef struct
{

	int consume_point;
	int net_point;
	int capacity_request;
	int cost_already;
}Consume;

//void findshortestlink(int (*table)[50],int consumen_num,int point_from,int point_to,int price);
void findshortestlink(int (*table)[MATVEX/2],int* consume_num,int* point_from,int* point_to,int* price);

void printx();
void CreatMGraph(Graph *G,int node_num,int net_link,char * topo[MAX_EDGE_NUM]);
void PrintMGraph(Graph *G);

void ShortestPath_Dijkstra (Graph G, int v0, Patharc *P,ShortPathTable *D);

//void CreatMConsume(MConsume G, char *topo[MAX_EDGE_NUM]);//define a function to creat consume table

void deploy_server(char * graph[MAX_EDGE_NUM], int edge_num, char * filename);



#endif





//New functions from Nanjsun.



//	void CreatMGraph(MGraph *G,int node_num,int net_link,char * const topo[MAX_EDGE_NUM]);
