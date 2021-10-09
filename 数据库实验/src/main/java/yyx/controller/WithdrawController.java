package yyx.controller;

import com.github.pagehelper.PageInfo;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import yyx.entity.Bills;
import yyx.entity.WithdrawTicket;
import yyx.service.BillService;
import yyx.service.WithdrawService;

import java.util.List;

@Controller
public class WithdrawController {

    @Autowired
    WithdrawService withdrawService;

    @RequestMapping("/withdrawinfo/{userid}/{pn}")
    public String getbillinfo(@PathVariable(value="pn")Integer pn,
                              @PathVariable(value="userid")Integer userid,
                              Model model){
        System.out.println(userid);
        List<WithdrawTicket> getfromdb=withdrawService.getuserwithdraw(userid);
        PageInfo page=new PageInfo(getfromdb,5);
        model.addAttribute("pageInfo",page);
        model.addAttribute("userid",userid);
        return "WEB-INF/views/withdrawinfomation";
    }
}
