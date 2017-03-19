#include "node.h"

Node::Node()
{

}

Node::Node(int id, int bandwichRequired):id(id),bandwichRequired(bandwichRequired)
{}

Node::Node(int id, std::shared_ptr<Node> preNode):id(id),preNode(preNode)
{}
