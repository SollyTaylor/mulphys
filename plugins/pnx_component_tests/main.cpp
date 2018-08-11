#include <QCoreApplication>
#include "Common.h"

#include "GeometricalField.h"
#include "Reader.h"
#include "ReaderBase.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QObject* obj = new QObject();

    {
        pnx::ReaderBase* rb = pnx::Reader::get("pnx_reader_stl",obj);
        qDebug() << rb->module_name();
    }

    delete obj;
    exit(0);
}
