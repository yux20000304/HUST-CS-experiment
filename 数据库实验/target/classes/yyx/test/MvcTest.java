package yyx.test;


import com.github.pagehelper.PageInfo;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.mock.web.MockHttpServletRequest;
import org.springframework.test.context.ContextConfiguration;
import org.springframework.test.context.junit4.SpringJUnit4ClassRunner;
import org.springframework.test.context.web.WebAppConfiguration;
import org.springframework.test.web.servlet.MockMvc;
import org.springframework.test.web.servlet.MvcResult;
import org.springframework.test.web.servlet.request.MockMvcRequestBuilders;
import org.springframework.test.web.servlet.setup.MockMvcBuilders;
import org.springframework.web.context.WebApplicationContext;
import yyx.entity.UserInfo;

import java.util.List;

@RunWith(SpringJUnit4ClassRunner.class)
@WebAppConfiguration
@ContextConfiguration(locations = {"classpath:applicationContext.xml","file:E:/课程/数据库/demo/Database_project/src/main/webapp/WEB-INF/dispatcher-servlet.xml"})
public class MvcTest {

    @Autowired
    WebApplicationContext context;
    //虚拟mvc请求
    MockMvc mockMvc;

    @Before
    public void initMockMvc(){
        mockMvc = MockMvcBuilders.webAppContextSetup(context).build();
    }

    @Test
    public void testPage() throws Exception {
        //模拟请求，拿到返回值
        MvcResult result=mockMvc.perform(MockMvcRequestBuilders.get("/users")
                .param("pn","1")).andReturn();
        //请求成功之后，请求域中有pageinfo
        MockHttpServletRequest request=result.getRequest();
        PageInfo pi= (PageInfo) request.getAttribute("pageInfo");
        System.out.println("当前页码："+pi.getPageNum());
        System.out.println("总页码："+pi.getPages());
        System.out.println("总记录数："+pi.getTotal());
        System.out.println("在页面需要连续显示的页码：");

        int[] nums=pi.getNavigatepageNums();
        for(int i:nums){
            System.out.println(" "+i);
        }

        //获取员工数据
        List<UserInfo> list=pi.getList();
        for(UserInfo userInfo:list){
            System.out.println(userInfo.toString());
        }
    }
}
