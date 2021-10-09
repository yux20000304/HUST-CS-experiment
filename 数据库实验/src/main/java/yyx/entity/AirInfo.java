package yyx.entity;

import java.util.Date;

public class AirInfo {
    private String id;

    private Date takeoffTime;

    private Date arriveTime;

    private String originStat;

    private String termStat;

    private Integer price;

    private Integer bookedseats;

    private Integer totalseats;

    public AirInfo(String id, Date takeoffTime, Date arriveTime, String originStat, String termStat, Integer price, Integer bookedseats, Integer totalseats) {
        this.id = id;
        this.takeoffTime = takeoffTime;
        this.arriveTime = arriveTime;
        this.originStat = originStat;
        this.termStat = termStat;
        this.price = price;
        this.bookedseats = bookedseats;
        this.totalseats = totalseats;
    }

    public AirInfo() {
    }

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id == null ? null : id.trim();
    }

    public Date getTakeoffTime() {
        return takeoffTime;
    }

    public void setTakeoffTime(Date takeoffTime) {
        this.takeoffTime = takeoffTime;
    }

    public Date getArriveTime() {
        return arriveTime;
    }

    public void setArriveTime(Date arriveTime) {
        this.arriveTime = arriveTime;
    }

    public String getOriginStat() {
        return originStat;
    }

    public void setOriginStat(String originStat) {
        this.originStat = originStat == null ? null : originStat.trim();
    }

    public String getTermStat() {
        return termStat;
    }

    public void setTermStat(String termStat) {
        this.termStat = termStat == null ? null : termStat.trim();
    }

    public Integer getPrice() {
        return price;
    }

    public void setPrice(Integer price) {
        this.price = price;
    }

    public Integer getBookedseats() {
        return bookedseats;
    }

    public void setBookedseats(Integer bookedseats) {
        this.bookedseats = bookedseats;
    }

    public Integer getTotalseats() {
        return totalseats;
    }

    public void setTotalseats(Integer totalseats) {
        this.totalseats = totalseats;
    }
}