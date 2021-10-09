// pages/list/list.js
const db = wx.cloud.database()
const scoreCollection = db.collection("score")
Page({

  /**
   * 页面的初始数据
   */
  data: {

  },
  onShow: function(options) {
    scoreCollection.orderBy('score', 'desc').get().then(res => {
      console.log(res);
      // console.log(2);
      this.setData({
        score: res.data
      })
    })
  },
})