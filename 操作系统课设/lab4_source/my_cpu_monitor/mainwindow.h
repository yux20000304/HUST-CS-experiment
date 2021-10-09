#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <unistd.h>
#include <QTimer>
#include <sys/sysinfo.h>
#include <QObject>
#include <QProcess>
#include <QDebug>
#include <QWidget>
#include <QList>
#include <QChartView>
#include <QSplineSeries>
#include <QtCore/QTimer>
#include <QList>
#include <QPushButton>
#include "chart.h"
#include <QChart>
#include <QtCharts/QtCharts>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QList<float> yList;     //list for
    QList<float> yList1;    //list for

private slots:
    void timer_update_currentTabInfo();
    void CpuUpdate();
    void get_info(int index);       //show the information
    void get_pid_table();
    void initchart();

    void on_MainWindow_tabifiedDockWidgetActivated();

    void on_pushButton_clicked();


    void on_pushButton_2_clicked();

public slots:


private:
    QString host_name;
    QString boot_time;
    QString run_time;
    QString kernel_version;
    QString cpu_version;
    int pid_num;

    double usage[100];
    double m_cpu_total = 0;
    double m_cpu_used = 0;

    int max_count;

    QTimer m_timer;
    QPushButton *button ;

    bool start;
    QList<int>  data;
    QSplineSeries *series;
    QChart chart;
    QChartView *chartView;
    int count;

};
#endif // MAINWINDOW_H
