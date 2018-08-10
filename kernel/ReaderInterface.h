#ifndef READERINTERFACE_H
#define READERINTERFACE_H

#include "Common.h"
#include "GeometricalField.h"

namespace pnx {

class ReaderInterface {
public:
    virtual pnx::GeometricalField* create_geometrical_field() = 0;

    inline virtual void load_geometrical_field_file(const QString& input_file_name,
                                                    const double scale_factor)
    {
        Q_UNUSED(input_file_name)
        Q_UNUSED(scale_factor)
        std::stringstream ss;
        ss << "The geometrical field reader not implemented in current reader.";
        THROW_PNXEXCEPTION_INFO(ss.str());
    }

    virtual ~ReaderInterface(){}
};
}

Q_DECLARE_INTERFACE(pnx::ReaderInterface, "pnx.reader.interface")

#endif // READERINTERFACE_H
