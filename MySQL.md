## MySQL

### 1、连接数据量

```mysql
mysql -u username -p
```

输入命令后回车，显示Enter password:    输入密码即可。

username登录时使用的用户名

### 2、创建数据库

```mysql
create database databaseName
```

databaseName:需要创建的数据库名。

### 3、删除数据库

```mysql
drop database databaseName
```

databaseName:需要删除的数据库名。

### 4、选择数据库

```mysql
use databaseName
```

databaseName：想要使用的数据库名。

### 5、创建数据表

```mysql
create table tableName(column_name column_type);
```

tableName:需要创建的数据表名

column_name:创建表中的列名

column_type:创建表中的列数据类型

实例：

```mysql
create table if not exists Device_Type(
    Device_id int auto_increment,
    Device_name varchar(64) not null,
    Device_typenum varchar(24) not null,
    Device_date datetime，
    primary key(Device_id)
) default charset=utf8;
```

```mysql
create table if not exists Consumables_Type(
    Consumable_id int auto_increment,
    Consumable_name varchar(64) not null,
    Consumable_typenum varchar(24) not null,
    Consumable_date datetime,
    primary key(Consumable_id)
) default charset=utf8;
```

```mysql
create table if not exists Types_Num(
    Type_id int auto_increment,
    Type_Num varchar(24) not null,
    Type_date datetime,
    primary key(Type_id)
)default charset=utf8;
```



* auto_increment定义列自增属性，一般用于主键，数值会自动增加1
* primary key用于定义该列为主键，可以使用多列来定义主键,列间以逗号分隔
* charset设置编码
* 如果不想字段为null，设置该字段属性为not null, 在操作数据库时如果该字段为null，则会报错。

### 6、删除数据表

```mysql
drop table tableName
```

tableName:需要删除的数据表名

### 7、插入数据

```mysql
insert into tableName(field1, field2,...fieldN) values(value1, value2,...valueN )
```

tableName:需要插入数据的表名

filed1...fieldN:需要插入数据的表列名

value1...valueN:需要插入的数据。

实例：

```mysql
insert into Device_type
(Device_name, Device_typenum, Device_date) 
values
("Genie", "001", NOW());
```

```mysql
insert into Types_Num
(Type_Num, Type_date)
values("001", NOW()),("002", NOW()), ("003", NOW());
```



NOW() 函数返回当前系统的日期和时间。

### 8、查询数据

```mysql
select column_name1, column_name2, ...column_nameN from tableName 
[where condition]
[limit N][offset M]
```

* where 语句来包含筛选条件
* limit 属性来设定返回的记录数
* offset 指定select语句开始查询的数据偏移量,默认情况下偏移量为0
* 使用* 代替字段，将返回所有字段的值。

实例

```mysql
select * from Device_Type where Device_typenum = '0001' limit 5 offset 1;
```

只返回唯一的不同值。

```mysql
select distinct column_name1, column_name2, ...column_nameN from tableName 
[where condition]
[limit N][offset M]
```



### 9、where子句

```mysql
select field1, field2, ...fieldN from tableName1, tableName2
[where condition1 [and[or]] condition2];
```

* 查询语句中可以一次查询一个或多个表，表名之间用（,）分隔。
* 查询语句中可以使用where来设定查询条件
* 可以使用and（与）或or（或）来连接多个查询条件
* where子句也可以用于delete、update等命令语句

实例：

```mysql
select * from Device_Type where Device_typenum = '005' or Device_id < 2;
```

### 10、update更新

```mysql
update tableName set field1 = 'newvalue1', field2 = 'newvalue2' 
[where condition]
```

* 可以一次更新一个字段或多个字段的值

实例：

```mysql
update Device_Type set Device_typenum = '0002' 
where Device_id > 6 and  Device_typenum = '005';
```

### 11、delete语句

```mysql
delete from tableName [where condition];
```

* 如果没有where子句，则会删除表中所有的数据。

实例：

```mysql
delete from Device_Type where Device_id > 8;
```

### 12、like语句

```mysql
select field1, field2,...fieldN from tableName
where like condition;
```

* 可以在where子句中使用like子句
* 可以使用like子句代替等号=
* like通常与%一起使用，类似于一个元字符的搜索

实例：

```mysql
update Device_Type set Device_name = 'SuperGenie' where Device_name like 'DP%';
```

