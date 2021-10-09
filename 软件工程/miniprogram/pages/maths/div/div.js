// maths.js
const app = getApp()
Page({
  data: {
    x: app.globalData.x,
    y: app.globalData.y,
    z: app.globalData.x * app.globalData.y,
    result: '',
    answer: app.globalData.answer,
    timer: 'clock', //定时器名字
    countDownNum: '10' //倒计时初始值
  },
  onShow() {
    app.globalData.x = Math.floor(Math.random() * Math.pow(10, app.globalData.diff)) + 1;
    app.globalData.y = Math.floor(Math.random() * Math.pow(10, app.globalData.diff)) + 1;
    this.setData({
      x: app.globalData.x,
      y: app.globalData.y,
      z: app.globalData.x * app.globalData.y,
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
    if (parseInt(this.data.result) == this.data.y) {
      app.globalData.answer = true
    }
    else {
      app.globalData.answer = false
    }
    this.setData({
      answer: app.globalData.answer,
    })
    clearInterval(this.data.timer);
    this.jmpans();
  },
  jmpans() {
    wx.redirectTo({
      url: '../div/answer/answer',
    })
  },
  countDown: function () {
    let that = this;
    let countDownNum = that.data.countDownNum;
    that.data.timer = setInterval(function () {
      if (countDownNum == 0) {
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