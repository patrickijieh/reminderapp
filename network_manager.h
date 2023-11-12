#ifndef NETWORK_MANAGER_H
#define NETWORK_MANAGER_H
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

class network_manager : public QObject
{
public:
    network_manager();
    ~network_manager();
    void get_user(std::string username, std::string pass);

private:
    QNetworkAccessManager *qnam;
    std::string network_response;
    bool get(const char* URL);

private slots:
    void reply_finished(QNetworkReply *reply);
    void network_error();
    void ssl_error();
};

#endif // NETWORK_MANAGER_H
