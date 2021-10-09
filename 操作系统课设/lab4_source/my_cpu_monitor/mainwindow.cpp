#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QMessageBox>
#include <QDir>
#include <QListWidget>
#include <QListWidgetItem>
#include <QStringList>
#include <QTimer>
#include <QDateTime>
#include <QProcess>
#include <QPainter>
#include <QStringList>
#include <QTableWidgetItem>
#include <QtGui>
#include <QLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTimer*timer=new QTimer(this);          //init the timer
    connect( timer, SIGNAL( timeout() ), this, SLOT( timer_update_currentTabInfo() ) );     //insert timer which means update all the time
    timer_update_currentTabInfo();
    connect( timer, SIGNAL( timeout() ), this, SLOT( CpuUpdate() ) );
    get_info(1);
    get_info(0);
    connect( timer, SIGNAL( timeout() ), this, SLOT(on_MainWindow_tabifiedDockWidgetActivated() ) );

    timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timer_update_currentTabInfo(){
    QFile tempFile;
    QDateTime time;
    QString tempStr;
    int pos;
    ui->label_CurrentTime->setText(time.currentDateTime().toString("yyyy")+"."+\
                                   time.currentDateTime().toString("M")+"."+\
                                   time.currentDateTime().toString("d")+" "+\
                                   time.currentDateTime().toString("h")+":"+\
                                   time.currentDateTime().toString("m")+":"+\
                                   time.currentDateTime().toString("s"));           //get the current time


    tempFile.close(); //close stat file
    tempFile.setFileName("/proc/meminfo"); //open memory file
    if ( !tempFile.open(QIODevice::ReadOnly) )      //fail to open the file
    {
        QMessageBox::warning(this, tr("warning"), tr("The meminfo file can not open!"), QMessageBox::Yes);
        return ;
    }
    QString memTotal;       //show memory total
    QString memFree;        //show memory total free
    QString memUsed;        //show memory already used
    int nMemTotal, nMemFree, nMemUsed;

    while (1)
    {
        tempStr = tempFile.readLine();
        if ((pos = tempStr.indexOf("MemTotal"))!= -1)  //find the memtotal line
        {
            memTotal = tempStr.mid(pos+10, tempStr.length()-13);
            memTotal = memTotal.trimmed();
            nMemTotal = memTotal.toInt()/1024;
        }
        else if ((pos = tempStr.indexOf("MemFree")) != -1)  //find the memfree line
        {
            memFree = tempStr.mid(pos+9, tempStr.length()-12);
            memFree = memFree.trimmed();
            nMemFree = memFree.toInt()/1024;
            break;
        }
    }

    nMemUsed = nMemTotal - nMemFree;        //calculate the used memory

    memUsed = QString::number(nMemUsed, 10);    //tranlate into string
    memFree = QString::number(nMemFree, 10);
    memTotal = QString::number(nMemTotal, 10);

    ui->progressBar_RAM->setValue(nMemUsed*100/nMemTotal);

        struct sysinfo info;
        sysinfo(&info);
        struct tm *ptm=nullptr;
        ptm=gmtime(&info.uptime);
        char time_buf[30];
        sprintf(time_buf,"%02d:%02d:%02d",ptm->tm_hour,ptm->tm_min,ptm->tm_sec);
        ui->label_runningtime->setText(QString(time_buf));

    tempFile.close();
}



