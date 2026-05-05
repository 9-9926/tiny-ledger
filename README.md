# tiny-ledger
A simple command-line personal ledger in C / 纯C语言（数组）命令行个人记账本
# tiny-ledger

纯 C 语言命令行个人记账本。

## 功能
- 添加收支记录（金额、类型、备注）
- 显示所有记录
- 按序号删除记录
- 按序号修改记录
- 自动保存到 `ledger.txt`
- 启动时自动读取历史数据

## 编译运行
使用 Visual Studio 2026：
1. 新建空项目
2. 添加 `main.c`
3. Ctrl + F5 运行

## 技术点
- 结构体、数组、循环、条件判断
- 文件 IO：`fopen` / `fprintf` / `fscanf`
- 数据校验：类型检查、范围检查、空链表检查
