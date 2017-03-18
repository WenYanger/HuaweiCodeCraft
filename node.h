#ifndef NODE_H
#define NODE_H
#include <memory>


class Node
{
public:
    int id=0;
    int customerFlag = 0;
    int bandwichRequired = 0; //消费节点所需的流量
    int bandCurrent = 0;    //当前已经满足的流量

    std::shared_ptr<Node> preNode;
    std::shared_ptr<Node> nextNode;

public:
    Node();
    Node(int id,int bandwichRequired);
};

#endif // NODE_H
