#include "ToDoList.h"
#include"TaskReader.h"
#include"TaskWriter.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ToDoList w;
    TaskWriter task_writer;
    w.show();
    return a.exec();
}
