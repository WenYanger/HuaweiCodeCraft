#include <QCoreApplication>
#include <graph.h>
#include <QDebug>      // 用于检查运行时间
#include <sys/time.h>  // 用于检查运行时间

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    struct timeval tpstart,tpend;
    float timeuse;
    gettimeofday(&tpstart,NULL);

    std::string filePath = "D:\\Development\\C++ Program\\HuaweiCodeCraft\\case_example\\case10000.txt";
    Graph * g = new Graph();
    g->initialGraphFromFile(filePath);
    //g->showGraph();


    gettimeofday(&tpend,NULL);
    timeuse=(1000000*(tpend.tv_sec-tpstart.tv_sec) + tpend.tv_usec-tpstart.tv_usec)/1000000.0;
    qDebug()<<timeuse<<"s";


    return a.exec();
}
