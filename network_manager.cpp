#include "network_manager.h"

network_manager::network_manager()
{
    qnam = new QNetworkAccessManager(this);
}

network_manager::~network_manager()
{
    delete qnam;
}

bool network_manager::get(const char* URL)
{
    QNetworkReply *res = qnam->get(QNetworkRequest(QUrl(URL)));

    connect(res, &QIODevice::readyRead,
            this, &network_manager::reply_finished);

    connect(res, &QNetworkReply::errorOccurred,
            this, &network_manager::network_error);

    connect(res, &QNetworkReply::sslErrors,
            this, &network_manager::ssl_error);

    return true;
}

void network_manager::reply_finished()
{
    printf("callback function\n");
}

void network_manager::network_error()
{
    printf("ERROR OCCURED\n");
}

void network_manager::ssl_error()
{
    printf("ssl error (?)\n");
}


