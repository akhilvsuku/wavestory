#include "receivermain.h"

receivermain::receivermain()
{
}

void receivermain::receiver_controller()
{

    m_svr.Get("/hi", [this](const httplib::Request& req, httplib::Response& res) {
        process_hi( req, res);
        });


    m_svr.Get("/fetch_search", [this](const httplib::Request& req, httplib::Response& res) {
        fetch_search(req, res);
        });

    m_svr.Post("/singin_signup",
        [&](const httplib::Request& req, httplib::Response& res/*, const httplib::ContentReader& content_reader*/) {
            singin_signup(req, res);
        });


    m_svr.listen("0.0.0.0", 8080);
}

void receivermain::process_hi(const httplib::Request& req, httplib::Response& res)
{
    res.set_content("Hello World in function!", "text/plain");

}

void receivermain::singin_signup(const httplib::Request& req, httplib::Response& res)
{
    std::string str_uname = "";
    std::string str_pwrd = "";
    if (req.has_param("username")) {
        str_uname = req.get_param_value("username");
    }

    if (req.has_param("password")) {
        str_pwrd = req.get_param_value("password");
    }

    std::string str_resp = str_uname + str_pwrd;
    res.set_content(str_resp, "text/plain");
}

void receivermain::fetch_search(const httplib::Request& req, httplib::Response& res)
{
    std::string str_uname = "";
    std::string str_pwrd = "";
    if (req.has_param("username")) {
        str_uname = req.get_param_value("username");
    }

    if (req.has_param("password")) {
        str_pwrd = req.get_param_value("password");
    }

    std::string str_resp = str_uname + str_pwrd;
        res.set_content(str_resp, "text/plain");
}

void receivermain::fetch_search_update(const httplib::Request& req, httplib::Response& res)
{
}

void receivermain::manage_account(const httplib::Request& req, httplib::Response& res)
{
}

void receivermain::manage_payment(const httplib::Request& req, httplib::Response& res)
{
}

void receivermain::manage_booking(const httplib::Request& req, httplib::Response& res)
{
}

void receivermain::delete_account(const httplib::Request& req, httplib::Response& res)
{
}

receivermain::~receivermain()
{
}
