// pages/maths/mix/mix.js
const app = getApp()
Page({
  data: {
    NUM: Math.floor(Math.random() * 3) + 3, //代表参与运算的数的个数
    list: [],          //保存参与运算的数，随机生成
    operater: ["+", "-", "x", "÷"],
    eql: [],     //生成的随机算式保存在此列表中
    result: 0,
    result_str: '',
    answer: app.globalData.answer,
    counter: app.globalData.counter,
    maxtime: app.globalData.maxtime,
    record: app.globalData.usersrecord.record,
    timer: 'clock', //定时器名字
    countDownNum: '60' //倒计时初始值
  },
  onShow() {
    //生命周期函数，当页面每展示时执行一次。
    console.log(this.data.NUM)

    this.setData({
      counter: app.globalData.counter,
      maxtime: app.globalData.maxtime,
      NUM: Math.floor(Math.random() * 3) + 3, 
}),
    this.generate(this.data.NUM);
    this.equation(this.data.NUM);
    this.setData({
      result: this.getResult(this.data.eql, this.data.NUM),
      record: app.globalData.usersrecord.record,
    }),
    app.globalData.counter = app.globalData.counter + 1;
    app.globalData.mixrsl = this.data.result;

    this.countDown();
  },

  generate(NUM) { //生成相应个数的随机数用以参与运算
    for (var i = 0; i < NUM; i++) {
      var temp = 'list[' + i + ']';
      this.setData({
        [temp]: Math.floor(Math.random() * 100) + 1
      })
    }
  },

  equation(NUM) {
    var i = 0,
      j = 0;
    var tmp = 'eql[' + i + ']';
    this.setData({
      [tmp]: this.data.list[j]
    })
    i++;
    for (; i < 2 * NUM - 2; i++) {
      tmp = 'eql[' + i + ']';
      this.setData({
        [tmp]: this.data.operater[Math.floor(Math.random() * 4)]
      });
      i = i + 1;
      //将参与运算的数据保存到eql列表
      tmp = 'eql[' + i + ']';
      j++;
      //将运算符保存到eql列表
      this.setData({
        [tmp]: this.data.list[j],
      })
    }
    //算式生成完毕，存储在eql[]中
  },
  getResult(eql, NUM) {
    //求值函数
    var result = 0;  //用以保存结果的局部变量
    var temp = new Array;
    var j = 0;
    //大致思路：根据运算的优先级来进行运算，先将乘除运算计算完毕，
    //生成一个只剩加减的算式
    for (var i = 1; i < 2 * NUM - 1; i += 2) {
      if (eql[i] == "x") {
        //碰到乘法就对前一个符号进行检验，如果不是除法就将该
        //乘号左边的数保存到临时列表中，准备进行乘法运算，如果是除法就将
        //直接将计数变量减1，以之前的除法运算结果作为临时值进行乘法运算
        if (eql[i - 2] != "÷") {
          temp[j] = eql[i - 1];
        }
        else {
          j--;
        }
        temp[j] = temp[j] * eql[i + 1];
        while (eql[i + 2] == "x" && i + 2 < 2 * NUM - 1) {
          i += 2;
          temp[j] = temp[j] * eql[i + 1]
        }
        j++;
        continue;
      }
      //除法思路与乘法大致相同
      else if (eql[i] == "÷") {
        if (eql[i - 2] != "x") {
          temp[j] = eql[i - 1];
        }
        else {
          j--;
        }
        temp[j] = temp[j] / eql[i + 1]
        while (eql[i + 2] == "÷" && i + 2 < 2 * NUM - 1) {
          i += 2;
          temp[j] = temp[j] / eql[i + 1]
        }
        j++;
        continue;
      }
      //碰到加减法，就进行适当的判断后将值保存在临时列表中
      else if (eql[i] == "+" || eql[i] == "-") {
        if (eql[i - 2] == "+" || eql[i - 2] == "-" || i - 2 <= 0) {
          temp[j++] = eql[i - 1];
        }
        temp[j++] = eql[i];
        if (i + 2 >= 2 * NUM - 1) {
          temp[j++] = eql[i + 1];
        }
        continue;
      }
    }
    console.log(temp)
    //计算处理得到的仅包含加减运算的算式
    result = temp[0];
    for (var i = 1; i < j; i += 2) {
      if (temp[i] == "+") {
        result = result + temp[i + 1];
      } else if (temp[i] == "-") {
        result = result - temp[i + 1];
      }
    }
    return parseInt(result);//对结果进行取整处理
  },

  InputValue(res) {
    this.setData({
      result_str: res.detail.value,
    })
  },

  SURE() {
    //判断结果是否正确的函数
    if (parseInt(this.data.result_str) == this.data.result) {
      app.globalData.answer = true,
      app.globalData.usersrecord.record += 1 
    } else {
      app.globalData.answer = false
    }
    this.setData({
      answer: app.globalData.answer,
    })
    clearInterval(this.data.timer);
    //获得结果后跳转至结果显示页面
    this.jmpans();
  },
  jmpans: function() {
    wx.redirectTo({
      url: '../mix/answer/answer',
    })
  },

  countDown: function() {
    let that = this;
    let countDownNum = that.data.countDownNum;
    that.data.timer = setInterval(function() {
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