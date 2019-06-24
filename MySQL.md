## MySQL

### 1、连接数据量

```sql
mysql -u username -p
```

输入命令后回车，显示Enter password:    输入密码即可。

username登录时使用的用户名

### 2、创建数据库

```sql
create database databaseName
```

databaseName:需要创建的数据库名。

### 3、删除数据库

```sql
drop database databaseName
```

databaseName:需要删除的数据库名。

### 4、选择数据库

```sql
use databaseName
```

databaseName：想要使用的数据库名。

### 5、创建数据表

```sql
create table tableName(column_name column_type);
```

tableName:需要创建的数据表名

column_name:创建表中的列名

column_type:创建表中的列数据类型

实例：

```sql
create table if not exists Device_Type(
    Device_id int auto_increment,
    Device_name varchar(64) not null,
    Device_typenum varchar(24) not null,
    Device_date datetime，
    primary key(Device_id)
) default charset=utf8;
```

* auto_increment定义列自增属性，一般用于主键，数值会自动增加1
* primary key用于定义该列为主键，可以使用多列来定义主键,列间以逗号分隔
* charset设置编码
* 如果不想字段为null，设置该字段属性为not null, 在操作数据库时如果该字段为null，则会报错。

### 6、删除数据表

```sql
drop table tableName
```

tableName:需要删除的数据表名

### 7、插入数据

```sql
insert into tableName(field1, field2,...fieldN) values(value1, value2,...valueN )
```

tableName:需要插入数据的表名

filed1...fieldN:需要插入数据的表列名

value1...valueN:需要插入的数据。

实例：

```sql
insert into Device_type
(Device_name, Device_typenum, Device_date) 
values
("Genie", "001", NOW());
```

NOW() 函数返回当前系统的日期和时间。

### 8、查询数据

```sql
select column_name1, column_name2, ...column_nameN from tableName 
[where condition]
[limit N][offset M]
```

* where 语句来包含筛选条件
* limit 属性来设定返回的记录数
* offset 指定select语句开始查询的数据偏移量,默认情况下偏移量为0
* 使用* 代替字段，将返回所有字段的值。

实例

```sql
select * from Device_Type where Device_typenum = '0001' limit 5 offset 1;
```

### 9、where子句

```sql
select field1, field2, ...fieldN from tableName1, tableName2
[where condition1 [and[or]] condition2];
```

* 查询语句中可以一次查询一个或多个表，表名之间用（,）分隔。
* 查询语句中可以使用where来设定查询条件
* 可以使用and（与）或or（或）来连接多个查询条件
* where子句也可以用于delete、update等命令语句

实例：

```sql
select * from Device_Type where Device_typenum = '005' or Device_id < 2;
```

### 10、update更新

```sql
update tableName set field1 = 'newvalue1', field2 = 'newvalue2' 
[where condition]
```

* 可以一次更新一个字段或多个字段的值

实例：

```sql
update Device_Type set Device_typenum = '0002' 
where Device_id > 6 and  Device_typenum = '005';
```

### 11、delete语句

```sql
delete from tableName [where condition];
```

* 如果没有where子句，则会删除表中所有的数据。

实例：

```sql
delete from Device_Type where Device_id > 8;
```

### 12、like语句

```sql
select field1, field2,...fieldN from tableName
where like condition;
```

