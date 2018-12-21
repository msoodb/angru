#include "_log.h"

#include <boost/log/core/core.hpp>
#include <boost/log/expressions/formatters/date_time.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/trivial.hpp>
#include <boost/core/null_deleter.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#include <fstream>
#include <ostream>

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace sinks = boost::log::sinks;
namespace attrs = boost::log::attributes;
namespace keywords = boost::log::keywords;

BOOST_LOG_ATTRIBUTE_KEYWORD(line_id, "LineID", unsigned int)
BOOST_LOG_ATTRIBUTE_KEYWORD(timestamp, "TimeStamp", boost::posix_time::ptime)
BOOST_LOG_ATTRIBUTE_KEYWORD(severity, "Severity", logging::trivial::severity_level)

BOOST_LOG_GLOBAL_LOGGER_INIT(logger, src::severity_logger_mt) {
    src::severity_logger_mt<boost::log::trivial::severity_level> logger;

    // add attributes
    logger.add_attribute("LineID", attrs::counter<unsigned int>(1));     // lines are sequentially numbered
    logger.add_attribute("TimeStamp", attrs::local_clock());             // each log line gets a timestamp

    // get core
    boost::shared_ptr< logging::core > core = logging::core::get();

    // typedef a text and file sink
    typedef sinks::synchronous_sink <sinks::text_file_backend> file_sink;
    typedef sinks::synchronous_sink <sinks::text_ostream_backend> text_sink;

    // add a text and file sink
    boost::shared_ptr<text_sink> sink = boost::make_shared<text_sink>();
    boost::shared_ptr<file_sink> backend = boost::make_shared< file_sink >(
            keywords::file_name = LOGFILE,
            keywords::open_mode = std::ios_base::app|std::ios_base::out,
            keywords::rotation_size = 5 * 1024 * 1024,
            keywords::time_based_rotation = sinks::file::rotation_at_time_point(12, 0, 0));
    // add a logfile stream to our sink
    //sink->locked_backend()->add_stream(boost::make_shared<std::ofstream>(LOGFILE));

    // add "console" output stream to our sink
    //sink->locked_backend()->add_stream(boost::shared_ptr<std::ostream>(&std::clog, boost::null_deleter()));
    //backend->locked_backend()->add_stream(boost::shared_ptr<std::ostream>(&std::clog, boost::null_deleter()));


    // Enable auto-flushing after each log record written
    //sink->auto_flush(true);
    //backend->auto_flush(true);

    // specify the format of the log message
    logging::formatter formatter = expr::stream
        << std::setw(7) << std::setfill('0') << line_id << std::setfill(' ') << " | "
        << expr::format_date_time(timestamp, "%Y-%m-%d, %H:%M:%S.%f") << " "
        << "[" << logging::trivial::severity << "]"
        << " - " << expr::smessage;

    //sink->set_formatter(formatter);
    backend->set_formatter(formatter);

    // only messages with severity >= SEVERITY_THRESHOLD are written
    //sink->set_filter(severity >= SEVERITY_THRESHOLD);
    backend->set_filter(severity >= SEVERITY_THRESHOLD);


    // "register" our sink
    //core->add_sink(sink);
    core->add_sink(backend);
    return logger;
}
