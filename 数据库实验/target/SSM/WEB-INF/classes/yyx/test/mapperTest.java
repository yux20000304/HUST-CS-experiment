package yyx.test;


import org.apache.ibatis.session.SqlSession;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;
import org.springframework.test.context.ContextConfiguration;
import org.springframework.test.context.junit4.SpringJUnit4ClassRunner;
import yyx.dao.*;
import yyx.entity.*;
import yyx.service.AirInfoService;

import java.util.Calendar;
import java.util.Date;
import java.util.GregorianCalendar;
import java.util.UUID;


//使用注解进行单元测试
@RunWith(SpringJUnit4ClassRunner.class)
@ContextConfiguration(locations = {"classpath:applicationContext.xml"})
public class mapperTest {

    @Autowired
    ManagerMapper managerMapper;
    @Autowired
    AirInfoMapper airInfoMapper;


    //    批量的sqlSession
    @Autowired
    SqlSession sqlSession;

    /**
     * 测试DepartmentMapper
     */
    @Test
    public void testyyx(){

        ManagerMapper mapper1 = sqlSession.getMapper(ManagerMapper.class);
        for(int i = 0; i < 100; i++){
            String uuid = UUID.randomUUID().toString().substring(0, 5) + i;
            mapper1.insertSelective(new Manager("yyx"+i,i,"123456"));
        }

        UserInfoMapper mapper2 = sqlSession.getMapper(UserInfoMapper.class);
        for(int i=100;i<200;i++){
            String uuid = UUID.randomUUID().toString().substring(0, 5) + i;
            mapper2.insertSelective(new UserInfo("yyxuser"+i,i,"123456"));
        }

//        BillsMapper mapper3 =sqlSession.getMapper(BillsMapper.class);
//        for(int i=100;i<200;i++){
//            String uuid = UUID.randomUUID().toString().substring(0, 5) + i;
//            mapper3.insertSelective(new Bills(i,i,i+400));
//        }

        AirInfoMapper mapper4 = sqlSession.getMapper(AirInfoMapper.class);
        for(int i = 100; i < 200; i++){
            String uuid = UUID.randomUUID().toString().substring(0, 5) + i;
            Date date=new Date();
            Date date1=new Date();
            Calendar c=new GregorianCalendar();
            c.setTime(date);
            c.add(Calendar.HOUR,10);
            date=c.getTime();
            c.add(Calendar.HOUR,1);
            date1=c.getTime();
            System.out.println(date);
            mapper4.insertSelective(new AirInfo("flight"+i,date,date1,"wuhan","guangzhou",100+i,0,100));
        }

        BookMapper mapper5 = sqlSession.getMapper(BookMapper.class);
        for(int i=100;i<200;i++){
            String uuid = UUID.randomUUID().toString().substring(0, 5) + i;
            mapper5.insertSelective(new Book(i,i,"flight"+i,new Date(80*i),i*10));
        }
        System.out.println("success!!");
//        WithdrawTicketMapper mapper6=sqlSession.getMapper(WithdrawTicketMapper.class);
//        for(int i=100;i<200;i++){
//            String uuid = UUID.randomUUID().toString().substring(0, 5) + i;
//            mapper6.insertSelective(new WithdrawTicket(i,i,i,false));
//        }

//        AirSeatMapper mapper7=sqlSession.getMapper(AirSeatMapper.class);
//        for(int i=100;i<200;i++){
//            String uuid = UUID.randomUUID().toString().substring(0, 5) + i;
//            mapper7.insertSelective(new AirSeat(i,"flight"+i,i-100));
//        }

    }

}
