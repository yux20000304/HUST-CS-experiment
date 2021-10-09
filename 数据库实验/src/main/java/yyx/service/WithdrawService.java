package yyx.service;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import yyx.dao.WithdrawTicketMapper;
import yyx.entity.BillsExample;
import yyx.entity.WithdrawTicket;
import yyx.entity.WithdrawTicketExample;

import java.util.List;

@Service
public class WithdrawService {
    @Autowired
    WithdrawTicketMapper withdrawTicketMapper;

    public List<WithdrawTicket> getuserwithdraw(Integer userid){

        WithdrawTicketExample withdrawTicketExample=new WithdrawTicketExample();
        WithdrawTicketExample.Criteria c1=withdrawTicketExample.createCriteria();
        c1.andPIdEqualTo(userid);
        return withdrawTicketMapper.selectByExample(withdrawTicketExample);
    }
}
