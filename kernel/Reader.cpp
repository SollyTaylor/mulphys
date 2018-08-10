#include "Reader.h"

pnx::GeometricalField *pnx::Reader::read(const QString &plugin_path,
                                         const QString &input_file_name,
                                         const double scale_factor)
{
    QFileInfo qfi(plugin_path);
    if (qfi.exists() && qfi.isFile())
    {
        QPluginLoader loader(plugin_path);
        QObject * possiblePlugin = loader.instance();
        if(possiblePlugin)
        {
            pnx::ReaderInterface* plugin =
                    qobject_cast<pnx::ReaderInterface*>(possiblePlugin);
            if(plugin){
                plugin->load_geometrical_field_file(input_file_name, scale_factor);
                pnx::GeometricalField* ptr = plugin->create_geometrical_field();
                return ptr;
            }

            THROW_PNXEXCEPTION_INFO("Failed to load plugin: " + plugin_path.toStdString());

        }
        else
        {
            pnx::Common::print_info("Plugin: " + plugin_path + " not found.");
            THROW_PNXEXCEPTION_INFO("Failed to load plugin: " + plugin_path.toStdString());
        }
    }
    THROW_PNXEXCEPTION_INFO("Failed to load plugin: " + plugin_path.toStdString() + ", Plugin not exist.");
}
