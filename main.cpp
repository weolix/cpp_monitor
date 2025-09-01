#include <iostream>
#include <ctime>
#include "crow.h"


auto kb_to_gb_str = [](long kb) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << (kb / 1048576.0);
    return oss.str();
};


int main()
{
    crow::SimpleApp app;

    // 健康检查接口
    CROW_ROUTE(app, "/api/ping")
    ([](){
        return crow::response(200, "xxr pong");
    });

    // 版本信息接口
    CROW_ROUTE(app, "/api/version")
    ([](){
        crow::json::wvalue x;
        x["version"] = "0.1.0";
        x["desc"] = "cpp_monitor backend demo";
        return x;
    });

    // 服务器时间接口
    CROW_ROUTE(app, "/api/time")
    ([](){
        std::time_t now = std::time(nullptr);
        std::string time_str = std::ctime(&now);
        return crow::response(200, time_str);
    });

    // 服务器状态接口
    CROW_ROUTE(app, "/api/status")
    ([](){
        // 获取CPU使用率
        std::ifstream stat_file("/proc/stat");
        std::string line;
        std::getline(stat_file, line);
        std::istringstream ss(line);
        std::string cpu;
        long user, nice, system, idle;
        ss >> cpu >> user >> nice >> system >> idle;
        long total = user + nice + system + idle;
        double cpu_usage = 0.0;
        if (total > 0) {
            cpu_usage = 100.0 * (user + nice + system) / total;
        }

        // 获取内存信息
        std::ifstream mem_file("/proc/meminfo");
        long mem_total = 0, mem_free = 0, mem_available = 0;
        std::string key;
        while (mem_file >> key) {
            if (key == "MemTotal:") mem_file >> mem_total;
            else if (key == "MemFree:") mem_file >> mem_free;
            else if (key == "MemAvailable:") { mem_file >> mem_available; break; }
            mem_file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        std::ostringstream cpu_oss;
        cpu_oss << std::fixed << std::setprecision(2) << cpu_usage;

        crow::json::wvalue x;
        x["cpu"] = cpu_oss.str();
        x["mem_total_gb"] = kb_to_gb_str(mem_total);
        x["mem_free_gb"] = kb_to_gb_str(mem_free);
        x["mem_avail_gb"] = kb_to_gb_str(mem_available);
        return x;
    });

    // GPU 信息接口
    CROW_ROUTE(app, "/api/gpu")
    ([](){
        std::vector<crow::json::wvalue> gpus;
        FILE* fp = popen("nvidia-smi --query-gpu=name,utilization.gpu,memory.total,memory.used --format=csv,noheader,nounits", "r");
        if (!fp) {
            crow::json::wvalue x;
            x["error"] = "nvidia-smi not found or no GPU present";
            return x;
        }
        char buf[256];
        while (fgets(buf, sizeof(buf), fp)) {
            std::istringstream iss(buf);
            std::string name, util, mem_total, mem_used;
            std::getline(iss, name, ',');
            std::getline(iss, util, ',');
            std::getline(iss, mem_total, ',');
            std::getline(iss, mem_used, ',');
            crow::json::wvalue gpu;
            gpu["name"] = name;
            gpu["utilization_percent"] = util;
            gpu["memory_total_mb"] = mem_total;
            gpu["memory_used_mb"] = mem_used;
            gpus.push_back(std::move(gpu));
        }
        pclose(fp);
        crow::json::wvalue result;
        result["gpus"] = std::move(gpus);
        return result;
    });

    app.port(18080).multithreaded().run();
    return 0;
}