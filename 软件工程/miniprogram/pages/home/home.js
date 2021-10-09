const app = getApp()

Page({
  jumpdiff() {
    wx.redirectTo({
      url: '../diff/diff',
    })
  },
  jumpadd(){
    app.globalData.type = 1;  //1代表加法，2代表减法，
    this.jumpdiff();
  },
  jumpsub(){
    app.globalData.type = 2;
    this.jumpdiff();
  },
  jumpmul() {
    app.globalData.type = 3;
    this.jumpdiff();
  },
  jumpdiv() {
    app.globalData.type = 4;
    this.jumpdiff();
  },
  jumpmix(){
    wx.redirectTo({
      url: '../maths/mix/mix',
    })
  }
})