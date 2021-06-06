#include "Data.h"

Data::Data()
{
    std::cout << "Validator constructor completed" << std::endl;
}

Data& Data::getInstance() {
    static Data  instance;
    return instance;
}


