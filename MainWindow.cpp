#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    git_libgit2_init();
    settings = new QSettings("Savings");

    tray = new QSystemTrayIcon(this);

    tray->setIcon(QIcon(":/pic/Git-Icon.png"));
    tray->show();
    tray->setToolTip("Git client");
}

MainWindow::~MainWindow() {
    delete ui;
    delete settings;
    delete tray;
    git_libgit2_shutdown();
}

void MainWindow::show_notification(const QString& notification_header,
                                   const QString& notification_body) {
    tray->showMessage(notification_header,
                      notification_body, QIcon(":/pic/Git-Icon.png"), 3000);
}

void MainWindow::on_open_folder_btn_clicked() {
    folder_name = QFileDialog::getExistingDirectory(this, tr("Open folder"), "/home");

   if (!QDir::setCurrent(this->folder_name)) {
       show_notification("Oops!", "Could not change the current working directory");
   } else {
       settings->setValue("path", this->folder_name);
       ui->open_folder_btn->setText(this->folder_name);
   }
}

