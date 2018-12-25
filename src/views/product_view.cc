#include "views/product_view.h"

#include <iostream>
#include <string>

#include <pqxx/pqxx>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "tools/system.h"
#include "tools/log.h"
#include "wrappers/postgresql.h"
#include "models/product_model.h"

namespace angru{
namespace mvc{
namespace view{

ProductView::ProductView(){}
ProductView::~ProductView(){}

} // view
} // mvc
} // angru
