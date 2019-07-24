#include "informationwidget.h"

#include <QVBoxLayout>
#include <QDebug>

InformationWidget::InformationWidget(QWidget *parent)
    : QWidget(parent)
    , m_infoLabel(new QLabel)
{
    m_infoLabel->setStyleSheet("QLabel {"
                               "color: white;"
                               "}");
    //m_infoLabel->setAlignment(Qt::AlignVCenter|Qt::AlignLeft);
    font.setFamily("Noto Mono");
	m_infoLabel->setFont(font);

    QVBoxLayout *centralLayout = new QVBoxLayout;
    centralLayout->addWidget(m_infoLabel);
    centralLayout->setSpacing(0);
    centralLayout->setMargin(0);

    setLayout(centralLayout);
}

void InformationWidget::UpdateData(const QString &cpu,const QString &mem,const QString &sbytes,const QString &rbytes)
{

    QString s_cpu = cpu;
    s_cpu.replace(QString("%"), QString(""));
    int i_cpu = s_cpu.toInt();

    QString s_mem = mem;
    s_mem.replace(QString("%"), QString(""));
    int i_mem = s_mem.toInt();

    if(i_cpu > 90 ||i_mem >90 ){
        m_infoLabel->setStyleSheet("QLabel {"
                               "color: red;"
                               "}");
    }
    else if(i_cpu > 75 ||i_mem >75 ){
        m_infoLabel->setStyleSheet("QLabel {"
                               "color: yellow;"
                               "}");
    }else{
        m_infoLabel->setStyleSheet("QLabel {"
                               "color: white;"
                               "}");
    }
    m_infoLabel->setText(QString("CPU: %1 ↑ %2/S\nMEM: %3 ↓ %4/S")
                         .arg(s_cpu).arg(sbytes)
                         .arg(mem).arg(rbytes));
    //m_infoLabel->adjustSize();
}

void InformationWidget::UpdateData(const QString &sbytes,const QString &rbytes)
{
    m_infoLabel->setText(QString(" %1/S\n %2/S")
                         .arg(sbytes)
                         .arg(rbytes));
}