补充：

### 13、union操作符

MySQL union操作符用于连接两个及以上的select语句，将结果组合到一个结果集中。

```mysql
select field1, field2,... fieldN from tableName1
[where condition]
union [all | distinct]
select field1, field2,... fieldN from tableName2
[where condition]
```

distinct: 可选，删除结果集中的重复数据。默认情况下union已经删除了重复数据，所有distinct对结果没有影响

all: 可选，返回结果集中的所有数据，包括重复的数据。

实例：

```mysql
select Device_typenum from Device_Type
union all 
select Consumable_typenum from Consumables_Type;
```

### 14、MySQL排序

```mysql
select field1, field2, ... fieldN from tableName
order by fieldX ASC | DESC;
```

* ASC  升序
* DESC 降序

实例

```mysql
select * from Device_Type order by Device_id desc;
```

### 15、分组

```mysql
select field, function(field) from tableName 
[where condition]
group by field;
```

function(): SQL 函数

实例：

```mysql
select Consumable_name, COUNT(*) from Consumables_Type group by Consumable_name;
```

```mysql
select Consumable_name, COUNT(*) as count from Consumables_Type group by Consumable_name;
```

* as 起别名

使用with rollup：可以在实现在分组统计的基础上再进行相同的统计

```mysql
select Consumable_name, COUNT(*) as count from Consumables_Type group by Consumable_name with rollup;
```

返回中的NULL则为统计的总和。

```mysql
select coalesce(Consumable_name, "total") as name, COUNT(*) as count from Consumables_Type group by Consumable_name with rollup;
```

### 16、连接的使用

#### 1、inner join（内连接或等值连接）

获取两个表中字段匹配关系的记录

```mysql
select tableName1.field1, tableName1.field2, tableName2.field1 from tableName1
inner join tableName2
on tableName1.filed = tableName2.filed;
```

实例：

```mysql
select Consumables_Type.Consumable_id, Consumables_Type.Consumable_date, Types_Num.Type_Num from Consumables_Type
inner join Types_Num
on Consumables_Type.Consumable_typenum = Types_Num.Type_Num;
```



#### 2、left join(左连接)

获取左表中的所有记录，即使右表中没有匹配关系的记录

实例：

```mysql
select Consumables_Type.Consumable_id, Consumables_Type.Consumable_date, Types_Num.Type_Num from Consumables_Type
left join Types_Num
on Consumables_Type.Consumable_typenum = Types_Num.Type_Num;
```



#### 3、right join(右连接)

获取右表中的所有记录，即使左表中没有匹配关系的记录

实例：

```mysql
select Consumables_Type.Consumable_id, Consumables_Type.Consumable_date, Types_Num.Type_Num from Consumables_Type
right join Types_Num
on Consumables_Type.Consumable_typenum = Types_Num.Type_Num;
```

### 17、NULL值处理

* is null: 当列的值是 NULL,此运算符返回 true
* is not null:当列的值不为NULL时，运算符返回true

实例：

```mysql
insert into Types_Num (Type_Num) values("004"), ("007"), ("008");
```

使用以下语句查询表Types_Num中Type_date字段为null的数据。

```
select * from Types_Num where Type_date = NULL;
```

执行上述语句会返回“empty set”。

正确的查询方式如下：

```mysql
select * from Types_Num where Type_date is null;
```

### 18、事务

MySQL 事务主要用于处理操作量大，复杂度高的数据。比如说要删除某个产品的信息，这个产品的信息可能存在于多个表中，这需要删除每个表中该产品相关的信息，如果有某个表中信息没有成功删除，这可能就造成整个产品信息库错误，因此对于该产品的信息要么全部彻底删除，要么一个都不删除。

- 在 MySQL 中只有使用了 Innodb 数据库引擎的数据库或表才支持事务。
- 事务处理可以用来维护数据库的完整性，保证成批的 SQL 语句要么全部执行，要么全部不执行。
- 事务用来管理 insert,update,delete 语句

事务控制语句：

* begin或 start transaction 显示的开启一个事务。
* commit或commit work提交事务，使对数据库的修改变成永久性的。
* rollback或rollback work回滚会结束用户的事务，并撤销正在进行的所有未提交的修改
* savepoint *identifier*，savepoint 允许在事务中创建一个保存点，一个事务中可以有多个 savepoint
* release savepoint  *identifier*  删除一个事务的保存点，保存点不存在时，执行该语句会抛出一个异常
* rollback to  *identifier* 把事务回滚到保存点, 保存点不存在时，执行该语句会抛出一个异常
* set transaction 用来设置事务的隔离级别

