# QT desktop application
## 第一版基本UI
## 文件夹命名规约
1. 模块文件夹名称采用大驼峰命名法
2. AppQml - 存放qml文件处
3. AppQmlBackend - 存放qml后端文件
   1. parasdbapi - 所有数据查询处, 因为查询业务不频繁, 故使用. 如有需要可改为http访问方式
5. DbEntity - 数据库实体类
6. QmlFontLoader - 程序默认样式与字体, 可忽略
## 功能以及示例
1. 提供了数据库查询等实际功能/示例, 在 parasdbapi 中
2. 提供了ModbusTCP功能/示例, 在 parasmachine 中
