#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QFileDialog>
#include <QDir>

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

    git_repository_free(repo);
    git_libgit2_shutdown();
}

void MainWindow::show_notification(const QString& notification_header,
                                   const QString& notification_body) {
    tray->showMessage(notification_header,
                      notification_body,
                      QIcon(":/pic/Git-Icon.png"),
                      3000);
}

void MainWindow::on_open_folder_btn_clicked() {
    working_dir = QFileDialog::getExistingDirectory(this,
                                                    tr("Open folder"),
                                                    "/home");

   if (!QDir::setCurrent(working_dir)) {
       show_notification("Oops!",
                         "Could not change the current working directory");
       return;
   }

   settings->setValue("path", working_dir);
   ui->floder_path_label->setText(working_dir);

   if (git_repository_open(&repo, working_dir.toStdString().c_str())) {
       show_notification("Warning!",
                         "Cannot find .git");
   }


}

