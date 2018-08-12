#ifndef COMMON_H
#define COMMON_H

#include <QString>
#include <QFileInfo>
#include <QDebug>
#include <QPluginLoader>
#include <QMap>

#include <iostream>
#include <sstream>

#include <armadillo>

#ifndef _MSC_VER
#define NOEXCEPT noexcept
#else
#define NOEXCEPT
#endif

namespace pnx {

class pnxExceptions: public std::exception{
public:

    explicit pnxExceptions(const std::string& message,
                          const int line_number,
                          const std::string& function,
                          const std::string& file_name)
        : msg_(message)
    {
        std::stringstream ss;
        ss << line_number;
        msg_ = msg_
                + "\n at line: " + ss.str()
                + "\n in func: " + function
                + "\n in file: " + file_name;
    }

    /*
     *
     *
     ** Destructor.
     *
     *
     */
    virtual ~pnxExceptions(){}

protected:
    std::string msg_;
};

#define THROW_PNXEXCEPTION_INFO(INFO)    \
{ \
    pnx::pnxExceptions excep(INFO, __LINE__, __FUNCTION__, __FILE__); \
    throw excep;\
}




class Common
{
public:

    enum AppName {
        AppNamePanax
    };

    Common(){}

    static void print_info(const QString& info, const bool endl = true);

    static QString get_plugin_name_from_path(const QString& path, bool isDebug);

    static QString get_root_dir(const AppName app_name);

    static bool is_debug_build();


    ///
    /// plugin related static functions
    ///
    ///
    ///

    static const QString get_plugin_dir();
    static const QString get_plugin_path(const QString& module_name);

    template<typename InterfaceType, typename BaseType>
    static BaseType* get(const QString& plugin_name, QObject* parent) {

        const QString plugin_path = pnx::Common::get_plugin_path(plugin_name);
        QFileInfo qfi(plugin_path);
        if (qfi.exists() && qfi.isFile())
        {
            QPluginLoader loader(plugin_path);
            QObject * possiblePlugin = loader.instance();
            if(possiblePlugin)
            {
                InterfaceType* plugin = qobject_cast<InterfaceType*>(possiblePlugin);
                if(plugin)
                {
                    BaseType* ptr = plugin->create_plugin(parent);
                    return ptr;
                }
                else
                {
                    QString err;
                    QTextStream ss(&err);
                    ss <<  "Not a plugin: "<< loader.errorString();
                    THROW_PNXEXCEPTION_INFO(err.toStdString());
                }
            }
            else
            {
                QString err;
                QTextStream ss(&err);
                ss << QObject::tr("Failed to load plugin: `" )
                   << plugin_path
                   << QObject::tr("` Several reasons might cause this issue: ") << endl
                   << QObject::tr(" (1) Some pure virtual functions might not be implemented in plugin. ") << endl
                   << QObject::tr(" (2) The Plugins and its caller should build with the same build configuration (release/debug, except on Unix-like systems)") << endl
                   << QObject::tr(" (3) The Plugins and its caller should build with the same major version and minor/patch version equal or smaller than application minor/patch version of Qt") << endl
                   << QObject::tr(" (4) You can also set QT_DEBUG_PLUGINS=1 in the launch environment of the application to get more verbose debugging information about plugin loading.") << endl
                   << QObject::tr(" (5) If the caller used an old version of Qt dll/so/dynlib's (e.g. QtCore.dll, QtWidget) of old versions usually after an old Qt deployment, delete the old deployment and retry.") << endl
                   ;
                THROW_PNXEXCEPTION_INFO(err.toStdString());
            }
        }
        else
        {
            QString err;
            QTextStream ss(&err);
            ss <<  QObject::tr("Plugin ")<< plugin_path << QObject::tr(" not found. \n");
            ss << QObject::tr(" Representative problems:\n")
               << QObject::tr(" (1) The plugin is not registered before its dependant, the related plugin should be registered mannually if necessary. \n")
               << QObject::tr(" (2) The plugin is not generated before use, the user should make sure the proper built type (debug/release) is chosen.\n");
            THROW_PNXEXCEPTION_INFO(err.toStdString());
        }
    }



};
}




#endif // COMMON_H
