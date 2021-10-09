// pages/wrong/wrong.js
const app = getApp()
Page({
  data: {
    result: (app.globalData.x - app.globalData.y),
    cnt: app.globalData.counter,
    maxtime: app.globalData.maxtime,
    answer: app.globalData.answer,
  },
  onShow() {
    this.setData({
      result: app.globalData.x - app.globalData.y,
      cnt: app.globalData.counter,
      answer: app.globalData.answer,
    })
  },
  jmp() {
    wx.redirectTo({
      url: '../../sub/sub',
    })
  },
  jmphome() {
    app.globalData.counter = 1;
    app.globalData.answer = false;
    app.globalData.diff = 0;
    app.globalData.type = 0;
    wx.reLaunch({
      url: '../../../home/home',
    })
  },
})