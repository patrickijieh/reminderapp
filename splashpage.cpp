#include <iostream>
#include "splashpage.h"
#include "./ui_splashpage.h"
#include "util.h"

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

    this->hide_login_form(true);
    this->hide_signup_form(true);

    connect(
        ui->login_btn, &QPushButton::clicked,
        this, &SplashPage::login_clicked);

    connect(
        ui->signup_btn, &QPushButton::clicked,
        this, &SplashPage::signup_clicked);

    connect(
        ui->login_confirm_btn, &QPushButton::clicked,
        this, &SplashPage::login_confirm_clicked);

    connect(
        ui->signup_confrim_btn, &QPushButton::clicked,
        this, &SplashPage::signup_confirm_clicked);
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

void SplashPage::login_confirm_clicked()
{
    printf("get login info\n");
    std::string username = ui->login_username->text().toStdString();
    std::string password = ui->login_password->text().toStdString();

    if (username == "Patrick" && password == "Ijieh")
    {
        this->hide_login_form(true);
    }
}

void SplashPage::signup_confirm_clicked()
{
    printf("get signup info\n");
    std::string username = ui->signup_username->text().toStdString();
    std::string password = ui->signup_password->text().toStdString();
    std::string confirmed_password = ui->signup_password_2->text().toStdString();
}

void SplashPage::change_to_page(PAGE_ID window)
{
    switch (window)
    {
    case SPLASH:
        break;

    case LOGIN:
        util::sleep(500);
        ui->login_btn->hide();
        ui->signup_btn->hide();
        this->hide_login_form(false);
        this->hide_signup_form(true);
        break;

    case SIGNUP:
        util::sleep(500);
        ui->login_btn->hide();
        ui->signup_btn->hide();
        this->hide_login_form(true);
        this->hide_signup_form(false);
        break;

    case MAIN_APPLICATION:
        break;
    }
}

void SplashPage::hide_login_form(bool hide)
{
    if (hide)
    {
        ui->login_username->hide();
        ui->login_password->hide();
        ui->login_confirm_btn->hide();
    }

    else
    {
        ui->login_username->show();
        ui->login_password->show();
        ui->login_confirm_btn->show();
    }
}

void SplashPage::hide_signup_form(bool hide)
{
    if (hide)
    {
        ui->signup_username->hide();
        ui->signup_password->hide();
        ui->signup_password_2->hide();
        ui->signup_confrim_btn->hide();
    }

    else
    {
        ui->signup_username->show();
        ui->signup_password->show();
        ui->signup_password_2->show();
        ui->signup_confrim_btn->show();
    }
}
