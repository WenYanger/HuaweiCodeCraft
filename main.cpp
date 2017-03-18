#include <QCoreApplication>
#include <graph.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::string filePath = "D:\\Development\\C++ Program\\HuaweiCodeCraft\\case_example\\case0.txt";
    Graph * g = new Graph();
    g->initialGraphFromFile(filePath);
    return a.exec();
}
