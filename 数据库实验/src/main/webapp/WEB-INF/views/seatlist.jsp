<%--
  Created by IntelliJ IDEA.
  User: admin
  Date: 2021/6/15
  Time: 14:37
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>
<html>
<head>
    <title>用户列表</title>

    <%
        pageContext.setAttribute("APP_PATH", request.getContextPath());
    %>


    <script src="${APP_PATH}/static/js/jquery-3.1.1.js"></script>
    <link href="${APP_PATH}/static/bootstrap-3.3.7-dist/css/bootstrap.min.css" rel="stylesheet">
    <script src="${APP_PATH}/static/bootstrap-3.3.7-dist/js/bootstrap.min.js"></script>

    <style>

        /*
 * Base structure
 */

        /* Move down content because we have a fixed navbar that is 50px tall */
        body {
            padding-top: 50px;
        }


        /*
         * Global add-ons
         */

        .sub-header {
            padding-bottom: 10px;
            border-bottom: 1px solid #eee;
        }

        /*
         * Top navigation
         * Hide default border to remove 1px line.
         */
        .navbar-fixed-top {
            border: 0;
        }

        /*
         * Sidebar
         */

        /* Hide for mobile, show later */
        .sidebar {
            display: none;
        }
        @media (min-width: 768px) {
            .sidebar {
                position: fixed;
                top: 51px;
                bottom: 0;
                left: 0;
                z-index: 1000;
                display: block;
                padding: 20px;
                overflow-x: hidden;
                overflow-y: auto; /* Scrollable contents if viewport is shorter than content. */
                background-color: #f5f5f5;
                border-right: 1px solid #eee;
            }
        }

        /* Sidebar navigation */
        .nav-sidebar {
            margin-right: -21px; /* 20px padding + 1px border */
            margin-bottom: 20px;
            margin-left: -20px;
        }
        .nav-sidebar > li > a {
            padding-right: 20px;
            padding-left: 20px;
        }
        .nav-sidebar > .active > a,
        .nav-sidebar > .active > a:hover,
        .nav-sidebar > .active > a:focus {
            color: #fff;
            background-color: #428bca;
        }


        /*
         * Main content
         */

        .main {
            padding: 20px;
        }
        @media (min-width: 768px) {
            .main {
                padding-right: 40px;
                padding-left: 40px;
            }
        }
        .main .page-header {
            margin-top: 0;
        }


        /*
         * Placeholder dashboard ideas
         */

        .placeholders {
            margin-bottom: 30px;
            text-align: center;
        }
        .placeholders h4 {
            margin-bottom: 0;
        }
        .placeholder {
            margin-bottom: 20px;
        }
        .placeholder img {
            display: inline-block;
            border-radius: 50%;
        }


    </style>


</head>
<body>

<nav class="navbar navbar-inverse navbar-fixed-top">
    <div class="container-fluid">
        <div class="navbar-header">
            <button type="button" class="navbar-toggle collapsed" data-toggle="collapse" data-target="#navbar" aria-expanded="false" aria-controls="navbar">
                <span class="sr-only">Toggle navigation</span>
                <span class="icon-bar"></span>
                <span class="icon-bar"></span>
                <span class="icon-bar"></span>
            </button>
            <a class="navbar-brand" href="#">机票预订系统</a>
        </div>
        <div id="navbar" class="navbar-collapse collapse">
            <ul class="nav navbar-nav navbar-right">
                <li><a herf="#"> 你好，用户${userid}</a></li>
                <li><a href="/logout">退出用户登录</a></li>
                <li><a href="/helpcontrol">帮助</a></li>
            </ul>
            <form class="navbar-form navbar-right">
                <input type="text" class="form-control" placeholder="Search...">
            </form>
        </div>
    </div>
</nav>

