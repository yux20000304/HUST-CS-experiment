
const app = getApp()
Page({
  data: {
    result: app.globalData.mixrsl,  //将要显示的运算结果
    cnt: app.globalData.counter,
    maxtime: app.globalData.maxtime,
    answer: app.globalData.answer,
    record: app.globalData.usersrecord.record
  },
  onShow() {
    //声明周期函数
    this.setData({
      result: app.globalData.x + app.globalData.y,
      cnt: app.globalData.counter,
      answer: app.globalData.answer,
      result: app.globalData.mixrsl,
      record: app.globalData.usersrecord.record
    })
  },
  jmp() {
    wx.redirectTo({
      url: '../../mix/mix',
    })
  },
  jmphome() {
    app.globalData.counter = 1;
    app.globalData.answer = false;
    app.globalData.diff = 0;
    app.globalData.type = 0;
    if (app.globalData.usersrecord.record >= app.globalData.usersrecord.maxrecord)
    {
      app.globalData.usersrecord.maxrecord = app.globalData.usersrecord.record;
    }
    app.globalData.usersrecord.record=0;
    console.log(app.globalData.usersrecord.maxrecord)
    wx.reLaunch({
      url: '../../../home/home',
    })

  },
})