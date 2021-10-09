//app.js
App({
  onLaunch: function () {
    
    if (!wx.cloud) {
      console.error('请使用 2.2.3 或以上的基础库以使用云能力')
    } else {
      wx.cloud.init({
        // env 参数说明：
        //   env 参数决定接下来小程序发起的云开发调用（wx.cloud.xxx）会默认请求到哪个云环境的资源
        //   此处请填入环境 ID, 环境 ID 可打开云控制台查看
        //   如不填则使用默认环境（第一个创建的环境）
        // env: 'my-env-id',
        //测试号：1.1.1
        env: "cloudfunctions-8gaey69hfaa4218d",
        traceUser: true,
      })
    }
  },
    globalData: {
    userinfo: null,    
    x: Math.floor(Math.random() * 100),
    y: Math.floor(Math.random() * 100),   //参与运算的随机数
    counter: 1,     //计数变量用于保存已经做的题目数
    maxtime: 10,    //每轮最大做题数
    answer: false,   //答案是否正确的变量
    diff: 0,         //难度选择
    type: 0,         //选择的运算类型
    mixrsl: 0,       //混合运算的结果
    usersrecord:{
      record: 0,
      maxrecord:0
    },

  }
})
