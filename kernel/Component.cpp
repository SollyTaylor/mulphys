#include "Component.h"


pnx::ComponentBase *pnx::Component::get(const QString &plugin_path)
{
    bool load_debug = true;
#if  defined( QT_DEBUG )
    load_debug = true;
#else
    load_debug = false;
#endif
    pnx::Common::print_info("plugin path:" + plugin_path);
    QFileInfo qfi(plugin_path);
    QString plugin_name = pnx::Common::get_plugin_name_from_path(plugin_path, load_debug);
    if (qfi.exists() && qfi.isFile())
    {
        QPluginLoader loader(plugin_path);
        QObject * possiblePlugin = loader.instance();
        if(possiblePlugin)
        {
            pnx::ComponentInterface* plugin =
                    qobject_cast<pnx::ComponentInterface*>(possiblePlugin);
            if(plugin){
//                qDebug() << "Plugin loaded!";
                pnx::ComponentBase* ptr = plugin->create_component();
                return ptr;
            }
            else
            {
                std::stringstream ss;
                THROW_PNXEXCEPTION_INFO("Failed to load plugin: " + plugin_path.toStdString());
            }
        }
        else
        {
            std::stringstream ss;
            ss << "  Typical Reasons not enumerated." << std::endl;
            pnx::Common::print_info(QString::fromStdString(ss.str()));
            THROW_PNXEXCEPTION_INFO("Failed to load plugin: " + plugin_path.toStdString());
        }
    }
    else
    {
        std::stringstream ss;
        ss << "Plugin " << plugin_path.toStdString() << " not found.\n"
           << " Typical reasons: \n"
           << " (1) The plugin is not registered before its dependant, the related plugin should be registered mannually if necessary. \n"
           << " (2) The plugin is not generated before use, the user should make sure the proper built type (debug/release) is chosen.\n";
        THROW_PNXEXCEPTION_INFO(ss.str());
    }
}
