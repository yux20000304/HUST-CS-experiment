package yyx.service;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import yyx.dao.AirSeatMapper;
import yyx.entity.AirSeat;
import yyx.entity.AirSeatExample;
import yyx.entity.Book;
import yyx.entity.BookExample;

import java.util.List;
@Service
public class AirSeatService {
    @Autowired
    AirSeatMapper airSeatMapper;

    public List<AirSeat> getflightseats(String flightinfo){
        AirSeatExample airSeatExample=new AirSeatExample();
        airSeatExample.setOrderByClause("seatnum");
        airSeatExample.or().andFlightIdEqualTo(flightinfo);
        return airSeatMapper.selectByExample(airSeatExample);

    }

    public Integer countseatratio(String flightinfo){
        AirSeatExample airSeatExample=new AirSeatExample();
        AirSeatExample.Criteria c1=airSeatExample.createCriteria();
        c1.andFlightIdEqualTo(flightinfo);
        return airSeatMapper.selectByExample(airSeatExample).size();
    }
}
