# cpp_monitor 项目开发流程指引

## 项目简介

cpp_monitor 是一个用于监控服务器状态、物联网设备数据、或任何实时时间序列数据的 Web 仪表盘。  
- **后端**：采用 C++ 实现高性能 API 服务，处理海量实时数据。  
- **前端**：基于现代 Web 技术（如 Vue3/React + ECharts）实现实时数据可视化。  
- **AI 集成**：支持在数据流中实时分析、预测或异常检测。

---

## 技术架构

- **后端**：C++（推荐 Crow/Drogon/Restinio/Pistache 等现代 Web 框架）
- **数据库**：可选 SQLite/PostgreSQL/MySQL 或时序数据库（如 InfluxDB）
- **前端**：Vue3 或 React + ECharts
- **AI 算法**：C++ 内调用 ONNX Runtime 或通过 pybind11 调用 Python 模型
- **通信协议**：RESTful API（初期），可扩展支持 WebSocket 实时推送

---

## 开发环境准备

1. 安装 C++17/20 编译器（如 g++/clang）
2. 安装并配置 CMake
3. 安装依赖库（如 Crow/Drogon、spdlog、sqlite3/libpqxx、pybind11/ONNX Runtime 等）
4. Node.js & npm/yarn（用于前端开发）
5. Docker（可选，便于环境隔离与部署）

---

## 开发流程（推荐路线）

### 1. 明确需求与功能划分

- 数据采集/上报接口
- 数据存储
- API 查询接口
- 前端实时可视化界面
- AI 实时分析或异常检测

---

### 2. 后端 API 服务搭建

- 选型并初始化 Web 框架项目（如 Crow/Drogon）
- 实现基础 RESTful API（如 `/api/ping`、`/api/metrics`）
- 使用 Postman/curl 本地测试接口

---

### 3. 前端仪表盘原型开发

- 使用 Vue3 或 React 初始化前端项目
- 集成 ECharts，绘制静态或模拟数据图表
- 实现与后端 API 对接，拉取并展示实时数据

---

### 4. 数据持久化与流转

- 后端集成数据库（如 SQLite/PostgreSQL）
- 实现数据写入与查询接口（如 `/api/push_data`、`/api/query_data`）
- 前端定时上报/请求数据，完成动态刷新

---

### 5. 支持实时通信（可选）

- 后端集成 WebSocket 服务（可用 crow/drogon 自带模块或 uWebSockets）
- 前端通过 WebSocket 实时接收数据并刷新

---

### 6. AI/异常检测模块集成

- 后端集成 pybind11 或 ONNX Runtime
- 提供数据分析/预测接口（如 `/api/analyze`）
- 前端展示分析结果或异常告警

---

### 7. 项目部署与优化

- 使用 Docker 容器化后端与前端，便于部署和测试
- 编写部署和启动文档、环境变量说明

---

### 8. 持续迭代与完善

- 增加用户权限与认证功能
- 丰富数据可视化类型与交互
- 性能优化与高可用设计
- 自动化测试与 CI/CD 流程

---

## 参考资料

- [Crow C++ 微框架](https://github.com/CrowCpp/Crow)
- [Drogon Web 框架](https://github.com/drogonframework/drogon)
- [pybind11](https://github.com/pybind/pybind11)
- [ONNX Runtime](https://onnxruntime.ai/)
- [Vue3 官方文档](https://cn.vuejs.org/)
- [React 官方文档](https://react.dev/)
- [ECharts 文档](https://echarts.apache.org/zh/index.html)
- [Docker 官方文档](https://docs.docker.com/)

---

## 建议

- 优先实现最小可用产品（MVP），逐步完善功能
- 代码与文档同步维护，便于后续协作和推广
- 多关注 C++ 网络编程和现代 Web 前端相关社区
