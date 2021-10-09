package yyx.entity;

public class AirSeat {
    private Integer id;

    private String flightId;

    private Integer seatnum;

    public AirSeat(Integer id, String flightId, Integer seatnum) {
        this.id = id;
        this.flightId = flightId;
        this.seatnum = seatnum;
    }

    public AirSeat() {
    }

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public String getFlightId() {
        return flightId;
    }

    public void setFlightId(String flightId) {
        this.flightId = flightId == null ? null : flightId.trim();
    }

    public Integer getSeatnum() {
        return seatnum;
    }

    public void setSeatnum(Integer seatnum) {
        this.seatnum = seatnum;
    }
}