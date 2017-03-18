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
    //std::cout<<this->numberNode<<" "<<this->numberSpring<<" "<<this->numberCustomer<<std::endl<<this->costServer<<std::endl;

    //初始化节点和链路
    while(!file.eof()){
        file>>idStart>>idEnd>>bandwich>>costRent;
        //std::cout<<idStart<<" "<<idEnd<<" "<<bandwich<<" "<<costRent<<std::endl;
        (this->MainGraph[idStart])[idEnd] = std::shared_ptr<Spring>(new Spring(bandwich,costRent));
        (this->MainGraph[idEnd])[idStart] = std::shared_ptr<Spring>(new Spring(bandwich,costRent));

        //初始化消费节点
        if(!(++countSpring < this->numberSpring)){
            while(!file.eof()){
                file>>idCustomer>>idLink>>bandwichRequired;
                this->customerNodes.push_back(std::shared_ptr<Node>(new Node(idLink,bandwichRequired)));
                //std::cout<<idCustomer<<" "<<idLink<<" "<<bandwichRequired<<std::endl;
            }
            this->customerNodes.erase(this->customerNodes.end()-1); // 删除多出来的一个节点
            break;
        }
    }

    //Test: 初始化搜索点,-1为出发点，-2为终止点
    this->setServer(14);
    this->setServer(32);

    //初始化搜索点,-1为出发点，-2为终止点
    this->customerNodesSize = this->customerNodes.size();
    for (int i = 0; i < this->customerNodesSize; i++)
    {
        //
        this->MainGraph[-1][this->customerNodes[i]->id] = std::shared_ptr<Spring>(new Spring(99999,0));
    }


    //std::cout<<this->MainGraph[0][26]->bandwich;

    this->getCost();
}

void Graph::randomSearch() // 暴力搜索
{
    //1. 进行估值计算，将节点进行价值排序
    
    //2. 
}

int Graph::getCost() // 获取当前的最小cost
{
    int serverCost = this->minCostNodes.size() * this->costServer; // 服务器部署费用

    //计算链路cost

    //初始化距离数组
    int* dis = new int[this->numberNode];
    int* cost = new int[this->numberNode];
    int* visit = new int[this->numberNode];
    for(int i=0; i<this->numberNode; i++){
        dis[i]  = 999999;
        cost[i] = 0;
        visit[i] =0;
    }

    std::queue<int> q;
    q.push(-1);
    while(!q.empty()){
        int nodeId = q.front();
        q.pop();
        std::map<int, std::shared_ptr<Spring>> sp = this->MainGraph[nodeId];

        for(std::map<int, std::shared_ptr<Spring>>::iterator it = sp.begin();  it!=sp.end();  ++it){
            //std::cout<<"key:"<<it->first<<"value:"<<it->second->bandwich<<std::endl;
            if(nodeId==-1){
                //std::cout<<(it->first)<<" : "<<dis[it->first];
                dis[it->first] = 0;
                cost[it->first] = 0;
                //std::cout<<"-> "<<dis[it->first]<<std::endl;
            }else{
                if((cost[nodeId] + it->second->cost) < dis[it->first]){
                    //std::cout<<(it->first)<<" : "<<dis[it->first];
                    cost[it->first] = cost[nodeId] + it->second->cost;
                    dis[it->first] = cost[nodeId] + it->second->cost;
                    //std::cout<<"-> "<<dis[it->first]<<std::endl;
                }
            }
            if(visit[it->first]==0){
                q.push(it->first);
                visit[it->first]=1;
            }
        }
    }

//    for(int i=0; i<this->numberNode; i++){
//        std::cout<<i<<" : "<<dis[i]<<std::endl;
//    }

    //delete cost;
}

void Graph::spfa(int s, int t)
{

}

void Graph::showGraph()
{
    for(int i=-1;i<50;i++){
        std::map<int, std::shared_ptr<Spring>> sp = this->MainGraph[i];
        std::cout<<"line "<<i<<std::endl;
        for(std::map<int, std::shared_ptr<Spring>>::iterator it = sp.begin(); it!=sp.end(); ++it){
            std::cout<<"  "<<it->first<<std::endl;
        }
    }
}

void Graph::setServer(int id){
    this->minCostNodes.push_back(id);
    this->MainGraph[id][-2] = std::shared_ptr<Spring>(new Spring(999999,0));
}