void MainWindow::get_info(int index){
    QString tempStr;
    QFile tempFile;
    int pos;
    if(index ==0){//SystemInfo
        //int ok;
        tempFile.setFileName("/proc/cpuinfo");
        if ( !tempFile.open(QIODevice::ReadOnly) )
        {
            QMessageBox::warning(this, tr("warning"), tr("The cpuinfo file can not open!"), QMessageBox::Yes);
            return;
        }
        char hostname[30];
        gethostname(hostname,30);
        ui->label_hostname->setText(hostname);

        struct sysinfo info;
        time_t cur_time=0;
        time_t boot_time=0;
        struct tm *ptm=nullptr;
        if(sysinfo(&info)) return;
        time(&cur_time);
        boot_time=cur_time-info.uptime;
        ptm=localtime(&boot_time);
        char boottime_buf[30];
        sprintf(boottime_buf,"%d.%d.%d %02d:%02d:%02d",ptm->tm_year+1900,ptm->tm_mon+1,ptm->tm_mday,
                ptm->tm_hour,ptm->tm_min,ptm->tm_sec);
        ui->label_boot_time->setText(QString(boottime_buf));


        //循环读取文件内容，查找需要的信息
        while (1)
        {
            tempStr = tempFile.readLine();
            if (pos = tempStr.indexOf("model name"), pos != -1)
            {
                pos += 12;
                QString *cpu_type = new QString( tempStr.mid(pos, tempStr.length()-12) );
                ui->label_CPUType->setText(*cpu_type);
                break;
            }
        }
        tempFile.close();


        tempFile.setFileName("/proc/version");
        if ( !tempFile.open(QIODevice::ReadOnly) )
        {
            QMessageBox::warning(this, tr("warning"), tr("The version file can not open!"), QMessageBox::Yes);
            return ;
        }
        tempStr = tempFile.readLine();

        int pos1 = tempStr.indexOf("(");
        QString *os_type = new QString( tempStr.mid(14, pos1-pos-2) );
        ui->label_SystemVersion->setText(*os_type);

        tempFile.close();
    }

    else if(index==1){//ProgInfo
        ui->listWidget_process->clear();
        QDir qd("/proc");
        QStringList qsList = qd.entryList();
        QString qs = qsList.join("\n");
        QString id_of_pro;
        bool ok;
        int find_start = 3;
        int a, b;
        int nProPid;
        QString proName;
        QString proState;
        QString proPri;
        QString proMem;
        QListWidgetItem *title = new QListWidgetItem("PID\t" + QString::fromUtf8("名称") + "\t\t\t\t" +
                                                     QString::fromUtf8("PPID") + "\t" +
                                                     QString::fromUtf8("优先级") + "\t" +
                                                     QString::fromUtf8("占用内存"), ui->listWidget_process);
        //循环读取进程
        while (1)
        {
            //获取进程PID
            a = qs.indexOf("\n", find_start);
            b = qs.indexOf("\n", a+1);
            find_start = b;
            id_of_pro = qs.mid(a+1, b-a-1);
            nProPid = id_of_pro.toInt(&ok, 10);
            if(!ok)
            {
                break;
            }

            //打开PID所对应的进程状态文件
            tempFile.setFileName("/proc/" + id_of_pro + "/stat");
            if ( !tempFile.open(QIODevice::ReadOnly) )
            {
                QMessageBox::warning(this, tr("warning"), tr("The pid stat file can not open!"), QMessageBox::Yes);
                return;
            }
            tempStr = tempFile.readLine();
            if (tempStr.length() == 0)
            {
                break;
            }
            a = tempStr.indexOf("(");
            b = tempStr.indexOf(")");
            proName = tempStr.mid(a+1, b-a-1);
            proName.trimmed();
            proName.split("\t");
            proState = tempStr.section(" ", 3, 3);
            proPri = tempStr.section(" ", 17, 17);
            proMem = tempStr.section(" ", 22, 22);


            if (proName.length() >= 30)
            {
                QListWidgetItem *item = new QListWidgetItem(id_of_pro + "\t" +
                                                            proName + "\t\t\t" +
                                                            proState + "\t" +
                                                            proPri + "\t" +
                                                            proMem, ui->listWidget_process);
            }
            else
            {
                QListWidgetItem *item = new QListWidgetItem(id_of_pro + "\t" +
                                                            proName + "\t\t\t\t" +
                                                            proState + "\t" +
                                                            proPri + "\t" +
                                                            proMem, ui->listWidget_process);
            }

            tempFile.close();
        }

        tempFile.close(); //关闭该PID进程的状态文件


    }
}




void MainWindow::get_pid_table(){
    QProcess process;
    process.start("ps -ax");
    process.waitForFinished();
    QString str=process.readLine();



}



void MainWindow::CpuUpdate()
{
    QProcess process;
    process.start("cat /proc/stat");        //get the cpu ratio


    process.waitForFinished();              //wait until the process is over
    QString str = process.readLine();       //read from the /proc/stat
    str.replace("\n","");
    str.replace(QRegExp("( ){1,}")," ");
    auto lst = str.split(" ");
    if(lst.size() > 3)
    {
        double use = lst[1].toDouble() + lst[2].toDouble() + lst[3].toDouble();
        double total = 0;
        for(int i = 1;i < lst.size();++i)
            total += lst[i].toDouble();
        if(total - m_cpu_total > 0)
        {
            for(int i=99;i>0;i--){
                usage[i]=usage[i-1];
            }
            usage[0] = (use - m_cpu_used) / (total - m_cpu_total) * 100.0;
            ui->cpu_rate->setText(QString::number(usage[0], '.', 2)+"%");
            //qDebug("cpu usage:%.2lf%%",(use - m_cpu_use__) / (total - m_cpu_total__) * 100.0);
            m_cpu_total = total;
            m_cpu_used = use;
        }
    }
    process.close();
}


void MainWindow::initchart(){

}

void MainWindow::on_MainWindow_tabifiedDockWidgetActivated()
{
           QLineSeries *series = new QLineSeries();
           for(int i=0;i<60;i++){
               series->append(i,usage[i]);
           }

           QChart *chart = new QChart();
           chart->legend()->hide();
           chart->addSeries(series);
           chart->createDefaultAxes();
           chart->setTitle("CPU ratio");

           QValueAxis *axisX = new QValueAxis();
           axisX->setRange(0, 50);

           chart->setAxisX(axisX);

           series->attachAxis(axisX);
           ui->cpu_chart->setChart(chart);
           ui->cpu_chart->setRenderHint(QPainter::Antialiasing);
}


void MainWindow::on_pushButton_clicked()
{
    system("shutdown -h now");
}



void MainWindow::on_pushButton_2_clicked()
{

    if(!ui->lineEdit->text().isEmpty())
       {
           QProcess process;

           process.start("kill "+ui->lineEdit->text());
           while (process.waitForFinished());
           QString q=process.readAll();
           process.kill();
       }
}
