/*
 Navicat Premium Data Transfer

 Source Server         : adb_lab
 Source Server Type    : MySQL
 Source Server Version : 80300
 Source Host           : localhost:3306
 Source Schema         : BankDatabase

 Target Server Type    : MySQL
 Target Server Version : 80300
 File Encoding         : 65001

 Date: 15/10/2024 17:14:57
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for account
-- ----------------------------
DROP TABLE IF EXISTS `account`;
CREATE TABLE `account`  (
  `account_id` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `branch_name` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `balance` float(8, 2) NOT NULL,
  `latest_visited` date NULL DEFAULT NULL,
  PRIMARY KEY (`account_id`) USING BTREE,
  UNIQUE INDEX `account_PK`(`account_id` ASC) USING BTREE,
  INDEX `FK_ACCOUNT_开户_BRANCH`(`branch_name` ASC) USING BTREE,
  CONSTRAINT `FK_ACCOUNT_开户_BRANCH` FOREIGN KEY (`branch_name`) REFERENCES `branch` (`branch_name`) ON DELETE RESTRICT ON UPDATE RESTRICT,
  CONSTRAINT `FK_ACCOUNT_开户_BRANCH_NEW` FOREIGN KEY (`branch_name`) REFERENCES `branch` (`branch_name`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci;

-- ----------------------------
-- Records of account
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for branch
-- ----------------------------
DROP TABLE IF EXISTS `branch`;
CREATE TABLE `branch`  (
  `branch_name` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `property` float(8, 2) NOT NULL,
  `city` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  PRIMARY KEY (`branch_name`) USING BTREE,
  UNIQUE INDEX `branch_PK`(`branch_name` ASC) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci;

-- ----------------------------
-- Records of branch
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for chech_account
-- ----------------------------
DROP TABLE IF EXISTS `chech_account`;
CREATE TABLE `chech_account`  (
  `account_id` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `overdraft_limit` float(8, 2) NULL DEFAULT NULL,
  PRIMARY KEY (`account_id`) USING BTREE,
  UNIQUE INDEX `chech_account_PK`(`account_id` ASC) USING BTREE,
  CONSTRAINT `FK_CHECH_AC_支票账户_账户_ACCOUNT` FOREIGN KEY (`account_id`) REFERENCES `account` (`account_id`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci;

-- ----------------------------
-- Records of chech_account
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for client
-- ----------------------------
DROP TABLE IF EXISTS `client`;
CREATE TABLE `client`  (
  `client_id` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `client_name` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `city` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `street` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  PRIMARY KEY (`client_id`) USING BTREE,
  UNIQUE INDEX `client_PK`(`client_id` ASC) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci COMMENT = '客户';

-- ----------------------------
-- Records of client
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for ClientLoans
-- ----------------------------
DROP TABLE IF EXISTS `ClientLoans`;
CREATE TABLE `ClientLoans`  (
  `loan_id` varchar(60) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `client_id` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  PRIMARY KEY (`loan_id`, `client_id`) USING BTREE,
  UNIQUE INDEX `客户贷款_PK`(`loan_id` ASC, `client_id` ASC) USING BTREE,
  INDEX `FK_CLIENTLO_客户贷款2_CLIENT`(`client_id` ASC) USING BTREE,
  CONSTRAINT `FK_CLIENTLO_客户贷款2_CLIENT` FOREIGN KEY (`client_id`) REFERENCES `client` (`client_id`) ON DELETE RESTRICT ON UPDATE RESTRICT,
  CONSTRAINT `FK_CLIENTLO_客户贷款_LOANS` FOREIGN KEY (`loan_id`) REFERENCES `loans` (`loan_id`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci;

-- ----------------------------
-- Records of ClientLoans
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for Common_employee
-- ----------------------------
DROP TABLE IF EXISTS `Common_employee`;
CREATE TABLE `Common_employee`  (
  `employee_id` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `Leader_id` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  PRIMARY KEY (`employee_id`) USING BTREE,
  UNIQUE INDEX `普通员工_PK`(`employee_id` ASC) USING BTREE,
  INDEX `FK_LEADER`(`Leader_id` ASC) USING BTREE,
  CONSTRAINT `FK_COMMON_E_普通员工_员工_EMPLOYEE` FOREIGN KEY (`employee_id`) REFERENCES `employee` (`employee_id`) ON DELETE RESTRICT ON UPDATE RESTRICT,
  CONSTRAINT `FK_LEADER` FOREIGN KEY (`Leader_id`) REFERENCES `manager` (`employee_id`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci;

-- ----------------------------
-- Records of Common_employee
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for deposit_account
-- ----------------------------
DROP TABLE IF EXISTS `deposit_account`;
CREATE TABLE `deposit_account`  (
  `account_id` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `rate` float NULL DEFAULT NULL,
  PRIMARY KEY (`account_id`) USING BTREE,
  UNIQUE INDEX `deposit_account_PK`(`account_id` ASC) USING BTREE,
  CONSTRAINT `FK_DEPOSIT__储蓄账户_账户_ACCOUNT` FOREIGN KEY (`account_id`) REFERENCES `account` (`account_id`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci;

-- ----------------------------
-- Records of deposit_account
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for employee
-- ----------------------------
DROP TABLE IF EXISTS `employee`;
CREATE TABLE `employee`  (
  `employee_id` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `branch_name` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `phone` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `address` longtext CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL,
  `date_be_employed` date NOT NULL,
  `employee_name` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  PRIMARY KEY (`employee_id`) USING BTREE,
  UNIQUE INDEX `employee_PK`(`employee_id` ASC) USING BTREE,
  INDEX `FK_EMPLOYEE_雇佣_BRANCH`(`branch_name` ASC) USING BTREE,
  CONSTRAINT `FK_EMPLOYEE_雇佣_BRANCH` FOREIGN KEY (`branch_name`) REFERENCES `branch` (`branch_name`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci COMMENT = '员工';

-- ----------------------------
-- Records of employee
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for loans
-- ----------------------------
DROP TABLE IF EXISTS `loans`;
CREATE TABLE `loans`  (
  `loan_id` varchar(60) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `branch_name` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `amount` float(8, 2) NULL DEFAULT NULL,
  `times` int NULL DEFAULT NULL,
  PRIMARY KEY (`loan_id`) USING BTREE,
  UNIQUE INDEX `loans_PK`(`loan_id` ASC) USING BTREE,
  INDEX `FK_LOANS_发放贷款_BRANCH`(`branch_name` ASC) USING BTREE,
  CONSTRAINT `FK_LOANS_发放贷款_BRANCH` FOREIGN KEY (`branch_name`) REFERENCES `branch` (`branch_name`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci;

-- ----------------------------
-- Records of loans
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for manager
-- ----------------------------
DROP TABLE IF EXISTS `manager`;
CREATE TABLE `manager`  (
  `employee_id` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `department` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  PRIMARY KEY (`employee_id`) USING BTREE,
  UNIQUE INDEX `manager_PK`(`employee_id` ASC) USING BTREE,
  CONSTRAINT `FK_MANAGER_经理_员工_EMPLOYEE` FOREIGN KEY (`employee_id`) REFERENCES `employee` (`employee_id`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci;

-- ----------------------------
-- Records of manager
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for OwnAccount
-- ----------------------------
DROP TABLE IF EXISTS `OwnAccount`;
CREATE TABLE `OwnAccount`  (
  `client_id` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `account_id` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  PRIMARY KEY (`client_id`, `account_id`) USING BTREE,
  UNIQUE INDEX `拥有账户_PK`(`client_id` ASC, `account_id` ASC) USING BTREE,
  INDEX `FK_OWNACCOU_拥有账户2_ACCOUNT`(`account_id` ASC) USING BTREE,
  CONSTRAINT `FK_OWNACCOU_拥有账户2_ACCOUNT` FOREIGN KEY (`account_id`) REFERENCES `account` (`account_id`) ON DELETE RESTRICT ON UPDATE RESTRICT,
  CONSTRAINT `FK_OWNACCOU_拥有账户_CLIENT` FOREIGN KEY (`client_id`) REFERENCES `client` (`client_id`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci;

-- ----------------------------
-- Records of OwnAccount
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for Payments
-- ----------------------------
DROP TABLE IF EXISTS `Payments`;
CREATE TABLE `Payments`  (
  `loan_id` varchar(60) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `payment_id` varchar(60) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `payment_amount` float(8, 2) NULL DEFAULT NULL,
  `payment_date` date NULL DEFAULT NULL,
  PRIMARY KEY (`payment_id`) USING BTREE,
  UNIQUE INDEX `Payments_PK`(`loan_id` ASC, `payment_id` ASC) USING BTREE,
  CONSTRAINT `FK_PAYMENTS_贷款_支付_LOANS` FOREIGN KEY (`loan_id`) REFERENCES `loans` (`loan_id`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci;

-- ----------------------------
-- Records of Payments
-- ----------------------------
BEGIN;
COMMIT;

-- ----------------------------
-- Table structure for Responsible
-- ----------------------------
DROP TABLE IF EXISTS `Responsible`;
CREATE TABLE `Responsible`  (
  `employee_id` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `client_id` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `res_type` tinyint NULL DEFAULT NULL,
  PRIMARY KEY (`employee_id`, `client_id`) USING BTREE,
  UNIQUE INDEX `Responsible_PK`(`employee_id` ASC, `client_id` ASC) USING BTREE,
  INDEX `FK_RESPONSI_RESPONSIB_CLIENT`(`client_id` ASC) USING BTREE,
  CONSTRAINT `FK_RESPONSI_RESPONSIB_CLIENT` FOREIGN KEY (`client_id`) REFERENCES `client` (`client_id`) ON DELETE RESTRICT ON UPDATE RESTRICT,
  CONSTRAINT `FK_RESPONSI_RESPONSIB_EMPLOYEE` FOREIGN KEY (`employee_id`) REFERENCES `employee` (`employee_id`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci;

-- ----------------------------
-- Records of Responsible
-- ----------------------------
BEGIN;
COMMIT;

SET FOREIGN_KEY_CHECKS = 1;
