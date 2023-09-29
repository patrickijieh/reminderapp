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

private:
    Ui::SplashPage *ui;
};
#endif // SPLASHPAGE_H
