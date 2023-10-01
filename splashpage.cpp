#include "splashpage.h"
#include "./ui_splashpage.h"

SplashPage::SplashPage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SplashPage)
{
    QString windowTitle("QuickRemind");
    QString iconPath(":/resources/windowIcon.ico");

    QIcon appIcon(iconPath);

    ui->setupUi(this);
    this->setWindowTitle(windowTitle);
    this->setWindowIcon(appIcon);
}

SplashPage::~SplashPage()
{
    delete ui;
}

void SplashPage::on_signup_clicked()
{
    printf("Hello World!\n");
}

void SplashPage::on_login_clicked()
{
    printf("clicked login!\n");
}
