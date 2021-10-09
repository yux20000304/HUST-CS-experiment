// maths.js
const app = getApp()
Page({
  data: {
    counter:app.globalData.counter,
    maxtime:app.globalData.maxtime,
    x: app.globalData.x,
    y: app.globalData.y,
    result: '',
    answer: app.globalData.answer,

   timer: 'clock',//定时器名字
    countDownNum: '10' //倒计时初始值
  },
  onShow() {
    app.globalData.x = Math.floor(Math.random() * Math.pow(10, app.globalData.diff));
    app.globalData.y = Math.floor(Math.random() * Math.pow(10, app.globalData.diff));
    this.setData({
      x: app.globalData.x,
      y: app.globalData.y,
      counter: app.globalData.counter,
      maxtime: app.globalData.maxtime,
    })
    app.globalData.counter = app.globalData.counter + 1;

    this.countDown();
  },
  InputValue(res) {
    this.setData({
      result: res.detail.value,
    })
  },
  SURE() {
    if (parseInt(this.data.result) == (this.data.x + this.data.y)) {
      app.globalData.answer = true
    } else {
      app.globalData.answer = false
    }
    this.setData({
      answer: app.globalData.answer,
    })
    clearInterval(this.data.timer);
    this.jmpans();
  },
  jmpans: function() {
    wx.redirectTo({
      url: '../add/answer/answer',
    })
  },
  countDown: function () {
    let that = this;
    let countDownNum = that.data.countDownNum;
    that.data.timer = setInterval(function () {
      if (countDownNum == 0) {
        console.log("again");
        clearInterval(that.data.timer);
        that.jmpans();
      } else {
        countDownNum--;
        that.setData({
          countDownNum: countDownNum
        })
      }
    }, 1000)
  },
})