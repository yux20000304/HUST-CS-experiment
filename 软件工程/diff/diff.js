// pages/diff/diff.js
const app = getApp()
Page({
  easy(){
    app.globalData.diff = 1;
    this.jmp();
  },
  normal(){
    app.globalData.diff = 2;
    this.jmp();
  },
  hard() {
    app.globalData.diff = 3;
    this.jmp();
  },

  jmp()
  {
    if(app.globalData.type == 1){
      wx.redirectTo({
        url: '../maths/add/add',
      })
    }
    else if (app.globalData.type == 2) {
      wx.redirectTo({
        url: '../maths/sub/sub',
      })
    }
    else if (app.globalData.type == 3) {
      wx.redirectTo({
        url: '../maths/mul/mul',
      })
    }
    else if (app.globalData.type == 4) {
      wx.redirectTo({
        url: '../maths/div/div',
      })
    }
  }
})