package com.dataliance.hadoop.hdfs;

public class DFSClusterStatus
{
    private String configuredCapacity;
    private String dfsUsed;
    private String nonDfsUsed;
    private String dfsRemaining;
    private String percentDfsUse;
    private String percentDfsRemaining;
    private int liveNodes;
    private int deadNodes;
    private long blocks;
    
    public String getConfiguredCapacity() {
        return this.configuredCapacity;
    }
    
    public void setConfiguredCapacity(final String configuredCapacity) {
        this.configuredCapacity = configuredCapacity;
    }
    
    public String getDfsUsed() {
        return this.dfsUsed;
    }
    
    public void setDfsUsed(final String dfsUsed) {
        this.dfsUsed = dfsUsed;
    }
    
    public String getNonDfsUsed() {
        return this.nonDfsUsed;
    }
    
    public void setNonDfsUsed(final String nonDfsUsed) {
        this.nonDfsUsed = nonDfsUsed;
    }
    
    public String getDfsRemaining() {
        return this.dfsRemaining;
    }
    
    public void setDfsRemaining(final String dfsRemaining) {
        this.dfsRemaining = dfsRemaining;
    }
    
    public String getPercentDfsUse() {
        return this.percentDfsUse;
    }
    
    public void setPercentDfsUse(final String percentDfsUse) {
        this.percentDfsUse = percentDfsUse;
    }
    
    public String getPercentDfsRemaining() {
        return this.percentDfsRemaining;
    }
    
    public void setPercentDfsRemaining(final String percentDfsRemaining) {
        this.percentDfsRemaining = percentDfsRemaining;
    }
    
    public int getLiveNodes() {
        return this.liveNodes;
    }
    
    public void setLiveNodes(final int liveNodes) {
        this.liveNodes = liveNodes;
    }
    
    public int getDeadNodes() {
        return this.deadNodes;
    }
    
    public void setDeadNodes(final int deadNodes) {
        this.deadNodes = deadNodes;
    }
    
    public long getBlocks() {
        return this.blocks;
    }
    
    public void setBlocks(final long blocks) {
        this.blocks = blocks;
    }
}
