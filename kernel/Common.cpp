#include "Common.h"

void pnx::Common::print_info(const QString &info, const bool isEndl)
{
    qDebug() << info;
    if (isEndl) {
        qDebug() << endl;
    }
}

QString pnx::Common::get_plugin_name_from_path(const QString &path, bool is_debug)
{
    QString qpath(path);
    QFile f(qpath);
    QFileInfo fileInfo(f.fileName());
    QString filename(fileInfo.completeBaseName());
#if defined(Q_OS_WIN32)
    {}
#elif defined(Q_OS_MAC)
    filename.remove(0,3); // remove the initial "lib" in name libtsp_xxx_xxx
#elif defined(Q_OS_LINUX)
    filename.remove(0,3); // remove the initial "lib" in name libtsp_xxx_xxx
#endif
    if (is_debug)
    {
        int qstrsz = filename.size();
        filename.remove(qstrsz-2,2);
    }
    return filename;
}

QString pnx::Common::get_root_dir(const AppName app_name)
{
    auto get_app_root = [](const QString& app_name)
    {
        QString root_env = QString(app_name).append("_ROOT");
#if defined(QT_DEBUG)
        QString root_dir = qgetenv(root_env.toStdString().c_str()).constData();
#else
        QString root_dir = qgetenv(root_env.toStdString().c_str()).constData();
        if (root_dir == "" || !QDir(root_dir).exists()) {
            root_dir = qApp->applicationDirPath();
        }
#endif


        if (root_dir != "")
        {
            return root_dir;
        }
        else
        {
            QString err;
            QTextStream ss(&err);
            ss << QObject::tr("The installation path is corrupted: ") << root_dir;
            THROW_PNXEXCEPTION_INFO(err.toStdString());
        }
    };

    switch(app_name)
    {
    case AppNamePanax:
    {
        return get_app_root("STRUX");
    }
    default:
    {
        QString err;
        QTextStream ss(&err);
        ss << QObject::tr("The application name is not recognized ") << app_name;
        THROW_PNXEXCEPTION_INFO(err.toStdString());
    }
    }
}
