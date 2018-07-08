# Panax
路线图和基本需求

1. 代码驱动的配置，全新的Panax语言
2. 支持插件扩展
3. 支持命令驱动的打包并形成可直接驱动的模型包
4. 支持多种几何文件的读取并形成统一的基于Json的数据文件，作为统一的数据交换格式，几何格式要开放，可以被其他工具方便使用
5. Json解析处理使用rapidJson，Json本身的处理使用Qt框架
6. 各种模块存在依存关系，模块之间可以作为其他模块的初始化组成部分



### 代码模型

#### 运行几何读取

| 主体   | 输入1            | 输入2                    | 输出                    | 动作 |
| ------ | ---------------- | ------------------------ | ----------------------- | ---- |
| reader | reader名称字符串 | 各种类型几何文件所在路径 | panax的Json格式几何文件 | read |
|        | cgns             | /path/to/xxxx.cgns       | xxx.geom.pnx            |      |

* 实例：

  ```
  reader r = new reader("cgns")
  geometry g = r.read("/path/to/xxxx.cgns")
  ```

  ​

#### 运行几何转换写出（geometry reader writer）



#### 运行求解器（solver）