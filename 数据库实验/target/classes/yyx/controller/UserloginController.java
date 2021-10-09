package yyx.controller;

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

@Controller
public class UserloginController {

    @Autowired
    UserInfoMapper userInfoMapper;

    @RequestMapping("/userlogincontrol")
    public String userlogin(Model model){

        return "WEB-INF/views/userlogin";
    }

    @RequestMapping("/usersignincontrol")
    public String usersignin(Model model){
        return "WEB-INF/views/usersigninpage";
    }

    @RequestMapping(value="/userlogincheck",method = RequestMethod.GET)
    public String userlogincheck(@RequestParam("username") String username, @RequestParam("password") String password, Model model){
        UserInfo getfromdb=userInfoMapper.selectByPrimaryKey(username);
        System.out.println(username);
        if(getfromdb!=null && getfromdb.getPassword().equals(password)){
            model.addAttribute("username",username);
            model.addAttribute("userid",getfromdb.getId());
            return "WEB-INF/views/userpage";
        }
        else{
            model.addAttribute("message","username or password is wrong!");
            return "WEB-INF/views/userlogin";
        }
    }

    @RequestMapping(value="/usersignincheck",method = RequestMethod.GET)
    public String usersignincheck(@RequestParam("username") String username,
                                  @RequestParam("password") String password,
                                  @RequestParam("confirmpassword") String confirmpassword,
                                  Model model){
        if(confirmpassword.equals(password)){
            userInfoMapper.insertSelective(new UserInfo(username,null,password));
            return "index";
        }
        else{
            model.addAttribute("message","password is wrong!");
            return "WEB-INF/views/usersigninpage";
        }
    }

    @RequestMapping(value="/backtouserpage/{userid}",method = RequestMethod.GET)
    public String backtouserpage(@PathVariable(value="userid") Integer userid, Model model) {
        model.addAttribute("userid",userid);
        return "WEB-INF/views/userpage";
    }

}
