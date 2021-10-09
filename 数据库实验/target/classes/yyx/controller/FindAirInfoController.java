package yyx.controller;

import com.github.pagehelper.PageHelper;
import com.github.pagehelper.PageInfo;
import org.apache.ibatis.annotations.Mapper;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RequestParam;
import yyx.dao.AirInfoMapper;
import yyx.dao.AirSeatMapper;
import yyx.entity.*;
import yyx.service.AirInfoService;
import yyx.service.AirSeatService;
import yyx.service.BookService;
import yyx.service.UserService;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.*;

@Controller
public class FindAirInfoController {

    @Autowired
    AirInfoService airInfoService;
    @Autowired
    AirInfoMapper airInfoMapper;
    @Autowired
    BookService bookService;
    @Autowired
    AirSeatService airSeatService;

    @RequestMapping("/findairinfo/{userid}/{pn}")
    public String getUser(@PathVariable(value="pn")Integer pn,
                          @PathVariable(value="userid")Integer userid,
                          Model model){
        //非常多的记录，需要分页
        //引入page helper插件
        //在查询之前只需要调用
        PageHelper.startPage(pn, 5);

        List<AirInfo> airInfos = airInfoService.getAll();
        //包装查询后的结果
        //封装了详细的信息，包括查询出来的数据，连续传入5页
        PageInfo page=new PageInfo(airInfos,5);
        model.addAttribute("pageInfo",page);
        model.addAttribute("userid",userid);
        return "WEB-INF/views/airinfomation";
    }

    @RequestMapping("/searchairseatinfo/{userid}")
    public String getairseatinfo(@PathVariable(value="userid")Integer userid,
                                 Model model){
        model.addAttribute("userid",userid);
        return "WEB-INF/views/searchflightseat";
    }

    @RequestMapping(value="/findflightseat/{userid}/{pn}",method = RequestMethod.GET)
    public String getflightseat(@PathVariable(value="userid")Integer userid,
                                @PathVariable(value="pn")Integer pn,
                                @RequestParam(value="flightinfo")String flightinfo,Model model){
        List<AirSeat> getfromdb=airSeatService.getflightseats(flightinfo);
        PageInfo page=new PageInfo(getfromdb,5);
        model.addAttribute("pageInfo",page);
        model.addAttribute("ratio",getfromdb.size());
        model.addAttribute("userid",userid);
        return "WEB-INF/views/seatlist";
    }

    @RequestMapping("/findmanagerairinfomation/{managername}/{pn}")
    public String managerairinfomation(@PathVariable(value="pn")Integer pn,
                          @PathVariable(value="managername")String managername,
                          Model model){

        PageHelper.startPage(pn, 5);

        List<AirInfo> airInfos= airInfoService.getAll();

        PageInfo page=new PageInfo(airInfos,5);
        model.addAttribute("pageInfo",page);
        model.addAttribute("managername",managername);
        return "WEB-INF/views/managerairinfomation";
    }


    @RequestMapping(value = "/insertflightinfo/{managername}/{pn}",method = RequestMethod.GET)
    public String insertflightinfo(@PathVariable(value="pn")Integer pn,
                          @PathVariable(value="managername")String managername,
                          @RequestParam(value="flightid")String flightid,
                          @RequestParam(value="takeofftime")String takeofftime,
                          @RequestParam(value="arrivetime")String arrivetime,
                          @RequestParam(value="originstat")String originstat,
                          @RequestParam(value="termstat")String termstat,
                          @RequestParam(value="price")Integer price,
                          @RequestParam(value="totalseats")Integer totalseats,
                          Model model) throws ParseException {
        Date date1= new SimpleDateFormat("yyyy-MM-dd HH:mm:ss").parse(takeofftime);
        Date date2= new SimpleDateFormat("yyyy-MM-dd HH:mm:ss").parse(arrivetime);

        airInfoMapper.insertSelective(new AirInfo(flightid,date1,date2,originstat,termstat,price,0,totalseats));
        PageHelper.startPage(pn, 5);

        List<AirInfo> airInfos = airInfoService.getAll();
        //包装查询后的结果
        //封装了详细的信息，包括查询出来的数据，连续传入5页
        PageInfo page=new PageInfo(airInfos,5);
        model.addAttribute("pageInfo",page);
        model.addAttribute("managername",managername);
        return "WEB-INF/views/managerairinfomation";
    }

}
