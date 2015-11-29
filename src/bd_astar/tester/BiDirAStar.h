/*PGR-GNU*****************************************************************

Copyright (c) 2015 pgRouting developers
Mail: project@pgrouting.org

------

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

********************************************************************PGR-GNU*/
/******************************************************************************
* $Id$
*
* Project:  pgRouting bdsp and bdastar algorithms
* Purpose:
* Author:   Razequl Islam <ziboncsedu@gmail.com>
*

******************************************************************************
* Permission is hereby granted, free of charge, to any person obtaining a
* copy of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies of this Software or works derived from this Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
* OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
* DEALINGS IN THE SOFTWARE.

*****************************************************************************/

#ifndef BIDIRASTAR_H
#define BIDIRASTAR_H

#include <vector>
#include <map>
#include <queue>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "MinHeap.h"
//#include "bdastar.h"

#define INF 1e15



typedef std::vector<long> LongVector;
typedef std::vector<LongVector> VectorOfLongVector;
//typedef std::pair<int, bool> PIB;
typedef std::pair<double, int> PDI;
//typedef std::pair<double, std::vector<int> > PDVI;

typedef struct edge 
{
	int id;
	int source;
	int target;
	double s_x;
	double s_y;
	double t_x;
	double t_y;
	double cost;
	double reverse_cost;
} edge_astar_t;

typedef struct path_element 
{
	int vertex_id;
	int edge_id;
	double cost;
}path_element_t;


typedef struct{
	int par_Node;
	int par_Edge;
}PARENT_PATH;

typedef struct{
	int NodeID;
	double xpos;
	double ypos;
	std::vector<int> Connected_Nodes;
	std::vector<int> Connected_Edges_Index;
}GraphNodeInfo;

struct GraphEdgeInfo
{
public:
	int EdgeID;
	int EdgeIndex;
	int Direction;
	double Cost;
	double ReverseCost;
	int StartNode;
	int EndNode;
};

typedef std::vector<GraphEdgeInfo> GraphEdgeVector;
typedef std::map<long,LongVector> Long2LongVectorMap;
typedef std::map<long,long> Long2LongMap;
typedef std::vector<GraphNodeInfo> GraphNodeVector;


class BiDirAStar
{
public:
	BiDirAStar(void);
	~BiDirAStar(void);
	
	int bidir_astar(edge_astar_t *edges, unsigned int edge_count, int maxNode, int start_vertex, int end_vertex,
		path_element_t **path, int *path_count, char **err_msg);
	

private:
	bool construct_graph(edge_astar_t *edges, int edge_count, int maxNode);
	void fconstruct_path(int node_id);
	void rconstruct_path(int node_id);
	bool addEdge(edge_astar_t edgeIn);
	bool connectEdge(GraphEdgeInfo& firstEdge, GraphEdgeInfo& secondEdge, bool bIsStartNodeSame);
	void init();
	void initall(int maxNode);
	void deleteall();
	//void explore(int cur_node, double cur_cost, int dir, std::priority_queue<PDI, std::vector<PDI>, std::greater<PDI> > &que);
	void explore(int cur_node, double cur_cost, int dir, MinHeap &que);
	double getcost(int node_id, int dir);
	void setcost(int node_id, int dir, double c);
	void setparent(int node_id, int dir, int parnode, int paredge);
	double gethcost(int node_id, int dir);
	double dist(double x1, double y1, double x2, double y2);

private:
	GraphEdgeVector m_vecEdgeVector;
	Long2LongMap m_mapEdgeId2Index;
	Long2LongVectorMap m_mapNodeId2Edge;
	GraphNodeVector m_vecNodeVector;
	int max_node_id;
	int max_edge_id;
	int m_lStartNodeId;
	int m_lEndNodeId;

	double m_MinCost;
	int m_MidNode;
	std::vector <path_element_t> m_vecPath;
	PARENT_PATH *m_pFParent;
	PARENT_PATH *m_pRParent;
	double *m_pFCost;
	double *m_pRCost;
};

#endif
