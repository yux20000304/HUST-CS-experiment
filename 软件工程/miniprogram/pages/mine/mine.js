// pages/mine/mine.js
const app = getApp()
const db = wx.cloud.database()
const scoreCollection = db.collection("score")
Page({
  data: {
    userInfo: {},
    haslogged: false,
    userscore: app.globalData.usersrecord.maxrecord,
    message:{},
    score:{}
  },

  hdlclick(res) {
    this.setData({
      userInfo: res.detail.userInfo,
      haslogged: true
    })
    console.log(res.detail.userInfo);
    // this.debug();
  },

  addData: function(event) {
    console.log(event);
    // console.log("ADDDATA");
    scoreCollection.add({
      data: {
        username: this.data.userInfo.nickName,
        score: 1,
        image: this.data.userInfo.avatarUrl
      }
    }).then(res => {
      console.log(res)
    })
  },
  // addData: function (event) {
  //   wx.cloud.callFunction({
  //     name: "addData"
  //   }).then(res => {
  //     console.log(1)
  //   })
  // },
  exit() {
    this.setData({
      haslogged: false
    })
  },

  searchScore: function(options) {
    scoreCollection.orderBy('score', 'desc').where({
      username: this.data.userInfo.nickName, // 填入当前用户 openid
    }).get().then(res => {
      console.log(res);
      this.setData({
        score: res.data,
      })
      if(res.data[0]==null){
         this.addData();
         this.searchScore();
        // console.log(123);
      }
      else if (res.data[0].score < app.globalData.usersrecord.maxrecord) {
        // console.log(999),
        this.update(),
        this.searchScore()
      }
      else return 0;
    })
  },

  // onGetOpenid: function() {
  //   // 调用云函数
  //   wx.cloud.callFunction({
  //     name: 'login',
  //     data: {},
  //     success: res => {
  //       console.log('[云函数] [login] user openid: ', res.result.openid)
  //       app.globalData.openid = res.result.openid

  //     },
  //     fail: err => {
  //       console.error('[云函数] [login] 调用失败', err)
  //     }
  //   })
  // },
  // update:function(event){
  //   scoreCollection.doc("2c94992a5da1fd1e03877a2e7f104060").update({
  //     data:{
  //       score:10
  //     }
  //   }).then(res=>{
  //     console.log(res)
  //   })
  // }
  update: function(event) {
    // let that=this
    wx.cloud.callFunction({
      name: 'update',
      data: {
        x: app.globalData.usersrecord.maxrecord,
        y: this.data.userInfo.nickName
      },
      success: res => {
        console.log(res)
      },
      fail: err => {
        console.error('[云函数] [update] 调用失败', err)
      }
    })
    console.log(123)
  }

  // debug: function(event){
  //   wx.cloud.callFunction({
  //     name: 'hello'
  //   })
  //   console.log("call hello");
  // },
  // success: res => {
  //   console.log(res);
  //   console.log("success")
  // },
  // fail: err => {
  //   console.error('[云函数] [login] 调用失败', err)
  // }

})