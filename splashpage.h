#ifndef SPLASHPAGE_H
#define SPLASHPAGE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class SplashPage; }
QT_END_NAMESPACE

class SplashPage : public QMainWindow
{
    Q_OBJECT

public:
    SplashPage(QWidget *parent = nullptr);
    ~SplashPage();

private slots:
    void on_signup_clicked();
    void on_login_clicked();

private:
    Ui::SplashPage *ui;
};
#endif // SPLASHPAGE_H
