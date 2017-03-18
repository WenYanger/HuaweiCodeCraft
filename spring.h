#ifndef SPRING_H
#define SPRING_H


class Spring
{
public:
    int bandwich = 0; //最大流量
    int bandwichCurrent = 0; //当前流量
    int cost = 0;
public:
    Spring();
    Spring(int bandwich, int cost);
};

#endif // SPRING_H
