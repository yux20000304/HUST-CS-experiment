package yyx.entity;

import java.util.Date;

public class Book {
    private Integer id;

    private Integer pId;

    private String airInfo;

    private Date booktime;

    private Integer price;

    public Book(Integer id, Integer pId, String airInfo, Date booktime, Integer price) {
        this.id = id;
        this.pId = pId;
        this.airInfo = airInfo;
        this.booktime = booktime;
        this.price = price;
    }

    public Book() {
    }

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public Integer getpId() {
        return pId;
    }

    public void setpId(Integer pId) {
        this.pId = pId;
    }

    public String getAirInfo() {
        return airInfo;
    }

    public void setAirInfo(String airInfo) {
        this.airInfo = airInfo == null ? null : airInfo.trim();
    }

    public Date getBooktime() {
        return booktime;
    }

    public void setBooktime(Date booktime) {
        this.booktime = booktime;
    }

    public Integer getPrice() {
        return price;
    }

    public void setPrice(Integer price) {
        this.price = price;
    }
}