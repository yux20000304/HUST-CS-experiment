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
import yyx.dao.BillsMapper;
import yyx.entity.Book;
import yyx.entity.UserInfo;
import yyx.service.BillService;
import yyx.service.BookService;
import yyx.service.UserService;

import java.util.List;

@Controller
public class FindBookInfoController {
    @Autowired
    BookService bookService;


    @RequestMapping("/findbookinfo/{userid}/{pn}")
    public String getBookInfo(@PathVariable(value="pn")Integer pn,@PathVariable(value="userid") Integer userid,
                          Model model){
        //非常多的记录，需要分页
        //引入page helper插件
        //在查询之前只需要调用
        PageHelper.startPage(pn, 5);
        System.out.println(userid);
        List<Book> users = bookService.getuserbook(userid);
        //包装查询后的结果
        //封装了详细的信息，包括查询出来的数据，连续传入5页
        PageInfo page=new PageInfo(users,5);
        model.addAttribute("pageInfo",page);
        model.addAttribute("userid",userid);
        return "WEB-INF/views/bookinfomation";
    }

    @RequestMapping("/gotocancelbook/{userid}/{pn}")
    public String gotocancelBook(@PathVariable(value="pn")Integer pn, @PathVariable(value="userid") Integer userid, Model model){
        PageHelper.startPage(pn, 5);

        List<Book> users = bookService.getuserbook(userid);
        //包装查询后的结果
        //封装了详细的信息，包括查询出来的数据，连续传入5页
        PageInfo page=new PageInfo(users,5);
        model.addAttribute("pageInfo",page);
        model.addAttribute("userid",userid);
        return "WEB-INF/views/cancelbookinfomation";
    }


    @RequestMapping(value="/cancelbook/{userid}",method= RequestMethod.GET)
    public String cancelbookInfo(@RequestParam(value="cancelid") Integer cancelid, @PathVariable(value="userid") Integer userid,Model model){
        bookService.cancelbook(cancelid);
        model.addAttribute("userid",userid);
        return "WEB-INF/views/userpage";
    }

}
