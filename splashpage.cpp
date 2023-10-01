#include "splashpage.h"
#include "./ui_splashpage.h"
#include <Windows.h>

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

    connect(
        ui->login_btn, &QPushButton::clicked,
        this, &SplashPage::login_clicked);

    connect(
        ui->signup_btn, &QPushButton::clicked,
        this, &SplashPage::signup_clicked);
}

SplashPage::~SplashPage()
{
    delete ui;
}

void SplashPage::login_clicked()
{
    printf("display login\n");
    ui->login_btn->setDisabled(true);
    this->change_to_page(LOGIN);
}

void SplashPage::signup_clicked()
{
    printf("display signup\n");
    ui->signup_btn->setDisabled(true);
    this->change_to_page(SIGNUP);
}

void SplashPage::change_to_page(PAGE_ID window)
{
    switch(window) {
    case SPLASH:
        break;

    case LOGIN:
        Sleep(500);
        ui->login_btn->hide();
        ui->signup_btn->hide();
        break;

    case SIGNUP:
        Sleep(500);
        ui->login_btn->hide();
        ui->signup_btn->hide();
        break;

    case MAIN_APPLICATION:
        break;

    }


}

