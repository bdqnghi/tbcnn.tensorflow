package com.xiedang.www.model;

import java.math.BigDecimal;
import java.util.Date;

/**
 * 单据文件
 * BillFiles
 * 数据库表：bill_files
 */
public class BillFiles {

    /**
     * 文件id
     * 表字段 : bill_files.BFS_ID
     */
    private String bfsId;

    /**
     * 文件名
     * 表字段 : bill_files.BFS_NAME
     */
    private String bfsName;

    /**
     * 文件地址
     * 表字段 : bill_files.BFS_PATH
     */
    private String bfsPath;

    /**
     * 文件类型
     * 表字段 : bill_files.BFS_TYPE
     */
    private String bfsType;

    /**
     * 详细见BillFileTypeEnum枚举(1质检单；2散船运单；3仓库保管单；6散船货物交接单；7散船放货通知单；11货权带过来的运单附件；14凭证；16散船服务合同补登；17散船委托合同补登；20开票交易商附件；21开票附件；22开票服务商附件；25散船放货单模板)
     * 表字段 : bill_files.BFS_BILL_TYPE
     */
    private String bfsBillType;

    /**
     * 单据ID
     * 表字段 : bill_files.BFS_BILL_ID
     */
    private String bfsBillId;

    /**
     * 软删除状态
     * 表字段 : bill_files.BFS_STATUS
     */
    private BigDecimal bfsStatus;

    /**
     * 创建时间
     * 表字段 : bill_files.BFS_CREATE_TIME
     */
    private Date bfsCreateTime;

    /**
     * 获取 文件id 字段:bill_files.BFS_ID
     *
     * @return bill_files.BFS_ID, 文件id
     */
    public String getBfsId() {
        return bfsId;
    }

    /**
     * 设置 文件id 字段:bill_files.BFS_ID
     *
     * @param bfsId the value for bill_files.BFS_ID, 文件id
     */
    public void setBfsId(String bfsId) {
        this.bfsId = bfsId == null ? null : bfsId.trim();
    }

    /**
     * 获取 文件名 字段:bill_files.BFS_NAME
     *
     * @return bill_files.BFS_NAME, 文件名
     */
    public String getBfsName() {
        return bfsName;
    }

    /**
     * 设置 文件名 字段:bill_files.BFS_NAME
     *
     * @param bfsName the value for bill_files.BFS_NAME, 文件名
     */
    public void setBfsName(String bfsName) {
        this.bfsName = bfsName == null ? null : bfsName.trim();
    }

    /**
     * 获取 文件地址 字段:bill_files.BFS_PATH
     *
     * @return bill_files.BFS_PATH, 文件地址
     */
    public String getBfsPath() {
        return bfsPath;
    }

    /**
     * 设置 文件地址 字段:bill_files.BFS_PATH
     *
     * @param bfsPath the value for bill_files.BFS_PATH, 文件地址
     */
    public void setBfsPath(String bfsPath) {
        this.bfsPath = bfsPath == null ? null : bfsPath.trim();
    }

    /**
     * 获取 文件类型 字段:bill_files.BFS_TYPE
     *
     * @return bill_files.BFS_TYPE, 文件类型
     */
    public String getBfsType() {
        return bfsType;
    }

    /**
     * 设置 文件类型 字段:bill_files.BFS_TYPE
     *
     * @param bfsType the value for bill_files.BFS_TYPE, 文件类型
     */
    public void setBfsType(String bfsType) {
        this.bfsType = bfsType == null ? null : bfsType.trim();
    }

    /**
     * 获取 详细见BillFileTypeEnum枚举(1质检单；2散船运单；3仓库保管单；6散船货物交接单；7散船放货通知单；11货权带过来的运单附件；14凭证；16散船服务合同补登；17散船委托合同补登；20开票交易商附件；21开票附件；22开票服务商附件；25散船放货单模板) 字段:bill_files.BFS_BILL_TYPE
     *
     * @return bill_files.BFS_BILL_TYPE, 详细见BillFileTypeEnum枚举(1质检单；2散船运单；3仓库保管单；6散船货物交接单；7散船放货通知单；11货权带过来的运单附件；14凭证；16散船服务合同补登；17散船委托合同补登；20开票交易商附件；21开票附件；22开票服务商附件；25散船放货单模板)
     */
    public String getBfsBillType() {
        return bfsBillType;
    }

    /**
     * 设置 详细见BillFileTypeEnum枚举(1质检单；2散船运单；3仓库保管单；6散船货物交接单；7散船放货通知单；11货权带过来的运单附件；14凭证；16散船服务合同补登；17散船委托合同补登；20开票交易商附件；21开票附件；22开票服务商附件；25散船放货单模板) 字段:bill_files.BFS_BILL_TYPE
     *
     * @param bfsBillType the value for bill_files.BFS_BILL_TYPE, 详细见BillFileTypeEnum枚举(1质检单；2散船运单；3仓库保管单；6散船货物交接单；7散船放货通知单；11货权带过来的运单附件；14凭证；16散船服务合同补登；17散船委托合同补登；20开票交易商附件；21开票附件；22开票服务商附件；25散船放货单模板)
     */
    public void setBfsBillType(String bfsBillType) {
        this.bfsBillType = bfsBillType == null ? null : bfsBillType.trim();
    }

    /**
     * 获取 单据ID 字段:bill_files.BFS_BILL_ID
     *
     * @return bill_files.BFS_BILL_ID, 单据ID
     */
    public String getBfsBillId() {
        return bfsBillId;
    }

    /**
     * 设置 单据ID 字段:bill_files.BFS_BILL_ID
     *
     * @param bfsBillId the value for bill_files.BFS_BILL_ID, 单据ID
     */
    public void setBfsBillId(String bfsBillId) {
        this.bfsBillId = bfsBillId == null ? null : bfsBillId.trim();
    }

    /**
     * 获取 软删除状态 字段:bill_files.BFS_STATUS
     *
     * @return bill_files.BFS_STATUS, 软删除状态
     */
    public BigDecimal getBfsStatus() {
        return bfsStatus;
    }

    /**
     * 设置 软删除状态 字段:bill_files.BFS_STATUS
     *
     * @param bfsStatus the value for bill_files.BFS_STATUS, 软删除状态
     */
    public void setBfsStatus(BigDecimal bfsStatus) {
        this.bfsStatus = bfsStatus;
    }

    /**
     * 获取 创建时间 字段:bill_files.BFS_CREATE_TIME
     *
     * @return bill_files.BFS_CREATE_TIME, 创建时间
     */
    public Date getBfsCreateTime() {
        return bfsCreateTime;
    }

    /**
     * 设置 创建时间 字段:bill_files.BFS_CREATE_TIME
     *
     * @param bfsCreateTime the value for bill_files.BFS_CREATE_TIME, 创建时间
     */
    public void setBfsCreateTime(Date bfsCreateTime) {
        this.bfsCreateTime = bfsCreateTime;
    }
}