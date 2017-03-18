#ifndef GRAPH_H
#define GRAPH_H
#include <node.h>
#include <spring.h>
#include <map>
#include <vector>
#include <queue>
#include <memory>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


class Graph
{
public:
    std::map<int, std::map<int, std::shared_ptr<Spring>>> MainGraph; //使用字典实现疏松矩阵
    std::vector<std::shared_ptr<Node>> customerNodes; //记录消费节点对应的普通节点，用于搜索
    int customerNodesSize;
    std::vector<int> minCostNodes; //当前最小成本对应的服务器所在节点id
    int numberNode; //网络节点数量
    int numberSpring; //网络链路数量
    int numberCustomer; //消费节点数量
    int costServer;  //视频内容服务器部署成本
    int costCurrent; //当前总成本
    int costMinimum; //当前最小成本




public:
    Graph();

    void initialGraphFromFile(std::string filePath);
    void randomSearch();
    int getCost();

    void showGraph();

private:
    void setServer(int id);

};

#endif // GRAPH_H
