# Qt操作Json

### 1、QJsonDocument

#### 1、详细说明

QJsonDocument类提供了读写JSON文档的方法。
QJsonDocument是一个封装了完整JSON文档的类，可以从基于UTF-8编码的文本或者Qt的二进制格式读写此文档。
可以使用QJsonDocument :: fromJson（）将JSON文档从其基于文本的表示转换为QJsonDocument。 toJson（）将其转换回文本。 解析器非常快速有效，并将JSON转换为Qt使用的二进制表示。
可以使用！isNull（）查询已解析文档的有效性
可以使用isArray（）和isObject（）查询文档是否包含数组或对象。 可以使用array（）或object（）检索文档中包含的数组或对象，然后进行读取或操作。
还可以使用fromBinaryData（）或fromRawData（）从存储的二进制表示创建文档。

### 2、QJsonArray

#### 1、详细说明

QJsonArray 类封装了一个 JSON 数组。

JSON 数组是值的列表。列表可以被操作，通过从数组中插入和删除 QJsonValue 。

一个 QJsonArray 可以和一个 QVariantList 相互转换。可以使用 size() 来查询条目的数量，通过 insert() 在指定索引处插入值，removeAt() 来删除指定索引的值。支持标准C++的迭代器。

QJsonArray是一个隐式共享类，只要它没有被修改，就会与创建它的文档共享数据。
QJsonArray对象和基于文本的JSON可以通过QJsonDocument进行相互转换。

### 3、QJsonObject

#### 1、详细说明

QJsonObject 类封装了一个 JSON 对象。

一个 JSON 对象是一个“key/value 对”列表，key 是独一无二的字符串，value 由一个 QJsonValue 表示。

一个 QJsonObject 可以和一个 QVariantMap 相互转换。可以使用 size() 来查询“key/value 对”的数量，通过 insert() 插入“key/value 对”， remove() 删除指定的 key。

QJsonObject是一个隐式共享类，只要它没有被修改，就会与创建它的文档共享数据。
QJsonObject对象和基于文本的JSON可以通过QJsonDocument进行相互转换。

### 4、QJsonParseError

#### 1、详细说明

QJsonParseError 类用于在 JSON 解析中报告错误。

### 5、QJsonValue

#### 1、详细说明

QJsonValue 类封装了一个值。

JSON 中的值有 6 种基本数据类型：

- bool（QJsonValue::Bool）
- double（QJsonValue::Double）
- string（QJsonValue::String）
- array（QJsonValue::Array）
- object（QJsonValue::Object）
- null（QJsonValue::Null）

一个值可以由任何上述数据类型表示。此外，QJsonValue 有一个特殊的标记来表示未定义的值，可以使用 isUndefined() 查询。

值的类型可以通过 type() 或 isBool()、isString() 等访问函数查询。同样地，值可以通过 toBool()、toString() 等函数转化成相应的存储类型。

与QVariant相反，不会尝试进行任何隐式类型转换。 这意味着转换为未存储在值中的类型将返回默认的构造返回值。

### 6、实例

生产一下Json文档：

```json
{
    "heartData": [
        {
            "I1": {
                "quality": 18.2,
                "temp": 25
            }
        },
        {
            "I2": {
                "quality": 2000,
                "temp": 20
            }
        },
        {
            "RO Rejection": {
                "value": 98
            }
        },
        {
            "TOC": {
                "value": 3
            }
        }
    ]
}
```

生产代码：

