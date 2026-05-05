/*
 * tiny-ledger
 * 一个纯 C 语言写的命令行个人记账本
 * 功能：添加、显示、删除、修改、文件保存/读取
 * 编译：Visual Studio 2026 / GCC
 * 作者：大学菜鸟练习用
 * 日期：2026-04-21
 */

#define _CRT_SECURE_NO_WARNINGS   // 关闭 VS 安全检查，使用标准 scanf
#include <stdio.h>
#include <string.h>

#define MAX 100   // 最大记录条数

 /* 单条记录的结构体 */
typedef struct {
    double money;   // 金额
    int Type;       // 0=收入, 1=支出
    char note[100]; // 备注
} Record;

/* 全局数据：记录仓库 + 当前数量 */
Record records[MAX];
int count = 0;

/* 打印菜单 */
void menu() {
    printf("================个人微型账本================\n");
    printf("按1添加记录\n");
    printf("按2显示所有记录\n");
    printf("按3删除记录\n");
    printf("按4修改记录\n");
    printf("按5保存文件\n");
    printf("按0退出\n");
    printf("============================================\n");
}

/* 添加一条记录到数组末尾 */
void add() {
    if (count >= MAX) {
        printf("记录已满\n");
        return;
    }
    printf("输入你第%d条记录的金额:", count + 1);
    scanf("%lf", &records[count].money);

    printf("输入你第%d条记录的类型(0=收入，1=支出):", count + 1);
    scanf("%d", &records[count].Type);

    /* 类型校验：只能输入 0 或 1 */
    if (records[count].Type != 1 && records[count].Type != 0) {
        printf("输入正确的类型选项\n");
        return;
    }

    printf("输入你第%d条记录的备注:", count + 1);
    scanf("%99s", records[count].note);   // %99s 防止缓冲区溢出

    count++;   // 总数 +1
    printf("当前共有%d条记录\n", count);
}

/* 显示所有记录 */
void show() {
    if (count == 0) {
        printf("没有记录\n");
        return;
    }
    for (int j = 0; j < count; j++) {
        printf("第%d条记录的金额是%.2lf\n", j + 1, records[j].money);

        if (records[j].Type == 0) {
            printf("第%d条记录类型是:收入\n", j + 1);
        }
        else {
            printf("第%d条记录类型是:支出\n", j + 1);
        }

        printf("第%d条记录的备注是:%s\n", j + 1, records[j].note);
        printf("\n");   // 每条之间空一行，美观
    }
}

/* 按序号删除记录：后面的记录往前移一格 */
void delete() {
    int j;
    if (count == 0) {
        printf("没有记录\n");
        return;
    }
    printf("输入要删除的记录序号(1-%d):", count);
    scanf("%d", &j);

    /* 合法性检查 */
    if (j < 1 || j > count) {
        printf("输入范围内的数字\n");
        return;
    }

    /* 从第 j 条开始，后面每条往前移一格，覆盖被删的记录 */
    for (int i = j - 1; i < count - 1; i++) {
        records[i] = records[i + 1];
    }

    count--;   // 总数 -1
    printf("删除成功\n");
}

/* 按序号修改记录：重新输入该位置的内容 */
void modfiy() {
    int j;
    if (count == 0) {
        printf("没有记录\n");
        return;
    }
    printf("输入要更改的记录序号(1-%d)\n", count);
    scanf("%d", &j);

    if (j < 1 || j > count) {
        printf("输入范围内的数字\n");
        return;
    }

    /* 重新写入该位置（数组下标 = 用户序号 - 1） */
    printf("第%d笔记录内的金额是:", j);
    scanf("%lf", &records[j - 1].money);

    printf("第%d笔记录内的类型是(0收入，1支出):", j);
    scanf("%d", &records[j - 1].Type);

    printf("第%d笔记录内的备注是:", j);
    scanf("%99s", records[j - 1].note);

    printf("修改成功\n");
}

/* 保存到文件：第一行写 count，后面每行写一条记录 */
void save() {
    FILE* fp = fopen("ledger.txt", "w");   // "w" = 覆盖写入
    if (fp == NULL) {
        printf("文件写入失败\n");
        return;
    }

    fprintf(fp, "%d\n", count);   // 先写总数，方便读取时知道循环次数

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%.2lf %d %s\n",
            records[i].money,
            records[i].Type,
            records[i].note);
    }

    fclose(fp);   // 必须关闭文件，否则数据可能没刷到硬盘
    printf("保存成功,共%d条记录\n", count);
}

/* 从文件读取：启动时自动加载历史数据 */
void load() {
    FILE* fp = fopen("ledger.txt", "r");   // "r" = 只读
    if (fp == NULL) {
        return;   // 第一次运行没有文件，静默返回，当成空账本
    }

    fscanf(fp, "%d", &count);   // 先读总数

    for (int i = 0; i < count; i++) {
        fscanf(fp, "%lf %d %99s",
            &records[i].money,
            &records[i].Type,
            records[i].note);   // 数组名本身就是地址，不需要 &
    }

    fclose(fp);
    printf("读取文件记录成功\n");
}

/* 主函数：菜单循环 */
int main() {
    int n = 0;
    load();   // 启动时自动读取历史数据

    while (1) {
        menu();
        printf("输入你的选择\n");
        scanf("%d", &n);

        switch (n) {
        case 0: {
            save();           // 退出前自动保存
            printf("成功退出\n");
            return 0;
        }
        case 1: { add(); break; }
        case 2: { show(); break; }
        case 3: { delete(); break; }
        case 4: { modfiy(); break; }
        case 5: { save(); break; }
        default: { printf("无效的操作\n"); }
        }
    }
    return 0;
}