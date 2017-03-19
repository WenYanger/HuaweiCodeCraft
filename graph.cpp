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

    this->FlowGraph = this->MainGraph;

    //Test: 初始化搜索点,-1为出发点
    this->setServer(64);
    this->setServer(229);
    this->setServer(559);
    this->setServer(669);
    this->setServer(769);
    this->setServer(829);

    //初始化搜索点,-1为出发点
    this->customerNodesSize = this->customerNodes.size();
    for (int i = 0; i < this->customerNodesSize; i++)
    {
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
    //this->SPFA();
    this->Dijkstra();

    int* customerCost = new int[this->numberCustomer];
    std::map<int,int> c;//消费节点cost与服务器id的映射
    for(int i=0; i<this->serverNodes.size(); i++){
        int cid = this->serverNodes[i];
        int ccost = this->dist[cid+1];
        customerCost[i] = ccost;
        c[ccost] = cid;

        std::cout<<this->dist[cid+1]<<": "<<cid<<std::endl;
    }

    //排序
    std::sort(customerCost, customerCost+this->serverNodes.size());

    //找当前服务器中花销最小的节点开始遍历，当前路径流量不可用时，重新进行最短路计算
    for(int i=0; i<this->serverNodes.size(); i++){
        int minServerID = c[customerCost[i]];
        int currentNodeID = minServerID;
        int minFlow;
        while(1){
            if(this->prev[currentNodeID+1] == 0){
                std::cout<<currentNodeID<<"->0"<<std::endl;
                break;
            }else{
                std::cout<<currentNodeID<<"->";
                currentNodeID = this->prev[currentNodeID+1];
            }
        }
    }

//    for(int i=0; i<this->numberNode; i++){
//        std::cout<<i<<" : "<<dis[i]<<std::endl;
//    }

    //delete cost;
}


void Graph::Dijkstra()
{
    int n = this->numberNode + 1;//注意这里，抽象了一个总的起点，注意下标变换

    if(!this->initialDijkstraFlag){
        this->S = new int[n];
        this->dist = new int[n];
        this->prev = new int[n];

        //初始化邻接矩阵
        this->A = new int*[n];
        for(int i=0; i<n; i++){
            A[i] = new int[n];
        }

        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                if(i==j){
                    A[i][j] = 0;
                }else{
                    A[i][j] = this->MAXINT;
                }
            }
        }

        int indexI,indexY;
        for(int i=0; i<n; i++){
            indexI = i-1;
            std::map<int, std::shared_ptr<Spring>> sp = this->MainGraph[indexI];
            for(std::map<int, std::shared_ptr<Spring>>::iterator it = sp.begin();  it!=sp.end();  ++it){
                indexY = it->first + 1;
                A[i][indexY] = it->second->cost;
            }
        }
        this->initialDijkstraFlag = 1;
    }



    //开始计算
    for(int i=0; i<n ; i++){
        this->dist[i] = this->A[0][i];
        this->S[i] = 0;
        if(this->dist[i] == this->MAXINT){
            this->prev[i] = -1;
        }
        else{
            this->prev[i] = 0;
        }
    }
    this->dist[0] = 0;
    this->S[0] = 1;
    for(int i=0; i<n; i++){
        int mindist = this->MAXINT;
        int u = 0;
        //找邻接最小权值对应点
        for(int j=0; j<n; j++){
            if(this->S[j]==0 && this->dist[j]<mindist){
                u = j;
                mindist = this->dist[j];
            }
        }
        this->S[u] = 1;
        for(int j=0; j<n; j++){
            if(this->S[j]==0 && this->A[u][j]<this->MAXINT){
                if(this->dist[u] + this->A[u][j] < this->dist[j] && (this->FlowGraph[u-1][j-1]->bandwich - this->FlowGraph[u-1][j-1]->bandwichCurrent)>0){//添加判断当前路流量是否越界
                    this->dist[j] = this->dist [u] + this->A[u][j];
                    this->prev[j] = u-1;
                }
            }
        }
    }

//    for(int i=0; i<n; i++){
//        std::cout<<i-1<<": "<<this->prev[i]<<std::endl;
//    }


}

void Graph::SPFA()
{
    //初始化距离数组
    int* dis = new int[this->numberNode];
    int* cost = new int[this->numberNode];
    int* visit = new int[this->numberNode];
    for(int i=0; i<this->numberNode; i++){
        dis[i]  = 999999;
        cost[i] = 0;
        visit[i] =0;
    }

    //使用BFS(SPFA)搜索最短路
    std::queue<int> q;
    q.push(-1);
    int preNodeId, nextNodeId;
    while(!q.empty()){
        preNodeId = q.front();
        q.pop();
        std::map<int, std::shared_ptr<Spring>> sp = this->MainGraph[preNodeId];

        for(std::map<int, std::shared_ptr<Spring>>::iterator it = sp.begin();  it!=sp.end();  ++it){
            //std::cout<<"key:"<<it->first<<"value:"<<it->second->bandwich<<std::endl;
            nextNodeId = it->first;
            if(preNodeId==-1){
                //std::cout<<(it->first)<<" : "<<dis[it->first];
                dis[nextNodeId] = 0;
                cost[nextNodeId] = 0;
                //std::cout<<"-> "<<dis[it->first]<<std::endl;


            }else{
                if((cost[preNodeId] + it->second->cost) < dis[nextNodeId]){
                    //std::cout<<(it->first)<<" : "<<dis[it->first];
                    cost[nextNodeId] = cost[preNodeId] + it->second->cost;
                    dis[nextNodeId] = cost[preNodeId] + it->second->cost;
                    //std::cout<<"-> "<<dis[it->first]<<std::endl;

                }
            }
            if(visit[nextNodeId]==0){
                q.push(nextNodeId);
                visit[nextNodeId]=1;
            }
        }
    }

    for(int i=0; i<this->numberNode; i++){
        std::cout<<i<<" : "<<dis[i]<<std::endl;
    }
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
    this->serverNodes.push_back(id);
    this->MainGraph[id][-2] = std::shared_ptr<Spring>(new Spring(999999,0));
}
