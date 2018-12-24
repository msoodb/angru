#include "productView.h"

#include <iostream>
#include <string>

#include <pqxx/pqxx>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "_error.h"
#include "_log.h"
#include "_PostgreSQL.h"
#include "productModel.h"


ProductView::ProductView(){}
ProductView::~ProductView(){}
