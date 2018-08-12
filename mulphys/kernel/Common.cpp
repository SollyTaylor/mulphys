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

QJsonDocument mphs::Common::read_json_file(const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
    {
        QString err =
                QObject::tr("Failed to open json file ")
                + "("+ path + ")";
        THROW_MPHSEXCEPTION_INFO(err.toStdString());
    }
    QByteArray qba = file.readAll();
    QJsonParseError error;
    QJsonDocument document = QJsonDocument::fromJson(qba, &error);
    if (error.error != QJsonParseError::NoError)
    {
        int char_offset = error.offset;
        QByteArray qba_left = qba.left(char_offset);
        int row = qba_left.count("\n");
        int offset = char_offset - qba_left.lastIndexOf("\n");
        QString err =
                error.errorString()
                + "\n @row: " + QString::number(row) +
                + "\n @offset: " + QString::number(offset);
        THROW_MPHSEXCEPTION_INFO(err.toStdString());
    }
    return document;
}

QJsonObject mphs::Common::read_json_file_object(const QString &path)
{
    QJsonDocument doc = read_json_file(path);
    if (!doc.isObject())
    {
        QString s;
        QTextStream ss(&s);
        ss << QObject::tr("The document is not an legal object when reading version.json.");
        THROW_MPHSEXCEPTION_INFO(s.toStdString());
    }
    return doc.object();
}

void mphs::Common::write_json_file_object(const QString &path, QJsonObject obj)
{
    QJsonDocument doc;
    doc.setObject(obj);
    QFile file(path);
    if (file.open(QFile::WriteOnly))
    {
        file.write(doc.toJson());
    }
}

void mphs::Common::check_json_schema(const QJsonDocument &json, const QJsonDocument &jsonSchema)
{
    std::string json_str(json.toJson().toStdString());
    std::string json_schema_str(jsonSchema.toJson().toStdString());
    check_json_schema(json_str, json_schema_str);
}

void mphs::Common::check_json_schema(const QJsonObject &json, const QJsonObject &jsonSchema)
{
    QJsonDocument json_doc, json_schema_doc;
    json_doc.setObject(json);
    json_schema_doc.setObject(jsonSchema);
    check_json_schema(json_doc,
                      json_schema_doc);
}

void mphs::Common::check_json_schema(const QJsonArray &json, const QJsonObject &jsonSchema)
{
    QJsonDocument json_doc, json_schema_doc;
    json_doc.setArray(json);
    json_schema_doc.setObject(jsonSchema);
    check_json_schema(json_doc,
                      json_schema_doc);
}

void mphs::Common::check_json_schema(const QString &json, const QString &jsonSchema)
{
    check_json_schema(json.toStdString(),
                      jsonSchema.toStdString());
}

void mphs::Common::check_json_schema(const std::string &json, const std::string &jsonSchema)
{
    // build json document
    const char* inputJson_cstr = json.c_str();
    rapidjson::StringStream ss_json(inputJson_cstr);

    rapidjson::Document d;
    if (d.ParseStream(ss_json).HasParseError()) {
        QString err;
        QTextStream serr(&err);
        serr << QObject::tr("\nError(offset ")
             << QString::number(static_cast<unsigned>(d.GetErrorOffset()))
             << "): "
             << QString::fromStdString(GetParseError_En(d.GetParseError()))
             << "\n"
             << QObject::tr("The input json is not a valid JSON. ");
        THROW_MPHSEXCEPTION_INFO(err.toStdString());
    }

    // build json schema document
    const char* schemaJson_cstr = jsonSchema.c_str();
    rapidjson::StringStream ss_json_schema(schemaJson_cstr);
    rapidjson::Document sd;
    if (sd.ParseStream(ss_json_schema).HasParseError()) {
        QString err;
        QTextStream serr(&err);
        serr << QObject::tr("\nError(offset ")
             << QString::number(static_cast<unsigned>(sd.GetErrorOffset()))
             << "): "
             << QString::fromStdString(GetParseError_En(sd.GetParseError()))
             << "\n"
             << QObject::tr("The input json schema is not a valid JSON. ");
        THROW_MPHSEXCEPTION_INFO(err.toStdString());
    }
    rapidjson::SchemaDocument schema(sd);
    rapidjson::SchemaValidator validator(schema);

    if (!d.Accept(validator)) {
        // Input JSON is invalid according to the schema
        // Output diagnostic information
        rapidjson::StringBuffer sb;
        validator.GetInvalidSchemaPointer().StringifyUriFragment(sb);

        printf("Invalid schema: %s\n", sb.GetString());
        QString invalid_schema_qstr(sb.GetString());

        printf("Invalid keyword: %s\n", validator.GetInvalidSchemaKeyword());
        QString invalid_keyword_qstr(validator.GetInvalidSchemaKeyword());

        sb.Clear();
        validator.GetInvalidDocumentPointer().StringifyUriFragment(sb);
        printf("Invalid document: %s\n", sb.GetString());
        QString invalid_document_qstr(sb.GetString());

        QString err;
        QTextStream serr(&err);
        serr << QObject::tr("Invalid Schema:   ") << invalid_schema_qstr << "\n";
        serr << QObject::tr("Invalid keyword:  ") << invalid_keyword_qstr << "\n";
        serr << QObject::tr("Invalid document: ") << invalid_document_qstr << "\n";
        THROW_MPHSEXCEPTION_INFO(err.toStdString());
    }
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

const QString mphs::Common::get_plugin_json_path(const QString &module_name)
{
    const QString omnia_dir = get_plugin_dir();
    const QString omnia_json_path = omnia_dir + "/" + module_name + ".json";
    QFileInfo qf(omnia_json_path);
    if (!qf.exists() || !qf.isFile())
    {
        QString err;
        QTextStream ss(&err);
        ss << QObject::tr("The module json file path ")
           << omnia_json_path << QObject::tr(" does not exist.");
        THROW_MPHSEXCEPTION_INFO(err.toStdString());
    }
    return omnia_json_path;
}

void mphs::Common::check_is_json_object(const QJsonObject &jv, const QString &key)
{
    if (jv.contains(key) && jv[key].isObject()) {
        return;
    }
    else {
        QString err = QObject::tr("The key (") + key + QObject::tr(") is not found or not object.");
        THROW_MPHSEXCEPTION_INFO(err.toStdString());
    }
}
