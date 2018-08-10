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

    /*
     *
     *
     ** Returns a pointer to the (constant) error description.
     *  @return A pointer to a \c const \c char*. The underlying memory
     *          is in posession of the \c Exception object. Callers \a must
     *          not attempt to free the memory.
     *
     *
     *
     */
    virtual const char* what() const noexcept {
        return msg_.c_str();
    }

protected:
    std::string msg_;
};





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



};
}

#define THROW_PNXEXCEPTION_INFO(INFO)    \
{ \
    pnx::pnxExceptions excep(INFO, __LINE__, __FUNCTION__, __FILE__); \
    throw excep;\
}



#endif // COMMON_H
