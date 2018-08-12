#include "Common.h"

void mphs::Common::print_info(const QString &info, const bool isEndl)
{
    qDebug() << info;
    if (isEndl) {
        qDebug() << endl;
    }
}

QString mphs::Common::get_plugin_name_from_path(const QString &path, bool is_debug)
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

QString mphs::Common::get_root_dir(const AppName app_name)
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
            THROW_MPHSEXCEPTION_INFO(err.toStdString());
        }
    };

    switch(app_name)
    {
    case AppNameMulphys:
    {
        return get_app_root("MULPHYS");
    }
    default:
    {
        QString err;
        QTextStream ss(&err);
        ss << QObject::tr("The application name is not recognized ") << app_name;
        THROW_MPHSEXCEPTION_INFO(err.toStdString());
    }
    }
}

bool mphs::Common::is_debug_build()
{
    bool load_debug = true;
#if  defined( QT_DEBUG )
    load_debug = true;
#else
    load_debug = false;
#endif
    return load_debug;
}

const QString mphs::Common::get_plugin_dir()
{
//    QString plugin_dir;
//    if (is_debug_build())
//    {
//        plugin_dir = get_root_dir(AppNameMulphys) + "/components/Debug";
//    }
//    else
//    {
//        plugin_dir = get_installer_package_subdir("omnia") + "/data/plugins";
//    }
//    return plugin_dir;
    return mphs::Common::get_root_dir(AppNameMulphys) + "/components/Debug";
}

const QString mphs::Common::get_plugin_path(const QString &module_name)
{
    const QString plugin_dir = get_plugin_dir();
#if defined(Q_OS_WIN64) || defined(Q_OS_WIN32)
    QString module_file_path = plugin_dir + "/" + module_name + ".dll";
#elif defined(Q_OS_MAC) // for linux and mac use unsigned __int64
    QString module_file_path = omnia_dir + "/lib" + module_name + ".dylib";
#elif defined(Q_OS_LINUX)
    QString module_file_path = omnia_dir + "/lib" + module_name + ".so";
#else
#error Not one of WIN32,Win64,MACOSX,LINUX platform is used currently.
#endif
    QFileInfo qf(module_file_path);
    if (!qf.exists() || !qf.isFile())
    {
        QString err;
        QTextStream ss(&err);
        ss << QObject::tr("The module file path ")
           << module_file_path << QObject::tr(" does not exist.");
        THROW_MPHSEXCEPTION_INFO(err.toStdString());
    }
    return module_file_path;
}
