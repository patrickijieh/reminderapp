#ifndef SPLASHPAGE_H
#define SPLASHPAGE_H

#include <QMainWindow>
#include "window_identifiers.h"

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
    void change_to_page(PAGE_ID window);
    void hide_login_form(bool hide);

private:
    Ui::SplashPage *ui;
};
#endif // SPLASHPAGE_H
