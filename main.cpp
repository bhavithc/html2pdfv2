#include <QtWidgets>
#include <QElapsedTimer>
#include "HtmlToPdfConvertor.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QElapsedTimer timer;
    timer.start();

    HtmlToPdfConvertor convertor(
            "D:/Development/html2pdfv2/build-html2pdfv2-Desktop_Qt_6_4_3_MSVC2019_64bit-Debug/test.html",
            "D:/Development/html2pdfv2/build-html2pdfv2-Desktop_Qt_6_4_3_MSVC2019_64bit-Debug/output.pdf");
    QFuture<bool> fut;
    convertor.convert(fut);
//    fut.waitForFinished();
    const bool success = true; //fut.result();

    qDebug() << "The slow operation took" << timer.elapsed() << "milliseconds";
    qDebug() << "The slow operation took" << timer.nsecsElapsed() << "nanoseconds";

    if (success) {
        qDebug() << "SUCCESS";
    } else {
        qDebug() << "FAILED";
    }

    return a.exec();
}
