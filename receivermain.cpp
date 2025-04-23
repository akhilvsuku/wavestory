#include "receivermain.h"
#include <filesystem>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>

namespace fs = std::filesystem;

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
    const auto& files = req.files;

    auto it = files.find("file");
    if (it != files.end()) {
        const auto& file = it->second;

        std::ofstream out("/app/" + file.filename, std::ios::binary);
        if (out.is_open()) {
            out << file.content;
            out.close();

            res.set_content("File uploaded successfully: " + file.filename, "text/plain");
        } else {
            res.status = 500;
            res.set_content("Failed to save file.", "text/plain");
        }
    } else {
        res.status = 400;
        res.set_content("No file found in the request.", "text/plain");
    }
	
    /*     
        fs::path currentPath = fs::current_path();  // Gets the working directory
        fs::path canonicalPath = fs::canonical(currentPath);  // Resolves symlinks etc.
    */
}


void receivermain::load_doc(const httplib::Request& req, httplib::Response& res)
{
    std::string str_path = "";
	
    if (req.has_param("filename")) {
        str_path = req.get_param_value("filename");
    }
    std::string file_path = "/app/" + str_path;  // Your actual file path

    if (!std::filesystem::exists(file_path)) {
        res.status = 404;
        res.set_content("File not found", "text/plain");
        return;
    }

    std::ifstream file(file_path, std::ios::binary);
    if (!file.is_open()) {
        res.status = 500;
        res.set_content("Failed to open file", "text/plain");
        return;
    }

    std::string file_content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    res.set_content(file_content, "application/octet-stream");
    res.set_header("Content-Disposition", "attachment; filename=\"" + str_path + "\"");
}


receivermain::~receivermain()
{
}
