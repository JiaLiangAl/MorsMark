#ifndef MORSAPP_H
#define MORSAPP_H
#include "MorsConfig.h"

/** ****************************************************************************
 * @brief The MorsApp class
 * Mors 应用程序类，继承自 QApplication，使用单例模式
 * 新添功能：
 *   + Mors 应用程序配置文件的读写
 *   + Mors 应用程序的全局选项
 *
 * ****************************************************************************/
class MorsApp: public QApplication
{
    Q_OBJECT
private: // private data member

    QHash<QString, QString> options_;
public: // ctor & dtor

    MorsApp(int & argc, char** argv);
    virtual ~MorsApp(void);

public: // option information

    //! 重设为默认设置
    void loadDefaultOption(void);

    //! 获取指定 key 的设置
    QString option(const QString& key) const;

    //! 设置指定 key 的设置值
    void setOption(const QString& key, const QString& val);

    //! 保存当前设置
    void saveOption(void) const;
};

/** ****************************************************************************
 * @brief qMorsApp
 * @return 返回 MorsApp 的单例指针
 *
 * ****************************************************************************/
inline MorsApp* qMorsApp(void) {
    return static_cast<MorsApp*>(QCoreApplication::instance());
}

#endif // MORSAPP_H
