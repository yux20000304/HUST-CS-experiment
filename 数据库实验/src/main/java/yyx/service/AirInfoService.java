package yyx.service;


import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import yyx.dao.AirInfoMapper;
import yyx.dao.AirSeatMapper;
import yyx.entity.*;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.*;

@Service
public class AirInfoService {

    @Autowired
    AirInfoMapper airInfoMapper;

    @Autowired
    AirSeatService airSeatService;

    public List<AirInfo> getAll() {

        return airInfoMapper.selectByExample(null);

    }



    public HashMap<AirInfo, Integer> getAllmanagerairinfo(){
        List<AirInfo> airInfos=airInfoMapper.selectByExample(null);
        HashMap<AirInfo,Integer> airInfoWithSeats=new HashMap<>();
        for(AirInfo airInfo:airInfos){
            Integer temp=airSeatService.countseatratio(airInfo.getId());
            airInfoWithSeats.put(airInfo,temp);
        }
        return airInfoWithSeats;
    }




    public List<AirInfo> getset(String from,String to,Integer year,Integer month,Integer day) throws ParseException {
        SimpleDateFormat dateformat = new SimpleDateFormat("yyyy-MM-dd");
        Date date1 = dateformat.parse(year+"-"+month+"-"+day);
        Date date2 = dateformat.parse(year+"-"+month+"-"+(day+1));
        AirInfoExample airInfoExample=new AirInfoExample();
        AirInfoExample.Criteria c1=airInfoExample.createCriteria();
        c1.andTakeoffTimeBetween(date1,date2).andOriginStatEqualTo(from).andTermStatEqualTo(to);
        return airInfoMapper.selectByExample(airInfoExample);
    }

}
