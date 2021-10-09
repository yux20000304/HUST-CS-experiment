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
import yyx.dao.ManagerMapper;
import yyx.dao.UserInfoMapper;
import yyx.entity.Manager;
import yyx.entity.UserInfo;

import java.util.List;

@Controller
public class ManagerloginController {

    @Autowired
    ManagerMapper managerMapper;

    @RequestMapping("/managerlogincontrol")
    public String managerlogin(
                          Model model){

        return "WEB-INF/views/managerlogin";
    }

    @RequestMapping(value="/managerlogincheck",method = RequestMethod.GET)
    public String managerlogincheck(@RequestParam("managername") String managername,@RequestParam("password") String password, Model model){
        Manager getfromdb=managerMapper.selectByPrimaryKey(managername);
        System.out.println(managername);
        if(getfromdb!=null && getfromdb.getPassword().equals(password)){
            model.addAttribute("managername",managername);
            return "WEB-INF/views/managerpage";
        }
        else{
            model.addAttribute("message","username or password is wrong!");
            return "WEB-INF/views/managerlogin";
        }
    }

    @RequestMapping("/backtomanagerpage/{managername}")
    public String backtomanagerpage(@PathVariable(value="managername")String managername
                                    ,Model model){
        model.addAttribute("managername",managername);
        return "WEB-INF/views/managerpage";
    }


}
