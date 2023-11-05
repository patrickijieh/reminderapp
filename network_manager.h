#ifndef NETWORK_MANAGER_H
#define NETWORK_MANAGER_H
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

class network_manager : public QObject
{
public:
    network_manager();
    ~network_manager();
    bool get(const char* URL);

private:
    QNetworkAccessManager *qnam;

private slots:
    void reply_finished();
    void network_error();
    void ssl_error();
};

#endif // NETWORK_MANAGER_H
