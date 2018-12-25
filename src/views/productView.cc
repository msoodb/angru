#include "views/productView.h"

#include <iostream>
#include <string>

#include <pqxx/pqxx>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "tools/_system.h"
#include "tools/_log.h"
#include "wrappers/_PostgreSQL.h"
#include "models/productModel.h"


ProductView::ProductView(){}
ProductView::~ProductView(){}
