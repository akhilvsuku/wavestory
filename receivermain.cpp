#include "receivermain.h"
#include <filesystem>

namespace fs = std::filesystem;

std::string trav_print(std::string str_path) {
	std::string path = str_path; // current directory
	std::string str_out = ""; // current directory

    try {
        for (const auto& entry : fs::directory_iterator(path)) {
            if (fs::is_directory(entry.status())) {
                str_out += " -> " + entry.path().string();
            }
        }
    } catch (const fs::filesystem_error& e) {
        str_out += "Filesystem error: " + std::string(e.what());
    }
}

receivermain::receivermain()
{
}

void receivermain::receiver_controller()
{

    m_svr.Get("/version", [this](const httplib::Request& req, httplib::Response& res) {
        process_version( req, res);
        });


    m_svr.Get("/fetch_search", [this](const httplib::Request& req, httplib::Response& res) {
        fetch_search(req, res);
        });
		
		
    m_svr.Get("/save_doc", [this](const httplib::Request& req, httplib::Response& res) {
        save_doc(req, res);
        });

    m_svr.Post("/singin_signup",
        [&](const httplib::Request& req, httplib::Response& res/*, const httplib::ContentReader& content_reader*/) {
            singin_signup(req, res);
        });


    m_svr.listen("0.0.0.0", 8080);
}

void receivermain::process_version(const httplib::Request& req, httplib::Response& res)
{
    res.set_content("v1.0.02", "text/plain");

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


void receivermain::save_doc(const httplib::Request& req, httplib::Response& res)
{ 
    std::string str_doc = "";
    std::string str_path = "";
    if (req.has_param("doc")) {
        str_doc = req.get_param_value("doc");
    }
	
	
    if (req.has_param("find")) {
        str_path = req.get_param_value("find");
    }
	
	if(str_path != "") {
		std::string str_res = trav_print(str_path);
		res.set_content(str_res.c_str(), "text/plain");
	}
	else { 
		res.set_content("No path", "text/plain");
    }
}


void receivermain::load_doc(const httplib::Request& req, httplib::Response& res)
{
}


receivermain::~receivermain()
{
}
