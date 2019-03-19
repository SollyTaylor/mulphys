#ifndef COMMON_H
#define COMMON_H

#include <QObject>
#include <QString>
#include <QFileInfo>
#include <QDebug>
#include <QPluginLoader>

// containers
#include <QMap>
#include <QList>

// Json related data
#include <QJsonObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonParseError>

#include "rapidjson/filereadstream.h"
#include "rapidjson/document.h"
#include "rapidjson/schema.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/error/en.h"

// IO
#include <QFile>
#include <iostream>
#include <sstream>

#include <armadillo>

#ifndef _MSC_VER
#define NOEXCEPT noexcept
#else
#define NOEXCEPT
#endif

typedef QMap<QString, QList<quint8>> SectionIndices;

typedef QString FieldKey; // i.e.: processor:variable

namespace mphs {

enum FieldLocation {
    UndefinedLocation = 0,
    REDUCED,
    VERTEX_MAPPED,
    FACE_MAPPED,
    CELL_MAPPED
};

enum FieldDataType {
    UndefinedDataType = 0,
    Scalar,
    DoubleVector,
    IntVector,
    UintVector,
    DoubleMatrix,
    IntMatrix,
    UintMatrix
};

enum FieldIOType {
    UndefinedIOType = 0,
    State,  // in processor
    Input,  // in processor
    Output, // in processor
    InputOutput // in geometrical field
};







class mphsExceptions: public std::exception{
public:

    explicit mphsExceptions(const std::string& message,
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
    virtual ~mphsExceptions(){}

protected:
    std::string msg_;
};

#define THROW_MPHSEXCEPTION_INFO(INFO)    \
{ \
    mphs::mphsExceptions excep(INFO, __LINE__, __FUNCTION__, __FILE__); \
    throw excep;\
}


class Common
{
public:

    enum AppName {
        AppNameMulphys
    };

    Common(){}

    static void print_info(const QString& info, const bool endl = true);

    static QString get_plugin_name_from_path(const QString& path, bool isDebug);

    static QString get_root_dir(const AppName app_name);

    static bool is_debug_build();

    ///
    /// json related static functions
    ///
    static QJsonDocument read_json_file(const QString& path);
    static QJsonObject read_json_file_object(const QString& path);
    static void write_json_file_object(const QString& path, QJsonObject obj);
    static void check_json_schema(const QJsonDocument& json,
                                  const QJsonDocument& jsonSchema);

    static void check_json_schema(const QJsonObject& json,
                                  const QJsonObject& jsonSchema);

    static void check_json_schema(const QJsonArray& json,
                                  const QJsonObject& jsonSchema);

    static void check_json_schema(const QString& json,
                                  const QString& jsonSchema);

private:
    static void check_json_schema(const std::string& json,
                                  const std::string& jsonSchema);
public:
    ///
    ///
    ///
    /// plugin related static functions
    ///
    ///
    ///

    static const QString get_plugin_dir();
    static const QString get_plugin_path(const QString& module_name);
    static const QString get_plugin_json_path(const QString& module_name);
    static void check_is_json_object(const QJsonObject& jv, const QString& key = "");

    template<typename InterfaceType, typename BaseType>
    static BaseType* get(const QString& plugin_name, QObject* parent) {

        const QString plugin_path = mphs::Common::get_plugin_path(plugin_name);
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
                    THROW_MPHSEXCEPTION_INFO(err.toStdString());
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
                THROW_MPHSEXCEPTION_INFO(err.toStdString());
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
            THROW_MPHSEXCEPTION_INFO(err.toStdString());
        }
    }



};
}




#endif // COMMON_H
