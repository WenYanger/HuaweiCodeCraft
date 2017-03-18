#include "graph.h"

Graph::Graph()
{

}

void Graph::initialGraphFromFile(std::string filePath)
{
    std::ifstream file(filePath);
    if(!file){
        std::cout<<"File Open Failed.";
        return;
    }
    int idStart, idEnd, bandwich, costRent; // 初始化普通节点
    int idCustomer, idLink, bandwichRequired;  // 初始化消费节点
    int countSpring = 0;
    file>>this->numberNode>>this->numberSpring>>this->numberCustomer>>this->costServer;
    std::cout<<this->numberNode<<" "<<this->numberSpring<<" "<<this->numberCustomer<<std::endl<<this->costServer<<std::endl;

    //初始化节点和链路
    while(!file.eof()){
        file>>idStart>>idEnd>>bandwich>>costRent;
        std::cout<<idStart<<" "<<idEnd<<" "<<bandwich<<" "<<costRent<<std::endl;
        (this->MainGraph[idStart])[idEnd] = std::shared_ptr<Spring>(new Spring(bandwich,costRent));
        if(!(++countSpring < this->numberSpring)){
            while(!file.eof()){
                file>>idCustomer>>idLink>>bandwichRequired;
                this->customerNodes.push_back(std::shared_ptr<Node>(new Node(idLink,bandwichRequired)));
                std::cout<<idCustomer<<" "<<idLink<<" "<<bandwichRequired<<std::endl;
            }
            break;
        }
    }

    std::cout<<this->MainGraph[0][26]->bandwich;


}

void Graph::randomSearch() // 暴力搜索
{

}
