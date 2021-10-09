package yyx.controller;

import com.github.pagehelper.PageHelper;
import com.github.pagehelper.PageInfo;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RequestParam;
import yyx.dao.AirInfoMapper;
import yyx.dao.AirSeatMapper;
import yyx.dao.BookMapper;
import yyx.entity.AirInfo;
import yyx.entity.AirInfoExample;
import yyx.entity.AirSeat;
import yyx.entity.Book;
import yyx.service.AirInfoService;
import yyx.service.AirSeatService;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.List;

@Controller
public class SubscribeController {

    @Autowired
    BookMapper bookMapper;

    @Autowired
    AirInfoMapper airInfoMapper;

    @Autowired
    AirInfoService airInfoService;

    @Autowired
    AirSeatMapper airSeatMapper;

    @RequestMapping(value="/findsubscribe/{userid}/{pn}",method = RequestMethod.GET)
    public String findsubscribe(@PathVariable(value="pn")Integer pn,@PathVariable(value="userid")Integer userid,
                            @RequestParam(value="from",defaultValue = "wuhan") String from,@RequestParam(value="to",defaultValue = "guangzhou")String to ,
                            @RequestParam(value="year",defaultValue = "2021") Integer year,@RequestParam(value="month",defaultValue = "6")Integer month,
                                @RequestParam(value="day",defaultValue = "18")Integer day, Model model) throws ParseException {
        PageHelper.startPage(pn, 5);
        List<AirInfo> getfromdb=airInfoService.getset(from,to,year,month,day);
        PageInfo page=new PageInfo(getfromdb,5);
        model.addAttribute("pageInfo",page);
        model.addAttribute("userid",userid);
        model.addAttribute("from",from);
        model.addAttribute("to",to);
        model.addAttribute("year",year);
        model.addAttribute("month",month);
        model.addAttribute("day",day);
        System.out.println(from);
        return "WEB-INF/views/subscribe";
    }

    @RequestMapping("/suitairinfo/{userid}")
    public String suitairinfo(@PathVariable(value="userid")Integer userid ,Model model){
        model.addAttribute("userid",userid);
        return "WEB-INF/views/searchpage";
    }

    @RequestMapping(value="/subscribe/{userid}",method = RequestMethod.GET)
    public String subscribe(@RequestParam(value="from")String from,@RequestParam(value="to")String to,
                            @PathVariable(value="userid")Integer userid,
                            @RequestParam(value="airinfo") String airinfo,
                            Model model ){
        AirInfo airInfo=airInfoMapper.selectByPrimaryKey(airinfo);
        if(airInfo.getBookedseats().equals(airInfo.getTotalseats())){
            model.addAttribute("userid",userid);
            return "WEB-INF/views/userpage";
        }
        Integer price=airInfo.getPrice();
        bookMapper.insertSelective(new Book(null,userid,airinfo,new Date(),price));
        airInfoMapper.updateByPrimaryKey(new AirInfo(airInfo.getId(),airInfo.getTakeoffTime(),
                                            airInfo.getArriveTime(),airInfo.getOriginStat(),
                                            airInfo.getTermStat(),airInfo.getPrice(),
                                airInfo.getBookedseats()+1,airInfo.getTotalseats()));
        airSeatMapper.insertSelective(new AirSeat(null,airInfo.getId(),airInfo.getBookedseats()));
        model.addAttribute("userid",userid);
        return "WEB-INF/views/userpage";
    }

}