```c++
void DJson::clearJsonObject(QJsonObject &object)
{
    QStringList strList = object.keys();

    for(int i = 0; i < strList.size(); ++i)
    {
        object.remove(strList.at(i));
    }

}

void DJson::createJsonFile(const QString &fileName)
{
    QJsonArray jsonArray;
    QJsonObject rootObject;
    QJsonObject branchObject;
    QJsonObject leafObject;

    leafObject.insert("quality", 18.2);
    leafObject.insert("temp", 25.0);
    branchObject.insert("I1", leafObject);
    jsonArray.append(branchObject);
    clearJsonObject(leafObject);
    clearJsonObject(branchObject);

    leafObject.insert("quality", 2000);
    leafObject.insert("temp", 20.0);
    branchObject.insert("I2", leafObject);
    jsonArray.append(branchObject);
    clearJsonObject(leafObject);
    clearJsonObject(branchObject);

    leafObject.insert("value", 98);
    branchObject.insert("RO Rejection", leafObject);
    jsonArray.append(branchObject);
    clearJsonObject(leafObject);
    clearJsonObject(branchObject);

    leafObject.insert("value", 3);
    branchObject.insert("TOC", leafObject);
    jsonArray.append(branchObject);
    clearJsonObject(leafObject);
    clearJsonObject(branchObject);

    rootObject.insert("heartData", jsonArray);

    QJsonDocument jsonDocument;
    jsonDocument.setObject(rootObject);

    QByteArray byteArray = jsonDocument.toJson(QJsonDocument::Indented);

    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << QString("fail to open the file: %1, %2, %3").arg(__FILE__).arg(__LINE__).arg(__FUNCTION__);
        return;
    }
    QTextStream out(&file);
    out << byteArray;

    file.close();

    qDebug() << byteArray;
}
```

解析：

```
void DJson::initList()
{
    m_iList << "I1" << "I2" << "I3" << "I4" << "I5";
    m_vList << "RO Rejection" << "TOC";
}

void DJson::parseJsonFile(const QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << QString("fail to open the file: %1, %2, %3").arg(__FILE__).arg(__LINE__).arg(__FUNCTION__);
        return;
    }
    QByteArray array = file.readAll();
    QJsonParseError jsonParseError;
    QJsonDocument jsonDocument(QJsonDocument::fromJson(array, &jsonParseError));
    if(QJsonParseError::NoError != jsonParseError.error)
    {
        qDebug() << QString("JsonParseError: %1").arg(jsonParseError.errorString());
        return;
    }
    QJsonObject rootObject = jsonDocument.object();

    if(!rootObject.keys().contains("heartData"))
    {
        qDebug() << "No target value";
        return;
    }
    qDebug() << rootObject.keys();

    QJsonValue jsonValue = rootObject.value("heartData");
    if(!jsonValue.isArray())
    {
        qDebug() << "No target array";
    }
    QJsonArray jsonArray = jsonValue.toArray();

    for(auto iter = jsonArray.constBegin(); iter != jsonArray.constEnd(); ++iter)
    {
        parseJsonObject(iter);
    }
    qDebug() << rootObject.keys();
}

void DJson::parseJsonObject(QJsonArray::const_iterator iter)
{
    QJsonObject jsonObject = (*iter).toObject();
    for(int i = 0; i < m_iList.size(); ++i)
    {
        if(jsonObject.keys().contains(m_iList.at(i)))
        {
            parseJsonObjectI(jsonObject);
            return;
        }
    }

    for(int i = 0; i < m_vList.size(); ++i)
    {
        if(jsonObject.keys().contains(m_vList.at(i)))
        {
            parseJsonObjectV(jsonObject);
            return;
        }
    }


}

void DJson::parseJsonObjectI(QJsonObject &object)
{
    qDebug() << object.keys();
    for(int i = 0; i < object.keys().size(); ++i)
    {
        QJsonValue jsonValue = object.value(object.keys().at(i));
        if(jsonValue.isObject())
        {
            QJsonObject jsonObject = jsonValue.toObject();

            if(jsonObject.keys().contains("quality"))
            {
                qDebug() << QString("%1 : %2").arg("quality").arg(jsonObject.value("quality").toDouble());
            }
            if(jsonObject.keys().contains("temp"))
            {
                qDebug() << QString("%1 : %2").arg("temp").arg(jsonObject.value("temp").toDouble());
            }
        }
    }
    qDebug() << object.keys();
}

void DJson::parseJsonObjectV(QJsonObject &object)
{
    qDebug() << object.keys();
    for(int i = 0; i < object.keys().size(); ++i)
    {
        QJsonValue jsonValue = object.value(object.keys().at(i));
        if(jsonValue.isObject())
        {
            QJsonObject jsonObject = jsonValue.toObject();
            if(jsonObject.keys().contains("value"))
            {
                qDebug() << QString("%1 : %2").arg("value").arg(jsonObject.value("value").toInt());
            }
        }
    }
    qDebug() << object.keys();
}

```

