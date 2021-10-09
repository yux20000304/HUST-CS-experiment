// 云函数入口文件
const cloud = require('wx-server-sdk')

cloud.init({
  // API 调用都保持和云函数当前所在环境一致
  env: "cloudfunctions-8gaey69hfaa4218d"
})
const db=cloud.database()
// 云函数入口函数
exports.main = async (event, context) => {
sum= event.x,
signname= event.y

return await db.collection("score").where({
  username: signname
}).update({
  data:{
    score:sum,
  }
})
// return "okk";
}