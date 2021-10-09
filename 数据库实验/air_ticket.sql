drop database air_ticket_book_management;

create database air_ticket_book_management;

use air_ticket_book_management;

-- 表一 管理员信息表
create table manager(
	id int unique,
    Username char(20) primary key,
    Password char(20)
);
-- 表二 用户信息表
create table user_info(
	id int unique auto_increment,
    Username char(20) primary key,
    Password char(20)
);
-- 表三 账单表
create table bills(
	id int primary key auto_increment,
    P_id int,
    Pay int,
    constraint person_bill foreign key (P_id) references user_info(id) ON DELETE CASCADE ON UPDATE CASCADE
);

-- 表六 航班信息表
create table air_info(
	id char(20) primary key,
    Takeoff_time datetime,
    Arrive_time datetime,
    origin_stat char(20),
    Term_stat char(20),
    price int,
    bookedseats int,
    totalseats int
);

-- 表四 订单表
create table book(
	id int primary key auto_increment,
    P_id int,
    Air_info char(20),
    Booktime datetime,
    Price int,
    constraint air_num foreign key (Air_info) references air_info(id),
    constraint person_book foreign key (P_id) references user_info(id) ON DELETE CASCADE ON UPDATE CASCADE
);
-- 表五 取票通知表
create table withdraw_ticket(
	id int primary key auto_increment,
    P_id int,
    Book_id int,
    Withdraw bool,
    constraint booknumber foreign key (Book_id) references book(id),
	constraint personnumber foreign key (P_id) references user_info(id) ON DELETE CASCADE ON UPDATE CASCADE
);

-- 表七 航班座位表
create table air_seat(
	id int primary key auto_increment,
    Flight_id char(20),
    Seatnum int,
    constraint flightid foreign key (Flight_id) references air_info(id) 
);

set global time_zone='+8:00';

DELIMITER $$
create trigger insert_book
after insert
on book
for each row
begin
    insert into bills(P_id,Pay) values(new.P_id,new.Price);
    insert into withdraw_ticket(P_id,Book_id,Withdraw) values(new.P_id,new.id,false);
	insert into air_seat(Flight_id) values(new.Air_info);
end;$$

DELIMITER ;


