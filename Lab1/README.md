# README

## 实验要求

**根据下面的需求描述，使用SAP(Sybase) Power Designer 16.x设计相应的数据库概念模型，并转换成MySQL上的物理数据库结构。**

某银行准备开发一个银行业务管理系统，通过调查，得到以下的主要需求：

银行有多个支行。各个支行位于某个城市，每个支行有唯一的名字。银行要监控每个支行的资产。 银行的客户通过其身份证号来标识。银行存储每个客户的姓名及其居住的街道和城市。客户可以有帐户，并且可以贷款。客户可能和某个银行员工发生联系，该员工是此客户的贷款负责人或银行帐户负责人。 银行员工也通过身份证号来标识。员工分为部门经理和普通员工，每个部门经理都负责领导其所在部门的员工，并且每个员工只允许在一个部门内工作。每个支行的管理机构存储每个员工的姓名、电话号码、 家庭地址及其经理的身份证号。银行还需知道每个员工开始工作的日期，由此日期可以推知员工的雇佣期。 银行提供两类帐户——储蓄帐户和支票帐户。帐户可以由2个或2个以上客户所共有，一个客户也可有两个或两个以上的帐户。每个帐户被赋以唯一的帐户号。银行记录每个帐户的余额 、开户的支行以及每个帐户所有者访问该帐户的最近日期。另外，每个储蓄帐户有其利率，且每个支票帐户有其透支额。 每笔贷款由某个分支机构发放，能被一个或多个客户所共有。每笔贷款用唯一的贷款号标识。银行需要知道每笔贷款所贷金额以及逐次支付的情况（银行将贷款分几次付给客户）。虽然贷款号不能唯一标识银行所有为贷款所付的款项，但可以唯一标识为某贷款所付的款项。对每次的付款需要记录日期和金额。

提交内容：

(1) 文档：设计报告（参考格式：adb-lab01-template.docx）,word/PDF均可。
(2) 原始设计文件，以及readme。
(3) 提交截至时间：2024/11/30 12:00 PM（北京时间），提交方式：等待助教通知


## 文件架构介绍

```
├── BankDatabase.cdm                #概念数据模型
├── BankDatabasePDM.pdm             #物理数据模型
├── Full Conceptual Report_files    #概念设计数据报告，用浏览器打开该文件夹下 Full Conceptual Report_toc.html
├── Full Physical Report_files      #物理数据模型报告，用浏览器打开该文件夹下 Full Physical Report_toc.html
├── README.md                       
├── adb-lab01-template.docx         #实验报告
└── 数据库实现.sql                    #数据的物理部署,所用环境为 MySQL8.3.0
```

## 环境要求

+ 操作系统：Windows 10 或更新版本（建议安装 Power Designer）
+ 软件版本：
    + SAP(Sybase) Power Designer 16.x
	+ MySQL 8.3.0（或兼容版本）
+ 数据库管理工具：推荐使用 MySQL Workbench 或 Navicat 连接 MySQL 数据库。

## 使用说明

1. **概念数据模型的查看**
使用 Power Designer 打开 BankDatabase.cdm 文件以查看银行业务的概念模型。

2. **物理数据模型的查看**
使用 Power Designer 打开 BankDatabasePDM.pdm 文件以查看银行业务的物理模型。

3. **生成数据库**
运行 数据库实现.sql 文件将物理模型部署到 MySQL 数据库中，步骤如下：
    1. 打开 MySQL Workbench 或 Navicat。
	2. 新建一个数据库（建议命名为 BankDatabase）。
	3. 执行 数据库实现.sql 文件以创建所有表和约束。

4. **报告查看**
	打开以下文件夹中的 HTML 文件以查看详细的报告：
	+ **概念模型报告**：Full Conceptual Report_files/Full Conceptual Report_toc.html
	+ **物理模型报告**：Full Physical Report_files/Full Physical Report_toc.html

## 项目目标

本实验旨在通过需求分析、概念建模和物理建模三个阶段，掌握以下技能：
+ 数据库需求分析和抽象建模。
+ 使用 Power Designer 创建数据库概念模型（CDM）和物理模型（PDM）。
+ 将数据库设计转换为 MySQL 的物理实现。
+ 理解并实现复杂的数据库约束关系。

## 贡献

如需改进或报告问题，请通过以下方式联系项目负责人：
  + 邮箱：jianqiaozh@mail.ustc.edn.cn
  + GitHub（结课前项目为private）: https://github.com/CambridgeZ/Advanced_DataBase_USTC 