#ifndef NODE_H
#define NODE_H


class Node
{
public:
    int id=0;
    int customerFlag = 0;
    int bandwichRequired = 0; //消费节点所需的流量
    int bandCurrent = 0;    //当前已经满足的流量
public:
    Node();
    Node(int id,int bandwichRequired);
};

#endif // NODE_H
