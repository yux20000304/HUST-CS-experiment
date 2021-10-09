package yyx.service;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import yyx.dao.BillsMapper;
import yyx.entity.Bills;
import yyx.entity.BillsExample;

import java.util.List;

@Service
public class BillService {
    @Autowired
    BillsMapper billsMapper;

    public List<Bills> getuserbill(Integer userid){
        BillsExample billsExample=new BillsExample();
        BillsExample.Criteria c1=billsExample.createCriteria();
        c1.andPIdEqualTo(userid);
        return billsMapper.selectByExample(billsExample);
    }
}
