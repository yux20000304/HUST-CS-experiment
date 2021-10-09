package yyx.service;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import yyx.dao.AirInfoMapper;
import yyx.dao.BookMapper;
import yyx.dao.WithdrawTicketMapper;
import yyx.entity.AirInfo;
import yyx.entity.Book;
import yyx.entity.BookExample;
import yyx.entity.WithdrawTicketExample;

import java.util.List;

@Service
public class BookService {
    @Autowired
    BookMapper bookMapper;
    @Autowired
    WithdrawTicketMapper withdrawTicketMapper;
    @Autowired
    AirInfoMapper airInfoMapper;

    public List<Book> getAll(){
        return bookMapper.selectByExample(null);
    }

    public List<Book> getuserbook(Integer usrId){
        BookExample bookExample=new BookExample();
        bookExample.or().andPIdEqualTo(usrId);
        return bookMapper.selectByExample(bookExample);
    }

    public void cancelbook(Integer cancelid){
        WithdrawTicketExample withdrawTicketExample=new WithdrawTicketExample();
        WithdrawTicketExample.Criteria c1=withdrawTicketExample.createCriteria();
        c1.andBookIdEqualTo(cancelid);
        Book book=bookMapper.selectByPrimaryKey(cancelid);
        AirInfo airInfo=airInfoMapper.selectByPrimaryKey(book.getAirInfo());
        withdrawTicketMapper.deleteByExample(withdrawTicketExample);
        bookMapper.deleteByPrimaryKey(cancelid);
        airInfoMapper.updateByPrimaryKey(new AirInfo(airInfo.getId(),airInfo.getTakeoffTime(),
                airInfo.getArriveTime(),airInfo.getOriginStat(),
                airInfo.getTermStat(),airInfo.getPrice(),
                airInfo.getBookedseats()-1,airInfo.getTotalseats()));
    }

}
