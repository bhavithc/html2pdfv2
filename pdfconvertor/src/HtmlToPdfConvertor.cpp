#include "HtmlToPdfConvertor.h"

#include <QDebug>

HtmlToPdfConvertor::HtmlToPdfConvertor(const std::string &htmlFilePath, const std::string &pdfFilePath)
    : m_htmlFilePath(htmlFilePath)
    , m_pdfFilePath(pdfFilePath)
{
    QObject::connect(&m_view, SIGNAL(pdfPrintingFinished(const QString &, bool)), this, SLOT(pdfGenerated(const QString &, bool)));
    QObject::connect(&m_view, SIGNAL(loadStarted()), this, SLOT(loadStarted()));
    QObject::connect(&m_view, SIGNAL(loadProgress(int)), this, SLOT(loadProgress(int)));
    QObject::connect(&m_view, SIGNAL(loadFinished(bool)), this, SLOT(loadFinished(bool)));
}

void HtmlToPdfConvertor::convert(QFuture<bool>& fut)
{
    m_view.load(QUrl::fromLocalFile(m_htmlFilePath.c_str()));
    fut = m_promise.future();
    m_promise.start();
}

void HtmlToPdfConvertor::loadStarted()
{
    qDebug() << "Loading " << m_htmlFilePath.c_str() << " ...";
}

void HtmlToPdfConvertor::loadProgress(int progress)
{
    qDebug() << "Completed " << progress << "%";
}

void HtmlToPdfConvertor::loadFinished(bool success)
{
    if (success) {
        qDebug() << m_htmlFilePath.c_str() << " loaded !";
        m_view.printToPdf(m_pdfFilePath.c_str());
    } else {
        qDebug() << "Failed to load the html file !";
        pdfGenerated(QString::fromStdString(m_pdfFilePath), false);
    }

}

void HtmlToPdfConvertor::pdfGenerated(const QString& outputPath, bool success)
{
    if (success) {
        qDebug() << "Pdf generated successfully !";
    } else {
        qDebug() << "Failed to generate pdf !";
    }
    m_promise.addResult(success);
    m_promise.finish();
}
