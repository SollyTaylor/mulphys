# Mulphys



### 代码模型

#### 运行几何读取

| 主体   | 输入1            | 输入2                    | 输出                    | 动作 |
| ------ | ---------------- | ------------------------ | ----------------------- | ---- |
| reader | reader名称字符串 | 各种类型几何文件所在路径 | panax的Json格式几何文件 | read |
|        | cgns             | /path/to/xxxx.cgns       | xxx.geom.mphs           |      |

* 实例：

  ```
  reader r = new reader("cgns")
  geometry g = r.read("/path/to/xxxx.cgns")
  ```



#### 运行几何转换写出（writer）



#### 运行求解器（solver）



processes

* file -> reader -> geometry
* geometry -> writer -> file
* geometry [, field, environment]   -> solver -> field
* field (init) -> dynamics -> field

runner

* model(dynamics1[,dynmiacs2...]) + reporter
* batch + model(dynamics1[,dynmiacs2...]) + reporter
* controller + model(dynamics1[,dynmiacs2...]) + reporter

simulation

* runner1 -> runner2 -> ... ->runnerN
* scheduler


！！！！！！！！

场的处理直接使用armadillo实现，所有元素直接作为mat出现，mat可以转换为scalar和vector

！！！！！！！！


1. 以上每一个对象都需要dump出来，查看其中的详细信息, mulphys dump <object-name>
2. solver不关心变量名称，只关心（1）场变量类型和输入顺序、（2）转换方式是格心格点插值积分、（3）输入输出几何
3. 不考虑边值问题，只考虑初值问题






！！！！！！！！

务必注意分区求解物理场，solver需要接受物理场进行进一步处理

！！！！！！！！









路线图和基本需求

1. 构建内核库，重建resource继承树和geometry类型
2. 实现reader，通过reader读取file生成geometry类型，此类型是可以共享的
3. 代码驱动的配置，全新的Panax语言
4. 支持插件扩展各种组件
5. 支持命令驱动的打包并形成可直接驱动的模型包，代码只提取需要的模型和插件模块进行运行
6. 支持多种几何文件的读取并形成统一的基于Json的数据文件，作为统一的数据交换格式，几何格式要开放，可以被其他工具方便使用
7. Json Schema解析处理使用rapidJson，Json本身的处理使用Qt框架
8. 各种组件存在依存关系，模块之间可以作为其他模块的初始化组成部分




命令行

- mphs read foo.txt (根据后缀名决定读取器，如果有多个对应则提示用户显式制定读取器) 输出bar.pnxf文件
- mphs write bar.pnxf foo.plt
- mphs run foo.pnx (执行panax文件)
- mphs describe component_foo (输出component_foo组件的详细信息)
- mphs version
- mphs help
- mphs package (打包panax为一个独立的可执行包)