##### 事务处理主要有两种方法

###### 1、用 BEGIN, ROLLBACK, COMMIT来实现

- **begin** 开始一个事务
- **rollback** 事务回滚
- **commit**事务确认

###### 2、直接用 SET 来改变 MySQL 的自动提交模式:

* **set autocommit**=0 禁止自动提交
* **set autocommit**=1 开启自动提交。

**在 MySQL 命令行的默认设置下，事务都是自动提交的，即执行 SQL 语句后就会马上执行 COMMIT 操作。因此要显式地开启一个事务务须使用命令 BEGIN 或 START TRANSACTION，或者执行命令 SET AUTOCOMMIT=0，用来禁止使用当前会话的自动提交**

### 19、alter命令

alter table语句用于在已有表中添加、删除或修改列。

* 增加字段

```mysql
alter table tableName add fieldName datatype
```

在名为tableName的表中，增加一个名为fieldName的字段，数据类型为datatype.

实例：

```mysql
alter table Types_Num add Type_msg varchar(64);
```



* 删除字段

```mysql
alter table tableName drop fieldName
```

在名为tableName的表中，删除名为fieldName的字段。

实例：

```mysql
alter table Types_Num drop Type_msg;
```

* 修改字段

如果需要修改字段类型及名称, 可以在alter命令中使用 modify或 change 子句 。

```mysql
alter table tableName modify fieldName newdatatype;
```

在名为tableName的表中，将名为fieldName的字段的数据类型修改为newdatatype。

实例：

```mysql
alter table Types_Num modify Type_msg char(128);
```

使用 change 子句, 在 change关键字之后，紧跟着的是你要修改的字段名，然后指定新字段名及类型

```mysql
alter table tableName change oldfield newfield datatype
```

在名为tableName的表中，将名为oldfield的字段修改为名为newfield，数据类型为datatype的字段。

实例：

```mysql
alter table Types_Num change Type_msg Type_message varchar(128);
```

* 新增加字段并设置默认值

实例：

```mysql
alter table Types_Num add Type_msg varchar(64) not null default "unknow"
```

* 修改表名

```mysql
alter table oldTablName rename to newTableName
```

实例：

```mysql
alter table Types_Num rename to Types_Serial;
```

### 20、索引

#### 1、普通索引

##### 创建索引

```mysql
create index indexName on tableName(fieldName(length));
```

indexName:索引名

tableName:表名

fieldName:列名

如果是CHAR，VARCHAR类型，length可以小于字段实际长度；如果是BLOB和TEXT类型，必须指定 length。

##### 修改表结构添加索引

```mysql
alter table tableName add index indexName(fieldName);
```

##### 创建表时创建索引

```mysql
create table tableName(
    ID int not null,
    fieldName varchar(24) not null,
    index[indexName](fieldName(length))
);
```

##### 删除索引

```mysql
drop index [indexName] on tableName
```

#### 2、唯一索引

##### 创建索引

```mysql
create unique index indexName on tableName(fieldName(length));
```



##### 修改表结构添加索引

```mysql
alter table tableName add unique index indexName(fieldName);
```



##### 创建表时创建索引

```mysql
create table tableName(
    ID int not null,
    fieldName varchar(24) not null,
    unique[indexName](fieldName(length))
);
```

### 3、显示索引信息

```mysql
show index from tableName;
```

### 21、临时表

MySQL临时表在只在当前连接下有效，连接断开后临时表会自动删除。当使用脚本语言或客户端连接MySQL创建临时表时，脚本运行结束或客户端关闭，则临时表删除。

```mysql
create temporary table tableName(
);
```

使用

```mysql
show tables;
```

不会显示临时表信息。

### 22、复制表

#### 1、方法1

```mysql
create table newTableName();
```

```mysql
insert into newTableName (field1, field2, ...fiedlN)
select field1, field2, ...fiedlN from oldTableName
```



#### 2、方法2

```mysql
create table newTableName like oldTableName; #只复制表结构
insert into newTableName select * from oldTableName; #复制表中的数据
```

#### 