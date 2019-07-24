#ifndef HOMEMONITORPLUGIN_H
#define HOMEMONITORPLUGIN_H

#include "informationwidget.h"
#include <string.h>
#include <QObject>
#include <QTimer>
#include <dde-dock/pluginsiteminterface.h>

class SysMonitorPlugin : public QObject, PluginsItemInterface
{
    Q_OBJECT
    Q_INTERFACES(PluginsItemInterface)
    Q_PLUGIN_METADATA(IID "com.deepin.dock.PluginsItemInterface" FILE "sys_monitor.json")

public:
    explicit SysMonitorPlugin(QObject *parent = nullptr);

    const QString pluginDisplayName() const override;
    const QString pluginName() const override;
    void init(PluginProxyInterface *proxyInter) override;

    QWidget *itemWidget(const QString &itemKey) override;
    QWidget *itemTipsWidget(const QString &itemKey) override;
    QWidget *itemPopupApplet(const QString &itemKey) override;

    bool pluginIsAllowDisable() override;
    bool pluginIsDisable() override;
    void pluginStateSwitched() override;

    const QString itemContextMenu(const QString &itemKey) override;
    void invokedMenuItem(const QString &itemKey, const QString &menuId, const bool checked) override;
	void displayModeChanged(const Dock::DisplayMode displayMode) override;

	const QString toHumanRead(unsigned long l,const char *unit,int digit);
private slots:
    // 用于更新数据的槽函数
    void refreshInfo();
private:
    //CPU工作时间除以总时间,内存百分比,交换区百分比
    int cpuPercent,memPercent,swapPercent;
	QString strcpu,strmem,strswap;
    // 获取cpu总时间,获取cpu工作时间
    unsigned long long totaltime,worktime;
	//保存上一次结果
    unsigned long long oldtotaltime,oldworktime;
	//cpu的各种时间变量
	unsigned long long user, nice, system, idle;
    unsigned long long iowait, irq, softirq, steal, guest, guestnice;
	//字符数组保存文件内容
	char buffer[1024];
	//文件描述符
	FILE* fp;
	//总内存，可用内存
	unsigned long totalmem,availablemem,tmp,totalswap,freeswap;
	//接收字节数，发送字节数
	unsigned long rbytes,sbytes,oldrbytes,oldsbytes,tmpr,tmps;
	char devname[1024];
	QString s,r;
	// 字体
	QFont font;
	//显示模式
	Dock::DisplayMode dismode;

private:
    // 处理时间间隔的计时器
    QTimer *m_refreshTimer;
    InformationWidget *m_pluginWidget;
    QLabel *m_tipsWidget;
    QLabel *m_appletWidget;
};

#endif // HOMEMONITORPLUGIN_H
