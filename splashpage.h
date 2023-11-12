#ifndef SPLASHPAGE_H
#define SPLASHPAGE_H

#include <QMainWindow>
#include "util.h"

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
    void signup_clicked();
    void login_clicked();
    void login_confirm_clicked();
    void signup_confirm_clicked();
    void change_to_page(PAGE_ID window);
    void hide_login_form(bool hide);
    void hide_signup_form(bool hide);
    void back_clicked();

private:
    Ui::SplashPage *ui;
};
#endif // SPLASHPAGE_H
