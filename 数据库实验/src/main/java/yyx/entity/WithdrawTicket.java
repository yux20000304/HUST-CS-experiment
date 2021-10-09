package yyx.entity;

public class WithdrawTicket {
    private Integer id;

    private Integer pId;

    private Integer bookId;

    private Boolean withdraw;

    public WithdrawTicket(Integer id, Integer pId, Integer bookId, Boolean withdraw) {
        this.id = id;
        this.pId = pId;
        this.bookId = bookId;
        this.withdraw = withdraw;
    }

    public WithdrawTicket() {
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

    public Integer getBookId() {
        return bookId;
    }

    public void setBookId(Integer bookId) {
        this.bookId = bookId;
    }

    public Boolean getWithdraw() {
        return withdraw;
    }

    public void setWithdraw(Boolean withdraw) {
        this.withdraw = withdraw;
    }
}