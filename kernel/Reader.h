
#ifndef READER_H
#define READER_H

#include "Common.h"
#include "GeometricalField.h"
#include "ReaderInterface.h"

namespace pnx {

class Reader
{
public:
    static GeometricalField* read(const QString& plugin_path,
                                  const QString& input_file_name,
                                  const double scale_factor);

};

}



#endif // READER_H
