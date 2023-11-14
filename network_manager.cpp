#include "network_manager.h"

network_manager::network_manager()
{
    qnam = new QNetworkAccessManager(this);
}

network_manager::~network_manager()
{
    delete qnam;
}

void network_manager::get(const char* URL)
{
    QNetworkReply *res = qnam->get(QNetworkRequest(QUrl(URL)));

    connect(qnam, &QNetworkAccessManager::finished,
            this, &network_manager::reply_finished);

    connect(res, &QNetworkReply::errorOccurred,
            this, &network_manager::network_error);

    connect(res, &QNetworkReply::sslErrors,
            this, &network_manager::ssl_error);
}

void network_manager::post(const char* URL, std::string query_str)
{
    QNetworkRequest req = QNetworkRequest(QUrl(URL));
    req.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/x-www-form-urlencoded"));
    QNetworkReply *res = qnam->post(req, QByteArray(query_str.c_str()));

    connect(qnam, &QNetworkAccessManager::finished,
            this, &network_manager::reply_finished);

    connect(res, &QNetworkReply::errorOccurred,
            this, &network_manager::network_error);

    connect(res, &QNetworkReply::sslErrors,
            this, &network_manager::ssl_error);
}

void network_manager::create_user(std::string email, std::string username, std::string pass)
{
    std::string url = "http://cop4331wastaken.com/users/";

    std::string query = "";
    query.append("email=" + email + "&");
    query.append("username=" + username + "&");
    query.append("password=" + pass);

    this->post(url.c_str(), query);
}

void network_manager::get_user(std::string email, std::string pass)
{
    std::string url = "http://cop4331wastaken.com/users/";
    url.append(email);
    url.append("/");
    url.append(pass);
    printf("%s\n", url.c_str());
    this->get(url.c_str());
}

void network_manager::reply_finished(QNetworkReply *reply)
{
    QByteArray res = reply->readAll();
    network_response = res.toStdString();
    printf("%s\n", res.toStdString().c_str());
    reply->deleteLater();
}

void network_manager::network_error()
{
    printf("ERROR OCCURED\n");
}

void network_manager::ssl_error()
{
    printf("ssl error (?)\n");
}


