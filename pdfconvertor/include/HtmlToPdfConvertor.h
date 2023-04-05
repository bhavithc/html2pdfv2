#pragma once

#include <QtWidgets>
#include <QtWebEngineWidgets>
#include <QObject>

#include <string>
#include <QPromise>
#include <QFuture>

class HtmlToPdfConvertor : public QObject
{
    Q_OBJECT
public:
    explicit HtmlToPdfConvertor(const std::string& htmlFilePath, const std::string& pdfFilePath);
    void convert(QFuture<bool>& fut);
public slots:
    void loadStarted();
    void loadProgress(int progress);
    void loadFinished(bool success);
    void pdfGenerated(const QString& outputPath, bool success);

private:
    std::string m_htmlFilePath {""};
    std::string m_pdfFilePath {""};
    QWebEngineView m_view;
    QPromise<bool> m_promise;
};
