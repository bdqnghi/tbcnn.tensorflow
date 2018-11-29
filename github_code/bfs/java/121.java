package jp.groupsession.v2.bbs.model;

import java.io.Serializable;

import jp.co.sjts.util.NullDefault;
import jp.co.sjts.util.date.UDate;

/**
 * <p>BBS_FOR_SUM Data Bindding JavaBean
 *
 * @author JTS DaoGenerator version 0.1
 */
public class BbsForSumModel implements Serializable {

    /** BFI_SID mapping */
    private int bfiSid__;
    /** BFS_THRE_CNT mapping */
    private int bfsThreCnt__;
    /** BFS_WRT_CNT mapping */
    private int bfsWrtCnt__;
    /** BFS_WRT_DATE mapping */
    private UDate bfsWrtDate__;
    /** BFS_AUID mapping */
    private int bfsAuid__;
    /** BFS_ADATE mapping */
    private UDate bfsAdate__;
    /** BFS_EUID mapping */
    private int bfsEuid__;
    /** BFS_EDATE mapping */
    private UDate bfsEdate__;
    /** BFS_SIZE mapping */
    private long bfsSize__;

    /**
     * <p>Default Constructor
     */
    public BbsForSumModel() {
    }

    /**
     * <p>get BFI_SID value
     * @return BFI_SID value
     */
    public int getBfiSid() {
        return bfiSid__;
    }

    /**
     * <p>set BFI_SID value
     * @param bfiSid BFI_SID value
     */
    public void setBfiSid(int bfiSid) {
        bfiSid__ = bfiSid;
    }

    /**
     * <p>get BFS_THRE_CNT value
     * @return BFS_THRE_CNT value
     */
    public int getBfsThreCnt() {
        return bfsThreCnt__;
    }

    /**
     * <p>set BFS_THRE_CNT value
     * @param bfsThreCnt BFS_THRE_CNT value
     */
    public void setBfsThreCnt(int bfsThreCnt) {
        bfsThreCnt__ = bfsThreCnt;
    }

    /**
     * <p>get BFS_WRT_CNT value
     * @return BFS_WRT_CNT value
     */
    public int getBfsWrtCnt() {
        return bfsWrtCnt__;
    }

    /**
     * <p>set BFS_WRT_CNT value
     * @param bfsWrtCnt BFS_WRT_CNT value
     */
    public void setBfsWrtCnt(int bfsWrtCnt) {
        bfsWrtCnt__ = bfsWrtCnt;
    }

    /**
     * <p>get BFS_WRT_DATE value
     * @return BFS_WRT_DATE value
     */
    public UDate getBfsWrtDate() {
        return bfsWrtDate__;
    }

    /**
     * <p>set BFS_WRT_DATE value
     * @param bfsWrtDate BFS_WRT_DATE value
     */
    public void setBfsWrtDate(UDate bfsWrtDate) {
        bfsWrtDate__ = bfsWrtDate;
    }

    /**
     * <p>get BFS_AUID value
     * @return BFS_AUID value
     */
    public int getBfsAuid() {
        return bfsAuid__;
    }

    /**
     * <p>set BFS_AUID value
     * @param bfsAuid BFS_AUID value
     */
    public void setBfsAuid(int bfsAuid) {
        bfsAuid__ = bfsAuid;
    }

    /**
     * <p>get BFS_ADATE value
     * @return BFS_ADATE value
     */
    public UDate getBfsAdate() {
        return bfsAdate__;
    }

    /**
     * <p>set BFS_ADATE value
     * @param bfsAdate BFS_ADATE value
     */
    public void setBfsAdate(UDate bfsAdate) {
        bfsAdate__ = bfsAdate;
    }

    /**
     * <p>get BFS_EUID value
     * @return BFS_EUID value
     */
    public int getBfsEuid() {
        return bfsEuid__;
    }

    /**
     * <p>set BFS_EUID value
     * @param bfsEuid BFS_EUID value
     */
    public void setBfsEuid(int bfsEuid) {
        bfsEuid__ = bfsEuid;
    }

    /**
     * <p>get BFS_EDATE value
     * @return BFS_EDATE value
     */
    public UDate getBfsEdate() {
        return bfsEdate__;
    }

    /**
     * <p>set BFS_EDATE value
     * @param bfsEdate BFS_EDATE value
     */
    public void setBfsEdate(UDate bfsEdate) {
        bfsEdate__ = bfsEdate;
    }

    /**
     * <p>get BFS_SIZE value
     * @return BFS_SIZE value
     */
    public long getBfsSize() {
        return bfsSize__;
    }

    /**
     * <p>set BFS_SIZE value
     * @param bfsSize BFS_SIZE value
     */
    public void setBfsSize(long bfsSize) {
        bfsSize__ = bfsSize;
    }

    /**
     * <p>to Csv String
     * @return Csv String
     */
    public String toCsvString() {
        StringBuffer buf = new StringBuffer();
        buf.append(bfiSid__);
        buf.append(",");
        buf.append(bfsThreCnt__);
        buf.append(",");
        buf.append(bfsWrtCnt__);
        buf.append(",");
        buf.append(NullDefault.getStringFmObj(bfsWrtDate__, ""));
        buf.append(",");
        buf.append(bfsAuid__);
        buf.append(",");
        buf.append(NullDefault.getStringFmObj(bfsAdate__, ""));
        buf.append(",");
        buf.append(bfsEuid__);
        buf.append(",");
        buf.append(NullDefault.getStringFmObj(bfsEdate__, ""));
        buf.append(",");
        buf.append(bfsSize__);
        return buf.toString();
    }

}
