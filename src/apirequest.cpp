#include "apirequest.h"
#include <QEventLoop>

APIRequest::APIRequest(QObject *parent)
    : QObject(parent),
    networkManager(new QNetworkAccessManager(this)) {}

QJsonDocument APIRequest::makeRequest(const QUrl &apiUrl, const QString &method, const QJsonObject &jsonData) const
{
    QNetworkRequest request(apiUrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = nullptr;
    if (method == "POST") {
        QByteArray data = QJsonDocument(jsonData).toJson();
        reply = networkManager->post(request, data);
    } else {  // Default is GET
        reply = networkManager->get(request);
    }

    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    QJsonDocument jsonResponse;
    if (reply->error() == QNetworkReply::NoError) {
        jsonResponse = QJsonDocument::fromJson(reply->readAll());
    } else {
        qWarning() << "Error en la solicitud:" << reply->errorString();
    }

    reply->deleteLater();
    return jsonResponse;
}

QJsonArray APIRequest::getJsonArray(const QUrl &apiUrl) const
{
    QJsonDocument jsonDoc = makeRequest(apiUrl);
    return jsonDoc.isArray() ? jsonDoc.array() : QJsonArray();
}

QJsonObject APIRequest::getJsonObject(const QUrl &apiUrl) const
{
    QJsonDocument jsonDoc = makeRequest(apiUrl);
    return jsonDoc.isObject() ? jsonDoc.object() : QJsonObject();
}

QJsonDocument APIRequest::get(const QUrl &apiUrl) const
{
    return makeRequest(apiUrl);
}
