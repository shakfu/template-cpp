#include <chrono>
#include <iostream>
#include <thread>

#include <args.hxx>
#include <cpp-terminal/base.hpp>
#include <cpr/cpr.h>
#include <indicators/indicators.hpp>
#include <pqxx/pqxx>
#include <sol/sol.hpp>
#include <spdlog/spdlog.h>
#include <taskflow/taskflow.hpp>
#include <toml.hpp>
#include <webview.h>
#include <xlsxwriter.h>
#include <zmq.hpp>

#include "core/process.hpp"
#include "db/store.hpp"
#include "model/vehicle.hpp"
#include "program.hpp"

#define SOL_ALL_SAFETIES_ON 1

int main(int argc, char *argv[])
{
    // options
    args::ArgumentParser parser("This the app main program.",
                                "This goes after the options.");
    args::HelpFlag help(parser, "help", "Display this help menu", {'h', "help"});
    args::CompletionFlag completion(parser, {"complete"});

    // optional file-based configuration (.toml)
    args::ValueFlag<std::string> config(parser, "config", "path to config file", {'c', "config"});


    args::Group group(
        parser, "This group is all exclusive:", args::Group::Validators::Xor);
    args::Flag demo(group, "demo", "run demo", {'d', "demo"});
    args::Flag task(group, "task", "run task", {'t', "task"});
    args::Flag web(group, "web", "view web", {'w', "web"});
    args::Flag msg(group, "msg", "run messaging demo", {'m', "msg"});
    args::Flag pg(group, "pg", "run postgres demo", {'p', "pg"});
    args::Flag bar(group, "bar", "run indicators demo", {'b', "bar"});
    args::Flag request(group, "request", "run cpr demo", {'r', "request"});
    args::Flag xlsx(group, "xlsx", "run xlsxwriter demo", {'x', "xlsx"});

    try
    {
        parser.ParseCLI(argc, argv);
    }
    catch (const args::Completion& e)
    {
        std::cout << e.what();
        return 0;
    }    
    catch (const args::Help&)
    {
        std::cout << parser;
        return 0;
    }
    catch (const args::ParseError& e)
    {
        spdlog::error("args::ParseError", e.what());
        std::cerr << parser;
        return 1;
    }
    catch (args::ValidationError e)
    {
        // std::cerr << e.what() << std::endl;
        std::cerr << parser;
        return 1;
    }

    if (config)
    {
        spdlog::info("loading confile file");
        try
        {
            auto cfg = toml::parse_file(args::get(config));
            std::string_view library_name = cfg["version"].value_or("0.0.0");
            cout << "Version: " << library_name << endl;
        }
        catch (toml::parse_error &e)
        {
            spdlog::error("toml::parse_file 'config.toml'", e.what());
        }

    }

    if (demo)
    {
        spdlog::info("Welcome to app::demo");
        std::string title = "Running " + color(Term::style::bold) + "Demo" +
                            color(Term::style::reset) + ".\n";
        cout << title << endl;

        // test classes
        model::Vehicle v;
        core::Process p;
        db::Store s;
        v.cost = 10.2;
        v.weight = 22.3;
        p.report(v);
        s.demo();

        // test lua wrapper 'sol'
        sol::state lua;
        lua.open_libraries(sol::lib::base, sol::lib::coroutine,
                           sol::lib::string, sol::lib::io);
        lua.script("print('bark bark bark!')");

        // test main
        program::foo();
    }
    if (task)
    {
        spdlog::info("Welcome to app::task");
        tf::Executor executor;
        tf::Taskflow taskflow("simple");

        auto [A, B, C, D] = taskflow.emplace(
            []() { std::cout << "TaskA\n"; }, []() { std::cout << "TaskB\n"; },
            []() { std::cout << "TaskC\n"; }, []() { std::cout << "TaskD\n"; });

        A.precede(B, C); // A runs before B and C
        D.succeed(B, C); // D runs after  B and C

        executor.run(taskflow).wait();
    }
    if (web)
    {
        spdlog::info("Welcome to app::web");
        webview::webview w(true, nullptr);
        w.set_title("app webview");
        w.set_size(480, 320, WEBVIEW_HINT_NONE);
        w.navigate("https://github.com/webview/webview");
        w.run();
    }
    if (msg)
    {
        spdlog::info("Welcome to app::msg");
        zmq::context_t ctx;
        zmq::socket_t sock(ctx, zmq::socket_type::push);
        sock.bind("inproc://test");
        sock.send(zmq::str_buffer("Hello, world"), zmq::send_flags::dontwait);
    }    
    if (pg)
    {
        spdlog::info("Welcome to app::pg");
        // Connect to the database.
        pqxx::connection c{"postgresql://sa@localhost/sa"};
        std::cout << "Connected to " << c.dbname() << '\n';
    }    
    if (bar)
    {
        spdlog::info("Welcome to app::bar");
        using namespace indicators;
        ProgressBar bar{
            option::BarWidth{50},
            option::Start{"["},
            // option::Fill{"="},
            // option::Lead{">"},
            option::Fill{"■"},
            option::Lead{"■"},
            option::Remainder{" "},
            option::End{"]"},
            option::PostfixText{"Extracting Archive"},
            option::ForegroundColor{Color::green},
            option::FontStyles{std::vector<FontStyle>{FontStyle::bold}}
        };
  
        // Update bar state
        while (true) {
            bar.tick();
            if (bar.is_completed())
                break;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
    if (request)
    {
        spdlog::info("Welcome to app::request");
        cpr::Response r = cpr::Get(cpr::Url{"https://python.org"});
        spdlog::info("status code: ", r.status_code);
        cout << r.text << endl;    
    }
    if (xlsx)
    {
        spdlog::info("Welcome to prolog::xlsx");
        lxw_workbook  *workbook  = workbook_new("demo.xlsx");
        lxw_worksheet *worksheet = workbook_add_worksheet(workbook, NULL);
        int row = 0;
        int col = 0;
        worksheet_write_string(worksheet, row, col, "Hello me!", NULL);
        workbook_close(workbook);
    }
    return 0;
}