<div class="container-fluid">
    <div class="row">
        <div class="col-sm-3 col-md-2 sidebar">
            <ul class="nav nav-sidebar">
                <li class="active"><a href="#">Overview <span class="sr-only">(current)</span></a></li>
                <li><a href="/backtouserpage/${userid}">回到个人主页</a></li>
                <li><a href="#">Analytics</a></li>
                <li><a href="#">Export</a></li>
            </ul>
            <ul class="nav nav-sidebar">
                <li><a href="">Nav item</a></li>
                <li><a href="">Nav item again</a></li>
                <li><a href="">One more nav</a></li>
                <li><a href="">Another nav item</a></li>
                <li><a href="">More navigation</a></li>
            </ul>
            <ul class="nav nav-sidebar">
                <li><a href="">Nav item again</a></li>
                <li><a href="">One more nav</a></li>
                <li><a href="">Another nav item</a></li>
            </ul>
        </div>
        <div class="col-sm-9 col-sm-offset-3 col-md-10 col-md-offset-2 main">
            <h1 class="page-header">火爆的航线</h1>

            <div class="row placeholders">
                <div class="col-xs-6 col-sm-3 placeholder">
                    <img src="/images/beijing.webp" width="200" height="200" class="img-responsive" alt="Generic placeholder thumbnail">
                    <h4>第一名</h4>
                    <span class="text-muted">北京</span>
                </div>
                <div class="col-xs-6 col-sm-3 placeholder">
                    <img src="/images/shanghai.webp" width="200" height="200" class="img-responsive" alt="Generic placeholder thumbnail">
                    <h4>第二名</h4>
                    <span class="text-muted">上海</span>
                </div>
                <div class="col-xs-6 col-sm-3 placeholder">
                    <img src="/images/guangzhou.webp" width="200" height="200" class="img-responsive" alt="Generic placeholder thumbnail">
                    <h4>第三名</h4>
                    <span class="text-muted">广州</span>
                </div>
            </div>

            <h2 class="sub-header">查询结果</h2>
            <div class="table-responsive">
                <table class="table table-striped">
                    <thread>
                        <tr>
                            <th>#</th>
                            <th>航班信息</th>
                            <th>座位号</th>
                        </tr>
                        <c:forEach items="${pageInfo.list}" var="emp">
                            <tr>
                                <th> </th>
                                <th>${emp.flightId}</th>
                                <th>${emp.seatnum}</th>
                            </tr>
                        </c:forEach>
                    </thread>
                </table>
            </div>

            <%--    显示分页信息--%>
            <div class="row">
                <%--            分页文字信息--%>
                <div class="col-md-6">
                    当前第${pageInfo.getPageNum()}/${pageInfo.getPages()}页，共${pageInfo.getTotal()}条记录。
                </div>

                <%--            分页条信息--%>
                <div class="col-md-6">

                    <nav aria-label="Page navigation">
                        <ul class="pagination">
                            <li><a href="${APP_PATH}/findflightseat/${userid}/1">首页</a></li>

                            <%--                        判断是否有上一页（是否是第一页），如果是，则不显示该标签，如果不是，点击可以跳转到上一页--%>
                            <c:if test="${pageInfo.hasPreviousPage}">
                                <li>
                                    <a href="${APP_PATH}/findflightseat/${userid}/${pageInfo.pageNum - 1}" aria-label="Previous">
                                        <span aria-hidden="true">&laquo;</span>
                                    </a>
                                </li>
                            </c:if>

                            <%--                        循环遍历分页条--%>
                            <c:forEach items="${pageInfo.navigatepageNums}" var="page_num">
                                <%--                            判断页码是否等于当前页码，如果等于就让他高亮显示，并且点击无效--%>
                                <c:if test="${page_num == pageInfo.pageNum}">
                                    <li class="active"><a href="#">${page_num}</a></li>
                                </c:if>
                                <%--                            如果不等于就正常显示，点击可以正常跳转--%>
                                <c:if test="${page_num != pageInfo.pageNum}">
                                    <%--                               href="${APP_PATH}/emps?pn=${page_num}跳转到点击的页码 --%>
                                    <li><a href="${APP_PATH}/findairinfo/${userid}/${page_num}">${page_num}</a></li>
                                </c:if>
                            </c:forEach>

                            <%--                        判断是否有下一页（是否是最后一页），如果是，则不显示该标签，如果不是，点击可以跳转到下一页--%>
                            <c:if test="${pageInfo.hasNextPage}">
                                <li>
                                    <a href="${APP_PATH}/findairinfo/${userid}/${pageInfo.pageNum + 1}" aria-label="Next">
                                        <span aria-hidden="true">&raquo;</span>
                                    </a>
                                </li>
                            </c:if>

                            <li><a href="${APP_PATH}/findairinfo/${userid}/${pageInfo.pages}">尾页</a></li>
                        </ul>
                    </nav>

                </div>
            </div>
        </div>

    </div>
</div>

<!-- Bootstrap core JavaScript
================================================== -->
<!-- Placed at the end of the document so the pages load faster -->
<script src="https://code.jquery.com/jquery-1.12.4.min.js" integrity="sha384-nvAa0+6Qg9clwYCGGPpDQLVpLNn0fRaROjHqs13t4Ggj3Ez50XnGQqc/r8MhnRDZ" crossorigin="anonymous"></script>
<script>window.jQuery || document.write('<script src="../../assets/js/vendor/jquery.min.js"><\/script>')</script>
<script src="../../dist/js/bootstrap.min.js"></script>
<!-- Just to make our placeholder images work. Don't actually copy the next line! -->
<script src="../../assets/js/vendor/holder.min.js"></script>
<!-- IE10 viewport hack for Surface/desktop Windows 8 bug -->
<script src="../../assets/js/ie10-viewport-bug-workaround.js"></script>
</body>
</html>