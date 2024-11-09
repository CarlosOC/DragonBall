#ifndef APIREQUEST_H
#define APIREQUEST_H

#include <QString>
#include <QJsonObject>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>

class APIRequest : public QObject
{
    Q_OBJECT

public:
    explicit APIRequest(QObject *parent = nullptr);

    QJsonArray getJsonArray(const QUrl &apiUrl) const;
    QJsonObject getJsonObject(const QUrl &apiUrl) const;
    QJsonDocument get(const QUrl &apiUrl) const;

private:
    QJsonDocument makeRequest(const QUrl &apiUrl, const QString &method = "GET", const QJsonObject &jsonData = {}) const;

    QNetworkAccessManager *networkManager;
};

#endif // APIREQUEST_H
