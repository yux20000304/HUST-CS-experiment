package yyx.entity;

public class Bills {
    private Integer id;

    private Integer pId;

    private Integer pay;

    public Bills(Integer id, Integer pId, Integer pay) {
        this.id = id;
        this.pId = pId;
        this.pay = pay;
    }

    public Bills() {
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

    public Integer getPay() {
        return pay;
    }

    public void setPay(Integer pay) {
        this.pay = pay;
    }
}