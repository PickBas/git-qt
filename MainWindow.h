#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QSettings>
#include <QSystemTrayIcon>
#include <git2.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void show_notification(const QString& notification_header,const QString& notification_body);
    ~MainWindow();

private slots:

    void on_open_folder_btn_clicked();

private:
    Ui::MainWindow *ui;
    QSettings* settings;
    QSystemTrayIcon* tray;
    QString working_dir;
    git_repository *repo;
};
#endif // MAINWINDOW_H
